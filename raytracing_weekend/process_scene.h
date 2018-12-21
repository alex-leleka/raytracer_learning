#pragma once

#include "color_defines.h"
#include "image_output.h"

class Hitable;
struct Ray;
struct ArgsPackage;

Color RayToColor(const Ray& ray, const Hitable* world, int depth, int i = 0, int j = 0);
void ProcessImage(ImageData& image);
void ProcessSceneToImage(const ArgsPackage& args, int startColumn, int endColumn);