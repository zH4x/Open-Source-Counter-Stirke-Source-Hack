#include "Backtrack.h"
#include "../SDK/ICVar.h"
#include "../options.h"
#include "../tools/math.h"


Vector AngleVector(Vector vec)
{
	auto sy = sin(vec.y / 180.f * static_cast<float>(PI));
	auto cy = cos(vec.y / 180.f * static_cast<float>(PI));

	auto sp = sin(vec.x / 180.f * static_cast<float>(PI));
	auto cp = cos(vec.x / 180.f * static_cast<float>(PI));

	return Vector(cp * cy, cp * sy, -sp);
}

float clamp(float val, float minVal, float maxVal)
{
	if (maxVal < minVal)
		return maxVal;
	else if (val < minVal)
		return minVal;
	else if (val > maxVal)
		return maxVal;
	else
		return val;
}

float TicksToTime(int tick)
{
	return g_globals->interval_per_tick * tick;
}

int TimeToTicks(float deltaTime)
{
	return ((int)0.5f + deltaTime / g_globals->interval_per_tick);
}

ConVar* minupdate;
ConVar* maxupdate;
ConVar* updaterate;
ConVar* interprate;
ConVar* cmin;
ConVar* cmax;
ConVar* interp;

float GetLerpTime()
{
	if (!minupdate)
		minupdate = g_cvar->FindVar(("sv_minupdaterate"));
	if (!maxupdate)
		maxupdate = g_cvar->FindVar(("sv_maxupdaterate"));
	if (!updaterate)
		updaterate = g_cvar->FindVar(("cl_updaterate"));
	if (!interprate)
		interprate = g_cvar->FindVar(("cl_interp_ratio"));
	if (!cmin)
		cmin = g_cvar->FindVar(("sv_client_min_interp_ratio"));
	if (!cmax)
		cmax = g_cvar->FindVar(("sv_client_max_interp_ratio"));
	if (!interp)
		interp = g_cvar->FindVar(("cl_interp"));

	auto updateRate = updaterate->GetInt();
	auto interpRatio = static_cast<float>(interprate->GetInt());
	auto minInterpRatio = cmin->GetFloat();
	auto maxInterpRatio = cmax->GetFloat();
	auto minUpdateRate = static_cast<float>(minupdate->GetInt());
	auto maxUpdateRate = static_cast<float>(maxupdate->GetInt());

	auto clampedUpdateRate = clamp(updateRate, minUpdateRate, maxUpdateRate);
	auto clampedInterpRatio = clamp(interpRatio, minInterpRatio, maxInterpRatio);

	auto lerp = clampedInterpRatio / clampedUpdateRate;

	if (lerp <= interprate->GetFloat())
		lerp = interprate->GetFloat();

	return lerp;
}

float GetFov(Vector Point, Vector LineOrigin, Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

void LegitBacktrack::Run(CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	if (!local_player || local_player->IsDormant())
		return;
	bool fakeLatency = Options.Misc.FakeLatency;
	int recordSize = fakeLatency ? 64 : 13;

	for (int i = 0; i < g_engine->GetMaxClients(); i++)
	{
		auto ent = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));

		if (!ent || ent->IsDormant() || ent->get_team_num() == local_player->get_team_num())
			continue;

		UpdateEntityData(ent, fakeLatency);

		while (this->entData[i].size() > recordSize)
		{
			this->entData[i].pop_back();
		}
		SetInvalidTicks(ent, this->entData[i], fakeLatency);
	}

	if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
	{
		auto ent = GetClosestEntity(local_player,cmd);

		if (!ent)
			return;

		BacktrackEntity(ent,cmd);
	}
}

