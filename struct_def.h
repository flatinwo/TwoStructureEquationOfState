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
    
    enum DataType {DENSITY, VOLUME, HEATCAPACITY_P, COMPRESSIBILITY, EXPANSIVITY, HEATCAPACITY_V, SPEEDOFSOUND, JUNK};
    
    struct state_pt_t{
        double temperature;
        double pressure;
    };
    
    struct property_t{
        double property;
        double uncertainty;
        std::string type;
        std::string source;
        DataType typenum; //maybe use a union here
    };
    
    typedef std::pair<state_pt_t,property_t> data_pt;
    typedef std::vector< std::pair <state_pt_t,property_t> > data_t;
    typedef std::vector<std::string> filelist_t;

}


#endif /* struct_def_h */
