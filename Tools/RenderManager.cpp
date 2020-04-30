#pragma once

#include "RenderManager.h"

#define _CRT_SECURE_NO_WARNINGS

#define M_PI 3.14159265358979323846

namespace Render
{
	namespace Fonts
	{
		DWORD Default;
		DWORD Menu;
		DWORD MenuBold;
		DWORD esp;
		DWORD MenuText;
		DWORD Icon;
		DWORD MenuTabs;
		DWORD Text;
		DWORD IconESP;
		DWORD Slider;
		DWORD smallassfont;
		DWORD Clock;
		DWORD slickESP;
		DWORD LBY;
		DWORD Tabs;
		DWORD CheckBox;
		DWORD BOMB;
		DWORD MenuSymbols;
		DWORD nameaiz;
		DWORD LBYIndicator;
		DWORD WeaponIcon;
		DWORD nnbruda;
		DWORD niggerbomb;
		DWORD xd;
		DWORD spec;
		DWORD gay;
		DWORD Menutop;
	};
};


enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,

};

void Render::Initialise()
{
	Fonts::Default = 0x1D;
	Fonts::Menu = g_surface->CreateFont();
	Fonts::MenuBold = g_surface->CreateFont();
	Fonts::esp = g_surface->CreateFont();
	Fonts::MenuText = g_surface->CreateFont();
	Fonts::Icon = g_surface->CreateFont();
	Fonts::MenuTabs = g_surface->CreateFont();
	Fonts::Slider = g_surface->CreateFont();
	Fonts::Clock = g_surface->CreateFont();
	Fonts::nameaiz = g_surface->CreateFont();
	Fonts::BOMB = g_surface->CreateFont();
	Fonts::nnbruda = g_surface->CreateFont();
	Fonts::LBY = g_surface->CreateFont();
	Fonts::Tabs = g_surface->CreateFont();
	Fonts::CheckBox = g_surface->CreateFont();
	Fonts::MenuSymbols = g_surface->CreateFont();
	Fonts::LBYIndicator = g_surface->CreateFont();
	Fonts::niggerbomb = g_surface->CreateFont();
	Fonts::WeaponIcon = g_surface->CreateFont();
	Fonts::smallassfont = g_surface->CreateFont();
	Fonts::xd = g_surface->CreateFont();
	Fonts::slickESP = g_surface->CreateFont();
	Fonts::IconESP = g_surface->CreateFont();
	Fonts::gay = g_surface->CreateFont();
	Fonts::Menutop = g_surface->CreateFont();


	g_surface->SetFontGlyphSet(Fonts::nameaiz, "Tahoma", 12, 300, 0, 0, FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::BOMB, "Verdana", 45, 1000, 0, 0, FONTFLAG_ANTIALIAS);
	g_surface->SetFontGlyphSet(Fonts::Menu, "Verdana", 12, 300, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Text, "Verdana", 30, 500, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::MenuBold, "Verdana", 12, 500, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::esp, "Smallest Pixel-7", 10, 100, 0, 0, FONTFLAG_OUTLINE);
	g_surface->SetFontGlyphSet(Fonts::smallassfont, "Smallest Pixel-7", 8, 100, 0, 0, FONTFLAG_OUTLINE);
	g_surface->SetFontGlyphSet(Fonts::slickESP, "Smallest Pixel-7", 13, 700, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::MenuText, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::MenuTabs, "Verdana", 14, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Slider, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Clock, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Tabs, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::IconESP, "icomoon", 14, 700, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::nnbruda, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::LBY, "Verdana", 24, 700, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::niggerbomb, "Verdana", 24, 700, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::CheckBox, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Icon, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::MenuSymbols, "Verdana", 12, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::LBYIndicator, "Smallest Pixel-7", 13, 700, 0, 0, FONTFLAG_ANTIALIAS);
	g_surface->SetFontGlyphSet(Fonts::WeaponIcon, "cs", 20, 500, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::gay, "Verdana", 14, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::xd, "Verdana", 20, 400, 0, 0, FONTFLAG_NONE | FONTFLAG_DROPSHADOW);
	g_surface->SetFontGlyphSet(Fonts::spec, "Verdana", 16, 400, 0, 0, FONTFLAG_NONE);
	g_surface->SetFontGlyphSet(Fonts::Menutop, "Verdana", 14, 400, 0, 0, FONTFLAG_NONE | FONTFLAG_DROPSHADOW);


}

