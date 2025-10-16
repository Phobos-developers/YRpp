/*

Version Control Class

Same As VersionClass in RA1 Source Code

*/

#pragma once
#include <GeneralDefinitions.h>


typedef enum CommProtocolEnum
{
    COMM_PROTOCOL_SINGLE_NO_COMP = 0, // single frame with no compression
    COMM_PROTOCOL_SINGLE_E_COMP,      // single frame with event compression
    COMM_PROTOCOL_MULTI_E_COMP,       // multiple frame with event compression
    COMM_PROTOCOL_COUNT,
    DEFAULT_COMM_PROTOCOL = COMM_PROTOCOL_MULTI_E_COMP
} CommProtocolType;


class VersionClass
{
public:
    DEFINE_REFERENCE(VersionClass, Instance, 0xA8ECE0)

    //.....................................................................
    // Constructor/Destructor
    //.....................................................................
    explicit __forceinline VersionClass(noinit_t) {}
	VersionClass() : VersionClass(noinit_t()) JMP_THIS(0x74F730);
    virtual ~VersionClass() JMP_THIS(0x4E7DE0);
    
    //.....................................................................
    // These routines return the current version number.  The long version
    // number contains the major version in the high word, and the minor
    // version in the low word.  They should be interpreted in hex.
    //.....................................................................
    unsigned int Version_Number(void) JMP_THIS(0x74F760);
    unsigned short Major_Version(void) JMP_THIS(0x74F960);
    unsigned short Minor_Version(void) JMP_THIS(0x74FA20);

    //.....................................................................
    // Retrieves a pointer to the version # as a text string (#.#), with
    // the trailing 0's trimmed off.
    //.....................................................................
    char* Version_Name(void) JMP_THIS(0x74FAE0);

    //.....................................................................
    // Retrieves a pointer to the current version text.
    //.....................................................................
    char* Version_Text()
    {
        return (VersionText);
    }

    //.....................................................................
    // Returns the default comm protocol for a given version number.
    //.....................................................................
    CommProtocolType Version_Protocol(unsigned int version) JMP_THIS(0x74FD20);

    //.....................................................................
    // These routines support "version clipping".
    //.....................................................................
    void Init_Clipping(void) JMP_THIS(0x74FD50);
    unsigned int Clip_Version(unsigned int minver, unsigned int maxver) JMP_THIS(0x74FD60);
    unsigned int Get_Clipped_Version(void)
    {
        return (MaxClipVer);
    }

    //.....................................................................
    // These routines return the theoretical lowest & highest version #'s
    // that this program will connect to; this does not take any previous
    // version clipping into account.
    //.....................................................................
    unsigned int Min_Version(void) JMP_THIS(0x74FDA0);
    unsigned int Max_Version(void) JMP_THIS(0x74FDB0);

private:
    //.....................................................................
    // Fills in a 'VersionText' with a descriptive version name.
    //.....................................................................
	void Read_Text_String(void) JMP_THIS(0x74FC80);

    /*
    //.....................................................................
    // These values define the major & minor version #'s for the current
    // version.  Change these values to change the game's version #!
    //.....................................................................
    enum VersionEnum
    {
#ifdef FIXIT_VERSION_3
        MAJOR_VERSION = 0x0003,
        MINOR_VERSION = 0x0000
#else
        MAJOR_VERSION = 0x0001,
        MINOR_VERSION = 0x2000
#endif
    };

    //.....................................................................
    // These values control which other versions this program will connect
    // to.  Keep them current!
    // If CHEAT is defined, the program will only connect to itself; these
    // values aren't used.
    //.....................................................................
    
    enum VersionRangeEnum
    {
#ifdef FIXIT_VERSION_3
        //	ajw - We can only play against same version.
        MIN_VERSION = VERSION_RA_300,
        MAX_VERSION = VERSION_RA_300
#else
        MIN_VERSION = VERSION_RED_ALERT_104, // 0x00010000,	// Version: 1.0
        MAX_VERSION = VERSION_AFTERMATH      // 0x00012000	// Version: 1.2
#endif
    };*/

    //.....................................................................
    // This is the program's version number, stored internally.
    //.....................................................................
    unsigned int Version;
    unsigned short MajorVer;
    unsigned short MinorVer;

    //.....................................................................
    // This array is used for formatting the version # as a string
    //.....................................................................
    char VersionName[30];

    //.....................................................................
    // This array contains special version labels (such as "Beta"), stored
    // in the file VERSION.TXT.  If the file isn't present, no label is
    // shown.
    //.....................................................................
    char VersionText[16];

    //.....................................................................
    // Values used for "Version Clipping"
    //.....................................................................
    unsigned int MinClipVer;
    unsigned int MaxClipVer;

    //.....................................................................
    // Bitfield Flags
    // IsInitialized: is set if the VERSION.TXT file has been read
    //.....................................................................
    unsigned VersionInit : 1;
    unsigned MajorInit : 1;
    unsigned MinorInit : 1;
    unsigned TextInit : 1;
};