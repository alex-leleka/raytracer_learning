#pragma once

#include <functional>

#include "image2d.h"

class Camera;
class HitableList;
class Hitable;

struct ArgsPackage
{
	const int &SamplesNum;
	ImageData & image;
	const Camera &cam;
	const Hitable * world;
};

class ThreadRunner
{
public:
	using Job = std::function<void(const ArgsPackage& args, const int startColumn, const int endColumn)>;
	ThreadRunner(Job job);
	~ThreadRunner();

	void ProcessSceneInThreads(const ArgsPackage& args);
private:
	void ExecutePayload(const ArgsPackage& args) const;
	void RunSingleThread(const ArgsPackage& args) const;
	void RunMultiThread(const ArgsPackage& args) const;
	Job processSceneToImage;

	bool timeProfiling;
};

