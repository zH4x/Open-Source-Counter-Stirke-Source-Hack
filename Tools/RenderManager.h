#pragma once

#include "../Interfaces.h"
#include <vector>

void Quad();

enum FontCenteringFlags {
	HFONT_CENTERED_NONE = (1 << 0),
	HFONT_CENTERED_X = (1 << 1),
	HFONT_CENTERED_Y = (1 << 2),
	HFONT_OFF_SCREEN,
};


namespace Render
{
	void Initialise();

	
	void text2(int x, int y, const char* _Input, int font, Color color);
	
	void GradientV(int x, int y, int w, int h, Color c1, Color c2);
	void DrawCircle(float x, float y, float r, float segments, Color color);

	namespace Fonts
	{
		extern DWORD Default;
		extern DWORD Menu;
		extern DWORD MenuBold;
		extern DWORD esp;
		extern DWORD MenuText;
		extern DWORD Icon;
		extern DWORD MenuTabs;
		extern DWORD smallassfont;
		extern DWORD spec;
		extern DWORD Text;
		extern DWORD nameaiz;
		extern DWORD Slider;
		extern DWORD Clock;
		extern DWORD LBY;
		extern DWORD Menutop;
		extern DWORD xd;
		extern DWORD nnbruda;
		extern DWORD Tabs;
		extern DWORD niggerbomb;
		extern DWORD BOMB;
		extern DWORD CheckBox;
		extern DWORD IconESP;
		extern DWORD slickESP;
		extern DWORD MenuSymbols;
		extern DWORD LBYIndicator;
		extern DWORD WeaponIcon;
		extern DWORD gay;
	};

	void Text(int x, int y, Color color, DWORD font, const char* text);
	void Text2(int x, int y, const char* _Input, int font, Color color);
	void Textf(int x, int y, Color color, DWORD font, const char* fmt, ...);
	void Text(int x, int y, Color color, DWORD font, const wchar_t* text);
	void TEXTUNICODE(int x, int y, const char* _Input, int font, Color color);
	float text_width(int font, const char* msg, ...);
	RECT GetTextSize(DWORD font, const char* text);

	RECT GetTextSize2(const char* _Input, int font);

	bool TransformScreen(const Vector& in, Vector& out);

	bool WorldToScreen(const Vector& in, Vector& out);

	RECT GetViewport();
};

