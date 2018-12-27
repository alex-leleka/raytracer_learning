#pragma once

struct ConfigurationVariables
{
	bool TimeProfilingEnabled = true;
	int PrimeRaysSamplesNum = 256;
	bool SingleThreadJobExecution = false;
	bool ShowImageInWindow = true;
	bool UseBhvStructure = true;
};

#include "test_defines.h"

#ifndef MAIN_TEST
CONSTEXPR ConfigurationVariables GlobalConfig;
#endif

// TODO: test for SingleThreadJobExecution, UseBhvStructure should return the same image