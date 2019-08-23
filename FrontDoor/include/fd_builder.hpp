#ifndef FD_BUILDER_HPP
#define FD_BUILDER_HPP

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

#endif // FD_BUILDER_HPP
