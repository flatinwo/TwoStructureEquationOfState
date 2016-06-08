//
//  optimize.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 6/2/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef optimize_hpp
#define optimize_hpp

#include <stdio.h>
#include "thermodynamic_fit.hpp"

namespace TSEOS {
    double getResidual(const gsl_vector* x, void* params);
}

#endif /* optimize_hpp */
