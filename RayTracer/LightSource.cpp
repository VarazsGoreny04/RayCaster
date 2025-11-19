#include "LightSource.h"

LightSource::LightSource(glm::vec3 origin, int rayCount)
{
	this->origin = origin;
	this->rayCount = rayCount;
}

static Ray CastRay(glm::vec3 origin, float angle)
{
	Ray ray{
		ray.origin = origin,
		ray.direction = glm::vec3(glm::cos(angle), 0, sin(angle))
	};

	return ray;
}

std::vector<Ray> LightSource::CastRays()
{
	std::vector<Ray> rays(rayCount);

	for (int i = 0; i < rayCount; ++i)
		rays.push_back(CastRay(origin, 360.0f / i));

	return rays;
}