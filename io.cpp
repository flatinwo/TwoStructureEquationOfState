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
        analyzedata(data);
        return;
    }
    
    void analyzedata(data_t& data){
        for (auto& i: data ) {
            if (i.second.type.find("density") != std::string::npos) i.second.typenum = DataType::DENSITY;
            else if (i.second.type.find("volume") != std::string::npos) i.second.typenum = DataType::VOLUME;
            else if (i.second.type.find("compressibility") != std::string::npos) i.second.typenum = DataType::COMPRESSIBILITY;
            else if (i.second.type.find("expansivity") != std::string::npos) i.second.typenum = DataType::EXPANSIVITY;
            else if (i.second.type.find("Cp") != std::string::npos) i.second.typenum = DataType::HEATCAPACITY_P;
            else if (i.second.type.find("Cv") != std::string::npos) i.second.typenum = DataType::HEATCAPACITY_V;
            else if (i.second.type.find("Cs") != std::string::npos) i.second.typenum = DataType::SPEEDOFSOUND;
            else i.second.typenum = DataType::JUNK;
        }
    }
    
}