#include "pch.h"
#include "menu.h"
#include "hooks.h"

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(reserved);

    if (reason == DLL_PROCESS_ATTACH)
    {
        const DWORD GameBase = reinterpret_cast<DWORD>(GetModuleHandleA(nullptr));
        DisableThreadLibraryCalls(instance);
        InitializeGui(GameBase);
        InitializeData(GameBase);
    }

    return true;
}