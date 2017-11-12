#ifndef __ntfs_attr_h___
#define __ntfs_attr_h___ 
#include "stdafx.h"

enum ATTR_TYPES{
  TYPE_STANDARD_INFORMATION           = 0X10,
  TYPE_ATTRIBUTE_LIST                 = 0X20,
  TYPE_FILE_NAME                      = 0X30,
  TYPE_VOLUME_VERSION_OBJECT_ID       = 0X40,
  TYPE_SECURITY_DESCRIPTOR            = 0X50,
  TYPE_VOLUME_NAME                    = 0X60,
  TYPE_VOLUME_INFORMATION             = 0X70,
  TYPE_DATA                           = 0X80,
  TYPE_INDEX_ROOT                     = 0X90,
  TYPE_INDEX_ALLOCATION               = 0XA0,
  TYPE_BITMAP                         = 0XB0,
  TYPE_SYMBOLIC_LINK_REPARSE_POINT    = 0XC0,
  TYPE_EA_INFORMATION                 = 0XD0,
  TYPE_EA                             = 0XE0,
  TYPE_PROPERTY_SET                   = 0XF0,
  TYPE_LOGGED_UTILITY_STREAM          = 0X100
};

char const * const attr_types[] = {
  "STANDARD_INFORMATION",
  "ATTRIBUTE_LIST",
  "FILE_NAME",
  "VOLUME_VERSION_OBJECT_ID",
  "SECURITY_DESCRIPTOR",
  "VOLUME_NAME",
  "VOLUME_INFORMATION",
  "DATA",
  "INDEX_ROOT",
  "INDEX_ALLOCATION",
  "BITMAP",
  "SYMBOLIC_LINK_REPARSE_POINT",
  "EA_INFORMATION",
  "EA",
  "PROPERTY_SET",
  "LOGGED_UTILITY_STREAM"
};

const char No[]   = "No";
const char Yes[]  = "Yes";

enum NAME_TYPES {
  POSIX,
  WIN_32,
  DOS,
  WIN32_IN_DOS_SPACE
};

char const * const name_types[] = {
  "POSIX",    //(unicode, case sensitive)
  "Win32",    //(unicode, case insensitive)
  "DOS",      //(8.3 ASCII, case insensitive)
  "Win32 7 DOS"  //(when Win32 fits in DOS space)
};

/*STRUCTURES*/

//MFT record header and attribute header
typedef struct {
  char              szSignature[4];    // Signature "FILE"
  unsigned short    wFixupOffset;    // offset to fixup pattern
  unsigned short    wFixupSize;      // Size of fixup-list +1
  long long         n64LogSeqNumber;  // log file seq number
  unsigned short    wSequence;      // sequence number in MFT
  unsigned short    wHardLinks;      // Hard-link count
  unsigned short    wAttribOffset;    // Offset to seq of Attributes
  unsigned short    wFlags;        // 0x01 = NonRes; 0x02 = Dir
  unsigned int      dwRecLength;    // Real size of the record
  unsigned int      dwAllLength;    // Allocated size of the record
  long long         n64BaseMftRec;    // pointer to base MFT rec or 0
  unsigned short    wNextAttrID;    // Minimum Identificator +1
  unsigned short    wFixupPattern;    // Current fixup pattern
  unsigned int      dwMFTRecNumber;    // Number of this MFT Record
                  // followed by resident and
                  // part of non-res attributes
} NTFS_MFT_FILE, *PNTFS_MFT_FILE;

