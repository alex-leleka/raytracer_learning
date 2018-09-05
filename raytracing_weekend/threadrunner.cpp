#include "threadrunner.h"

#include "camera.h"
#include "hitable_list.h"

#include <thread>
#include <vector>
#include <memory>
//#include <chrono>
#include <algorithm>

ThreadRunner::ThreadRunner(Job job) 
	: processSceneToImage(job)
{
}


ThreadRunner::~ThreadRunner()
{
}

void ThreadRunner::ProcessSceneInThreads(const ArgsPackage& args)
{
	const auto& image = args.image;

    const bool singleThread = false;
    const int singleThreadMultiplier = singleThread ? 0u : 1u;
	const int coresNumber = std::max(std::thread::hardware_concurrency() * singleThreadMultiplier, 2u) - 1u; // left a one core for OS
	const int columnNumber = image.GetColumns();
	const int columsPerCore = columnNumber / coresNumber;
    const int columnsRemainder = columnNumber % coresNumber;
	auto threadsWorkers = std::make_unique<std::thread[]>(coresNumber);
    int startColumn = 0;
    int endColumn = startColumn + columsPerCore + columnsRemainder;
	for (int coreIndex = 0; coreIndex < coresNumber; ++coreIndex)
	{
		threadsWorkers[coreIndex] = std::thread (processSceneToImage, args, startColumn, endColumn);
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