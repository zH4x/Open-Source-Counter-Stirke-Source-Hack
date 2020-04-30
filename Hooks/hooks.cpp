#include "hooks.h"

#include "../Hacks/hitmarker.h"
#include "../Menu.h"
#include "../Hacks/BulletTracer.h"
#include "../Hacks/FakeLatency.h"
#include "../Hacks/backtrack.h"
#include "../tools/UTIL Functions.h"





float __stdcall Hooked_ViewmodelFOV()
{
	if (g_engine->IsInGame() && g_engine->IsConnected())
	{
		if (Options.Misc.flViewModelValue)
		{
			float value = Options.Misc.flViewModelValue;
			return value;
		}
		else
		{
			return 68.f;
		}
	}
	return 68.f;
}

void DrawBeamd(Vector src, Vector end, Color color)
{

	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMPOINTS;
	beamInfo.m_pszModelName = "sprites/physbeam.vmt";
	beamInfo.m_nModelIndex = -1; // will be set by CreateBeamPoints if its -1
	beamInfo.m_flHaloScale = 0.0f;
	beamInfo.m_flLife = 2.0f;
	beamInfo.m_flWidth = 3.5f;
	beamInfo.m_flEndWidth = 1.1f;
	beamInfo.m_flFadeLength = 1.0f;
	beamInfo.m_flAmplitude = 2.0f;
	beamInfo.m_flBrightness = color.a();
	beamInfo.m_flSpeed = 0.2f;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flFrameRate = 0.f;
	beamInfo.m_flRed = color.r();
	beamInfo.m_flGreen = color.g();
	beamInfo.m_flBlue = color.b();
	beamInfo.m_nSegments = 2;
	beamInfo.m_bRenderable = true;
	beamInfo.m_nFlags = 0;

	/*
	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMPOINTS;
	beamInfo.m_pszModelName = "sprites/physbeam.vmt";
	beamInfo.m_nModelIndex = -1; // will be set by CreateBeamPoints if its -1
	beamInfo.m_flHaloScale = 0.0f;
	beamInfo.m_flLife = 1.0f;
	beamInfo.m_flWidth = 1.0f;
	beamInfo.m_flEndWidth = 1.0f;
	beamInfo.m_flFadeLength = 0.0f;
	beamInfo.m_flAmplitude = 0.0f;
	beamInfo.m_flBrightness = color.a();
	beamInfo.m_flSpeed = 0.2f;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flFrameRate = 0.f;
	beamInfo.m_flRed = color.r();
	beamInfo.m_flGreen = color.g();
	beamInfo.m_flBlue = color.b();
	beamInfo.m_nSegments = 2;
	beamInfo.m_bRenderable = true;
	beamInfo.m_nFlags = 0;
	*/
	beamInfo.m_vecStart = src;
	beamInfo.m_vecEnd = end;

	Beam_t* myBeam = g_beams->CreateBeamPoints(beamInfo);

	if (myBeam)
		g_beams->DrawBeam(myBeam);
}

cvmt_hook* d3ddevice_table = nullptr;
cvmt_hook* client_table = nullptr;
cvmt_hook* input_table = nullptr;
cvmt_hook* enginevgui_table = nullptr;
cvmt_hook* g_suface_T = nullptr;
cvmt_hook* Panel_t = nullptr;
cvmt_hook* viewoverride = nullptr;


OverrideViewFn       OverrideViewFn_t = nullptr;
senddatagram_t       oSendDataGram = nullptr;
Reset_fn			o_reset = nullptr;
EndScene_fn			o_end_scene = nullptr;
CreateMove_fn		o_create_move = nullptr;
FrameStageNotify_fn	o_frame_stage_notify = nullptr;
GetUserCmd_fn		o_get_user_cmd = nullptr;
Paint_fn			o_paint = nullptr;
sdLockCursor         g_LockCursor = nullptr;
PaintTraverse        o_PaintTraverse = nullptr;
GetViewModelFOVFn GetViewModelFOV;

std::vector<trace_info> trace_logs;



void __fastcall Hooked_OverrideView(void* _this, void* _edx, CViewSetup* pSetup) // credits, ActualCheats and outi - plasma
{

	OverrideViewFn_t(_this, pSetup); //Call the original.
	if (!g_engine->IsInGame() && !g_engine->IsConnected())
		return;

	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	static Vector newOrigin;
	if (Options.Visuals.bFreeCam)
	{
		
			float freecamspeed = Options.Visuals.flFreeCamSpeed;

			if (!GetAsyncKeyState(Options.Visuals.bFreeCamKey))
			{
				newOrigin = pSetup->origin;
			}
			
			if (GetAsyncKeyState(Options.Visuals.bFreeCamKey))
			{

				unsigned int fSpeed = freecamspeed; //5.f;
				if (GetAsyncKeyState(VK_CONTROL))
					fSpeed = fSpeed * 0.45;
				if (GetAsyncKeyState(VK_SHIFT))
					fSpeed = fSpeed * 1.65;
				if (GetAsyncKeyState(0x57)) // W		
				{
					newOrigin += pSetup->angles.Forward() * fSpeed;
				}
				if (GetAsyncKeyState(0x41)) // A		
				{
					newOrigin += pSetup->angles.Right() * fSpeed;
				}
				if (GetAsyncKeyState(0x44)) // D		
				{
					newOrigin -= pSetup->angles.Right() * fSpeed;
				}
				if (GetAsyncKeyState(0x53)) // S		
				{
					newOrigin -= pSetup->angles.Forward() * fSpeed;

				}
				if (GetAsyncKeyState(VK_SPACE)) // Space		
				{
					newOrigin += pSetup->angles.Up() * fSpeed;
				}
				pSetup->origin = newOrigin;
			
		}
	}
	

	if(Options.Misc.bEnableFov)
		if (pSetup->m_fov != 20.0f && pSetup->m_fov != Options.Visuals.FovValue) // no delet this, important for when zoomed- plasma
			pSetup->m_fov = Options.Visuals.FovValue;
	
}



