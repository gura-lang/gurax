//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_CONTENT_H
#define GURAX_MODULE_GIF_CONTENT_H
#include <gurax.h>

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("gif.Content");
public:
	struct Sep {
		static const UInt8 ImageDescriptor		= 0x2c;
		static const UInt8 ExtensionIntroducer	= 0x21;
		static const UInt8 Trailer				= 0x3b;
	};
	struct Header {
		char Signature[3];
		char Version[3];
		Header() {
			::memcpy(Signature, "GIF", 3);
			::memcpy(Version, "89a", 3);
		}
	};
	struct LogicalScreenDescriptor {
		Gurax_PackedUInt16_LE(LogicalScreenWidth);
		Gurax_PackedUInt16_LE(LogicalScreenHeight);
		UInt8 PackedFields;
		UInt8 BackgroundColorIndex;
		UInt8 PixelAspectRatio;
		UInt8 GlobalColorTableFlag() const { return (PackedFields >> 7) & 1; }
		UInt8 ColorResolution() const { return (PackedFields >> 4) & 7; }
		UInt8 SortFlag() const { return (PackedFields >> 3) & 1; }
		size_t SizeOfGlobalColorTable() const { return (PackedFields >> 0) & 7; }
	};
	struct ImageDescriptor {
		Gurax_PackedUInt16_LE(ImageLeftPosition);
		Gurax_PackedUInt16_LE(ImageTopPosition);
		Gurax_PackedUInt16_LE(ImageWidth);
		Gurax_PackedUInt16_LE(ImageHeight);
		UInt8 PackedFields;
		ImageDescriptor() {
			UInt8 localColorTableFlag = 0;
			UInt8 interlaceFlag = 0;
			UInt8 sortFlag = 0;
			UInt8 sizeOfLocalColorTable = 0;
			Gurax_PackUInt16(ImageLeftPosition, 0);
			Gurax_PackUInt16(ImageTopPosition, 0);
			Gurax_PackUInt16(ImageWidth, 0);
			Gurax_PackUInt16(ImageHeight, 0);
			PackedFields = (localColorTableFlag << 7) | (interlaceFlag << 6) |
				(sortFlag << 5) | (sizeOfLocalColorTable << 0);
		}
		UInt8 LocalColorTableFlag() const { return (PackedFields >> 7) & 1; }
		UInt8 InterlaceFlag() const { return (PackedFields >> 6) & 1; }
		UInt8 SortFlag() const { return (PackedFields >> 5) & 1; }
		UInt8 SizeOfLocalColorTable() const { return (PackedFields >> 0) & 7; }
	};
	struct GraphicControlExtension {
		UInt8 BlockSize;
		UInt8 PackedFields;
		Gurax_PackedUInt16_LE(DelayTime);
		UInt8 TransparentColorIndex;
		static const UInt8 Label = 0xf9;
		GraphicControlExtension() {
			UInt8 disposalMethod = 1;
			UInt8 userInputFlag = 0;
			UInt8 transparentColorFlag = 0;
			BlockSize = 4;
			PackedFields = (disposalMethod << 2) | (userInputFlag << 1) | (transparentColorFlag << 0);
			Gurax_PackUInt16(DelayTime, 0);
			TransparentColorIndex = 0;
		}
		UInt8 DisposalMethod() const { return (PackedFields >> 2) & 7; }
		UInt8 UserInputFlag() const { return (PackedFields >> 1) & 1; }
		UInt8 TransparentColorFlag() const { return (PackedFields >> 0) & 1; }
	};
	struct CommentExtension {
		Binary CommentData;
		bool validFlag;
		static const UInt8 Label = 0xfe;
		CommentExtension() {
			validFlag = false;
		}
	};
	struct PlainTextExtension {
		UInt8 BlockSize;
		Gurax_PackedUInt16_LE(TextGridLeftPosition);
		Gurax_PackedUInt16_LE(TextGridTopPosition);
		Gurax_PackedUInt16_LE(TextGridWidth);
		Gurax_PackedUInt16_LE(TextGridHeight);
		UInt8 CharacterCellWidth;
		UInt8 CharacterCellHeight;
		UInt8 TextForegroundColorIndex;
		UInt8 TextBackgroundColorIndex;
		Binary PlainTextData;
		bool validFlag;
		static const UInt8 Label = 0x01;
		PlainTextExtension() {
			BlockSize = 12;
			Gurax_PackUInt16(TextGridLeftPosition, 0);
			Gurax_PackUInt16(TextGridTopPosition, 0);
			Gurax_PackUInt16(TextGridWidth, 0);
			Gurax_PackUInt16(TextGridHeight, 0);
			CharacterCellWidth = 0;
			CharacterCellHeight = 0;
			TextForegroundColorIndex = 0;
			TextBackgroundColorIndex = 0;
			validFlag = false;
		}
	};
	struct ApplicationExtension {
		UInt8 BlockSize;
		char ApplicationIdentifier[8];
		char AuthenticationCode[3];
		Binary ApplicationData;
		bool validFlag;
		static const UInt8 Label = 0xff;
		ApplicationExtension() {
			BlockSize = 11;
			::memset(ApplicationIdentifier, 0x00, 8);
			::memset(AuthenticationCode, 0x00, 3);
			validFlag = false;
		}
	};
	struct Extensions {
		CommentExtension comment;
		PlainTextExtension plainText;
		ApplicationExtension application;
	};
	class ImageDataBlock {
	private:
		int _bitOffset;
		int _bitsRead;
		UInt8 _blockData[256];
	public:
		ImageDataBlock();
		bool ReadCode(Stream& stream, UInt16& code, int bitsOfCode);
		bool WriteCode(Stream& stream, UInt16 code, int bitsOfCode);
		bool Flush(Stream& stream);
	};
	class ImageProp : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ImageProp);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("gif.ImageProp");
	private:
		GraphicControlExtension _graphicControl;
		ImageDescriptor _imageDescriptor;
	public:
		ImageProp() {}
		ImageProp(GraphicControlExtension graphicControl) : _graphicControl(graphicControl) {}
	private:
		~ImageProp() = default;
	public:
		GraphicControlExtension& GetGraphicControl() const {
			return const_cast<ImageProp*>(this)->_graphicControl;
		}
		ImageDescriptor& GetImageDescriptor() const {
			return const_cast<ImageProp*>(this)->_imageDescriptor;
		}
	};
	class Entry : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Entry);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("gif.Entry");
	private:
		RefPtr<Image> _pImage;
		RefPtr<ImageProp> _pImageProp;
	public:
		Entry(Image* pImage, ImageProp* pImageProp) : _pImage(pImage), _pImageProp(pImageProp) {}
	private:
		~Entry() = default;
	};
	class EntryList : public ListBase<Entry*> {
	};
	class EntryOwner : public EntryList {
	public:
		~EntryOwner() { Clear(); }
		void Clear();
	};
	typedef std::map<Binary, UInt16> TransMap;