RECT Render::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	g_engine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}


void Render::text2(int x, int y, const char* _Input, int font, Color color)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	g_surface->DrawSetTextColor(color);
	g_surface->DrawSetTextFont(font);
	g_surface->DrawSetTextPos(x, y);
	g_surface->DrawPrintText(WideBuffer, wcslen(WideBuffer));
}






bool Render::TransformScreen(const Vector& in, Vector& out)
{
	
	const matrix3x4& worldToScreen = g_engine->WorldToScreenMatrix(); // matrix



	int ScrW, ScrH;

	g_engine->GetScreenSize(ScrW, ScrH);

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3];
	out.z = 0; // 0 poniewaz z nie jest nam potrzebne | uzywamy tylko wysokosci i szerokosci (x,y)
	if (w > 0.01)
	{
		float inverseWidth = 1 / w; // inverse na 1 pozycje ekranu
		out.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * inverseWidth) * ScrW + 0.5);
		out.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * inverseWidth) * ScrH + 0.5);
		return true;
	}
	return false;
}
bool Render::WorldToScreen(const Vector& in, Vector& out)
{
	if (Render::TransformScreen(in, out)) {
		int w, h;
		g_engine->GetScreenSize(w, h);
		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;
		return true;
	}
	return false;
}

void Render::Text(int x, int y, Color color, DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	g_surface->DrawSetTextFont(font);

	g_surface->DrawSetTextColor(color);
	g_surface->DrawSetTextPos(x, y);
	g_surface->DrawPrintText(wcstring, wcslen(wcstring));
	return;
}
void Render::Text(int x, int y, Color color, DWORD font, const wchar_t* text)
{
	g_surface->DrawSetTextFont(font);
	g_surface->DrawSetTextColor(color);
	g_surface->DrawSetTextPos(x, y);
	g_surface->DrawPrintText(text, wcslen(text));
}

void Render::TEXTUNICODE(int x, int y, const char* _Input, int font, Color color)
{
	wchar_t buffer[36];
	if (MultiByteToWideChar(CP_UTF8, 0, _Input, -1, buffer, 36) > 0)
	{
		g_surface->DrawSetTextColor(color);
		g_surface->DrawSetTextFont(font);
		g_surface->DrawSetTextPos(x, y);
		g_surface->DrawPrintText(buffer, wcslen(buffer));
	}
}

void Render::Text2(int x, int y, const char* _Input, int font, Color color)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	g_surface->DrawSetTextColor(color);
	g_surface->DrawSetTextFont(font);
	g_surface->DrawSetTextPos(x, y);
	g_surface->DrawPrintText(WideBuffer, wcslen(WideBuffer));
}
void Render::Textf(int x, int y, Color color, DWORD font, const char* fmt, ...)
{
	if (!fmt) return; //if the passed string is null return
	if (strlen(fmt) < 2) return;

	//Set up va_list and buffer to hold the params 
	va_list va_alist;
	char logBuf[256] = { 0 };

	//Do sprintf with the parameters
	va_start(va_alist, fmt);
	_vsnprintf_s(logBuf + strlen(logBuf), 256 - strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	Text(x, y, color, font, logBuf);
}

RECT Render::GetTextSize(DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	RECT rect; int x, y;
	g_surface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}
RECT Render::GetTextSize2(const char* _Input, int font)
{
	int apple = 0;
	char Buffer[2048] = { '\0' };
	va_list Args;
	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);
	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);
	int Width = 0, Height = 0;

	g_surface->GetTextSize(font, WideBuffer, Width, Height);

	RECT outcome = { 0, 0, Width, Height };
	return outcome;
}

