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
	{ TagId::ImageWidth,					"ImageWidth",					TypeId::LONG,		},
	{ TagId::ImageLength,					"ImageLength",					TypeId::LONG,		},
	{ TagId::BitsPerSample,					"BitsPerSample",				TypeId::SHORT,		},
	{ TagId::Compression,					"Compression",					TypeId::SHORT,		},
	{ TagId::PhotometricInterpretation,		"PhotometricInterpretation",	TypeId::SHORT,		},
	{ TagId::Orientation,					"Orientation",					TypeId::SHORT,		},
	{ TagId::SamplesPerPixel,				"SamplesPerPixel",				TypeId::SHORT,		},
	{ TagId::PlanarConfiguration,			"PlanarConfiguration",			TypeId::SHORT,		},
	{ TagId::YCbCrSubSampling,				"YCbCrSubSampling",				TypeId::SHORT,		},
	{ TagId::YCbCrPositioning,				"YCbCrPositioning",				TypeId::SHORT,		},
	{ TagId::XResolution,					"XResolution",					TypeId::RATIONAL,	},
	{ TagId::YResolution,					"YResolution",					TypeId::RATIONAL,	},
	{ TagId::ResolutionUnit,				"ResolutionUnit",				TypeId::SHORT,		},
	// B. Tags relating to recording offset
	{ TagId::StripOffsets,					"StripOffsets",					TypeId::LONG,		},
	{ TagId::RowsPerStrip,					"RowsPerStrip",					TypeId::LONG,		},
	{ TagId::StripByteCounts,				"StripByteCounts",				TypeId::LONG,		},
	{ TagId::JPEGInterchangeFormat,			"JPEGInterchangeFormat",		TypeId::JPEGInterchangeFormat, },
	{ TagId::JPEGInterchangeFormatLength,	"JPEGInterchangeFormatLength",	TypeId::LONG,		},
	// C. Tags relating to image data characteristics
	{ TagId::TransferFunction,				"TransferFunction",				TypeId::SHORT,		},
	{ TagId::WhitePoint,					"WhitePoint",					TypeId::RATIONAL,	},
	{ TagId::PrimaryChromaticities,			"PrimaryChromaticities",		TypeId::RATIONAL,	},
	{ TagId::YCbCrCoefficients,				"YCbCrCoefficients",			TypeId::RATIONAL,	},
	{ TagId::ReferenceBlackWhite,			"ReferenceBlackWhite",			TypeId::RATIONAL,	},
	// D. Other tags
	{ TagId::DateTime,						"DateTime",						TypeId::ASCII,		},
	{ TagId::ImageDescription,				"ImageDescription",				TypeId::ASCII,		},
	{ TagId::Make,							"Make",							TypeId::ASCII,		},
	{ TagId::Model,							"Model",						TypeId::ASCII,		},
	{ TagId::Software,						"Software",						TypeId::ASCII,		},
	{ TagId::Artist,						"Artist",						TypeId::ASCII,		},
	{ TagId::Copyright,						"Copyright",					TypeId::ASCII,		},
	// Pointers
	{ TagId::ExifIFDPointer,				"Exif",							TypeId::IFD,		},
	{ TagId::GPSInfoIFDPointer,				"GPSInfo",						TypeId::IFD,		},
};

