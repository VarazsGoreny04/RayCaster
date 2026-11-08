#pragma once

#include <vector>
#include "../includes/GLUtils.hpp"
#include "Ray.hpp"
#include "SceneObject.hpp"

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