//==============================================================================
// DataType.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// TagInfo
//------------------------------------------------------------------------------
// 4.6.4 TIFF Rev.6.0 Attribute Information
const TagInfo TagInfo::Tbl_TIFF[] = {
	// A. Tags relating to image data structure
	{ TagId::ImageWidth,					"ImageWidth",					TypeId::LONG,		nullptr,	},
	{ TagId::ImageLength,					"ImageLength",					TypeId::LONG,		nullptr,	},
	{ TagId::BitsPerSample,					"BitsPerSample",				TypeId::SHORT,		nullptr,	},
	{ TagId::Compression,					"Compression",					TypeId::SHORT,		nullptr,	},
	{ TagId::PhotometricInterpretation,		"PhotometricInterpretation",	TypeId::SHORT,		nullptr,	},
	{ TagId::Orientation,					"Orientation",					TypeId::SHORT,		nullptr,	},
	{ TagId::SamplesPerPixel,				"SamplesPerPixel",				TypeId::SHORT,		nullptr,	},
	{ TagId::PlanarConfiguration,			"PlanarConfiguration",			TypeId::SHORT,		nullptr,	},
	{ TagId::YCbCrSubSampling,				"YCbCrSubSampling",				TypeId::SHORT,		nullptr,	},
	{ TagId::YCbCrPositioning,				"YCbCrPositioning",				TypeId::SHORT,		nullptr,	},
	{ TagId::XResolution,					"XResolution",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::YResolution,					"YResolution",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::ResolutionUnit,				"ResolutionUnit",				TypeId::SHORT,		nullptr,	},
	// B. Tags relating to recording offset
	{ TagId::StripOffsets,					"StripOffsets",					TypeId::LONG,		nullptr,	},
	{ TagId::RowsPerStrip,					"RowsPerStrip",					TypeId::LONG,		nullptr,	},
	{ TagId::StripByteCounts,				"StripByteCounts",				TypeId::LONG,		nullptr,	},
	{ TagId::JPEGInterchangeFormat,			"JPEGInterchangeFormat",		TypeId::LONG,		nullptr,	},
	{ TagId::JPEGInterchangeFormatLength,	"JPEGInterchangeFormatLength",	TypeId::LONG,		nullptr,	},
	// C. Tags relating to image data characteristics
	{ TagId::TransferFunction,				"TransferFunction",				TypeId::SHORT,		nullptr,	},
	{ TagId::WhitePoint,					"WhitePoint",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::PrimaryChromaticities,			"PrimaryChromaticities",		TypeId::RATIONAL,	nullptr,	},
	{ TagId::YCbCrCoefficients,				"YCbCrCoefficients",			TypeId::RATIONAL,	nullptr,	},
	{ TagId::ReferenceBlackWhite,			"ReferenceBlackWhite",			TypeId::RATIONAL,	nullptr,	},
	// D. Other tags
	{ TagId::DateTime,						"DateTime",						TypeId::ASCII,		nullptr,	},
	{ TagId::ImageDescription,				"ImageDescription",				TypeId::ASCII,		nullptr,	},
	{ TagId::Make,							"Make",							TypeId::ASCII,		nullptr,	},
	{ TagId::Model,							"Model",						TypeId::ASCII,		nullptr,	},
	{ TagId::Software,						"Software",						TypeId::ASCII,		nullptr,	},
	{ TagId::Artist,						"Artist",						TypeId::ASCII,		nullptr,	},
	{ TagId::Copyright,						"Copyright",					TypeId::ASCII,		nullptr,	},
	// Pointers
	{ TagId::ExifIFDPointer,				"ExifIFDPointer",				TypeId::LONG,		"Exif",		},
	{ TagId::GPSInfoIFDPointer,				"GPSInfoIFDPointer",			TypeId::LONG,		"GPSInfo",	},
	{ TagId::invalid,						nullptr,						TypeId::UNDEFINED,	nullptr,	},
};