// 4.6.5 Exif IFD Attribute Information
static const TagInfo g_tagInfoTbl_Exif[] = {
	// A. Tags Relating to Version
	{ TagId::ExifVersion,					"ExifVersion",					TypeId::UNDEFINED,	},
	{ TagId::FlashPixVersion,				"FlashPixVersion",				TypeId::UNDEFINED,	},
	// B. Tag Relating to Image Data Characteristics
	{ TagId::ColorSpace,					"ColorSpace",					TypeId::SHORT,		},
	// C. Tags Relating to Image Configuration
	{ TagId::ComponentsConfiguration,		"ComponentsConfiguration",		TypeId::UNDEFINED,	},
	{ TagId::CompressedBitsPerPixel,		"CompressedBitsPerPixel",		TypeId::RATIONAL,	},
	{ TagId::PixelXDimension,				"PixelXDimension",				TypeId::LONG,		},
	{ TagId::PixelYDimension,				"PixelYDimension",				TypeId::LONG,		},
	// D. Tags Relating to User Information
	{ TagId::MakerNote,						"MakerNote",					TypeId::UNDEFINED,	},
	{ TagId::UserComment,					"UserComment",					TypeId::UNDEFINED,	},
	// E. Tags Relating to Related File Information
	{ TagId::RelatedSoundFile,				"RelatedSoundFile",				TypeId::ASCII,		},
	// F. Tags Relating to Date and Time
	{ TagId::DateTimeOriginal,				"DateTimeOriginal",				TypeId::ASCII,		},
	{ TagId::DateTimeDigitized,				"DateTimeDigitized",			TypeId::ASCII,		},
	{ TagId::SubSecTime,					"SubSecTime",					TypeId::ASCII,		},
	{ TagId::SubSecTimeOriginal,			"SubSecTimeOriginal",			TypeId::ASCII,		},
	{ TagId::SubSecTimeDigitized,			"SubSecTimeDigitized",			TypeId::ASCII,		},
	// G. Tags Relating to Picture-Taking Conditions
	{ TagId::ExposureTime,					"ExposureTime",					TypeId::RATIONAL,	},
	{ TagId::FNumber,						"FNumber",						TypeId::RATIONAL,	},
	{ TagId::ExposureProgram,				"ExposureProgram",				TypeId::SHORT,		},
	{ TagId::SpectralSensitivity,			"SpectralSensitivity",			TypeId::ASCII,		},
	{ TagId::ISOSpeedRatings,				"ISOSpeedRatings",				TypeId::SHORT,		},
	{ TagId::OECF,							"OECF",							TypeId::UNDEFINED,	},
	{ TagId::ShutterSpeedValue,				"ShutterSpeedValue",			TypeId::SRATIONAL,	},
	{ TagId::ApertureValue,					"ApertureValue",				TypeId::RATIONAL,	},
	{ TagId::BrightnessValue,				"BrightnessValue",				TypeId::SRATIONAL,	},
	{ TagId::ExposureBiasValue,				"ExposureBiasValue",			TypeId::SRATIONAL,	},
	{ TagId::MaxApertureValue,				"MaxApertureValue",				TypeId::RATIONAL,	},
	{ TagId::SubjectDistance,				"SubjectDistance",				TypeId::RATIONAL,	},
	{ TagId::MeteringMode,					"MeteringMode",					TypeId::SHORT,		},
	{ TagId::LightSource,					"LightSource",					TypeId::SHORT,		},
	{ TagId::Flash,							"Flash",						TypeId::SHORT,		},
	{ TagId::FocalLength,					"FocalLength",					TypeId::RATIONAL,	},
	{ TagId::SubjectArea,					"SubjectArea",					TypeId::SHORT,		},
	{ TagId::FlashEnergy,					"FlashEnergy",					TypeId::RATIONAL,	},
	{ TagId::SpatialFrequencyResponse,		"SpatialFrequencyResponse",		TypeId::UNDEFINED,	},
	{ TagId::FocalPlaneXResolution,			"FocalPlaneXResolution",		TypeId::RATIONAL,	},
	{ TagId::FocalPlaneYResolution,			"FocalPlaneYResolution",		TypeId::RATIONAL,	},
	{ TagId::FocalPlaneResolutionUnit,		"FocalPlaneResolutionUnit",		TypeId::SHORT,		},
	{ TagId::SubjectLocation,				"SubjectLocation",				TypeId::SHORT,		},
	{ TagId::ExposureIndex,					"ExposureIndex",				TypeId::RATIONAL,	},
	{ TagId::SensingMethod,					"SensingMethod",				TypeId::SHORT,		},
	{ TagId::FileSource,					"FileSource",					TypeId::UNDEFINED,	},
	{ TagId::SceneType,						"SceneType",					TypeId::UNDEFINED,	},
	{ TagId::CFAPattern,					"CFAPattern",					TypeId::UNDEFINED,	},
	{ TagId::CustomRendered,				"CustomRendered",				TypeId::SHORT,		},
	{ TagId::ExposureMode,					"ExposureMode",					TypeId::SHORT,		},
	{ TagId::WhiteBalance,					"WhiteBalance",					TypeId::SHORT,		},
	{ TagId::DigitalZoomRatio,				"DigitalZoomRatio",				TypeId::RATIONAL,	},
	{ TagId::FocalLengthIn35mmFilm,			"FocalLengthIn35mmFilm",		TypeId::SHORT,		},
	{ TagId::SceneCaptureType,				"SceneCaptureType",				TypeId::SHORT,		},
	{ TagId::GainControl,					"GainControl",					TypeId::RATIONAL,	},
	{ TagId::Contrast,						"Contrast",						TypeId::SHORT,		},
	{ TagId::Saturation,					"Saturation",					TypeId::SHORT,		},
	{ TagId::Sharpness,						"Sharpness",					TypeId::SHORT,		},
	{ TagId::DeviceSettingDescription,		"DeviceSettingDescription",		TypeId::UNDEFINED,	},
	{ TagId::SubjectDistanceRange,			"SubjectDistanceRange",			TypeId::SHORT,		},
	// H. Other Tags
	{ TagId::ImageUniqueID,					"ImageUniqueID",				TypeId::ASCII,		},
	// Pointers
	{ TagId::InteroperabilityIFDPointer,	"Interoperability",				TypeId::IFD,		},
};

