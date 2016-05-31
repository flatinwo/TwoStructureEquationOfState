//
//  background_terms.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/31/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "background_terms.hpp"

namespace TSEOS {
    
    /**
     \brief background term
     \return the background term
     \param n index of background term, t is temperature, and p is pressure
     */
    double Bterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  0: return 1;
            case  1: return p;
            case  2: return t;
            case  3: return p2;
            case  4: return p*t;
            case  5: return t2;
            case  6: return p2*p;
            case  7: return p2*t;
            case  8: return p*t2;
            case  9: return t2*t;
            case 10: return p2*p2;
            case 11: return p2*p*t;
            case 12: return p2*t2;
            case 13: return p*t2*t;
            case 14: return t2*t2;
            case 15: return p2*p2*p;
            case 16: return p2*p2*t;
            case 17: return p2*p*t2;
            case 18: return p2*t2*t;
            case 19: return p*t2*t2;
            case 20: return t2*t2*t;
            case 21: return p2*p2*p2;
            case 22: return p2*p2*p*t;
            case 23: return p2*p2*t2;
            case 24: return p2*p*t2*t;
            case 25: return p2*t2*t2;
            case 26: return p*t2*t2*t;
            case 27: return t2*t2*t2;
            case 28: return p2*p2*p2*p;
            case 29: return p2*p2*p2*t;
            case 30: return p2*p2*p*t2;
            case 31: return p2*p2*t2*t;
            case 32: return p2*p*t2*t2;
            case 33: return p2*t2*t2*t;
            case 34: return p*t2*t2*t2;
            case 35: return t2*t2*t2*t;
            case 36: return p2*p2*p2*p2;
            case 37: return p2*p2*p2*p*t;
            case 38: return p2*p2*p2*t2;
            case 39: return p2*p2*p*t2*t;
            case 40: return p2*p2*t2*t2;
            case 41: return p2*p*t2*t2*t;
            case 42: return p2*t2*t2*t2;
            case 43: return p*t2*t2*t2*t;
            case 44: return t2*t2*t2*t2;
                
        }
        return 0;
    }
    
    
    /**
     \brief first derivative of background term
     \return first derivative of background term with respect to t
     \param n index of background term, t is temperature, and p is pressure
     */
    double Btterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  2: return 1;
            case  4: return p;
            case  5: return 2*t;
            case  7: return p2;
            case  8: return 2*p*t;
            case  9: return 3*t2;
            case 11: return p2*p;
            case 12: return 2*p2*t;
            case 13: return 3*p*t2;
            case 14: return 4*t2*t;
            case 16: return p2*p2;
            case 17: return 2*p2*p*t;
            case 18: return 3*p2*t2;
            case 19: return 4*p*t2*t;
            case 20: return 5*t2*t2;
            case 22: return p2*p2*p;
            case 23: return 2*p2*p2*t;
            case 24: return 3*p2*p*t2;
            case 25: return 4*p2*t2*t;
            case 26: return 5*p*t2*t2;
            case 27: return 6*t2*t2*t;
            case 29: return p2*p2*p2;
            case 30: return 2*p2*p2*p*t;
            case 31: return 3*p2*p2*t2;
            case 32: return 4*p2*p*t2*t;
            case 33: return 5*p2*t2*t2;
            case 34: return 6*p*t2*t2*t;
            case 35: return 7*t2*t2*t2;
            case 37: return p2*p2*p2*p;
            case 38: return 2*p2*p2*p2*t;
            case 39: return 3*p2*p2*p*t2;
            case 40: return 4*p2*p2*t2*t;
            case 41: return 5*p2*p*t2*t2;
            case 42: return 6*p2*t2*t2*t;
            case 43: return 7*p*t2*t2*t2;
            case 44: return 8*t2*t2*t2*t;
                
        }
        return 0;
    }
    
    /**
     \brief first derivative of background term
     \return first derivative of background term with respect to p
     \param n index of background term, t is temperature, and p is pressure
     */
    double Bpterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  1: return 1;
            case  3: return 2*p;
            case  4: return t;
            case  6: return 3*p2;
            case  7: return 2*p*t;
            case  8: return t2;
            case 10: return 4*p2*p;
            case 11: return 3*p2*t;
            case 12: return 2*p*t2;
            case 13: return t2*t;
            case 15: return 5*p2*p2;
            case 16: return 4*p2*p*t;
            case 17: return 3*p2*t2;
            case 18: return 2*p*t2*t;
            case 19: return t2*t2;
            case 21: return 6*p2*p2*p;
            case 22: return 5*p2*p2*t;
            case 23: return 4*p2*p*t2;
            case 24: return 3*p2*t2*t;
            case 25: return 2*p*t2*t2;
            case 26: return t2*t2*t;
            case 28: return 7*p2*p2*p2;
            case 29: return 6*p2*p2*p*t;
            case 30: return 5*p2*p2*t2;
            case 31: return 4*p2*p*t2*t;
            case 32: return 3*p2*t2*t2;
            case 33: return 2*p*t2*t2*t;
            case 34: return t2*t2*t2;
            case 36: return 8*p2*p2*p2*p;
            case 37: return 7*p2*p2*p2*t;
            case 38: return 6*p2*p2*p*t2;
            case 39: return 5*p2*p2*t2*t;
            case 40: return 4*p2*p*t2*t2;
            case 41: return 3*p2*t2*t2*t;
            case 42: return 2*p*t2*t2*t2;
            case 43: return t2*t2*t2*t;
                
        }
        return 0;
    }
    
    /**
     \brief second derivative of background term
     \return second derivative of background term with respect to p and p
     \param n index of background term, t is temperature, and p is pressure
     */
    double Bppterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  3: return 2;
            case  6: return 6*p;
            case  7: return 2*t;
            case 10: return 12*p2;
            case 11: return 6*p*t;
            case 12: return 2*t2;
            case 15: return 20*p2*p;
            case 16: return 12*p2*t;
            case 17: return 6*p*t2;
            case 18: return 2*t2*t;
            case 21: return 30*p2*p2;
            case 22: return 20*p2*p*t;
            case 23: return 12*p2*t2;
            case 24: return 6*p*t2*t;
            case 25: return 2*t2*t2;
            case 28: return 42*p2*p2*p;
            case 29: return 30*p2*p2*t;
            case 30: return 20*p2*p*t2;
            case 31: return 12*p2*t2*t;
            case 32: return 6*p*t2*t2;
            case 33: return 2*t2*t2*t;
            case 36: return 56*p2*p2*p2;
            case 37: return 42*p2*p2*p*t;
            case 38: return 30*p2*p2*t2;
            case 39: return 20*p2*p*t2*t;
            case 40: return 12*p2*t2*t2;
            case 41: return 6*p*t2*t2*t;
            case 42: return 2*t2*t2*t2;
                
        }
        return 0;
    }
    
    /**
     \brief second derivative of background term
     \return second derivative of background term with respect to t and p
     \param n index of background term, t is temperature, and p is pressure
     */
    double Btpterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  4: return 1;
            case  7: return 2*p;
            case  8: return 2*t;
            case 11: return 3*p2;
            case 12: return 4*p*t;
            case 13: return 3*t2;
            case 16: return 4*p2*p;
            case 17: return 6*p2*t;
            case 18: return 6*p*t2;
            case 19: return 4*t2*t;
            case 22: return 5*p2*p2;
            case 23: return 8*p2*p*t;
            case 24: return 9*p2*t2;
            case 25: return 8*p*t2*t;
            case 26: return 5*t2*t2;
            case 29: return 6*p2*p2*p;
            case 30: return 10*p2*p2*t;
            case 31: return 12*p2*p*t2;
            case 32: return 12*p2*t2*t;
            case 33: return 10*p*t2*t2;
            case 34: return 6*t2*t2*t;
            case 37: return 7*p2*p2*p2;
            case 38: return 12*p2*p2*p*t;
            case 39: return 15*p2*p2*t2;
            case 40: return 16*p2*p*t2*t;
            case 41: return 15*p2*t2*t2;
            case 42: return 12*p*t2*t2*t;
            case 43: return 7*t2*t2*t2;
                
        }
        return 0;
    }
    
    
    /**
     \brief second derivative of background term
     \return second derivative of background term with respect to t and t
     \param n index of background term, t is temperature, and p is pressure
     */
    double Bttterm(int n, double t, double p)
    {
        double t2 = t*t;
        double p2 = p*p;
        switch(n)
        {
            case  5: return 2;
            case  8: return 2*p;
            case  9: return 6*t;
            case 12: return 2*p2;
            case 13: return 6*p*t;
            case 14: return 12*t2;
            case 17: return 2*p2*p;
            case 18: return 6*p2*t;
            case 19: return 12*p*t2;
            case 20: return 20*t2*t;
            case 23: return 2*p2*p2;
            case 24: return 6*p2*p*t;
            case 25: return 12*p2*t2;
            case 26: return 20*p*t2*t;
            case 27: return 30*t2*t2;
            case 30: return 2*p2*p2*p;
            case 31: return 6*p2*p2*t;
            case 32: return 12*p2*p*t2;
            case 33: return 20*p2*t2*t;
            case 34: return 30*p*t2*t2;
            case 35: return 42*t2*t2*t;
            case 38: return 2*p2*p2*p2;
            case 39: return 6*p2*p2*p*t;
            case 40: return 12*p2*p2*t2;
            case 41: return 20*p2*p*t2*t;
            case 42: return 30*p2*t2*t2;
            case 43: return 42*p*t2*t2*t;
            case 44: return 56*t2*t2*t2;
                
        }
        return 0;
    }

}
