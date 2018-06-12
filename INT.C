//****************************************************************************
// @Module        Interrupt Unit
// @Filename      INT.C
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains functions that use the IR module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:24
//
//****************************************************************************

// USER CODE BEGIN (IR_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IR_General,2)
#include <stdio.h>
#include "Routines.h"
#include "Flash.h"
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IR_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IR_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IR_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IR_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IR_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IR_General,8)
// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IR_General,9)

// USER CODE END


//****************************************************************************
// @Function      void INT_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IR function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                The project settings regarding the external interrupts are 
//                taken over into the corresponding special function 
//                registers IENx (interrupt enabling), TCON and EXICONx 
//                (trigger selection)(x=0 or 1). The global enable Bit EA is 
//                not changed. The initialization of the interrupt priorities 
//                is located in function MAIN_vInit.
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

// USER CODE BEGIN (IR_Init,1)

// USER CODE END

void INT_vInit(void)
{
  // USER CODE BEGIN (IR_Init,2)

  // USER CODE END

  //   ------ Port initialization for Interrupt module-----

  //   ---------- Non Maskable Interrupt configuration ----------

  ///   NMIWDT disabled
  ///   NMIPLL enabled
  ///   NMIFLASH disabled
  ///   NMIOCDS disabled
  ///   NMIVDD enabled
  ///   NMIVDDP enabled
  ///   NMIECC enabled
  NMICON        =  0x72;         //  NMI Control Register 
  ///  ---------- external interrupt 0 ----------
  ///  disabled

  ///  ---------- external interrupt 1 ----------
  ///  disabled

  ///  ---------- external interrupt 2 ----------
  ///  disabled

  ///  ---------- external interrupt 3 to 6----------
  ///  disabled

  IEN0          =  0x02;         //  interrupt enable  register 0
  IEN1          =  0x00;         //  interrupt enable register 1
  EXICON0       =  0x00;         // external interrupt trigger select 
                                 // register 0
  EXICON1       =  0x00;         // external interrupt trigger select 
                                 // register 1
  MODPISEL      =  0x00;         // peripheral input select register 
  // USER CODE BEGIN (IR_Init,3)

  // USER CODE END

} //  End of function INT_vInit


//****************************************************************************
// @Function      void INT_viNmiIsr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the Non Maskable 
//                Interrupts. 
//                Please note that you have to add application specific code 
//                to this function.
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

// USER CODE BEGIN (IR_IsrNMI,1)

// USER CODE END

void INT_viNmiIsr(void) interrupt NMIINT
{

   // USER CODE BEGIN (IR_IsrNMI,2)

  // USER CODE END

  SFR_PAGE(_su0, noSST);         // switch to page0 without saving


  if( NMISR & 0x02 )// if NMIPLL request flag is set
  {
     NMISR &= ~(ubyte)0x02; //   clear FNMIPLL

  // USER CODE BEGIN (IR_IsrNMI,4)
     printf("FNMIPLL\n");
  // USER CODE END

   }

   if( NMISR & 0x10 )// if NMIVDD request flag is set
   {
      NMISR &= ~(ubyte)0x10; //   clear FNMIVDD

  // USER CODE BEGIN (IR_IsrNMI,7)
	  printf("FNMIVDD\n");
  // USER CODE END

   }

  if( NMISR & 0x20 )// if NMIVDDP request flag is set
  {
      NMISR &= ~(ubyte)0x20; //   clear FNMIVDDP

  // USER CODE BEGIN (IR_IsrNMI,8)
	  printf("FNMIVDDP\n");
  // USER CODE END

   }

   if( NMISR & 0x40 )// if NMIECC request flag is set
   {
      NMISR &= ~(ubyte)0x40; //   clear FNMIECC

  // USER CODE BEGIN (IR_IsrNMI,9)
	  printf("FNMIECC\n");
  // USER CODE END

   }


} //  End of function INT_viNmiIsr


// USER CODE BEGIN (IR_General,10)

// USER CODE END

