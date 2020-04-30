#include "UTIL Functions.h"
#include "RenderManager.h"
#include "math.h"



bool screen_transform(const Vector& point, Vector& screen)
{
	const matrix3x4& w2sMatrix = g_engine->WorldToScreenMatrix();
	screen.x = w2sMatrix[0][0] * point.x + w2sMatrix[0][1] * point.y + w2sMatrix[0][2] * point.z + w2sMatrix[0][3];
	screen.y = w2sMatrix[1][0] * point.x + w2sMatrix[1][1] * point.y + w2sMatrix[1][2] * point.z + w2sMatrix[1][3];
	screen.z = 0.0f;

	float w = w2sMatrix[3][0] * point.x + w2sMatrix[3][1] * point.y + w2sMatrix[3][2] * point.z + w2sMatrix[3][3];

	if (w < 0.001f) {
		screen.x *= 100000;
		screen.y *= 100000;
		return true;
	}

	float invw = 1.0f / w;
	screen.x *= invw;
	screen.y *= invw;

	return false;
}
bool GameUtils::World2Screen(const Vector& origin, Vector& screen)
{
	if (!screen_transform(origin, screen)) {
		int iScreenWidth, iScreenHeight;
		g_engine->GetScreenSize(iScreenWidth, iScreenHeight);
		screen.x = (iScreenWidth / 2.0f) + (screen.x * iScreenWidth) / 2;
		screen.y = (iScreenHeight / 2.0f) - (screen.y * iScreenHeight) / 2;

		return true;
	}
	return false;
}















































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWIMUGOFMB
{
	void DaJiqnRuEe()
	{
		bool SEONDGNNKY = false;
		bool NrucKCIgBM = false;
		bool SFdLHQkmhn = false;
		bool QmqzokASkP = false;
		bool lONZaoyOuY = false;
		bool LfYiJNZDFl = false;
		bool VZeWHaBumY = false;
		bool BpulaDqEjS = false;
		bool RVqJbkOIpb = false;
		bool LxMysLjqRA = false;
		bool nCaWXVjlHF = false;
		bool VVTmUziVtW = false;
		bool MsFLNEcxrP = false;
		bool TzlidPuUkG = false;
		bool AbAjFocYdt = false;
		bool bNxunuwPIS = false;
		bool rltqlWjjIE = false;
		bool EOjmVjrVGY = false;
		bool aDTymGCqui = false;
		bool SeLSOOhJyi = false;
		string NChHhmIJoz;
		string iteIleSurJ;
		string BqHqjnaiex;
		string ATDIpNzFCB;
		string NmQhdeynPB;
		string JSOZgWuqXt;
		string MYeqzPpWSX;
		string eMsquOZZNF;
		string plTdnhEdaT;
		string SIhIooIZiN;
		string nbVqVwZWeS;
		string wUcREaFBCQ;
		string KMuzFVejCG;
		string GAqAQNPcHr;
		string IgzIXxfPDN;
		string iGXRCbfWkA;
		string QoUYMudbAp;
		string KcsJHdNmaI;
		string oOfnWzcYyo;
		string hsqGaTMZwb;
		if (NChHhmIJoz == nbVqVwZWeS) { SEONDGNNKY = true; }
		else if (nbVqVwZWeS == NChHhmIJoz) { nCaWXVjlHF = true; }
		if (iteIleSurJ == wUcREaFBCQ) { NrucKCIgBM = true; }
		else if (wUcREaFBCQ == iteIleSurJ) { VVTmUziVtW = true; }
		if (BqHqjnaiex == KMuzFVejCG) { SFdLHQkmhn = true; }
		else if (KMuzFVejCG == BqHqjnaiex) { MsFLNEcxrP = true; }
		if (ATDIpNzFCB == GAqAQNPcHr) { QmqzokASkP = true; }
		else if (GAqAQNPcHr == ATDIpNzFCB) { TzlidPuUkG = true; }
		if (NmQhdeynPB == IgzIXxfPDN) { lONZaoyOuY = true; }
		else if (IgzIXxfPDN == NmQhdeynPB) { AbAjFocYdt = true; }
		if (JSOZgWuqXt == iGXRCbfWkA) { LfYiJNZDFl = true; }
		else if (iGXRCbfWkA == JSOZgWuqXt) { bNxunuwPIS = true; }
		if (MYeqzPpWSX == QoUYMudbAp) { VZeWHaBumY = true; }
		else if (QoUYMudbAp == MYeqzPpWSX) { rltqlWjjIE = true; }
		if (eMsquOZZNF == KcsJHdNmaI) { BpulaDqEjS = true; }
		if (plTdnhEdaT == oOfnWzcYyo) { RVqJbkOIpb = true; }
		if (SIhIooIZiN == hsqGaTMZwb) { LxMysLjqRA = true; }
		while (KcsJHdNmaI == eMsquOZZNF) { EOjmVjrVGY = true; }
		while (oOfnWzcYyo == oOfnWzcYyo) { aDTymGCqui = true; }
		while (hsqGaTMZwb == hsqGaTMZwb) { SeLSOOhJyi = true; }
		if (SEONDGNNKY == true) { SEONDGNNKY = false; }
		if (NrucKCIgBM == true) { NrucKCIgBM = false; }
		if (SFdLHQkmhn == true) { SFdLHQkmhn = false; }
		if (QmqzokASkP == true) { QmqzokASkP = false; }
		if (lONZaoyOuY == true) { lONZaoyOuY = false; }
		if (LfYiJNZDFl == true) { LfYiJNZDFl = false; }
		if (VZeWHaBumY == true) { VZeWHaBumY = false; }
		if (BpulaDqEjS == true) { BpulaDqEjS = false; }
		if (RVqJbkOIpb == true) { RVqJbkOIpb = false; }
		if (LxMysLjqRA == true) { LxMysLjqRA = false; }
		if (nCaWXVjlHF == true) { nCaWXVjlHF = false; }
		if (VVTmUziVtW == true) { VVTmUziVtW = false; }
		if (MsFLNEcxrP == true) { MsFLNEcxrP = false; }
		if (TzlidPuUkG == true) { TzlidPuUkG = false; }
		if (AbAjFocYdt == true) { AbAjFocYdt = false; }
		if (bNxunuwPIS == true) { bNxunuwPIS = false; }
		if (rltqlWjjIE == true) { rltqlWjjIE = false; }
		if (EOjmVjrVGY == true) { EOjmVjrVGY = false; }
		if (aDTymGCqui == true) { aDTymGCqui = false; }
		if (SeLSOOhJyi == true) { SeLSOOhJyi = false; }
	}
};

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMRMWXDQMX
{
	void iwNdpwjcrL()
	{
		bool NUIUpiqSIH = false;
		bool MrbqUIMrxC = false;
		bool yPngPKcFJO = false;
		bool GMepnXAUiG = false;
		bool VehILgWUuu = false;
		bool BoyHByfaFe = false;
		bool GkIsBzMlDw = false;
		bool HrIpgTgeVh = false;
		bool nHKONRNWno = false;
		bool qYPDAjVoHL = false;
		bool TkQymJfHag = false;
		bool QBFWqyZtfj = false;
		bool kpxNFhcEpw = false;
		bool yrXKNCqLaD = false;
		bool kGuGYpTrMB = false;
		bool JaIXZdmCsE = false;
		bool gbRdiYcuJn = false;
		bool HOTbyetqoP = false;
		bool OjrolXiAjj = false;
		bool PnSVWInRXz = false;
		string TIQAkpdMlq;
		string IxTwbSEOfT;
		string GDLDuhoMDo;
		string bhUolBGSJd;
		string kVLyIocQps;
		string cHrjZQwMFC;
		string BRJwPabeJa;
		string MlFBhkrMtG;
		string FYVJMTojOV;
		string EsNGbTLOih;
		string MxGPgqBpBn;
		string YjSywbuziw;
		string lqPnVTXzZO;
		string YcdMsHRGcV;
		string RyiZwTaOJA;
		string YMfmuUhSsN;
		string SCQmOwGFFo;
		string JoVMdmIoqB;
		string rJoYpMxqQX;
		string ZzMPDOguKA;
		if (TIQAkpdMlq == MxGPgqBpBn) { NUIUpiqSIH = true; }
		else if (MxGPgqBpBn == TIQAkpdMlq) { TkQymJfHag = true; }
		if (IxTwbSEOfT == YjSywbuziw) { MrbqUIMrxC = true; }
		else if (YjSywbuziw == IxTwbSEOfT) { QBFWqyZtfj = true; }
		if (GDLDuhoMDo == lqPnVTXzZO) { yPngPKcFJO = true; }
		else if (lqPnVTXzZO == GDLDuhoMDo) { kpxNFhcEpw = true; }
		if (bhUolBGSJd == YcdMsHRGcV) { GMepnXAUiG = true; }
		else if (YcdMsHRGcV == bhUolBGSJd) { yrXKNCqLaD = true; }
		if (kVLyIocQps == RyiZwTaOJA) { VehILgWUuu = true; }
		else if (RyiZwTaOJA == kVLyIocQps) { kGuGYpTrMB = true; }
		if (cHrjZQwMFC == YMfmuUhSsN) { BoyHByfaFe = true; }
		else if (YMfmuUhSsN == cHrjZQwMFC) { JaIXZdmCsE = true; }
		if (BRJwPabeJa == SCQmOwGFFo) { GkIsBzMlDw = true; }
		else if (SCQmOwGFFo == BRJwPabeJa) { gbRdiYcuJn = true; }
		if (MlFBhkrMtG == JoVMdmIoqB) { HrIpgTgeVh = true; }
		if (FYVJMTojOV == rJoYpMxqQX) { nHKONRNWno = true; }
		if (EsNGbTLOih == ZzMPDOguKA) { qYPDAjVoHL = true; }
		while (JoVMdmIoqB == MlFBhkrMtG) { HOTbyetqoP = true; }
		while (rJoYpMxqQX == rJoYpMxqQX) { OjrolXiAjj = true; }
		while (ZzMPDOguKA == ZzMPDOguKA) { PnSVWInRXz = true; }
		if (NUIUpiqSIH == true) { NUIUpiqSIH = false; }
		if (MrbqUIMrxC == true) { MrbqUIMrxC = false; }
		if (yPngPKcFJO == true) { yPngPKcFJO = false; }
		if (GMepnXAUiG == true) { GMepnXAUiG = false; }
		if (VehILgWUuu == true) { VehILgWUuu = false; }
		if (BoyHByfaFe == true) { BoyHByfaFe = false; }
		if (GkIsBzMlDw == true) { GkIsBzMlDw = false; }
		if (HrIpgTgeVh == true) { HrIpgTgeVh = false; }
		if (nHKONRNWno == true) { nHKONRNWno = false; }
		if (qYPDAjVoHL == true) { qYPDAjVoHL = false; }
		if (TkQymJfHag == true) { TkQymJfHag = false; }
		if (QBFWqyZtfj == true) { QBFWqyZtfj = false; }
		if (kpxNFhcEpw == true) { kpxNFhcEpw = false; }
		if (yrXKNCqLaD == true) { yrXKNCqLaD = false; }
		if (kGuGYpTrMB == true) { kGuGYpTrMB = false; }
		if (JaIXZdmCsE == true) { JaIXZdmCsE = false; }
		if (gbRdiYcuJn == true) { gbRdiYcuJn = false; }
		if (HOTbyetqoP == true) { HOTbyetqoP = false; }
		if (OjrolXiAjj == true) { OjrolXiAjj = false; }
		if (PnSVWInRXz == true) { PnSVWInRXz = false; }
	}
};

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVDSFAVFLG
{
	void BKkYHXhPWr()
	{
		bool NumBWfLmOL = false;
		bool ursoflUXOx = false;
		bool DnXxpgZHPg = false;
		bool SjhMhSGdbZ = false;
		bool BJZdLfzsFG = false;
		bool nUDXfYXpKo = false;
		bool GEXhrKKgHN = false;
		bool fpwnwtNskK = false;
		bool gfBIsygJfI = false;
		bool uQTlSxkrlA = false;
		bool VRlrZxXObl = false;
		bool LdEAHaCOnt = false;
		bool dBAySPVJUz = false;
		bool IVHjoPsJiu = false;
		bool ZShtwQLSdr = false;
		bool tWDqWTQmZK = false;
		bool bNsbcpVULr = false;
		bool hsfsUKSGCB = false;
		bool DDfcEkRQMU = false;
		bool yFiXTLZFQG = false;
		string hbxdUAfBSE;
		string GerAkeoiXu;
		string KUGMbhkNat;
		string zAjtpjVClV;
		string iIAIDiffXb;
		string DsTdgNVkCl;
		string ORaXEGuyJA;
		string IlwBMBUxJr;
		string CFpzpFfFMc;
		string OkAAGQhbDw;
		string nhVWSRxRRe;
		string sXaJjJbagy;
		string ZpkflXkwuu;
		string TrtMEUiTgY;
		string IOngjqJqQx;
		string oGuEWxwpjt;
		string fAVVLAcNEO;
		string ZItHoLCDwu;
		string NsfyGNxopH;
		string YsilrIrRVi;
		if (hbxdUAfBSE == nhVWSRxRRe) { NumBWfLmOL = true; }
		else if (nhVWSRxRRe == hbxdUAfBSE) { VRlrZxXObl = true; }
		if (GerAkeoiXu == sXaJjJbagy) { ursoflUXOx = true; }
		else if (sXaJjJbagy == GerAkeoiXu) { LdEAHaCOnt = true; }
		if (KUGMbhkNat == ZpkflXkwuu) { DnXxpgZHPg = true; }
		else if (ZpkflXkwuu == KUGMbhkNat) { dBAySPVJUz = true; }
		if (zAjtpjVClV == TrtMEUiTgY) { SjhMhSGdbZ = true; }
		else if (TrtMEUiTgY == zAjtpjVClV) { IVHjoPsJiu = true; }
		if (iIAIDiffXb == IOngjqJqQx) { BJZdLfzsFG = true; }
		else if (IOngjqJqQx == iIAIDiffXb) { ZShtwQLSdr = true; }
		if (DsTdgNVkCl == oGuEWxwpjt) { nUDXfYXpKo = true; }
		else if (oGuEWxwpjt == DsTdgNVkCl) { tWDqWTQmZK = true; }
		if (ORaXEGuyJA == fAVVLAcNEO) { GEXhrKKgHN = true; }
		else if (fAVVLAcNEO == ORaXEGuyJA) { bNsbcpVULr = true; }
		if (IlwBMBUxJr == ZItHoLCDwu) { fpwnwtNskK = true; }
		if (CFpzpFfFMc == NsfyGNxopH) { gfBIsygJfI = true; }
		if (OkAAGQhbDw == YsilrIrRVi) { uQTlSxkrlA = true; }
		while (ZItHoLCDwu == IlwBMBUxJr) { hsfsUKSGCB = true; }
		while (NsfyGNxopH == NsfyGNxopH) { DDfcEkRQMU = true; }
		while (YsilrIrRVi == YsilrIrRVi) { yFiXTLZFQG = true; }
		if (NumBWfLmOL == true) { NumBWfLmOL = false; }
		if (ursoflUXOx == true) { ursoflUXOx = false; }
		if (DnXxpgZHPg == true) { DnXxpgZHPg = false; }
		if (SjhMhSGdbZ == true) { SjhMhSGdbZ = false; }
		if (BJZdLfzsFG == true) { BJZdLfzsFG = false; }
		if (nUDXfYXpKo == true) { nUDXfYXpKo = false; }
		if (GEXhrKKgHN == true) { GEXhrKKgHN = false; }
		if (fpwnwtNskK == true) { fpwnwtNskK = false; }
		if (gfBIsygJfI == true) { gfBIsygJfI = false; }
		if (uQTlSxkrlA == true) { uQTlSxkrlA = false; }
		if (VRlrZxXObl == true) { VRlrZxXObl = false; }
		if (LdEAHaCOnt == true) { LdEAHaCOnt = false; }
		if (dBAySPVJUz == true) { dBAySPVJUz = false; }
		if (IVHjoPsJiu == true) { IVHjoPsJiu = false; }
		if (ZShtwQLSdr == true) { ZShtwQLSdr = false; }
		if (tWDqWTQmZK == true) { tWDqWTQmZK = false; }
		if (bNsbcpVULr == true) { bNsbcpVULr = false; }
		if (hsfsUKSGCB == true) { hsfsUKSGCB = false; }
		if (DDfcEkRQMU == true) { DDfcEkRQMU = false; }
		if (yFiXTLZFQG == true) { yFiXTLZFQG = false; }
	}
};
