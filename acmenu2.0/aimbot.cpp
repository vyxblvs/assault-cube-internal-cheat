#include "pch.h"
#include "aimbot.h"
#include "hooks.h"

UINT* PlayerCount;
entity*** EntityListPtr;


void aimbot()
{
	entity** EntityList = *EntityListPtr;

	float furthest   = MAX_FLOAT;
	float FinalYaw   = NULL;
	float FinalPitch = NULL;

	for (int x = 1; x < *PlayerCount; ++x)
	{
		if (EntityList[x]->dead || (EntityList[x]->team == player->team && !config.TeamAim)) continue;

		float absX = player->x_axis - EntityList[x]->x_axis;
		float absY = player->y_axis - EntityList[x]->y_axis;
		float absZ = EntityList[x]->z_axis - player->z_axis;
		float distance = sqrtf((absX * absX) + (absY * absY));

		if (distance < furthest)
		{
			FinalYaw   = static_cast<float>(atan2f(absY, absX) * (180 / M_PI) - 90);
			FinalPitch = static_cast<float>(atan2f(absZ, distance) * (180 / M_PI));

			if (!config.AimClose) break;

			furthest = distance;
		}
	}

	if (FinalYaw)
	{
		player->yaw   = FinalYaw;
		player->pitch = FinalPitch;
	}
}


//this replaces a function that would check if you shot a player and return an entity* if you did
entity* MagicBullet_main()
{
	if (!*EntityListPtr) return nullptr;

	entity** EntityList = *EntityListPtr;
	entity* target = nullptr;
	float furthest = MAX_FLOAT;

	for (int x = 1; x < *PlayerCount; ++x)
	{
		if (!EntityList[x]->dead && (!config.TeamAim || EntityList[x]->team != player->team))
		{
			if (!config.AimClose) return EntityList[x];

			const float distance = sqrtf(static_cast<float>(pow(player->x_axis - EntityList[x]->x_axis, 2) + pow(player->y_axis - EntityList[x]->y_axis, 2)));
			if (distance < furthest)
			{
				furthest = distance;
				target = EntityList[x];
			}
		}
	}

	return target;
}


//this is inlined cuz i didnt wanna import the hooks struct for nasm, takes more space than saves
__declspec(naked) entity* MagicBullet()
{
	__asm
	{
		mov eax, [player]
		cmp [esp+8], eax
		lea eax, MagicBullet_main
		jne _leave
		mov eax, hooks.HitReg
	_leave:
		jmp eax
	}
}