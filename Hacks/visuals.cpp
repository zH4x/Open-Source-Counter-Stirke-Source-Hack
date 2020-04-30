#include "visuals.h"
#include "../tools/math.h"
#include <vector>
#include "misc.h"
#include "../options.h"
#include "../tools/UTIL Functions.h"
#include "backtrack.h"

cvisuals_2* visuals = new cvisuals_2();

void render_text(int x, int y, Color color, HFont font, const wchar_t * text)
{
	g_surface->DrawSetTextPos(x, y);
	g_surface->DrawSetTextFont(font);
	g_surface->DrawSetTextColor(color);
	g_surface->DrawPrintText(text, wcslen(text));
}

const char* WeaponIDToAlias(int id)
{
	static auto function = reinterpret_cast<const char*(*)(int)>(
		tools::get_rel32(tools::find_pattern("client.dll", "E8 ? ? ? ? 50 FF 75 94"), 1, 5));
	return function(id);
}

void cvisuals_2::initialize()
{
	courier_new = g_surface->CreateFont();
	g_surface->SetFontGlyphSet(courier_new, "Courier New", 40, 20, 1, 0, ISurface::FONTFLAG_OUTLINE);

	initialized = true;
}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}


void cvisuals_2::render()
{

	render_esp();
	render_spread_circle();
	auto local = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local || local->IsDormant())
		return;
	if (Options.Misc.BackTrack && (Options.Visuals.BacktrackDots || Options.Visuals.BacktrackVisuals))
	{

		for (size_t i = 0; i < g_engine->GetMaxClients(); i++)
		{
			auto pEntity = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));
			if (!pEntity || pEntity->IsDormant() || pEntity->get_health() < 1 || pEntity->get_team_num() == local->get_team_num())
				continue;
			if (!local->IsDormant() && (Options.Visuals.BacktrackDots || Options.Visuals.BacktrackVisuals)) {
				if (!f_LegitBacktrack.entData[pEntity->GetIndex()].empty()) {
					//return;

					if (Options.Visuals.BacktrackDots)
					{
						for (unsigned int t = 0; t < f_LegitBacktrack.entData[pEntity->GetIndex()].size(); t++)
						{
							Vector hitbox = f_LegitBacktrack.entData[pEntity->GetIndex()].at(t).headPos, screen;
							if (GameUtils::World2Screen(hitbox, screen))
							{
								g_surface->DrawSetColor(Color(255, 255, 255, 255));
								g_surface->DrawOutlinedRect(screen[0], screen[1], screen[0] + 2, screen[1] + 2);
							}
						}
					}
					if (Options.Visuals.BacktrackVisuals)
					{
						for (unsigned int t = 0; t < f_LegitBacktrack.entData[pEntity->GetIndex()].size(); t++) {
							Vector hitbox = f_LegitBacktrack.entData[pEntity->GetIndex()].at(t).headPos, screen;
							if (GameUtils::World2Screen(hitbox, screen)) {
								g_surface->DrawSetColor(Color(255, 0, 0, 200));
								g_surface->DrawLine(screen[0] - 8, screen[1] - 0, screen[0] + 8, screen[1] + 0);
								g_surface->DrawLine(screen[0] + 0, screen[1] - 8, screen[0] - 0, screen[1] + 8);
								g_surface->DrawSetColor(Color(255, 255, 255, 255));
								g_surface->DrawLine(screen[0] - 4, screen[1] - 0, screen[0] + 4, screen[1] + 0);
								g_surface->DrawLine(screen[0] + 0, screen[1] - 4, screen[0] - 0, screen[1] + 4);
							}
						}
					}
				}
			}
		}
	}

	if (Options.Visuals.ShowVelocity)
	{
		auto Velocity = local->m_vecVelocity();
		float flSpeed = sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);

		char buffer[64];
		char ret = snprintf(buffer, sizeof buffer, "%i", (int)flSpeed);


		int w, h;
		auto lineSize = 8;
		int screenSizeX, screenCenterX;
		int screenSizeY, screenCenterY;
		g_surface->GetScreenSize(screenSizeX, screenSizeY);

		screenCenterX = screenSizeX / 2;
		screenCenterY = screenSizeY / 2;
		g_surface->GetTextSize(courier_new, GetWC(buffer), w, h);
		if (flSpeed < 10)
		{
			render_text(screenCenterX - 12, screenCenterY - 320,
				Color(255, 255, 255, 255), courier_new, GetWC(buffer));
		}
		else
			render_text(screenCenterX - 25, screenCenterY - 320,
				Color(255, 255, 255, 255), courier_new, GetWC(buffer));
		
	}

}




