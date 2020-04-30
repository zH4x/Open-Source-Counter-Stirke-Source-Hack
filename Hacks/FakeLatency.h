#pragma once
#include "../Interfaces.h"
#include <deque>


struct CIncomingSequence
{
	CIncomingSequence::CIncomingSequence(int instate, int outstate, int seqnr, float time)
	{
		inreliablestate = instate;
		outreliablestate = outstate;
		sequencenr = seqnr;
		curtime = time;
	}
	int inreliablestate;
	int outreliablestate;
	int sequencenr;
	float curtime;
};


class LagCompensation
{										
public:
	int m_last_incoming_sequence_number;
	void UpdateIncomingSequences();
	void ClearIncomingSequences();
	void AddLatencyToNetchan(CNetChan* netchan, float Latency);

};

extern LagCompensation* gLagCompensation;