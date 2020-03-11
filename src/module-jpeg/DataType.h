//==============================================================================
// DataType.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_DATATYPE_H
#define GURAX_MODULE_JPEG_DATATYPE_H
#include <gurax.h>
#include "Symbol.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Marker
//------------------------------------------------------------------------------
struct Marker {
	static const UInt16 None	= 0x0000;
	static const UInt16 SOF0	= 0xffc0;
	static const UInt16 SOF1	= 0xffc1;
	static const UInt16 SOF2	= 0xffc2;
	static const UInt16 SOF3	= 0xffc3;
	static const UInt16 SOF4	= 0xffc4;
	static const UInt16 SOF5	= 0xffc5;
	static const UInt16 SOF6	= 0xffc6;
	static const UInt16 SOF7	= 0xffc7;
	static const UInt16 SOF8	= 0xffc8;
	static const UInt16 SOF9	= 0xffc9;
	static const UInt16 SOF10	= 0xffca;
	static const UInt16 SOF11	= 0xffcb;
	static const UInt16 SOF12	= 0xffcc;
	static const UInt16 SOF13	= 0xffcd;
	static const UInt16 SOF14	= 0xffce;
	static const UInt16 SOF15	= 0xffcf;
	static const UInt16 SOI		= 0xffd8;
	static const UInt16 DHT		= 0xffd4;
	static const UInt16 SOS		= 0xffda;
	static const UInt16 DQT		= 0xffdb;
	static const UInt16 DRI		= 0xffdd;
	static const UInt16 APP0	= 0xffe0;	// JFIF
	static const UInt16 APP1	= 0xffe1;	// Exif
	static const UInt16 APP2	= 0xffe2;	// ICC Profile
	static const UInt16 APP3	= 0xffe3;
	static const UInt16 APP4	= 0xffe4;
	static const UInt16 APP5	= 0xffe5;
	static const UInt16 APP6	= 0xffe6;
	static const UInt16 APP7	= 0xffe7;
	static const UInt16 APP8	= 0xffe8;
	static const UInt16 APP9	= 0xffe9;
	static const UInt16 APP10	= 0xffea;
	static const UInt16 APP11	= 0xffeb;
	static const UInt16 APP12	= 0xffec;
	static const UInt16 APP13	= 0xffed;
	static const UInt16 APP14	= 0xffee;	// Adobe
	static const UInt16 APP15	= 0xffef;
	static const UInt16 COM		= 0xfffe;
};

class SymbolAssoc_Marker : public SymbolAssoc<UInt16, Marker::None> {
public:
	SymbolAssoc_Marker() {
		Assoc(Gurax_Symbol(SOF0),	Marker::SOF0);
		Assoc(Gurax_Symbol(SOF1),	Marker::SOF1);
		Assoc(Gurax_Symbol(SOF2),	Marker::SOF2);
		Assoc(Gurax_Symbol(SOF3),	Marker::SOF3);
		Assoc(Gurax_Symbol(SOF4),	Marker::SOF4);
		Assoc(Gurax_Symbol(SOF5),	Marker::SOF5);
		Assoc(Gurax_Symbol(SOF6),	Marker::SOF6);
		Assoc(Gurax_Symbol(SOF7),	Marker::SOF7);
		Assoc(Gurax_Symbol(SOF8),	Marker::SOF8);
		Assoc(Gurax_Symbol(SOF9),	Marker::SOF9);
		Assoc(Gurax_Symbol(SOF10),	Marker::SOF10);
		Assoc(Gurax_Symbol(SOF11),	Marker::SOF11);
		Assoc(Gurax_Symbol(SOF12),	Marker::SOF12);
		Assoc(Gurax_Symbol(SOF13),	Marker::SOF13);
		Assoc(Gurax_Symbol(SOF14),	Marker::SOF14);
		Assoc(Gurax_Symbol(SOF15),	Marker::SOF15);
		Assoc(Gurax_Symbol(SOI),	Marker::SOI);
		Assoc(Gurax_Symbol(DHT),	Marker::DHT);
		Assoc(Gurax_Symbol(SOS),	Marker::SOS);
		Assoc(Gurax_Symbol(DQT),	Marker::DQT);
		Assoc(Gurax_Symbol(DRI),	Marker::DRI);
		Assoc(Gurax_Symbol(APP0),	Marker::APP0);
		Assoc(Gurax_Symbol(APP1),	Marker::APP1);
		Assoc(Gurax_Symbol(APP2),	Marker::APP2);
		Assoc(Gurax_Symbol(APP3),	Marker::APP3);
		Assoc(Gurax_Symbol(APP4),	Marker::APP4);
		Assoc(Gurax_Symbol(APP5),	Marker::APP5);
		Assoc(Gurax_Symbol(APP6),	Marker::APP6);
		Assoc(Gurax_Symbol(APP7),	Marker::APP7);
		Assoc(Gurax_Symbol(APP8),	Marker::APP8);
		Assoc(Gurax_Symbol(APP9),	Marker::APP9);
		Assoc(Gurax_Symbol(APP10),	Marker::APP10);
		Assoc(Gurax_Symbol(APP11),	Marker::APP11);
		Assoc(Gurax_Symbol(APP12),	Marker::APP12);
		Assoc(Gurax_Symbol(APP13),	Marker::APP13);
		Assoc(Gurax_Symbol(APP14),	Marker::APP14);
		Assoc(Gurax_Symbol(APP15),	Marker::APP15);
		Assoc(Gurax_Symbol(COM),	Marker::COM);
	}
	static const SymbolAssoc& GetInstance() {
		static SymbolAssoc* pSymbolAssoc = nullptr;
		return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Marker());
	}
};