// 4.6.5 Exif IFD Attribute Information
const TagInfo TagInfo::Tbl_Exif[] = {
	// A. Tags Relating to Version
	{ TagId::ExifVersion,					"ExifVersion",					TypeId::UNDEFINED,	nullptr,	},
	{ TagId::FlashPixVersion,				"FlashPixVersion",				TypeId::UNDEFINED,	nullptr,	},
	// B. Tag Relating to Image Data Characteristics
	{ TagId::ColorSpace,					"ColorSpace",					TypeId::SHORT,		nullptr,	},
	// C. Tags Relating to Image Configuration
	{ TagId::ComponentsConfiguration,		"ComponentsConfiguration",		TypeId::UNDEFINED,	nullptr,	},
	{ TagId::CompressedBitsPerPixel,		"CompressedBitsPerPixel",		TypeId::RATIONAL,	nullptr,	},
	{ TagId::PixelXDimension,				"PixelXDimension",				TypeId::LONG,		nullptr,	},
	{ TagId::PixelYDimension,				"PixelYDimension",				TypeId::LONG,		nullptr,	},
	// D. Tags Relating to User Information
	{ TagId::MakerNote,						"MakerNote",					TypeId::UNDEFINED,	nullptr,	},
	{ TagId::UserComment,					"UserComment",					TypeId::UNDEFINED,	nullptr,	},
	// E. Tags Relating to Related File Information
	{ TagId::RelatedSoundFile,				"RelatedSoundFile",				TypeId::ASCII,		nullptr,	},
	// F. Tags Relating to Date and Time
	{ TagId::DateTimeOriginal,				"DateTimeOriginal",				TypeId::ASCII,		nullptr,	},
	{ TagId::DateTimeDigitized,				"DateTimeDigitized",			TypeId::ASCII,		nullptr,	},
	{ TagId::SubSecTime,					"SubSecTime",					TypeId::ASCII,		nullptr,	},
	{ TagId::SubSecTimeOriginal,			"SubSecTimeOriginal",			TypeId::ASCII,		nullptr,	},
	{ TagId::SubSecTimeDigitized,			"SubSecTimeDigitized",			TypeId::ASCII,		nullptr,	},
	// G. Tags Relating to Picture-Taking Conditions
	{ TagId::ExposureTime,					"ExposureTime",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::FNumber,						"FNumber",						TypeId::RATIONAL,	nullptr,	},
	{ TagId::ExposureProgram,				"ExposureProgram",				TypeId::SHORT,		nullptr,	},
	{ TagId::SpectralSensitivity,			"SpectralSensitivity",			TypeId::ASCII,		nullptr,	},
	{ TagId::ISOSpeedRatings,				"ISOSpeedRatings",				TypeId::SHORT,		nullptr,	},
	{ TagId::OECF,							"OECF",							TypeId::UNDEFINED,	nullptr,	},
	{ TagId::ShutterSpeedValue,				"ShutterSpeedValue",			TypeId::SRATIONAL,	nullptr,	},
	{ TagId::ApertureValue,					"ApertureValue",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::BrightnessValue,				"BrightnessValue",				TypeId::SRATIONAL,	nullptr,	},
	{ TagId::ExposureBiasValue,				"ExposureBiasValue",			TypeId::SRATIONAL,	nullptr,	},
	{ TagId::MaxApertureValue,				"MaxApertureValue",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::SubjectDistance,				"SubjectDistance",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::MeteringMode,					"MeteringMode",					TypeId::SHORT,		nullptr,	},
	{ TagId::LightSource,					"LightSource",					TypeId::SHORT,		nullptr,	},
	{ TagId::Flash,							"Flash",						TypeId::SHORT,		nullptr,	},
	{ TagId::FocalLength,					"FocalLength",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::SubjectArea,					"SubjectArea",					TypeId::SHORT,		nullptr,	},
	{ TagId::FlashEnergy,					"FlashEnergy",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::SpatialFrequencyResponse,		"SpatialFrequencyResponse",		TypeId::UNDEFINED,	nullptr,	},
	{ TagId::FocalPlaneXResolution,			"FocalPlaneXResolution",		TypeId::RATIONAL,	nullptr,	},
	{ TagId::FocalPlaneYResolution,			"FocalPlaneYResolution",		TypeId::RATIONAL,	nullptr,	},
	{ TagId::FocalPlaneResolutionUnit,		"FocalPlaneResolutionUnit",		TypeId::SHORT,		nullptr,	},
	{ TagId::SubjectLocation,				"SubjectLocation",				TypeId::SHORT,		nullptr,	},
	{ TagId::ExposureIndex,					"ExposureIndex",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::SensingMethod,					"SensingMethod",				TypeId::SHORT,		nullptr,	},
	{ TagId::FileSource,					"FileSource",					TypeId::UNDEFINED,	nullptr,	},
	{ TagId::SceneType,						"SceneType",					TypeId::UNDEFINED,	nullptr,	},
	{ TagId::CFAPattern,					"CFAPattern",					TypeId::UNDEFINED,	nullptr,	},
	{ TagId::CustomRendered,				"CustomRendered",				TypeId::SHORT,		nullptr,	},
	{ TagId::ExposureMode,					"ExposureMode",					TypeId::SHORT,		nullptr,	},
	{ TagId::WhiteBalance,					"WhiteBalance",					TypeId::SHORT,		nullptr,	},
	{ TagId::DigitalZoomRatio,				"DigitalZoomRatio",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::FocalLengthIn35mmFilm,			"FocalLengthIn35mmFilm",		TypeId::SHORT,		nullptr,	},
	{ TagId::SceneCaptureType,				"SceneCaptureType",				TypeId::SHORT,		nullptr,	},
	{ TagId::GainControl,					"GainControl",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::Contrast,						"Contrast",						TypeId::SHORT,		nullptr,	},
	{ TagId::Saturation,					"Saturation",					TypeId::SHORT,		nullptr,	},
	{ TagId::Sharpness,						"Sharpness",					TypeId::SHORT,		nullptr,	},
	{ TagId::DeviceSettingDescription,		"DeviceSettingDescription",		TypeId::UNDEFINED,	nullptr,	},
	{ TagId::SubjectDistanceRange,			"SubjectDistanceRange",			TypeId::SHORT,		nullptr,	},
	// H. Other Tags
	{ TagId::ImageUniqueID,					"ImageUniqueID",				TypeId::ASCII,		nullptr,	},
	// Pointers
	{ TagId::InteroperabilityIFDPointer,	"InteroperabilityIFDPointer",	TypeId::LONG,		"Interoperability"	},
	{ TagId::invalid,						nullptr,						TypeId::UNDEFINED,	nullptr,	},
};

