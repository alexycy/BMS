//***************************************************************************
//*     BootROM entries for XC88x-AA/AB/AC Step                             *
//*     Updated      : 28/02/2007                                           *
//*     Copyright    : (c) 2006 Infineon Technologies AG                    *
//*     Changes      :                                                      *
//*       28/02/2007 : Added #define: XRAM_CALL_ADDRESS                     *
//***************************************************************************

#ifndef  __XC88x_FLADDR_H__
#define  __XC88x_FLADDR_H__

// User Configuration //
#define XC88xAA           1    // Must be set to '1' (for AA step)
#define XC88xAB           0    // Must be set to '0' (set to '1' for AB step)
#define XC88xAC           0    // Must be set to '0' (set to '1' for AC step)

#define USE_BANK          3    // Register Bank used during Program / Erase
                               // Default = 3
#define WORDLINE_BUFFER_ADDRESS  0xC0  // Starting address of the Buffer in the IRAM
                                       // This Buffer will be used to store data
                                       // before it is being programmed to flash
#define USE_64BYTE_BUFFER 0       // If PFlash will be programmed, set this to '1'
                                  // Programming PFLash will need 64Byte WordLine Buffer
                                  // Else, default buffer size is set to 32byte.
#define USE_PFLERASE      1       // Set to '1' if PFlErase() routine is to be used.
                                  // Set to '0' if not used, to save some code space.
#define USE_DLFERASE      1       // Set to '1' if DFlErase() routine is to be used.
                                  // Set to '0' if not used, to save some code space.
#define XRAM_CALL_ADDRESS 0xF500  // The Flash Erase / Program routine will build a code
                                  // in this location.
                                  // The number of bytes needed is:

// End of user configuration


//+----------------------------------------------+
//|   ROM entries taken from manual              |
//|   and AppNote aboute programming the FLASH   |
//|   used in XC88x_FLHANDLER.ASM                |
//+----------------------------------------------+

//====================================================================================
#if XC88xAA                                     // Use the FSM to program / erase flash
#define FLASH_ERASE_BROM_ENTRY          0xDFF9  // Erase Flash Bank
#define FLASH_PROGRAM_BROM_ENTRY        0xDFF6  // Program Flash Bank.
#define FLASH_ERASE_ABORT_BROM_ENTRY    0xDFF3  // Abort the on going erase process
#define FLASH_READ_STATUS_BROM_ENTRY    0xDFF0  // Read Flash Status
#endif
//====================================================================================

//+-----------------------------------------+
//|   General definitions of used sources   |
//+-----------------------------------------+
// used buffer address in IRAM for Wordline erase/program 
#if (XC88xAA)  
#define MAGIC_MEMORY                  0x36  // reserve magic memory from D:0x36 .. D:0x3E
#if (USE_64BYTE_BUFFER == 1)
#define BYTES_PER_WORDLINE            64    //
#else
#define BYTES_PER_WORDLINE            32    //
#endif
#define RESERVED_BYTES                0x08
#define PFLASH0                       0     // PFlash 0
#define PFLASH1                       1     // PFlash 1
#define PFLASH2	                      2     // PFlash 2
#define DFLASH0                       3     // DFlash 0
#define DFLASH1                       4     // DFlash 1

#endif
//+------------------------------------------------+
//|   End of general definitions of used sources   |
//+------------------------------------------------+



//************************************************************************************************
//*   Definitions of Bank-, Sector- and Wordlineaddresses
//* 
//************************************************************************************************
// Sectors of PFlash0 for erasing -- transferred in  PFlErase() first parameter

// Sector.07/Sector.06/Sector.05/Sector.04/Sector.03/Sector.02/ Sector.01/ Sector.00 /
// ---------/---------/---------/---------/---------/Pfl0Sec02/ Pfl0Sec01/ Pfl0Sec00 /
// ---------/---------/---------/---------/---------/-256B-4WL/-256B--4WL/-7.5k-120WL/
// ---------/---------/---------/---------/---------/-0x1F00--/--0x1E00--/--0x0000----/
#define PFL0_SEC0   0x0001
#define PFL0_SEC1   0x0002
#define PFL0_SEC2   0x0004

// Sectors of PFlash1 for erasing -- transferred in  PFlErase() Second parameter

// Sector.07/Sector.06/Sector.05/Sector.04/Sector.03/Sector.02/ Sector.01/ Sector.00  /
// ---------/---------/---------/---------/---------/Pfl1Sec02/ Pfl1Sec01/ Pfl1Sec00  /
// ---------/---------/---------/---------/---------/-256B-4WL/-256B--4WL/-7.5k-120WL/
// ---------/---------/---------/---------/---------/-0x3F00--/--0x3E00--/--0x2000----/
#define PFL1_SEC0   0x0001
#define PFL1_SEC1   0x0002
#define PFL1_SEC2   0x0004

// Sectors of PFlash2 for erasing -- transferred in  PFlErase() Third parameter

// Sector.07/Sector.06/Sector.05/Sector.04/Sector.03/Sector.02/ Sector.01/ Sector.00  /
// ---------/---------/---------/---------/---------/Pfl2Sec02/ Pfl2Sec01/ Pfl2Sec00  /
// ---------/---------/---------/---------/---------/-256B-4WL/-256B--4WL/-7.5k-120WL/
// ---------/---------/---------/---------/---------/-0x5F00--/--0x5E00--/--0x4000----/
#define PFL2_SEC0   0x0001
#define PFL2_SEC1   0x0002
#define PFL2_SEC2   0x0004

// Sectors of DFlash 0 for erasing -- transfered in DFlErase() First parameter
// DFlash 0 address is also mirrorred to 0x7xxx

