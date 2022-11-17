//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
Writer::GzipInfo Writer::gzipInfo;
Writer::Bzip2Info Writer::bzip2Info;

Writer::Writer(Stream* pStreamDst) : _pStreamDst(pStreamDst)
{
}

bool Writer::Add(Stream& stream, const char* fileName, RefPtr<DateTime> pDateTimeM,
			RefPtr<DateTime> pDateTimeA, RefPtr<DateTime> pDateTimeC)
{
	Header hdr;
	hdr.SetName(PathName(fileName).ReplaceSep("/").c_str());
	hdr.SetLinkName("");
	hdr.SetSize(stream.GetBytes());
	RefPtr<Stat> pStat(stream.CreateStat());
	if (pStat) {
		char buff[80];
		hdr.SetMode(0100000 | (pStat->GetMode() & 0777));
		if (!pDateTimeM) pDateTimeM.reset(pStat->GetDateTimeM().Reference());
		if (!pDateTimeA) pDateTimeA.reset(pStat->GetDateTimeA().Reference());
		if (!pDateTimeC) pDateTimeC.reset(pStat->GetDateTimeC().Reference());
		hdr.SetUid(pStat->GetUid());
		hdr.SetGid(pStat->GetGid());
		::sprintf(buff, "%d", pStat->GetUid());
		hdr.SetUName(buff);
		::sprintf(buff, "%d", pStat->GetGid());
		hdr.SetGName(buff);
	} else {
		hdr.SetMode(0100666);
		RefPtr<DateTime> pDt(OAL::CreateDateTimeCur(false));
		if (!pDateTimeM) pDateTimeM.reset(pDt->Reference());
		if (!pDateTimeA) pDateTimeA.reset(pDt->Reference());
		if (!pDateTimeC) pDateTimeC.reset(pDt->Reference());
		hdr.SetUid(0);
		hdr.SetGid(0);
		hdr.SetUName("0");
		hdr.SetGName("0");
	}
	hdr.SetMTime(pDateTimeM.release());
	hdr.SetATime(pDateTimeA.release());
	hdr.SetCTime(pDateTimeC.release());
	hdr.SetChksum(0);
	hdr.SetTypeFlag(0x00);
	hdr.SetDevMajor(0);
	hdr.SetDevMinor(0);
	return Add(stream, hdr);
}

bool Writer::Add(Stream& stream, const Header& hdr)
{
	if (!_pStreamDst) return true;
	char buffBlock[Header::BLOCKSIZE];
	size_t bytesBody = stream.GetBytes();
	size_t bytesPadding = (bytesBody + Header::BLOCKSIZE - 1) /
							Header::BLOCKSIZE * Header::BLOCKSIZE - bytesBody;
	if (!hdr.ComposeHeaderBlock(buffBlock)) return false;
	if (!_pStreamDst->Write(buffBlock, Header::BLOCKSIZE)) return false;
	if (!_pStreamDst->PipeFromStream(stream)) return false;
	::memset(buffBlock, 0x00, bytesPadding);
	return _pStreamDst->Write(buffBlock, bytesPadding);
}

void Writer::Close()
{
	if (!_pStreamDst) return;
	char buffBlock[Header::BLOCKSIZE * 2];
	::memset(buffBlock, 0x00, Header::BLOCKSIZE * 2);
	_pStreamDst->Write(buffBlock, Header::BLOCKSIZE * 2);
	_pStreamDst->Close();
	_pStreamDst.reset(nullptr);
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Writer");
}

Gurax_EndModuleScope(tar)
