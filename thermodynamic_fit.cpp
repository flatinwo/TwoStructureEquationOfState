//
//  thermodynamic_fit.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "thermodynamic_fit.hpp"
#include "io.hpp"
#include "background_terms.hpp"
#include <cassert>
#include <algorithm>
#include <numeric> //std::accumulate
#include <functional> //std::bind
#include <iostream>
#include <cmath>
#include "findxe.hpp"
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include "optimize.hpp"

namespace TSEOS {
    
    ThermodynamicFit::ThermodynamicFit(const char* filepath, filelist_t filelist){
        loaddata(filepath, _alldata, filelist);
        _ppty = filelist;
        _critical_pt = {183.,172.};
        _rhoc = 0.0556;
        _property_residual_flag = false;
        _number_of_iterations = 15000;
        
        data_pt pt;
        pt.first.temperature = 200.;
        pt.first.pressure = 100;
        pt.second.type = "test";
        pt.second.typenum = DENSITY;
        _test_pts.push_back(pt);
        
        _init();
        refresh();
    }
    
    ThermodynamicFit::~ThermodynamicFit(){
    }
    
    void ThermodynamicFit::_init(){
        _MH2O = 0.018015268,
        _R = 8.3144621;

    }
    
    void ThermodynamicFit::refresh(){
        _rhocR = _rhoc*_R;
        _rhocRTc = _rhocR*_critical_pt.temperature;
        _pc__rhocRTc = _critical_pt.pressure/_rhocRTc;
        _pc_S0__rhocRTc = (_critical_pt.pressure - _S0)/_rhocRTc;
        
    }
    
    void ThermodynamicFit::run(){
        _sortData();
        _optimize();
    }
    
    void ThermodynamicFit::setCriticalPt(state_pt_t pt, double rhoc){
        _critical_pt = pt;
        _rhoc = rhoc;
        refresh();
    }
    
    void ThermodynamicFit::setPropertyResidualFlag(bool flag){
        _property_residual_flag = flag;
    }
    
    //uses functions of background terms
    double ThermodynamicFit::Bxx(state_pt_t& pt, double (*Bfunc) (int, double, double)){
        double sum=0;int j=0;
        for (auto& i : _bg_terms) sum += (i*(Bfunc(j++, pt.temperature, pt.pressure)));
        return sum;
    }
    
    double ThermodynamicFit::Bp(state_pt_t& pt, double Lp, double w0){
        return _getc01(Lp, w0) + Bxx(pt, Bpterm);
    }
    
    double ThermodynamicFit::residualpt(data_pt& pt){
        double unc = pt.second.uncertainty;
        double sres = evaluate(pt) - pt.second.property;
        return sres*sres/(unc*unc);
    }
    
    double ThermodynamicFit::residual(const gsl_vector* x){
        int j=0;
        for (auto& i : _bgname) _bg_terms[i] = gsl_vector_get(x, j++);
        for (auto& i: _specs) *i = gsl_vector_get(x, j++);
        
        //auto f = std::bind(&ThermodynamicFit::_residualpt, std::placeholders::_1); //can't use same function name within bind
        
        double res = std::accumulate(_alldata.begin(), _alldata.end(), 0.0F, [&] (const double acc, data_pt& data) { return acc + residualpt(data);}); //accumulate not always faster, use -funroll-loops
        
        assert(_alldata.size() > 0);
       // std::cout << res/((double) _alldata.size()) << std::endl;
        return res/((double) _alldata.size());
    }
    
    void ThermodynamicFit::_sortData(){
        _sorted_alldata.resize(_ppty.size());
        for (unsigned int i=0; i<_alldata.size(); i++)
            for (unsigned int j=0; j < _ppty.size(); j++)
                if (_ppty[j].compare(_alldata[i].second.type) == 0)
                    _sorted_alldata[j].push_back(&_alldata[i]);
        
    }
    
    
    double ThermodynamicFit::_getc01(double Lp, double w0){;
        assert(-1.);
        return 0.;
    }
    
