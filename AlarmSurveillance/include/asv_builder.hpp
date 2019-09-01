#ifndef ASV_BUILDER_HPP
#define ASV_BUILDER_HPP

#include "asv_system.hpp"

#include <cstdint>

namespace hcv
{
	namespace asv
	{
		class ASVBuilder
		{
			public:
				static ASVSystem* BuildAlert(const uint8_t&, const uint8_t&, const uint8_t&);

				static ASVSystem* BuildIdle(const uint8_t&, const uint8_t&, const uint8_t&);
		};

	} // namespace asv
} // namespace hcv

#endif // FD_BUILDER_HPP