void cvisuals_2::render_esp()
{
	auto local = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local)
		return;

	for (auto i = 0; i < g_entitylist->GetHighestEntityIndex(); i++)
	{
		auto entity = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));
		if (!entity || entity->IsDormant())
			continue;

		auto client_class = entity->GetClientClass();
		if (!client_class)
			continue;

		if (client_class->m_ClassID == CCSPlayer)
			render_player(entity);
	}
}

void cvisuals_2::render_player(C_CSPlayer* player)
{
	auto local = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (player->get_life_state() == 1
		|| player->get_team_num() == local->get_team_num()
		|| player == local)
		return;
	

	auto weapon = player->GetActiveWeapon();
	if (!weapon)
		return;

	auto weapondata = weapon->GetWpnData();
	if (!weapondata)
		return;

	int screen_width, screen_height;
	g_engine->GetScreenSize(screen_width, screen_height);

	rect_s rect{};
	if (get_bounding_box(player, rect))
	{
		if (Options.Visuals.bBox)
		{
			g_surface->DrawSetColor(get_player_color(player));
			g_surface->DrawOutlinedRect(rect.left, rect.top, rect.right, rect.bottom);
		}

		if (Options.Visuals.bHealthbar)
		{
			g_surface->DrawSetColor(get_health_color(player->get_health()));
			g_surface->DrawOutlinedRect(rect.left, rect.bottom + 2,
				rect.left + (rect.right - rect.left) / 100.f * player->get_health(), rect.bottom + 2);
		}

		if (Options.Visuals.visuals_snapline)
		{
			g_surface->DrawSetColor(255, 255, 255, 255);
			g_surface->DrawLine(screen_width / 2.f, screen_height, rect.left + (rect.right - rect.left) / 2.f, rect.bottom);
		}

	}
}

void cvisuals_2::render_spread_circle()
{
	if (!Options.Visuals.visuals_spread_circle)
		return;

	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player)
		return;

	auto weapon = local_player->GetActiveWeapon();
	if (!weapon)
		return;

	const auto accuracy = weapon->GetInaccuracy() * 550.f; //3000

	int screen_w, screen_h;
	g_surface->GetScreenSize(screen_w, screen_h);

	g_surface->DrawSetColor(255, 0, 0, 255);
	g_surface->DrawOutlinedCircle(screen_w / 2, screen_h / 2, accuracy, 360);
}

Color cvisuals_2::get_player_color(C_CSPlayer* pEntity)
{
	
	if (pEntity->get_team_num() == 2)
		return entity::is_visible(pEntity, 12) ? Color(Options.Visuals.rEspVisable_t, Options.Visuals.gEspVisable_t, Options.Visuals.bEspVisable_t, 255) : Color(Options.Visuals.rEsp_t, Options.Visuals.gEsp_t, Options.Visuals.bEsp_t, 255);
	if (pEntity->get_team_num() == 3)
		return entity::is_visible(pEntity, 12) ? Color(Options.Visuals.rEspVisable_ct, Options.Visuals.gEspVisable_ct, Options.Visuals.bEspVisable_ct, 255) : Color(Options.Visuals.rEsp, Options.Visuals.gEsp, Options.Visuals.bEsp, 255);
	return Color();
}

Color cvisuals_2::get_health_color(int health)
{
	health = max(0, min(health, 100));

	return Color(min((510 * (100 - health)) / 100, 255), min((510 * health) / 100, 255), 0, 255);
}

bool cvisuals_2::get_bounding_box(C_BasePlayer* entity, rect_s& rect)
{
	matrix3x4_t trans;
	math::AngleMatrix(entity->GetRenderAngles(), entity->GetRenderOrigin(), trans);

	Vector min, max;
	entity->GetRenderBounds(min, max);

	Vector points[8]
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	for (auto& point : points)
	{
		Vector point_transformed;
		math::VectorTransform(point, trans, point_transformed);
		if (g_debugoverlay->ScreenPosition(point_transformed, point))
			return false;
	}

	auto left = points[0].x;
	auto top = points[0].y;
	auto right = points[0].x;
	auto bottom = points[0].y;

	for (auto i = 0; i < 8; i++)
	{
		if (left > points[i].x)
			left = points[i].x;
		if (bottom < points[i].y)
			bottom = points[i].y;
		if (right < points[i].x)
			right = points[i].x;
		if (top > points[i].y)
			top = points[i].y;
	}

	rect = { left, top, right, bottom };

	return true;
}



