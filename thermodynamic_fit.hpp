//
//  thermodynamic_fit.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef thermodynamic_fit_hpp
#define thermodynamic_fit_hpp

#include <stdio.h>
#include "struct_def.h"
#include <gsl/gsl_vector.h>
#include <string>

namespace TSEOS {
    class ThermodynamicFit{
    public:
        ThermodynamicFit(const char* filename, filelist_t file_list);
        ~ThermodynamicFit();
        
        void setCriticalPt(state_pt_t, double);
        
    protected:
        double _MH20, _R, _rhoc;
        double _L0, _a, _b, _w0;
        
        data_t _alldata;
        state_pt_t _critical_pt;
        filelist_t _ppty;
        
        std::vector<std::string> _specname;
        std::vector<double> _specs;
        std::vector<double> _delta_spec;
        std::vector<double> _bg_terms;
        std::vector<double> _delta_bg_terms;
        
        double evaluate(data_pt&);
        
        double Bxx(state_pt_t&, double (*funcp)(int, double, double));  //function pointer
        double Bp(state_pt_t&, double Lp, double w0);
        
        virtual double _getc01(double Lp, double w0);
        virtual double _setup();
        
        double _residual(const gsl_vector* x);
        double _residual(data_pt&);
        double _property_residual();
        void _optimize();
        
    private:
        double _del;
    };
}

#endif /* thermodynamic_fit_hpp */
