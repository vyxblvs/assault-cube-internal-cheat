#include "pch.h"
#include "hooks.h"
#include "config.h"
#include "aimbot.h"
#include "asm functions.h"


/*
* everything here (besides ToggleCrouch) will hook/unhook depending on the status of the feature 
* this is done to prevent writing these checks in asm, and cuz if everything was always hooked, it'd hurt performance (not in any way that matters but might aswell prevent that)
* 
* some functions like ToggleFirerate will just patch the targeted code completely if their sliders are set to the maximum or minimum value
* this is done for the same reason, its just faster
*/


void ToggleFirerate()
{
	if (config.firerate == 1 || config.firerate == 100)
	{
		if (*hooks.firerate == _call)
		{
			constexpr BYTE buffer[] = { 0x8B, 0x46, 0x14 };
			memcpy(hooks.firerate + 2, buffer, sizeof(buffer)); 
		}

		if (config.firerate == 1)
		{
			constexpr BYTE buffer[] = { 0x89, 0x08 };
			memcpy(hooks.firerate, buffer, sizeof(buffer));
		}

		else memset(hooks.firerate, nop, 2);
	}
	else hook(hooks.firerate, firerate, _call, 0);
}


void ToggleReload()
{
	if (config.reload == 1 || config.reload == 100)
	{
		if (*hooks.reload == _call)
		{
			constexpr BYTE buffer[] = { 0x8B, 0x47, 0x10 };
			memcpy(hooks.reload + 2, buffer, sizeof(buffer));
		}

		if (config.reload == 1) memset(hooks.reload, 0x01, 2);

		else memset(hooks.reload, nop, 2);
	}
	else hook(hooks.reload, reload, _call, 0);
}


void ToggleAmmo()
{
	if (config.ammo) hook(hooks.InfAmmo, InfAmmo, _call, 1);
	else
	{
		constexpr BYTE buffer[] = { 0xFF, 0x08, 0x8D, 0x44, 0x24, 0x1C };
		memcpy(hooks.InfAmmo, buffer, sizeof(buffer));
	}
}


void ToggleReserves()
{
	if (config.reserves) hook(hooks.InfReserves, InfReserves, _call, 0);
	else
	{
		constexpr BYTE buffer[] = { 0x29, 0x30, 0x8B, 0x47, 0x0C };
		memcpy(hooks.InfReserves, buffer, sizeof(buffer));
	}
}


void ToggleSwitch()
{
	if (config.WpnSwitch) memset(hooks.WpnSwitch, nop, 4);
	else
	{
		constexpr BYTE buffer[] = { 0x80, 0x78, 0x66, 0x00 };
		memcpy(hooks.WpnSwitch, buffer, sizeof(buffer));
	}
}


void ToggleRecoil()
{
	if (config.recoil < 100) hook(hooks.recoil, RecoilScale, _jmp, 4);
	else
	{
		constexpr BYTE buffer[] = { 0xF3, 0x0F, 0x5D, 0xD0, 0xF3, 0x0F, 0x11, 0x50, 0x40 };
		memcpy(hooks.recoil, buffer, sizeof(buffer));
	}
}


void ToggleSpread()
{
	if (config.spread < 100) hook(hooks.spread, SpreadScale, _call, 0);
	else
	{
		constexpr BYTE buffer[] = { 0xFF, 0x50, 0x04, 0x8B, 0x17 };
		memcpy(hooks.spread, buffer, sizeof(buffer));
	}
}


void TogglePush()
{
	if (config.push < 100) hook(hooks.PushPtr, PushScale, _call, 0);
	else
	{
		constexpr BYTE buffer[] = { 0x8B, 0x52, 0x08, 0xFF, 0xD2 };
		memcpy(hooks.PushPtr, buffer, sizeof(buffer));
	}
}


void ToggleArmor()
{
	if (config.NoArmor) hook(hooks.armor, ArmorPiercing, _call, 1);
	else
	{
		constexpr BYTE buffer[] = { 0xF3, 0x0F, 0x2C, 0xC9, 0x2B, 0xF1 };
		memcpy(hooks.damage, buffer, sizeof(buffer));
	}
}


void ToggleMagic()
{
	if (config.MagicBullet) hook(hooks.MagicBulletPtr, MagicBullet, _call, 0);
	else
	{
		constexpr BYTE buffer[] = { 0xE8, 0xC8, 0x07, 0x00, 0x00 };
		memcpy(hooks.MagicBulletPtr, buffer, sizeof(buffer));
	}
}


void ToggleGodmode()
{
	if (config.godmode) hook(hooks.damage, godmode, _call, 0);
	else
	{
		constexpr BYTE buffer[] = { 0x29, 0x73, 0x04, 0x8B, 0xC6 };
		memcpy(hooks.damage, buffer, sizeof(buffer));
	}
}


void ToggleModels()
{
	if (config.InvisGun) memset(hooks.ModelRemoval, nop, 5);
	else
	{
		constexpr BYTE buffer[] = { 0xE8, 0x61, 0x94, 0xF4, 0xFF };
		memcpy(hooks.ModelRemoval, buffer, sizeof(buffer));
	}
}


void ToggleCrouch()
{
	*hooks.CrouchSpeed[0] = config.crouch / 10;
	*hooks.CrouchSpeed[1] = *hooks.CrouchSpeed[0] * -1;
}