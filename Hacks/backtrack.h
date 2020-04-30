#pragma once

#include <deque>
#include "../Interfaces.h"
#include "../hooks/hooks.h"

struct EntityData
{
	Vector headPos;
	float simulationTime;
	Vector origin;
	QAngle angs;
	bool isTickValid;
};

class LegitBacktrack
{
public:
	void Run(CUserCmd* cmd);

	std::deque<EntityData> entData[64];
private:
	bool CheckValidTick(int tick, EntityData data, bool fakeLatency);
	void SetInvalidTicks(C_CSPlayer* ent, std::deque<EntityData>& data, bool fakeLatency);
	void UpdateEntityData(C_CSPlayer* ent, bool fakeLatency);
	C_CSPlayer* GetClosestEntity(C_CSPlayer* pLocal, CUserCmd* cmd);
	void BacktrackEntity(C_CSPlayer* ent, CUserCmd* cmd);
}; extern LegitBacktrack f_LegitBacktrack;