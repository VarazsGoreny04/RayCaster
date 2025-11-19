#pragma once

#include <vector>
#include "Ray.h"

class LightSource
{
public:
	glm::vec3 origin;
	int rayCount;

	LightSource(glm::vec3 origin, int rayCount);
	std::vector<Ray> CastRays();
};