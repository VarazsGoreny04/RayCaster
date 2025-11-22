#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include "../includes/GLUtils.hpp"
#include "Ray.h"
#include "SceneObject.h"

class LightSource
{
public:
	glm::vec2 origin;
	float direction;
	int fov;
	int rayCount;

	LightSource(glm::vec2 origin, float direction, int fov, int rayCount);
	std::vector<glm::vec2> Shine(std::vector<SceneObject> sceneObjects) const;
};

#endif // LIGHTSOURCE_H