//==============================================================================
// DataType.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// TagInfo
//------------------------------------------------------------------------------
const TagInfo TagInfo::Empty;

// 4.6.4 TIFF Rev.6.0 Attribute Information
static const TagInfo g_tagInfoTbl_TIFF[] = {
	// A. Tags relating to image data structure
	{ TagId::ImageWidth,					"ImageWidth",					TypeId::LONG,		1,			},
	{ TagId::ImageLength,					"ImageLength",					TypeId::LONG,		1,			},
	{ TagId::BitsPerSample,					"BitsPerSample",				TypeId::SHORT,		3,			},
	{ TagId::Compression,					"Compression",					TypeId::SHORT,		1,			},
	{ TagId::PhotometricInterpretation,		"PhotometricInterpretation",	TypeId::SHORT,		1,			},
	{ TagId::Orientation,					"Orientation",					TypeId::SHORT,		1,			},
	{ TagId::SamplesPerPixel,				"SamplesPerPixel",				TypeId::SHORT,		1,			},
	{ TagId::PlanarConfiguration,			"PlanarConfiguration",			TypeId::SHORT,		1,			},
	{ TagId::YCbCrSubSampling,				"YCbCrSubSampling",				TypeId::SHORT,		2,			},
	{ TagId::YCbCrPositioning,				"YCbCrPositioning",				TypeId::SHORT,		1,			},
	{ TagId::XResolution,					"XResolution",					TypeId::RATIONAL,	1,			},
	{ TagId::YResolution,					"YResolution",					TypeId::RATIONAL,	1,			},
	{ TagId::ResolutionUnit,				"ResolutionUnit",				TypeId::SHORT,		1,			},
	// B. Tags relating to recording offset
	{ TagId::StripOffsets,					"StripOffsets",					TypeId::LONG,		Count::S,	},
	{ TagId::RowsPerStrip,					"RowsPerStrip",					TypeId::LONG,		1,			},
	{ TagId::StripByteCounts,				"StripByteCounts",				TypeId::LONG,		Count::S,	},
	{ TagId::JPEGInterchangeFormat,			"JPEGInterchangeFormat",		TypeId::JPEGInterchangeFormat, 1, },
	{ TagId::JPEGInterchangeFormatLength,	"JPEGInterchangeFormatLength",	TypeId::LONG,		1,			},
	// C. Tags relating to image data characteristics
	{ TagId::TransferFunction,				"TransferFunction",				TypeId::SHORT,		3 * 256,	},
	{ TagId::WhitePoint,					"WhitePoint",					TypeId::RATIONAL,	2,			},
	{ TagId::PrimaryChromaticities,			"PrimaryChromaticities",		TypeId::RATIONAL,	6,			},
	{ TagId::YCbCrCoefficients,				"YCbCrCoefficients",			TypeId::RATIONAL,	3,			},
	{ TagId::ReferenceBlackWhite,			"ReferenceBlackWhite",			TypeId::RATIONAL,	6,			},
	// D. Other tags
	{ TagId::DateTime,						"DateTime",						TypeId::ASCII,		20,			},
	{ TagId::ImageDescription,				"ImageDescription",				TypeId::ASCII,		Count::Any,	},
	{ TagId::Make,							"Make",							TypeId::ASCII,		Count::Any,	},
	{ TagId::Model,							"Model",						TypeId::ASCII,		Count::Any,	},
	{ TagId::Software,						"Software",						TypeId::ASCII,		Count::Any,	},
	{ TagId::Artist,						"Artist",						TypeId::ASCII,		Count::Any,	},
	{ TagId::Copyright,						"Copyright",					TypeId::ASCII,		Count::Any,	},
	// Pointers
	{ TagId::ExifIFDPointer,				"Exif",							TypeId::IFD,		1,			},
	{ TagId::GPSInfoIFDPointer,				"GPSInfo",						TypeId::IFD,		1,			},
};

