#include "hooks.h"
#include "../ImGui/imgui_impl_dx9.h"

HRESULT STDMETHODCALLTYPE reset_hooked(IDirect3DDevice9* vDevice, D3DPRESENT_PARAMETERS* Params)
{
	if (!was_initialized)
		return o_reset(vDevice, Params);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto ret = o_reset(vDevice, Params);

	ImGui_ImplDX9_CreateDeviceObjects();

	return ret;
}
