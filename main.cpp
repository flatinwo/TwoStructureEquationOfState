//
//  main.cpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/25/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#include <iostream>
#include "struct_def.h"
#include "io.hpp"
#include "findxe.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    TSEOS::filelist_t myfiles;
    TSEOS::data_t mydata;
    myfiles.push_back("density.dat");
    
    
    TSEOS::loaddata("/Users/Folarin/Research/UMD/Code/LyonOptimizationLatinwov3/bin/Data/v30/",
                    mydata, myfiles);
    
    std::cout << "me" << std::endl;
    std::cout << TSEOS::xe(1.0,1.0,0.02,1.0) << std::endl;
    
    
    return 0;
    
    
}
