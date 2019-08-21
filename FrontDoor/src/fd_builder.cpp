#include "fd_builder.hpp"

#include "body_detector.hpp"
#include "fd_state.hpp"

namespace hcv
{
	///////////////////////////
	FDSystem* FDBuilder::BuildAlert(const uint8_t& i_seconds_for_starting_alarm,
			const uint8_t& i_seconds_for_stopping_alarm,
			const uint8_t& i_seconds_for_stopping_recording)
	{
		return new FDSystem(new BodyDetector(), 
				AlertState::InstanceAsBase(),
				i_seconds_for_starting_alarm,
				i_seconds_for_stopping_alarm,
				i_seconds_for_stopping_recording);
	}

	///////////////////////////
	FDSystem* FDBuilder::BuildIdle(const uint8_t& i_seconds_for_starting_alarm,
			const uint8_t& i_seconds_for_stopping_alarm,
			const uint8_t& i_seconds_for_stopping_recording)
	{
		return new FDSystem(new BodyDetector(), 
				IdleState::InstanceAsBase(),
				i_seconds_for_starting_alarm,
				i_seconds_for_stopping_alarm,
				i_seconds_for_stopping_recording);
	}

} // namespace hcv
