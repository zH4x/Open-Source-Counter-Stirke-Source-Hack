#pragma once

#include "../tools/entity.h"
#include "../SDK/CBaseEntity.h"
#include <vector>



class cmisc
{
public:
	void move(CUserCmd* cmd);
	void FakeLowLatency();
	void engine_prediction(C_BasePlayer * player, CUserCmd * cmd);
	void FPS();
};

class NoFall
{
	//Hooks
public:
	void PrePredictionCreateMove(CUserCmd* cmd);
	void PostPredictionCreateMove(CUserCmd* cmd);
};

class AutoStrafe
{
public:

	void Run(CUserCmd* cmd);
};

namespace knife_bot
{
	void handle(CUserCmd* cmd, bool& send_packet);
}
namespace features
{
	void fastStop(CUserCmd* cmd);
}
void Ladder(CUserCmd* cmd);
void DrawKzKeys();
void Kz(CUserCmd* cmd);
void FastRun(CUserCmd* cmd);
void Walkbot(Vector& OrigAng, CUserCmd* cmd);
void SetShadows();
void DrawCrossHair();
void CrossHair();
void AutoPistol(CUserCmd* cmd);
void bhop(CUserCmd* cmd);
void BacktrackHitBoxes();

extern AutoStrafe gStrafe;
extern NoFall gFall;
extern cmisc* misc;