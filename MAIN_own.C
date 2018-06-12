//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       BM_Master.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          10.08.2007 14:17:24
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)
// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (MAIN_General,2)
#include "Routines.h"
#include "MemoryXC8.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "Flash.h"
#include "Service.h"

#ifdef SLAVE_BOARDS
#include "Slave.h"
#endif


//****************************************************************************
//                         CHECK COMPILER SWITCH
//****************************************************************************
#if defined (SLAVE_BOARDS)
	#if defined (A123_BATTERY_10_CELLS)
	    #message "A123: Slave + 10 Cells"   
	#elif defined (LITEC_BATTERY_12_CELLS)
	      #message "Litec: Slave + 12 Cells" 
	#elif defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
		  #message "Panasonic/Maxwell: Slave + 12 Cells"
	#elif defined (MAXWELL_9_CELLS)
		  #message "Maxwell: Slave + 9 Cells - not yet adapted..."
	#else
	  #error "Slave: wrong compiler switch"
	#endif
#else
  #error "wrong compiler switch"
#endif
 

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Switches
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)
//SLAVE_BOARDS SM_LIGHT PRINT_ERROR PRINT FLASH_DATA A123_BATTERY_10_CELLS
//SLAVE_BOARDS SM_LIGHT PRINT_ERROR PRINT FLASH_DATA LITEC_BATTERY_12_CELLS
//SLAVE_BOARDS SM_LIGHT PRINT_ERROR PRINT FLASH_DATA PANASONIC_12_CELLS
//SLAVE_BOARDS SM_LIGHT PRINT_ERROR PRINT FLASH_DATA MAXWELL_12_CELLS
//SLAVE_BOARDS SM_LIGHT PRINT_ERROR PRINT FLASH_DATA MAXWELL_9_CELLS

//#define SLAVE_BOARDS
//#define PRINT
//#define PRINT_ERROR
//#define PRINT_WARNING
//#define FLASH_DATA 
//#define A123_BATTERY_10_CELLS	or LITEC_BATTERY_12_CELLS or PANASONIC_12_CELLS or MAXWELL_12_CELLS or MAXWELL_9_CELLS
//#define SM_LIGHT

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// ADC register definition
sfr16   RESULT_REGISTER_0   =  0xCA;
sfr16	RESULT_REGISTER_1	=  0xCC;
sfr16	RESULT_REGISTER_2	=  0xCE;
sfr16	RESULT_REGISTER_3	=  0xD2;

// MDU register definition
sfr16   MDU_Operand1 =  0xB2; 
sfr16   MDU_Operand2 =  0xB4;
sfr16   MDU_Operand3 =  0xB6;

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)
volatile SlaveData sSlaveData;
volatile SlaveData *pSlaveData = &sSlaveData; 
volatile char idata FLAG_Pin;
// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

void MeasSequentialChannels_1_to_3(SlaveData *pSlaveData);
void MeasParallelChannels_4_to_7(SlaveData *pSlaveData);
void MeasSequentialChannel_0(SlaveData *pSlaveData);
void IsTemperatureAndBlockOutOfRange(SlaveData *pSlaveData);
void IsAnyCellOutOfRange(SlaveData *pSlaveData);
void Print(SlaveData *pSlaveData);
void PrintAll(SlaveData *pSlaveData);
void PrintDigit(SlaveData *pSlaveData);
void CellBalancing(SlaveData *pSlaveData);
void NormalMode(SlaveData *pSlaveData);
char BoardIdentification(SlaveData *pSlaveData);
void ScanTempAndBlockVoltage(SlaveData *pSlaveData);
void ScanCells(SlaveData *pSlaveData);
void MDU_ScaleCells(SlaveData *pSlaveData);
void BalancingType(char Type);
void CheckTempAndBlock( SlaveData *pSlaveData );
void CheckCells( SlaveData *pSlaveData );
void CheckAllConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop);
void CheckCellConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop);
void CheckBlockConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop);
void CheckComCondition(char *STATE, SlaveData *pSlaveData, unsigned int *loop);


// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller. It is 
//                assumed that the SFRs are in their reset state.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          10.08.2007
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Init,1)

// USER CODE END

void MAIN_vInit(void)
{
  // USER CODE BEGIN (MAIN_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - External Osc is selected (configuration is done in the startup file 
  ///    'START_XC.A51')
  ///  - PLL Mode, NDIV =  24
  ///  - input frequency is 8 MHz


  //   FCLK runs at 2 times the frequency of PCLK.
  SFR_PAGE(_su1, noSST);         // switch to page1

  CMCON         =  0x10;         // load Clock Control Register

  SFR_PAGE(_su0, noSST);         // switch to page0


  ///  *********************************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  *********************************************************************************

  ///  Initialization of module 'GPIO'
  IO_vInit();

  ///  Initialization of module 'Interrupt Unit'
  INT_vInit();

  ///  Initialization of module 'UART (Serial Interface)'
  UART_vInit();

//GK  ///  Initialization of module 'Timer 0/1'
//GK  T01_vInit();

  ///  Initialization of module 'Analog / Digital Converter (ADC)'
  ADC_vInit();

  ///  Initialization of module 'Capture / Compare Unit 6 (CCU6)'
  CC6_vInit();
  
  ///  Initialization of module 'MultiCAN Controller '    
  CAN_vInit();

  ///  Initialization of  'Shared interrupts'
//  SHINT_vInit();


  //   Interrupt Priority

  IP            =  0x20;         // load Interrupt Priority Register
  IPH           =  0x00;         // load Interrupt Priority High Register
  IP1           =  0x20;         // load Interrupt Priority 1 Register
  IPH1          =  0x30;         // load Interrupt Priority 1 High Register


  // USER CODE BEGIN (MAIN_Init,3)

  //// Interrupt structure 2 mode 0 is selected.

  //// Interrupt service routine choice 2 is selected.

  //   globally enable interrupts
  EA            =  1;           

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          10.08.2007
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Main,1)
   
// USER CODE END

