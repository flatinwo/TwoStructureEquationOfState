//
//  findxe.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "findxe.hpp"
#include <iostream>
#include <gsl/gsl_roots.h>

namespace TSEOS {

    
    /**
     \brief first derivative of G with respect to x
     \return the dG/dx at x
     \param n x is mole fraction of LDL, p is a pointer
              to parameters for LL and WW
                LL is -lnK, WW is chi parameter, and t is temperature
     */
    
    
    double solfun (double x, void * p)
    {
        struct xparams * params = (struct xparams *)p;
        double LL = (params->LL);
        double WW = (params->WW);
        double T = (params->t + 1);
        
        return LL + T*log(x/(1-x)) + WW*(1-2*x);
    }
    
    
    
    /**
     \brief solves for xe
     \return equilibrium value of x
     \param t is temperature, p is pressure, 
            L is -ln K, and W is interaction parameter
     */
    
    double xe(double t, double p, double L, double W)
    {
        double lower=0.00001, upper=0.999999, x_hi, x_lo;
        if (L==0 && p < 0) return 0.5;
        if (L<0)
        {
            lower = 0.5;
            upper = 0.999999;
        }
        if (L>0)
        {
            lower = 0.0000001;
            upper = 0.5;
        }
        
        const gsl_root_fsolver_type * T = gsl_root_fsolver_brent;
        gsl_root_fsolver * s = gsl_root_fsolver_alloc(T);
        
        struct xparams params = {L,W,t};
        
        
        gsl_function F;
        F.function = &solfun;
        F.params = &params;
        
        gsl_root_fsolver_set(s, &F, lower, upper);
        
        int iter;
        int status = -2;
        for (iter = 1; iter < 100; iter++)
        {
            gsl_root_fsolver_iterate(s);
            x_lo = gsl_root_fsolver_x_lower(s);
            x_hi = gsl_root_fsolver_x_upper(s);
            if( (x_hi - x_lo)/x_lo < 1e-4 && (x_hi - x_lo) < 1e-7)
            {
                status = 1;
                break; //why is this command necessary?
            }
        }
        if (status != 1) std::cout <<  "Warning: findxe did not converge after 100 steps" << std::endl;
        return gsl_root_fsolver_root(s);
    }
    
}