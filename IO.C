//****************************************************************************
// @Module        GPIO
// @Filename      IO.C
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains functions that use the IO module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:24
//
//****************************************************************************

// USER CODE BEGIN (IO_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IO_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IO_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IO_General,9)

// USER CODE END


//****************************************************************************
// @Function      void IO_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IO function 
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

// USER CODE BEGIN (IO_Init,1)

// USER CODE END

void IO_vInit(void)
{
  // USER CODE BEGIN (IO_Init,2)

  // USER CODE END


  ///  ***********************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  
  ///  If no pins are selected DAvE assumes that registers are in default 
  ///  settings
  ///  ***********************************************************************

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P0:
  ///  -----------------------------------------------------------------------
  ///  P0.3:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P0.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P0.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P0.7:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 

  SFR_PAGE(_pp1, noSST);         // switch to page 1
  P0_PUDEN      =  0x44;         // load pullup/pulldown enable register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P0_DIR        =  0xB8;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P1:
  ///  -----------------------------------------------------------------------
  ///  P1.0:
  ///  - is used as alternate input for the UART Receive Input
  ///  - pull-up device is assigned
  ///  P1.1:
  ///  - is used as alternate output for the UART Transmit Output
  ///  - push/pull output is selected
  ///  - pull-up device is assigned
  ///  P1.2:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P1.3:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P1.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P1.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P1.6:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P1.7:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 

  SFR_PAGE(_pp1, noSST);         // switch to page 1
  P1_PUDEN      =  0x03;         // load pullup/pulldown enable register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P1_DIR        =  0xFC;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P2:
  ///  -----------------------------------------------------------------------
  ///  P2.0:
  ///  - is used as alternate input for the Analog Input 0
  ///  - pull device is disabled (tristate) 
  ///  P2.1:
  ///  - is used as alternate input for the Analog Input 1
  ///  - pull device is disabled (tristate) 
  ///  P2.2:
  ///  - is used as alternate input for the Analog Input 2
  ///  - pull device is disabled (tristate) 
  ///  P2.3:
  ///  - is used as alternate input for the Analog Input 3
  ///  - pull device is disabled (tristate) 
  ///  P2.4:
  ///  - is used as alternate input for the Analog Input 4
  ///  - pull device is disabled (tristate) 
  ///  P2.5:
  ///  - is used as alternate input for the Analog Input 5
  ///  - pull device is disabled (tristate) 
  ///  P2.6:
  ///  - is used as alternate input for the Analog Input 6
  ///  - pull device is disabled (tristate) 
  ///  P2.7:
  ///  - is used as alternate input for the Analog Input 7
  ///  - pull device is disabled (tristate) 


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P3:
  ///  -----------------------------------------------------------------------
  ///  P3.0:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P3.1:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P3.2:
  ///  - is used as alternate input for the MCAN Node 1 Receiver Input
  ///  - pull device is disabled (tristate) 
  ///  P3.3:
  ///  - is used as alternate output for the MCAN Node 1 Transmitter Output
  ///  - push/pull output is selected
  ///  - pull device is disabled (tristate) 
  ///  P3.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P3.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P3.6:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P3.7:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 


  P3_DIR        =  0xF3;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P4:
  ///  -----------------------------------------------------------------------
  ///  P4.0:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P4.1:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 
  ///  P4.3:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  - pull device is disabled (tristate) 


  P4_DIR        =  0x0B;         // load direction register


  // USER CODE BEGIN (IO_Init,3)

  // USER CODE END

} //  End of function IO_vInit




// USER CODE BEGIN (IO_General,10)

// USER CODE END

