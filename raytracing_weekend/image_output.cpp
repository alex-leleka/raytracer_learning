#include "image_output.h"

#include <fstream>
#include "image2d.h"

void WriteImage(const std::string& fileName, const ImageData& imageData)
{
	std::ofstream file{ fileName };

	file << "P3" << std::endl
		<< imageData.GetColumns() << " "
		<< imageData.GetRows() << std::endl
		<< "255" << std::endl;

	bool gammacorrection = true;
	for (int i = 0; i < imageData.GetRows(); ++i)
	{
		for (int j = 0; j < imageData.GetColumns(); ++j)
		{
			auto color = imageData(i, j);
			const int maxValue = 255;
			if (gammacorrection)
			{
				color.r = sqrt(color.r);
				color.g = sqrt(color.g);
				color.b = sqrt(color.b);
			}
			auto colorInt = ColorFloatToInt(color, maxValue);
			file << colorInt.r << " " << colorInt.g << " " << colorInt.b << std::endl;
		}
	}

	file.close();
}