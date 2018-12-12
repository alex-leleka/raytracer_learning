#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "vector.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "mathutils.h"
#include "material.h"
#include "threadrunner.h"
#include "image_output.h"
#include "image2d.h"
#include "process_scene.h"

int main()
{
	ImageData image;

	ProcessImage(image);

	WriteImage("Test.ppm", image);

	system("pause"); // wait for a key pressed
}

//------------------------------
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