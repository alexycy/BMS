#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MemoryXC8.h"
#include "Routines.h"


//********************************************************
//			         FLASH ROUTINE
//********************************************************                
void FlashCalculateAdr( SlaveData *pSlaveData )
{
   unsigned int idata SectorAdr;
   char idata WL, WL_Start;
   
   // define WL
   if(*(unsigned long code *)FlashB400 != 0 && *(unsigned long code *)FlashB7E0 == 0) 
        // second sector
        WL_Start=32;  
   else // first sector
        WL_Start= 0;  
   
   // Wl = Wordline = 32 Byte
   for(WL=WL_Start; WL<((FlashB800-FlashB000)/sizeof(WLBuf))+1; WL++)
   {	    	       
     // calculate start address	from 0xB000...0xB3E0 or 0xB400....0xB800
     SectorAdr = FlashB000 + (sizeof(WLBuf) * WL);
     // search the empty line     
     if( *(unsigned long code *)SectorAdr == 0 ) 
       break; 
   }
  
   // check address
   if(SectorAdr == FlashB000 || SectorAdr == FlashB800)
   {  
     // next free adress
     pSlaveData->FlashData.NextSectorAdr    = FlashB000;
     // current adress
     pSlaveData->FlashData.CurrentSectorAdr = FlashB7E0;     
   }     
   else
   {          
     // next free adress
     pSlaveData->FlashData.NextSectorAdr    = SectorAdr;
     // current address
     pSlaveData->FlashData.CurrentSectorAdr = SectorAdr - sizeof(WLBuf);
   }
   
   printf("read from FlashAdr:0x%x\n", (unsigned int)pSlaveData->FlashData.CurrentSectorAdr);          
   printf("-> next empty FlashAdr:0x%x\n", (unsigned int)pSlaveData->FlashData.NextSectorAdr);          
}


//********************************************************
//			         FLASH ROUTINE
//********************************************************                
void FlashErrors( SlaveData *pSlaveData )
{
   char idata SectorNo;
   unsigned char xdata *pAdr = NULL;
   static unsigned char FlashValue = 0;

   // only 3 times flash possible
   if( FlashValue <= 2  )
   {
     // calculate sector 0 or 1
     if(pSlaveData->FlashData.NextSectorAdr < FlashB800)  SectorNo = 1;
     if(pSlaveData->FlashData.NextSectorAdr < FlashB400)  SectorNo = 0;

     // which Sector No?
     switch( SectorNo )
     {
       case 0: //******************************************************
  			   //            address where to save value 0xB000
  			   //******************************************************     
   			 
   		       // fill internal RAM buffer
   		       LoadXD2WLBuf( (unsigned char xdata *)&pSlaveData->FlashData );
   		       // program flash
   		       ProgWL( (unsigned char code *)pSlaveData->FlashData.NextSectorAdr );
   		       // wait until ready
   		       while(FlReady(4) == 0);
   		       
  		       // new current sector address
  		       pSlaveData->FlashData.CurrentSectorAdr = pSlaveData->FlashData.NextSectorAdr;
  		       // new next sector address
  		       pSlaveData->FlashData.NextSectorAdr    = pSlaveData->FlashData.CurrentSectorAdr+sizeof(WLBuf);

		       // erase flash bank 1
  		       if(pSlaveData->FlashData.CurrentSectorAdr == FlashB000_20) 
  		       {
	             // erase D-flash1 sector 1
                 DFlErase(0, DFL1_SEC1);
   		         // wait until ready
   		         while(FlReady(4) == 0);
  		       }

   		       break;

       case 1: //******************************************************
		       //            address where to save value 0xB400
		       //****************************************************** 
   		       
   		       // fill internal RAM buffer
   		       LoadXD2WLBuf( (unsigned char xdata *)&pSlaveData->FlashData );
   		       // program flash
   		       ProgWL( (unsigned char code *)pSlaveData->FlashData.NextSectorAdr );
   		       // wait until ready
   		       while(FlReady(4) == 0);						

		       // new current sector address
  		       pSlaveData->FlashData.CurrentSectorAdr = pSlaveData->FlashData.NextSectorAdr;			 
  		       // new next sector address
  		       pSlaveData->FlashData.NextSectorAdr    = pSlaveData->FlashData.CurrentSectorAdr+sizeof(WLBuf);
  		       // update next sector address
  		       if(pSlaveData->FlashData.CurrentSectorAdr >= FlashB7E0) 
  		          pSlaveData->FlashData.NextSectorAdr     = FlashB000;
  		    	 
  		       // erase flash bank 0
  		       if(pSlaveData->FlashData.CurrentSectorAdr == FlashB400_20) 
  		       {
                 // erase D-flash1 sector 0
                 DFlErase(0, DFL1_SEC0);
   		    	 // wait until ready
   		    	 while(FlReady(4) == 0);
  		       }
  		    	 
   		       break;

	   // clear flash
	   default: // erase D-flash1 sector 0
                DFlErase(0, DFL1_SEC0);
                // wait until ready
                while(FlReady(4) == 0);
	            // erase D-flash1 sector 1
                DFlErase(0, DFL1_SEC1);
                // wait until ready
                while(FlReady(4) == 0);			  			          
           	    // read flash
           	    FlashCalculateAdr(pSlaveData);
				printf("Error: wrong flash sector!!!\n\n");
			    break;
     } 

     printf("written to FlashAdr:0x%x \n", (unsigned int)pSlaveData->FlashData.CurrentSectorAdr);        
     printf("-> next empty FlashAdr:0x%x\n", (unsigned int)pSlaveData->FlashData.NextSectorAdr);        
	 // update
     FlashValue++;
   }
}

