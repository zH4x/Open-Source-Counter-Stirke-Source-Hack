#include "interfaces.h"
#include "tools/tools.h"
#include "Menu/Menu.h"





//------------------------------------------//
// CreateInterface
//------------------------------------------//
IBaseClientDll*		g_client = nullptr;
IClientEntityList*	g_entitylist = nullptr;
IGameMovement*		g_gamemovement = nullptr;
IPrediction*		g_prediction = nullptr;
IVEngineClient*		g_engine = nullptr;
IVModelInfo*		g_modelinfo = nullptr;
IEngineTrace*		g_trace = nullptr;
IVDebugOverlay*		g_debugoverlay = nullptr;
ICvar*				g_cvar = nullptr;
IPhysicsSurfaceProps* g_physprops = nullptr;
CEngineVGui*		g_enginevgui = nullptr;
ISurface*			g_surface = nullptr;
IGameEventManager2* EventManager = nullptr;
IPanel* Panels = nullptr;
ClientModeShared* ClientMode = nullptr;
IInputSystem* g_InputSystem = nullptr;
IViewRenderBeams* g_beams = nullptr;
IMaterialSystem* MatSystemOther = nullptr;
CModelRender* MdlRender = nullptr;
//------------------------------------------//
// Pattern Scan
//------------------------------------------//
CInput*				g_input = nullptr;
CClientState*	g_clientstate = nullptr;
IDirect3DDevice9*	g_d3ddevice = nullptr;
CGlobalVars*		g_globals = nullptr;
IMoveHelper*		g_movehelper = nullptr;
IVRenderView* g_renderview = nullptr;

bool* g_pbCursorLocked()
{
	return *reinterpret_cast<bool**>(
		tools::find_pattern("vguimatsurface.dll", "A3 ? ? ? ? C6 05") + 0x7);
}

//------------------------------------------//
// Initialize Interfaces
//------------------------------------------//
void initialize_interfaces()
{
	//------------------------------------------//
	// Factories
	//------------------------------------------//

	auto client_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface"));
	auto engine_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"));
	auto vstdlib_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface"));
	auto vphysics_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface"));
	auto vguimatsurface_factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface"));
	auto inputsysteam = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("inputsystem.dll"), "CreateInterface"));
	auto VGUI2Factory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface"));
	auto MaterialSystemFactory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA("MaterialSystem.dll"), "CreateInterface"));
	//------------------------------------------//
	// CreateInterface
	//------------------------------------------//
	g_client = reinterpret_cast<IBaseClientDll*>(client_factory("VClient017", nullptr));
	g_entitylist = reinterpret_cast<IClientEntityList*>(client_factory("VClientEntityList003", nullptr));
	g_gamemovement = reinterpret_cast<IGameMovement*>(client_factory("GameMovement001", nullptr));
	g_prediction = reinterpret_cast<IPrediction*>(client_factory("VClientPrediction001", nullptr));
	g_engine = reinterpret_cast<IVEngineClient*>(engine_factory("VEngineClient014", nullptr));
	g_modelinfo = reinterpret_cast<IVModelInfo*>(engine_factory("VModelInfoClient006", nullptr));
	g_trace = reinterpret_cast<IEngineTrace*>(engine_factory("EngineTraceClient003", nullptr));
	g_debugoverlay = reinterpret_cast<IVDebugOverlay*>(engine_factory("VDebugOverlay003", nullptr));
	g_cvar = reinterpret_cast<ICvar*>(vstdlib_factory("VEngineCvar004", nullptr));
	g_physprops = reinterpret_cast<IPhysicsSurfaceProps*>(vphysics_factory("VPhysicsSurfaceProps001", nullptr));
	g_enginevgui = reinterpret_cast<CEngineVGui*>(engine_factory("VEngineVGui001", nullptr));
	g_surface = reinterpret_cast<ISurface*>(vguimatsurface_factory("VGUI_Surface030", nullptr));
	EventManager = reinterpret_cast<IGameEventManager2*>(engine_factory("GAMEEVENTSMANAGER002", nullptr));
	g_InputSystem = (IInputSystem*)inputsysteam(INPUTSYSTEM_INTERFACE_VERSION, NULL);
	Panels = (IPanel*)VGUI2Factory("VGUI_Panel009", NULL);
	MatSystemOther = reinterpret_cast<IMaterialSystem*>(MaterialSystemFactory("VMaterialSystem080", nullptr));
	MdlRender = reinterpret_cast<CModelRender*>(engine_factory("VEngineModel016", nullptr));
	g_renderview = reinterpret_cast<IVRenderView*>(engine_factory(VENGINE_RENDERVIEW_INTERFACE_VERSION, nullptr));
	//------------------------------------------//
	// Pattern Scan
	//------------------------------------------//
	auto dwClientModeAddress = tools::find_pattern("client.dll","8B 0D ? ? ? ? 8B 01 5D FF 60 28 CC"); //Native Source SDK 2013 ClientMode Signature
	ClientMode = **(ClientModeShared***)(dwClientModeAddress + 2);

	g_beams = **reinterpret_cast<IViewRenderBeams***>(
		tools::find_pattern("client.dll", "8B 0D ? ? ? ? 8B 01 FF 50 0C 6A 00") + 2);
	g_input = **reinterpret_cast<CInput***>(
		tools::find_pattern("client.dll", "8B 0D ? ? ? ? 8B 01 FF 60 44") + 2);
	g_clientstate = *reinterpret_cast<CClientState**>(
		tools::find_pattern("engine.dll", "B9 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 83 78 14 00") + 1);
	g_d3ddevice = **reinterpret_cast<IDirect3DDevice9***>(
		tools::find_pattern("shaderapidx9.dll", "A1 ? ? ? ? 8D 53 08") + 1);
	g_globals = **reinterpret_cast<CGlobalVars***>((
		*reinterpret_cast<uintptr_t**>(g_client))[0] + 0x34);
	g_movehelper = **reinterpret_cast<IMoveHelper***>(
		tools::find_pattern("client.dll", "FF 35 ? ? ? ? 50 8B 11 56") + 2);
}