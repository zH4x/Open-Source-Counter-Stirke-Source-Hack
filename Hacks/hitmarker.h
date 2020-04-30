#include "../Interfaces.h"
#include "../ImGui/imgui.h"
#include <Windows.h>
#include "../ImGui/imgui_internal.h"
#include "../tools/math.h"
#include "../options.h"
#include "damageindirector.h"


#pragma comment(lib, "Winmm.lib") 


class hitmarker
{
    class player_hurt_listener
        : public IGameEventListener2
    {
    public:
        void start()
        {
            if (!EventManager->AddListener(this, "player_hurt", false)) {
                // Log::Fatal("Failed to register the event");
            }
        }
        void stop()
        {
            EventManager->RemoveListener(this);
        }
        void FireGameEvent(IGameEvent* event) override
        {
            hitmarker::singleton()->on_fire_event(event);
        }
    };
public:

    static hitmarker* singleton()
    {
        static hitmarker* instance = new hitmarker;
        return instance;
    }


    void initialize()
    {
        _listener.start();

    }
    void end()
    {
        _listener.stop();

    }


    void on_fire_event(IGameEvent* event)
    {
        auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
        if (!local_player)
            return;
        if (!strcmp(event->GetName(), "player_hurt")) {
            int userid2 = g_engine->GetPlayerForUserID(event->GetInt("userid"));
            C_BasePlayer* m_entity = (C_BasePlayer * )g_entitylist->GetClientEntity(userid2);
            int attacker = event->GetInt("attacker");
            if (Options.Visuals.ShowDamage && g_engine->GetPlayerForUserID(attacker) == g_engine->GetLocalPlayer())
            {
                DamageIndicator_t DmgIndicator;
                DmgIndicator.iDamage = event->GetInt("dmg_health");
                DmgIndicator.Player = m_entity;
                DmgIndicator.flEraseTime = local_player->get_tick_base() * g_globals->interval_per_tick + 3.f;
                DmgIndicator.bInitialized = false;

                damage_indicators.data.push_back(DmgIndicator);
            }
            if (g_engine->GetPlayerForUserID(attacker) == g_engine->GetLocalPlayer()) {
                //g_pSurface->PlaySound doesnt work for some reason
                if (Options.Visuals.bHitMarker) {
                    PlaySoundA(_soundFileName, NULL, SND_ASYNC);
                    _flHurtTime = g_globals->curtime;

                }
            }
        }
    }


    void on_paint()
    {
       

        auto curtime = g_globals->curtime;
        auto lineSize = 8;
        if (_flHurtTime + 0.25f >= curtime) {
            int screenSizeX, screenCenterX;
            int screenSizeY, screenCenterY;
            g_surface->GetScreenSize(screenSizeX, screenSizeY);

            screenCenterX = screenSizeX / 2;
            screenCenterY = screenSizeY / 2;
            g_surface->DrawSetColor(Color(200, 200, 200));
            g_surface->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
            g_surface->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
            g_surface->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
            g_surface->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
        }
    }

private:
    bool should;
    int count;
    int olddamge = 100;
    int damage;
    bool mehurt;
    bool check;
    player_hurt_listener    _listener;
    const char* _soundFileName = "C:\\Cheat\\hitsound.wav";
    float                   _flHurtTime;
};

