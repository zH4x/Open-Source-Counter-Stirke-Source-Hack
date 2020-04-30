#include "hooks.h"
#include "../tools/entity.h"
#include "../tools/math.h"
#include "../tools/game.h"
#include "../hacks/aimbot.h"
#include "../hacks/visuals.h"
#include "../hacks/misc.h"
#include "../hacks/edgejump.h"
#include "../hacks/hitmarker.h"
#include "../hacks/BulletTracer.h"
#include "../hacks/FakeLatency.h"
#include "../hacks/backtrack.h"
#include "../Menu.h"


LagCompensation* gLagCompensation;
cvmt_hook* net_channel_hook = nullptr;
std::vector<trace_pos_info> trace_pos;
void __stdcall _CreateMove(int sequence_number, float input_sample_frametime, bool active, bool& sendpacket)
{

	o_create_move(sequence_number, input_sample_frametime, active);

	

	auto cmd = &g_input->m_pCommands[sequence_number % MULTIPLAYER_BACKUP];
	auto verified = &g_input->m_pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];

	
	if (!cmd || !verified)
		return;
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;
	auto weapon = local_player->GetActiveWeapon();

	if (weapon)
	{
		if (weapon->GetWeaponID() == WEAPON_KNIFE)
		{
			if (Options.Misc.KnifeBot)
				knife_bot::handle(cmd, sendpacket);
		}
		else
		{
			if (Options.Misc.AutoPistol && !Cvars.MenuOpened && !g_engine->Con_IsVisible())
				AutoPistol(cmd);
			misc->move(cmd);
			aimbot.move(cmd, sendpacket);
			aimbot.noSpread(cmd, sendpacket);
		}
	}
	BacktrackHitBoxes();
	if (Options.Misc.bBunnyhop)
		bhop(cmd);
		if(Options.Misc.BackTrack)
		f_LegitBacktrack.Run(cmd);
		SetShadows();
		Vector OrigAng = cmd->viewangles;
		OrigAng.Normalize();
		if (Options.Misc.bWalkBot)
			Walkbot(OrigAng,cmd);
		if (Options.Misc.bAutoStrafe)
		gStrafe.Run(cmd);
		if (Options.Misc.Fastrun)
		FastRun(cmd);
		if (Options.Visuals.ShowKeys)
		Kz(cmd);
		if (Options.Misc.FastStop)
		features::fastStop(cmd);
		misc->FPS();
		misc->FakeLowLatency();
	if (Options.Misc.AutoJumpBug || Options.Misc.Edgejumnp)
	{
		if (Options.Misc.Edgejumnp)
		{
			Edge.PrePredictionCreateMove(cmd, local_player);
			misc->engine_prediction(local_player, cmd);
			Edge.PostPredictionCreateMove(cmd, local_player);
		}
		if (Options.Misc.AutoJumpBug)
		{

			gFall.PrePredictionCreateMove(cmd);
			misc->engine_prediction(local_player, cmd);
			gFall.PostPredictionCreateMove(cmd);
		}
	}
	
		if (!Options.Misc.hooked)
		{
			if (net_channel_hook)
				net_channel_hook = nullptr;
		}


		gLagCompensation->UpdateIncomingSequences();



		if (!net_channel_hook)
		{
			if (g_clientstate->m_NetChannel)
			{
				auto netchan = reinterpret_cast<CNetChan*>(g_clientstate->m_NetChannel);

				if (netchan && !net_channel_hook)
				{
					net_channel_hook = new cvmt_hook(netchan);
					oSendDataGram = net_channel_hook->hook<senddatagram_t>(46, reinterpret_cast<void*>(send_data_gram_hook));
					//net_channel_hook->hook(hooks::indexes::send_net_msg, hooks::send_net_msg_hook);
					Options.Misc.hooked = true;
				}
			}
		}
	
		
	

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();
}

void __declspec(naked) __stdcall create_move(int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		LEA  EAX, [EBP - 01]
		PUSH EAX
		PUSH[ESP + 0x10]
		PUSH[ESP + 0x10]
		PUSH[ESP + 0x10]
		CALL _CreateMove
		RET 0x0C
	}
}