// Sector.15/Sector.14/Sector.13/Sector.12/Sector.11/Sector.10/Sector.09/Sector.08/
// ---------/---------/---------/---------/---------/---------/Dfl0Sec09/Dfl0Sec08/
// ---------/---------/---------/---------/---------/---------/-128-4WL-/-128-4WL-/
// ---------/---------/---------/---------/---------/---------/--0xAF80-/--0xAF00-/
 
// Sector.07/Sector.06/Sector.05/Sector.04/Sector.03/Sector.02/Sector.01/Sector.00/
// Dfl0Sec07/Dfl0Sec06/Dfl0Sec05/Dfl0Sec04/Dfl0Sec03/Dfl0Sec02/Dfl0Sec01/Dfl0Sec00/
// -128-4WL-/-128-4WL-/-256-8WL-/-256-8WL-/-512-16WL/-512-16WL/-1k--32WL/-1k--32WL/
// --0xAE80-/--0xAE00-/--0xAD00-/--0xAC00-/-0xAA00--/-0xA800--/--0xA400-/--0xA000-/

#define DFL0_SEC0   0x0001
#define DFL0_SEC1   0x0002
#define DFL0_SEC2   0x0004
#define DFL0_SEC3   0x0008
#define DFL0_SEC4   0x0010
#define DFL0_SEC5   0x0020
#define DFL0_SEC6   0x0040
#define DFL0_SEC7   0x0080
#define DFL0_SEC8   0x0100
#define DFL0_SEC9   0x0200
#define DFL0_SECALL 0x3FF

// Sectors of DFlash 1 for erasing -- transfered in DFlErase() Second parameter
// DFlash 1 address is also mirrorred to 0x6xxx

// Sector.15/Sector.14/Sector.13/Sector.12/Sector.11/Sector.10/Sector.09/Sector.08/
// ---------/---------/---------/---------/---------/---------/Dfl1Sec09/Dfl1Sec08/
// ---------/---------/---------/---------/---------/---------/-128-4WL-/-128-4WL-/
// ---------/---------/---------/---------/---------/---------/--0xAF80-/--0xAF00-/
 
// Sector.07/Sector.06/Sector.05/Sector.04/Sector.03/Sector.02/Sector.01/Sector.00/
// Dfl1Sec07/Dfl1Sec06/Dfl1Sec05/Dfl1Sec04/Dfl1Sec03/Dfl1Sec02/Dfl1Sec01/Dfl1Sec00/
// -128-4WL-/-128-4WL-/-256-8WL-/-256-8WL-/-512-16WL/-512-16WL/-1k--32WL/-1k--32WL/
// --0xAE80-/--0xAE00-/--0xAD00-/--0xAC00-/-0xAA00--/-0xA800--/--0xA400-/--0xA000-/

#define DFL1_SEC0   0x0001
#define DFL1_SEC1   0x0002
#define DFL1_SEC2   0x0004
#define DFL1_SEC3   0x0008
#define DFL1_SEC4   0x0010
#define DFL1_SEC5   0x0020
#define DFL1_SEC6   0x0040
#define DFL1_SEC7   0x0080
#define DFL1_SEC8   0x0100
#define DFL1_SEC9   0x0200
#define DFL1_SECALL 0x3FF

//###################################################################################
// WordLine startaddresses for Sectors in PFlas 0, each WL with 64bytes

