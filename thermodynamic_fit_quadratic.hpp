//
//  thermodynamic_fit_quadratic.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 6/2/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef thermodynamic_fit_quadratic_hpp
#define thermodynamic_fit_quadratic_hpp

#include <stdio.h>
#include "thermodynamic_fit.hpp"

namespace TSEOS {
    class ThermodynamicFitQuadratic : public ThermodynamicFit{
    public:
        ThermodynamicFitQuadratic(const char* filepath, filelist_t file_list);
        
    protected:
        double _getc01(double Lp, double w0);
        void _setupEvaluate();
        void _init();
        
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

#endif /* thermodynamic_fit_quadratic_hpp */