// 4.6.5 Exif IFD Attribute Information
static const TagInfo g_tagInfoTbl_Exif[] = {
	// A. Tags Relating to Version
	{ TagId::ExifVersion,					"ExifVersion",					TypeId::UNDEFINED,	4,			},
	{ TagId::FlashPixVersion,				"FlashPixVersion",				TypeId::UNDEFINED,	4,			},
	// B. Tag Relating to Image Data Characteristics
	{ TagId::ColorSpace,					"ColorSpace",					TypeId::SHORT,		1,			},
	// C. Tags Relating to Image Configuration
	{ TagId::ComponentsConfiguration,		"ComponentsConfiguration",		TypeId::UNDEFINED,	4,			},
	{ TagId::CompressedBitsPerPixel,		"CompressedBitsPerPixel",		TypeId::RATIONAL,	1,			},
	{ TagId::PixelXDimension,				"PixelXDimension",				TypeId::LONG,		1,			},
	{ TagId::PixelYDimension,				"PixelYDimension",				TypeId::LONG,		1,			},
	// D. Tags Relating to User Information
	{ TagId::MakerNote,						"MakerNote",					TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::UserComment,					"UserComment",					TypeId::UNDEFINED,	Count::Any,	},
	// E. Tags Relating to Related File Information
	{ TagId::RelatedSoundFile,				"RelatedSoundFile",				TypeId::ASCII,		13,			},
	// F. Tags Relating to Date and Time
	{ TagId::DateTimeOriginal,				"DateTimeOriginal",				TypeId::ASCII,		20,			},
	{ TagId::DateTimeDigitized,				"DateTimeDigitized",			TypeId::ASCII,		20,			},
	{ TagId::SubSecTime,					"SubSecTime",					TypeId::ASCII,		Count::Any,	},
	{ TagId::SubSecTimeOriginal,			"SubSecTimeOriginal",			TypeId::ASCII,		Count::Any,	},
	{ TagId::SubSecTimeDigitized,			"SubSecTimeDigitized",			TypeId::ASCII,		Count::Any,	},
	// G. Tags Relating to Picture-Taking Conditions
	{ TagId::ExposureTime,					"ExposureTime",					TypeId::RATIONAL,	1,			},
	{ TagId::FNumber,						"FNumber",						TypeId::RATIONAL,	1,			},
	{ TagId::ExposureProgram,				"ExposureProgram",				TypeId::SHORT,		1,			},
	{ TagId::SpectralSensitivity,			"SpectralSensitivity",			TypeId::ASCII,		Count::Any,	},
	{ TagId::ISOSpeedRatings,				"ISOSpeedRatings",				TypeId::SHORT,		Count::Any,	},
	{ TagId::OECF,							"OECF",							TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::ShutterSpeedValue,				"ShutterSpeedValue",			TypeId::SRATIONAL,	1,			},
	{ TagId::ApertureValue,					"ApertureValue",				TypeId::RATIONAL,	1,			},
	{ TagId::BrightnessValue,				"BrightnessValue",				TypeId::SRATIONAL,	1,			},
	{ TagId::ExposureBiasValue,				"ExposureBiasValue",			TypeId::SRATIONAL,	1,			},
	{ TagId::MaxApertureValue,				"MaxApertureValue",				TypeId::RATIONAL,	1,			},
	{ TagId::SubjectDistance,				"SubjectDistance",				TypeId::RATIONAL,	1,			},
	{ TagId::MeteringMode,					"MeteringMode",					TypeId::SHORT,		1,			},
	{ TagId::LightSource,					"LightSource",					TypeId::SHORT,		1,			},
	{ TagId::Flash,							"Flash",						TypeId::SHORT,		1,			},
	{ TagId::FocalLength,					"FocalLength",					TypeId::RATIONAL,	1,			},
	{ TagId::SubjectArea,					"SubjectArea",					TypeId::SHORT,		Count::E2_3_4, },
	{ TagId::FlashEnergy,					"FlashEnergy",					TypeId::RATIONAL,	1,			},
	{ TagId::SpatialFrequencyResponse,		"SpatialFrequencyResponse",		TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::FocalPlaneXResolution,			"FocalPlaneXResolution",		TypeId::RATIONAL,	1,			},
	{ TagId::FocalPlaneYResolution,			"FocalPlaneYResolution",		TypeId::RATIONAL,	1,			},
	{ TagId::FocalPlaneResolutionUnit,		"FocalPlaneResolutionUnit",		TypeId::SHORT,		1,			},
	{ TagId::SubjectLocation,				"SubjectLocation",				TypeId::SHORT,		2,			},
	{ TagId::ExposureIndex,					"ExposureIndex",				TypeId::RATIONAL,	1,			},
	{ TagId::SensingMethod,					"SensingMethod",				TypeId::SHORT,		1,			},
	{ TagId::FileSource,					"FileSource",					TypeId::UNDEFINED,	1,			},
	{ TagId::SceneType,						"SceneType",					TypeId::UNDEFINED,	1,			},
	{ TagId::CFAPattern,					"CFAPattern",					TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::CustomRendered,				"CustomRendered",				TypeId::SHORT,		1,			},
	{ TagId::ExposureMode,					"ExposureMode",					TypeId::SHORT,		1,			},
	{ TagId::WhiteBalance,					"WhiteBalance",					TypeId::SHORT,		1,			},
	{ TagId::DigitalZoomRatio,				"DigitalZoomRatio",				TypeId::RATIONAL,	1,			},
	{ TagId::FocalLengthIn35mmFilm,			"FocalLengthIn35mmFilm",		TypeId::SHORT,		1,			},
	{ TagId::SceneCaptureType,				"SceneCaptureType",				TypeId::SHORT,		1,			},
	{ TagId::GainControl,					"GainControl",					TypeId::RATIONAL,	1,			},
	{ TagId::Contrast,						"Contrast",						TypeId::SHORT,		1,			},
	{ TagId::Saturation,					"Saturation",					TypeId::SHORT,		1,			},
	{ TagId::Sharpness,						"Sharpness",					TypeId::SHORT,		1,			},
	{ TagId::DeviceSettingDescription,		"DeviceSettingDescription",		TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::SubjectDistanceRange,			"SubjectDistanceRange",			TypeId::SHORT,		1,			},
	// H. Other Tags
	{ TagId::ImageUniqueID,					"ImageUniqueID",				TypeId::ASCII,		33,			},
	// Pointers
	{ TagId::InteroperabilityIFDPointer,	"Interoperability",				TypeId::IFD,		1,			},
};