#pragma pack(push, 1)
typedef struct// if resident then + RESIDENT
{          //  else + NONRESIDENT
  unsigned int    dwType;
  unsigned short  wFullLength;  // äëèíà àòðèáóòà, âêëþ÷àÿ ýòîò çàãîëîâîê
  unsigned short  wReserved;
  unsigned char   uchNonResFlag;  // íåðåçèäåíòíûé ôëàã (non-resident flag)
  unsigned char   uchNameLength;  // äëèíà èìåíè àòðèáóòà (íîëü åñëè àòðèáóò áåçûìÿííûé)
  unsigned short  wNameOffset;  // ñìåùåíèå èìåíè (íîëü åñëè àòðèáóò áåçûìÿííûé) 
  unsigned short  wFlags;      // ôëàãè
  unsigned short  wID;      // èäåíòèôèêàòîð àòðèáóòà (attribute ID)

  union ATTR
  {
    struct RESIDENT
    {
      unsigned int    dwLength;    // äëèíà òåëà àòðèáóòà, áåç çàãîëîâêà
      unsigned short  wAttrOffset;  // ñìåùåíèå òåëà àòðèáóòà  
      unsigned char   uchIndexedTag;  // èíäåêñíûé ôëàã
      unsigned char   uchPadding;    // äëÿ âûðàâíèâàíèÿ
    } Resident;

    struct NONRESIDENT
    {
      long long       n64StartVCN;      // íà÷àëüíûé âèðòóàëüíûé êëàñòåð (starting VCN)
      long long       n64EndVCN;      // êîíå÷íûé âèðòóàëüíûé êëàñòåð (last VCN)
      unsigned short  wDatarunOffset;   // ñìåùåíèå ñïèñêà îòðåçêîâ (data runs) 
      unsigned short  wCompressionSize; // ðàçìåð áëîêà ñæàòèÿ (compression unit size), îêðóãëåííûé äî 4 áàéò ââåðõ
      unsigned char   uchPadding[4];    // äëÿ âûðàâíèâàíèÿ
      long long       n64AllocSize;    // âûäåëåííûé ðàçìåð (allocated size), îêðóãëåííûé äî ðàçìåðà êëàñòåðà
      long long       n64RealSize;    // ðåàëüíûé ðàçìåð (real size)
      long long       n64StreamSize;    // èíèöèàëèçèðîâàííûé ðàçìåð ïîòîêà (initialized data size of the stream)
                      // data runs...
    }NonResident;
  }Attr;
} NTFS_ATTRIBUTE, *PNTFS_ATTRIBUTE;
#pragma pack(pop)

#define w2k
//0x10 always resident
typedef struct {
  long long       n64Create;    // Creation time
  long long       n64Modify;    // Last Modify time
  long long       n64Modfil;    // Last modify of record
  long long       n64Access;    // Last Access time
  unsigned int    dwFATAttributes;// As FAT + 0x800 = compressed
  unsigned int    dwReserved1;  // unknown Ìàêñèìàëüíîå êîëè÷åñòâî âåðñèé.

  unsigned int    dwVersionNum;  // ìëàäøåå äâîéíîå ñëîâî íîìåðà âåðñèè (version number)
  unsigned int    dwClassID;    // èäåíòèôèêàòîð êëàññà (class ID)
#ifdef w2k
  unsigned int    dwOwnerID;    // èäåíòèôèêàòîð âëàäåëüöà (owner ID)
  unsigned int    dwSecurityID;  // èäåíòèôèêàòîð áåçîïàñíîñòè (security ID)
  long long       n64QuotaCharged;// êîëè÷åñòâî êâîòèðóåìûõ áàéò (quota charged)
  long long       n64USN;      // íîìåð ïîñëåäíåé ïîñëåäîâàòåëüíîñòè îáíîâëåíèÿ (update sequence number USN)
#endif
} ATTR_STANDARD;
#undef w2k

struct MFT_REF {
  long long index : 48;  //èíäåêñ ýëåìåíòà â òàáëèöå
  unsigned int ordinal;      //ïîðÿäêîâûé íîìåð
};

//0x20 
typedef struct {
  unsigned int    dwType;      // The attribute type code.
  unsigned short  wRecLength;    // The size of this structure, plus the optional name buffer, in bytes.
  unsigned char   bNameLength;  // The size of the optional attribute name, in characters. If a name 
                //exists, this value is nonzero and the structure is followed immediately 
                //by a Unicode string of the specified number of characters.
  unsigned char   bNameOffset;  // Reserved.
  long long       n64StartVCN;  // The lowest virtual cluster number (VCN) for this attribute. This member 
                //is zero unless the attribute requires multiple file record segments and 
                //unless this entry is a reference to a segment other than the first one. 
                //In this case, this value is the lowest VCN that is described by the referenced segment.
  long long       n64BaseMftRec;  // The master file table (MFT) segment in which the attribute resides. 
  unsigned short  wAttrID;    // Reserved.
  wchar_t         wcName[1];    // The start of the optional attribute name
} ATTR_LIST;

//0x30 always resident
typedef struct {
  long long     dwMftParentDir;             // Seq-nr parent-dir MFT entry ;;MFT_REF
  long long     n64Create;                  // Creation time
  long long     n64Modify;                  // Last Modify time
  long long     n64Modfil;                  // Last modify of record
  long long     n64Access;                  // Last Access time
  long long     n64Allocated;               // Allocated disk space
  long long     n64RealSize;                // Size of the file
  unsigned int  dwFlags;          // attribute
  unsigned int  dwEAsReparsTag;        // Used by EAs and Reparse
  unsigned char chFileNameLength;
  unsigned char chFileNameType;             // 8.3 / Unicode
  wchar_t       wFilename[1];             // Name (in Unicode ?)
}ATTR_FILENAME;

