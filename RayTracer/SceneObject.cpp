#include "SceneObject.h"

SceneObject::SceneObject(ObjectContainer objContainer, glm::mat4 transform, glm::vec3 color)
{
	this->objContainer = objContainer;
	this->transform = transform;
	this->color = color;
}