//
//  optimize.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 6/2/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "optimize.hpp"
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

namespace TSEOS {
    double getResidual(const gsl_vector* x, void* params){
        ThermodynamicFit* p = (ThermodynamicFit *) params;
        return p->residual(x);
    }
    
}