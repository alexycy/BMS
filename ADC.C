//****************************************************************************
// @Module        Analog / Digital Converter (ADC)
// @Filename      ADC.C
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains functions that use the ADC module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:26
//
//****************************************************************************

// USER CODE BEGIN (ADC_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (ADC_General,2)
#include "Routines.h"
#include <stdio.h>
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (ADC_General,4)
sfr16   RESULT_REGISTER_0   =  0xCA;
sfr16	RESULT_REGISTER_1	=  0xCC;
sfr16	RESULT_REGISTER_2	=  0xCE;
sfr16	RESULT_REGISTER_3	=  0xD2;

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (ADC_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC_General,6)
//extern Board_Data xdata sBoardData;
//GKextern unsigned char Pin;
// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (ADC_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (ADC_General,9)

// USER CODE END


//****************************************************************************
// @Function      void ADC_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the ADC function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                Following SFR fields will be initialized:
//                GLOBCTR  - Global Control
//                PRAR     - Priority and Arbitration Register
//                ETRCR    - External Trigger Control Register
//                CHCTRx   - Channel Control Register x
//                RCRx     - Result Control Register x
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

// USER CODE BEGIN (ADC_Init,1)

// USER CODE END

void ADC_vInit(void)
{
  // USER CODE BEGIN (ADC_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of Global Control:
  ///  -----------------------------------------------------------------------
  ///  - the ADC module clock is enabled
  ///  - the ADC module clock = 24,00 MHz
  ///   
  ///  - the result is 10 bits wide
  ///  --- Conversion Timing -----------------
  ///  - conversion time (CTC)    = 02,04 us

  ///  - Configure global control functions 

  SFR_PAGE(_ad0, noSST);         // switch to page 0

  ADC_GLOBCTR   =  0x10;         // load global control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Priority and Arbitration:
  ///  -----------------------------------------------------------------------
  ///  - the priority of request source 0 is high
  ///  - the wait-for-start mode is selected for source 0
  ///  - the priority of request source 1 is low
  ///  - the wait-for-start mode is selected for source 1
  ///  - the arbitration started by pending conversion request is selected
  ///  - Arbitration Slot 0 is enabled
  ///  - Arbitration Slot 1 is disabled

  ADC_PRAR      =  0x51;         // load Priority and Arbitration register

  SFR_PAGE(_ad1, noSST);         // switch to page 1

  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel Control Registers:
  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel 0
  ///  - the result register0 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR0    =  0x00;         // load channel control register

  ///  Configuration of Channel 1
  ///  - the result register1 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR1    =  0x01;         // load channel control register

  ///  Configuration of Channel 2
  ///  - the result register2 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR2    =  0x02;         // load channel control register

  ///  Configuration of Channel 3
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR3    =  0x03;         // load channel control register

  ///  Configuration of Channel 4
  ///  - the result register0 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR4    =  0x00;         // load channel control register

  ///  Configuration of Channel 5
  ///  - the result register1 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR5    =  0x01;         // load channel control register

  ///  Configuration of Channel 6
  ///  - the result register2 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR6    =  0x02;         // load channel control register

  ///  Configuration of Channel 7
  ///  - the result register3 is selected
  ///  - the limit check 0 is selected

  ADC_CHCTR7    =  0x03;         // load channel control register

  SFR_PAGE(_ad0, noSST);         // switch to page 0

  ///  -----------------------------------------------------------------------
  ///  Configuration of Sample Time Control:
  ///  -----------------------------------------------------------------------

  ADC_INPCR0    =  0x03;         // load input class register

  SFR_PAGE(_ad4, noSST);         // switch to page 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of Result Control Registers:
  ///  -----------------------------------------------------------------------
  ///  Configuration of Result Control Register 0
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is enabled
  ///  - the VF reset by read access to RESRxH/RESRAxH

  ADC_RCR0      =  0xC0;         // load result control register 0

  ///  Configuration of Result Control Register 1
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is enabled
  ///  - the VF reset by read access to RESRxH/RESRAxH

  ADC_RCR1      =  0xC0;         // load result control register 1

  ///  Configuration of Result Control Register 2
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is enabled
  ///  - the VF reset by read access to RESRxH/RESRAxH

  ADC_RCR2      =  0xC0;         // load result control register 2

  ///  Configuration of Result Control Register 3
  ///  - the data reduction filter is disabled
  ///  - the event interrupt is disabled
  ///  - the wait-for-read mode is enabled
  ///  - the VF reset by read access to RESRxH/RESRAxH

  ADC_RCR3      =  0xC0;         // load result control register 3

  SFR_PAGE(_ad5, noSST);         // switch to page 5

  ///  -----------------------------------------------------------------------
  ///  Configuration of Channel Interrupt Node Pointer Register:
  ///  -----------------------------------------------------------------------
  ///  - the SR 0 line become activated if channel 0 interrupt is generated
  ///  - the SR 0 line become activated if channel 1 interrupt is generated
  ///  - the SR 0 line become activated if channel 2 interrupt is generated
  ///  - the SR 0 line become activated if channel 3 interrupt is generated
  ///  - the SR 0 line become activated if channel 4 interrupt is generated
  ///  - the SR 0 line become activated if channel 5 interrupt is generated
  ///  - the SR 0 line become activated if channel 6 interrupt is generated
  ///  - the SR 0 line become activated if channel 7 interrupt is generated

  ADC_CHINPR    =  0x00;         // load channel interrupt node pointer 
                                 // register 

  ///  -----------------------------------------------------------------------
  ///  Configuration of Event Interrupt Node Pointer Registers:
  ///  -----------------------------------------------------------------------
  ///  - the SR 0 line become activated if the event 0 interrupt is generated
  ///  - the SR 0 line become activated if the event 1 interrupt is generated
  ///  - the SR 0 line become activated if the event 4 interrupt is generated
  ///  - the SR 0 line become activated if the event 5 interrupt is generated
  ///  - the SR 0 line become activated if the event 6 interrupt is generated
  ///  - the SR 0 line become activated if the event 7 interrupt is generated

  ADC_EVINPR    =  0x00;         // load event interrupt set flag register 

  SFR_PAGE(_ad0, noSST);         // switch to page 0

  ///  -----------------------------------------------------------------------
  ///  Configuration of Limit Check Boundary:
  ///  -----------------------------------------------------------------------

  ADC_LCBR      =  0xB7;         // load limit check boundary register

  ///  -----------------------------------------------------------------------
  ///  Configuration of External Trigger Control:
  ///  -----------------------------------------------------------------------
  ///  - the trigger input ETR02 is selected for Source 0
  ///  - the trigger input ETR10 is selected for Source 1
  ///  - the synchronizing stage is not in external trigger input REQTR0 path
  ///  - the synchronizing stage is not in external trigger input REQTR1 path

  ADC_ETRCR     =  0x02;         // load external trigger control register

  SFR_PAGE(_ad6, noSST);         // switch to page 6

  ///  -----------------------------------------------------------------------
  ///  Configuration of Conversion Queue Mode Register:
  ///  -----------------------------------------------------------------------
  ///  - the gating line is permanently 1
  ///  - the external trigger is enabled

  ADC_QMR0      =  0x05;         // load queue mode register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Conversion Request Mode Registers:
  ///  -----------------------------------------------------------------------
  ///  - the gating line is permanently 0
  ///  - the external trigger is disabled
  ///  - the source interrupt is disabled
  ///  - the autoscan functionality is disabled

  ADC_CRMR1     =  0x00;         // load conversion request mode register 1

  SFR_PAGE(_ad0, noSST);         // switch to page 0

  ADC_GLOBCTR  |=  0x80;         // turn on Analog part

  ///  - ADC-Interrupt (EADC) remains disabled


  // USER CODE BEGIN (ADC_Init,3)

  // USER CODE END

} //  End of function ADC_vInit


