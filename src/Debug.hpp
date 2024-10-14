#pragma once

#define DEBUG

#ifdef DEBUG
		#include <iostream>
    #define DEBUG_LOG(msg) std::cerr << "DEBUG: " << msg << std::endl;
#else
    #define DEBUG_LOG(msg)
#endif