// Sector 0 -- 7.5 kbytes -- 120 Wordlines
#define PFL0_SEC0_WL00  0x0000
#define PFL0_SEC0_WL01  0x0040
#define PFL0_SEC0_WL02  0x0080
#define PFL0_SEC0_WL03  0x00C0
#define PFL0_SEC0_WL04  0x0100
#define PFL0_SEC0_WL05  0x0140
#define PFL0_SEC0_WL06  0x0180
#define PFL0_SEC0_WL07  0x01C0
#define PFL0_SEC0_WL08  0x0200
#define PFL0_SEC0_WL09  0x0240
#define PFL0_SEC0_WL10  0x0280
#define PFL0_SEC0_WL11  0x02C0
#define PFL0_SEC0_WL12  0x0300
#define PFL0_SEC0_WL13  0x0340
#define PFL0_SEC0_WL14  0x0380
#define PFL0_SEC0_WL15  0x03C0
#define PFL0_SEC0_WL16  0x0400
#define PFL0_SEC0_WL17  0x0440
#define PFL0_SEC0_WL18  0x0480
#define PFL0_SEC0_WL19  0x04C0
#define PFL0_SEC0_WL20  0x0500
#define PFL0_SEC0_WL21  0x0540
#define PFL0_SEC0_WL22  0x0580
#define PFL0_SEC0_WL23  0x05C0
#define PFL0_SEC0_WL24  0x0600
#define PFL0_SEC0_WL25  0x0640
#define PFL0_SEC0_WL26  0x0680
#define PFL0_SEC0_WL27  0x06C0
#define PFL0_SEC0_WL28  0x0700
#define PFL0_SEC0_WL29  0x0740
#define PFL0_SEC0_WL30  0x0780
#define PFL0_SEC0_WL31  0x07C0
#define PFL0_SEC0_WL32  0x0800
#define PFL0_SEC0_WL33  0x0840
#define PFL0_SEC0_WL34  0x0880
#define PFL0_SEC0_WL35  0x08C0
#define PFL0_SEC0_WL36  0x0900
#define PFL0_SEC0_WL37  0x0940
#define PFL0_SEC0_WL38  0x0980
#define PFL0_SEC0_WL39  0x09C0
#define PFL0_SEC0_WL40  0x0A00
#define PFL0_SEC0_WL41  0x0A40
#define PFL0_SEC0_WL42  0x0A80
#define PFL0_SEC0_WL43  0x0AC0
#define PFL0_SEC0_WL44  0x0B00
#define PFL0_SEC0_WL45  0x0B40
#define PFL0_SEC0_WL46  0x0B80
#define PFL0_SEC0_WL47  0x0BC0
#define PFL0_SEC0_WL48  0x0C00
#define PFL0_SEC0_WL49  0x0C40
#define PFL0_SEC0_WL50  0x0C80
#define PFL0_SEC0_WL51  0x0CC0
#define PFL0_SEC0_WL52  0x0D00
#define PFL0_SEC0_WL53  0x0D40
#define PFL0_SEC0_WL54  0x0D80
#define PFL0_SEC0_WL55  0x0DC0
#define PFL0_SEC0_WL56  0x0E00
#define PFL0_SEC0_WL57  0x0E40
#define PFL0_SEC0_WL58  0x0E80
#define PFL0_SEC0_WL59  0x0EC0
#define PFL0_SEC0_WL60  0x0F00
#define PFL0_SEC0_WL61  0x0F40
#define PFL0_SEC0_WL62  0x0F80
#define PFL0_SEC0_WL63  0x0FC0
#define PFL0_SEC0_WL64  0x1000
#define PFL0_SEC0_WL65  0x1040
#define PFL0_SEC0_WL66  0x1080
#define PFL0_SEC0_WL67  0x10C0
#define PFL0_SEC0_WL68  0x1100
#define PFL0_SEC0_WL69  0x1140
#define PFL0_SEC0_WL70  0x1180
#define PFL0_SEC0_WL71  0x11C0
#define PFL0_SEC0_WL72  0x1200
#define PFL0_SEC0_WL73  0x1240
#define PFL0_SEC0_WL74  0x1280
#define PFL0_SEC0_WL75  0x12C0
#define PFL0_SEC0_WL76  0x1300
#define PFL0_SEC0_WL77  0x1340
#define PFL0_SEC0_WL78  0x1380
#define PFL0_SEC0_WL79  0x13C0
#define PFL0_SEC0_WL80  0x1400
#define PFL0_SEC0_WL81  0x1440
#define PFL0_SEC0_WL82  0x1480
#define PFL0_SEC0_WL83  0x14C0
#define PFL0_SEC0_WL84  0x1500
#define PFL0_SEC0_WL85  0x1540
#define PFL0_SEC0_WL86  0x1580
#define PFL0_SEC0_WL87  0x15C0
#define PFL0_SEC0_WL88  0x1600
#define PFL0_SEC0_WL89  0x1640
#define PFL0_SEC0_WL90  0x1680
#define PFL0_SEC0_WL91  0x16C0
#define PFL0_SEC0_WL92  0x1700
#define PFL0_SEC0_WL93  0x1740
#define PFL0_SEC0_WL94  0x1780
#define PFL0_SEC0_WL95  0x17C0
#define PFL0_SEC0_WL96  0x1800
#define PFL0_SEC0_WL97  0x1840
#define PFL0_SEC0_WL98  0x1880
#define PFL0_SEC0_WL99  0x18C0
#define PFL0_SEC0_WL100 0x1900
#define PFL0_SEC0_WL101 0x1940
#define PFL0_SEC0_WL102 0x1980
#define PFL0_SEC0_WL103 0x19C0
#define PFL0_SEC0_WL104 0x1A00
#define PFL0_SEC0_WL105 0x1A40
#define PFL0_SEC0_WL106 0x1A80
#define PFL0_SEC0_WL107 0x1AC0
#define PFL0_SEC0_WL108 0x1B00
#define PFL0_SEC0_WL109 0x1B40
#define PFL0_SEC0_WL110 0x1B80
#define PFL0_SEC0_WL111 0x1BC0
#define PFL0_SEC0_WL112 0x1C00
#define PFL0_SEC0_WL113 0x1C40
#define PFL0_SEC0_WL114 0x1C80
#define PFL0_SEC0_WL115 0x1CC0
#define PFL0_SEC0_WL116 0x1D00
#define PFL0_SEC0_WL117 0x1D40
#define PFL0_SEC0_WL118 0x1D80
#define PFL0_SEC0_WL119 0x1DC0

// Sector 1 -- 256 bytes -- 4 Wordlines
#define PFL0_SEC1_WL120 0x1E00
#define PFL0_SEC1_WL121 0x1E40
#define PFL0_SEC1_WL122 0x1E80
#define PFL0_SEC1_WL123 0x1EC0

// Sector 2 -- 256 bytes -- 4 Wordlines
#define PFL0_SEC2_WL124 0x1F00
#define PFL0_SEC2_WL125 0x1F40
#define PFL0_SEC2_WL126 0x1F80
#define PFL0_SEC2_WL127 0x1FC0

//###################################################################################
// WordLine startaddresses for Sectors in PFlash 1, each _WL with 64bytes