void main(void)
{
  // USER CODE BEGIN (MAIN_Main,2)
      
  // USER CODE END

  MAIN_vInit();
  TI = 1;
  CLEAR; POS;
  
  //********************************************************
  //		              INIT
  //********************************************************
  {
   unsigned int i, n;
   unsigned char* r;
   

#if defined (A123_BATTERY_10_CELLS)    
   SFR_PAGE(_cc1, noSST);         // switch to page 1           
   CCU6_T12PRL    =  0x62;        // load CCU6 T12 period register low	   (4,125탎)
   CCU6_T12PRH    =  0x00;        // load CCU6 T12 period register lhigh
   SFR_PAGE(_cc0, noSST);         // switch to page 0
   CCU6_TCTR4L    =  0x40;        // load CCU6 timer control register 4 low
   CCU6_TCTR4H    =  0x40;        // load CCU6 timer control register 4 high
#elif defined (LITEC_BATTERY_12_CELLS)
   SFR_PAGE(_cc1, noSST);         // switch to page 1           
   CCU6_T12PRL    =  0xAA;        // load CCU6 T12 period register low	   (7,125탎)
   CCU6_T12PRH    =  0x00;        // load CCU6 T12 period register lhigh
   SFR_PAGE(_cc0, noSST);         // switch to page 0
   CCU6_TCTR4L    =  0x40;        // load CCU6 timer control register 4 low
   CCU6_TCTR4H    =  0x40;        // load CCU6 timer control register 4 high
#elif defined (MAXWELL_12_CELLS)
   SFR_PAGE(_cc1, noSST);         // switch to page 1        
   CCU6_T12PRL    =  0x47;        // load CCU6 T12 period register low	   (3,0탎)
   CCU6_T12PRH    =  0x00;        // load CCU6 T12 period register lhigh
   SFR_PAGE(_cc0, noSST);         // switch to page 0
   CCU6_TCTR4L    =  0x40;        // load CCU6 timer control register 4 low
   CCU6_TCTR4H    =  0x40;        // load CCU6 timer control register 4 high
#endif    
    
      
   r = (unsigned char *)&sSlaveData;   
   n = (unsigned int)sizeof(sSlaveData)/sizeof(unsigned char);
   for(i=0; i<n; i++)
     *(unsigned char *)(r+i) = 0x00;

   // set to IN-Block balancing
   sSlaveData.BLOCK_BALANCING = IN_BLOCK;   
   
   // set Sek pins to 0
   for(i=0; i<Cells; i++)				
      //DeactivateSek(i);
	  SekOff[i]();

   // set Prim_H to 0
   PrimH_Off();

//   // switch PORTS: either JTAG or SM_LIGHT
//#ifdef SM_LIGHT  
//   SFR_PAGE(_pp1, noSST);         // switch to page 1
//   P0_PUDEN      =  0x40;         // load pullup/pulldown enable register  
//   SFR_PAGE(_pp0, noSST);         // switch to page 0
//   // clear Pins
//   P0_0=1; P0_1=1; P0_2=1;
//   P0_DIR        =  0xBF;         // load direction register
//#else
//   SFR_PAGE(_pp1, noSST);         // switch to page 1
//   P0_PUDEN      =  0x44;         // load pullup/pulldown enable register
//   SFR_PAGE(_pp0, noSST);         // switch to page 0
//   P0_DIR        =  0xB8;         // load direction register
//#endif
 
   // clear flag
   NMISR &= ~(ubyte)0x02;         // clear FNMIPLL
  }
 
  // USER CODE BEGIN (MAIN_Main,3)
 

//*****************************************************
//		               MENU
//*****************************************************
  printf("\033[2J");
  printf("\n-BATTERY MANAGEMENT %s %s-\n uC SW Version:%s \n", __DATE__, __TIME__, VERSION);
  // read corr. factors  												  
  FlashReadBoardCorrValues(pSlaveData);
           

//   while(1)
//   {
//     CAN_vTransmit(5);
//	 printf("Test\n");
//     { unsigned int i;
//     for(i=0; i<60000; i++)
//      _nop_(); 
//     }  
//   }   



//********************************************************
//		                  START
//********************************************************
  // USER CODE END

  while(1)
  {  
  // USER CODE BEGIN (MAIN_Main,4)   		 
   	NormalMode(pSlaveData);

  // USER CODE END
  }

} //  End of function main


// USER CODE BEGIN (MAIN_General,10)


//*******************************************************
//
//                 GENERAL FUNCTIONS
//
//********************************************************

//********************************************************
//			         PRINT ELEMENTS
//********************************************************                
void Print(SlaveData *pSlaveData)
{
#if defined (PRINT)  
   BLINK;
   printf("\nMeasurement:\n");
   ATTRIBUTE_OFF;
   printf(" Tmin:%7dC Tmax:%4dC \n",   ((int)pSlaveData->Tmin), ((int)pSlaveData->Tmax));					// format Q.0
   printf(" Umin:%7.2fV Umax:%4.2fV\n",(float)pSlaveData->Umin_u/4096, (float)pSlaveData->Umax_u/4096); 	// format Q.12
   printf(" Ublock:%5.2fV\n\n",        (float)pSlaveData->Ublock/256);  									// format Q.8
   printf(" Udiff:%6.2fV\n",           (float)pSlaveData->Umax_u/4096 - (float)pSlaveData->Umin_u/4096);	// format Q.12
   printf(" Uaver:%6.2fV\n",           (float)pSlaveData->Uaver_u/4096);                                    // format Q.12                                                                                                 
#endif
}

