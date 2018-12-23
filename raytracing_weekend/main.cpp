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
#include "test_defines.h"

#ifndef TEST_RUN
int main()
{
	ImageData image;

	ProcessImage(image);

	WriteImage("Test.ppm", image);
	DisplayImage(image);

	system("pause"); // wait for a key pressed
}
#endif // TEST_RUN