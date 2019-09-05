#ifndef SRV_BUILDER_HPP
#define SRV_BUILDER_HPP

#include "srv/system.hpp"

#include <cstdint>

namespace hcv
{
	namespace srv 
	{
		class SRVBuilder
		{
			public:
				static SRVSystem* BuildAlert(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t& = 500);

				static SRVSystem* BuildIdle(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t& = 500);
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_BUILDER_HPP
