#include "FakeLatency.h"



static std::deque<CIncomingSequence>sequences;
static int lastincomingsequencenumber;
void LagCompensation::UpdateIncomingSequences()
{

	INetChannel* ch = (INetChannel*)g_engine->GetNetChannelInfo();

	CNetChan* netchan = reinterpret_cast<CNetChan*>(ch);
	if (netchan)
	{
		//if (LocalPlayer.Real_m_nInSequencenumber == 0)
		//{
		//	LocalPlayer.Real_m_nInSequencenumber = netchan->m_nInSequenceNr;
		//	lastincomingsequencenumber = netchan->m_nInSequenceNr;
		//	//LocalPlayer.ModifiedSequenceNr = false;
		//}

		if (netchan->m_nInSequenceNr > lastincomingsequencenumber)
		{

			lastincomingsequencenumber = netchan->m_nInSequenceNr;

			sequences.push_front(CIncomingSequence(netchan->m_nInReliableState, netchan->m_nOutReliableState, netchan->m_nInSequenceNr, g_globals->realtime));
		}

		if (sequences.size() > 2048)
			sequences.pop_back();
	}
}

void LagCompensation::ClearIncomingSequences()
{
	m_last_incoming_sequence_number = 0;
	sequences.clear();
}

//Adds latency to the local player
void LagCompensation::AddLatencyToNetchan(CNetChan* netchan, float Latency)
{
	for (auto& seq : sequences)
	{
		if (g_globals->realtime - seq.curtime >= Latency)
		{
			netchan->m_nInReliableState = seq.inreliablestate;
			netchan->m_nInSequenceNr = seq.sequencenr;
			break;
		}
	}
}