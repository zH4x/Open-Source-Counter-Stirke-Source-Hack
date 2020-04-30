


class cOptions
{
public:
	struct
	{
		struct
		{
			bool bAimbotEnable;
			bool bAutoShoot;
			bool bAutoScope;
			bool bAutoRevolver;
			bool bSilentAim;
			bool pSilentAim;
			bool bAutoPistol;
			bool aimbot_on_key;
			int key;
			float aimbot_smooth;
			float Fov;
			int  iHitbox;
			int hitbox = 12;
			int  iSelection;
			float aimbot_mindmg;
		}Aimbot;
		struct
		{
			bool bVelocityPrediction;
			int	 iMultibox;
			bool bMultipoint;
			int  iPointscale;
			int  iHitchance;
			int  iMinDmg;
			bool bAcceptKillDmg;
			bool bNoRecoil;
		}Accuracy;
		struct
		{
			int  iAntiAimResolver;
			int  iAccuracyBoost;
			int  iPreferBaim;
			bool bPositionAdj;
			bool bBruteforce;
			bool bResolver;

		}HvH;
		struct
		{
			struct
			{
				bool bEnableAntiAim;
				bool bAtTargets;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Stand;
			struct
			{
				bool bEnableAntiAim;
				bool bAtTargets;
				bool bMemeWalk;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Move;
			struct
			{
				bool bEnableEdge;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Edge;
			struct
			{
				bool bFakeWalk;
				int  iFakeWalkKey;
			}Misc;
		}AntiAim;

	}Ragebot;
	struct
	{
		struct
		{
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bAutoPistol;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Pistols;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Rifles;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Snipers;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Shotguns;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Smgs;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Heavy;

		}Aimbot;
		struct
		{
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//	int  iTriggerDelay = 10;
				bool bTriggerRecoil;
				bool bAutoRevolver;
				bool bRevolverSecondary;
				bool bAutoPistol;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Pistols;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Rifles;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
				bool bScoped;
			}Snipers;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Shotguns;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Smgs;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Heavy;

		}Trigger;
	}Legitbot;
	struct
	{
		
			
				bool bBox;
				bool bHealthbar;
				bool bHealthText;
				bool bArmorBar;
				int	 iBarPos;
				bool bSkeleton;
				bool bAimlines;
				bool bPitch;
				bool bYaw;
				bool visuals_snapline;
			
				bool bWeapons;
				bool bAmmo;
				bool bName;
				bool bIsScoped;
				bool bIsFlashed;
				bool visuals_spread_circle;
		
				bool bDroppedWeapons;
				bool bEnemyOnly;
				bool bXQZ;
				bool bC4;
				bool bHostage;
			bool bInfoBox;
			bool bInfoLby;
			bool bInfoVelocity;
			bool bInfoAngles;
			bool bPlayerBox;

	
			bool bSpecList;
			bool bCrosshair;
			bool bNormalCrosshair;
			bool bRecoilCrosshair;
			bool bSpreadCrosshair;
			bool bNoVisualRecoil;
			bool bRankReveal;
			bool bThirdperson;
			int  iThirdPerson;
			int  iThirdPersonKey;
			float flThirdPersonRange;
			bool bScopeRemover;
			bool bEngineRadar;
			bool bWatermark = true;
			bool bTime;
			bool bHitMarker;
			bool ShowDamage;
			int	 iHitsound;
			int  iKillsound;
			bool ShowVelocity;
			bool ShowKeys;
		
			bool bAsusWalls;
			float flAsusFactor = 100;
			bool bNightMode;
			bool bNoFlash;
			bool bNoSmoke;
			bool NoSky;
			int	 iSkyboxChanger;
			bool bBulletTracer;
			bool rainbowtracer;
			bool bBulletTracerEnemy;
			int rEsp;
			int gEsp;
			int bEsp;
			int rEsp_t;
			int gEsp_t;
			int bEsp_t;
			int rEspVisable_t;
			int gEspVisable_t;
			int bEspVisable_t;
			int rEspVisable_ct;
			int gEspVisable_ct;
			int bEspVisable_ct;
			int brightEsp;
			int rTracer = 255;
			int gTracer = 255;
			int bTracer = 255;
			int BrightTracer = 255;
			float flTracerLenght = 1;
			bool bColorMod;

	
		
