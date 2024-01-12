#pragma once
#include "config.h"

#define _call  0xE8
#define _jmp   0xE9
#define nop    0x90


//Helpers

void SetHook(BYTE* location, BYTE* dst, BYTE type, int ExtraBytes);

void InitializeData(const DWORD GameBase);


//Hook management

void ToggleArmor();

void ToggleMagic();

void ToggleModels();

void ToggleFirerate();

void ToggleReload();

void ToggleAmmo();

void ToggleReserves();

void ToggleSwitch();

void ToggleRecoil();

void ToggleSpread();

void TogglePush();

void ToggleGodmode();

void ToggleCrouch();


//Macros

#define ptr(x) reinterpret_cast<void*>(x)

#define DisableProtections(dst, size, buffer) VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, buffer)

#define hook(location, dst, type, ExtraBytes) SetHook(location, reinterpret_cast<BYTE*>(dst), type, ExtraBytes)


//Hook Locations

struct _locations // Initial values are RVA's (no, i will not be pattern scanning for a game that receives one update per decade)
{
    
    BYTE* damage         = reinterpret_cast<BYTE*>(0x1C221);

    BYTE* armor          = reinterpret_cast<BYTE*>(0x1C21D);

    BYTE* MagicBulletPtr = reinterpret_cast<BYTE*>(0xC9A83);

    BYTE* HitReg         = reinterpret_cast<BYTE*>(0xCA250);

    BYTE* firerate       = reinterpret_cast<BYTE*>(0xC73EA);

    BYTE* WpnSwitch      = reinterpret_cast<BYTE*>(0xC7311);

    BYTE* ModelRemoval   = reinterpret_cast<BYTE*>(0xC8ADA);

    BYTE* InfAmmo        = reinterpret_cast<BYTE*>(0xC73EF);

    BYTE* InfReserves    = reinterpret_cast<BYTE*>(0xC8FE9);

    BYTE* reload         = reinterpret_cast<BYTE*>(0xC8FC7);

    BYTE* recoil         = reinterpret_cast<BYTE*>(0xC8E4E);

    BYTE* spread         = reinterpret_cast<BYTE*>(0xC8C32);

    BYTE* PushPtr        = reinterpret_cast<BYTE*>(0xC8C3F);

    BYTE* VisCheck       = reinterpret_cast<BYTE*>(0x5F576);

    float* CrouchSpeed[2] = { reinterpret_cast<float*>(0x15BBF8), reinterpret_cast<float*>(0x15BF70) };

}; extern _locations hooks;