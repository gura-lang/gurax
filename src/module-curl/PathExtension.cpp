﻿//==============================================================================
// PathExtention.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return !pDirectoryParent &&
		(String::StartsWith<CharCase>(pDirectoryParent->GetName(), "http:") ||
		String::StartsWith<CharCase>(pDirectoryParent->GetName(), "https:") ||
		String::StartsWith<CharCase>(pDirectoryParent->GetName(), "ftp:") ||
		String::StartsWith<CharCase>(pDirectoryParent->GetName(), "ftps:") ||
		String::StartsWith<CharCase>(pDirectoryParent->GetName(), "sftp:"));
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe)
{
	const char* uri = *pPathName;
	size_t len = ::strlen(uri);
	Directory::Type type = (len > 0 && uri[len - 1] == '/')? Directory::Type::Folder : Directory::Type::Item;
	RefPtr<Directory> pDirectory(new DirectoryEx(type, uri));
	*pPathName = uri + len;
	return pDirectory.release();
}

PathMgr::Existence PathMgrEx::DoCheckExistence(Directory* pDirectoryParent, const char** pPathName)
{
	RefPtr<Directory> pDirectory(DoOpenDirectory(pDirectoryParent, pPathName, Directory::Type::None));
	Error::Clear();
	return pDirectory? Existence::Exist : Existence::None;
}

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
StatEx::StatEx() : Stat(nullptr, "", Flag::Reg, 0666, -1, 0, 0)
{
}

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":curl";
	return str;
}

#if 0
//------------------------------------------------------------------------------
// StatExList
//------------------------------------------------------------------------------
StatEx* StatExList::FindByName(const char* fileName) const
{
	PathName pathName(fileName);
	for (StatEx* pStatEx : *this) {
		if (pathName.DoesMatch(pStatEx->GetCentralFileHeader().GetFileName())) return pStatEx;
	}
	return nullptr;
}

bool StatExList::Write(Stream& streamDst) const
{
	for (StatEx* pStatEx : *this) {
		if (!pStatEx->GetCentralFileHeader().Write(streamDst)) return false;
	}
	return true;
}

//------------------------------------------------------------------------------
// StatExOwner
//------------------------------------------------------------------------------
void StatExOwner::Clear()
{
	for (StatEx* pStatEx : *this) StatEx::Delete(pStatEx);
	clear();
}

bool StatExOwner::ReadCentralDirectory(Stream& streamSrc)
{
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc);
	if (Error::IsIssued()) return false;
	if (!streamSrc.SetOffset(offsetCentralDirectory)) return false;
	UInt32 signature;
	while (ReadStream(streamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(streamSrc)) return false;
			if (!hdr.SkipFileData(streamSrc)) return false;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(streamSrc)) return false;
		} else if (signature == CentralFileHeader::Signature) {
			std::unique_ptr<CentralFileHeader> pCentralFileHeader(new CentralFileHeader());
			if (!pCentralFileHeader->Read(streamSrc)) return false;
			push_back(new StatEx(pCentralFileHeader.release()));
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(streamSrc)) return false;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(streamSrc)) return false;
			break;
		} else {
			Error::Issue(ErrorType::FormatError, "unknown signature %08x", signature);
			return false;
		}
	}
	return true;
}
#endif

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
void DirectoryEx::DoRewindChild()
{
	_idxChild = 0;
}

Directory* DirectoryEx::DoNextChild()
{
	return nullptr;
}

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
	CURL* curl = ::curl_easy_init();
	::curl_easy_setopt(curl, CURLOPT_URL, GetName());
	::curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	::curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	//::curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, CallbackXFERINFO);
	//::curl_easy_setopt(curl, CURLOPT_XFERINFODATA, progressInfo);
	CURLcode res = ::curl_easy_perform(curl);
	::curl_easy_cleanup(curl);
	return nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	//StatEx* pStatEx = GetCoreEx().GetStatEx();
	//return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
	return nullptr;
}

Gurax_EndModuleScope(curl)
