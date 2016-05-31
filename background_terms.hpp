//
//  background_terms.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//


#ifndef background_terms_hpp
#define background_terms_hpp

#include <stdio.h>
#include "struct_def.h"

//maybe replace Bttterm with Btt and so on...

namespace TSEOS{
    /** Contains functions and derivatives for the 
        background terms contributions to the 
        Gibbs free energy.
     */
    double Bterm(int n, double t, double p);
    double Btterm(int n, double t, double p);
    double Bpterm(int n, double t, double p);
    double Bppterm(int n, double t, double p);
    double Btpterm(int n, double t, double p);
    double Bttterm(int n, double t, double p);
}

#endif /* background_terms_hpp */
