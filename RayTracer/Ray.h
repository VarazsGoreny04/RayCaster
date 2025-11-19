#pragma once

#include "RayTracer.h"

class Ray
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction);
	~Ray();
};