// Sector 0 -- 7.5 kbytes -- 120 Wordlines
#define PFL1_SEC0_WL00  0x2000
#define PFL1_SEC0_WL01  0x2040
#define PFL1_SEC0_WL02  0x2080
#define PFL1_SEC0_WL03  0x20C0
#define PFL1_SEC0_WL04  0x2100
#define PFL1_SEC0_WL05  0x2140
#define PFL1_SEC0_WL06  0x2180
#define PFL1_SEC0_WL07  0x21C0
#define PFL1_SEC0_WL08  0x2200
#define PFL1_SEC0_WL09  0x2240
#define PFL1_SEC0_WL10  0x2280
#define PFL1_SEC0_WL11  0x22C0
#define PFL1_SEC0_WL12  0x2300
#define PFL1_SEC0_WL13  0x2340
#define PFL1_SEC0_WL14  0x2380
#define PFL1_SEC0_WL15  0x23C0
#define PFL1_SEC0_WL16  0x2400
#define PFL1_SEC0_WL17  0x2440
#define PFL1_SEC0_WL18  0x2480
#define PFL1_SEC0_WL19  0x24C0
#define PFL1_SEC0_WL20  0x2500
#define PFL1_SEC0_WL21  0x2540
#define PFL1_SEC0_WL22  0x2580
#define PFL1_SEC0_WL23  0x25C0
#define PFL1_SEC0_WL24  0x2600
#define PFL1_SEC0_WL25  0x2640
#define PFL1_SEC0_WL26  0x2680
#define PFL1_SEC0_WL27  0x26C0
#define PFL1_SEC0_WL28  0x2700
#define PFL1_SEC0_WL29  0x2740
#define PFL1_SEC0_WL30  0x2780
#define PFL1_SEC0_WL31  0x27C0
#define PFL1_SEC0_WL32  0x2800
#define PFL1_SEC0_WL33  0x2840
#define PFL1_SEC0_WL34  0x2880
#define PFL1_SEC0_WL35  0x28C0
#define PFL1_SEC0_WL36  0x2900
#define PFL1_SEC0_WL37  0x2940
#define PFL1_SEC0_WL38  0x2980
#define PFL1_SEC0_WL39  0x29C0
#define PFL1_SEC0_WL40  0x2A00
#define PFL1_SEC0_WL41  0x2A40
#define PFL1_SEC0_WL42  0x2A80
#define PFL1_SEC0_WL43  0x2AC0
#define PFL1_SEC0_WL44  0x2B00
#define PFL1_SEC0_WL45  0x2B40
#define PFL1_SEC0_WL46  0x2B80
#define PFL1_SEC0_WL47  0x2BC0
#define PFL1_SEC0_WL48  0x2C00
#define PFL1_SEC0_WL49  0x2C40
#define PFL1_SEC0_WL50  0x2C80
#define PFL1_SEC0_WL51  0x2CC0
#define PFL1_SEC0_WL52  0x2D00
#define PFL1_SEC0_WL53  0x2D40
#define PFL1_SEC0_WL54  0x2D80
#define PFL1_SEC0_WL55  0x2DC0
#define PFL1_SEC0_WL56  0x2E00
#define PFL1_SEC0_WL57  0x2E40
#define PFL1_SEC0_WL58  0x2E80
#define PFL1_SEC0_WL59  0x2EC0
#define PFL1_SEC0_WL60  0x2F00
#define PFL1_SEC0_WL61  0x2F40
#define PFL1_SEC0_WL62  0x2F80
#define PFL1_SEC0_WL63  0x2FC0
#define PFL1_SEC0_WL64  0x3000
#define PFL1_SEC0_WL65  0x3040
#define PFL1_SEC0_WL66  0x3080
#define PFL1_SEC0_WL67  0x30C0
#define PFL1_SEC0_WL68  0x3100
#define PFL1_SEC0_WL69  0x3140
#define PFL1_SEC0_WL70  0x3180
#define PFL1_SEC0_WL71  0x31C0
#define PFL1_SEC0_WL72  0x3200
#define PFL1_SEC0_WL73  0x3240
#define PFL1_SEC0_WL74  0x3280
#define PFL1_SEC0_WL75  0x32C0
#define PFL1_SEC0_WL76  0x3300
#define PFL1_SEC0_WL77  0x3340
#define PFL1_SEC0_WL78  0x3380
#define PFL1_SEC0_WL79  0x33C0
#define PFL1_SEC0_WL80  0x3400
#define PFL1_SEC0_WL81  0x3440
#define PFL1_SEC0_WL82  0x3480
#define PFL1_SEC0_WL83  0x34C0
#define PFL1_SEC0_WL84  0x3500
#define PFL1_SEC0_WL85  0x3540
#define PFL1_SEC0_WL86  0x3580
#define PFL1_SEC0_WL87  0x35C0
#define PFL1_SEC0_WL88  0x3600
#define PFL1_SEC0_WL89  0x3640
#define PFL1_SEC0_WL90  0x3680
#define PFL1_SEC0_WL91  0x36C0
#define PFL1_SEC0_WL92  0x3700
#define PFL1_SEC0_WL93  0x3740
#define PFL1_SEC0_WL94  0x3780
#define PFL1_SEC0_WL95  0x37C0
#define PFL1_SEC0_WL96  0x3800
#define PFL1_SEC0_WL97  0x3840
#define PFL1_SEC0_WL98  0x3880
#define PFL1_SEC0_WL99  0x38C0
#define PFL1_SEC0_WL100 0x3900
#define PFL1_SEC0_WL101 0x3940
#define PFL1_SEC0_WL102 0x3980
#define PFL1_SEC0_WL103 0x39C0
#define PFL1_SEC0_WL104 0x3A00
#define PFL1_SEC0_WL105 0x3A40
#define PFL1_SEC0_WL106 0x3A80
#define PFL1_SEC0_WL107 0x3AC0
#define PFL1_SEC0_WL108 0x3B00
#define PFL1_SEC0_WL109 0x3B40
#define PFL1_SEC0_WL110 0x3B80
#define PFL1_SEC0_WL111 0x3BC0
#define PFL1_SEC0_WL112 0x3C00
#define PFL1_SEC0_WL113 0x3C40
#define PFL1_SEC0_WL114 0x3C80
#define PFL1_SEC0_WL115 0x3CC0
#define PFL1_SEC0_WL116 0x3D00
#define PFL1_SEC0_WL117 0x3D40
#define PFL1_SEC0_WL118 0x3D80
#define PFL1_SEC0_WL119 0x3DC0

// Sector 1 -- 256 bytes -- 4 Wordlines
#define PFL1_SEC1_WL120 0x3E00
#define PFL1_SEC1_WL121 0x3E40
#define PFL1_SEC1_WL122 0x3E80
#define PFL1_SEC1_WL123 0x3EC0

