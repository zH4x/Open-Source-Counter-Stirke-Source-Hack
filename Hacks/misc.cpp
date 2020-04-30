#include "misc.h"
#include "../tools/game.h"
#include "../tools/math.h"
#include "visuals.h"
#include "../Menu.h"
#include "edgejump.h"
#include "aimbot.h"
#include "../options.h"
#include "backtrack.h"
#include "../ImGui/imgui_internal.h"
cmisc* misc = new cmisc();
NoFall gFall;
AutoStrafe gStrafe;

float FrameCount;
float FpsCount;
float InterpFps;
float PreStrafe;
float JumpOff;

float Keyforwardm = false;
float Keymoveleft = false;
float Keymoveright = false;
float Keyback = false;
float Keyduck = false;
float Keyjump = false;

bool Strafe = false;
bool Fastrun = false;
bool Gstrafe = false;
bool Bhop = false;
bool Jumpbug = false;

bool Checked = false;
bool Checked1 = false;


void triggerbot(CUserCmd* cmd, C_BasePlayer* local_player, int custom_seed = -1)
{
	if (Options.Misc.on_key && !GetAsyncKeyState(Options.Misc.triggerbot_key))
		return;

	auto weapon = local_player->GetActiveWeapon();
	if (!weapon)
		return;

	const auto server_time = local_player->get_tick_base() * g_globals->interval_per_tick;
	if (server_time <= weapon->get_next_primary_attack() || server_time <= local_player->get_next_attack())
		return;

	auto weapon_data = weapon->GetWpnData();
	if (!weapon_data)
		return;

	weapon->UpdateAccuracyPenalty();

	auto seed = cmd->random_seed & 0xFF;
	if (custom_seed != -1)
		seed = custom_seed;

	game::RandomSeed(seed + 1);

	const auto rand1 = game::RandomFloat(0.f, M_PI_F * 2.f);
	const auto rand2 = game::RandomFloat(0.f, weapon->GetInaccuracy());

	const auto v37 = cosf(rand1) * rand2;
	const auto v38 = sinf(rand1) * rand2;

	Vector2D  spreads[16];

	auto vec_start = local_player->get_eye_position();
	auto viewangles = cmd->viewangles;
	viewangles -= local_player->get_aim_punch() * 2.f;

	for (auto i = 0; i < weapon_data->m_iBullets; i++)
	{
		const auto rand3 = game::RandomFloat(0.0, M_PI_F * 2.f);
		const auto rand4 = game::RandomFloat(0.0, weapon->GetSpread());

		spreads[i].x = cosf(rand3) * rand4;
		spreads[i].y = sinf(rand3) * rand4;

		const auto final_spread_x = spreads[i].x + v37;
		const auto final_spread_y = spreads[i].y + v38;

		Vector forward, right, up;
		math::AngleVectors(viewangles, &forward, &right, &up);

		auto vec_dir = forward + (right * final_spread_x) + (up * final_spread_y);
		VectorNormalize(vec_dir);

		float flMaxRange = 8000;

		auto vec_end = vec_start + vec_dir * flMaxRange; // max bullet range is 10000 units

		Ray_t ray;
		ray.Init(vec_start, vec_end);

		CTraceFilter filter;
		filter.pSkip = local_player;

		trace_t tr;

		g_trace->TraceRay(ray, 0x4600400B, &filter, &tr);

		// Check for player hitboxes extending outside their collision bounds
		const float rayExtension = 40.0f;
		game::UTIL_ClipTraceToPlayers(vec_start, vec_end + vec_dir * rayExtension, 0x4600400B, &filter, &tr);

		if (tr.fraction == 1.0f)
			continue; // we didn't hit anything, stop tracing shoot

		auto entity = reinterpret_cast<C_BasePlayer*>(tr.m_pEnt);
		if (!entity || entity->get_life_state() == 1)
			continue;

		if (!Options.Misc.misc_triggerbot_filter[5] && entity->get_team_num() == local_player->get_team_num())
			continue;

		auto can_continue = false;
		if (Options.Misc.misc_triggerbot_filter[0] && tr.hitgroup == HITGROUP_HEAD)
			can_continue = true;
		if (Options.Misc.misc_triggerbot_filter[1] && tr.hitgroup == HITGROUP_CHEST)
			can_continue = true;
		if (Options.Misc.misc_triggerbot_filter[2] && tr.hitgroup == HITGROUP_STOMACH)
			can_continue = true;
		if (Options.Misc.misc_triggerbot_filter[3] && (tr.hitgroup == HITGROUP_LEFTARM || tr.hitgroup == HITGROUP_RIGHTARM))
			can_continue = true;
		if (Options.Misc.misc_triggerbot_filter[4] && (tr.hitgroup == HITGROUP_LEFTLEG || tr.hitgroup == HITGROUP_RIGHTLEG))
			can_continue = true;

		if (!can_continue)
			continue;

		if (custom_seed != -1)
		{
			cmd->random_seed = custom_seed & 0x7FFFFFFF;

			//Generate a command number for the custom seed
			unsigned cmd_number = 0;
			while ((MD5_PseudoRandom(cmd_number) & 0xFF) != custom_seed)
				cmd_number++;

			cmd->command_number = cmd_number;
		}

		cmd->buttons |= IN_ATTACK;

	
			if (Options.Visuals.visuals_triggerbot_hit_point)
				g_debugoverlay->AddBoxOverlay(tr.endpos, Vector(-2, -2, -2), Vector(2, 2, 2), cmd->viewangles, 255, 0, 0, 127, 4);

			if (Options.Visuals.visuals_triggerbot_hitbox)
			{
				static auto DrawClientHitboxes = reinterpret_cast<void(__thiscall*)(void*, float, bool)>(
					tools::find_pattern("client.dll", "55 8B EC 83 EC 60 57"));
				DrawClientHitboxes(tr.m_pEnt, 4.f, false);
			}
		
	}
}




