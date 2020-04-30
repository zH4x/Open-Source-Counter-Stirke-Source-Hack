#include "Menu.h"
#include "../tools/entity.h"
#include <array>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../SDK/ISurface.h"
#include "../hacks/visuals.h"
#include <vector>
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include "options.h"
#include "../hacks/misc.h"
#include "menuhelper.h"

using namespace std;
cmenu* menu = new cmenu();
CVars Cvars;
cOptions Options;
const char* keyNames[] =
{
	"",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};

bool color_picker(const char* label, ImColor& col, ImGuiColorEditFlags flags = 0)
{
	float color[3]{ col.Value.x, col.Value.y, col.Value.z };

	if (!ImGui::ColorPicker3(label, color, flags))
		return false;

	col.Value.x = color[0];
	col.Value.y = color[1];
	col.Value.z = color[2];

	return true;
}

bool color_picker(const char* label, Color& col, ImGuiColorEditFlags flags = 0)
{
	float color[3]{ col.r() / 255.f, col.b() / 255.f, col.b() / 255.f };

	if (!ImGui::ColorPicker3(label, color, flags))
		return false;

	col.SetR(color[0] * 255.f);
	col.SetG(color[1] * 255.f);
	col.SetB(color[2] * 255.f);

	return true;
}

size_t CurTabOpen = 0;
static bool shoulddraw;


void AddTab(size_t Index, const char* Text)
{
	static const size_t TabWidth = 104;
	static const size_t TabHeight = 25;

	ImGui::PushID(Index);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);

	if (Index == 1)
		ImGui::SameLine(Index * (TabWidth + 5));
	else if (Index > 1)
		ImGui::SameLine(Index * (TabWidth + 4 - Index));

	if (CurTabOpen == Index)
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(15, 15, 15));			// Color on tab open
	else
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(5, 5, 5));			// Color on tab closed

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(40, 40, 40));			// Color on mouse hover in tab
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(35, 35, 35));			// Color on click tab

	if (ImGui::Button(Text, ImVec2(TabWidth, TabHeight)))	// If tab clicked
		CurTabOpen = Index;

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
	ImGui::PopID();
}


void visualss()
{
	ImGui::Checkbox("Box Esp", &Options.Visuals.bBox);
	ImGui::Checkbox("Health Bar", &Options.Visuals.bHealthbar);
	ImGui::Checkbox("Snap Lines", &Options.Visuals.visuals_snapline);
	ImGui::Checkbox("No Flash", &Options.Visuals.bNoFlash);
	ImGui::Checkbox("Spread Circle", &Options.Visuals.visuals_spread_circle);
	ImGui::Checkbox("Draw Triggerbot Hit Point", &Options.Visuals.visuals_triggerbot_hit_point);
	ImGui::Checkbox("Draw Hitboxes On Triggerbot Hit", &Options.Visuals.visuals_triggerbot_hitbox);
	ImGui::Checkbox("No Visual Recoil", &Options.Visuals.NoVisualRecoil);
	ImGui::Checkbox("Show Bhop Window", &Options.Visuals.ShowKeys);
	ImGui::Checkbox("Show Velocity", &Options.Visuals.ShowVelocity);
	ImGui::Checkbox("Tracers", &Options.Visuals.bBulletTracer);
	ImGui::Checkbox("Players Tracers", &Options.Visuals.bBulletTracerEnemy);
	ImGui::Checkbox("Hitmarker", &Options.Visuals.bHitMarker);
	ImGui::Checkbox("Damage Indirector", &Options.Visuals.ShowDamage);
	ImGui::Checkbox("Crosshair", &Options.Misc.visual_crosshair);
	if (Options.Misc.visual_crosshair)
	{
		ImGui::SliderFloat("Crosshair Offset", &Options.Misc.visual_crosshair_offset, 0.f, 25.f, "Crosshair Offset: %.0f");
		ImGui::SliderFloat("Crosshair Spin Speed", &Options.Misc.visual_crosshair_spin, -10.f, 10.f, "Crosshair Spin: %.1f");
	}
	ImGui::Checkbox("FOV", &Options.Misc.bEnableFov);
	if (Options.Misc.bEnableFov)
	ImGui::SliderInt("%###int", &Options.Visuals.FovValue, 90, 150, "%.1f");
	ImGui::SliderInt("ViewModel FOV##int", &Options.Misc.flViewModelValue, 50, 150, "%.1f");
	ImGui::Checkbox("No Shadows", &Options.Visuals.NoShadows);
	ImGui::Checkbox("Backtrack Visuals", &Options.Visuals.BacktrackVis);
	if (Options.Visuals.BacktrackVis)
	{
		ImGui::BeginChild("\r", ImVec2(260, 120), true);
		{
			ImGui::Checkbox("Backtrack HitBoxes", &Options.Visuals.BacktrackChams);
			ImGui::Checkbox("Backtrack dots", &Options.Visuals.BacktrackDots);
			ImGui::Checkbox("Other", &Options.Visuals.BacktrackVisuals);
		}ImGui::EndChild();
	}
	
}

