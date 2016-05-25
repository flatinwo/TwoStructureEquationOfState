//
//  io.hpp
//  TwoStructureEquationOfState
//
//  Created by Folarin Latinwo on 5/25/16.
//  Copyright © 2016 Folarin Latinwo. All rights reserved.
//

#ifndef io_hpp
#define io_hpp

#include <stdio.h>
#include "struct_def.h"

namespace TSEOS {
    void loaddata(const char* filename, data_t& data);
}

#endif /* io_hpp */