void cmisc::move(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;

	switch (Options.Misc.trigger)
	{
	case 1:
		triggerbot(cmd, local_player);
		break;
	case 2:
	{
		for (auto i = 0; i < 256; i++)
			triggerbot(cmd, local_player, i);
		break;
	}
	default:
		break;
	}
}

void bhop(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
		cmd->buttons |= IN_JUMP;
	}
	else if (cmd->buttons & IN_JUMP)
	{
		if (local_player->get_flags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

void SetShadows() {

	auto Name = g_cvar->FindVar("r_shadows");
	Name->SetValue(Options.Visuals.NoShadows ? 0 : 1);
}

void cmisc::FakeLowLatency()
{

	auto engine = (DWORD)GetModuleHandleA("engine.dll");
	auto fps_value = *(float*)(engine + 0x67093C);
	if (!Checked)
	{
		*(float*)(engine + 0x624990) = 1;
		Checked = true;
	}
	if (Options.Misc.FakeLowLatency && Checked)
	{
		g_engine->ClientCmd_Unrestricted("cl_cmdrate 1");
		Checked1 = true;
	}
	else if (Checked1)
	{
		g_engine->ClientCmd_Unrestricted("cl_cmdrate 67");
		Checked1 = false;
	}
}

void cmisc::engine_prediction(C_BasePlayer* player, CUserCmd* cmd)
{
	static auto g_pMoveData = *reinterpret_cast<CMoveData**>(
		tools::find_pattern("client.dll", "FF 35 ? ? ? ? 57") + 2);
	static auto m_nPredictionRandomSeed = *reinterpret_cast<int**>(
		tools::find_pattern("client.dll", "A3 ? ? ? ? 5D C3 55 8B EC 8B 45 08") + 1);
	static auto m_pPredictionPlayer = *reinterpret_cast<C_BasePlayer***>(
		tools::find_pattern("client.dll", "89 3D ? ? ? ? F3 0F 2A 87") + 2);

	auto player_address = reinterpret_cast<std::uintptr_t>(player);

	//Set m_pCurrentCommand
	*reinterpret_cast<CUserCmd**>(player_address + 0x101C) = cmd;

	*m_nPredictionRandomSeed = cmd->random_seed;
	*m_pPredictionPlayer = player;

	if (*reinterpret_cast<bool*>(reinterpret_cast<std::uintptr_t>(g_prediction) + 0xB))
		g_globals->frametime = 0.0;
	else
		g_globals->frametime = g_globals->interval_per_tick;

	g_gamemovement->StartTrackPredictionErrors(player);

	if (cmd->weaponselect)
	{
		printf("cmd->weaponselect: %d\n", cmd->weaponselect);
	}

	if (cmd->impulse)
	{
		//Set m_nImpulse, yes its 4 bytes, not 1, i have no fucking idea why
		*reinterpret_cast<DWORD*>(player_address + 0x10C4) = cmd->impulse;
	}

	player->UpdateButtonState(cmd->buttons);

	player->SetLocalViewAngles(cmd->viewangles);

	//TODO
	//if (C_BasePlayer::PhysicsRunThink(player, 0))
	//	(*(void(__thiscall **)(int))(*(_DWORD *)player + 0x3F4))(player);
	//thinktick = C_BasePlayer::GetNextThinkTick((_DWORD *)player, 0);
	//if (thinktick > 0 && thinktick <= *(_DWORD *)(player + 0x10EC))
	//{
	//	C_BasePlayer::SetNextThink((_DWORD *)player, -1.0, 0);
	//	(*(void(__thiscall **)(int))(*(_DWORD *)player + 0x1E4))(player);// C_BasePlayer::Think
	//}

	g_prediction->SetupMove(player, cmd, g_movehelper, g_pMoveData);
	g_gamemovement->ProcessMovement(player, g_pMoveData);
	g_prediction->FinishMove(player, cmd, g_pMoveData);
	g_gamemovement->FinishTrackPredictionErrors(player);

	//Set m_pCurrentCommand
	*reinterpret_cast<CUserCmd**>(player_address + 0x101C) = nullptr;

	*m_nPredictionRandomSeed = -1;
	*m_pPredictionPlayer = nullptr;

}

void cmisc::FPS()
{
	auto engine = (DWORD)GetModuleHandleA("engine.dll");
	auto fps_value = *(float*)(engine + 0x67093C);
	if (!Options.Misc.LowFps)
	{
		if (fps_value != 300)
		*(float*)(engine + 0x67093C) = 300;
		return;
	}
	
	
	if (fps_value > 35)
		*(float*)(engine + 0x67093C) = 34.2f;
	
}

void Kz(CUserCmd* cmd)
{

	if (cmd->buttons & IN_FORWARD) { Keyforwardm = true; }
	else { Keyforwardm = false; }
	if (cmd->buttons & IN_MOVELEFT) { Keymoveleft = true; }
	else { Keymoveleft = false; }
	if (cmd->buttons & IN_MOVERIGHT) { Keymoveright = true; }
	else { Keymoveright = false; }
	if (cmd->buttons & IN_BACK) { Keyback = true; }
	else { Keyback = false; }
	if (cmd->buttons & IN_DUCK) { Keyduck = true; }
	else { Keyduck = false; }
	if (cmd->buttons & IN_JUMP) { Keyjump = true;; }
	else { Keyjump = false; }
}
int rotation_start_index;
void ImRotateStart()
{
	rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
}

ImVec2 ImRotationCenter()
{
	ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

	const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

	return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
}

ImVec2 operator-(const ImVec2& l, const ImVec2& r)
{
	return{ l.x - r.x, l.y - r.y };
}

void ImRotateEnd(float rad, ImVec2 center)
{
	float s = sin(rad), c = cos(rad);
	center = ImRotate(center, s, c) - center;

	auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}

void CrossHair()
{
	float x = ImGui::GetWindowSize().x / 2, y = ImGui::GetWindowSize().y / 2;
	float ColorHSV[3];
	float ColorRGB[3];
	float ColorFloat;

	ImGui::ColorConvertRGBtoHSV(Options.Visuals.CrosshairRed, Options.Visuals.CrosshairGreen, Options.Visuals.CrosshairBlue, ColorHSV[0], ColorHSV[1], ColorHSV[2]);
	ImRotateStart();
	ColorFloat = ColorHSV[0];
	for (unsigned int i = 1; i <= 15; i++)
	{
		ColorFloat += 1.0f / 15.0f;
		if (ColorFloat > 1.0f)
			ColorFloat -= 1.0f;
		ImGui::ColorConvertHSVtoRGB(ColorFloat, ColorHSV[1], ColorHSV[2], ColorRGB[0], ColorRGB[1], ColorRGB[2]);
		ImGui::GetCurrentWindow()->DrawList->AddLine({ x - i - Options.Misc.visual_crosshair_offset, y - i - Options.Misc.visual_crosshair_offset }, { x - i - 1 - Options.Misc.visual_crosshair_offset, y - i - 1 - Options.Misc.visual_crosshair_offset }, ImColor(ColorRGB[0], ColorRGB[1], ColorRGB[2], (float)Options.Misc.visual_alpha), 2.0f);
	}

	ColorFloat = ColorHSV[0];
	for (unsigned int i = 1; i <= 15; i++)
	{
		ColorFloat += 1.0f / 15.0f;
		if (ColorFloat > 1.0f)
			ColorFloat -= 1.0f;
		ImGui::ColorConvertHSVtoRGB(ColorFloat, ColorHSV[1], ColorHSV[2], ColorRGB[0], ColorRGB[1], ColorRGB[2]);
		ImGui::GetCurrentWindow()->DrawList->AddLine({ x + i + Options.Misc.visual_crosshair_offset, y - i - Options.Misc.visual_crosshair_offset }, { x + i + 1 + Options.Misc.visual_crosshair_offset, y - i - 1 - Options.Misc.visual_crosshair_offset }, ImColor(ColorRGB[0], ColorRGB[1], ColorRGB[2], (float)Options.Misc.visual_alpha), 2.0f);
	}

	ColorFloat = ColorHSV[0];
	for (unsigned int i = 1; i <= 15; i++)
	{
		ColorFloat += 1.0f / 15.0f;
		if (ColorFloat > 1.0f)
			ColorFloat -= 1.0f;
		ImGui::ColorConvertHSVtoRGB(ColorFloat, ColorHSV[1], ColorHSV[2], ColorRGB[0], ColorRGB[1], ColorRGB[2]);
		ImGui::GetCurrentWindow()->DrawList->AddLine({ x + i + Options.Misc.visual_crosshair_offset, y + i + Options.Misc.visual_crosshair_offset }, { x + i + 1 + Options.Misc.visual_crosshair_offset, y + i + 1 + Options.Misc.visual_crosshair_offset }, ImColor(ColorRGB[0], ColorRGB[1], ColorRGB[2], (float)Options.Misc.visual_alpha), 2.0f);
	}

	ColorFloat = ColorHSV[0];
	for (unsigned int i = 1; i <= 15; i++)
	{
		ColorFloat += 1.0f / 15.0f;
		if (ColorFloat > 1.0f)
			ColorFloat -= 1.0f;
		ImGui::ColorConvertHSVtoRGB(ColorFloat, ColorHSV[1], ColorHSV[2], ColorRGB[0], ColorRGB[1], ColorRGB[2]);
		ImGui::GetCurrentWindow()->DrawList->AddLine({ x - i - Options.Misc.visual_crosshair_offset, y + i + Options.Misc.visual_crosshair_offset }, { x - i - 1 - Options.Misc.visual_crosshair_offset, y + i + 1 + Options.Misc.visual_crosshair_offset }, ImColor(ColorRGB[0], ColorRGB[1], ColorRGB[2], (float)Options.Misc.visual_alpha), 2.0f);
	}
	static float RotateButton = 0.0f;
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	if (Options.Misc.visual_crosshair_spin)
	{
		if (GetTickCount() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				RotateButton += (0.001f * (M_PI * 2)) * Options.Misc.visual_crosshair_spin;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount();
		}

		if (RotateButton / (M_PI * 2) > 1.0f || RotateButton / (M_PI * 2) < -1.0f)
			RotateButton = 0.0f;
	}
	else
		RotateButton = 0.0f;

	ImRotateEnd(RotateButton,ImRotationCenter());
}

void DrawCrossHair()
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	
		float WindowBorderSize = ImGui::GetStyle().WindowBorderSize;
		ImGui::GetStyle().WindowBorderSize = 0.0f;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin("DrawCrossHair", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
		{
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiSetCond_Always);

			if (Options.Misc.visual_crosshair && !local_player->IsDormant() && g_engine->GetMaxClients())
			{
				CrossHair();
			}
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::GetStyle().WindowBorderSize = WindowBorderSize;
		}
	
}

void DrawKzKeys()
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	if (Options.Visuals.ShowKeys && !local_player->IsDormant() && g_engine->GetMaxClients())
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.25f));
		ImGui::SetNextWindowPos(ImVec2(167, (ImGui::GetIO().DisplaySize.y / 2) - ImGui::GetIO().DisplaySize.y / 20 * 1), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("kz-show-keys", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("%s", Keyforwardm ? "  W" : "  |");
			ImGui::Text("%s %s %s", Keymoveleft ? "A" : "-", Keyback ? "S" : "+", Keymoveright ? "D" : "-");
			ImGui::Text(Keyduck ? " Duck" : "  |");
			ImGui::Text(Keyjump ? " Jump" : "  |");

			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

void FastRun(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	if (Options.Misc.Fastrun && local_player->get_flags() & FL_ONGROUND)
	{
		static bool Run = false;
		if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVELEFT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVERIGHT))
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 205.6002f;
				cmd->forwardmove -= 205.6002f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 205.6002f;
				cmd->forwardmove += 205.6002f;
			}
		}
		else if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVERIGHT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVELEFT))
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 205.6002f;
				cmd->forwardmove += 205.6002f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 205.6002f;
				cmd->forwardmove -= 205.6002f;
			}
		}
		else if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK)
		{
			if (Run)
			{
				Run = false;
				cmd->sidemove -= 205.6002f;
			}
			else
			{
				Run = true;
				cmd->sidemove += 205.6002f;
			}
		}
		else if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
		{
			if (Run)
			{
				Run = false;
				cmd->forwardmove -= 205.6002f;
			}
			else
			{
				Run = true;
				cmd->forwardmove += 205.6002f;
			}
		}
	}
}