// 4.6.6 GPS Attribute Information
const TagInfo TagInfo::Tbl_GPSInfo[] = {
	// A. Tags Relating to GPS
	{ TagId::GPSVersionID,					"GPSVersionID",					TypeId::BYTE,		nullptr,	},
	{ TagId::GPSLatitudeRef,				"GPSLatitudeRef",				TypeId::ASCII,		nullptr,	},
	{ TagId::GPSLatitude,					"GPSLatitude",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSLongitudeRef,				"GPSLongitudeRef",				TypeId::ASCII,		nullptr,	},
	{ TagId::GPSLongitude,					"GPSLongitude",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSAltitudeRef,				"GPSAltitudeRef",				TypeId::BYTE,		nullptr,	},
	{ TagId::GPSAltitude,					"GPSAltitude",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSTimeStamp,					"GPSTimeStamp",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSSatellites,					"GPSSatellites",				TypeId::ASCII,		nullptr,	},
	{ TagId::GPSStatus,						"GPSStatus",					TypeId::ASCII,		nullptr,	},
	{ TagId::GPSMeasureMode,				"GPSMeasureMode",				TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDOP,						"GPSDOP",						TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSSpeedRef,					"GPSSpeedRef",					TypeId::ASCII,		nullptr,	},
	{ TagId::GPSSpeed,						"GPSSpeed",						TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSTrackRef,					"GPSTrackRef",					TypeId::ASCII,		nullptr,	},
	{ TagId::GPSTrack,						"GPSTrack",						TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSImgDirectionRef,			"GPSImgDirectionRef",			TypeId::ASCII,		nullptr,	},
	{ TagId::GPSImgDirection,				"GPSImgDirection",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSMapDatum,					"GPSMapDatum",					TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDestLatitudeRef,			"GPSDestLatitudeRef",			TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDestLatitude,				"GPSDestLatitude",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSDestLongitudeRef,			"GPSDestLongitudeRef",			TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDestLongitude,				"GPSDestLongitude",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSBearingRef,					"GPSBearingRef",				TypeId::ASCII,		nullptr,	},
	{ TagId::GPSBearing,					"GPSBearing",					TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSDestDistanceRef,			"GPSDestDistanceRef",			TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDestDistance,				"GPSDestDistance",				TypeId::RATIONAL,	nullptr,	},
	{ TagId::GPSProcessingMethod,			"GPSProcessingMethod",			TypeId::UNDEFINED,	nullptr,	},
	{ TagId::GPSAreaInformation,			"GPSAreaInformation",			TypeId::UNDEFINED,	nullptr,	},
	{ TagId::GPSDateStamp,					"GPSDateStamp",					TypeId::ASCII,		nullptr,	},
	{ TagId::GPSDifferential,				"GPSDifferential",				TypeId::SHORT,		nullptr,	},
	{ TagId::invalid,						nullptr,						TypeId::UNDEFINED,	nullptr,	},
};

// 4.6.7 Interoperability IFD Attribute Information
const TagInfo TagInfo::Tbl_Interoperability[] = {
	{ TagId::InteroperabilityIndex,			"InteroperabilityIndex",		TypeId::ASCII,		nullptr,	},
	{ TagId::InteroperabilityVersion,		"InteroperabilityVersion",		TypeId::BYTE,		nullptr,	},
	{ TagId::RelatedImageWidth,				"RelatedImageWidth",			TypeId::SHORT,		nullptr,	},
	{ TagId::RelatedImageHeight,			"RelatedImageHeight",			TypeId::SHORT,		nullptr,	},
	{ TagId::invalid,						nullptr,						TypeId::UNDEFINED,	nullptr,	},
};

const TagInfo* TagInfo::LookupByTagId(const Symbol* pSymbolOfIFD, UInt16 tagId)
{
	const TagInfo *pTagInfo =
		!pSymbolOfIFD? Tbl_TIFF :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Exif))? Tbl_Exif :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(Interoperability))? Tbl_Interoperability :
		pSymbolOfIFD->IsIdentical(Gurax_Symbol(GPSInfo))? Tbl_GPSInfo : nullptr;
	if (!pTagInfo) return nullptr;
	for (int i = 0; pTagInfo->name != nullptr; i++, pTagInfo++) {
		if (pTagInfo->tagId == tagId) return pTagInfo;
	}
	return nullptr;
}

Gurax_EndModuleScope(jpeg)