// 0x40 always resident
typedef struct {
  long long n128ObjectId[2];    // Unique Id assigned to file 
  long long n128BirVolumeId[2];  // Volume where file was created
  long long n128BirObjectId[2];  // Original Object Id of file
  long long n128DomainId[2];    // Domain in which object was created
} ATTR_OBJECT_ID;

//0x50 always non-resident
typedef struct {

} ATTR_SECURITY_DESCRIPTOR;

//0x60 always resident, used only for $Volume file
typedef struct {
  wchar_t UNICODE_NAME[1];
} ATTR_VOLUME_NAME;

//0x70 always resident, used only for $Volume file
typedef struct {
  long long       n64Reserved;
  unsigned short  wVersionNumber;
  unsigned short  wFlags;      // VOLUME_FLAGS
  unsigned int    dwReserved;
} ATTR_VOLUME_INFORMATION;

//used only for $Volume file
typedef enum {
  Dirty               = 0x0001,
  Resize_LogFile      = 0x0002,
  Upgrade_Mount       = 0x0004,
  Mounted_NT4         = 0x0008,
  Delete_USN_underway = 0x0010,
  Repair_Objects_Ids  = 0x0020,
  Modified_by_chkdsk  = 0x8000
} VOLUME_FLAGS;

typedef enum _INDEX_ENTRY_FLAGS {
  INDEX_ENTRY_NODE = 1,
  INDEX_ENTRY_END  = 2 //ïîñëåäíèé ýëåìåíò â óçëå
} INDEX_ENTRY_FLAGS;

//  header of index
typedef struct _INDEX_HEADER {
  unsigned long   entries_offset;  //áàéòîâîå ñìåùåíèå ïåðâîãî èíäåêñíîãî ýëåìåíòà, îòíîñèòåëüíî çàãîëîâêà óçëà
  unsigned long   index_length;    //ðàçìåð óçëà â áàéòàõ
  unsigned long   allocated_size;  //âûäåëåííûé ðàçìåð óçëà
  unsigned long   flags;
} INDEX_HEADER, *PINDEX_HEADER;

// header of index item
typedef struct _INDEX_ENTRY_HEADER_DIR {
  MFT_REF             indexed_file;    //àäðåñ MFT ôàéëà
  unsigned short      length;        //ñìåùåíèå ñëåäóþùåãî ýëåìåíòà, îòíîñèòåëüíî òåêóùåãî
  unsigned short      key_length;      //äëèíà àòðèáóòà $FILE_NAME
  INDEX_ENTRY_FLAGS   flags;  //ôëàãè
  ATTR_FILENAME       file_name;  //ñàì àòðèáóò $FILE_NAME, åñëè key_length áîëüøå íóëÿ.
} INDEX_ENTRY_HEADER_DIR, *PINDEX_ENTRY_HEADER_DIR;

//0x90 always resident çàãîëîâîê $INDEX_ROOT
typedef struct _INDEX_ROOT {
  unsigned int    type;            //òèï èíäåêñèðóåìîãî àòðèáóòà
  unsigned int    collation_rule;      //ïðàâèëî óïîðÿäî÷åíèÿ â äåðåâå
  unsigned int    index_block_size;      //ðàçìåð èíäåêñíîé çàïèñè â áàéòàõ 
  unsigned char   clusters_per_index_block; //size of each index block (record) in clusters ëèáî ëîãàðèôì ðàçìåðà
  unsigned char   reserved[3];        //unused
  INDEX_HEADER    index;        //çàãîëîâîê èíäåêñíîãî óçëà
} INDEX_ROOT, *PINDEX_ROOT;

//0xa0 always non-resident çàãîëîâîê èíäåêñíîé çàïèñè
typedef struct _INDEX_ALLOCATION {
  unsigned long       magic;        //ñèãíàòóðà "INDX"
  unsigned short      usa_ofs;
  unsigned short      usa_count;
  unsigned long long  lsn;
  unsigned long long  index_block_vcn;  //VCN èíäåêñíîé çàïèñè
  INDEX_HEADER        index;        //çàãîëîâîê óçëà
} INDEX_ALLOCATION, *PINDEX_ALLOCATION;

#endif
