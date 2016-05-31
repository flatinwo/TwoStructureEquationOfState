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

namespace TSEOS {
    ThermodynamicFit::ThermodynamicFit(const char* filename, filelist_t filelist){
        loaddata(filename, _alldata, filelist);
        _ppty = filelist;
        _critical_pt = {183.,172.};
        _rhoc = 0.0556;
    }
    
    ThermodynamicFit::~ThermodynamicFit(){
        
    }
    
    void ThermodynamicFit::setCriticalPt(state_pt_t pt, double rhoc){
        _critical_pt = pt;
        _rhoc = rhoc;
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
    
    double ThermodynamicFit::_residual(data_pt& pt){
        double unc = pt.second.uncertainty;
        double sres = evaluate(pt) - pt.second.property;
        return sres*sres/(unc*unc);
    }
    
    double ThermodynamicFit::_residual(const gsl_vector* x){
        int j=0; double res=0.;
        for (auto& i : _bg_terms) i = gsl_vector_get(x, j++);
        for (auto& i: _specs) i = gsl_vector_get(x, j++);
        
        std::accumulate(_alldata.begin(), _alldata.end(), res);
        
        assert(_alldata.size() > 0);
        return res/((double) _alldata.size());
    }
}
