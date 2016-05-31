//
//  findxe.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef findxe_hpp
#define findxe_hpp

#include <stdio.h>

namespace TSEOS {
    /** Contains functions and structs for finding equilibrium
        mole fraction at specified:
        temperature t,
        pressure p,
        -ln(equilibrium constant), L
        interaction parameter, W
     */
    double xe(double t, double p, double L, double W);
    
    
    double solfun(double x, void * p);
    struct xparams{
        double LL; //-ln K
        double WW; //chi parameter
    };
}

#endif /* findxe_hpp */
