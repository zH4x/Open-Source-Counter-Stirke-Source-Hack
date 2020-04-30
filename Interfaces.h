#pragma once

#include "sdk/sdk.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "SDK/IGameEvent.h"
#include "SDK/beams.h"
#include "SDK/IInputSystem.H"
#include "SDK/IMaterial.h"
#include "SDK/ICVar.h"
#include "SDK/RenderView.h"



class ClientModeShared
{
public:
	bool IsChatPanelOutOfFocus(void)
	{
		typedef PVOID(__thiscall* OriginalFn)(PVOID);
		PVOID CHudChat = get_vfunc<OriginalFn>(this, 19)(this);
		if (CHudChat)
		{
			return *(PFLOAT)((DWORD)CHudChat + 0xFC) == 0;
		}
		return false;
	}
};
//------------------------------------------//
// CreateInterface
//------------------------------------------//
extern ClientModeShared* ClientMode;
extern IVRenderView* g_renderview;
extern IBaseClientDll*		g_client;
extern IClientEntityList*	g_entitylist;
extern IGameMovement*		g_gamemovement;
extern IPrediction*			g_prediction;
extern IVEngineClient*		g_engine;
extern IVModelInfo*			g_modelinfo;
extern IEngineTrace*		g_trace;
extern IVDebugOverlay*		g_debugoverlay;
extern ICvar*				g_cvar;
extern IPhysicsSurfaceProps* g_physprops;
extern CEngineVGui*			g_enginevgui;
extern ISurface*			g_surface;
extern IGameEventManager2* EventManager;
extern IPanel* Panels;
extern IViewRenderBeams* g_beams;
extern IInputSystem* g_InputSystem;
extern IMaterialSystem* MatSystemOther;
extern CModelRender* MdlRender;
//------------------------------------------//
// Pattern Scan
//------------------------------------------//
extern CInput*				g_input;
extern CClientState*	g_clientstate;
extern IDirect3DDevice9*	g_d3ddevice;
extern CGlobalVars*			g_globals;
extern IMoveHelper*			g_movehelper;
//------------------------------------------//
// Initialize Interfaces
//------------------------------------------//
extern bool* g_pbCursorLocked();
extern void initialize_interfaces();