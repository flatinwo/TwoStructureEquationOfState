//
//  struct_def.h
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/25/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef struct_def_h
#define struct_def_h

#include <vector>
#include <utility>
#include <map>
#include <string>

namespace TSEOS {
    struct state_pt_t{
        double temperature;
        double pressure;
    };
    
    struct property_t{
        double property;
        double uncertainty;
        std::string datatype;
        std::string units;
    };
    
    typedef std::map<state_pt_t,property_t> data_t;

}


#endif /* struct_def_h */
