#ifndef MACROS_HPP
#define MACROS_HPP

#ifndef NDEBUG
#define PRINT(to_print) cout << to_print << endl
#else
#define PRINT(to_print) while(0) // Avoid empty statements.
#endif

#define RVMsg(rv) RetValMsg::GetMsg(rv)

#endif // MACROS_HPP
