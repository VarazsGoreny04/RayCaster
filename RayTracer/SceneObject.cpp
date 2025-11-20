#include "SceneObject.h"

SceneObject::SceneObject(ObjectContainer objContainer, glm::mat4 transform)
{
	this->objContainer = objContainer;
	this->transform = transform;
}