void PrintAll(SlaveData *pSlaveData)
{
#if defined (PRINT)  
   BLINK;
   printf("\nMeasurement:\n");
   ATTRIBUTE_OFF;
   printf(" Tmin:%7dC Tmax:%4dC \n",     (int)pSlaveData->Tmin, (int)pSlaveData->Tmax);						// format Q.0
   printf(" Umin:%7.3fV Umax:%4.3fV\n\n",(float)pSlaveData->Umin_u/4096, (float)pSlaveData->Umax_u/4096); 	// format Q.12
   
   printf(" Temp1:%6dC \n Temp2:%6dC \n Temp3:%6dC \n", ((int)pSlaveData->T_R5), ((int)pSlaveData->T_R6), ((int)pSlaveData->T_R7));  // format Q.0 
   printf(" Tboard:%5dC \n\n",(int)pSlaveData->T_Rboard);       																	 // format Q.0

   printf(" U0corr:%5.3fV \n",   (float)pSlaveData->Umux_u[0]/4096);  // format Q.12 
   printf(" U1corr:%5.3fV \n",   (float)pSlaveData->Umux_u[1]/4096);
   printf(" U2corr:%5.3fV \n",   (float)pSlaveData->Umux_u[2]/4096);
   printf(" U3corr:%5.3fV \n",   (float)pSlaveData->Umux_u[3]/4096);
   printf(" U4corr:%5.3fV \n",   (float)pSlaveData->Umux_u[4]/4096);
   printf(" U5corr:%5.3fV \n",   (float)pSlaveData->Umux_u[5]/4096);
   printf(" U6corr:%5.3fV \n",   (float)pSlaveData->Umux_u[6]/4096);  
   printf(" U7corr:%5.3fV \n",   (float)pSlaveData->Umux_u[7]/4096);
   printf(" U8corr:%5.3fV \n",   (float)pSlaveData->Umux_u[8]/4096);
   printf(" U9corr:%5.3fV \n",   (float)pSlaveData->Umux_u[9]/4096);
   printf(" U10corr:%4.3fV \n",  (float)pSlaveData->Umux_u[10]/4096);
   printf(" U11corr:%4.3fV \n\n",(float)pSlaveData->Umux_u[11]/4096);
   
   printf(" Ublock:%5.3fV\n\n",  (float)pSlaveData->Ublock/256);                                    // format Q.8
   printf(" Udiff:%6.3fV \n",    (float)pSlaveData->Umax_u/4096 - (float)pSlaveData->Umin_u/4096);	// format Q.12
   printf(" Uaver:%6.3fV \n",    (float)pSlaveData->Uaver_u/4096);                                  // format Q.12                                                                                                                                                                                                                                                                 
#endif
}

void PrintDigit(SlaveData *pSlaveData)
{
   printf("\n U0dig:%d \n",(int)pSlaveData->Umux_dig[0]);   
   printf(" U1dig:%d \n",(int)pSlaveData->Umux_dig[1]);
   printf(" U2dig:%d \n",(int)pSlaveData->Umux_dig[2]);
   printf(" U3dig:%d \n",(int)pSlaveData->Umux_dig[3]);
   printf(" U4dig:%d \n",(int)pSlaveData->Umux_dig[4]);
   printf(" U5dig:%d \n",(int)pSlaveData->Umux_dig[5]);
   printf(" U6dig:%d \n",(int)pSlaveData->Umux_dig[6]);  
   printf(" U7dig:%d \n",(int)pSlaveData->Umux_dig[7]);
   printf(" U8dig:%d \n",(int)pSlaveData->Umux_dig[8]);
   printf(" U9dig:%d \n",(int)pSlaveData->Umux_dig[9]);
   printf(" U10dig:%d\n",(int)pSlaveData->Umux_dig[10]);
   printf(" U11dig:%d\n\n",(int)pSlaveData->Umux_dig[11]);

   printf(" blockdig:%d\n\n",(int)pSlaveData->Umux_dig_block);
//added by XI

}


