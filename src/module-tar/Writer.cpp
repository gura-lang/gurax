//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
Writer::Writer(Stream* pStreamDst) : _pStreamDst(pStreamDst)
{
}

bool Writer::Add(const char* fileName, Stream& stream)
{
	Header hdr;
	hdr.SetName(fileName);
	hdr.SetLinkName("");
	hdr.SetSize(stream.GetBytes());
	RefPtr<Stat> pStat(stream.CreateStat());
	if (pStat) {
		char buff[80];
		hdr.SetMode(0100000 | (pStat->GetMode() & 0777));
		hdr.SetMTime(pStat->GetDateTimeM().Reference());
		hdr.SetATime(pStat->GetDateTimeA().Reference());
		hdr.SetCTime(pStat->GetDateTimeC().Reference());
		hdr.SetUid(pStat->GetUid());
		hdr.SetGid(pStat->GetGid());
		::sprintf(buff, "%d", pStat->GetUid());
		hdr.SetUName(buff);
		::sprintf(buff, "%d", pStat->GetGid());
		hdr.SetGName(buff);
	} else {
		hdr.SetMode(0100666);
		RefPtr<DateTime> pDt(OAL::CreateDateTimeCur(false));
		hdr.SetMTime(pDt->Reference());
		hdr.SetATime(pDt->Reference());
		hdr.SetCTime(pDt->Reference());
		hdr.SetUid(0);
		hdr.SetGid(0);
		hdr.SetUName("0");
		hdr.SetGName("0");
	}
	hdr.SetChksum(0);
	hdr.SetTypeFlag(0x00);
	hdr.SetDevMajor(0);
	hdr.SetDevMinor(0);
	//if (!pThis->Add(streamSrc, hdr)) return Value::Nil;
	return false;
}

void Writer::Close()
{
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Writer");
}

Gurax_EndModuleScope(tar)