// Sector 2 -- 256 bytes -- 4 Wordlines
#define PFL1_SEC2_WL124 0x3F00
#define PFL1_SEC2_WL125 0x3F40
#define PFL1_SEC2_WL126 0x3F80
#define PFL1_SEC2_WL127 0x3FC0

//###################################################################################
// WordLine startaddresses for Sectors in PFlash 2, each WL with 64bytes

// Sector 0 -- 7.5 kbytes -- 120 Wordlines
#define PFL2_SEC0_WL00  0x4000
#define PFL2_SEC0_WL01  0x4040
#define PFL2_SEC0_WL02  0x4080
#define PFL2_SEC0_WL03  0x40C0
#define PFL2_SEC0_WL04  0x4100
#define PFL2_SEC0_WL05  0x4140
#define PFL2_SEC0_WL06  0x4180
#define PFL2_SEC0_WL07  0x41C0
#define PFL2_SEC0_WL08  0x4200
#define PFL2_SEC0_WL09  0x4240
#define PFL2_SEC0_WL10  0x4280
#define PFL2_SEC0_WL11  0x42C0
#define PFL2_SEC0_WL12  0x4300
#define PFL2_SEC0_WL13  0x4340
#define PFL2_SEC0_WL14  0x4380
#define PFL2_SEC0_WL15  0x43C0
#define PFL2_SEC0_WL16  0x4400
#define PFL2_SEC0_WL17  0x4440
#define PFL2_SEC0_WL18  0x4480
#define PFL2_SEC0_WL19  0x44C0
#define PFL2_SEC0_WL20  0x4500
#define PFL2_SEC0_WL21  0x4540
#define PFL2_SEC0_WL22  0x4580
#define PFL2_SEC0_WL23  0x45C0
#define PFL2_SEC0_WL24  0x4600
#define PFL2_SEC0_WL25  0x4640
#define PFL2_SEC0_WL26  0x4680
#define PFL2_SEC0_WL27  0x46C0
#define PFL2_SEC0_WL28  0x4700
#define PFL2_SEC0_WL29  0x4740
#define PFL2_SEC0_WL30  0x4780
#define PFL2_SEC0_WL31  0x47C0
#define PFL2_SEC0_WL32  0x4800
#define PFL2_SEC0_WL33  0x4840
#define PFL2_SEC0_WL34  0x4880
#define PFL2_SEC0_WL35  0x48C0
#define PFL2_SEC0_WL36  0x4900
#define PFL2_SEC0_WL37  0x4940
#define PFL2_SEC0_WL38  0x4980
#define PFL2_SEC0_WL39  0x49C0
#define PFL2_SEC0_WL40  0x4A00
#define PFL2_SEC0_WL41  0x4A40
#define PFL2_SEC0_WL42  0x4A80
#define PFL2_SEC0_WL43  0x4AC0
#define PFL2_SEC0_WL44  0x4B00
#define PFL2_SEC0_WL45  0x4B40
#define PFL2_SEC0_WL46  0x4B80
#define PFL2_SEC0_WL47  0x4BC0
#define PFL2_SEC0_WL48  0x4C00
#define PFL2_SEC0_WL49  0x4C40
#define PFL2_SEC0_WL50  0x4C80
#define PFL2_SEC0_WL51  0x4CC0
#define PFL2_SEC0_WL52  0x4D00
#define PFL2_SEC0_WL53  0x4D40
#define PFL2_SEC0_WL54  0x4D80
#define PFL2_SEC0_WL55  0x4DC0
#define PFL2_SEC0_WL56  0x4E00
#define PFL2_SEC0_WL57  0x4E40
#define PFL2_SEC0_WL58  0x4E80
#define PFL2_SEC0_WL59  0x4EC0
#define PFL2_SEC0_WL60  0x4F00
#define PFL2_SEC0_WL61  0x4F40
#define PFL2_SEC0_WL62  0x4F80
#define PFL2_SEC0_WL63  0x4FC0
#define PFL2_SEC0_WL64  0x5000
#define PFL2_SEC0_WL65  0x5040
#define PFL2_SEC0_WL66  0x5080
#define PFL2_SEC0_WL67  0x50C0
#define PFL2_SEC0_WL68  0x5100
#define PFL2_SEC0_WL69  0x5140
#define PFL2_SEC0_WL70  0x5180
#define PFL2_SEC0_WL71  0x51C0
#define PFL2_SEC0_WL72  0x5200
#define PFL2_SEC0_WL73  0x5240
#define PFL2_SEC0_WL74  0x5280
#define PFL2_SEC0_WL75  0x52C0
#define PFL2_SEC0_WL76  0x5300
#define PFL2_SEC0_WL77  0x5340
#define PFL2_SEC0_WL78  0x5380
#define PFL2_SEC0_WL79  0x53C0
#define PFL2_SEC0_WL80  0x5400
#define PFL2_SEC0_WL81  0x5440
#define PFL2_SEC0_WL82  0x5480
#define PFL2_SEC0_WL83  0x54C0
#define PFL2_SEC0_WL84  0x5500
#define PFL2_SEC0_WL85  0x5540
#define PFL2_SEC0_WL86  0x5580
#define PFL2_SEC0_WL87  0x55C0
#define PFL2_SEC0_WL88  0x5600
#define PFL2_SEC0_WL89  0x5640
#define PFL2_SEC0_WL90  0x5680
#define PFL2_SEC0_WL91  0x56C0
#define PFL2_SEC0_WL92  0x5700
#define PFL2_SEC0_WL93  0x5740
#define PFL2_SEC0_WL94  0x5780
#define PFL2_SEC0_WL95  0x57C0
#define PFL2_SEC0_WL96  0x5800
#define PFL2_SEC0_WL97  0x5840
#define PFL2_SEC0_WL98  0x5880
#define PFL2_SEC0_WL99  0x58C0
#define PFL2_SEC0_WL100 0x5900
#define PFL2_SEC0_WL101 0x5940
#define PFL2_SEC0_WL102 0x5980
#define PFL2_SEC0_WL103 0x59C0
#define PFL2_SEC0_WL104 0x5A00
#define PFL2_SEC0_WL105 0x5A40
#define PFL2_SEC0_WL106 0x5A80
#define PFL2_SEC0_WL107 0x5AC0
#define PFL2_SEC0_WL108 0x5B00
#define PFL2_SEC0_WL109 0x5B40
#define PFL2_SEC0_WL110 0x5B80
#define PFL2_SEC0_WL111 0x5BC0
#define PFL2_SEC0_WL112 0x5C00
#define PFL2_SEC0_WL113 0x5C40
#define PFL2_SEC0_WL114 0x5C80
#define PFL2_SEC0_WL115 0x5CC0
#define PFL2_SEC0_WL116 0x5D00
#define PFL2_SEC0_WL117 0x5D40
#define PFL2_SEC0_WL118 0x5D80
#define PFL2_SEC0_WL119 0x5DC0

