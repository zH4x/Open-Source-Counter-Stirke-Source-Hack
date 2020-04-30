#include "hooks.h"
#include "../hacks/visuals.h"
#include "../Menu.h"
#include "../options.h"
#include "../Hacks/FakeLatency.h"




void __fastcall frame_stage_notify(void* thisptr, void*, ClientFrameStage_t curStage)
{
	

	if (curStage == FRAME_RENDER_START)
	{
		static Vector qOldPunch;
		auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
		if (local_player && Options.Visuals.NoVisualRecoil)
		{
			if (!local_player->IsDormant())
			{

				local_player->get_flash_max_alpha() = Options.Visuals.bNoFlash ? 0.f : 255.f;

				qOldPunch = local_player->get_aim_punch();
				local_player->get_aim_punch().Init();

				o_frame_stage_notify(thisptr, curStage);

				local_player->get_aim_punch() = qOldPunch;
			}
		}
		else 
			o_frame_stage_notify(thisptr, curStage);
	}

	//o_frame_stage_notify(thisptr, curStage);

}