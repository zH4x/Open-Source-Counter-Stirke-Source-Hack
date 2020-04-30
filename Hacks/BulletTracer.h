#include <vector>
#include "../SDK/Vector.h"
#include "../Interfaces.h"


void DrawBeamd(Vector src, Vector end, Color color);

class trace_info
{
public:
	trace_info(Vector starts, Vector positions, float times, int userids)
	{
		this->start = starts;
		this->position = positions;
		this->time = times;
		this->userid = userids;
	}

	Vector position;
	Vector start;
	float time;
	int userid;
};

extern std::vector<trace_info> trace_logs;

#define EVENT_DEBUG_ID_INIT 42 
class CBulletListener
{
	class BulletListener : IGameEventListener2
	{
	public:
		void start()
		{
			if (!EventManager->AddListener(this, "bullet_impact", false))
			{
				throw std::exception("Failed to register the event");
			}
		}
		void stop()
		{
			EventManager->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CBulletListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void)
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CBulletListener* singleton()
	{
		static CBulletListener* instance = new CBulletListener();
		return instance;
	}

	void init()
	{
		_listener.start();
	}
	void end()
	{
		_listener.stop();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "bullet_impact"))
		{

			if (!Options.Visuals.bBulletTracer)
				return;
			auto userid2 = g_engine->GetPlayerForUserID(event->GetInt("userid"));
			C_BasePlayer* shooter =  (C_BasePlayer*)g_entitylist->GetClientEntity(userid2);

			Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));
			if (shooter)
				trace_logs.push_back(trace_info(shooter->get_eye_position(), position, g_globals->curtime, event->GetInt("userid")));

			//	}
		}

	}

	void OnStudioRender()
	{
		if (Options.Visuals.bBulletTracer)
		{

			for (unsigned int i = 0; i < trace_logs.size(); i++) {

				auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
				if (!local_player)
					return;
				auto userid1 = g_engine->GetPlayerForUserID(trace_logs[i].userid);
				auto* shooter = (C_BasePlayer*)g_entitylist->GetClientEntity(userid1);

				if (!shooter) return;

				Color color;
				if (shooter == local_player)
				{
					color = Color(Options.Visuals.rTracer, Options.Visuals.gTracer, Options.Visuals.bTracer, Options.Visuals.BrightTracer);
				}
				else if(Options.Visuals.bBulletTracerEnemy)
					color = Color(255, 0, 0, 255);
				else
					continue;

				DrawBeamd(trace_logs[i].start, trace_logs[i].position, color);

				trace_logs.erase(trace_logs.begin() + i);
			}
		}
	}

private:
	BulletListener _listener;

	class cbullet_tracer_info
	{
	public:
		cbullet_tracer_info(Vector src, Vector dst, float time, Color color)
		{
			this->src = src;
			this->dst = dst;
			this->time = time;
			this->color = color;
		}

		Vector src, dst;
		float time;
		Color color;
	};

	std::vector<cbullet_tracer_info> logs;
};