#ifndef MACROS_HPP
#define MACROS_HPP

#include <dbg.h>

#include <iostream>

#ifndef PRINT_INFO_MACRO_DISABLE
#define printINFO(INFO) \
	std::cout << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ << ") INFO: " << INFO << "." << endl;
#else
#define printINFO(INFO) while(0) // Avoid empty statememts.
#endif

#ifndef PRINT_ERROR_MACRO_DISABLE
#define printERROR(ERROR) \
	std::cerr << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ << ") ERROR: " << ERROR << "." << endl;
#else
#define printERROR(ERROR) while(0) // Avoid empty statememts.
#endif

#define RCMsg(rc) RCodeMsg::GetMsg(rc)

#endif // MACROS_HPP