// 4.6.6 GPS Attribute Information
static const TagInfo g_tagInfoTbl_GPSInfo[] = {
	// A. Tags Relating to GPS
	{ TagId::GPSVersionID,					"GPSVersionID",					TypeId::BYTE,		4,			},
	{ TagId::GPSLatitudeRef,				"GPSLatitudeRef",				TypeId::ASCII,		2,			},
	{ TagId::GPSLatitude,					"GPSLatitude",					TypeId::RATIONAL,	3,			},
	{ TagId::GPSLongitudeRef,				"GPSLongitudeRef",				TypeId::ASCII,		2,			},
	{ TagId::GPSLongitude,					"GPSLongitude",					TypeId::RATIONAL,	3,			},
	{ TagId::GPSAltitudeRef,				"GPSAltitudeRef",				TypeId::BYTE,		1,			},
	{ TagId::GPSAltitude,					"GPSAltitude",					TypeId::RATIONAL,	1,			},
	{ TagId::GPSTimeStamp,					"GPSTimeStamp",					TypeId::RATIONAL,	3,			},
	{ TagId::GPSSatellites,					"GPSSatellites",				TypeId::ASCII,		Count::Any,	},
	{ TagId::GPSStatus,						"GPSStatus",					TypeId::ASCII,		2,			},
	{ TagId::GPSMeasureMode,				"GPSMeasureMode",				TypeId::ASCII,		2,			},
	{ TagId::GPSDOP,						"GPSDOP",						TypeId::RATIONAL,	1,			},
	{ TagId::GPSSpeedRef,					"GPSSpeedRef",					TypeId::ASCII,		2,			},
	{ TagId::GPSSpeed,						"GPSSpeed",						TypeId::RATIONAL,	1,			},
	{ TagId::GPSTrackRef,					"GPSTrackRef",					TypeId::ASCII,		2,			},
	{ TagId::GPSTrack,						"GPSTrack",						TypeId::RATIONAL,	1,			},
	{ TagId::GPSImgDirectionRef,			"GPSImgDirectionRef",			TypeId::ASCII,		2,			},
	{ TagId::GPSImgDirection,				"GPSImgDirection",				TypeId::RATIONAL,	1,			},
	{ TagId::GPSMapDatum,					"GPSMapDatum",					TypeId::ASCII,		Count::Any,	},
	{ TagId::GPSDestLatitudeRef,			"GPSDestLatitudeRef",			TypeId::ASCII,		2,			},
	{ TagId::GPSDestLatitude,				"GPSDestLatitude",				TypeId::RATIONAL,	3,			},
	{ TagId::GPSDestLongitudeRef,			"GPSDestLongitudeRef",			TypeId::ASCII,		2,			},
	{ TagId::GPSDestLongitude,				"GPSDestLongitude",				TypeId::RATIONAL,	3,			},
	{ TagId::GPSBearingRef,					"GPSBearingRef",				TypeId::ASCII,		2,			},
	{ TagId::GPSBearing,					"GPSBearing",					TypeId::RATIONAL,	1,			},
	{ TagId::GPSDestDistanceRef,			"GPSDestDistanceRef",			TypeId::ASCII,		2,			},
	{ TagId::GPSDestDistance,				"GPSDestDistance",				TypeId::RATIONAL,	1,			},
	{ TagId::GPSProcessingMethod,			"GPSProcessingMethod",			TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::GPSAreaInformation,			"GPSAreaInformation",			TypeId::UNDEFINED,	Count::Any,	},
	{ TagId::GPSDateStamp,					"GPSDateStamp",					TypeId::ASCII,		11,			},
	{ TagId::GPSDifferential,				"GPSDifferential",				TypeId::SHORT,		1,			},
};

