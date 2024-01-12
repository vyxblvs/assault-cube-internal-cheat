#pragma once

//Forward declarations

int HandleEvent(SDL_Event* SdlEvent);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//Original WndProc definition

typedef LRESULT(CALLBACK* _WndProc)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern _WndProc OgWndProc;