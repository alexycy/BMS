//****************************************************************************
// @Module        Capture / Compare Unit 6 (CCU6)
// @Filename      CC6.C
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description   This file contains functions that use the CCU6 module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:26
//
//****************************************************************************

// USER CODE BEGIN (CCU6_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (CCU6_General,2)
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CCU6_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CCU6_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CCU6_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU6_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU6_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CCU6_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CCU6_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CC6_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CCU6 function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
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

// USER CODE BEGIN (Init,1)

// USER CODE END

void CC6_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  SFR_PAGE(_cc1, noSST);         // switch to page 1

  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Control Register
  ///  -----------------------------------------------------------------------

  CCU6_TCTR0L    =  0x00;        // load CCU6 timer control register 0 low
  CCU6_TCTR0H    =  0x00;        // load CCU6 timer control register 0 high

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Timer 12:
  ///  -----------------------------------------------------------------------
  ///  - timer 12 Input clock selected  is 1
  ///  - the additional prescaler for T12 is enabled.
  ///  - timer 12 run bit is reset
  ///  - single shot mode is enabled
  ///  - timer 12 works in edge aligned mode
  ///  - interrupt on period match is disabled
  ///  - interrupt on one match is disabled

  CCU6_T12PRL    =  0x47;        // load CCU6 T12 period register low
  CCU6_T12PRH    =  0x00;        // load CCU6 T12 period register lhigh

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Timer 13:
  ///  -----------------------------------------------------------------------
  ///  - Timer T13 Input clock selected is 1
  ///  - The additional prescaler for T13 is disabled
  ///  - timer 13 run bit is reset
  ///  - trigger control is disabled
  ///  - single shot mode is disabled
  ///  - interrupt on period match is disabled
  ///  - interrupt on compare match is disabled

  CCU6_T13PRL    =  0x01;        // load CCU6 T13 period register low
  CCU6_T13PRH    =  0x00;        // load CCU6 T13 period register high

  ///  -----------------------------------------------------------------------
  ///  Configuration of Dead-Time Control Register for Timer T12
  ///  -----------------------------------------------------------------------

  CCU6_T12DTCL   =  0x01;        // load CCU6 dead time control register low 
                                 // for timer T12

  CCU6_T12DTCH   =  0x00;        // load CCU6 dead time control register high 
                                 // for timer T12

  SFR_PAGE(_cc0, noSST);         // switch to page 0

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Channel 0:
  ///  -----------------------------------------------------------------------
  ///  - channel 0 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Channel 1:
  ///  -----------------------------------------------------------------------
  ///  - channel 1 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Channel 2:
  ///  -----------------------------------------------------------------------
  ///  - channel 2 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 Channel 3:
  ///  -----------------------------------------------------------------------
  ///  - T13 output is not inverted


  CCU6_CC63SRL   =  0x00;        // load CCU6 capture/compare shadow register 
                                 // low for channel 3
  CCU6_CC63SRH   =  0x00;        // load CCU6 capture/compare shadow register 
                                 // high for channel 3


  ///  -----------------------------------------------------------------------
  ///  Configuration of Multi-Channel Mode Output Register
  ///  -----------------------------------------------------------------------

  CCU6_MCMOUTSL  =  0x00;        // load CCU6 multi channel mode output 
                                 // control register low
  CCU6_MCMOUTSH  =  0x00;        // load CCU6 multi channel mode output 
                                 // control register high

  SFR_PAGE(_cc2, noSST);         // switch to page 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Control Register
  ///  -----------------------------------------------------------------------

  CCU6_TCTR2L    =  0x01;        // load CCU6 timer control register 2 low
  CCU6_TCTR2H    =  0x00;        // load CCU6 timer control register 2 high

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 trap control:
  ///  -----------------------------------------------------------------------
  ///  - a trap can only be generated by SW by setting the bit TRPF
  ///  - the trap state is left when a zero-match of T12 (while counting up) 
  ///    is detected (synchronization to T12)
  ///  - bit TRPF is automatically cleared by HW (according to TRPPEN, TRPM0 
  ///    and TRPM1)
  ///  - trap interrupt is disabled

  CCU6_TRPCTRL   =  0x00;        // load CCU6 trap control register low
  CCU6_TRPCTRH   =  0x00;        // load CCU6 trap control register high

  ///  -----------------------------------------------------------------------
  ///  Configuration of Multi Channel Mode:
  ///  -----------------------------------------------------------------------
  ///  - multi channel mode is disabled

  CCU6_MODCTRL   =  0x00;        // load CCU6 modulation control register low
  CCU6_MODCTRH   =  0x00;        // load CCU6 modulation control register high

  ///  -----------------------------------------------------------------------
  ///  Configuration of Multi_Channel Mode Control Register
  ///  -----------------------------------------------------------------------

  CCU6_MCMCTR    =  0x00;        // load CCU6 multi channel mode control 
                                 // register 

  ///  -----------------------------------------------------------------------
  ///  Configuration of T12 Capture/Compare Mode Select Register
  ///  -----------------------------------------------------------------------

  CCU6_T12MSELL  =  0x00;        // load CCU6 T12 campture/compare mode 
                                 // select register low

  CCU6_T12MSELH  =  0x00;        // load CCU6 T12 campture/compare mode 
                                 // select register high
  ///  -----------------------------------------------------------------------
  ///  Configuration of Passive State Level Register
  ///  -----------------------------------------------------------------------

  CCU6_PSLR      =  0x00;        // load CCU6 passive state level register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 interrupt control:
  ///  -----------------------------------------------------------------------
  ///  - for channel 0 interrupts is node I0 selected
  ///  - for channel 1 interrupts is node I0 selected
  ///  - for channel 2 interrupts is node I0 selected
  ///  - for correct hall event interrupt is node I0 selected
  ///  - for error interrupts is node I0 selected
  ///  - for T12 interrupts is node I0 selected
  ///  - for T13 interrupts is node I0 selected

  CCU6_INPL      =  0x00;        // load CCU6 capture/compare interrupt node 
                                 // pointer register low
  CCU6_INPH      =  0x00;        // load CCU6 capture/compare interrupt node 
                                 // pointer register high

  CCU6_IENL      =  0x00;        // load CCU6 capture/compare interrupt 
                                 // enable register low
  CCU6_IENH      =  0x00;        // load CCU6 capture/compare interrupt 
                                 // enable register high

  SFR_PAGE(_cc3, noSST);         // switch to page 3

  ///  -----------------------------------------------------------------------
  ///  Configuration of Compare State Register
  ///  -----------------------------------------------------------------------

  CCU6_CMPSTATH  =  0x00;        // load CCU6 compare status register high

  ///  -----------------------------------------------------------------------
  ///  Configuration of CCU6 module input signals:
  ///  -----------------------------------------------------------------------
  ///  - signal CC60 is not used
  ///  - signal CC61 is not used
  ///  - signal CC62 is not used
  ///  - signal #CTRAP is not used

  CCU6_PISEL0L   =  0x00;        // load CCU6 Port Input Select Register 0 Low

  ///  - signal CCPOS0 is not used
  ///  - signal CCPOS1 is not used
  ///  - signal CCPOS2 is not used
  ///  - signal T12HR is not used

  CCU6_PISEL0H   =  0x00;        // load CCU6 Port Input Select Register 0 
                                 // High

  ///  - signal T13HR is not used

  CCU6_PISEL2    =  0x00;        // load CCU6 Port Input Select Register 2




  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CCU6 Channels Interrupts:
  ///  -----------------------------------------------------------------------
  ///  - capture/compare interrupt node 0 is disabled
  ///  - capture/compare interrupt node 1 is disabled
  ///  - capture/compare interrupt node 2 is disabled
  ///  - capture/compare interrupt node 3 is disabled

  SFR_PAGE(_cc0, noSST);         // switch to page 0

  ///  -----------------------------------------------------------------------
  ///  Timer Control Register
  ///  -----------------------------------------------------------------------
  ///  -  enable shadow transfer to T12 and T13

  CCU6_TCTR4L    =  0x40;        // load CCU6 timer control register 4 low

  CCU6_TCTR4H    =  0x40;        // load CCU6 timer control register 4 high

  // USER CODE BEGIN (Init,3)
  // USER CODE END

} //  End of function CC6_vInit


// USER CODE BEGIN (CCU6_General,10)

// USER CODE END

