#include "pch.h"
#include "menu.h"
#include "config.h"
#include "hooks.h"
#include "aimbot.h"


inline void CleanMenu()
{
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();
	ImGui::EndTabBar();
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


void SetupFrame()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	static bool resized = false;
	if (!resized)
	{
		ImGui::SetNextWindowSize({ 500, 300 });
		resized = true;
	}

	ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	constexpr const char* title  = "dbg";
	static const float TextWidth = ImGui::CalcTextSize(title).x;
	const float WindowWidth		 = ImGui::GetWindowSize().x;

	ImGui::SetCursorPosX((WindowWidth - TextWidth) * 0.5f);
	ImGui::Text(title);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Border, { 0.6f, 0.13f, 0.60f, 1 });
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
				if (ImGui::Checkbox("Magic Bullet", &config.MagicBullet)) ToggleMagic();

				ImGui::Checkbox("Aimbot",			&config.aimbot);

				ImGui::Checkbox("Aim Closest",		&config.AimClose);

				ImGui::Checkbox("Aim at Team",		&config.TeamAim);

				ImGui::Checkbox("Target on shoot",  &config.AimOnClick);

				ImGui::Checkbox("Triggerbot",		&config.triggerbot);		

				ImGui::EndTabItem();
			}


			if (ImGui::BeginTabItem("Exploits"))
			{
				//Checkbox's

				if (ImGui::Checkbox("Godmode",		       &config.godmode))   ToggleGodmode();

				if (ImGui::Checkbox("Infinite Ammo",       &config.ammo))	   ToggleAmmo();

				if (ImGui::Checkbox("Infinite Reserves",   &config.reserves))  ToggleReserves();

				if (ImGui::Checkbox("Armor Piercing",      &config.NoArmor))   ToggleArmor();

				if (ImGui::Checkbox("Switch",			   &config.WpnSwitch)) ToggleSwitch();


				//Sliders

				if (ImGui::SliderFloat("Recoil",	     &config.recoil,   0, 100)) ToggleRecoil();

				if (ImGui::SliderFloat("Spread",		 &config.spread,   0, 100)) ToggleSpread();

				if (ImGui::SliderFloat("Pushback",		 &config.push,	   0, 100)) TogglePush();

				if (ImGui::SliderFloat("Firerate",	     &config.firerate, 1, 100)) ToggleFirerate();

				if (ImGui::SliderFloat("Reload Speed",   &config.reload,   1, 100)) ToggleReload();

				if (ImGui::SliderFloat("Crouch Speed",   &config.crouch,   1, 100)) ToggleCrouch();

				ImGui::EndTabItem();
			}


			if (ImGui::BeginTabItem("Misc"))
			{

				if (ImGui::Checkbox("Remove weapon models", &config.InvisGun)) ToggleModels();

				ImGui::SliderFloat("FOV", config.fov, 1, 170);

				ImGui::SliderFloat("Roll", &player->roll, 0, 360);

				ImGui::EndTabItem();
			}

		}
		
		CleanMenu();
	}

	if (*EntityListPtr && config.aimbot && (!config.AimOnClick || config.MouseDown)) aimbot();

	SDL_GL_SwapWindow(window);
}


//initializing ImGui and setting up the menus theme. the colors probably dont need to be so incredibly precise but im picky lol
void InitializeGui(const DWORD GameBase)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(*(SDL_Window**)(GameBase + 0x185870), *(SDL_GLContext*)(GameBase - 0x3A7A78));
	ImGui_ImplOpenGL2_Init();

	ImGuiStyle* const style = &ImGui::GetStyle();

	style->Colors[ImGuiCol_ResizeGrip]		     = { 0, 0, 0, 0 };
	style->Colors[ImGuiCol_ResizeGripActive]     = { 0, 0, 0, 0 };
	style->Colors[ImGuiCol_ResizeGripHovered]    = { 0, 0, 0, 0 };

	style->Colors[ImGuiCol_FrameBg]				 = { 0.19f, 0.19f, 0.19f, 1 };
	style->Colors[ImGuiStyleVar_FramePadding]	 = { 2, 2, 2, 2 };
	style->Colors[ImGuiStyleVar_FrameBorderSize] = { 1, 1, 1, 1 };
	style->Colors[ImGuiStyleVar_FrameRounding]	 = { 0, 0, 0, 0 };

	style->Colors[ImGuiCol_Border]				 = { 0.6f, 0.13f, 0.60f, 1 };
	style->Colors[ImGuiCol_WindowBg]			 = { 0.11764f, 0.05490f, 0.21568f, 1 };

	style->Colors[ImGuiCol_Tab]					 = { 0.33333f, 0.18039f, 0.58039f, 1 };
	style->Colors[ImGuiCol_TabActive]			 = { 0.48333f, 0.33039f, 0.73039f, 1 };
	style->Colors[ImGuiCol_TabHovered]			 = { 0.58333f, 0.43039f, 0.83039f, 1 };

	style->Colors[ImGuiCol_CheckMark]			 = { 0.08627f, 0.91372f, 0.30588f, 1 };

	style->Colors[ImGuiCol_SliderGrab]			 = { 0.39215f, 0.39215f, 0.39215f, 1 };
	style->Colors[ImGuiCol_SliderGrabActive]	 = { 0.51372f, 0.51372f, 0.51372f, 1 };

	style->Colors[ImGuiCol_FrameBgHovered]		 = { 0.23f, 0.23f, 0.23f, 1 };
	style->Colors[ImGuiCol_FrameBgActive]		 = { 0.23f, 0.23f, 0.23f, 1 };

	style->TabRounding = 0;
}