// Sector 1 -- 256 bytes -- 4 Wordlines
#define PFL2_SEC1_WL120 0x5E00
#define PFL2_SEC1_WL121 0x5E40
#define PFL2_SEC1_WL122 0x5E80
#define PFL2_SEC1_WL123 0x5EC0

// Sector 2 -- 256 bytes -- 4 Wordlines
#define PFL2_SEC2_WL124 0x5F00
#define PFL2_SEC2_WL125 0x5F40
#define PFL2_SEC2_WL126 0x5F80
#define PFL2_SEC2_WL127 0x5FC0

//###################################################################################
// WordLine startaddresses for sectors in DFlash 0, each WL with 32bytes
// DFlash 0 address is also mirrorred to 0x7xxx

// Sector 0 -- 1024 bytes -- 32 Wordlines
#define DFL0_SEC0_WL00  0xA000
#define DFL0_SEC0_WL01  0xA020
#define DFL0_SEC0_WL02  0xA040
#define DFL0_SEC0_WL03  0xA060
#define DFL0_SEC0_WL04  0xA080
#define DFL0_SEC0_WL05  0xA0A0
#define DFL0_SEC0_WL06  0xA0C0
#define DFL0_SEC0_WL07  0xA0E0
#define DFL0_SEC0_WL08  0xA100
#define DFL0_SEC0_WL09  0xA120
#define DFL0_SEC0_WL10  0xA140
#define DFL0_SEC0_WL11  0xA160
#define DFL0_SEC0_WL12  0xA180
#define DFL0_SEC0_WL13  0xA1A0
#define DFL0_SEC0_WL14  0xA1C0
#define DFL0_SEC0_WL15  0xA1E0
#define DFL0_SEC0_WL16  0xA200
#define DFL0_SEC0_WL17  0xA220
#define DFL0_SEC0_WL18  0xA240
#define DFL0_SEC0_WL19  0xA260
#define DFL0_SEC0_WL20  0xA280
#define DFL0_SEC0_WL21  0xA2A0
#define DFL0_SEC0_WL22  0xA2C0
#define DFL0_SEC0_WL23  0xA2E0
#define DFL0_SEC0_WL24  0xA300
#define DFL0_SEC0_WL25  0xA320
#define DFL0_SEC0_WL26  0xA340
#define DFL0_SEC0_WL27  0xA360
#define DFL0_SEC0_WL28  0xA380
#define DFL0_SEC0_WL29  0xA3A0
#define DFL0_SEC0_WL30  0xA3C0
#define DFL0_SEC0_WL31  0xA3E0

// Sector 1 -- 1024 bytes -- 32 Wordlines
#define DFL0_SEC1_WL32  0xA400
#define DFL0_SEC1_WL33  0xA420
#define DFL0_SEC1_WL34  0xA440
#define DFL0_SEC1_WL35  0xA460
#define DFL0_SEC1_WL36  0xA480
#define DFL0_SEC1_WL37  0xA4A0
#define DFL0_SEC1_WL38  0xA4C0
#define DFL0_SEC1_WL39  0xA4E0
#define DFL0_SEC1_WL40  0xA500
#define DFL0_SEC1_WL41  0xA520
#define DFL0_SEC1_WL42  0xA540
#define DFL0_SEC1_WL43  0xA560
#define DFL0_SEC1_WL44  0xA580
#define DFL0_SEC1_WL45  0xA5A0
#define DFL0_SEC1_WL46  0xA5C0
#define DFL0_SEC1_WL47  0xA5E0
#define DFL0_SEC1_WL48  0xA600
#define DFL0_SEC1_WL49  0xA620
#define DFL0_SEC1_WL50  0xA640
#define DFL0_SEC1_WL51  0xA660
#define DFL0_SEC1_WL52  0xA680
#define DFL0_SEC1_WL53  0xA6A0
#define DFL0_SEC1_WL54  0xA6C0
#define DFL0_SEC1_WL55  0xA6E0
#define DFL0_SEC1_WL56  0xA700
#define DFL0_SEC1_WL57  0xA720
#define DFL0_SEC1_WL58  0xA740
#define DFL0_SEC1_WL59  0xA760
#define DFL0_SEC1_WL60  0xA780
#define DFL0_SEC1_WL61  0xA7A0
#define DFL0_SEC1_WL62  0xA7C0
#define DFL0_SEC1_WL63  0xA7E0

