//****************************************************************************
// File Name     MemoryXC8.c
// Author        Andreas Jansen, Infineon Technologies
//----------------------------------------------------------------------------
// Derivatives   Infineon XC866
//
// Description   Sets of function to handle the memory in the XC866.
//               In particular, the EEPROM handling is taken care of here.
//
//----------------------------------------------------------------------------
// Date          25.01.2005 10:48:38
// Copyright     (c) 2005 Infineon Technologies
//****************************************************************************

#include "MemoryXC8.h"
#include "MAIN.H"


// Buffer for the 32byte data before being written to eEPROM
//GKunsigned char idata WLBuf[BYTES_PER_WORDLINE];

// **************************************************************************
// Function Name:    void LoadXD2WLBuf (unsigned char xdata *address)
// Description:      Load  32byte of data from the XDATA to the WLBuf
//                   WLBuf is a buffer that is located in the IDATA-space
// Input Parameter:  *address ==>  pointer to the address
// 								   in the XDATA memory
// Output Parameter: none
void LoadXD2WLBuf(unsigned char xdata *address)
{
// Loads Wordline Buffer with 32bytes from given address in XDATA
unsigned char i;
	for (i=0; i<BYTES_PER_WORDLINE; i++) 
	{ WLBuf[i] = *address++;
	}
}


// ***********************************************************************
// Function Name:    void LoadConst2WLBuf (unsigned char code *address)
// Description:      Load 32byte of data from the CODE to the WLBuf
//                   WLBuf is a buffer that is located in the IDATA-space
// Input Parameter:  *address ==>  pointer to the address
// 								   in the CODE memory
// Output Parameter: none
//GKvoid LoadConst2WLBuf(unsigned char code *address)
//GK{
//GK// Loads Wordline Buffer with 32bytes from given address in CODE
//GKunsigned char i;
//GK	for (i=0; i<BYTES_PER_WORDLINE; i++) 
//GK	{ WLBuf[i] = *address++;
//GK	}
//GK}


// *************************************************************************************
// Function Name:    void LoadConst2XD (unsigned char xdata *dstaddress, 
//                   unsigned char code *srcaddress, unsigned int length)
// Description:      Copy the data from the CODE memory to XDATA memory
// Input Parameter:  *srcaddress ==> pointer to the location in the FLASH/EEPROM.
//                   lenght      ==> The number of byte to be copied
// Output Parameter: *dstaddress ==> pointer to the location in the XDATA memory.
//                                   The data will be copied to this location
//GKvoid LoadConst2XD(unsigned char xdata *dstaddress, unsigned char code *srcaddress, unsigned int length)
//GK{
//GK// Loads number of constants to XDATA at given addresses
//GKunsigned int i;
//GK	for (i=0; i<length; i++) 
//GK	{ *dstaddress++ = *srcaddress++;
//GK	}
//GK}

// *************************************************************************************
// Function Name:    void LoadXD2XD (unsigned char xdata *dstaddress, 
//                   unsigned char xdata *srcaddress, unsigned int length)
// Description:      Copy the data from the XDATA memory to XDATA memory
// Input Parameter:  *srcaddress ==> pointer to the location in the XDATA memory.
//                                   No byte alignment is necessary
//                   lenght      ==> The number of byte to be copied
// Output Parameter: *dstaddress ==> pointer to the location in the XDATA memory.
//                                   The data will be copied to this location
//GKvoid LoadXD2XD(unsigned char xdata *dstaddress, unsigned char xdata *srcaddress, unsigned int length)
//GK{
//GK// Copies number of bytes in XDATA to XDATA at given addresses
//GKunsigned int i;
//GK	for (i=0; i<length; i++) 
//GK	{ *dstaddress++ = *srcaddress++;
//GK	}
//GK}

// *************************************************************************************
// Function Name:    unsigned char ReadIdata (unsigned char idata *address) 
// Description:      Read from IDATA memory
// Input Parameter:  *address ==> pointer to the location in the IDATA memory.
//                                No byte alignment is necessary
// Return Value:	 Data Byte
//GKunsigned char ReadIdata(unsigned char idata *address)
//GK{
//GK// Read Idata at given address
//GKreturn (*address);
//GK}


//
// .......... wichtig ..........
//				 |

// **************************************************************************************
// Function Name:    void ProgWL (unsigned char code *AdrBnkXSecYWLZ)
// Description:      Program the data from the WLBuf to the location in the EEPROM
//                   which is pointed by *ADrBnkXSecYWLZ
// Input Parameter:  *AdrBnkXSecYWLZ ==> pointer to the location in the EEPROM.
//                                       The address must be aligned to a 32byte boundary
// Output Parameter: none 
bit ProgWL(unsigned char code *AdrBnkXSecYWLZ)
{
    unsigned int i;
	
	i = AdrBnkXSecYWLZ;
	MEM_DPH = i>>8;
	MEM_DPL = i;
	//_FlProg(SrcBuf);
	return FlProg(&WLBuf[0]);
}

// *************************************************************************************
// Function Name:    unsigned char ReadConst (unsigned char const *address) 
// Description:      Read from CODE memory
// Input Parameter:  *address ==> pointer to the location in the CODE memory.
//                                No byte alignment is necessary
// Return Value:	 Data Byte
//GKunsigned char ReadConst(unsigned char code *address)
//GK{
//GK	return (*address);
//GK}

//GKunsigned int ReadInt(unsigned int code *address)
//GK{
//GK	return (*address);
//GK}