//****************************************************************************
// @Function      void ADC_vStartSeqReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, 
//                ubyte ubRFill, ubyte ubChannelNum) 
//
//----------------------------------------------------------------------------
// @Description   This function request software controlled conversion for 
//                new channel.
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubExtTrg: 
//                External Trigger : defines external trigger
// @Parameters    ubEnIntr: 
//                Enable Source Interrupt : defines source interrupt
// @Parameters    ubRFill: 
//                Refill : defines the refill
// @Parameters    ubChannelNum: 
//                Name of the Request Channel Number (0 - 7)
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

void ADC_vStartSeqReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum)
{

  ubyte ubVal = 0;
  if (ubExtTrg == 1){ ubVal = 0x80;}
  if (ubEnIntr == 1){ ubVal = ubVal + 0x40;}
  if (ubRFill == 1){ ubVal = ubVal + 0x20;}
  ubVal = ubVal + (ubChannelNum & 0x07);

  SFR_PAGE(_ad6, SST1);          // switch to page 6

  ADC_QINR0 = ubVal; // requested channel 

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

} //  End of function ADC_vStartSeqReqChNum


//****************************************************************************
// @Function      ubyte ADC_ubGetEventInterruptFlag(void) 
//
//----------------------------------------------------------------------------
// @Description   This function reads the activated event interupt flags 
//                EVINFR
//
//----------------------------------------------------------------------------
// @Returnvalue   Bit x = 1 if event interrupt for event x has occured, else 0
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