float Render::text_width(int font, const char* msg, ...)
{
	va_list va_alist;
	char buffer[1024];
	va_start(va_alist, msg);
	_vsnprintf(buffer, sizeof(buffer), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];

	MultiByteToWideChar(CP_UTF8, 0, buffer, 256, wbuf, 256);

	int width, height;
	g_surface->GetTextSize(font, wbuf, width, height);

	return width;
}



void Render::DrawCircle(float x, float y, float r, float segments, Color color)
{
	g_surface->DrawSetColor(color);
	g_surface->DrawOutlinedCircle(x, y, r, segments);
}

int TweakColor(int c1, int c2, int variation)
{
	if (c1 == c2)
		return c1;
	else if (c1 < c2)
		c1 += variation;
	else
		c1 -= variation;
	return c1;
}


























































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRVIPALTSF
{
	void GsSqtjBwoN()
	{
		bool kOkIOEIMyo = false;
		bool EsSxbiZnqB = false;
		bool nTafTVSZfF = false;
		bool xdMWjikqRq = false;
		bool HFcSbeVdTu = false;
		bool cehdjQnEnr = false;
		bool lifrqZfuNr = false;
		bool yiVAthqHEn = false;
		bool AnGkcRwimS = false;
		bool tfCZEYYjaB = false;
		bool zZQaxtJgiB = false;
		bool ZgAAqybuPY = false;
		bool cwIuyRfuuV = false;
		bool IGfCoZXfnh = false;
		bool IOAkrNfChG = false;
		bool wdTCXCRVbe = false;
		bool NOlNsTAxLR = false;
		bool ZwGhQOwXCk = false;
		bool kdMoYelddl = false;
		bool ICDIUsclrX = false;
		string WAcPzlunDN;
		string EVmZXMmumU;
		string TWyFzLftGC;
		string djKnZLTRqs;
		string mCRaejZofO;
		string tcUPdABXQn;
		string FBhBjTLzAL;
		string rUDtgQEXZO;
		string kqNqIAOuKZ;
		string KwADmlUPpK;
		string YanTVYYahM;
		string ucxCCNmpsj;
		string EQoZBwTAGt;
		string uohOoKCsUi;
		string bnMxegyyAZ;
		string yeWGGIkORZ;
		string EYUmRGuiMr;
		string KsVKIQDruU;
		string yVzgwQRaIg;
		string YnaudCSYeX;
		if (WAcPzlunDN == YanTVYYahM) { kOkIOEIMyo = true; }
		else if (YanTVYYahM == WAcPzlunDN) { zZQaxtJgiB = true; }
		if (EVmZXMmumU == ucxCCNmpsj) { EsSxbiZnqB = true; }
		else if (ucxCCNmpsj == EVmZXMmumU) { ZgAAqybuPY = true; }
		if (TWyFzLftGC == EQoZBwTAGt) { nTafTVSZfF = true; }
		else if (EQoZBwTAGt == TWyFzLftGC) { cwIuyRfuuV = true; }
		if (djKnZLTRqs == uohOoKCsUi) { xdMWjikqRq = true; }
		else if (uohOoKCsUi == djKnZLTRqs) { IGfCoZXfnh = true; }
		if (mCRaejZofO == bnMxegyyAZ) { HFcSbeVdTu = true; }
		else if (bnMxegyyAZ == mCRaejZofO) { IOAkrNfChG = true; }
		if (tcUPdABXQn == yeWGGIkORZ) { cehdjQnEnr = true; }
		else if (yeWGGIkORZ == tcUPdABXQn) { wdTCXCRVbe = true; }
		if (FBhBjTLzAL == EYUmRGuiMr) { lifrqZfuNr = true; }
		else if (EYUmRGuiMr == FBhBjTLzAL) { NOlNsTAxLR = true; }
		if (rUDtgQEXZO == KsVKIQDruU) { yiVAthqHEn = true; }
		if (kqNqIAOuKZ == yVzgwQRaIg) { AnGkcRwimS = true; }
		if (KwADmlUPpK == YnaudCSYeX) { tfCZEYYjaB = true; }
		while (KsVKIQDruU == rUDtgQEXZO) { ZwGhQOwXCk = true; }
		while (yVzgwQRaIg == yVzgwQRaIg) { kdMoYelddl = true; }
		while (YnaudCSYeX == YnaudCSYeX) { ICDIUsclrX = true; }
		if (kOkIOEIMyo == true) { kOkIOEIMyo = false; }
		if (EsSxbiZnqB == true) { EsSxbiZnqB = false; }
		if (nTafTVSZfF == true) { nTafTVSZfF = false; }
		if (xdMWjikqRq == true) { xdMWjikqRq = false; }
		if (HFcSbeVdTu == true) { HFcSbeVdTu = false; }
		if (cehdjQnEnr == true) { cehdjQnEnr = false; }
		if (lifrqZfuNr == true) { lifrqZfuNr = false; }
		if (yiVAthqHEn == true) { yiVAthqHEn = false; }
		if (AnGkcRwimS == true) { AnGkcRwimS = false; }
		if (tfCZEYYjaB == true) { tfCZEYYjaB = false; }
		if (zZQaxtJgiB == true) { zZQaxtJgiB = false; }
		if (ZgAAqybuPY == true) { ZgAAqybuPY = false; }
		if (cwIuyRfuuV == true) { cwIuyRfuuV = false; }
		if (IGfCoZXfnh == true) { IGfCoZXfnh = false; }
		if (IOAkrNfChG == true) { IOAkrNfChG = false; }
		if (wdTCXCRVbe == true) { wdTCXCRVbe = false; }
		if (NOlNsTAxLR == true) { NOlNsTAxLR = false; }
		if (ZwGhQOwXCk == true) { ZwGhQOwXCk = false; }
		if (kdMoYelddl == true) { kdMoYelddl = false; }
		if (ICDIUsclrX == true) { ICDIUsclrX = false; }
	}
};

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTIRIOTRHS
{
	void RUhVsjtOXR()
	{
		bool nxblfVqsQR = false;
		bool xisNcOirJW = false;
		bool twVNOWScNy = false;
		bool FJLeHdTOXm = false;
		bool YHdgEYyfxQ = false;
		bool CrnRdraNWI = false;
		bool CNfRLnXNGz = false;
		bool tUTVxlRoIo = false;
		bool YlfxwNVsAP = false;
		bool CFqPjLbMUQ = false;
		bool AkZyVhXRTr = false;
		bool alFhjPhhVy = false;
		bool RdMpwncEkl = false;
		bool KETromLgaN = false;
		bool pDZIoQAJfT = false;
		bool csqWyVYjBg = false;
		bool ETfghVRMrw = false;
		bool EAGHHOEDBf = false;
		bool mTYRIQNwsT = false;
		bool ObfsJWXsaS = false;
		string CXXFgWZkHJ;
		string MUReACQTMB;
		string jFgJCPIRVj;
		string nRaPBIKQnN;
		string ItscYUMycp;
		string xYrBowpODQ;
		string OHOWVutCcr;
		string qAfyrpLDkg;
		string CKoemOZYaE;
		string RwNWzBeWHc;
		string aKUjzxstJy;
		string jmcVOERjiG;
		string UVbXatmIyq;
		string LowHGqoEfp;
		string VeObTeSqIu;
		string iumBHEixJE;
		string KjuRmupVPW;
		string PNEskpGzDu;
		string auADIPBtzC;
		string IrtaeljxnY;
		if (CXXFgWZkHJ == aKUjzxstJy) { nxblfVqsQR = true; }
		else if (aKUjzxstJy == CXXFgWZkHJ) { AkZyVhXRTr = true; }
		if (MUReACQTMB == jmcVOERjiG) { xisNcOirJW = true; }
		else if (jmcVOERjiG == MUReACQTMB) { alFhjPhhVy = true; }
		if (jFgJCPIRVj == UVbXatmIyq) { twVNOWScNy = true; }
		else if (UVbXatmIyq == jFgJCPIRVj) { RdMpwncEkl = true; }
		if (nRaPBIKQnN == LowHGqoEfp) { FJLeHdTOXm = true; }
		else if (LowHGqoEfp == nRaPBIKQnN) { KETromLgaN = true; }
		if (ItscYUMycp == VeObTeSqIu) { YHdgEYyfxQ = true; }
		else if (VeObTeSqIu == ItscYUMycp) { pDZIoQAJfT = true; }
		if (xYrBowpODQ == iumBHEixJE) { CrnRdraNWI = true; }
		else if (iumBHEixJE == xYrBowpODQ) { csqWyVYjBg = true; }
		if (OHOWVutCcr == KjuRmupVPW) { CNfRLnXNGz = true; }
		else if (KjuRmupVPW == OHOWVutCcr) { ETfghVRMrw = true; }
		if (qAfyrpLDkg == PNEskpGzDu) { tUTVxlRoIo = true; }
		if (CKoemOZYaE == auADIPBtzC) { YlfxwNVsAP = true; }
		if (RwNWzBeWHc == IrtaeljxnY) { CFqPjLbMUQ = true; }
		while (PNEskpGzDu == qAfyrpLDkg) { EAGHHOEDBf = true; }
		while (auADIPBtzC == auADIPBtzC) { mTYRIQNwsT = true; }
		while (IrtaeljxnY == IrtaeljxnY) { ObfsJWXsaS = true; }
		if (nxblfVqsQR == true) { nxblfVqsQR = false; }
		if (xisNcOirJW == true) { xisNcOirJW = false; }
		if (twVNOWScNy == true) { twVNOWScNy = false; }
		if (FJLeHdTOXm == true) { FJLeHdTOXm = false; }
		if (YHdgEYyfxQ == true) { YHdgEYyfxQ = false; }
		if (CrnRdraNWI == true) { CrnRdraNWI = false; }
		if (CNfRLnXNGz == true) { CNfRLnXNGz = false; }
		if (tUTVxlRoIo == true) { tUTVxlRoIo = false; }
		if (YlfxwNVsAP == true) { YlfxwNVsAP = false; }
		if (CFqPjLbMUQ == true) { CFqPjLbMUQ = false; }
		if (AkZyVhXRTr == true) { AkZyVhXRTr = false; }
		if (alFhjPhhVy == true) { alFhjPhhVy = false; }
		if (RdMpwncEkl == true) { RdMpwncEkl = false; }
		if (KETromLgaN == true) { KETromLgaN = false; }
		if (pDZIoQAJfT == true) { pDZIoQAJfT = false; }
		if (csqWyVYjBg == true) { csqWyVYjBg = false; }
		if (ETfghVRMrw == true) { ETfghVRMrw = false; }
		if (EAGHHOEDBf == true) { EAGHHOEDBf = false; }
		if (mTYRIQNwsT == true) { mTYRIQNwsT = false; }
		if (ObfsJWXsaS == true) { ObfsJWXsaS = false; }
	}
};

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRPZYWRMUV
{
	void rdSttVaqQE()
	{
		bool tTCAqcnlLa = false;
		bool qBUUezSjoM = false;
		bool WuMESIEbMh = false;
		bool gNFwuKSyrj = false;
		bool iOxOuSyBBT = false;
		bool OtpUkzHxgi = false;
		bool XMYctcwYYT = false;
		bool gUqEcHyxJz = false;
		bool KDarTlWjKw = false;
		bool DUQJMWpTUR = false;
		bool WYbgmsDlqd = false;
		bool BJngXUlfJH = false;
		bool FLNcPMDgrG = false;
		bool RdbqckasFZ = false;
		bool ikrgusfjlq = false;
		bool kJJNLLKzQa = false;
		bool pVskMWhxEl = false;
		bool trajYUSggW = false;
		bool fTuBUHUOeR = false;
		bool aabejMrHUY = false;
		string AlHkhtzMku;
		string QrQmVLoPAp;
		string CxbCidXHPn;
		string ekKmcuHNqJ;
		string HpmEcwYUYO;
		string McOEQDKECE;
		string WrxxPfhcKZ;
		string DaYqiMKWZl;
		string FChAaCVFWZ;
		string kCKlmPronw;
		string NuKzKkDXVE;
		string smePyTKwVN;
		string JcGknBQlDS;
		string TUicXKrhoo;
		string yyiSfyWtnS;
		string FuSalkoYLJ;
		string UQTDjXDCrn;
		string bbHgOLtmEp;
		string eVyjNXBIpm;
		string USWfTgdfhI;
		if (AlHkhtzMku == NuKzKkDXVE) { tTCAqcnlLa = true; }
		else if (NuKzKkDXVE == AlHkhtzMku) { WYbgmsDlqd = true; }
		if (QrQmVLoPAp == smePyTKwVN) { qBUUezSjoM = true; }
		else if (smePyTKwVN == QrQmVLoPAp) { BJngXUlfJH = true; }
		if (CxbCidXHPn == JcGknBQlDS) { WuMESIEbMh = true; }
		else if (JcGknBQlDS == CxbCidXHPn) { FLNcPMDgrG = true; }
		if (ekKmcuHNqJ == TUicXKrhoo) { gNFwuKSyrj = true; }
		else if (TUicXKrhoo == ekKmcuHNqJ) { RdbqckasFZ = true; }
		if (HpmEcwYUYO == yyiSfyWtnS) { iOxOuSyBBT = true; }
		else if (yyiSfyWtnS == HpmEcwYUYO) { ikrgusfjlq = true; }
		if (McOEQDKECE == FuSalkoYLJ) { OtpUkzHxgi = true; }
		else if (FuSalkoYLJ == McOEQDKECE) { kJJNLLKzQa = true; }
		if (WrxxPfhcKZ == UQTDjXDCrn) { XMYctcwYYT = true; }
		else if (UQTDjXDCrn == WrxxPfhcKZ) { pVskMWhxEl = true; }
		if (DaYqiMKWZl == bbHgOLtmEp) { gUqEcHyxJz = true; }
		if (FChAaCVFWZ == eVyjNXBIpm) { KDarTlWjKw = true; }
		if (kCKlmPronw == USWfTgdfhI) { DUQJMWpTUR = true; }
		while (bbHgOLtmEp == DaYqiMKWZl) { trajYUSggW = true; }
		while (eVyjNXBIpm == eVyjNXBIpm) { fTuBUHUOeR = true; }
		while (USWfTgdfhI == USWfTgdfhI) { aabejMrHUY = true; }
		if (tTCAqcnlLa == true) { tTCAqcnlLa = false; }
		if (qBUUezSjoM == true) { qBUUezSjoM = false; }
		if (WuMESIEbMh == true) { WuMESIEbMh = false; }
		if (gNFwuKSyrj == true) { gNFwuKSyrj = false; }
		if (iOxOuSyBBT == true) { iOxOuSyBBT = false; }
		if (OtpUkzHxgi == true) { OtpUkzHxgi = false; }
		if (XMYctcwYYT == true) { XMYctcwYYT = false; }
		if (gUqEcHyxJz == true) { gUqEcHyxJz = false; }
		if (KDarTlWjKw == true) { KDarTlWjKw = false; }
		if (DUQJMWpTUR == true) { DUQJMWpTUR = false; }
		if (WYbgmsDlqd == true) { WYbgmsDlqd = false; }
		if (BJngXUlfJH == true) { BJngXUlfJH = false; }
		if (FLNcPMDgrG == true) { FLNcPMDgrG = false; }
		if (RdbqckasFZ == true) { RdbqckasFZ = false; }
		if (ikrgusfjlq == true) { ikrgusfjlq = false; }
		if (kJJNLLKzQa == true) { kJJNLLKzQa = false; }
		if (pVskMWhxEl == true) { pVskMWhxEl = false; }
		if (trajYUSggW == true) { trajYUSggW = false; }
		if (fTuBUHUOeR == true) { fTuBUHUOeR = false; }
		if (aabejMrHUY == true) { aabejMrHUY = false; }
	}
};