void AutoPistol(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;

	auto weapon = local_player->GetActiveWeapon();
	if (!weapon)
		return;

	if (weapon->get_clip() <= 0)
		return;



	auto weapon_data = weapon->GetWpnData();
	if (!weapon_data)
		return;
	if (!weapon_data->bFullAuto)
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		if (cmd->tick_count % 2)	cmd->buttons |= IN_ATTACK;
		else						cmd->buttons &= ~IN_ATTACK;
	}
	
}


namespace features
{
	void fastStop(CUserCmd* cmd)
	{
		if (!Options.Misc.FastStop || (Options.Misc.Edgejumnp && GetAsyncKeyState(Options.Misc.EdgejumnpKey)))
			return;

		auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
		if (!local_player)
			return;

		auto can_continue = false;
		if (Options.Misc.FastStop_filter[0] && local_player->get_flags() & FL_ONGROUND)
			can_continue = true;
		if (Options.Misc.FastStop_filter[1] && !(local_player->get_flags() & FL_ONGROUND))
			can_continue = true;
		if (Options.Misc.FastStop_filter[2])
			can_continue = true;

		if (!can_continue) return;
		Vector velocity = local_player->m_vecVelocity();
		QAngle direction;
		math::vector2angles(velocity, direction);
		float speed = velocity.Length2D();
		bool inMove = cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT;
		if (inMove || GetAsyncKeyState(VK_SPACE))
			return;

		
		direction.y = cmd->viewangles.y - direction.y;

		Vector forward;
		math::angle2vectors(direction, forward);

		Vector right = (forward + 0.217812) * -speed;
		Vector left = (forward + -0.217812) * -speed;

		Vector move_forward = (forward + 0.217812) * -speed;
		Vector move_backward = (forward + -0.217812) * -speed;


		{
			if (!(cmd->buttons & IN_MOVELEFT))
			{
				cmd->sidemove += +left.y;
			}

			if (!(cmd->buttons & IN_MOVERIGHT))
			{
				cmd->sidemove -= -right.y;
			}
		}

		
		{
			if (!(cmd->buttons & IN_FORWARD))
			{
				if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
					return;

				cmd->forwardmove += +move_forward.x;
			}

			if (!(cmd->buttons & IN_BACK))
			{
				if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
					return;

				cmd->forwardmove -= -move_backward.x;
			}
		}
	}
}