//********************************************************
//			         NORMAl MODE
//********************************************************                
void NormalMode(SlaveData *pSlaveData)
{   
#ifdef SLAVE_BOARDS   
   
   unsigned int Data         = 0;
   //unsigned char SYNCH       = 0;
   static char STATE         = State_Reset;
   static unsigned int loop  = 0;
   //unsigned long reset_loop;
      
    
   // SLAVE STATE - MACHINE
   switch( STATE )
   {
      
   	 case State_Normal:					 // LED on -> only for debug
	                                     printf("STATE - Normal S%bu\n", pSlaveData->Name);
	                                     // check sensors and block voltage
	                                     CheckTempAndBlock( pSlaveData );
										 // check all cells
										 CheckCells( pSlaveData );
									 									 	 
										 // printf
										 Print(pSlaveData);
                                         // has slave been requested?
                                         SlaveHasBeenPinged(pSlaveData);	 										                                          
                                         // store CAN relevant values
                                         SlavePrepareOwnBoardDataForCAN(pSlaveData);
                                                                                                                       
                                         // Cell balancing
                                         CellBalancing(pSlaveData);
					   				 	 // check all conditions
										 CheckAllConditions(&STATE, pSlaveData, &loop);
										 
			                             break;
     
     case State_CellConditionInvalid:	 // LED on -> only for debug
	                                     LED_CellConditionInvalid; printf("STATE - CellCon invalid\n");	                                     
										 // scan all cells
										 CheckCells( pSlaveData );									 	 
										 // printf
										 Print(pSlaveData);
                                         // Cell balancing
                                         CellBalancing(pSlaveData);
			   						 	 // check cell conditions
										 CheckCellConditions(&STATE, pSlaveData, &loop);

   			                             break;

	 case State_NoCommunication: 		 // LED on -> only for debug
	                                     LED_NoCommunication; printf("STATE - No Com, S%bx gets no request\n", pSlaveData->Name);                                       
	                                     // has slave been requested?
	                                     SlaveHasBeenPinged(pSlaveData);	 										 
	                                     // check communication condition
	                                     CheckComCondition(&STATE, pSlaveData, &loop);

   			                             break;

	 case State_Synch:					 // LED on -> only for debug
	                                     printf("STATE - Synch\n");
	                                     // check sensors and block voltage
	                                     CheckTempAndBlock(pSlaveData);
                                         // store CAN relevant values
                                         SlavePrepareOwnBoardDataForCAN(pSlaveData);									  	
									  	 // check all conditions
										 CheckAllConditions(&STATE, pSlaveData, &loop);								  	 
										 
			                             break;

	 case State_BlockConditionInvalid:	 // LED on -> only for debug
	                                     LED_BlockConditionInvalid;	printf("STATE - BlockCon invalid\n");
	                                     // check sensors and block voltage
										 CheckTempAndBlock( pSlaveData );									  	
										 // printf
										 Print(pSlaveData);
									  	 // check block conditions
										 CheckBlockConditions(&STATE, pSlaveData, &loop);									 
										 
			                             break;

	 case State_Reset:                   // LED on -> only for debug
	                                     printf("STATE - ResetS%bu\n", pSlaveData->Name);
                                         
                                         // calculate error flash address
                                         FlashCalculateAdr(pSlaveData);
                                         // read errror/warning value                                                                                   
                                         FlashReadErrors(pSlaveData);
	                                     	                                     
	                                     // check sensors and block voltage
	                                     CheckTempAndBlock(pSlaveData);
                                         // who is who?
                                         BoardIdentification(pSlaveData); 

                                         // without the request the slave can't start									  	
	                                     if( SlaveHasBeenRequested(pSlaveData) )
                                           // read command in the pipe
                                           SlaveErrorProcessing(pSlaveData);     										    										   
										   
	                                     // slave starts with inter- or intra block balancing?
	                                     SlaveHasBeenPinged(pSlaveData);	 										 
									  	 // check all conditions
										 CheckAllConditions(&STATE, pSlaveData, &loop);								  	 
	                    
										 break;

	 default:							 printf("State unknown!!!\n");
	                                     break;
   }
   
   // clear error bit
   pSlaveData->Error     = NoError;
   // clear error type
   pSlaveData->ErrorType = NoErrorType;

#endif	//end SLAVE


   //************************************************
   //		     press 'ESC' for stop
   //************************************************
   // clear flag
   NMISR &= ~(ubyte)0x02;         // clear FNMIPLL
   	   
   if(RI)
   { 
     RI=0;

     if(SBUF==0x65) //press 'e' = erase	errors
     {
   	   // erase D-flash1 sector 1
   	   DFlErase(0, DFL1_SEC1);
   	   // wait until ready
   	   while(FlReady(4) == 0);			  			          
   	   // erase D-flash1 sector 0
   	   DFlErase(0, DFL1_SEC0);
   	   // wait until ready
   	   while(FlReady(4) == 0);
	   // read flash address
	   FlashCalculateAdr(pSlaveData);

	   printf("Erase Sectors 0 and 1\n");
     }

	 if(SBUF==0x70) //press 'p' = print
	 {
       printf(" Temp1:%6.1fC \n Temp2:%6.1fC \n Temp3:%6.1fC \n", (float)pSlaveData->T_R5, (float)pSlaveData->T_R6, (float)pSlaveData->T_R7 );	  /* format Q.0	*/
       printf(" Tboard:%5.1fC \n\n",(float)pSlaveData->T_Rboard);        // format Q.0
       printf(" U0corr:%5.2fV \n",(float)pSlaveData->Umux_u[0]/4096);    // format Q.12
       printf(" U1corr:%5.2fV \n",(float)pSlaveData->Umux_u[1]/4096);
       printf(" U2corr:%5.2fV \n",(float)pSlaveData->Umux_u[2]/4096);
       printf(" U3corr:%5.2fV \n",(float)pSlaveData->Umux_u[3]/4096);
       printf(" U4corr:%5.2fV \n",(float)pSlaveData->Umux_u[4]/4096);
       printf(" U5corr:%5.2fV \n",(float)pSlaveData->Umux_u[5]/4096);
       printf(" U6corr:%5.2fV \n",(float)pSlaveData->Umux_u[6]/4096);  
       printf(" U7corr:%5.2fV \n",(float)pSlaveData->Umux_u[7]/4096);
       printf(" U8corr:%5.2fV \n",(float)pSlaveData->Umux_u[8]/4096);
       printf(" U9corr:%5.2fV \n",(float)pSlaveData->Umux_u[9]/4096);
       printf(" U10corr:%4.2fV \n",  (float)pSlaveData->Umux_u[10]/4096);
       printf(" U11corr:%4.2fV \n\n",(float)pSlaveData->Umux_u[11]/4096);
	 }

     if(SBUF==0x72) //press 'r' = read flash error
	 {
       // calculate error flash address
       FlashCalculateAdr(pSlaveData);
       // read
       FlashReadErrors(pSlaveData);
	 }
   }					  					  
}



//********************************************************
//		TOP-/BOTTOM- or INTERBLOCK BALANCING
//********************************************************                
void CellBalancing(SlaveData *pSlaveData)
{      
   unsigned int idata Umax_Uaver_u, Uaver_Umin_u;

   // calculate difference from Umax/Umin to Uaver
   Umax_Uaver_u        = pSlaveData->Umax_u  - pSlaveData->Uaver_u;
   Uaver_Umin_u        = pSlaveData->Uaver_u - pSlaveData->Umin_u;
   pSlaveData->Udiff_u = pSlaveData->Umax_u  - pSlaveData->Umin_u;

   // check	the difference between Umin and Umax and wait for
   // appr. the same time we have in case of balancing 3-4s    
   if( pSlaveData->Udiff_u <= U50mV && !(pSlaveData->BLOCK_BALANCING & INTER_BLOCK))
   {   	 									
     // printf nothing to do
     #if defined (PRINT)  
      printf("\n---\n");
     #endif

     LED_NOBALANCING;
     // pause of the same length needed for Bottom-/Top- and InterBlockBalancing
	 // Bottom Balancing
	 BalancingType(DUMMY_BALANCING);
   	 
   	 return;
   }   

   // INTER- or IN-Balancing
   if( (Umax_Uaver_u < Uaver_Umin_u) && !(pSlaveData->BLOCK_BALANCING & INTER_BLOCK) )
   { 
     // printf cell which is bottom balanced
     #if defined (PRINT)
      printf("\nBottomBalance:%bd\n", pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex]);
     #endif
	   
     LED_BOTTOM;  	 	 
	 // Bottom Balancing
	 BalancingType(BOTTOM_BALANCING);
   }
   else	 
   {       
     // printf cell which is top balanced
     if( pSlaveData->BLOCK_BALANCING & INTER_BLOCK )
	 {
       #if defined (PRINT)       
        printf("\nINTER Block Balance:%bd\n", pSlaveData->BalanceCellIndex[0]);
       #endif

	   LED_INTERBLOCK;
	   // InterBlock Balancing
	   BalancingType(INTERBLOCK_BALANCING);
	 }
	 else
	 {
       #if defined (PRINT)       
        printf("\nTopBalance:%bd\n", pSlaveData->BalanceCellIndex[0]);
       #endif

	   LED_TOP;
	   // Top Balancing
	   BalancingType(TOP_BALANCING);
	 }
   }

   // primH off
   PrimH_Off();	
}