inline UInt16 SymbolToMarker(const Symbol* pSymbol)
{
	return SymbolAssoc_Marker::GetInstance().ToAssociated(pSymbol);
}

inline const Symbol* MarkerToSymbol(UInt16 marker)
{
	return SymbolAssoc_Marker::GetInstance().ToSymbol(marker);
}

//------------------------------------------------------------------------------
// Type
//------------------------------------------------------------------------------
struct Type {
	static const UInt8 BYTE			= 1;
	static const UInt8 ASCII		= 2;
	static const UInt8 SHORT		= 3;
	static const UInt8 LONG			= 4;
	static const UInt8 RATIONAL		= 5;
	static const UInt8 UNDEFINED	= 7;
	static const UInt8 SLONG		= 9;
	static const UInt8 SRATIONAL	= 10;
};

//------------------------------------------------------------------------------
// UnitSize
//------------------------------------------------------------------------------
struct UnitSize {
	static const UInt8 BYTE			= 1;
	static const UInt8 ASCII		= 1;
	static const UInt8 SHORT		= 2;
	static const UInt8 LONG			= 4;
	static const UInt8 RATIONAL		= 8;
	static const UInt8 UNDEFINED	= 0;
	static const UInt8 SLONG		= 4;
	static const UInt8 SRATIONAL	= 8;
};

