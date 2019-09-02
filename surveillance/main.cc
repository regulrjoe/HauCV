#include "srv/system.hpp"
#include "srv/builder.hpp"
#include "retval.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

int main()
{
	int seconds_for_starting_alarm = 5;
	int seconds_for_stopping_alarm = 10;
	int seconds_for_stopping_recording = 15;

	assert(seconds_for_stopping_recording > seconds_for_stopping_alarm);

	hcv::srv::SRVSystem* system = hcv::srv::SRVBuilder::BuildIdle(
			seconds_for_starting_alarm, 
			seconds_for_stopping_alarm, 
			seconds_for_stopping_recording);

	assert(system != NULL);

	cout << hcv::RetValMsg::GetMsg(hcv::RetVal::OK) << "\n";
	cout << hcv::RetValMsg::GetMsg(hcv::RetVal::NOTOK) << endl;

	return 0;
}
