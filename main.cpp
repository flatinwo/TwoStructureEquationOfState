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
#include "thermodynamic_fit.hpp"
#include "thermodynamic_fit_quadratic.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    TSEOS::filelist_t myfiles;
    //TSEOS::data_t mydata;
    myfiles.push_back("density.dat");
    
    
    //TSEOS::loaddata("/Users/Folarin/Research/UMD/Code/LyonOptimizationLatinwov3/bin/Data/v30/",
    //mydata, myfiles);
    
    TSEOS::ThermodynamicFitQuadratic MyFit("/Users/Folarin/Research/UMD/Code/LyonOptimizationLatinwov3/bin/Data/v40/",
                                  myfiles);
    MyFit.setCriticalPt({190.,168.}, 0.0556);
    
    MyFit.run();
    
    
    std::cout << "me" << std::endl;
    std::cout << TSEOS::xe(1.0,1.0,0.02,1.0) << std::endl;
    
    
    return 0;
    
    /*
     VOLUME	344596
     DENSITY	941.826
     Cp	1194.94
     Cv	241.516
     Kt	0.000999613
     Cs	2.29244
     Ap	-0.0021185
     density.dat	Residual	8.49526
     */
    
}
