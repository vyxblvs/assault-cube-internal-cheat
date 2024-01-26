#include "pch.h"
#include "menu.h"
#include "config.h"
#include "hooks.h"
#include "aimbot.h"


inline void CleanMenu()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


inline void SetupFrame()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();

	ImGui::NewFrame();
	ImGui::SetNextWindowSize({ 600, 450 }, ImGuiCond_FirstUseEver);

	constexpr ImVec4 dark_purple = { 0.2156862f, 0.0117647f, 0.3686274f, 0.85f };

	ImGui::PushStyleColor(ImGuiCol_Border, dark_purple);

	ImGui::Begin("Github @vyxblvs", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

	ImGui::PopStyleColor();
}


bool CheckboxEx(const char* const label, bool* const var)
{
	constexpr ImVec4 dark_purple  = { 0.2156862f, 0.0117647f, 0.3686274f, 0.75f };
	constexpr ImVec4 light_purple = { 0.3156862f, 0.0217647f, 0.4686274f, 0.75f };
	constexpr ImVec4 LightGrey    = { 0.1562745f, 0.1562745f, 0.1562745f, 1.0f };

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    { 1.3f, 1.3f });
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,   1.5f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

	const bool v_status = *var;

	if (v_status)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg,        dark_purple);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, light_purple);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  light_purple);
	}
	else ImGui::PushStyleColor(ImGuiCol_Border, LightGrey);

	const bool status = ImGui::Checkbox(label, var);

	ImGui::PopStyleColor(v_status ? 3 : 1);
	ImGui::PopStyleVar(3);

	return status;
}


void DrawMenu(SDL_Window* window)
{
	if (config.menu)
	{
		SetupFrame();

		if (ImGui::BeginTabBar("Tabs"))
		{

			if (ImGui::BeginTabItem("Aimbot"))
			{
				if (CheckboxEx("Magic Bullet", &config.MagicBullet)) ToggleMagic();

				CheckboxEx("Aimbot",           &config.aimbot);

				CheckboxEx("Aim Closest",      &config.AimClose);

				CheckboxEx("Aim at Team",      &config.TeamAim);

				CheckboxEx("Target on shoot",  &config.AimOnClick);

				ImGui::EndTabItem(); 
			}

			if (ImGui::BeginTabItem("Exploits"))
			{
				//Checkbox's

				if (CheckboxEx("Godmode",            &config.godmode))   ToggleGodmode();

				if (CheckboxEx("Infinite Ammo",      &config.ammo))	  ToggleAmmo();

				if (CheckboxEx("Infinite Reserves",  &config.reserves))  ToggleReserves();

				if (CheckboxEx("Armor Piercing",     &config.NoArmor))   ToggleArmor();

				if (CheckboxEx("Switch",             &config.WpnSwitch)) ToggleSwitch();


				//Sliders

				if (ImGui::SliderFloat("Recoil",       &config.recoil,   0, 100)) ToggleRecoil();

				if (ImGui::SliderFloat("Spread",       &config.spread,   0, 100)) ToggleSpread();

				if (ImGui::SliderFloat("Pushback",     &config.push,	 0, 100)) TogglePush();

				if (ImGui::SliderFloat("Firerate",     &config.firerate, 1, 100)) ToggleFirerate();

				if (ImGui::SliderFloat("Reload Speed", &config.reload,   1, 100)) ToggleReload();

				if (ImGui::SliderFloat("Crouch Speed", &config.crouch,   1, 100)) ToggleCrouch();

				ImGui::EndTabItem();
			}
			
			if (ImGui::BeginTabItem("Misc"))
			{

				if (CheckboxEx("Remove weapon models", &config.InvisGun)) ToggleModels();

				ImGui::SliderFloat("FOV", config.fov, 1, 170);

				ImGui::SliderFloat("Roll", &player->roll, 0, 360);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		
		CleanMenu();
	}

	if (*EntityListPtr && config.aimbot && (!config.AimOnClick || config.MouseDown)) aimbot();

	SDL_GL_SwapWindow(window);
}


void InitializeGui(const DWORD GameBase)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(*(SDL_Window**)(GameBase + 0x185870), *(SDL_GLContext*)(GameBase - 0x3A7A78));
	ImGui_ImplOpenGL2_Init();

	ImGuiStyle& style = ImGui::GetStyle();

	constexpr ImVec4 clear          = { 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr ImVec4 black          = { 0.0f, 0.0f, 0.0f, 1.0f };
	constexpr ImVec4 grey           = { 0.0901960f, 0.0901960f, 0.0901960f, 1.0f };
	constexpr ImVec4 DarkGrey       = { 0.0601960f, 0.0601960f, 0.0601960f, 1.0f };
	constexpr ImVec4 LightGrey      = { 0.1562745f, 0.1562745f, 0.1562745f, 1.0f };
	constexpr ImVec4 DarkGrey_Child = { 0.0501960f, 0.0501960f, 0.0501960f, 1.0f };
	constexpr ImVec4 DarkPurple     = { 0.2156862f, 0.0117647f, 0.3686274f, 0.75f };
	constexpr ImVec4 LightPurple    = { 0.3156862f, 0.0217647f, 0.4686274f, 0.75f };
	constexpr ImVec4 LightPurple_2  = { 0.4156862f, 0.0317647f, 0.5686274f, 0.75f };

	style.TabRounding     = 0;
	style.FrameBorderSize = 1;
	style.FramePadding    = { 7.0f, 7.0f };
	style.Colors[ImGuiCol_ResizeGrip]        = clear;
	style.Colors[ImGuiCol_ResizeGripActive]  = clear;
	style.Colors[ImGuiCol_ResizeGripHovered] = clear;
	style.Colors[ImGuiCol_TitleBgActive]     = black;
	style.Colors[ImGuiCol_TitleBg]           = black;
	style.Colors[ImGuiCol_WindowBg]          = grey;
	style.Colors[ImGuiCol_Button]            = DarkGrey;
	style.Colors[ImGuiCol_ButtonActive]      = LightGrey;
	style.Colors[ImGuiCol_ButtonHovered]     = LightGrey;
	style.Colors[ImGuiCol_PopupBg]           = DarkGrey;
	style.Colors[ImGuiCol_Header]            = DarkGrey;
	style.Colors[ImGuiCol_HeaderActive]      = LightGrey;
	style.Colors[ImGuiCol_HeaderHovered]     = LightGrey;
	style.Colors[ImGuiCol_FrameBg]           = DarkGrey;
	style.Colors[ImGuiCol_FrameBgHovered]    = LightGrey;
	style.Colors[ImGuiCol_FrameBgActive]     = LightGrey;
	style.Colors[ImGuiCol_ChildBg]           = DarkGrey_Child;
	style.Colors[ImGuiCol_CheckMark]         = black;
	style.Colors[ImGuiCol_Tab]               = DarkGrey;
	style.Colors[ImGuiCol_TabActive]         = LightPurple;
	style.Colors[ImGuiCol_TabHovered]        = LightPurple_2;
	style.Colors[ImGuiCol_SliderGrab]        = DarkPurple;
	style.Colors[ImGuiCol_SliderGrabActive]  = LightPurple;
	style.Colors[ImGuiCol_Separator]         = DarkGrey;

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigWindowsResizeFromEdges = false;
}