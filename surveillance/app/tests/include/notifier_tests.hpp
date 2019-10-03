#ifndef NOTIFIER_TESTS_HPP
#define NOTIFIER_TESTS_HPP

#include "notifier.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;
using namespace std;
using namespace std::chrono;

namespace {

	//////////////////////
	////// NOTIFIER //////
	//////////////////////

	// AddDestination() & GetDestination().
	TEST(NotifierTest, AddAndGetDestination)
	{
		Notifier notifier;
		string tmp;

		EXPECT_EQ(notifier.AddDestination("Destination"), RetVal::OK);
		EXPECT_EQ(notifier.GetDestination(0, &tmp), RetVal::OK);
		EXPECT_EQ(tmp, "Destination");
		EXPECT_EQ(notifier.AddDestination(""), RetVal::NOTOK);
		EXPECT_EQ(notifier.GetDestination(1, &tmp), RetVal::NOTOK);
	}

	// NotifyAlarm()
//	TEST(NotifierTest, NotifyAlarm)
//	{
//		Notifier notifier;
//
//		EXPECT_EQ(
//				notifier.NotifyAlarm(
//					system_clock::to_time_t(
//						system_clock::now())),
//				RetVal::OK);
//
//	}

	// NotifyAlert()
//	TEST(NotifierTest, NotifyAlert)
//	{
//		Notifier notifier;
//
//		EXPECT_EQ(
//				notifier.NotifyAlert(
//					system_clock::to_time_t(
//						system_clock::now())),
//				RetVal::OK);
//	}

} // namespace

#endif // NOTIFIER_TESTS_HPP