//------------------------------------------------------------------------------
// TagId
//------------------------------------------------------------------------------
struct TagId {
	static const UInt16 invalid						= 0xffff;
	// 4.6.3 Exif-specific IFD
	// Pointers
	static const UInt16 ExifIFDPointer				= 0x8769;
	static const UInt16 GPSInfoIFDPointer			= 0x8825;
	static const UInt16 InteroperabilityIFDPointer	= 0xa005;
	// 4.6.4 TIFF Rev.6.0 Attribute Information
	// A. Tags relating to image data structure
	static const UInt16 ImageWidth					= 0x0100;
	static const UInt16 ImageLength					= 0x0101;
	static const UInt16 BitsPerSample				= 0x0102;
	static const UInt16 Compression					= 0x0103;
	static const UInt16 PhotometricInterpretation	= 0x0106;
	static const UInt16 Orientation					= 0x0112;
	static const UInt16 SamplesPerPixel				= 0x0115;
	static const UInt16 PlanarConfiguration			= 0x011c;
	static const UInt16 YCbCrSubSampling			= 0x0212;
	static const UInt16 YCbCrPositioning			= 0x0213;
	static const UInt16 XResolution					= 0x011a;
	static const UInt16 YResolution					= 0x011b;
	static const UInt16 ResolutionUnit				= 0x0128;
	// B. Tags relating to recording offset
	static const UInt16 StripOffsets				= 0x0111;
	static const UInt16 RowsPerStrip				= 0x0116;
	static const UInt16 StripByteCounts				= 0x0117;
	static const UInt16 JPEGInterchangeFormat		= 0x0201;
	static const UInt16 JPEGInterchangeFormatLength	= 0x0202;
	// C. Tags relating to image data characteristics
	static const UInt16 TransferFunction			= 0x012d;
	static const UInt16 WhitePoint					= 0x013e;
	static const UInt16 PrimaryChromaticities		= 0x013f;
	static const UInt16 YCbCrCoefficients			= 0x0211;
	static const UInt16 ReferenceBlackWhite			= 0x0214;
	// D. Other tags
	static const UInt16 DateTime					= 0x0132;
	static const UInt16 ImageDescription			= 0x010e;
	static const UInt16 Make						= 0x010f;
	static const UInt16 Model						= 0x0110;
	static const UInt16 Software					= 0x0131;
	static const UInt16 Artist						= 0x013b;
	static const UInt16 Copyright					= 0x8298;
	// 4.6.5 Exif IFD Attribute Information
	// A. Tags Relating to Version
	static const UInt16 ExifVersion					= 0x9000;
	static const UInt16 FlashPixVersion				= 0xa000;
	// B. Tag Relating to Image Data Characteristics
	static const UInt16 ColorSpace					= 0xa001;
	// C. Tags Relating to Image Configuration
	static const UInt16 ComponentsConfiguration		= 0x9101;
	static const UInt16 CompressedBitsPerPixel		= 0x9102;
	static const UInt16 PixelXDimension				= 0xa002;
	static const UInt16 PixelYDimension				= 0xa003;
	// D. Tags Relating to User Information
	static const UInt16 MakerNote					= 0x927c;
	static const UInt16 UserComment					= 0x9286;
	// E. Tags Relating to Related File Information
	static const UInt16 RelatedSoundFile			= 0xa004;
	// F. Tags Relating to Date and Time
	static const UInt16 DateTimeOriginal			= 0x9003;
	static const UInt16 DateTimeDigitized			= 0x9004;
	static const UInt16 SubSecTime					= 0x9290;
	static const UInt16 SubSecTimeOriginal			= 0x9291;
	static const UInt16 SubSecTimeDigitized			= 0x9292;
	// G. Tags Relating to Picture-Taking Conditions
	static const UInt16 ExposureTime				= 0x829a;
	static const UInt16 FNumber						= 0x829d;
	static const UInt16 ExposureProgram				= 0x8822;
	static const UInt16 SpectralSensitivity			= 0x8824;
	static const UInt16 ISOSpeedRatings				= 0x8827;
	static const UInt16 OECF						= 0x8828;
	static const UInt16 ShutterSpeedValue			= 0x9201;
	static const UInt16 ApertureValue				= 0x9202;
	static const UInt16 BrightnessValue				= 0x9203;
	static const UInt16 ExposureBiasValue			= 0x9204;
	static const UInt16 MaxApertureValue			= 0x9205;
	static const UInt16 SubjectDistance				= 0x9206;
	static const UInt16 MeteringMode				= 0x9207;
	static const UInt16 LightSource					= 0x9208;
	static const UInt16 Flash						= 0x9209;
	static const UInt16 FocalLength					= 0x920a;
	static const UInt16 SubjectArea					= 0x9214;
	static const UInt16 FlashEnergy					= 0xa20b;
	static const UInt16 SpatialFrequencyResponse	= 0xa20c;
	static const UInt16 FocalPlaneXResolution		= 0xa20e;
	static const UInt16 FocalPlaneYResolution		= 0xa20f;
	static const UInt16 FocalPlaneResolutionUnit	= 0xa210;
	static const UInt16 SubjectLocation				= 0xa214;
	static const UInt16 ExposureIndex				= 0xa215;
	static const UInt16 SensingMethod				= 0xa217;
	static const UInt16 FileSource					= 0xa300;
	static const UInt16 SceneType					= 0xa301;
	static const UInt16 CFAPattern					= 0xa302;
	static const UInt16 CustomRendered				= 0xa401;
	static const UInt16 ExposureMode				= 0xa402;
	static const UInt16 WhiteBalance				= 0xa403;
	static const UInt16 DigitalZoomRatio			= 0xa404;
	static const UInt16 FocalLengthIn35mmFilm		= 0xa405;
	static const UInt16 SceneCaptureType 			= 0xa406;
	static const UInt16 GainControl					= 0xa407;
	static const UInt16 Contrast					= 0xa408;
	static const UInt16 Saturation					= 0xa409;
	static const UInt16 Sharpness					= 0xa40a;
	static const UInt16 DeviceSettingDescription	= 0xa40b;
	static const UInt16 SubjectDistanceRange		= 0xa40c;
	// H. Other Tags
	static const UInt16 ImageUniqueID				= 0xa420;
	// 4.6.6 GPS Attribute Information
	// A. Tags Relating to GPS
	static const UInt16 GPSVersionID				= 0x0000;
	static const UInt16 GPSLatitudeRef				= 0x0001;
	static const UInt16 GPSLatitude					= 0x0002;
	static const UInt16 GPSLongitudeRef				= 0x0003;
	static const UInt16 GPSLongitude				= 0x0004;
	static const UInt16 GPSAltitudeRef				= 0x0005;
	static const UInt16 GPSAltitude					= 0x0006;
	static const UInt16 GPSTimeStamp				= 0x0007;
	static const UInt16 GPSSatellites				= 0x0008;
	static const UInt16 GPSStatus					= 0x0009;
	static const UInt16 GPSMeasureMode				= 0x000a;
	static const UInt16 GPSDOP						= 0x000b;
	static const UInt16 GPSSpeedRef					= 0x000c;
	static const UInt16 GPSSpeed					= 0x000d;
	static const UInt16 GPSTrackRef					= 0x000e;
	static const UInt16 GPSTrack					= 0x000f;
	static const UInt16 GPSImgDirectionRef			= 0x0010;
	static const UInt16 GPSImgDirection				= 0x0011;
	static const UInt16 GPSMapDatum					= 0x0012;
	static const UInt16 GPSDestLatitudeRef			= 0x0013;
	static const UInt16 GPSDestLatitude				= 0x0014;
	static const UInt16 GPSDestLongitudeRef			= 0x0015;
	static const UInt16 GPSDestLongitude			= 0x0016;
	static const UInt16 GPSBearingRef				= 0x0017;
	static const UInt16 GPSBearing					= 0x0018;
	static const UInt16 GPSDestDistanceRef			= 0x0019;
	static const UInt16 GPSDestDistance				= 0x001a;
	static const UInt16 GPSProcessingMethod			= 0x001b;
	static const UInt16 GPSAreaInformation			= 0x001c;
	static const UInt16 GPSDateStamp				= 0x001d;
	static const UInt16 GPSDifferential				= 0x001e;
	// 4.6.7 Interoperability IFD Attribute Information
	static const UInt16 InteroperabilityIndex		= 0x0001;
	static const UInt16 InteroperabilityVersion		= 0x0002;
	static const UInt16 RelatedImageWidth			= 0x1001;
	static const UInt16 RelatedImageHeight			= 0x1002;
};