static void NormalizeInOut(Vector& vIn, Vector& vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

static void AngleVectors2(const Vector& qAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	math::SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
	math::SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp * cy;
	vecForward[1] = cp * sy;
	vecForward[2] = -sp;
}

static void VectorAngles2(const Vector& vecForward, Vector& vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}


void Walkbot(Vector& OrigAng, CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;

	bool walkbotBefore = false;

	Vector viewangles;
	g_engine->GetViewAngles(viewangles);

	static int OldMouseX = OrigAng.y;
	int mousedx = OldMouseX - OrigAng.y;

	auto fDistanceToWall = [&](Vector diff = Vector(0, 0, 0))->float {
		auto tmpviewangles = viewangles + diff;
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = local_player;
		Vector begin = local_player->get_eye_position(), t, end;
		AngleVectors2(tmpviewangles, t);
		NormalizeInOut(t, end);
		end *= 8192.0f;
		end += begin;
		ray.Init(begin, end);
		g_trace->TraceRay(ray, 0x4600400B, &filter, &tr);
		return (begin - tr.endpos).Size();
	};

	static float old1, old2, old3;
	if (local_player->m_vecVelocity().Length() < 3)
	{
		viewangles.y += 2.0f;
	}
	float Distances = Options.Misc.flDistance;
	if (fDistanceToWall() < Distances) // we are near to some wall
	{
		int turn = Options.Misc.iTurn;
		float negativeDist = fDistanceToWall(Vector(0, -1, 0)), positiveDist = fDistanceToWall(Vector(0, 1, 0));
		if (abs(negativeDist - positiveDist) < 1.0f)
		{
			viewangles.y += turn;
		}
		else
		{
			viewangles.y += positiveDist < negativeDist ? -1 : 1;
		}
	}

	if (abs(viewangles.x) > 0)
		viewangles.x = 1;

	while (viewangles.y > 180.0f)
		viewangles.y -= 360.0f;
	while (viewangles.y < -180.0f)
		viewangles.y += 360.0f;

	g_engine->SetViewAngles(viewangles);

	if (!walkbotBefore)
	{
		cmd->forwardmove = 450.f;
		walkbotBefore = true;
	}

	else if (walkbotBefore)
	{
		walkbotBefore = false;
		cmd->forwardmove = 450.f;
	}
}


int lastFlags = 0;
float heightDiff;
bool shouldDuck;



void NoFall::PrePredictionCreateMove(CUserCmd* cmd)
{
	Ray_t ray;
	trace_t tr;

	if (!Options.Misc.AutoJumpBug)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)g_entitylist->GetClientEntity(g_engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	lastFlags = localplayer->get_flags();

	if (shouldDuck && !(lastFlags & FL_ONGROUND)) {
		
		cmd->buttons |= IN_DUCK;
	}

	Vector origin = localplayer->get_eye_position();
	ray.Init(origin, Vector(origin.x, origin.y, origin.z - 8192.0f));
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	g_trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);
	heightDiff = origin.z - tr.endpos.z;
	if (heightDiff > 200) {
	shouldDuck = true;
	}
	
}

