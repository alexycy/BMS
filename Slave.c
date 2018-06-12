#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MemoryXC8.h"
#include "Routines.h"
#include "Flash.h"


#ifdef SLAVE_BOARDS

// global variables
unsigned int volatile CAN_MODATA_H[16] = { CAN_MODATAH16,  CAN_MODATAH17,  CAN_MODATAH18,  CAN_MODATAH19,  \
                               			   CAN_MODATAH20,  CAN_MODATAH21,  CAN_MODATAH22,  CAN_MODATAH23,  \
										   CAN_MODATAH24,  CAN_MODATAH25,  CAN_MODATAH26,  CAN_MODATAH27,  \
										   CAN_MODATAH28,  CAN_MODATAH29,  CAN_MODATAH30,  CAN_MODATAH31 
                                         };  
unsigned int volatile CAN_MODATA_L[16] = { CAN_MODATAL16,  CAN_MODATAL17,  CAN_MODATAL18,  CAN_MODATAL19,  \
                               			   CAN_MODATAL20,  CAN_MODATAL21,  CAN_MODATAL22,  CAN_MODATAL23,  \
										   CAN_MODATAL24,  CAN_MODATAL25,  CAN_MODATAL26,  CAN_MODATAL27,  \
										   CAN_MODATAL28,  CAN_MODATAL29,  CAN_MODATAL30,  CAN_MODATAL31 
                                         };  
unsigned int volatile CAN_MOCTR[16]    = { CAN_MOCTR16,  CAN_MOCTR17,  CAN_MOCTR18,  CAN_MOCTR19,  \
                               	      	   CAN_MOCTR20,  CAN_MOCTR21,  CAN_MOCTR22,  CAN_MOCTR23,  \
								      	   CAN_MOCTR24,  CAN_MOCTR25,  CAN_MOCTR26,  CAN_MOCTR27,  \
								      	   CAN_MOCTR28,  CAN_MOCTR29,  CAN_MOCTR30,  CAN_MOCTR31 
                                         };  


// global const 
const unsigned int Board[16] = { 0x0001, 0x002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, \
                                 0x0100, 0x200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000}; 



#define StartWithMO                16u                                                          
#define AllocateMessageObject(x)   (0x02000002LU | ((unsigned long)x<<16))
#define DeallocateMessageObject(x) (0x00000002LU | ((unsigned long)x<<16))



//********************************************************
//		   Allocate of CAN Msg Obj 4, 5, 16-31 
//********************************************************                
void SlaveAllocateRelevantMessageObjects( char SlaveName )
{
   CAN_vWriteCANAddress(CAN_PANCTR);                                   // Addressing CAN_PANCTR
   CAN_vSetListCommand(AllocateMessageObject(4));                      // MO4 for list 2	   = ping
   CAN_vSetListCommand(AllocateMessageObject(5));                      // MO5 for list 2	   = errors
   CAN_vSetListCommand(AllocateMessageObject(SlaveName+StartWithMO));  // MO16-MO31 for list 2 = data		             	   
}

//********************************************************
//		        all used CAN MO are deallocated
//********************************************************                
void SlaveDeallocateAllMessageObjects( void )
{
   CAN_vWriteCANAddress(CAN_PANCTR);                  // Addressing CAN_PANCTR
   CAN_vSetListCommand(DeallocateMessageObject(0));   // MO0  for list 2 = data, not more in usage!!!
   CAN_vSetListCommand(DeallocateMessageObject(1));   // MO1  for list 2 = data, not more in usage!!!
   CAN_vSetListCommand(DeallocateMessageObject(2));   // MO2  for list 2 = data, not more in usage!!!
   CAN_vSetListCommand(DeallocateMessageObject(3));   // MO3  for list 2 = data, not more in usage!!!
   CAN_vSetListCommand(DeallocateMessageObject(4));   // MO4  for list 2 = ping
   CAN_vSetListCommand(DeallocateMessageObject(5));   // MO5  for list 2 = errors
   // 16 MO for 16 boards are implemented
   CAN_vSetListCommand(DeallocateMessageObject(16));  // MO16 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(17));  // MO17 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(18));  // MO18 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(19));  // MO19 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(20));  // MO20 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(21));  // MO21 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(22));  // MO22 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(23));  // MO23 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(24));  // MO24 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(25));  // MO25 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(26));  // MO26 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(27));  // MO27 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(28));  // MO28 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(29));  // MO29 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(30));  // MO30 for list 2 = data
   CAN_vSetListCommand(DeallocateMessageObject(31));  // MO31 for list 2 = data
}


//********************************************************
//		        HAS SLAVE BEEN PINGED?
//********************************************************                
unsigned int SlaveHasBeenPinged(SlaveData *pSlaveData)
{
   volatile unsigned char RxStatus = 0;
   unsigned int idata     dat      = 0;

   // board name don't existing:Service mode
   if(pSlaveData->Name < 0)
    return 0; 
   
   // address status register 
   CAN_vWriteCANAddress(CAN_MOCTR4);                     
   // enable
   CAN_vReadEN();
   // read data  
   RxStatus = CAN_DATA0; 
     
   // data is pending 
   if( (RxStatus & MOSTAT_RXPND) == MOSTAT_RXPND )
   {	  
	  // clear flag
	  pSlaveData->Error     &= ~SlaveGetsNoPing;
	  pSlaveData->ErrorType &= ~CommunicationFailure;

	  // read the receiving data?		                  
      CAN_vWriteCANAddress(CAN_MODATAL4);      
      // enable
      CAN_vReadEN();	            	   	        
      // read value  	
      dat = CAN_DATA01;

      // IN- or INTER-BLOCK-BALANCING   
      if( dat & Board[pSlaveData->Name] ) 
        //    a '1' is receiving
        pSlaveData->BLOCK_BALANCING = INTER_BLOCK;
      else // a '0' is receiving		     			          
        pSlaveData->BLOCK_BALANCING = IN_BLOCK;
      	 				 
      // address status register    
      CAN_vWriteCANAddress(CAN_MOCTR4);
      // write bit
      CAN_DATA0 = MOSTAT_RXPND;  
      // enable
      CAN_vWriteEN(D0_VALID);    
	  // return received data
	  return dat;
    }
   else	 // no pending data
   {
     // save error
     pSlaveData->Error     |= SlaveGetsNoPing; 
     pSlaveData->ErrorType |= CommunicationFailure;	
	 
	 return 0;	
   }
}       	  	 	                	 	


