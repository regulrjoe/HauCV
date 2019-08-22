#include "fd_system.hpp"
#include "fd_builder.hpp"

#include <assert.h>

int main()
{
	int seconds_for_starting_alarm = 5;
	int seconds_for_stopping_alarm = 10;
	int seconds_for_stopping_recording = 15;

	assert(seconds_for_stopping_recording > seconds_for_stopping_alarm);

	hcv::FDSystem* system = hcv::FDBuilder::BuildIdle(
			seconds_for_starting_alarm, 
			seconds_for_stopping_alarm, 
			seconds_for_stopping_recording);

	assert(system != NULL);

	return 0;
}
