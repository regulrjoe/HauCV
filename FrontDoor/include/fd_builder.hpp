#ifndef fd_builder_hpp
#define fd_builder_hpp

#include "fd_system.hpp"

#include <cstdint>

namespace hcv
{
	class FDBuilder
	{
		public:
			static FDSystem* BuildAlert(const uint8_t&, const uint8_t&, const uint8_t&);

			static FDSystem* BuildIdle(const uint8_t&, const uint8_t&, const uint8_t&);
	};

} // namespace hcv

#endif // system_builder_hpp