// 4.6.6 GPS Attribute Information
static const TagInfo g_tagInfoTbl_GPSInfo[] = {
	// A. Tags Relating to GPS
	{ TagId::GPSVersionID,					"GPSVersionID",					TypeId::BYTE,		},
	{ TagId::GPSLatitudeRef,				"GPSLatitudeRef",				TypeId::ASCII,		},
	{ TagId::GPSLatitude,					"GPSLatitude",					TypeId::RATIONAL,	},
	{ TagId::GPSLongitudeRef,				"GPSLongitudeRef",				TypeId::ASCII,		},
	{ TagId::GPSLongitude,					"GPSLongitude",					TypeId::RATIONAL,	},
	{ TagId::GPSAltitudeRef,				"GPSAltitudeRef",				TypeId::BYTE,		},
	{ TagId::GPSAltitude,					"GPSAltitude",					TypeId::RATIONAL,	},
	{ TagId::GPSTimeStamp,					"GPSTimeStamp",					TypeId::RATIONAL,	},
	{ TagId::GPSSatellites,					"GPSSatellites",				TypeId::ASCII,		},
	{ TagId::GPSStatus,						"GPSStatus",					TypeId::ASCII,		},
	{ TagId::GPSMeasureMode,				"GPSMeasureMode",				TypeId::ASCII,		},
	{ TagId::GPSDOP,						"GPSDOP",						TypeId::RATIONAL,	},
	{ TagId::GPSSpeedRef,					"GPSSpeedRef",					TypeId::ASCII,		},
	{ TagId::GPSSpeed,						"GPSSpeed",						TypeId::RATIONAL,	},
	{ TagId::GPSTrackRef,					"GPSTrackRef",					TypeId::ASCII,		},
	{ TagId::GPSTrack,						"GPSTrack",						TypeId::RATIONAL,	},
	{ TagId::GPSImgDirectionRef,			"GPSImgDirectionRef",			TypeId::ASCII,		},
	{ TagId::GPSImgDirection,				"GPSImgDirection",				TypeId::RATIONAL,	},
	{ TagId::GPSMapDatum,					"GPSMapDatum",					TypeId::ASCII,		},
	{ TagId::GPSDestLatitudeRef,			"GPSDestLatitudeRef",			TypeId::ASCII,		},
	{ TagId::GPSDestLatitude,				"GPSDestLatitude",				TypeId::RATIONAL,	},
	{ TagId::GPSDestLongitudeRef,			"GPSDestLongitudeRef",			TypeId::ASCII,		},
	{ TagId::GPSDestLongitude,				"GPSDestLongitude",				TypeId::RATIONAL,	},
	{ TagId::GPSBearingRef,					"GPSBearingRef",				TypeId::ASCII,		},
	{ TagId::GPSBearing,					"GPSBearing",					TypeId::RATIONAL,	},
	{ TagId::GPSDestDistanceRef,			"GPSDestDistanceRef",			TypeId::ASCII,		},
	{ TagId::GPSDestDistance,				"GPSDestDistance",				TypeId::RATIONAL,	},
	{ TagId::GPSProcessingMethod,			"GPSProcessingMethod",			TypeId::UNDEFINED,	},
	{ TagId::GPSAreaInformation,			"GPSAreaInformation",			TypeId::UNDEFINED,	},
	{ TagId::GPSDateStamp,					"GPSDateStamp",					TypeId::ASCII,		},
	{ TagId::GPSDifferential,				"GPSDifferential",				TypeId::SHORT,		},
};