// Sector 2 -- 512 bytes -- 16 Wordlines
#define DFL0_SEC2_WL64  0xA800
#define DFL0_SEC2_WL65  0xA820
#define DFL0_SEC2_WL66  0xA840
#define DFL0_SEC2_WL67  0xA860
#define DFL0_SEC2_WL68  0xA880
#define DFL0_SEC2_WL69  0xA8A0
#define DFL0_SEC2_WL70  0xA8C0
#define DFL0_SEC2_WL71  0xA8E0
#define DFL0_SEC2_WL72  0xA900
#define DFL0_SEC2_WL73  0xA920
#define DFL0_SEC2_WL74  0xA940
#define DFL0_SEC2_WL75  0xA960
#define DFL0_SEC2_WL76  0xA980
#define DFL0_SEC2_WL77  0xA9A0
#define DFL0_SEC2_WL78  0xA9C0
#define DFL0_SEC2_WL79  0xA9E0

// Sector 3 -- 512 bytes -- 16 Wordlines
#define DFL0_SEC3_WL80  0xAA00
#define DFL0_SEC3_WL81  0xAA20
#define DFL0_SEC3_WL82  0xAA40
#define DFL0_SEC3_WL83  0xAA60
#define DFL0_SEC3_WL84  0xAA80
#define DFL0_SEC3_WL85  0xAAA0
#define DFL0_SEC3_WL86  0xAAC0
#define DFL0_SEC3_WL87  0xAAE0
#define DFL0_SEC3_WL88  0xAB00
#define DFL0_SEC3_WL89  0xAB20
#define DFL0_SEC3_WL90  0xAB40
#define DFL0_SEC3_WL91  0xAB60
#define DFL0_SEC3_WL92  0xAB80
#define DFL0_SEC3_WL93  0xABA0
#define DFL0_SEC3_WL94  0xABC0
#define DFL0_SEC3_WL95  0xABE0

// Sector 4 -- 256 bytes -- 8 Wordlines
#define DFL0_SEC4_WL96  0xAC00
#define DFL0_SEC4_WL97  0xAC20
#define DFL0_SEC4_WL98  0xAC40
#define DFL0_SEC4_WL99  0xAC60
#define DFL0_SEC4_WL100 0xAC80
#define DFL0_SEC4_WL101 0xACA0
#define DFL0_SEC4_WL102 0xACC0
#define DFL0_SEC4_WL103 0xACE0

// Sector 5 -- 256 bytes -- 8 Wordlines
#define DFL0_SEC5_WL104 0xAD00
#define DFL0_SEC5_WL105 0xAD20
#define DFL0_SEC5_WL106 0xAD40
#define DFL0_SEC5_WL107 0xAD60
#define DFL0_SEC5_WL108 0xAD80
#define DFL0_SEC5_WL109 0xADA0
#define DFL0_SEC5_WL110 0xADC0
#define DFL0_SEC5_WL111 0xADE0

// Sector 6 -- 128 bytes -- 4 Wordlines
#define DFL0_SEC6_WL112 0xAE00
#define DFL0_SEC6_WL113 0xAE20
#define DFL0_SEC6_WL114 0xAE40
#define DFL0_SEC6_WL115 0xAE60

// Sector 7 -- 128 bytes -- 4 Wordlines
#define DFL0_SEC7_WL116 0xAE80
#define DFL0_SEC7_WL117 0xAEA0
#define DFL0_SEC7_WL118 0xAEC0
#define DFL0_SEC7_WL119 0xAEE0

// Sector 8 -- 128 bytes -- 4 Wordlines
#define DFL0_SEC8_WL120 0xAF00
#define DFL0_SEC8_WL121 0xAF20
#define DFL0_SEC8_WL122 0xAF40
#define DFL0_SEC8_WL123 0xAF60

// Sector 9 -- 128 bytes -- 4 Wordlines
#define DFL0_SEC9_WL124 0xAF80
#define DFL0_SEC9_WL125 0xAFA0
#define DFL0_SEC9_WL126 0xAFC0
#define DFL0_SEC9_WL127 0xAFE0

//###################################################################################
// WordLine startaddresses for sectors in DFlash 1, each WL with 32bytes
// DFlash 1 address is also mirrorred to 0x6xxx

// Sector 0 -- 1024 bytes -- 32 Wordlines
#define DFL1_SEC0_WL00  0xB000
#define DFL1_SEC0_WL01  0xB020
#define DFL1_SEC0_WL02  0xB040
#define DFL1_SEC0_WL03  0xB060
#define DFL1_SEC0_WL04  0xB080
#define DFL1_SEC0_WL05  0xB0A0
#define DFL1_SEC0_WL06  0xB0C0
#define DFL1_SEC0_WL07  0xB0E0
#define DFL1_SEC0_WL08  0xB100
#define DFL1_SEC0_WL09  0xB120
#define DFL1_SEC0_WL10  0xB140
#define DFL1_SEC0_WL11  0xB160
#define DFL1_SEC0_WL12  0xB180
#define DFL1_SEC0_WL13  0xB1A0
#define DFL1_SEC0_WL14  0xB1C0
#define DFL1_SEC0_WL15  0xB1E0
#define DFL1_SEC0_WL16  0xB200
#define DFL1_SEC0_WL17  0xB220
#define DFL1_SEC0_WL18  0xB240
#define DFL1_SEC0_WL19  0xB260
#define DFL1_SEC0_WL20  0xB280
#define DFL1_SEC0_WL21  0xB2A0
#define DFL1_SEC0_WL22  0xB2C0
#define DFL1_SEC0_WL23  0xB2E0
#define DFL1_SEC0_WL24  0xB300
#define DFL1_SEC0_WL25  0xB320
#define DFL1_SEC0_WL26  0xB340
#define DFL1_SEC0_WL27  0xB360
#define DFL1_SEC0_WL28  0xB380
#define DFL1_SEC0_WL29  0xB3A0
#define DFL1_SEC0_WL30  0xB3C0
#define DFL1_SEC0_WL31  0xB3E0

