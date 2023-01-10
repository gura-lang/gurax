//==============================================================================
// Content.h
// Specification: spec-gif89a.txt
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
	struct DisposalMethod {
		static const UInt8 None					= 0;
		static const UInt8 Keep					= 1;
		static const UInt8 Background			= 2;
		static const UInt8 Previous				= 3;
	};
	// 17. Header (required)
	struct Header {
		char Signature[3];
		char Version[3];
		Header() {
			::memcpy(Signature, "GIF", 3);
			::memcpy(Version, "89a", 3);
		}
	};
	// 18. Logical Screen Descriptor (required)
	struct LogicalScreenDescriptor {
		Gurax_PackedUInt16_LE(LogicalScreenWidth);
		Gurax_PackedUInt16_LE(LogicalScreenHeight);
		UInt8 PackedFields;
		UInt8 BackgroundColorIndex;
		UInt8 PixelAspectRatio;
		UInt8 GetGlobalColorTableFlag() const { return (PackedFields >> 7) & 1; }
		UInt8 GetColorResolution() const { return (PackedFields >> 4) & 7; }
		UInt8 GetSortFlag() const { return (PackedFields >> 3) & 1; }
		size_t GetSizeOfGlobalColorTable() const { return (PackedFields >> 0) & 7; }
		void Print() const {
			::printf("LogicalScreenWidth:     %d\n", Gurax_UnpackUInt16(LogicalScreenWidth));
			::printf("LogicalScreenHeight:    %d\n", Gurax_UnpackUInt16(LogicalScreenHeight));
			::printf("GlobalColorTableFlag:   %d\n", GetGlobalColorTableFlag());
			::printf("ColorResolution:        %d\n", GetColorResolution());
			::printf("SortFlag:               %d\n", GetSortFlag());
			::printf("SizeOfGlobalColorTable: %zd\n", GetSizeOfGlobalColorTable());
			::printf("BackgroundColorIndex:   %d\n", BackgroundColorIndex);
			::printf("PixelAspectRatio:       %d\n", PixelAspectRatio);
		}
	};
	// 20. Image Descriptor (optional)
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
		UInt8 GetLocalColorTableFlag() const { return (PackedFields >> 7) & 1; }
		UInt8 GetInterlaceFlag() const { return (PackedFields >> 6) & 1; }
		UInt8 GetSortFlag() const { return (PackedFields >> 5) & 1; }
		UInt8 GetSizeOfLocalColorTable() const { return (PackedFields >> 0) & 7; }
		void Print() const {
			::printf("ImageLeftPosition:     %d\n", Gurax_UnpackUInt16(ImageLeftPosition));
			::printf("ImageTopPosition:      %d\n", Gurax_UnpackUInt16(ImageTopPosition));
			::printf("ImageWidth:            %d\n", Gurax_UnpackUInt16(ImageWidth));
			::printf("ImageHeight:           %d\n", Gurax_UnpackUInt16(ImageHeight));
			::printf("LocalColorTableFlag:   %d\n", GetLocalColorTableFlag());
			::printf("InterlaceFlag:         %d\n", GetInterlaceFlag());
			::printf("SortFlag:              %d\n", GetSortFlag());
			::printf("SizeOfLocalColorTable: %d\n", GetSizeOfLocalColorTable());
		}
	};
	// 23. Graphic Control Extension (optional)
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
		UInt8 GetDisposalMethod() const { return (PackedFields >> 2) & 7; }
		UInt8 GetUserInputFlag() const { return (PackedFields >> 1) & 1; }
		UInt8 GetTransparentColorFlag() const { return (PackedFields >> 0) & 1; }
	};
	// 24. Comment Extension (optional)
	struct CommentExtension {
		Binary CommentData;
		bool validFlag;
		static const UInt8 Label = 0xfe;
		CommentExtension() {
			validFlag = false;
		}
	};
	// 25. Plain Text Extension (optional)
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
	// 26. Application Extension (optional)
	struct ApplicationExtension {
		struct Data {
			UInt8 BlockSize;
			UInt8 Id;
			Gurax_PackedUInt16_LE(LoopCount);
			Data() {
				BlockSize = 3;
				Id = 0x01;
				Gurax_PackUInt16(LoopCount, 0);
			};
		};
		UInt8 BlockSize;
		char ApplicationIdentifier[8];
		char AuthenticationCode[3];
		static const UInt8 Label = 0xff;
		ApplicationExtension() {
			BlockSize = 11;
			::memcpy(ApplicationIdentifier, "NETSCAPE", 8);
			::memcpy(AuthenticationCode, "2.0", 3);
		}
	};
	struct Extensions {
		CommentExtension commentExtension;
		PlainTextExtension plainTextExtension;
		ApplicationExtension applicationExtension;
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
	class GraphicBlock : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(GraphicBlock);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("gif.GraphicBlock");
	private:
		GraphicControlExtension _graphicControl;
		ImageDescriptor _imageDescriptor;
	public:
		GraphicBlock() {}
		GraphicBlock(GraphicControlExtension graphicControl) : _graphicControl(graphicControl) {}
	private:
		~GraphicBlock() = default;
	public:
		GraphicControlExtension& GetGraphicControl() const {
			return const_cast<GraphicBlock*>(this)->_graphicControl;
		}
		ImageDescriptor& GetImageDescriptor() const {
			return const_cast<GraphicBlock*>(this)->_imageDescriptor;
		}
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const GraphicBlock& other) const { return this == &other; }
		bool IsEqualTo(const GraphicBlock& other) const { return IsIdentical(other); }
		bool IsLessThan(const GraphicBlock& other) const { return this < &other; }
	};
	class Entry : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Entry);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("gif.Entry");
	private:
		RefPtr<GraphicBlock> _pGraphicBlock;
		RefPtr<Image> _pImage;
	public:
		Entry(GraphicBlock* pGraphicBlock, Image* pImage) : _pGraphicBlock(pGraphicBlock), _pImage(pImage) {}
	private:
		~Entry() = default;
	public:
		GraphicBlock& GetGraphicBlock() { return *_pGraphicBlock; }
		Image& GetImage() { return *_pImage; }
	};
	class EntryList : public ListBase<Entry*> {
	};
	class EntryOwner : public EntryList {
	public:
		~EntryOwner() { Clear(); }
		void Clear();
	};
	class Iterator_EachImage : public Iterator {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("Iterator_EachImage");
	private:
		RefPtr<Content> _pContent;
		size_t _idx;
	public:
		Iterator_EachImage(Content* pContent) : _pContent(pContent), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return _pContent->GetEntries().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	typedef std::map<Binary, UInt16> TransMap;
private:
	Header _header;
	LogicalScreenDescriptor _logicalScreenDescriptor;
	RefPtr<Palette> _pPaletteGlobal;
	Extensions _extensions;
	EntryOwner _entries;
	int _loopCount;
public:
	static Extensions extensionsDefault;
public:
	// Constructor
	Content() : _loopCount(0) {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) noexcept = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	bool Read(Stream& stream, const Image::Format& format);
	bool Write(Stream& stream, const Color& colorBackground, bool validBackgroundFlag);
	bool ReadColorTable(Stream& stream, Palette& palette);
	bool WriteColorTable(Stream& stream, const Palette& palette);
	bool ReadDataBlocks(Stream& stream, Binary& binary);
	bool WriteDataBlocks(Stream& stream, const UInt8* buff, size_t bytes);
	bool SkipImageDescriptor(Stream& stream);
	bool ReadImageDescriptor(Stream& stream, Image& image, GraphicBlock& GraphicBlock);
	bool WriteGraphicControl(Stream& stream, const GraphicControlExtension& graphiControl);
	bool WriteImageDescriptor(Stream& stream, Entry& entry);
	Header& GetHeader() { return _header; }
	LogicalScreenDescriptor& GetLogicalScreenDescriptor() {
		return _logicalScreenDescriptor;
	}
	Palette* GetGlobalPalette() { return _pPaletteGlobal.get(); }
	Extensions& GetExtensions() { return _extensions; }
	int GetLoopCount() const { return _loopCount; }
	void SetLoopCount(int loopCount) { _loopCount = loopCount; }
	EntryOwner& GetEntries() { return _entries; }
	void AddImage(const Image& image, UInt16 delayTime,
			UInt16 imageLeftPosition, UInt16 imageTopPosition, UInt8 disposalMethod);
	static bool ReadBuff(Stream& stream, void* buff, size_t bytes);
	static bool WriteBuff(Stream& stream, const void* buff, size_t bytes);
	static void Dump(UInt8* data, int bytes);
	static const Symbol* DisposalMethodToSymbol(UInt8 disposalMethod);
	static UInt8 DisposalMethodFromSymbol(const Symbol* pSymbol);
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