//------------------------------------------------------------------------------
// TIFF_BE
//------------------------------------------------------------------------------
struct TIFF_BE {
	Gurax_PackedUInt16_BE(Code);
	Gurax_PackedUInt32_BE(Offset0thIFD);
};

//------------------------------------------------------------------------------
// TIFF_LE
//------------------------------------------------------------------------------
struct TIFF_LE {
	Gurax_PackedUInt16_LE(Code);
	Gurax_PackedUInt32_LE(Offset0thIFD);
};

//------------------------------------------------------------------------------
// IFDHeader_BE
//------------------------------------------------------------------------------
struct IFDHeader_BE {
	Gurax_PackedUInt16_BE(TagCount);
};

//------------------------------------------------------------------------------
// IFDHeader_LE
//------------------------------------------------------------------------------
struct IFDHeader_LE {
	Gurax_PackedUInt16_LE(TagCount);
};

//------------------------------------------------------------------------------
// RATIONAL_BE
//------------------------------------------------------------------------------
struct RATIONAL_BE {
	Gurax_PackedUInt32_BE(numerator);
	Gurax_PackedUInt32_BE(denominator);
};

//------------------------------------------------------------------------------
// RATIONAL_LE
//------------------------------------------------------------------------------
struct RATIONAL_LE {
	Gurax_PackedUInt32_LE(numerator);
	Gurax_PackedUInt32_LE(denominator);
};

