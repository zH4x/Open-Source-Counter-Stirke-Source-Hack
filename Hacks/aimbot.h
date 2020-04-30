#pragma once

#include "../hooks/hooks.h"
#include "../tools/entity.h"
#include "../tools/math.h"
//#include "../tools/curs.h"



class caimbot
{
public:
	void move(CUserCmd * pCmd, bool & sendpacket);
	void noSpread(CUserCmd* pCmd, bool& sendpacket);
	C_CSPlayer* get_best_target();
};

extern caimbot aimbot;