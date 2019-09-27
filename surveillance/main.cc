#include "motion_detector.hpp"
#include "srv/system.hpp"
#include "srv/builder.hpp"

#include <opencv2/opencv.hpp>

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
using namespace hcv;

int main()
{
	int seconds_for_starting_alarm = 2;
	int seconds_for_stopping_alarm = 5;
	int seconds_for_stopping_recording = 15;
	int motion_detector_min_area = 500;
	string alarm_soundfile = "/app/config/sounds/airhorn.mp3";
	string alert_soundfile = "/app/config/sounds/smsalert.mp3";


	srv::SRVSystem* system = srv::SRVBuilder::BuildIdle(
			seconds_for_starting_alarm,
			seconds_for_stopping_alarm,
			seconds_for_stopping_recording,
			motion_detector_min_area,
			alarm_soundfile,
			alert_soundfile);

	assert(system != NULL);

	system->Start(100);

	return 0;
}
