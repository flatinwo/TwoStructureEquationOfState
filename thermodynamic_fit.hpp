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
        ThermodynamicFit(const char* filepath, filelist_t file_list);
        ~ThermodynamicFit();
        
        void setCriticalPt(state_pt_t, double);
        void setPropertyResidualFlag(bool flag);
        void setNumberOfIterations(unsigned short num);

        double residual(const gsl_vector* x);
        double residualpt(data_pt&);
        void property_residual(const gsl_vector* x);
        void run();
        
        void refresh();
        
    protected:
        double _MH2O, _R, _rhoc;
        double  _t, _p, _tau;
        double _rhocR, _rhocRTc, _pc__rhocRTc;
        double _pc_S0__rhocRTc;
        double _L, _Lt, _Lp, _Ltt, _Ltp, _Lpp;
        double _W, _Wt, _Wp, _Wtt, _Wtp, _Wpp;
        
        bool _property_residual_flag;
        unsigned short _number_of_iterations;
        
        data_t _alldata;
        state_pt_t _critical_pt;
        state_pt_t _reduced_pt;
        filelist_t _ppty;
        std::vector< std::vector<data_pt*> > _sorted_alldata;
        
        std::vector<std::string> _specname; //tooptimize, maybe make a struct for this
        std::vector<unsigned int> _bgname;  //tooptimize
        
        std::vector<double*> _specs;
        std::vector<double> _delta_specs;
        std::vector<double> _bg_terms;
        std::vector<double> _delta_bg_terms;
        std::vector<data_pt> _test_pts;
        
        double evaluate(data_pt&, bool=false);
        
        double Bxx(state_pt_t&, double (*funcp)(int, double, double));  //function pointer
        double Bp(state_pt_t&, double Lp, double w0);
        
        virtual double _getc01(double Lp, double w0);
        virtual void _setupEvaluate();
        
        void _optimize();
        void _sortData();
        virtual void _init();
        
    private:
        const double _del = 1;
        const double _f = 0;
        const double _A0 = -0.01;
        const double _A1 = -0.03;
        const double _S0 = -452;
        const double _S1 = 2.61;
        const double _S2 = -0.0065;
        
        double _L0, _a, _b, _w0, _d;
        
        
    };
}

#endif /* thermodynamic_fit_hpp */
