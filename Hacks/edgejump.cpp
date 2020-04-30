#include "edgejump.h"
#include "../options.h"


EdgeJump Edge;

int flags_backup = 0;

void EdgeJump::PrePredictionCreateMove(CUserCmd* cmd, C_BasePlayer* pLocal)
{
	if (!Options.Misc.Edgejumnp)
		return;
	if (!Options.Misc.AutoEdgeJump)
	if (!GetAsyncKeyState(Options.Misc.EdgejumnpKey))
		return;

	if (!pLocal)
		return;

	if (pLocal->GetMoveType() == MOVETYPE_LADDER || pLocal->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	flags_backup = pLocal->get_flags();
}

void EdgeJump::PostPredictionCreateMove(CUserCmd* cmd, C_BasePlayer* pLocal)
{
	if (!Options.Misc.Edgejumnp)
		return;
	if(!Options.Misc.AutoEdgeJump)
	if (!GetAsyncKeyState(Options.Misc.EdgejumnpKey))
		return;

	if (!pLocal)
		return;

	if (pLocal->GetMoveType() == MOVETYPE_LADDER || pLocal->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (flags_backup & FL_ONGROUND && !(pLocal->get_flags() & FL_ONGROUND))
		cmd->buttons |= IN_JUMP;

}