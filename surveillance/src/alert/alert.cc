#include "alert/alert.hpp"

#include <dbg.h>

#include <iostream>

#include <stdlib.h>

using namespace std;

namespace hcv
{

	///////////////
	Alert::Alert(const std::string& i_soundfile) : m_soundfile(i_soundfile)
	{
		dbg("Alert::Alert()");
	}

	///////////////
	Alert::~Alert()
	{
		dbg("Alert::~Alert()");
	}

	///////////////
	void Alert::Play()
	{
		dbg("Alert::Play()");
		dbg(m_soundfile);

		int pid;
		string player = "mpg123 " + m_soundfile;


		pid = fork();
		if (pid == 0)
		{
			cout << "Child process." << endl;
			
			execlp("/usr/bin/mpg123", " ", m_soundfile.c_str(), NULL);

			_exit(0);
		}
//		else
//		{
//			cout << "Parent process." << endl;
//
//			wait();
//		}
	}

} // namespace hcv
