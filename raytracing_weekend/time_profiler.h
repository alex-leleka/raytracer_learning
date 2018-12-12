#pragma once

#include <chrono>

class TimeProfiler
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;

public:
	void StartTimecount()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	// Returns end time in seconds
	double EndTimecount()
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		double elapsed_seconds = elapsed.count();
		return elapsed_seconds;
	}
};