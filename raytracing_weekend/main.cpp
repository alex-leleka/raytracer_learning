#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "vector.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "mathutils.h"
#include "material.h"
#include "image2d.h"
#include "threadrunner.h"

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

Color RayToColor(const Ray& ray, const Hitable* world, int depth);
void ProcessImage(ImageData& image);

int main()
{
	ImageData image;

	ProcessImage(image);

	WriteImage("Test.ppm", image);
}

void ProcessSceneToImage(const ArgsPackage& args, int startColumn, int endColumn);


void ProcessImage(ImageData& image)
{
	/*
	// small scene
	constexpr int Size = 5;
	Hitable *list[Size];
	list[0] = new Sphere(Vector3F{ 0, 0, -1 }, 0.5f, new Lambertian{ Vector3F{0.8f, 0.3f, 0.3f} });
	list[1] = new Sphere(Vector3F{ 0, -100.5f, -1 }, 100, new Lambertian{ Vector3F{ 0.8f, 0.8f, 0.0f } });
	list[2] = new Sphere(Vector3F{ 1, 0, -1 }, 0.5f, new Metal{ Vector3F{ 0.8f, 0.6f, 0.2f }, 1.0f});
	list[3] = new Sphere(Vector3F{ -1, 0, -1 }, 0.5f, new Dielectric{ 1.5f});
	list[4] = new Sphere(Vector3F{ -1, 0, -1 }, -0.45f, new Dielectric{ 1.5f });
	HitableList * world = new HitableList{ list , Size };//*/
	HitableList * world = GetRandomScene();

	Vector3F lookFrom{ -8, 4, 1 };
	Vector3F lookAt{ -4, 3, 0 };
	//Vector3F lookAt{ 0, 1, 0 };
	float distanceToFocus = (lookFrom - lookAt).length();
	float aperture = 0.0f;
	Camera cam(lookFrom, lookAt, Vector3F{ 0.f, 1.f, 0.f }, 70.f, image.GetColumns()/ float(image.GetRows()), aperture, distanceToFocus);
	const int SamplesNum = 100;

	ArgsPackage args{ SamplesNum, image, cam, world };
	ThreadRunner runner(ProcessSceneToImage);
	runner.ProcessSceneInThreads(args);
}

void ProcessSceneToImage(const ArgsPackage& args, int startColumn, int endColumn)
{
	// unpack args
	const int & SamplesNum { args.SamplesNum };
	ImageData & image { args.image };
	const Camera &cam { args.cam };
	const HitableList * world { args.world };

	const float SampleWeight = 1.0f / SamplesNum;
	for (int i = startColumn; i < endColumn; ++i)
	{
		for (int j = 0; j < image.GetRows(); ++j)
		{
			Color color{ 0,0,0 };
			for (int s = 0; s < SamplesNum; ++s)
			{
				float u = (i + GetRandomFloat()) / float(image.GetColumns());
				float v = 1.0f - (j + GetRandomFloat()) / float(image.GetRows());
				auto r = cam.GetRay(u, v);
				color += RayToColor(r, world, 0);
			}
			color *= SampleWeight;
			image(j, i) = color;
		}
	}
}

Color RayToColor(const Ray& ray, const Hitable* world, int depth)
{
	HitRecord record;
	const float antishadowAcneBias = 0.001f;
	const int MaxDepth = 50;
	if (world->hit(ray, antishadowAcneBias, std::numeric_limits<float>::max(), record))
	{
		Ray scattered;
		Vector3F attenuation;
		if (depth < MaxDepth && record.mat->scatter(ray, record, attenuation, scattered))
		{
			return attenuation * RayToColor(scattered, world, depth + 1);
		}
		return Vector3F{ 0, 0, 0 };
	}
	auto unitDirection = ray.direction().getunitvector();
	float t = 0.5f * (unitDirection.y + 1.0f);
	const Color white{ 1.0f, 1.0f, 1.0f };
	const Color lightBlue{ 0.5f, 0.7f, 1.0f };
	return lerp(white, lightBlue, t);
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