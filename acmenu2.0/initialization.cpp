#include "pch.h"
#include "hooks.h"
#include "menu.h"
#include "input.h"
#include "config.h"
#include "aimbot.h"

_locations hooks;
_WndProc OgWndProc;
_config config;
entity* player;


void SetHook(BYTE* location, BYTE* dst, BYTE type, int ExtraBytes)
{
	*location = type;
	*reinterpret_cast<DWORD*>(location + 1) = dst - (location + 5);
	if (ExtraBytes) memset(location + 5, nop, ExtraBytes);
}


inline void SetHookEx(void* location, void* dst, BYTE type, int ExtraBytes)
{
	DWORD protection;
	VirtualProtect(location, ExtraBytes + 5, PAGE_EXECUTE_READWRITE, &protection);
	SetHook(reinterpret_cast<BYTE*>(location), reinterpret_cast<BYTE*>(dst), type, ExtraBytes);
}


void HookWndProc()
{
	const auto window = *reinterpret_cast<SDL_Window**>(0x585870);
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	OgWndProc = reinterpret_cast<_WndProc>(SetWindowLongW(wmInfo.info.win.window, GWLP_WNDPROC, reinterpret_cast<long>(&WndProc)));
}


void InitializeGameData(const DWORD GameBase)
{
	for (int x = 0; x < sizeof(hooks) / sizeof(DWORD); ++x)
	{
		reinterpret_cast<DWORD*>(&hooks)[x] += GameBase;
	}

	PlayerCount	   = reinterpret_cast<UINT*>    (GameBase + 0x18AC0C);
	EntityListPtr  = reinterpret_cast<entity***>(GameBase + 0x18AC04);
	config.fov     = reinterpret_cast<float*>   (GameBase + 0x18A7CC);
	player		   = *reinterpret_cast<entity**>(GameBase + 0x18AC00);

	DWORD old;
	constexpr int sizes[] = { 2, 6, 5, 5, 5, 6, 5, 5, 9, 5, 5, 6, 4, 4 };
	for (int x = 0; x < sizeof(sizes) / sizeof(int); ++x)
	{
		DisableProtections(reinterpret_cast<BYTE**>(&hooks)[x], sizes[x], &old);
	}

	void* const roll = ptr(GameBase + 0xC2E37);
	DisableProtections(roll, 5, &old);
	memset(roll, nop, 5);
}


void InitializeData(const DWORD GameBase)
{
	//Setting initial hooks
	SetHookEx(ptr(0x4EBE61), &DrawMenu,    _call, 1); //SDL_GL_SwapWindow() call
	SetHookEx(ptr(0x4EC9B1), &HandleEvent, _call, 1); //SDL_PollEvent() call

	//finishing initialization tasks
	HookWndProc();
	InitializeGameData(GameBase);
}