			bool bPlayers;
			bool bWireframe;
			bool bFlat;
			bool bThroughWalls;
			bool bTransparent;
			bool bArms;
			bool bArmsWireframe;
			bool bArmsFlat;
			bool bArmsThroughWalls;
			bool bArmsTransparent;
		
			bool bEnabled;
			bool bChickens;
			bool bC4Carrier;
			bool bPlantedC4;
			bool bDefuseKits;
			bool hideteammates;
			bool bFreeCam;
			int  bFreeCamKey = VK_SHIFT;
			int flFreeCamSpeed = 1;
			bool Fov;
			bool NoHands;
			int FovValue = 90;
			bool ViewModelFov;
			int ViewModelFovValue = 90;
			bool NoVisualRecoil;
			bool NoShadows;
			bool BacktrackVis;
			bool BacktrackChams;
			bool BacktrackDots;
			bool BacktrackVisuals;
			bool visuals_triggerbot_hitbox;
			bool visuals_triggerbot_hit_point;
			Color colors_esp_t;
			Color colors_esp_ct;
			Color colors_esp_visible_t;
			Color colors_esp_visible_ct;
			int CrosshairRed;
			int CrosshairGreen;
			int CrosshairBlue = 255;
			Color colors_watermark = Color::ForestGreen();


		
	}Visuals;
	struct
	{
			bool bAutoJump;
			bool AutoJumpBug;
			bool AutoPistol;
			bool bAutoStrafe;
			bool bAirStuck;
			bool bSlowmotion;
			bool bZStrafe;
			bool LowFps;
			bool bCircleStrafer;
			bool bWalkBot;
			bool Edgejumnp;
			bool AutoEdgeJump;
			int  EdgejumnpKey = 0x43;
			bool bBunnyhop;
			bool Fastrun;
			bool FastStop;
			bool FastStop_filter[3]{ false, false, false };
			char Disconnectreason[100];
			char ClanTag[100];
			float flDistance = 0;
			int  iTurn = 0;
			int  iAirStuck;
			int  iAirStuckKey;
			int  iSlowMotionKey;
			int  iZStrafeKey;
			bool KnifeBot;
			bool FakeLowLatency;
			bool FakeLatency;
			float FakeLatencyValue;
			int  iCircleStraferMode;
			int  iCircleStraferKey;
			int  iAutoStrafeMode = 4;
			bool NoSpread;
			bool NoRecoil;
			bool BackTrack;
			bool visual_crosshair;
			float visual_crosshair_offset = 0;
			float visual_crosshair_spin = 10;
			int visual_alpha = 255;
			int trigger = 0;
			bool on_key;
			int triggerbot_key = 0x46;
			bool misc_triggerbot_filter[6]{ false, false, false, false, false, false };
			bool BacktrackTriggerBot;
			bool Run = true;
			bool hooked = false;
			bool bEnableFov;
			int flViewModelValue = 68;
	}Misc;
	struct
	{
		float espVisT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisT[3] = { 0.7f, 0.1f, 0.1f };
		float espVisCT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisCT[3] = { 0.7f, 0.1f, 0.1f };

		float chamsPlyrTVis[3] = { 0.9f,0.4f,0.f };
		float chamsPlyrTInvis[3] = { 0.9f, 0.0f, 0.f };
		float chamsPlyrCTVis[3] = { 0.f,0.4f,0.9f };
		float chamsPlyrCTInvis[3] = { 0.f,0.0f,0.9f };

		float chamsHandsVis[3] = { 0.4f, 0.2f, 1.f };
		float chamsHandsInvis[3] = { 1.f, 0.2f, 0.4f };

		float colormod[3] = { 0.3f, 0.3f, 0.3f };
		float colormodProps[3] = { 0.3f, 0.3f, 0.3f };
		float colormodModels[3] = { 0.3f, 0.3f, 0.3f };
		float bullettracer[3] = { 0.9f, 0.2f, 0.2f };

	}Col;
	struct
	{
		bool bEnableSkins;
	}Skins;
	struct
	{
		bool setup = false;
		int current;
		int iConfigs;
	}Config;
};

extern cOptions Options;