void BalancingType(char Type)
{
   //#define PulseNo    
   unsigned int idata loop;
   
   // load var.
   loop = 65535u;
   // balancing
   while(loop--)
   {
     // bottom balancing
     BalancingFunction[Type](pSlaveData); 
     // delay because of the energy bilanz 
     DELAY_30();
   }
}


//********************************************************
//			     CALCULATE CELL RANGE
//********************************************************                
void IsAnyCellOutOfRange(SlaveData *pSlaveData)
{        
   // error: is any cell over level?
   if(pSlaveData->Umax_u > UoverLevel)
   {  
     // error message
     pSlaveData->Error     |= CellOverLevel;
	 pSlaveData->ErrorType |= BoardFailure;
   #if defined (PRINT_ERROR) 
     printf("Error: Ucell[%bd] over level\n", pSlaveData->BalanceCellIndex[0]);
   #endif
   }  
    
   // error: is any cell under level?
   if(pSlaveData->Umin_u < UunderLevel)
   {  
     // error message
     pSlaveData->Error     |= CellUnderLevel;
	 pSlaveData->ErrorType |= BoardFailure;
   #if defined (PRINT_ERROR)
     printf("Error: Ucell[%bd] under level\n", pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex]);
   #endif
   }
}

//********************************************************
//			  CALCULATE TEMPERATURE RANGE
//********************************************************                
void IsTemperatureAndBlockOutOfRange(SlaveData *pSlaveData)
{
   // warning: is any temp over 280캜?
   if(pSlaveData->Tmax > ShortCut)
   {
   	 pSlaveData->Warning |= TempShortCut;
    #if defined (PRINT_WARNING)	 
	 printf("Warning: T%bd ShortCut\n", pSlaveData->TempIndex[0]);
    #endif
   } 
   else	//clear bit
    pSlaveData->Warning &= ~TempShortCut;
     
   
   // warning: is any temp under -220캜?
   if(pSlaveData->Tmin < Open)
   {
   	 // warning message
   	 pSlaveData->Warning |= TempOpen;
   #if defined (PRINT_WARNING)
	 printf("Warning: T%bd Open\n", pSlaveData->TempIndex[TempSensors-1]);
   #endif
   }
   else	//clear bit
	pSlaveData->Warning &= ~TempOpen;
   

   // error: is any temp over 75캜?
   if( (pSlaveData->Tmax > T75) && (pSlaveData->Tmax < QuasiShortCut) )  
   {   
   	 // error message
   	 pSlaveData->Error     |= TempOverLevel;
	 pSlaveData->ErrorType |= BoardFailure;
   #if defined (PRINT_ERROR)
     printf("Error: T%bd over 75C\n", pSlaveData->TempIndex[0]);
   #endif
   }  

   // error is Ublock
   if(pSlaveData->Ublock <= UblockUnderLevel)
   {
     // error
     pSlaveData->Error     |= BlockUnderLevel;
	 pSlaveData->ErrorType |= BoardFailure;
   #if defined (PRINT_ERROR)
     printf("Error: Ublock under level\n");
   #endif
   }
}