// Sector 1 -- 1024 bytes -- 32 Wordlines
#define DFL1_SEC1_WL32  0xB400
#define DFL1_SEC1_WL33  0xB420
#define DFL1_SEC1_WL34  0xB440
#define DFL1_SEC1_WL35  0xB460
#define DFL1_SEC1_WL36  0xB480
#define DFL1_SEC1_WL37  0xB4A0
#define DFL1_SEC1_WL38  0xB4C0
#define DFL1_SEC1_WL39  0xB4E0
#define DFL1_SEC1_WL40  0xB500
#define DFL1_SEC1_WL41  0xB520
#define DFL1_SEC1_WL42  0xB540
#define DFL1_SEC1_WL43  0xB560
#define DFL1_SEC1_WL44  0xB580
#define DFL1_SEC1_WL45  0xB5A0
#define DFL1_SEC1_WL46  0xB5C0
#define DFL1_SEC1_WL47  0xB5E0
#define DFL1_SEC1_WL48  0xB600
#define DFL1_SEC1_WL49  0xB620
#define DFL1_SEC1_WL50  0xB640
#define DFL1_SEC1_WL51  0xB660
#define DFL1_SEC1_WL52  0xB680
#define DFL1_SEC1_WL53  0xB6A0
#define DFL1_SEC1_WL54  0xB6C0
#define DFL1_SEC1_WL55  0xB6E0
#define DFL1_SEC1_WL56  0xB700
#define DFL1_SEC1_WL57  0xB720
#define DFL1_SEC1_WL58  0xB740
#define DFL1_SEC1_WL59  0xB760
#define DFL1_SEC1_WL60  0xB780
#define DFL1_SEC1_WL61  0xB7A0
#define DFL1_SEC1_WL62  0xB7C0
#define DFL1_SEC1_WL63  0xB7E0

// Sector 2 -- 512 bytes -- 16 Wordlines
#define DFL1_SEC2_WL64  0xB800
#define DFL1_SEC2_WL65  0xB820
#define DFL1_SEC2_WL66  0xB840
#define DFL1_SEC2_WL67  0xB860
#define DFL1_SEC2_WL68  0xB880
#define DFL1_SEC2_WL69  0xB8A0
#define DFL1_SEC2_WL70  0xB8C0
#define DFL1_SEC2_WL71  0xB8E0
#define DFL1_SEC2_WL72  0xB900
#define DFL1_SEC2_WL73  0xB920
#define DFL1_SEC2_WL74  0xB940
#define DFL1_SEC2_WL75  0xB960
#define DFL1_SEC2_WL76  0xB980
#define DFL1_SEC2_WL77  0xB9A0
#define DFL1_SEC2_WL78  0xB9C0
#define DFL1_SEC2_WL79  0xB9E0

// Sector 3 -- 512 bytes -- 16 Wordlines
#define DFL1_SEC3_WL80  0xBA00
#define DFL1_SEC3_WL81  0xBA20
#define DFL1_SEC3_WL82  0xBA40
#define DFL1_SEC3_WL83  0xBA60
#define DFL1_SEC3_WL84  0xBA80
#define DFL1_SEC3_WL85  0xBAA0
#define DFL1_SEC3_WL86  0xBAC0
#define DFL1_SEC3_WL87  0xBAE0
#define DFL1_SEC3_WL88  0xBB00
#define DFL1_SEC3_WL89  0xBB20
#define DFL1_SEC3_WL90  0xBB40
#define DFL1_SEC3_WL91  0xBB60
#define DFL1_SEC3_WL92  0xBB80
#define DFL1_SEC3_WL93  0xBBA0
#define DFL1_SEC3_WL94  0xBBC0
#define DFL1_SEC3_WL95  0xBBE0

// Sector 4 -- 256 bytes -- 8 Wordlines
#define DFL1_SEC4_WL96  0xBC00
#define DFL1_SEC4_WL97  0xBC20
#define DFL1_SEC4_WL98  0xBC40
#define DFL1_SEC4_WL99  0xBC60
#define DFL1_SEC4_WL100 0xBC80
#define DFL1_SEC4_WL101 0xBCA0
#define DFL1_SEC4_WL102 0xBCC0
#define DFL1_SEC4_WL103 0xBCE0

// Sector 5 -- 256 bytes -- 8 Wordlines
#define DFL1_SEC5_WL104 0xBD00
#define DFL1_SEC5_WL105 0xBD20
#define DFL1_SEC5_WL106 0xBD40
#define DFL1_SEC5_WL107 0xBD60
#define DFL1_SEC5_WL108 0xBD80
#define DFL1_SEC5_WL109 0xBDA0
#define DFL1_SEC5_WL110 0xBDC0
#define DFL1_SEC5_WL111 0xBDE0

// Sector 6 -- 128 bytes -- 4 Wordlines
#define DFL1_SEC6_WL112 0xBE00
#define DFL1_SEC6_WL113 0xBE20
#define DFL1_SEC6_WL114 0xBE40
#define DFL1_SEC6_WL115 0xBE60

// Sector 7 -- 128 bytes -- 4 Wordlines
#define DFL1_SEC7_WL116 0xBE80
#define DFL1_SEC7_WL117 0xBEA0
#define DFL1_SEC7_WL118 0xBEC0
#define DFL1_SEC7_WL119 0xBEE0

// Sector 8 -- 128 bytes -- 4 Wordlines
#define DFL1_SEC8_WL120 0xBF00
#define DFL1_SEC8_WL121 0xBF20
#define DFL1_SEC8_WL122 0xBF40
#define DFL1_SEC8_WL123 0xBF60

// Sector 9 -- 128 bytes -- 4 Wordlines
#define DFL1_SEC9_WL124 0xBF80
#define DFL1_SEC9_WL125 0xBFA0
#define DFL1_SEC9_WL126 0xBFC0
#define DFL1_SEC9_WL127 0xBFE0

#endif  // #ifndef  __XC88x_FLADDR_H__
