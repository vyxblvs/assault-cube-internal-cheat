#pragma once
#include "pch.h"
#include "hooks.h"


struct _config
{
	//Is menu enabled
    bool menu = false;

	//aimbot
    bool aimbot      = false;
    bool MagicBullet = false;
    bool AimClose    = false;
    bool TeamAim     = false;
    bool AimOnClick  = false;

    //exploits
    bool ammo      = false;
    bool godmode   = false;
    bool NoArmor   = false;
    bool reserves  = false;
    bool WpnSwitch = false;
    float VisRecoil   = 100.0f;
    float spread   = 100.0f;
    float PhysRecoil     = 100.0f;
    float firerate = 1.0f;
    float reload   = 1.0f;
    float crouch   = 6.0f;

	//misc
    bool InvisGun = false;
    float* fov = nullptr;

    //internal configuration
    bool MouseDown = false;
    bool shooting  = false;

}; extern "C" _config config;


struct weapon_info
{
    char name[8];      //0x0000
    char pad_0008[76]; //0x0008
    WORD base_recoil;  //0x0054
    WORD max_ammo;     //0x0056
};


struct entity;
struct weapon
{
    BYTE** VTable;         //0x0000
    UINT WeaponID;         //0x0004
    entity* player;        //0x0008
    weapon_info* info;     //0x000C
    UINT* WeaponReserves;  //0x0010
    UINT* WeaponAmmo;      //0x0014
    UINT* WeaponDelay;     //0x0018
    UINT ConsecutiveShots; //0x001C
    UINT ReloadDelay;      //0x0020
};


struct entity
{
    char pad_0000[40];     //0x0000
    float x_axis;          //0x0028
    float y_axis;          //0x002C
    float z_axis;          //0x0030
    float yaw;             //0x0034
    float pitch;           //0x0038
    float roll;            //0x003C
    char pad_0040[16];     //0x0040
    float height;          //0x0050
    char pad_0054[152];    //0x0054
    UINT health;           //0x00EC
    UINT armor;            //0x00F0
    char pad_00F4[20];     //0x00F4
    UINT pistol_reserves;  //0x0108
    UINT carbine_reserves; //0x010C
    UINT shotgun_reserves; //0x0110
    UINT smg_reserves;     //0x0114
    UINT sniper_reserves;  //0x0118
    UINT ar_reserves;      //0x011C
    char pad_0120[4];      //0x0120
    UINT akimbo_reserves;  //0x0124
    char pad_0128[4];      //0x0128
    UINT pistol_ammo;      //0x012C
    UINT carbine_ammo;     //0x0130
    UINT shotgun_ammo;     //0x0134
    UINT smg_ammo;         //0x0138
    UINT sniper_ammo;      //0x013C
    UINT ar_ammo;          //0x0140
    UINT grenades;         //0x0144
    UINT akimbo_ammo;      //0x0148
    UINT knife_delay;      //0x014C
    UINT pistol_delay;     //0x0150
    UINT carbine_delay;    //0x0154
    UINT shotgun_delay;    //0x0158
    UINT smg_delay;        //0x015C
    UINT sniper_delay;     //0x0160
    UINT ar_delay;         //0x0164
    UINT grenade_delay;    //0x0168
    UINT akimbo_delay;     //0x016C
    char pad_0170[149];    //0x0170
    char name[15];         //0x0205
    char pad_0214[248];    //0x0214
    UINT team;             //0x030C
    UINT swap_delay;       //0x0310
    char pad_0310[4];      //0x0314
    UINT dead;             //0x0318
    char pad_031C[72];     //0x031C
    weapon* weapon_ptr;    //0x0364
}; extern "C" entity* player;