    void ThermodynamicFit::_setupEvaluate(){
        assert(-1);
    }
    
    void ThermodynamicFit::_optimize(){
       /* construction for optimization*/
        gsl_vector* x;
        assert(_bgname.size() > 0);
        assert(_specs.size() > 0);
        assert(_bgname.size()==_delta_bg_terms.size());
        
        x = gsl_vector_alloc(_bgname.size()+_specs.size());
        gsl_vector* step = gsl_vector_alloc(_bgname.size()+_specs.size());
        
        unsigned int j=0;
        for (auto& i : _bgname) gsl_vector_set(x, j++, _bg_terms[i]);
        for (auto& i : _specs) gsl_vector_set(x, j++, *i);
        
        std::cerr << "Size of GSL vector x is " << x->size << std::endl;
        
        j=0;
        for (auto& i : _delta_bg_terms) gsl_vector_set(step, j++, i);
        for (auto& i : _delta_specs) gsl_vector_set(step, j++, i);
        
        
        //maybe make a separate class for GSL minimizers
        
        int status;
        const gsl_multimin_fminimizer_type* T = gsl_multimin_fminimizer_nmsimplex2rand;
        gsl_multimin_fminimizer* minimizer = gsl_multimin_fminimizer_alloc(T, _bgname .size()+_specs.size());
        gsl_multimin_function fit;
        fit.f = &getResidual;
        fit.n = _bgname.size() + _specs.size();
        fit.params = this;
        
        double xx=200, yy=1000;
        bool testme = true;
        gsl_multimin_fminimizer_set(minimizer, &fit, x, step);
        for (unsigned int n=0; n<_number_of_iterations; n++) {
            if (testme) {
                std::cout << evaluate(_test_pts[0]) << "\n";
                testme = false;
            }
            
            if ((n-200)%500==0) {
                yy=gsl_multimin_fminimizer_minimum(minimizer);
            }
            status = gsl_multimin_fminimizer_iterate(minimizer);
            gsl_vector* current_values = gsl_multimin_fminimizer_x(minimizer);
            if (n%500==0) {
                xx = gsl_multimin_fminimizer_minimum(minimizer);
                unsigned int k= (unsigned int)_bgname.size();
                for (unsigned int i=0; i<_specname.size();i++) std::cout << _specname[i] << "\t" << gsl_vector_get(current_values, k++) << ", ";
                for (unsigned int i=0; i<_bgname.size(); i++)
                    std::cout << "c[[" << _bgname[i] <<"]] = " << gsl_vector_get(current_values, i) << ", ";
                std::cout << "\n\n Iteration number " << n << "\n\n Residual = " << gsl_multimin_fminimizer_minimum(minimizer) << "\n\n";
               
                for (auto& pt : _test_pts) evaluate(pt,true);
                
                //gsl_multimin_fdfminimizer_restart(minimizer);
                property_residual(current_values);
                std::cout << "\n\n\n";
            
            }
        }
        
        
    }
    
    void ThermodynamicFit::property_residual(const gsl_vector* x){
        int j=0;
        for (auto& i : _bgname) _bg_terms[i] = gsl_vector_get(x, j++);
        for (auto& i: _specs) *i = gsl_vector_get(x, j++);
        
        for (unsigned int j=0, size=(unsigned int)_ppty.size(); j<size; j++) {
            double res = std::accumulate(_sorted_alldata[j].begin(), _sorted_alldata[j].end(), 0.0F,
                                         [&] (const double acc, data_pt* data) { return acc + residualpt(*data);});
            std::cout << _sorted_alldata[j][0]->second.type << "\tResidual\t" << res/((double) _sorted_alldata[j].size()) << std::endl; //use files for data
        }
    }
    