void Colors()
{
	
		ImGui::BeginChild("COL1", ImVec2(400, 150), true);
		{
			ImGui::Text("Visable t Esp");
			ImGui::Separator();

			ImGui::SliderInt("Red##int", &Options.Visuals.rEspVisable_t, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.gEspVisable_t, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.bEspVisable_t, 0, 255, "%.1f");
		}ImGui::EndChild();
	
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL2", ImVec2(400, 150), true);
		{
			ImGui::Text("InVisable t Esp");
			ImGui::Separator();
			ImGui::SliderInt("Red##int", &Options.Visuals.rEsp_t, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.gEsp_t, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.bEsp_t, 0, 255, "%.1f");
		}ImGui::EndChild();
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL3", ImVec2(400, 150), true);
		{
			ImGui::Text("Visable ct Esp");
			ImGui::Separator();
			ImGui::SliderInt("Red##int", &Options.Visuals.rEspVisable_ct, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.gEspVisable_ct, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.bEspVisable_ct, 0, 255, "%.1f");
		}ImGui::EndChild();
	}ImGui::NextColumn();
	{
		ImGui::BeginChild("COL4", ImVec2(400, 150), true);
		{
			ImGui::Text("InVisable ct Esp");
			ImGui::Separator();
			ImGui::SliderInt("Red##int", &Options.Visuals.rEsp, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.gEsp, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.bEsp, 0, 255, "%.1f");
		}ImGui::EndChild();
	}
	//ImGui::EndColumns();
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL5", ImVec2(400, 180), true);
		{
			ImGui::TextColored(ImVec4(15, 255, 255, 255), "Tracers Color");
			ImGui::Separator();

			ImGui::SliderInt("Red##int", &Options.Visuals.rTracer, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.gTracer, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.bTracer, 0, 255, "%.1f");
			ImGui::SliderInt("Brightness##int", &Options.Visuals.BrightTracer, 0, 255, "%.1f");
		}ImGui::EndChild();
	}ImGui::NextColumn();
	{
		ImGui::BeginChild("COL6", ImVec2(400, 180), true);
		{
			ImGui::TextColored(ImVec4(15, 255, 255, 255), "Crosshair Color");
			ImGui::Separator();

			ImGui::SliderInt("Red##int", &Options.Visuals.CrosshairRed, 0, 255, "%.1f");
			ImGui::SliderInt("Green##int", &Options.Visuals.CrosshairGreen, 0, 255, "%.1f");
			ImGui::SliderInt("Blue##int", &Options.Visuals.CrosshairBlue, 0, 255, "%.1f");
			ImGui::SliderInt("Brightness##int", &Options.Misc.visual_alpha, 0, 255, "%.1f");
		}ImGui::EndChild();
	}


}
int my_image_width = 20;
int my_image_height = 20;
PDIRECT3DTEXTURE9 my_texture = NULL;
void cmenu::aimbot_tab()
{
	ImGui::Checkbox("Enabled", &Options.Ragebot.Aimbot.bAimbotEnable);
	ImGui::Combo("Target Selection", &Options.Ragebot.Aimbot.iSelection, iSelection, ARRAYSIZE(iSelection));
	if (Options.Ragebot.Aimbot.iSelection == 1)
		ImGui::SliderFloat("FOV", &Options.Ragebot.Aimbot.Fov, 0.f, 360.f);
	ImGui::SliderFloat("Smooth", &Options.Ragebot.Aimbot.aimbot_smooth, 0.f, 50.f);
	ImGui::Combo("Hitbox", &Options.Ragebot.Aimbot.iHitbox, iHitbox, ARRAYSIZE(iHitbox));
	ImGui::Checkbox("Silent", &Options.Ragebot.Aimbot.bSilentAim);
	ImGui::Checkbox("Perfect Silent", &Options.Ragebot.Aimbot.pSilentAim);
	ImGui::Checkbox("Auto Fire", &Options.Ragebot.Aimbot.bAutoShoot);
	ImGui::SliderFloat("Minimum Damage", &Options.Ragebot.Aimbot.aimbot_mindmg, 0.f, 120.f);
	ImGui::Checkbox("On Key", &Options.Ragebot.Aimbot.aimbot_on_key);
	ImGui::Combo("Key", &Options.Ragebot.Aimbot.key, keyNames, ARRAYSIZE(keyNames));
	if (shoulddraw)
	{
		ImGui::Separator();
		ImGui::Image((void*)my_texture, ImVec2(530, 300));
	}
}

