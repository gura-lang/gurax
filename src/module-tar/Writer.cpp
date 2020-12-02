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

bool Writer::Add(Stream& stream, const char* fileName)
{
	Header hdr;
	hdr.SetName(PathName(fileName).ReplaceSep("/").c_str());
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
	return Add(stream, hdr);
}

bool Writer::Add(Stream& stream, const Header& hdr)
{
	char buffBlock[Header::BLOCKSIZE];
	size_t bytesBody = stream.GetBytes();
	size_t bytesPadding = (bytesBody + Header::BLOCKSIZE - 1) /
							Header::BLOCKSIZE * Header::BLOCKSIZE - bytesBody;
	hdr.ComposeHeaderBlock(buffBlock);
	if (!_pStreamDst->Write(buffBlock, Header::BLOCKSIZE)) return false;
	if (!_pStreamDst->PipeFromStream(stream)) return false;
	::memset(buffBlock, 0x00, bytesPadding);
	return _pStreamDst->Write(buffBlock, bytesPadding);
}

void Writer::Close()
{
	char buffBlock[Header::BLOCKSIZE * 2];
	::memset(buffBlock, 0x00, Header::BLOCKSIZE * 2);
	_pStreamDst->Write(buffBlock, Header::BLOCKSIZE * 2);
	_pStreamDst->Close();
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Writer");
}

Gurax_EndModuleScope(tar)