//------------------------------------------------------------------------------
// SRATIONAL_BE
//------------------------------------------------------------------------------
struct SRATIONAL_BE {
	Gurax_PackedUInt32_BE(numerator);
	Gurax_PackedUInt32_BE(denominator);
};

//------------------------------------------------------------------------------
// SRATIONAL_LE
//------------------------------------------------------------------------------
struct SRATIONAL_LE {
	Gurax_PackedUInt32_LE(numerator);
	Gurax_PackedUInt32_LE(denominator);
};

//------------------------------------------------------------------------------
// SHORT_BE
//------------------------------------------------------------------------------
struct SHORT_BE {
	Gurax_PackedUInt16_BE(num);
};

//------------------------------------------------------------------------------
// SHORT_LE
//------------------------------------------------------------------------------
struct SHORT_LE {
	Gurax_PackedUInt16_LE(num);
};

//------------------------------------------------------------------------------
// LONG_BE
//------------------------------------------------------------------------------
struct LONG_BE {
	Gurax_PackedUInt32_BE(num);
};

//------------------------------------------------------------------------------
// LONG_LE
//------------------------------------------------------------------------------
struct LONG_LE {
	Gurax_PackedUInt32_LE(num);
};

//------------------------------------------------------------------------------
// SLONG_BE
//------------------------------------------------------------------------------
struct SLONG_BE {
	Gurax_PackedUInt32_BE(num);
};

//------------------------------------------------------------------------------
// SLONG_LE
//------------------------------------------------------------------------------
struct SLONG_LE {
	Gurax_PackedUInt32_LE(num);
};

//------------------------------------------------------------------------------
// ValueRaw_BE
//------------------------------------------------------------------------------
union ValueRaw_BE {
	char BYTE[4];
	char ASCII[4];
	struct {
		Gurax_PackedUInt16_BE(num);
		Gurax_PackedUInt16_BE(second);
	} SHORT;
	struct {
		Gurax_PackedUInt32_BE(num);
	} LONG;
	struct {
		Gurax_PackedUInt32_BE(num);
	} SLONG;
};

//------------------------------------------------------------------------------
// TagRaw_BE
//------------------------------------------------------------------------------
struct TagRaw_BE {
	Gurax_PackedUInt16_BE(Id);
	Gurax_PackedUInt16_BE(Type);
	Gurax_PackedUInt32_BE(Count);
	UChar ValueRaw;
};

//------------------------------------------------------------------------------
// ValueRaw_LE
//------------------------------------------------------------------------------
union ValueRaw_LE {
	char BYTE[4];
	char ASCII[4];
	struct {
		Gurax_PackedUInt16_LE(num);
		Gurax_PackedUInt16_LE(second);
	} SHORT;
	struct {
		Gurax_PackedUInt32_LE(num);
	} LONG;
	struct {
		Gurax_PackedUInt32_LE(num);
	} SLONG;
};

//------------------------------------------------------------------------------
// TagRaw_LE
//------------------------------------------------------------------------------
struct TagRaw_LE {
	Gurax_PackedUInt16_LE(Id);
	Gurax_PackedUInt16_LE(Type);
	Gurax_PackedUInt32_LE(Count);
	UChar ValueRaw;
};

//------------------------------------------------------------------------------
// TagInfo
//------------------------------------------------------------------------------
struct TagInfo {
	UInt16 id;
	const char* name;
	UInt16 type;
	const char* nameForIFD;
};

//------------------------------------------------------------------------------
// TypeInfo
//------------------------------------------------------------------------------
struct TypeInfo {
	UInt16 type;
	const char *name;
	size_t unitSize;
};

Gurax_EndModuleScope(jpeg)

#endif