//********************************************************
//			         READ FLASH DATA
//********************************************************                
void FlashReadErrors( SlaveData *pSlaveData )
{
   volatile unsigned char a=0, b=0, c=0, d=0;
   
   a=((*(char code *)(pSlaveData->FlashData.CurrentSectorAdr+12))&0x02)>>1;
   b=((*(char code *)(pSlaveData->FlashData.CurrentSectorAdr+12))&0x08)>>3;
   c=((*(char code *)(pSlaveData->FlashData.CurrentSectorAdr+12))&0x10)>>4;
   d=((*(char code *)(pSlaveData->FlashData.CurrentSectorAdr+12))&0x20)>>5;

   printf("Read flashed Errors (0x%x):\n", ( unsigned int)pSlaveData->FlashData.CurrentSectorAdr);
   printf("- SlaveGetsNoPing: %bu\n", a );
   printf("- BlockUnderLevel: %bu\n", b );
   printf("- TempShortCut:    %bu\n", c );
   printf("- TempOpen:        %bu\n", d );
   printf("- TempOverlevel:  0x%bx\n",  *(unsigned char code *)(pSlaveData->FlashData.CurrentSectorAdr+11));
   printf("- CellUnderlevel: 0x%bx\n",  *(unsigned char code *)(pSlaveData->FlashData.CurrentSectorAdr+10));
   printf("- CellOverLevel:  0x%bx\n",  *(unsigned char code *)(pSlaveData->FlashData.CurrentSectorAdr+ 9));
}

//********************************************************
//			            SAVE ERRORS
//********************************************************                
void FlashBufferErrors( SlaveData *pSlaveData)
{  
   // save error/warning 		
   if(pSlaveData->Error & CellOverLevel)  
      pSlaveData->FlashData.CellOverLevel  = (0xF0 + pSlaveData->BalanceCellIndex[0]);
   if(pSlaveData->Error & CellUnderLevel) 
      pSlaveData->FlashData.CellUnderLevel = (0xF0 + pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex]);
   if(pSlaveData->Error & TempOverLevel)	    
      pSlaveData->FlashData.TempOverLevel  = (0xF0 + pSlaveData->TempIndex[0]);
   
   if(pSlaveData->Error & SlaveGetsNoPing)	    
      pSlaveData->FlashData.FurtherErrorBits.SlaveGetsNoPing = 1;
   if(pSlaveData->Error & BlockUnderLevel)	    
      pSlaveData->FlashData.FurtherErrorBits.BlockUnderLevel = 1;     
 	 
   // save warnings
   if(pSlaveData->Warning & TempShortCut)   
      pSlaveData->FlashData.FurtherErrorBits.TempShortCut = 1;
   if(pSlaveData->Warning & TempOpen)	    
      pSlaveData->FlashData.FurtherErrorBits.TempOpen     = 1;
}


//********************************************************
//			         FLASH ROUTINE
//********************************************************                
void FlashBoardCorrValues( unsigned int *buffer )
{
   // erase D-flash 1 sector 9
   DFlErase(0, DFL1_SEC9);			 
   // wait until ready
   while(FlReady(4) == 0);
   
   // fill internal RAM buffer
   LoadXD2WLBuf( (unsigned char xdata*)buffer );
   // program flash
   ProgWL( (unsigned char code *)FlashAddress_BFEO );
   // wait until ready
   while(FlReady(4) == 0);
   // print
   printf("\nboard parameter flashed at address 0x%x \n\n",FlashAddress_BFEO);
}

//********************************************************
//			         FLASH ROUTINE
//********************************************************                
void FlashReadBoardCorrValues( SlaveData *pSlaveData )
{
  unsigned char i;
  
  // add Offset
  printf("\nRead Flash Cal. Fac.:\n");
  for(i=0; i<Cells; i++)
  {
    pSlaveData->Ufac_u[i] = *(unsigned int code *)(FlashAddress_BFEO+(sizeof(unsigned int)*i));     
    printf(" cal.fac. cell%bu: %.4f\n", i, (float)pSlaveData->Ufac_u[i]/(32*Ucell_Grade));
  } 
  // block voltage corr value
  pSlaveData->Ufac_u[Cells] = *(unsigned int code *)(FlashAddress_BFEO+(sizeof(unsigned int)*Cells));     
    printf(" cal.fac. block: %.4f\n", (float)pSlaveData->Ufac_u[Cells]/Ublock_Grade);           
}