// 4.6.7 Interoperability IFD Attribute Information
static const TagInfo g_tagInfoTbl_Interoperability[] = {
	{ TagId::InteroperabilityIndex,			"InteroperabilityIndex",		TypeId::ASCII,		},
	{ TagId::InteroperabilityVersion,		"InteroperabilityVersion",		TypeId::BYTE,		},
	{ TagId::RelatedImageWidth,				"RelatedImageWidth",			TypeId::SHORT,		},
	{ TagId::RelatedImageHeight,			"RelatedImageHeight",			TypeId::SHORT,		},
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
	g_tagInfoMapByTagId.Register(
		g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapByTagId.Register(
		g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapByTagId.Register(
		g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapByTagId.Register(
		g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapByTagId_TIFF.Register(
		g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapByTagId_Exif.Register(
		g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapByTagId_GPSInfo.Register(
		g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapByTagId_Interoperability.Register(
		g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapBySymbol.Register(
		g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapBySymbol.Register(
		g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapBySymbol.Register(
		g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapBySymbol.Register(
		g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
	g_tagInfoMapBySymbol_TIFF.Register(
		g_tagInfoTbl_TIFF, Gurax_ArraySizeOf(g_tagInfoTbl_TIFF));
	g_tagInfoMapBySymbol_Exif.Register(
		g_tagInfoTbl_Exif, Gurax_ArraySizeOf(g_tagInfoTbl_Exif));
	g_tagInfoMapBySymbol_GPSInfo.Register(
		g_tagInfoTbl_GPSInfo, Gurax_ArraySizeOf(g_tagInfoTbl_GPSInfo));
	g_tagInfoMapBySymbol_Interoperability.Register(
		g_tagInfoTbl_Interoperability, Gurax_ArraySizeOf(g_tagInfoTbl_Interoperability));
}

const TagInfo* TagInfo::LookupByTagId(UInt16 tagId)
{
	return g_tagInfoMapByTagId.Lookup(tagId);
}

const TagInfo* TagInfo::LookupByTagId(const Symbol* pSymbolOfIFD, UInt16 tagId)
{
	return
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd0))?
			g_tagInfoMapByTagId_TIFF.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd1))?
			g_tagInfoMapByTagId_TIFF.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Exif))?
			g_tagInfoMapByTagId_Exif.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Interoperability))?
			g_tagInfoMapByTagId_Interoperability.Lookup(tagId) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(GPSInfo))?
			g_tagInfoMapByTagId_GPSInfo.Lookup(tagId) :
		nullptr;
}

const TagInfo* TagInfo::LookupBySymbol(const Symbol* pSymbol)
{
	return g_tagInfoMapBySymbol.Lookup(pSymbol);
}

const TagInfo* TagInfo::LookupBySymbol(const Symbol* pSymbolOfIFD, const Symbol* pSymbol)
{
	return
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd0))?
			g_tagInfoMapBySymbol_TIFF.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(ifd1))?
			g_tagInfoMapBySymbol_TIFF.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Exif))?
			g_tagInfoMapBySymbol_Exif.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Interoperability))?
			g_tagInfoMapBySymbol_Interoperability.Lookup(pSymbol) :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(GPSInfo))?
			g_tagInfoMapBySymbol_GPSInfo.Lookup(pSymbol) :
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
