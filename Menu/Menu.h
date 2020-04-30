#pragma once
#include <d3dx9.h>


class cmenu
{
public:

	void render(IDirect3DDevice9* vDevice);

private:
	enum class tabs_e
	{
		Aimbot,
		Visuals,
		Misc,
		ConVars,
		Configs,
		Players
	};

	void misc_tab();
	void aimbot_tab();

	tabs_e m_tab_selected = tabs_e::Aimbot;
};
class CVars
{
public:
	bool Aimbot;
	const char* windowName = "Counter-Strike Source";
	bool MenuOpened;
	bool visuals_triggerbot_hitbox;
};
#ifdef _WIN32
#pragma once
#endif
//void HudKeyBind(float& key, char* keyname, bool menukey);

extern CVars Cvars;
extern cmenu* menu;