    double ThermodynamicFit::evaluate(data_pt& pt, bool all){
        _t = (pt.first.temperature - _critical_pt.temperature)/_critical_pt.temperature;
        _p = (pt.first.pressure  - _critical_pt.pressure)/(_rhocRTc);
        _tau = 1. + _t;
        
        _setupEvaluate();
        
        double ses = _p + _pc__rhocRTc -(_S0/(_rhocRTc) + _S1/(_rhocR)*_t + _S2*_critical_pt.temperature/(_rhocR)*_t*_t);
        //double gs = (_A0 + _A1*_t)*pow(ses,1.5);
        double vs = 1.5*(_A0 + _A1*_t)*pow(ses,0.5);
        //double kts = 0.75*(_A0 + _A1*_t)*pow(ses,-0.5);
        
        
        double x = xe(_t,_p,_L,_W);
        double dxdt = (_Lt + log(x/(1-x)) + _Wt*(1.-2*x))/(2*_W - _tau/(x*(1.0-x)));
        double dxdp = (_Lp + _Wp*(1-2*x))/(2*_W - _tau/(x*(1-x)));
        
        /* For no spinodal
         double v = Bp(t,p,Lp,w0) + x*Lp + Wp*x*(1-x);*/ //volume in dimensionless units
        
        
        _reduced_pt.temperature = _t; //use a reference or pointer
        _reduced_pt.pressure = _p;
        
        /*For spinodal*/
        double v = Bp(_reduced_pt,_Lp,_w0) + vs + x*_Lp + _Wp*x*(1-x); //volume in dimensionless units.
        
        double kt = -1/v*(Bxx(_reduced_pt,Bppterm) + x*_tau*_Lpp + _tau*_Wpp*x*(1-x) + (_tau*_Lp + _tau*_Wp*(1-2*x))*dxdp); //isothermal compressibility in dimensionless units
        
        double cp = -_tau*(Bxx(_reduced_pt,Bttterm) + 2*x*_Lt + 2*x*(1-x)*_Wt + _tau*x*_Ltt + _tau*_Wtt*x*(1-x) + (_tau*_Lt + _tau*(1-2*x)*_Wt)*dxdt); //heat capcity at constant cp
       
        double ap = 1/v*(Bxx(_reduced_pt,Btpterm) + x*_Lp + x*_tau*_Ltp + _Wp*x*(1-x)
                         + _tau*_Wtp*x*(1-x) + (_tau*_Lp + _tau*_Wp*(1-2*x))*dxdt);
        
        double V = v/_rhoc*_MH2O*1e6; //m^3 kg^-1
        double Rho = _rhoc*_MH2O*1e6/v; //kg m^-3
        double KT = kt/(_rhocRTc); //Reciprocal MPa
        double CP = cp*_R/_MH2O; //Specific Heat: J Kg^-1 K^-1
        double AP = ap/_critical_pt.temperature; //Reciprocal Kelvins
        double CV = CP - 1e6*pt.first.temperature*AP*AP/(Rho*KT);
        double Cs=0.;
        
        if (CP/(Rho*CV*KT) > 0) Cs = sqrt(CP/(Rho*CV*KT));
        //else std::cerr << "Warning: speed of sound is imaginary! \n";
        
        if (!all) {
            switch (pt.second.typenum) {
                case VOLUME:    return V;
                case DENSITY:   return Rho;
                case HEATCAPACITY_P:    return CP;
                case HEATCAPACITY_V:    return CV;
                case COMPRESSIBILITY:   return KT;
                case SPEEDOFSOUND:  return Cs;
                case EXPANSIVITY:   return AP;
                case JUNK:
                    std::cerr << "Unknown data type\n";
                    exit(-1);
            }
        }
        else{
            std::cout   << "VOLUME\t" <<    V
                        << "\nDENSITY\t" << Rho
                        << "\nCp\t" <<      CP
                        << "\nCv\t" <<      CV
                        << "\nKt\t" <<      KT
                        << "\nCs\t" <<      Cs
                        << "\nAp\t" <<      AP
                        << std::endl;
            return 0.;
        }
    }
}