void TriggerBot()
{
	const char* triggerbot[]{ "Off", "Seed", "Bruteforce Seed" };

	ImGui::Combo("Triggerbot", &Options.Misc.trigger, triggerbot, ARRAYSIZE(triggerbot));
	ImGui::Checkbox("Triggerbot On Key", &Options.Misc.on_key);
	ImGui::Combo("Triggerbot Key", &Options.Misc.triggerbot_key, keyNames, ARRAYSIZE(keyNames));
	ImGui::Text("Filter");
	ImGui::Separator();
	ImGui::BeginChild("Filter", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 6.5));
	{
		ImGui::Selectable(" Head", &Options.Misc.misc_triggerbot_filter[0]);
		ImGui::Selectable(" Chest", &Options.Misc.misc_triggerbot_filter[1]);
		ImGui::Selectable(" Stomach", &Options.Misc.misc_triggerbot_filter[2]);
		ImGui::Selectable(" Arms", &Options.Misc.misc_triggerbot_filter[3]);
		ImGui::Selectable(" Legs", &Options.Misc.misc_triggerbot_filter[4]);
		ImGui::Selectable(" Friendlies", &Options.Misc.misc_triggerbot_filter[5]);
	}
	ImGui::EndChild();
}



bool LoadTextureFromFile(IDirect3DDevice9* vDevice, const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(vDevice, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}

//"                                  "


void cmenu::render(IDirect3DDevice9* vDevice)
{
	static bool inti;
	if (!inti)
	{
		bool ret = LoadTextureFromFile(vDevice, "C:\\Cheat\\Image.jpg", &my_texture, &my_image_width, &my_image_height);
		inti = true;
		if (ret)
			shoulddraw = true;
	}
		
	
	if (!Cvars.MenuOpened)
	{
		if (Options.Visuals.ShowKeys || Options.Misc.visual_crosshair)
		{
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			if (Options.Visuals.ShowKeys)
				DrawKzKeys();
			if (Options.Misc.visual_crosshair)
				DrawCrossHair();
			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}
	}
	else
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		auto& style = ImGui::GetStyle();
		ImGui::SetNextWindowSize(ImVec2(829, 800), ImGuiSetCond_FirstUseEver);
		//ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, 0), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		
		style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 255.00f);
		ImGui::Begin("\t\t\t\t\t\t\t\t  Cheat", NULL, ImVec2(540, 700), 0.98f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing);
		{
			style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
			AddTab(0, "Aimbot");
			AddTab(1, "Triggerbot");
			AddTab(2, "Visual");
			AddTab(3, "Misc");
			AddTab(4, "Colors");

			switch (CurTabOpen)
			{
			case 0:
				aimbot_tab();
				break;
			case 1:
				TriggerBot();
				break;
			case 2:
				visualss();
				break;
			case 3:
				misc_tab();
				break;
			case 4:
				Colors();
				break;
			}


		}



		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
}


void GetClanAddress(char* enable, int i)
{
	*(char*)((uintptr_t)GetModuleHandle("steamclient.dll") + 0x6AA0F8 + i) = enable[i];
}

void GetSendPacketAddress(char enable,int i)
{
	 *(char*)((uintptr_t)GetModuleHandle("engine.dll") + 0x2F6780+ i) = enable;
}



void DisconnectReasonValue(char* enable,int i)
{
	DWORD oldp;
	BYTE* sendPacketAddr = reinterpret_cast<BYTE*>((uintptr_t)GetModuleHandle("engine.dll") + 0x2F6780+i);
	VirtualProtect(sendPacketAddr, 1, PAGE_EXECUTE_READWRITE, &oldp);
	GetSendPacketAddress(Options.Misc.Disconnectreason[i], i);
	VirtualProtect(sendPacketAddr, 1, oldp, &oldp);
}



string dis;