//********************************************************
//		        HAS SLAVE BEEN REQUESTED?
//********************************************************                
char SlaveHasBeenRequested(SlaveData *pSlaveData)
{
   volatile unsigned char RxStatus = 0;
   volatile unsigned long i;

   // board name don't existing:Service mode
   if(pSlaveData->Name < 0)
    return 0; 

   // times	some sec.
   for(i=0; i<50000UL; i++)
   {
      // address status register 
      CAN_vWriteCANAddress(CAN_MOCTR[pSlaveData->Name]);	 
      // enable
      CAN_vReadEN();
      // read data  
      RxStatus = CAN_DATA0; 
      // no request pending
	  if( (RxStatus & MOSTAT_RXPND) != MOSTAT_RXPND )
		   continue;
	  else // okay
	       return 0;
   }

    // save error
    pSlaveData->Error     |= SlaveGetsNoReq; 
    pSlaveData->ErrorType |= CommunicationFailure;		 
    // error
    return 1;	
}       	  	 	                	 	

//********************************************************
//				  SLAVE READ COMMAND PIPE
//********************************************************                
void SlaveErrorProcessing(SlaveData *pSlaveData)
{  
   // board name don't existing:Service mode
   if(pSlaveData->Name < 0)
    return; 
      
   // checks board failure
   if( (pSlaveData->Error    & (BlockUnderLevel | TempOverLevel | CellUnderLevel  | CellOverLevel | SlaveGetsNoPing) ) || \
       (pSlaveData->ErrorType &   (BoardFailure | CommunicationFailure) ))
   {   	   
         
   #if defined (PRINT_ERROR)
	 printf("ErrorType: 0x%bx ErrorID: 0x%bx\n", (unsigned char)pSlaveData->ErrorType, (unsigned char)pSlaveData->Error);
   #endif
   
   #ifdef FLASH_DATA   
	 // read flash
	 FlashCalculateAdr(pSlaveData);	 	     	 
	 // and buffer errors
     FlashBufferErrors(pSlaveData);	           	 										 
	 // flash errors
	 FlashErrors(pSlaveData);     	 	         
   #endif
   	   
   	 // send out MO5 to Master
     CAN_vWriteCANAddress(CAN_MODATAL5);                    
     // load error data
     CAN_DATA0 = (unsigned char)(pSlaveData->ErrorType);                            
     CAN_DATA1 = (unsigned char)(pSlaveData->Error);                                                
     // declare both values as valid
     CAN_vWriteEN(D0_VALID+D1_VALID);               
	 // slave sends System Failure to Master
     CAN_vTransmit(5);  
   }
}

//********************************************************
//			      PREPARE BOARDS FOR CAN
//******************************************************                
void SlavePrepareOwnBoardDataForCAN(SlaveData *pSlaveData)
{
   // board name don't existing:Service mode
   if(pSlaveData->Name < 0)
    return; 
   
   // store board min cell format Q4.12 -> Q11.5
   pSlaveData->CanData.MinCell =      (unsigned char)(pSlaveData->Umin_u >> 7);    
   // store board max cell format Q4.12 -> Q11.5
   pSlaveData->CanData.MaxCell =      (unsigned char)(pSlaveData->Umax_u >> 7);   
   // store board min temp format Q16.0
   pSlaveData->CanData.MinTemp =      (int)(pSlaveData->Tmin);	                 
   // store board max temp format Q16.0
   pSlaveData->CanData.MaxTemp =      (int)(pSlaveData->Tmax);	                 
   // store board voltage format Q8.8
   pSlaveData->CanData.BoardVoltage = (unsigned int)(pSlaveData->Ublock);   

   // write buffer with 4 byte
   CAN_vWriteCANAddress(CAN_MODATA_L[pSlaveData->Name]);                    
   // format Q11.5
   CAN_DATA0  =	                      (unsigned char)pSlaveData->CanData.MaxCell;		
   // format Q11.5
   CAN_DATA1  =	                      (unsigned char)pSlaveData->CanData.MinCell;		
   // format Q16.0
   CAN_DATA23 =                       (int)pSlaveData->CanData.MinTemp;               	   
   // declare both values as valid
   CAN_vWriteEN(ALL_DATA_VALID);           
   
   // write buffer with 4 byte           	   
   CAN_vWriteCANAddress(CAN_MODATA_H[pSlaveData->Name]);	       	   	      
   // format Q16.0
   CAN_DATA01 =                       (int)pSlaveData->CanData.MaxTemp;		        
   // format Q8.8	
   CAN_DATA23 =                       (unsigned int)pSlaveData->CanData.BoardVoltage;  
   // declare both values as valid
   CAN_vWriteEN(ALL_DATA_VALID);                        	 
}


#endif