// 4.6.7 Interoperability IFD Attribute Information
static const TagInfo g_tagInfoTbl_Interoperability[] = {
	{ TagId::InteroperabilityIndex,			"InteroperabilityIndex",		TypeId::ASCII,		Count::Any,	},
};

static TagInfoMapByTagId g_tagInfoMapByTagId;
static TagInfoMapByTagId g_tagInfoMapByTagId_TIFF;
static TagInfoMapByTagId g_tagInfoMapByTagId_Exif;
static TagInfoMapByTagId g_tagInfoMapByTagId_GPSInfo;
static TagInfoMapByTagId g_tagInfoMapByTagId_Interoperability;

static TagInfoMapBySymbol g_tagInfoMapBySymbol;
static TagInfoMapBySymbol g_tagInfoMapBySymbol_TIFF;
static TagInfoMapBySymbol g_tagInfoMapBySymbol_Exif;
static TagInfoMapBySymbol g_tagInfoMapBySymbol_GPSInfo;
static TagInfoMapBySymbol g_tagInfoMapBySymbol_Interoperability;

void TagInfo::Initialize()
{
	g_tagInfoMapByTagId.Register(g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapByTagId.Register(g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapByTagId.Register(g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapByTagId.Register(g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapByTagId_TIFF.Register(g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapByTagId_Exif.Register(g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapByTagId_GPSInfo.Register(g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapByTagId_Interoperability.Register(g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapBySymbol.Register(g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapBySymbol.Register(g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapBySymbol.Register(g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapBySymbol.Register(g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapBySymbol_TIFF.Register(g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapBySymbol_Exif.Register(g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapBySymbol_GPSInfo.Register(g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapBySymbol_Interoperability.Register(g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
}

//const TagInfo* TagInfo::LookupByTagId(UInt16 tagId)
//{
//	return g_tagInfoMapByTagId.Lookup(tagId);
//}

const TagInfo* TagInfo::LookupByTagId(const Symbol* pSymbolOfIFD, UInt16 tagId)
{
	return
		pSymbolOfIFD->IsEmpty()? g_tagInfoMapByTagId.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd0))? g_tagInfoMapByTagId_TIFF.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd1))? g_tagInfoMapByTagId_TIFF.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Exif))? g_tagInfoMapByTagId_Exif.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Interoperability))? g_tagInfoMapByTagId_Interoperability.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(GPSInfo))? g_tagInfoMapByTagId_GPSInfo.Lookup(tagId) :
		nullptr;
}

//const TagInfo* TagInfo::LookupBySymbol(const Symbol* pSymbol)
//{
//	return g_tagInfoMapBySymbol.Lookup(pSymbol);
//}

const TagInfo* TagInfo::LookupBySymbol(const Symbol* pSymbolOfIFD, const Symbol* pSymbol)
{
	return
		pSymbolOfIFD->IsEmpty()? g_tagInfoMapBySymbol.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd0))? g_tagInfoMapBySymbol_TIFF.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd1))? g_tagInfoMapBySymbol_TIFF.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Exif))? g_tagInfoMapBySymbol_Exif.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Interoperability))? g_tagInfoMapBySymbol_Interoperability.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(GPSInfo))? g_tagInfoMapBySymbol_GPSInfo.Lookup(pSymbol) :
		nullptr;
}

//------------------------------------------------------------------------------
// TagInfoMapByTagId
//------------------------------------------------------------------------------
void TagInfoMapByTagId::Register(const TagInfo tagInfoTbl[], size_t n)
{
	for (size_t i = 0; i < n; i++) {
		(*this)[tagInfoTbl[i].tagId] = &tagInfoTbl[i];
	}
}

const TagInfo* TagInfoMapByTagId::Lookup(UInt16 tagId) const
{
	auto iter = find(tagId);
	return (iter == end())? nullptr : iter->second;
}

//------------------------------------------------------------------------------
// TagInfoMapBySymbol
//------------------------------------------------------------------------------
void TagInfoMapBySymbol::Register(const TagInfo tagInfoTbl[], size_t n)
{
	for (size_t i = 0; i < n; i++) {
		(*this)[Symbol::Add(tagInfoTbl[i].name)] = &tagInfoTbl[i];
	}
}

const TagInfo* TagInfoMapBySymbol::Lookup(const Symbol* pSymbol) const
{
	auto iter = find(pSymbol);
	return (iter == end())? nullptr : iter->second;
}

Gurax_EndModuleScope(jpeg)
