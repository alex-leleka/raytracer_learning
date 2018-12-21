#include "threadrunner.h"

#include "camera.h"
#include "hitable_list.h"
#include "time_profiler.h"

#include <thread>
#include <vector>
#include <memory>
//#include <chrono> // for debug
#include <algorithm>
#include <iostream>

ThreadRunner::ThreadRunner(Job job) 
	: processSceneToImage(job)
	, timeProfiling(TimeProfilingEnabled)
{
}


ThreadRunner::~ThreadRunner()
{
}

void ThreadRunner::ProcessSceneInThreads(const ArgsPackage& args)
{
	TimeProfiler timeProfiler;
	if (timeProfiling)
	{
		std::cout << "Start work | ";
		timeProfiler.StartTimecount();
	}

	ExecutePayload(args);

	if (timeProfiling)
	{
		double timeSeconds = timeProfiler.EndTimecount();
		std::cout << "Result: " << timeSeconds << " sec." << std::endl;
	}
}

void ThreadRunner::ExecutePayload(const ArgsPackage& args) const
{
	if (SingleThreadJobExecution)
	{
		RunSingleThread(args);
	}
	else
	{
		RunMultiThread(args);
	}
}

void ThreadRunner::RunSingleThread(const ArgsPackage& args) const
{
	const auto& image = args.image;
	processSceneToImage(args, 0, image.GetColumns());
}

void ThreadRunner::RunMultiThread(const ArgsPackage& args) const
{
	const int coresNumber = std::max(std::thread::hardware_concurrency(), 2u) - 1u; // left a one core for OS
	const auto& image = args.image;
	const int columnNumber = image.GetColumns();
	const int columsPerCore = columnNumber / coresNumber;
	const int columnsRemainder = columnNumber % coresNumber;
	auto threadsWorkers = std::make_unique<std::thread[]>(coresNumber);
	int startColumn = 0;
	int endColumn = startColumn + columsPerCore + columnsRemainder;

	for (int coreIndex = 0; coreIndex < coresNumber; ++coreIndex)
	{
		threadsWorkers[coreIndex] = std::thread(processSceneToImage, args, startColumn, endColumn);
		startColumn = endColumn;
		endColumn += columsPerCore;
	}

	// for debug
	//using namespace std::chrono_literals;
	//std::this_thread::sleep_for(5s);

	for (int coreIndex = 0; coreIndex < coresNumber; ++coreIndex)
	{
		threadsWorkers[coreIndex].join();
	}
}
