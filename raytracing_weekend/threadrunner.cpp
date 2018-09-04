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

	const int coresNumber = std::max(std::thread::hardware_concurrency(), 2u) - 1u; // left a one core for OS
	const int columnNumber = image.GetColumns();
	const int columsPerCore = columnNumber / coresNumber;
	auto threadsWorkers = std::make_unique<std::thread[]>(coresNumber);
	for (int coreIndex = 0, startColumn = 0; coreIndex < coresNumber; ++coreIndex, startColumn += columsPerCore)
	{
		int endColumn = std::min(startColumn + columsPerCore, image.GetColumns());
		threadsWorkers[coreIndex] = std::thread (processSceneToImage, args, startColumn, endColumn);
	}
	
	// for debug
	//using namespace std::chrono_literals;
	//std::this_thread::sleep_for(5s);

	for (int coreIndex = 0; coreIndex < coresNumber; ++coreIndex)
	{
		threadsWorkers[coreIndex].join();
	}
}