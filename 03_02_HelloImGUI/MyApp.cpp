#include "MyApp.h"
#include "includes/SDL_GLDebugMessageCallback.h"

#include <imgui.h>

CMyApp::CMyApp()
{
}

CMyApp::~CMyApp()
{
}

void CMyApp::SetupDebugCallback()
{
	// if the program is running in the debug context, allow and setup the debug callback function
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(SDL_GLDebugMessageCallback, nullptr);
	}
}

bool CMyApp::Init()
{
	SetupDebugCallback();

	// set the screen clearing color to blue-ish
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	//
	// other initializations
	//

	glEnable(GL_CULL_FACE); // enable the culling of backwards facing polygons (from the point of view of the camera)
	glCullFace(GL_BACK);	// GL_BACK: backwards facing polygons, GL_FRONT: forwards facing polygons

	glEnable(GL_DEPTH_TEST); // enabling depth testing (obstruction)

	return true;
}

void CMyApp::Clean()
{
}

void CMyApp::Update(const SUpdateInfo &updateInfo)
{
	m_ElapsedTimeInSec = updateInfo.ElapsedTimeInSec;
}

void CMyApp::Render()
{
	// clear the framebuffer (GL_COLOR_BUFFER_BIT)
	// ... and the depth buffer (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CMyApp::RenderGUI()
{
	// ImGui::ShowDemoWindow();

	if (ImGui::Begin("My Window"))
	{
		if (ImGui::Button("My Button"))
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	ImGui::End();
}

// https://wiki.libsdl.org/SDL2/SDL_KeyboardEvent
// https://wiki.libsdl.org/SDL2/SDL_Keysym
// https://wiki.libsdl.org/SDL2/SDL_Keycode
// https://wiki.libsdl.org/SDL2/SDL_Keymod

void CMyApp::KeyboardDown(const SDL_KeyboardEvent &key)
{
}

void CMyApp::KeyboardUp(const SDL_KeyboardEvent &key)
{
}

// https://wiki.libsdl.org/SDL2/SDL_MouseMotionEvent

void CMyApp::MouseMove(const SDL_MouseMotionEvent &mouse)
{
}

// https://wiki.libsdl.org/SDL2/SDL_MouseButtonEvent

void CMyApp::MouseDown(const SDL_MouseButtonEvent &mouse)
{
}

void CMyApp::MouseUp(const SDL_MouseButtonEvent &mouse)
{
}

// https://wiki.libsdl.org/SDL2/SDL_MouseWheelEvent

void CMyApp::MouseWheel(const SDL_MouseWheelEvent &wheel)
{
}

// two new parameters for the resized window's width (_w) and height (_h)
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);
}

// For handling other, more exotic events that haven't been handled yet
// https://wiki.libsdl.org/SDL2/SDL_Event

void CMyApp::OtherEvent(const SDL_Event &ev)
{
}