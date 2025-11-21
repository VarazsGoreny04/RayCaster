// GLEW
#include <GL/glew.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

// standard
#include <iostream>
#include <sstream>

#include "RayTracer.h"

static int InitSDL()
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[SDL initialization] Error during the SDL initialization: %s", SDL_GetError());

		return 1;
	}

	std::atexit(SDL_Quit);

	return 0;
}

static void OpenGLConfig()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef _DEBUG 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif 

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// antialiasing - ha kell
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
}

static int InitGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[GLEW] Error during the initialization of glew.");

		return 1;
	}

	return 0;
}

static int OpenGLVersion(SDL_Window* win, SDL_GLContext* context)
{
	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Running OpenGL %d.%d", glVersion[0], glVersion[1]);

	if (glVersion[0] == -1 && glVersion[1] == -1)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);

		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[OGL context creation] Error during the inialization of the OGL context! Maybe one of the SDL_GL_SetAttribute(...) calls is erroneous.");

		return 1;
	}

	std::stringstream window_title;
	window_title << "OpenGL " << glVersion[0] << "." << glVersion[1];
	SDL_SetWindowTitle(win, window_title.str().c_str());

	return 0;
}

static void InitImGui(SDL_Window* win, SDL_GLContext* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(win, context);
	ImGui_ImplOpenGL3_Init();
}

static void DestructImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

int main(int argc, char* args[])
{
	if (InitSDL())
		return 1;

	OpenGLConfig();

	// hozzuk létre az ablakunkat
	SDL_Window* win = nullptr;
	win = SDL_CreateWindow("Hello SDL&OpenGL!",							// az ablak fejléce
		100,															// az ablak bal-felsõ sarkának kezdeti X koordinátája
		100,															// az ablak bal-felsõ sarkának kezdeti Y koordinátája
		800,															// ablak szélessége
		600,															// és magassága
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);	// megjelenítési tulajdonságok

	if (win == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[Window creation] Error during the SDL initialization: %s", SDL_GetError());
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(win);
	if (context == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[OGL context creation] Error during the creation of the OGL context: %s", SDL_GetError());
		return 1;
	}

	// vsync-et
	SDL_GL_SetSwapInterval(1);

	if (InitGLEW())
		return 1;

	if (OpenGLVersion(win, &context))
		return 1;

	InitImGui(win, &context);

	{
		RayTracer app;
		if (!app.Init())
		{
			SDL_GL_DeleteContext(context);
			SDL_DestroyWindow(win);
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[app.Init] Error during the initialization of the application!");
			return 1;
		}

		SDL_Event event;
		bool ShowImGui = true;
		bool quit = false;

		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
				bool is_mouse_captured = ImGui::GetIO().WantCaptureMouse;		//kell-e az imgui-nak az egér
				bool is_keyboard_captured = ImGui::GetIO().WantCaptureKeyboard;	//kell-e az imgui-nak a billentyûzet

				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;

					// ALT + ENTER vált teljes képernyõre, és vissza.
					if ((event.key.keysym.sym == SDLK_RETURN)								// Enter le lett nyomva, ...
						&& (event.key.keysym.mod & KMOD_ALT)								// az ALTal együtt, ...
						&& !(event.key.keysym.mod & (KMOD_SHIFT | KMOD_CTRL | KMOD_GUI)))	// de más modifier gomb nem lett lenyomva.
					{
						Uint32 FullScreenSwitchFlag = (SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP;
						SDL_SetWindowFullscreen(win, FullScreenSwitchFlag);
						is_keyboard_captured = true; // Az ALT+ENTER-t ne kapja meg az alkalmazás.
					}
					// CTRL + F1 ImGui megjelenítése vagy elrejtése
					if ((event.key.keysym.sym == SDLK_F1)									// F1 le lett nyomva, ...
						&& (event.key.keysym.mod & KMOD_CTRL)								// az CTRLal együtt, ...
						&& !(event.key.keysym.mod & (KMOD_SHIFT | KMOD_ALT | KMOD_GUI)))	// de más modifier gomb nem lett lenyomva.
					{
						ShowImGui = !ShowImGui;
						is_keyboard_captured = true; // A CTRL+F1-t ne kapja meg az alkalmazás.
					}
					if (!is_keyboard_captured)
						app.KeyboardDown(event.key);
					break;
				case SDL_KEYUP:
					if (!is_keyboard_captured)
						app.KeyboardUp(event.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (!is_mouse_captured)
						app.MouseDown(event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					if (!is_mouse_captured)
						app.MouseUp(event.button);
					break;
				case SDL_MOUSEWHEEL:
					if (!is_mouse_captured)
						app.MouseWheel(event.wheel);
					break;
				case SDL_MOUSEMOTION:
					if (!is_mouse_captured)
						app.MouseMove(event.motion);
					break;
				case SDL_WINDOWEVENT:
					// Néhány platformon (pl. Windows) a SIZE_CHANGED nem hívódik meg az elsõ megjelenéskor.
					// Szerintünk ez bug az SDL könytárban.
					// Ezért ezt az esetet külön lekezeljük, 
					// mivel a MyApp esetlegesen tartalmazhat ablak méret függõ beállításokat, pl. a kamera aspect ratioját a perspective() hívásnál.
					if ((event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) || (event.window.event == SDL_WINDOWEVENT_SHOWN))
					{
						int w, h;
						SDL_GetWindowSize(win, &w, &h);
						app.Resize(w, h);
					}
					break;
				default:
					app.OtherEvent(event);
				}
			}

			static Uint32 LastTick = SDL_GetTicks();
			Uint32 CurrentTick = SDL_GetTicks();
			SUpdateInfo updateInfo
			{
				static_cast<float>(CurrentTick) / 1000.0f,
				static_cast<float>(CurrentTick - LastTick) / 1000.0f
			};
			LastTick = CurrentTick;

			app.Update(updateInfo);
			app.Render();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();

			ImGui::NewFrame();
			if (ShowImGui) app.RenderGUI();
			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			SDL_GL_SwapWindow(win);
		}

		app.Clean();
	}

	DestructImGui();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);

	return 0;
}
