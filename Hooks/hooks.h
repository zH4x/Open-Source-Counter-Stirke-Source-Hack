#pragma once

#include <Windows.h>
#include "../tools/vmt_hook.h"
#include "../interfaces.h"
#include "../SDK/CViewSetup.h"
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../ImGui/imgui.h"
#include "../SDK/NetChannel.h"

extern cvmt_hook* d3ddevice_table;
extern cvmt_hook* client_table;
extern cvmt_hook* input_table;
extern cvmt_hook* enginevgui_table;
extern cvmt_hook* g_suface_T;
extern cvmt_hook* Panel_t;
extern cvmt_hook* viewoverride;
extern cvmt_hook* net_channel_hook;
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2
struct bf_write;
typedef HRESULT(STDMETHODCALLTYPE* Reset_fn)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
typedef HRESULT(STDMETHODCALLTYPE* EndScene_fn)(IDirect3DDevice9*);
typedef void(__stdcall* CreateMove_fn)(int, float, bool);
typedef void(__thiscall* FrameStageNotify_fn)(void*, ClientFrameStage_t);
typedef CUserCmd*(__thiscall* GetUserCmd_fn)(void*, int sequence_number);
typedef void(__thiscall* Paint_fn)(void*, PaintMode_t);
typedef void(__thiscall* sdLockCursor)(ISurface*);
typedef void(__thiscall* PaintTraverse)(PVOID pPanels, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
typedef int(__thiscall* senddatagram_t)(CNetChan* netchan, bf_write* datagram);
typedef void(__thiscall* OverrideViewFn) (void*, CViewSetup*);
typedef float(__stdcall* GetViewModelFOVFn)();


extern GetViewModelFOVFn GetViewModelFOV;
extern OverrideViewFn       OverrideViewFn_t;
extern senddatagram_t       oSendDataGram;
extern PaintTraverse        o_PaintTraverse;
extern sdLockCursor         g_LockCursor;
extern Reset_fn				o_reset;
extern EndScene_fn			o_end_scene;
extern CreateMove_fn		o_create_move;
extern FrameStageNotify_fn	o_frame_stage_notify;
extern GetUserCmd_fn		o_get_user_cmd;
extern Paint_fn				o_paint;

struct studiohwdata_t;
struct StudioDecalHandle_t;

struct DrawModelState_t
{
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	IClientRenderable* m_pRenderable;
	const matrix3x4* m_pModelToWorld;
	StudioDecalHandle_t* m_decals;
	int						m_drawFlags;
	int						m_lod;
};

HRESULT STDMETHODCALLTYPE	reset_hooked(IDirect3DDevice9* vDevice, D3DPRESENT_PARAMETERS* Params);
HRESULT STDMETHODCALLTYPE	end_scene_hooked(IDirect3DDevice9* vDevice);
LRESULT STDMETHODCALLTYPE	wnd_proc_hooked(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void __stdcall				create_move(int sequence_number, float input_sample_frametime, bool active);
bool __fastcall				write_usercmd_delta_to_buffer(void* ecx, void* edx, void* buf, int from, int to, bool isnewcommand);
void __fastcall				frame_stage_notify(void* thisptr, void*, ClientFrameStage_t curStage);
CUserCmd* __fastcall		get_user_cmd(void* thisptr, void*, int sequence_number);
void __fastcall				paint(void* thisptr, void*, PaintMode_t mode);
void __fastcall hkLockCursor(ISurface* pThis, void*);
void __fastcall Hooked_PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
int __fastcall send_data_gram_hook(CNetChan* netchan, void* edx, bf_write* datagram);
float __stdcall Hooked_ViewmodelFOV();

extern bool PressedKeys[256];
extern bool was_initialized;
extern WNDPROC pOldWindowProc;
extern HWND hWindow;

extern void initialize_hooks();
extern void uninitialize_hooks();

class trace_pos_info
{
public:
	trace_pos_info(Vector positions)
	{
		this->position = positions;
	}

	Vector position;
};

extern std::vector<trace_pos_info> trace_pos;