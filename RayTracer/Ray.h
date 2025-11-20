#ifndef RAY_H
#define RAY_H

#include <vector>
#include <glm/glm.hpp>
#include "../includes/GLUtils.hpp"

class Ray
{
public:
	glm::vec2 origin;
	glm::vec2 direction;

	Ray();
	Ray(glm::vec2 origin, glm::vec2 direction);
	~Ray();
};

glm::vec2 Intersect(Ray& a, Ray& b);
glm::vec2 Intersect(Ray& ray, glm::vec2 a, glm::vec2 b);
glm::vec2 Intersect(Ray& ray, std::vector<Vertex> points);

#endif // RAY_H