private:
	Header _header;
	LogicalScreenDescriptor _logicalScreenDescriptor;
	RefPtr<Palette> _pPaletteGlobal;
	Extensions _exts;
	ImageOwner _images;
public:
	// Constructor
	Content();
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) noexcept = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content();
public:
	bool Read(Stream& stream, Image* pImageTgt, Image::Format format);
	bool Write(Stream& stream, const Color& colorBackground, bool validBackgroundFlag, UInt16 loopCount);
	bool ReadColorTable(Stream& stream, Palette& palette);
	bool WriteColorTable(Stream& stream, const Palette& palette);
	bool ReadDataBlocks(Stream& stream, Binary& binary);
	bool WriteDataBlocks(Stream& stream, const Binary& binary);
	bool SkipImageDescriptor(Stream& stream);
	bool ReadImageDescriptor(Stream& stream, Image& image, ImageProp& imageProp);
	bool WriteGraphicControl(Stream& stream,
								const GraphicControlExtension& graphiControl);
	bool WriteImageDescriptor(Stream& stream,
		const GraphicControlExtension& graphicControl, Image& image);
	Header& GetHeader() { return _header; }
	LogicalScreenDescriptor& GetLogicalScreenDescriptor() {
		return _logicalScreenDescriptor;
	}
	Palette* GetGlobalPalette() { return _pPaletteGlobal.get(); }
	Extensions& GetExtensions() { return _exts; }
	ImageOwner& GetImages() { return _images; }
	void AddImage(Image* pImage,
			UInt16 imageLeftPosition, UInt16 imageTopPosition,
			UInt16 delayTime, UChar disposalMethod);
	static bool ReadBuff(Stream& stream, void* buff, size_t bytes);
	static bool WriteBuff(Stream& stream, const void* buff, size_t bytes);
	static void Dump(UChar* data, int bytes);
	static const Symbol* DisposalMethodToSymbol(UChar disposalMethod);
	static UChar DisposalMethodFromSymbol(const Symbol* pSymbol);
	static ImageDescriptor* GetImageDescriptor(Image& image);
	static GraphicControlExtension* GetGraphicControl(Image& image);
	static int GetPlausibleBackgroundIndex(Palette& palette, Image& image);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(gif)

#endif
