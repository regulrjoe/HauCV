#ifndef SRV_BUILDER_HPP
#define SRV_BUILDER_HPP

#include "srv/system.hpp"

#include <cstdint>
#include <string>

namespace hcv
{
	namespace srv 
	{
		class SRVBuilder
		{
			public:
				static SRVSystem* BuildAlert(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t&, const string&, const string&);

				static SRVSystem* BuildIdle(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t&, const string&, const string&);
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_BUILDER_HPP