void __fastcall Hooked_PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	
		o_PaintTraverse(pPanels, vguiPanel, forceRepaint, allowForce); //Call the original.
		static unsigned int vguiFocusOverlayPanel;
		

		if (vguiFocusOverlayPanel == NULL)
		{											//FocusOverlayPanel
			const char* szName = Panels->GetName(vguiPanel);
			if (szName[0] == 'F' && szName[5] == 'O' && szName[12] == 'P')
			{
				vguiFocusOverlayPanel = vguiPanel;
			}
		}

		if (vguiFocusOverlayPanel == vguiPanel)
		{
			
			Panels->SetTopmostPopup(vguiFocusOverlayPanel, true);

			
			Panels->SetMouseInputEnabled(vguiPanel, Cvars.MenuOpened);
			if (g_engine->IsInGame() && g_engine->IsConnected())
			{
				if(Options.Visuals.ShowDamage)
				damage_indicators.paint();
				if (Options.Visuals.bBulletTracer)
				CBulletListener::singleton()->OnStudioRender();
			}

		}
	
}


int __fastcall send_data_gram_hook(CNetChan* netchan, void* edx, bf_write* datagram)
{

	static auto o_send_data_gram = oSendDataGram;
	if (!Options.Misc.FakeLatency || datagram)
	{
		return o_send_data_gram(netchan, datagram);
	}

	auto instate = netchan->m_nInReliableState;
	auto in_sequencenr = netchan->m_nInSequenceNr;

	auto lag_s = Options.Misc.FakeLatencyValue / 1000.f;
	auto lag_delta = lag_s - g_engine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);

	gLagCompensation->AddLatencyToNetchan(netchan, lag_delta);

	int ret = o_send_data_gram(netchan, datagram);

	netchan->m_nInReliableState = instate;
	netchan->m_nInSequenceNr = in_sequencenr;

	return ret;
}



void __fastcall hkLockCursor(ISurface* pThis, void*)
{
	if (Cvars.MenuOpened)
	{
		pThis->UnlockCursor();
		g_InputSystem->EnableInput(false);
		pThis->SetCursor(vgui::dc_arrow);
		*g_pbCursorLocked() = true;
	}
	else
	{
		g_InputSystem->EnableInput(true);
		pThis->SetCursor(vgui::dc_none);
		*g_pbCursorLocked() = false;
		g_LockCursor(pThis);
	}
}



void initialize_hooks()
{

	hWindow = FindWindowA("Valve001", nullptr);

	pOldWindowProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWindow, GWLP_WNDPROC, LONG_PTR(wnd_proc_hooked)));

	d3ddevice_table = new cvmt_hook(g_d3ddevice);
	o_reset = d3ddevice_table->hook<Reset_fn>(16, reinterpret_cast<void*>(reset_hooked));
	o_end_scene = d3ddevice_table->hook<EndScene_fn>(42, reinterpret_cast<void*>(end_scene_hooked));

	client_table = new cvmt_hook(g_client);
	o_create_move = client_table->hook<CreateMove_fn>(21, reinterpret_cast<void*>(create_move));
	//client_table->hook(23, WriteUsercmdDeltaToBuffer);
	o_frame_stage_notify = client_table->hook<FrameStageNotify_fn>(35, reinterpret_cast<void*>(frame_stage_notify));

	input_table = new cvmt_hook(g_input);
	o_get_user_cmd = input_table->hook<GetUserCmd_fn>(8, reinterpret_cast<void*>(get_user_cmd));

	g_suface_T = new cvmt_hook(g_surface);
	g_LockCursor = g_suface_T->hook<sdLockCursor>(62, reinterpret_cast<void*>(hkLockCursor));

	Panel_t = new cvmt_hook(Panels);
	o_PaintTraverse = Panel_t->hook<PaintTraverse>(41, reinterpret_cast<void*>(Hooked_PaintTraverse));

	enginevgui_table = new cvmt_hook(g_enginevgui);
	o_paint = enginevgui_table->hook<Paint_fn>(13, reinterpret_cast<void*>(paint));

	viewoverride = new cvmt_hook(ClientMode);
	OverrideViewFn_t = viewoverride->hook<OverrideViewFn>(16, reinterpret_cast<void*>(Hooked_OverrideView));
	GetViewModelFOV = viewoverride->hook<GetViewModelFOVFn>(32, reinterpret_cast<void*>(Hooked_ViewmodelFOV));


	

	

	CBulletListener::singleton()->init();
	hitmarker::singleton()->initialize();

}

void uninitialize_hooks()
{
	SetWindowLongPtr(hWindow, GWLP_WNDPROC, LONG_PTR(pOldWindowProc));
	Options.Misc.hooked = true;
	delete viewoverride;
	delete d3ddevice_table;
	delete client_table;
	delete input_table;
	delete enginevgui_table;
	delete g_suface_T;
	delete Panel_t;
	delete net_channel_hook;
	Options.Visuals.ShowDamage = false;
	Options.Visuals.bBulletTracer = false;
	Options.Visuals.bHitMarker = false;
	CBulletListener::singleton()->end();
	hitmarker::singleton()->end();
}