ubyte ADC_ubGetEventInterruptFlag(void)
{
  ubyte ubResult = 0;

  SFR_PAGE(_ad5, SST1);          // switch to page 5

  ubResult = ADC_EVINFR ;

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

  return(ubResult);
} //  End of function ADC_ubGetEventInterruptFlag


//****************************************************************************
// @Function      void ADC_vClearEventInterruptFlag(ubyte ubChannelNum) 
//
//----------------------------------------------------------------------------
// @Description   This function clears the corresponding event interrupt flag 
//                in register EVINFR.
//                Example: 
//                ADC_vClearEventInterruptFlag( 0x03 )
//                clears EVINCR.EVINC0 (bit 0) and EVINCR.EVINC1 (bit 1)
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubChannelNum: 
//                Name of the event interrupt to be cleared
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

void ADC_vClearEventInterruptFlag(ubyte ubChannelNum)
{

  SFR_PAGE(_ad5, SST1);          // switch to page 5

  ADC_EVINCR = ubChannelNum;

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

} //  End of function ADC_vClearEventInterruptFlag






// USER CODE BEGIN (ADC_General,10)
uword ADC_uwGetResultData0(void)
{
  uword uwResult = 0;

  SFR_PAGE(_ad2, SST1);          // switch to page 2

    if ( ADC_RESR0L & 0x10 )       //  if Result Register0 contains valid data
    {    
    //uwResult = (uword)((ADC_RESR0H << 2) + ((ADC_RESR0L >> 6)& 0x03));   // for 10-bit resolution (without accumulation)
    uwResult = (RESULT_REGISTER_0 >> 6) & 0x3FF;
    }

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

  return(uwResult);
} //  End of function ADC_uwGetResultData0

uword ADC_uwGetResultData1(void)
{
  uword uwResult = 0;

  SFR_PAGE(_ad2, SST1);          // switch to page 2

    if ( ADC_RESR1L & 0x10 )       //  if Result Register1 contains valid data
    {
    //uwResult = (uword)((ADC_RESR1H << 2) + ((ADC_RESR1L >> 6)& 0x03));   // for 10-bit resolution (without accumulation)
    uwResult = (RESULT_REGISTER_1 >> 6);
    }

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

  return(uwResult);
} //  End of function ADC_uwGetResultData1x


uword ADC_uwGetResultData2(void)
{
  uword uwResult = 0;

  SFR_PAGE(_ad2, SST1);          // switch to page 2

    if ( ADC_RESR2L & 0x10 )       //  if Result Register2 contains valid data
    {
    //uwResult = (uword)((ADC_RESR2H << 2) + ((ADC_RESR2L >> 6)& 0x03));   // for 10-bit resolution (without accumulation)
    uwResult = (RESULT_REGISTER_2 >> 6);
    }

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

  return(uwResult);
} //  End of function ADC_uwGetResultData2x

uword ADC_uwGetResultData3(void)
{
  uword uwResult = 0;

  SFR_PAGE(_ad2, SST1);          // switch to page 2

    if ( ADC_RESR3L & 0x10 )       //  if Result Register3 contains valid data
    {
    //uwResult = (uword)((ADC_RESR3H << 2) + ((ADC_RESR3L >> 6)& 0x03));   // for 10-bit resolution (without accumulation)
    uwResult = (RESULT_REGISTER_3 >> 6);
    }

  SFR_PAGE(_ad0, RST1);          // restore the old ADC page

  return(uwResult);
} //  End of function ADC_uwGetResultData3x

// USER CODE END

