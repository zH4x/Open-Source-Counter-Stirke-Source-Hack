#include "../SDK/CBaseEntity.h"
#include "../Interfaces.h"
#include "../SDK/Vector.h"
#include <vector>

struct DamageIndicator_t {
	int iDamage;
	bool bInitialized;
	float flEraseTime;
	float flLastUpdate;
	C_BasePlayer* Player;
	Vector Position;
};

class DamageIndicators {
public:
	std::vector<DamageIndicator_t> data;
	void paint();
};

extern DamageIndicators damage_indicators;