#include "pch.h"
#include "input.h"
#include "config.h"
#include "aimbot.h"


//this will hook the games SDL_PollEvent call and give ImGui the chance to process input if the menu is toggled
int HandleEvent(SDL_Event* SdlEvent)
{
	const int status = SDL_PollEvent(SdlEvent); 

	if (config.menu)
	{
		ImGui_ImplSDL2_ProcessEvent(SdlEvent);
		return false;
	}

	return status;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		SDL_SetRelativeMouseMode(static_cast<SDL_bool>(config.menu));

		config.menu = !config.menu;
		ImGui::GetIO().WantCaptureKeyboard = config.menu;
		ImGui::GetIO().WantCaptureMouse	   = config.menu;

		return true;
	}

	if (msg == WM_LBUTTONDOWN) config.MouseDown = true;

	else if (msg == WM_LBUTTONUP) config.MouseDown = false;
	
	return OgWndProc(hWnd, msg, wParam, lParam);
}