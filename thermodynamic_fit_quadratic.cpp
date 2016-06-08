//
//  thermodynamic_fit_quadratic.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 6/2/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "thermodynamic_fit_quadratic.hpp"
#include <cmath>

namespace TSEOS {
    ThermodynamicFitQuadratic::ThermodynamicFitQuadratic(const char* filepath, filelist_t file_list):ThermodynamicFit(filepath,file_list){
        _init();
        refresh();
    }
    
    double ThermodynamicFitQuadratic::_getc01(double Lp, double w0){
        return (1. - 0.5*_L0*_a - 0.25*_w0 - 1.5*_A0*sqrt(_pc_S0__rhocRTc));
    }
    
    void ThermodynamicFitQuadratic::_setupEvaluate(){
        _L = _L0*(_t + _a*_p + _b*_t*_p + _d*_p*_p + _f*_t*_t);
        _Lt = _L0*(1 + _b*_p + 2*_f*_t);
        _Lp = _L0*(_a + _b*_t + 2*_d*_p);
        _Ltt = 2*_L0*_f;
        _Lpp = 2*_L0*_d;
        _Ltp = _L0*_b;
        
        _W = _del*(2 + _w0*_p) + (1 - _del)*_tau*(2 + _w0*_p),
        _Wp = _del*_w0 + (1 - _del)*_tau*_w0,
        _Wt = (1 - _del)*(2 + _w0*_p),
        _Wpp = 0,
        _Wtt = 0,
        _Wtp = (1 - _del)*_w0;
    }
    
    void ThermodynamicFitQuadratic::_init(){
        _MH2O = 0.018015268,
        _R = 8.3144621;
        
        _bgname.clear();
        _bgname.push_back(3);
        _bgname.push_back(4);
        _bgname.push_back(7);
        _bgname.push_back(8);
        _bgname.push_back(11);
        
        _L0 = 1.53;
        _a = 0.17;
        _b = -0.05;
        _d = 0.003;
        _w0 = 0.03;
        
        _specs.clear();
        _specs.push_back(&_L0);
        _specs.push_back(&_a);
        _specs.push_back(&_b);
        _specs.push_back(&_d);
        _specs.push_back(&_w0);
        
        _delta_specs.clear();
        _delta_specs.push_back(0.001);
        _delta_specs.push_back(0.0001);
        _delta_specs.push_back(0.001);
        _delta_specs.push_back(0.0001);
        _delta_specs.push_back(0.001);
        
        
        _specname.clear();
        _specname.push_back("L0");
        _specname.push_back("a");
        _specname.push_back("b");
        _specname.push_back("d");
        _specname.push_back("w0");
        
        _delta_bg_terms.resize(_bgname.size(),0.001);
        
        _bg_terms.resize(28,0.);
        _bg_terms[_bgname[0]] = -0.00367108;
        _bg_terms[_bgname[1]] = 0.151317;
        _bg_terms[_bgname[2]] = -0.00149268;
        _bg_terms[_bgname[3]] = -0.0218064;
        _bg_terms[_bgname[4]] = 0.00110725;
    }
    
}
