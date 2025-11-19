#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Utils
#include "../includes/Camera.h"
#include "../includes/CameraManipulator.h"
#include "../includes/GLUtils.hpp"

struct SUpdateInfo
{
	float ElapsedTimeInSec = 0.0f; // Program indulása óta eltelt idõ
	float DeltaTimeInSec = 0.0f;   // Elõzõ Update óta eltelt idõ
};

struct Intersection
{
	glm::vec2 uv;
	float t;
};

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	bool Init();
	void Clean();

	void Update(const SUpdateInfo&);
	void Render();
	void RenderGUI();

	//void RenderTable();
	void RenderBoxes();

	void KeyboardDown(const SDL_KeyboardEvent&);
	void KeyboardUp(const SDL_KeyboardEvent&);
	void MouseMove(const SDL_MouseMotionEvent&);
	void MouseDown(const SDL_MouseButtonEvent&);
	void MouseUp(const SDL_MouseButtonEvent&);
	void MouseWheel(const SDL_MouseWheelEvent&);
	void Resize(int, int);

	void OtherEvent(const SDL_Event&);

protected:
	void SetupDebugCallback();

	// Adat változók

	float m_ElapsedTimeInSec = 0.0f;

	// Picking

	glm::ivec2 m_PickedPixel = glm::ivec2(0, 0);
	bool m_IsPicking = false;
	bool m_IsCtrlDown = false;

	glm::uvec2 m_windowSize = glm::uvec2(0, 0);

	// Kamera
	Camera m_camera;
	CameraManipulator m_cameraManipulator;

	//
	// OpenGL-es dolgok
	//

	// shaderekhez szükséges változók
	GLuint m_programID = 0; // shaderek programja

	bool lightSwitch = false;
	int state = 0;

	// Shaderek inicializálása, és törlése
	void InitShaders();
	void CleanShaders() const;

	// Geometriával kapcsolatos változók

	void SetCommonUniforms();
	void DrawObject(OGLObject& obj, const glm::mat4& world);

	OGLObject m_quadGPU = {};

	// Geometria inicializálása, és törlése
	void InitGeometry();
	void CleanGeometry();

	// Textúrázás, és változói
	GLuint m_SamplerID = 0;

	GLuint m_BoxTextureID = 0;

	void InitTextures();
	void CleanTextures() const;
};