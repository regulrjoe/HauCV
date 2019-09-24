#ifndef MACROS_HPP
#define MACROS_HPP

#include <iostream>

#ifndef NDEBUG
#define PRINT(to_print) cout << to_print << endl
#else
#define PRINT(to_print) while(0) // Avoid empty statements.
#endif

#define RCMsg(rc) RCodeMsg::GetMsg(rc)

#define PRINTERR(rc) std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] An ERROR was caught: " << RCMsg(rc) << "." << std::endl

#define PRINTEXC(e) std::cerr <<  "[" << __FILE__ << ":" << __LINE__ << "]An EXCEPTION was caught: " << e.what() << "." << std::endl;
 

#endif // MACROS_HPP