void cmenu::misc_tab()
{
	ImGui::Text("Movement");
	ImGui::Separator();
		ImGui::Checkbox("Bunnyhop", &Options.Misc.bBunnyhop);
		ImGui::Checkbox("AutoStrafe", &Options.Misc.bAutoStrafe);
		if (Options.Misc.bAutoStrafe)
		{
			ImGui::SameLine(); ImGui::Combo("##", &Options.Misc.iAutoStrafeMode, iAutostrafer, IM_ARRAYSIZE(iAutostrafer));
		}
		ImGui::Checkbox("JumpBug", &Options.Misc.AutoJumpBug);
		ImGui::Checkbox("Knifebot", &Options.Misc.KnifeBot);
		ImGui::Checkbox("FastStop", &Options.Misc.FastStop);
		ImGui::BeginChild("Filter", ImVec2(110, 60));
			{
		ImGui::Selectable(" Ground Only", &Options.Misc.FastStop_filter[0]);
		ImGui::Selectable(" Air Only ", &Options.Misc.FastStop_filter[1]);
		ImGui::Selectable(" Both", &Options.Misc.FastStop_filter[2]);
		}ImGui::EndChild();
		ImGui::Checkbox("FastRun", &Options.Misc.Fastrun);
		ImGui::Checkbox("Edgejump", &Options.Misc.Edgejumnp); if (Options.Misc.Edgejumnp) 
		{
		ImGui::Checkbox("Auto EdgeJump",&Options.Misc.AutoEdgeJump);
		if(!Options.Misc.AutoEdgeJump)
		ImGui::Combo("", &Options.Misc.EdgejumnpKey, keyNames, IM_ARRAYSIZE(keyNames)); 
		}
		ImGui::Checkbox("Walkbot", &Options.Misc.bWalkBot);
		if (Options.Misc.bWalkBot) {
			ImGui::Text("Distance to Wall");
			ImGui::PushItemWidth(125.5);
			ImGui::SliderFloat("%##float", &Options.Misc.flDistance, 0, 500, "%.1f", (1.0f));
			ImGui::Text("Degrees Turn");
			ImGui::PushItemWidth(125.5);
			ImGui::SliderInt("###int", &Options.Misc.iTurn, -180, 180, "%.1f");
		}
		ImGui::Checkbox("Low FPS", &Options.Misc.LowFps); if (ImGui::IsItemHovered()) { ImGui::SameLine(); ImGui::Text("[Better rate for Bhopping without Autobhop]"); };
	

	ImGui::Text("Misc II");
	ImGui::Separator();
	ImGui::Checkbox("FreeCam", &Options.Visuals.bFreeCam);
	if (Options.Visuals.bFreeCam)
	{
		ImGui::Combo("", &Options.Visuals.bFreeCamKey, keyNames, IM_ARRAYSIZE(keyNames));
		ImGui::SliderInt("%##int", &Options.Visuals.flFreeCamSpeed, 1, 10, "%.1f");
	}
		ImGui::Checkbox("NoSpread", &Options.Misc.NoSpread);
		ImGui::Checkbox("NoRecoil", &Options.Misc.NoRecoil);
		ImGui::Checkbox("AutoPistol", &Options.Misc.AutoPistol);
		ImGui::Checkbox("Backtrack", &Options.Misc.BackTrack);
		ImGui::Checkbox("Fake Ping", &Options.Misc.FakeLatency);
		if (Options.Misc.FakeLatency)
		{
			ImGui::SliderFloat("%", &Options.Misc.FakeLatencyValue, 0, 800, "%.1f", (1.0f));
		}
		ImGui::Checkbox("Fake Low Latency", &Options.Misc.FakeLowLatency);
		ImGui::Text("Other");
		ImGui::Separator();
		ImGui::InputText("Disconnect Reason", Options.Misc.Disconnectreason, IM_ARRAYSIZE(Options.Misc.Disconnectreason));

		if (ImGui::Button("Submit", ImVec2(60, 30)))
		{
			int length = sizeof(Options.Misc.Disconnectreason);
			for (int i = 0; i < length; i++)
			{
				DisconnectReasonValue(Options.Misc.Disconnectreason,i);
			}
		}
		ImGui::InputText("Clan Tag", Options.Misc.ClanTag, IM_ARRAYSIZE(Options.Misc.ClanTag));

		if (ImGui::Button("Submit##", ImVec2(60, 30)))
		{
			int length = sizeof(Options.Misc.ClanTag);
			for (int j = 0; j < length; j++)
			{
				if (j = length - 1)
				{
					g_engine->ClientCmd_Unrestricted("cl_clanid 0");
					GetClanAddress(Options.Misc.ClanTag, j);
					g_engine->ClientCmd_Unrestricted("cl_clanid 1");
				}
				else GetClanAddress(Options.Misc.ClanTag, j);
			}
		}

			
}