void NoFall::PostPredictionCreateMove(CUserCmd* cmd) {
	if (!Options.Misc.AutoJumpBug)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)g_entitylist->GetClientEntity(g_engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (!(lastFlags & FL_ONGROUND) && (localplayer->get_flags() & FL_ONGROUND) && shouldDuck) {
		cmd->buttons &= ~IN_DUCK;
		shouldDuck = false;
	}
}

QAngle NormalizeAngle(QAngle angles)
{
	if (angles.x > 89)
	{
		angles.x = 89;
	}
	else if (-89 > angles.x)
	{
		angles.x = -89;
	}

	if (angles.y > 180)
	{
		angles.y -= 360;
	}
	else if (-180 > angles.y)
	{
		angles.y += 360;
	}

	angles.z = 0;

	return angles;
}

inline void DrawRect(int x1, int y1, int x2, int y2, Color clr)
{
	g_surface->DrawSetColor(clr);
	g_surface->DrawFilledRect(x1, y1, x2, y2);
}


static void RageStrafe(CUserCmd* cmd,C_BasePlayer* pLocal)
{
	
	static bool leftRight;
	bool inMove = cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT;

	if (cmd->buttons & IN_FORWARD && pLocal->m_vecVelocity().Length() <= 50.0f)
		cmd->forwardmove = 450.0f;

	float yaw_change = 0.0f;
	if (pLocal->m_vecVelocity().Length() > 50.f)
		yaw_change = 30.0f * fabsf(30.0f / pLocal->m_vecVelocity().Length());

	auto weapon = pLocal->GetActiveWeapon();
	if (weapon && !weapon->get_clip() == 0 && cmd->buttons & IN_ATTACK)
		yaw_change = 0.0f;

	QAngle viewAngles;
	g_engine->GetViewAngles(viewAngles);
	if (cmd->buttons & IN_ATTACK)
		return;
	
	
	if (!(pLocal->get_flags() & FL_ONGROUND) && !inMove)
	{
		if (leftRight || cmd->mousedx > 0)
		{
			viewAngles.y += yaw_change;
			cmd->sidemove = 450.f;
		}
		else if (!leftRight || cmd->mousedx < 0)
		{
			viewAngles.y -= yaw_change;
			cmd->sidemove = -450.f;
		}

		leftRight = !leftRight;
	}
	
	
	NormalizeAngle(viewAngles);
	math::clamp_angles(viewAngles);

	math::correct_movement(viewAngles, cmd, cmd->forwardmove, cmd->sidemove);

	//if (!curs.AutoStrafe_silent)
	//	cmd->viewangles = viewAngles;
}



