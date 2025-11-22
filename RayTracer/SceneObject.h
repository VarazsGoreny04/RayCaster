#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <glm/glm.hpp>
#include "../includes/GLUtils.hpp"

struct ObjectContainer
{
	OGLObject oglObject;
	MeshObject<Vertex> meshObject;
};

class SceneObject
{
public:
	ObjectContainer objContainer;
	glm::mat4 transform;
	glm::vec3 color;
	
	SceneObject(ObjectContainer objContainer, glm::mat4 transform, glm::vec3 color);
};

#endif // SCENEOBJECT_H