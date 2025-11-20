#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include "../includes/GLUtils.hpp"
#include "Ray.h"

class LightSource
{
public:
	glm::vec2 origin;
	int rayCount;

	LightSource(glm::vec2 origin, int rayCount);
	std::vector<Ray> CastRays();
	std::vector<glm::vec2> Shine(std::vector<Vertex> points);
};

#endif // LIGHTSOURCE_H