void AutoStrafe::Run(CUserCmd* cmd)
{
	if (!Options.Misc.bAutoStrafe)
		return;

	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;

	if (!(local_player->get_flags() & FL_ONGROUND))
	{

		if (!GetAsyncKeyState(VK_SPACE))
			return;
		switch (Options.Misc.iAutoStrafeMode)
		{
		case 0:
			cmd->sidemove = cmd->mousedx < 1 ? -450.f : 450.f;
			break;
		case 1:
			cmd->sidemove = cmd->mousedx < 1 ? 450.f : -450.f;
			break;
		case 2:
			cmd->forwardmove = cmd->mousedx < 1 ? -450.f : 450.f;
			break;
		case 3:
			cmd->forwardmove = cmd->mousedx < 1 ? 450.f : -450.f;
			break;
		case 4:
			RageStrafe(cmd, local_player);
		default:
			break;
		}
	}
}

void BacktrackHitBoxes()
{
	if (!Options.Misc.BackTrack)
		return;

	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	for (int i = 0; i < g_engine->GetMaxClients(); i++)
	{
		auto entity = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));
		if (!entity || entity == local_player || entity->get_team_num() == local_player->get_team_num() || entity->IsDormant())
			continue;
		if (entity->m_vecVelocity().Length() <= 15.0f)
			continue;
		float Value = 0.200;
		if (Options.Misc.FakeLatency)
			Value += (Options.Misc.FakeLatencyValue / 1000);
		if (f_LegitBacktrack.entData[entity->GetIndex()].size() < 3)
			continue;

		if (Options.Visuals.BacktrackChams)
		{
			//for (int j = 0; j < f_LegitBacktrack.entData[entity->GetIndex()].size(); j++)
			{
				{
					static auto DrawClientHitboxes = reinterpret_cast<void(__thiscall*)(void*, float, bool)>(
						tools::find_pattern("client.dll", "55 8B EC 83 EC 60 57"));
					DrawClientHitboxes(entity, Value, false);
				}
			}

			//entity->SetAngles(oldAngs);
			//entity->SetAbsOrigin(oldOrigin);
		}
	}
}

