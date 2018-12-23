#define MAIN_TEST

#include "config.h"
#include "config_constant.h"

#include "image2d.h"
#include "process_scene.h"

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

void RunTests();

#ifdef TEST_RUN
int main()
{
	RunTests();
}
#endif // TEST_RUN

namespace VisualTest
{
	void debugImageOutput(ImageData& image)
	{
		for (int i = 0; i < image.GetRows(); ++i)
		{
			for (int j = 0; j < image.GetColumns(); ++j)
			{
				auto& texel = image(i, j);
				texel.r = i / float(image.GetRows());
				texel.g = j / float(image.GetColumns());
				texel.b = 0.3f;
			}
		}
	}
}

bool CompareImagesIsEqual(const ImageData& imageA, const ImageData& imageB, float error)
{
	float errorX{ 0 };
	float maxVectorError = 3 * error;
	for (int i = 0; i < imageA.GetSize(); ++i)
	{
		float currentError = (imageA.GetByLinearIndex(i) - imageB.GetByLinearIndex(i)).dot(ImageData::TDataType(1, 1, 1));
		if (currentError > maxVectorError)
		{
			std::cout << "Index: " << i << " Error: " << currentError << std::endl;
			//return false;
			errorX = errorX > currentError ? errorX : currentError;
		}
	}
	std::cout << " Max error : " << errorX;
	return true;
}

#ifdef TEST_RUN
void RunTests()
{
	GlobalConfig.TimeProfilingEnabled = 0;
	GlobalConfig.PrimeRaysSamplesNum = 1;
	GlobalConfig.SingleThreadJobExecution = false;
	ImageData imageResultSingleThread;
	ProcessImage(imageResultSingleThread);
	GlobalConfig.SingleThreadJobExecution = true;
	ImageData imageResultMultiThread;
	ProcessImage(imageResultMultiThread);
	const float epsilon = 0.01f;
	assert(CompareImagesIsEqual(imageResultSingleThread, imageResultMultiThread, epsilon) && "Image Comparison Text Failed");

}
#endif // TEST_RUN