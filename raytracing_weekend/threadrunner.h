#pragma once

#include <functional>

#include "image2d.h"

class Camera;
class HitableList;

struct ArgsPackage
{
	const int &SamplesNum;
	ImageData & image;
	const Camera &cam;
	const HitableList * world;
};

class ThreadRunner
{
public:
	using Job = std::function<void(const ArgsPackage& args, int startColumn, int endColumn)>;
	ThreadRunner(Job job);
	~ThreadRunner();

	void ProcessSceneInThreads(const ArgsPackage& args);
private:
	Job processSceneToImage;
};