namespace knife_bot
{
	const auto stab_dist = 64.f;
	const auto slash_dist = 64.f;

	void handle(CUserCmd* cmd, bool& send_packet)
	{
		if (!Options.Misc.KnifeBot)
			return;
		auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
		if (!local_player)
			return;

		if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
			return;

		auto weapon = local_player->GetActiveWeapon();

		if (!weapon)
			return;

		if (weapon->GetWeaponID() != WEAPON_KNIFE)
			return;
		
		const auto server_time = local_player->get_tick_base() * g_globals->interval_per_tick;
		if (server_time <= weapon->get_next_primary_attack() || server_time <= local_player->get_next_attack())
			return;

		Ray_t ray;
		QAngle angles;
		trace_t tr;



	//	const auto interpolation_comp = get_interpolation_compensation();
		

	
		
			for (auto i = 0;i<g_engine->GetMaxClients();i++)
			{
				const auto eye_pos = local_player->get_eye_position();
				auto entity = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));
				if (!entity || entity == local_player || entity->get_team_num() == local_player->get_team_num()||entity->IsDormant())
					continue;

				CTraceFilterSkipTwoEntities filter = CTraceFilterSkipTwoEntities(local_player, entity);
				
	
				
					float old_side_move = cmd->sidemove;
					float old_forward_move = cmd->forwardmove;

					
					auto hitboxpos = entity::get_hitbox_position(entity, 12);
					

					const auto distance = eye_pos.DistTo(hitboxpos);
					if (distance > slash_dist)
						continue;

					ray.Init(eye_pos, hitboxpos);
					g_trace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);
					if (eye_pos.DistTo(tr.endpos) > slash_dist)
						continue;

					

					auto old_angles = cmd->viewangles;
					cmd->buttons |=  IN_ATTACK2;
					
					//cmd->viewangles = angles;

					//math::correct_movement(old_angles, cmd, old_forward_move, old_side_move);

					//send_packet = false;

					//return;
			    
		}
	}
}
