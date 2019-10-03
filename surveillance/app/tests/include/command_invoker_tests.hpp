#ifndef SOUND_CONTROLLER_TESTS_HPP
#define SOUND_CONTROLLER_TESTS_HPP

#include "command_invoker.hpp"
#include "commands.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;

namespace {

	/////////////////////////////
	///// COMMAND INVOKER ///////
	/////////////////////////////
	
	// StartAlarmCommand
	TEST(CommandInvokerTest, StartAlarmCommand)
	{
		CommandInvoker invoker;

		invoker.SetCommand("start_alarm", new StartAlarmCommand("tcp://127.0.0.1:1111", "smsalert.mp3"));

		RetVal rv = RetVal::OK;
		try
		{
			invoker.Invoke("start_alarm");
		}
		catch(const RetVal& rv_)
		{
			rv = rv_;
		}
		EXPECT_EQ(rv, RetVal::OK);

		invoker.SetCommand("start_alarm", new StartAlarmCommand("tcp://127.0.0.1:1111", "mmsalert.mp3"));

		rv = RetVal::OK;
		try
		{
			invoker.Invoke("start_alarm");
		}
		catch (const RetVal& rv_)
		{
			rv = rv_;
		}
		EXPECT_EQ(rv, RetVal::NOTOK);

	}
	
	// StopAlarmCommand
	TEST(CommandInvokerTest, StopAlarmCommand)
	{
		CommandInvoker invoker;

		invoker.SetCommand("stop_alarm", new StopAlarmCommand("tcp://127.0.0.1:1112"));

		RetVal rv = RetVal::OK;
		try
		{
			invoker.Invoke("stop_alarm");
		}
		catch(const RetVal& rv_)
		{
			rv = rv_;
		}
		EXPECT_EQ(rv, RetVal::OK);
	}

	// ShutdownAlarmCommand
	TEST(CommandInvokerTest, ShutdownAlarmCommand)
	{
		CommandInvoker invoker;

		invoker.SetCommand("shutdown_alarm", new ShutdownAlarmCommand("tcp://127.0.0.1:1110"));

		RetVal rv = RetVal::OK;
		try
		{
			invoker.Invoke("shutdown_alarm");
		}
		catch(const RetVal& rv_)
		{
			rv = rv_;
		}
		EXPECT_EQ(rv, RetVal::OK);
	}

} // namespace

#endif // SOUND_CONTROLLER_TESTS_HPP
