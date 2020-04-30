#include "hooks/hooks.h"
#include <fstream>
#include <array>
#include "Menu/options.h"
#include "Hacks/edgejump.h"
#define DUMP_CLASS_IDS

DWORD WINAPI thread(LPVOID dll)
{

	initialize_interfaces();
	initialize_hooks();

	g_cvar->ConsoleColorPrintf(Color(50, 255, 255), "Sucessfully Injected!\n");

#ifdef DUMP_CLASS_IDS
	std::ofstream file("class_ids.txt");
	file << "enum class EClassIds : int" << std::endl;
	file << "{" << std::endl;
	auto clazz = g_client->GetAllClasses();
	while (clazz)
	{
		file << "\t" << clazz->m_pNetworkName << " = " << clazz->m_ClassID << "," << std::endl;
		clazz = clazz->m_pNext;
	}

	file << "};" << std::endl;
	file.close();
	
#endif
	static bool was_enbaled;
	auto engine = (DWORD)GetModuleHandleA("engine.dll");
	while (!(GetAsyncKeyState(VK_END) & 0x8000))
	{
		auto local_player = reinterpret_cast<C_CSPlayer*>(g_entitylist->GetClientEntity(g_engine->GetLocalPlayer()));
		auto connect = *(DWORD*)(engine + 0x3C611C); // exact Full Connect addres better than g_engine->IsConnected();
		if (connect != 1)  // To fix send_data_gram Hook;
		{
			if (Options.Misc.hooked)
				Options.Misc.hooked = false;
			if (Options.Misc.FakeLatency)
			{
				was_enbaled = true;
				Options.Misc.FakeLatency = false;
			}
		}
		else 
			if(local_player->GetMoveType() == MOVETYPE_WALK) // we don't want to enable it when we rejoin immediately to avoid network problems
			if (was_enbaled && !Options.Misc.FakeLatency)
			{
				Options.Misc.FakeLatency = true;
				was_enbaled = false;
			}
		Sleep(5);
	}


	uninitialize_hooks();
	Sleep(1000);
	g_cvar->ConsoleColorPrintf(Color(255, 50, 50), "Sucessfully Unloaded!\n");
	FreeLibraryAndExitThread(static_cast<HMODULE>(dll), EXIT_SUCCESS);
	return 0;
}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (hinstDLL)
			DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, 0, thread, hinstDLL, 0, nullptr);
	}

	return TRUE;
}