C_CSPlayer* LegitBacktrack::GetClosestEntity(C_CSPlayer* pLocal,CUserCmd* cmd)
{
	C_CSPlayer* bestentity = nullptr;
	auto bestfov = 180;

	Vector current_angles;
	g_engine->GetViewAngles(current_angles);

	auto local = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	for (auto i = 0; i < g_entitylist->GetHighestEntityIndex(); i++)
	{
		auto entity = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(i));

		if (!entity
			|| entity->IsDormant()
			|| entity->get_health() <= 0
			|| entity->get_life_state() == 1
			|| entity->get_team_num() == local->get_team_num()
			|| entity == local)
			continue;

		auto clientclass = entity->GetClientClass();
		if (!clientclass)
			continue;

		if (clientclass->m_ClassID != CCSPlayer)
			continue;

		auto delta = local->get_eye_position() - entity->GetHitboxPosition(12);
		Vector angles;
		math::VectorAngles(delta, angles);
		math::clamp_angles(angles);

		//if (!can_penetrate_point(local, entity, angles))
			//continue;

		delta = angles - current_angles;
		delta.y = std::remainderf(delta.y, 360.f);
		auto fov = delta.Length2D();

		if (fov < bestfov)
		{
			bestfov = fov;
			bestentity = entity;
		}
	}

	return bestentity;
}

Vector extrapolate(C_BasePlayer* his, int value) {

	return his->get_origin() + (his->m_vecVelocity() * (g_globals->interval_per_tick * (float)value));
}

void LegitBacktrack::BacktrackEntity(C_CSPlayer* ent,CUserCmd* cmd)
{
	auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
	Vector viewAngles = AngleVector(cmd->viewangles + (local_player->get_aim_punch() * 2.f));
	Vector pLocalHead = local_player->get_eye_position();
	EntityData bestData = this->entData[ent->GetIndex()].back();

	std::deque<EntityData>& data = this->entData[ent->GetIndex()];
	float fov = 180.f;

	for (int i = 0; i < data.size(); i++)
	{
		if (!data.at(i).isTickValid)
			continue;

		Vector headPos = data.at(i).headPos;

		float thisFov = GetFov(headPos, pLocalHead, viewAngles);

		if (thisFov < fov)
		{
			fov = thisFov;
			bestData = data.at(i);
		}
	}


	int bestTickTime = TimeToTicks(bestData.simulationTime);
	
	//g_Utils->Print("Backtracking from tickcount %d To %d, a total of %d ticks", g_Globals.cmd->tick_count, bestTickTime, g_Globals.cmd->tick_count - bestTickTime);

	cmd->tick_count = bestTickTime;
}

ConVar* maxUnlag;

bool LegitBacktrack::CheckValidTick(int tick, EntityData data, bool fakeLatency)
{
	if (!fakeLatency)
		return true;

	float correct = 0;

	

	correct += g_engine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
	correct += g_engine->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);
	//correct += GetLerpTime();

	correct = clamp(correct, 0, 1.0f);

	float deltaTime = correct - (g_globals->curtime - data.simulationTime);

	float maxDelta = 0.2f;

	/*if (fakeLatency)
		maxDelta += 0.8 - i_GlobalVars->interval_per_tick;*/

	bool isValid = false;

	float debug = fabsf(deltaTime);



	return fabsf(deltaTime) <= maxDelta; //fabsf

	/*float outlatency;
	INetChannelInfo *nci = i_Engine->GetNetChannelInfo();
	if (nci) {
		outlatency = nci->GetLatency(FLOW_OUTGOING);
	}
	float correct = clamp(outlatency + GetLerpTime(), 0.0f, 1.0f);
	float flTargetTime = TicksToTime(tick);
	float deltaTime = correct - (i_GlobalVars->curtime - flTargetTime);

	float flMaxDelta = 0.2f;
	if (fakeLatency)
		flMaxDelta += 0.8 - i_GlobalVars->interval_per_tick;
	return (fabsf(deltaTime) <= flMaxDelta);*/
}

void LegitBacktrack::SetInvalidTicks(C_CSPlayer* ent, std::deque<EntityData>& data, bool fakeLatency)
{
	for (int i = 0; i < data.size(); i++)
	{
		bool isValid = CheckValidTick(i, data.at(i), fakeLatency);

		data.at(i).isTickValid = isValid;
	}
}

void LegitBacktrack::UpdateEntityData(C_CSPlayer* ent, bool fakeLatency)
{
	Vector headPos = ent->GetHitboxPosition(12);
	float simTime = ent->GetSimulationTime();

	Vector origin = ent->get_origin();
	QAngle absAng = ent->GetAbsAngles();

	bool validTick = !fakeLatency;

	this->entData[ent->GetIndex()].push_front({ headPos, simTime, origin, absAng, validTick });
}

LegitBacktrack f_LegitBacktrack;