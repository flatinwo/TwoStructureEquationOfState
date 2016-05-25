//
//  io.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/25/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include "io.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <utility>

namespace TSEOS {
    void loaddata(const char* filepath, data_t& data, filelist_t& files){
        assert(files.size() > 0);
        
        state_pt_t pt; property_t ppty;
        std::string str;
        data.clear();
        
        for (auto& i : files) {
            std::string datafilename = std::string(filepath)+i;
            std::ifstream datafile(datafilename.c_str());
            
            if (datafile.is_open()) {
                std::cerr << datafilename << " is now open...\n";
                while (getline(datafile, str)) {
                    std::istringstream is1(str);
                    is1 >> pt.temperature
                        >> pt.pressure
                        >> ppty.property
                        >> ppty.uncertainty
                        >> ppty.source;
                    ppty.type = i;
                    
                    data.push_back(std::make_pair(pt, ppty));
                }
            }
            else std::cerr << datafilename << " cannot be found\n";
        }
        return;
    }
}