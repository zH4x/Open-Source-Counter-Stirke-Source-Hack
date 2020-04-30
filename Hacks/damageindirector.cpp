#include "damageindirector.h"
#include "../tools/RenderManager.h"
#include "../tools/UTIL Functions.h"


DamageIndicators damage_indicators;

void DamageIndicators::paint() {
	auto local = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));

	float current_time = local->get_tick_base() * g_globals->interval_per_tick;

	for (int i = 0; i < data.size(); i++) {
		if (data[i].flEraseTime < current_time) {
			data.erase(data.begin() + i);
			continue;
		}

		if (!data[i].bInitialized) {
			data[i].Position = data[i].Player->GetHitboxPosition(12);
			data[i].bInitialized = true;
		}

		if (current_time - data[i].flLastUpdate > 0.0001f) {
			data[i].Position.z -= (0.1f * (current_time - data[i].flEraseTime));
			data[i].flLastUpdate = current_time;
		}

		Vector screen_pos;

		if (GameUtils::World2Screen(data[i].Position, screen_pos)) {
			Render::text2(screen_pos.x, screen_pos.y, std::to_string(data[i].iDamage).c_str(), Render::Fonts::Menutop, Color(255, 0, 0, 255));
		}


	}
}