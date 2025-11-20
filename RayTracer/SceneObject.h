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
	
	SceneObject(ObjectContainer objContainer, glm::mat4 transform);
};

#endif // SCENEOBJECT_H