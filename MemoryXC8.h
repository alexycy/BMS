
// Header for MemoryCopy.c
// Memory handling of XC866 derivatives

#ifndef _MEMORYCOPY_H
#define _MEMORYCOPY_H

#include "MAIN.H"
#include "XC88x_FLADDR.H"

// Header for MemoryCopy.c
// CODE memory  = 0xA000 - 0xAFFF
// XDATA memory = 0xF000 - 0xF1FF
// IDATA memory = 0x0 - 0xFF

extern unsigned char idata WLBuf[BYTES_PER_WORDLINE];

// Function to program the WLBuf 
bit ProgWL(unsigned char code *AdrBnkXSecYWLZ);
// Function to load the data from XDATA memory to WLBuf
void LoadXD2WLBuf(unsigned char xdata *address);
// Function to load the data from CODE memory to WLBuf
//GKvoid LoadConst2WLBuf(unsigned char code *address);
// Function to load the data from CODE memory to XDATA memory
//GKvoid LoadConst2XD(unsigned char xdata *dstaddress, unsigned char code *srcaddress, unsigned int length);
// Function to read a byte from IDATA memory
//unsigned char ReadIdata(unsigned char idata *address);
// Function to read a byte from CODE memory
//GKunsigned char ReadConst(unsigned char code *address);
//GKunsigned int ReadInt(unsigned int code *address);
// Function to check if the flash is ready after erase or program
//unsigned char FlReadyNoInt (void);


//GK// All of the description of the functions below is done in XC866_FLHANDER.ASM
//GK// Erase Flash Sectors
//GK// Required Stack Size = 10
//GKextern bit PFlErase (unsigned char Bank0Sector, unsigned char Bank1Sector, unsigned char Bank2Sector);
//GK#ifdef XC866BB
//GKextern bit DFlErase (unsigned int Bank3Sector);
//GK#endif
//GK#ifdef XC88xAA
//GKextern bit DFlErase (unsigned int DFlash0Sector, unsigned int DFlash1Sector);
//GK#endif
//GK#ifdef XC88xAB
//GKextern bit DFlErase (unsigned int DFlash0Sector, unsigned int DFlash1Sector);
//GK#endif

// All of the description of the functions below is done in XC88x_FLHANDER.ASM
// Erase Flash Sectors
// Required Stack Size = 12
//GKextern bit PFlErase (unsigned char Bank0Sector, unsigned char Bank1Sector, unsigned char Bank2Sector);
extern bit DFlErase (unsigned int DFlash0Sector, unsigned int DFlash1Sector);


//extern void FlErase (unsigned int sectors);
//extern void FlashTimer(void);
extern bit FlProg(unsigned char idata *SrcBuf);

// Check if Flash is ready to read
// Bank = Bank Number to be checked
// Required Stack Size = 5
extern bit FlReady(unsigned char Bank);

// Abort the existing erase process
// Required Stack Size = 5
//GKextern bit FlEraseAbort(void);

sfr MEM_DPH    = 0x83;    
sfr MEM_DPL    = 0x82;
sfr MEM_NMICON = 0xBB;
sfr MEM_NMISR  = 0xBC;

#endif