char BoardIdentification(SlaveData *pSlaveData)
{
//#if defined (SLAVE_BOARDS)
  			   
  // POSITION 0: u > 4,84V
  if(pSlaveData->Uident >= U4_84V)									
  { 
	// wrong ID
	pSlaveData->Name = -1;
    printf("Slave: Service mode\n");
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects((char)-16);
    // single block charging
    ServiceMode(pSlaveData);
  }

  // POSITION 1: 4,53V to 4,84V
  if(      U4_53V < pSlaveData->Uident && pSlaveData->Uident < U4_84V)
  {
	pSlaveData->Name = SlaveBoard0;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID
	return pSlaveData->Name;	 
  }  // POSITION 2: 4,25V - 4,53V
  else if(U4_25V < pSlaveData->Uident && pSlaveData->Uident <= U4_53V)
  {
	pSlaveData->Name = SlaveBoard1;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);	
	// return ID
	return pSlaveData->Name;		
  }	 // POSITION 3: 4,02V - 4,25V
  else if(U4_02V < pSlaveData->Uident && pSlaveData->Uident <= U4_25V)
  {
  	pSlaveData->Name = SlaveBoard2;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 4: 3,81V - 4,02V
  else if(U3_81V < pSlaveData->Uident && pSlaveData->Uident <= U4_02V)
  {
	pSlaveData->Name = SlaveBoard3;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 5: 3,61V - 3,81V
  else if(U3_61V < pSlaveData->Uident && pSlaveData->Uident <= U3_81V)
  {
	pSlaveData->Name = SlaveBoard4;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 6: 3,43V - 3,61V
  else if(U3_43V < pSlaveData->Uident && pSlaveData->Uident <= U3_61V)
  {
	pSlaveData->Name = SlaveBoard5;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 7: 3,28V - 3,43V
  else if(U3_28V < pSlaveData->Uident && pSlaveData->Uident <= U3_43V)
  {
	pSlaveData->Name = SlaveBoard6;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 8: 3,14V - 3,28V
  else if(U3_14V < pSlaveData->Uident && pSlaveData->Uident <= U3_28V)
  {
	pSlaveData->Name = SlaveBoard7;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 9: 3,00V - 3,14V
  else if(U3_00V < pSlaveData->Uident && pSlaveData->Uident <= U3_14V)
  {
	pSlaveData->Name = SlaveBoard8;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 10: 2,88V - 3,00V
  else if(U2_88V < pSlaveData->Uident && pSlaveData->Uident <= U3_00V)
  {
	pSlaveData->Name = SlaveBoard9;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 11: 2,77V - 2,88V
  else if(U2_77V < pSlaveData->Uident && pSlaveData->Uident <= U2_88V)
  {
	pSlaveData->Name = SlaveBoard10;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 12: 2,67V - 2,77V
  else if(U2_67V < pSlaveData->Uident && pSlaveData->Uident <= U2_77V)
  {
	pSlaveData->Name = SlaveBoard11;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 13: 2,57V - 2,67V
  else if(U2_57V < pSlaveData->Uident && pSlaveData->Uident <= U2_67V)
  {
	pSlaveData->Name = SlaveBoard12;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 14: 2,48V - 2,57V
  else if(U2_48V < pSlaveData->Uident && pSlaveData->Uident <= U2_57V)
  {
	pSlaveData->Name = SlaveBoard13;
	// deallocate all objects
    SlaveDeallocateAllMessageObjects();
	// allocate all relevant MOs
	SlaveAllocateRelevantMessageObjects(pSlaveData->Name);
	// return ID	
	return pSlaveData->Name;				
  }	 // POSITION 15: <2,48V
  else 
  {
	// wrong ID
    printf("\n->wrong Slave ID, position 0xF is already reserved!!!\n");
	while(1);
  }
//#endif
}

//********************************************************
//
//                      partial SCAN
//
//********************************************************
void ScanTempAndBlockVoltage(SlaveData *pSlaveData)
{
   int idata res0, res1, res2, res3;
    
   //**********************************
   //     CHANNEL 0-3: Temp0-Temp3
   //**********************************
   // start channel 0 (Temp Rref)
   ADC_vStartSeqReqChNum(0, 0, 0, 0);
   // start channel 1 (Temp R5)
   ADC_vStartSeqReqChNum(0, 0, 0, 1);
   // start channel 2 (Temp R6)
   ADC_vStartSeqReqChNum(0, 0, 0, 2);
   // start channel 3 (Temp R7)
   ADC_vStartSeqReqChNum(0, 0, 0, 3);  
       	
   // wait as long as busy and result register 0/1/2/3 and sequential request 1 is set 
   while(ADC_ubGetEventInterruptFlag() != 0xF1);
   
   // read data	from result register 0
   res0 = ADC_uwGetResultData0();   
   // read data	from result register 1
   res1 = ADC_uwGetResultData1();
   // read data from result register 2 
   res2 = ADC_uwGetResultData2();
   // read data from result register 3 
   res3 = ADC_uwGetResultData3();   
   // clear event flags
   ADC_vClearEventInterruptFlag(0xF1);
       
   // calculate temperature	T5, T6, T7
   pSlaveData->T_R5   = MDU_Convert_ADC2Temp(res1);
   pSlaveData->T_R6   = MDU_Convert_ADC2Temp(res2);
   pSlaveData->T_R7   = MDU_Convert_ADC2Temp(res3); 

   //***********************************
   //  CHANNEL 4-6: Tboard, Uident, Ublock
   //***********************************
   // start channel 4 (Tboard)
   ADC_vStartSeqReqChNum(0, 0, 0, 4);
   // start channel 5 (Uident)
   ADC_vStartSeqReqChNum(0, 0, 0, 5);
   // start channel 6 (Ublock)
   ADC_vStartSeqReqChNum(0, 0, 0, 6);
      	
   // wait as long as busy and result register 0/1/2 and sequential request 1 is set 
   while(ADC_ubGetEventInterruptFlag() != 0x71);
   
   // read data	from result register 0
   res0 = ADC_uwGetResultData0();   
   // read data	from result register 1
   res1 = ADC_uwGetResultData1();
   // read data from result register 2 
   res2 = ADC_uwGetResultData2();   
   // clear event flags
   ADC_vClearEventInterruptFlag(0x71);

   // calculate Tboard, Uident, Ublock
   pSlaveData->T_Rboard = MDU_Convert_ADC2Temp(res0);
   pSlaveData->Uident   = res1; // =ID

    pSlaveData->Umux_dig_block = res2;
//added by XI	 


   //pSlaveData->Ublock   = MDU_Convert_ADC2UBlock(res2);

   //pSlaveData->Ublock = res2 * 40 * sSlaveData.Ufac_u[Cells] / 2;
   pSlaveData->Ublock = res2 *5*11*256/1024;
   //added by Ningyi 	 
}

//********************************************************
//
//                SCAN ALL ADC-CHANNELS
//
//********************************************************
void ScanCells(SlaveData *pSlaveData)
{
   volatile int idata res3;
   volatile char idata i, j;

#if defined (A123_BATTERY_10_CELLS)
	char j_end = 8;
	char j_inc = j_end-1;
	char i_off = Cell_5;
#elif defined (MAXWELL_9_CELLS)
	char j_end = 9;
	char j_inc = j_end-1;
	char i_off = Cell_5;
#elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS) 
	char j_end = 1;
	char j_inc = 1;
	char i_off = Cells;
#endif

   //EA = 0;
   DisableCANInterrupt();

   // set Prim_H on     
   PrimH_On(); 

   // set Prim_L 
   PrimL_On();
   DELAY_25(); 	//3탎
   PrimL_Off();

   DELAY_200(); //50탎

   //***********************************
   //     CHANNEL 7: Umux Sek0-Sek4, Umux Sek7-Sek11
   //***********************************
   for(j=0; j<j_end; j=j+j_inc)
   {
     for (i=0+j; i<i_off+j; i++)
     { 						 
       // set Voltage Number
       FLAG_Pin = i;       
       // start sequential conversion (external trigger)
       ADC_vStartSeqReqChNum(1, 0, 0, 7);   
    
       // set Prim_H on     
       PrimH_On(); 
    
    DELAY_80(); //+18탎 -> 24탎   
    
	   // set Prim_L 
	   PrimL_On(); 
	   // wait
	   DELAY_2();     

/* 
     // clear PrimL
     PrimL_Off();
	 // wait
	 DELAY_3();
     // set Sek
     SekOn[FLAG_Pin]();  
     // start Timer 12 to trigger 			
     CC6_vStartTmr(CC6_TIMER_12);	       	   
     // wait until timer is running (TR12-BIT)
     while(CCU6_TCTR0L & 0x10);
     // wait until ADC sample (SAMPLE-BIT) 
     while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
	 // clear Sek
	 SekOff[FLAG_Pin]();
*/
	   
       // switch port pin on
       //  = ActivateSek(FLAG_Pin)					
   	   switch(FLAG_Pin)
   	   {
   	      case 0:  // clear PrimL
   	               PrimL_Off();
				   // wait
		           DELAY_3();
   	               // set Sek
   	               SekOn_0();  
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_0();
   	               break;

   	      case 1:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_1();  
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_1();
   	     	       break;

   	      case 2:  // clear PrimL
   	               PrimL_Off(); 
		           // wait
		           DELAY_3();
   	               // set Sek
   	               SekOn_2(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_2();	       	                
   	               break;

   	      case 3:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_3(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_3();	       	     	        
   	     	       break;

   	      case 4:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_4(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_4();	       	     	        
   	     	       break;

   	      case 5:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_5(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_5();	       	     	        
   	     	       break;

   	      case 6:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_6(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_6();	       	     	        
   	     	       break;

   	      case 7:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_7();  
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_7();
   	     	       break;

   	      case 8:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_8(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_8();	       	     	        
   	     	       break;

   	      case 9:  // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_9(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_9();
   	     	       break;

   	      case 10: // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_10(); 
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_10();
   	     	       break;

   	      case 11: // clear PrimL
   	               PrimL_Off();
		           // wait
		           DELAY_3();
   	     	       // set Sek
   	     	       SekOn_11();
                   // start Timer 12 to trigger 			
                   CC6_vStartTmr(CC6_TIMER_12);	       	   
                   // wait until timer is running (TR12-BIT)
                   while(CCU6_TCTR0L & 0x10);
                   // wait until ADC sample (SAMPLE-BIT) 
                   while( !(ADC_GLOBSTR & 0x2) );       		       	           			                   
				   // clear Sek
				   SekOff_11();	       	     	        
   	     	       break;

   	   	  default: break;
       }   


       // if result register 3 and sequential request 1 is set 	 
       while(ADC_ubGetEventInterruptFlag() != 0x81);
	   
       // read result register
       res3 = ADC_uwGetResultData3();
       // clear event flag
       ADC_vClearEventInterruptFlag(0x81);     	 
       
       // integer data processing
       pSlaveData->Umux_dig[FLAG_Pin] = res3;	
	   
	   printf(" Udig:%d \n",(int)pSlaveData->Umux_dig[FLAG_Pin]);
//	   printf(" Udig:%d \n",(int)pSlaveData->Umux_dig[FLAG_PIN]);
//added by XI
	   
	    
       pSlaveData->Umux_u[FLAG_Pin]   = MDU_Convert_ADC(res3);	 
	   //pSlaveData->Umux_u[FLAG_Pin] = MDU_Convert_ADC_rough(res3);
       //pSlaveData->Umux_u[FLAG_Pin] = res3;       
       //printf("Umux[%bd]:%u\n", (char)FLAG_Pin, (unsigned int)pSlaveData->Umux_u[FLAG_Pin]);
       
       // set Prim_H off     
       PrimH_Off();       
     }
   }
   //printf("\n\n");

   //***********************************
   //     CHANNEL 7: Umux Sek5-Sek6
   //***********************************   
#if defined (A123_BATTERY_10_CELLS)   
   // integer data processing	 
   pSlaveData->Umux_u[5] = 0;
   // integer data processing	 
   pSlaveData->Umux_u[6] = 0;
#elif defined (MAXWELL_9_CELLS)   
   // integer data processing	 
   pSlaveData->Umux_u[5] = 0;
   // integer data processing	 
   pSlaveData->Umux_u[6] = 0;
   // integer data processing	 
   pSlaveData->Umux_u[7] = 0;
#endif

   // scale the cells to Ublock
   MDU_ScaleCells(pSlaveData);

   //EA = 1;
   EnableCANInterrupt();
}

//***********************************
//   Sum calculation and Average
//***********************************   
void MDU_ScaleCells(SlaveData *pSlaveData)
{
   char idata i;
   int idata res1;
   int diff=0;
   unsigned int idata res2;


   //************************
   //	       SUM
   //************************	 
   // clear variable
   pSlaveData->Umux_scale_ul = 0;
   // calculate SUM
   #if defined (A123_BATTERY_10_CELLS)                
    // sum all voltages from U0 to U9
    for(i=0; i<5; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12     
    for(i=7; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12 
   #elif defined (MAXWELL_9_CELLS)
    // sum all voltages from U0 to U9
    for(i=0; i<5; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12     
    for(i=8; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12 
   #elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    for(i=0; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12     
   #endif

   //************************
   //	 DIFFERENCE/Cell
   //************************
   // calulate difference
   //pSlaveData->Umux_scale_ul = pSlaveData->Umux_scale_ul>>4;
   //diff = pSlaveData->Ublock - (unsigned int)pSlaveData->Umux_scale_ul; // format Q.8  
   
//***********   
   diff = (int)((unsigned long)(pSlaveData->Ublock<<4) - pSlaveData->Umux_scale_ul); // format Q.12  
//***********   
   // diff/Cells
   SYSCON0 |= 0x01;
   MDU_Operand1 = (int)diff;				 // format Q.12   	!!!
   #if defined (A123_BATTERY_10_CELLS)    
    MDU_Operand3 = (Cells-2);
   #elif defined (MAXWELL_9_CELLS)
	MDU_Operand3 = (Cells-3);
   #elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    MDU_Operand3 = Cells;    	 
   #endif    	 
   MDU_MDUCON = 0x15;  				         // signed 16/16-bit Division   
   while((MDU_MDUSTAT & 0x04)== 0x04);     	
   res1 = MDU_Operand1;
   _nop_();
   SYSCON0 &= 0xFE;
   
   //************************
   //	     NEW Cell
   //************************   
   #if defined (A123_BATTERY_10_CELLS)                
    // sum all voltages from U0 to U11
    for(i=0; i<5; i++) 
     pSlaveData->Umux_u[i] += (int)res1; // format Q.12     
    for(i=7; i<Cells; i++) 
     pSlaveData->Umux_u[i] += (int)res1; // format Q.12 
   #elif defined (MAXWELL_9_CELLS)
    // sum all voltages from U0 to U11
    for(i=0; i<5; i++) 
     pSlaveData->Umux_u[i] += (int)res1; // format Q.12     
    for(i=8; i<Cells; i++) 
     pSlaveData->Umux_u[i] += (int)res1; // format Q.12 
   #elif defined(LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    for(i=0; i<Cells; i++) 
     pSlaveData->Umux_u[i] += (int)res1; // format Q.12     
   #endif

   //************************
   //	     NEW SUM
   //************************   
   // clear variable
   pSlaveData->Umux_scale_ul = 0;
   // calculate SUM
   #if defined (A123_BATTERY_10_CELLS)                
    // sum all voltages from U0 to U9
    for(i=0; i<5; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12    
    for(i=7; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12 
   #elif defined (MAXWELL_9_CELLS)
    // sum all voltages from U0 to U9
    for(i=0; i<5; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12    
    for(i=8; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12 
   #elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    for(i=0; i<Cells; i++) 
     pSlaveData->Umux_scale_ul += pSlaveData->Umux_u[i];   // format Q.12     
   #endif      

   //************************
   //	      AVERAGE
   //************************      
   SYSCON0 |= 0x01;
   // Uaver = Umux_scale/Cells;
   MDU_Operand1 = (unsigned int)(pSlaveData->Umux_scale_ul & 0xFFFF);
   MDU_Operand2 = (unsigned int)(pSlaveData->Umux_scale_ul >> 16) & 0xFFFF;  
   
   #if defined (A123_BATTERY_10_CELLS)    
    MDU_Operand3 = (Cells-2);
   #elif defined (MAXWELL_9_CELLS)
	MDU_Operand3 = (Cells-3);
   #elif defined(LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    MDU_Operand3 = Cells;    	 
   #endif
   
   MDU_MDUCON = 0x12;  				         // unsigned 32/16-bit Division   
   while((MDU_MDUSTAT & 0x04)== 0x04);     	
   res2 = MDU_Operand1;	    				 // format Q.12
   pSlaveData->Uaver_u = res2;
   SYSCON0 &= 0xFE;
}


void CheckTempAndBlock( SlaveData *pSlaveData )
{
	// scan all Temperature sensors
    ScanTempAndBlockVoltage(pSlaveData);
    // sort all Temp
    GetAndSortTemperature(pSlaveData);
    // temp processing	>75캜
    IsTemperatureAndBlockOutOfRange(pSlaveData);
}

void CheckCells( SlaveData *pSlaveData )
{
	// scan all cells
	ScanCells(pSlaveData);                                         
    // sort all cells
    GetAndSortAllCellVoltages(pSlaveData);                                              
    // cell processing
    IsAnyCellOutOfRange(pSlaveData);
}

void CheckAllConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop)
{      
   // check cell conditions = BoardFailure
   if ( pSlaveData->Error & (TempOverLevel | BlockUnderLevel) )
   {
     // new state
     *STATE = State_BlockConditionInvalid;	
     // clear
     *loop=0;
   }
   // check block conditions = BoardFailure
   else if( pSlaveData->Error & (CellOverLevel | CellUnderLevel) )
   {
     // new state
     *STATE = State_CellConditionInvalid; 
     // clear
     *loop=0;											  
   }
   // check com conditions
   else if( pSlaveData->Error & SlaveGetsNoPing )
   {
     // new state
     *STATE = State_NoCommunication; 
     // clear
     *loop=0;											  
   }
   else
   {
     // old state
     *STATE = State_Normal; 
     // clear
     *loop=0;											  
   }
}


// check cell conditions
void CheckCellConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop)
{
   // check conditions = BoardFailure
   if(pSlaveData->Error & (CellOverLevel | CellUnderLevel) )
   {
     // some sec
     if((*loop)++ > Time_CellConditionInvalid)
     {                                           	 
   	  // read command in the pipe
      SlaveErrorProcessing(pSlaveData);     										    
   	  // clear 
      *loop = 0;
     }
     // old state
     *STATE = State_CellConditionInvalid; 
   }
   else
   {
     // new state
     *STATE = State_Normal; 
     // clear
     *loop=0;
   }   			                             
}

void CheckBlockConditions(char *STATE, SlaveData *pSlaveData, unsigned int *loop)
{
   // check conditions = BoardFailure
   if( pSlaveData->Error & (TempOverLevel | BlockUnderLevel) )
   {        
     // some sec
     if((*loop)++ > Time_BlockConditionInvalid)
     {                                           	 
       // read command in the pipe
       SlaveErrorProcessing(pSlaveData);     										    
       // clear 
       *loop = 0;
     }
     // old state
     *STATE = State_BlockConditionInvalid;	
   }
   else
   { 
     // new state
     *STATE = State_Synch; 
     // clear
     *loop=0;
   }
}

void CheckComCondition(char *STATE, SlaveData *pSlaveData, unsigned int *loop)
{
   // error processing	                                         
   if( pSlaveData->Error & SlaveGetsNoPing )
   {                                            
     // some sec
     if((*loop)++ > Time_NoCommunication)
     {                                           	 	                                       	        
       // read command in the pipe
       SlaveErrorProcessing(pSlaveData);     										    
       // clear 
       *loop = 0;
     }
          
     // old state
     *STATE = State_NoCommunication; 
   }
   else
   {
     // new state
     *STATE = State_Synch; 
     // clear
     *loop=0;
   }
}



// USER CODE END