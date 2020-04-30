#include "hooks.h"
//#include "../tools/curs.h"
#include "../Menu.h"

bool PressedKeys[256]{ false };
bool was_initialized = false;
WNDPROC pOldWindowProc = nullptr;
HWND hWindow = nullptr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
static bool che;
LRESULT STDMETHODCALLTYPE wnd_proc_hooked(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		PressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		PressedKeys[wParam] = false;
		break;
	default: break;
	}

	{
		static bool isDown = false;
		static bool isClicked = false;
		if (PressedKeys[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}
		else if (!PressedKeys[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}

		if (isClicked) 
		{
			Cvars.MenuOpened = !Cvars.MenuOpened;

			*(int*)((DWORD)GetModuleHandleA("vguimatsurface.dll") + 0x139CC0) = !Cvars.MenuOpened;
		}
		
	}

	if (Cvars.MenuOpened && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(pOldWindowProc, hWnd, uMsg, wParam, lParam);
}