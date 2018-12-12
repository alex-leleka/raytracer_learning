#pragma once

#include "color_defines.h"
#include "image_output.h"

class Hitable;
struct Ray;
struct ArgsPackage;


Color RayToColor(const Ray& ray, const Hitable* world, int depth);
void ProcessImage(ImageData& image);
void ProcessSceneToImage(const ArgsPackage& args, int startColumn, int endColumn);