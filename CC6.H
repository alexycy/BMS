//****************************************************************************
// @Module        Capture / Compare Unit 6 (CCU6)
// @Filename      CC6.H
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description   This file contains all function prototypes and macros for 
//                the CCU6 module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:26
//
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,1)

// USER CODE END



#ifndef _CC6_H_
#define _CC6_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies CC6 timer 12
#define CC6_TIMER_12 12

//   This parameter identifies CC6 timer 13
#define CC6_TIMER_13 13

//   This parameter identifies CC6 channel 0
#define CC6_CHANNEL_0 0

//   This parameter identifies CC6 channel 1
#define CC6_CHANNEL_1 1

//   This parameter identifies CC6 channel 2
#define CC6_CHANNEL_2 2

//   This parameter identifies CC6 channel 3
#define CC6_CHANNEL_3 3


// USER CODE BEGIN (CCU6_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CCU6_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CC6_vInit(void);


// USER CODE BEGIN (CCU6_Header,8)
//GKsfr16   CCU6_T12PRLH        =  0x9C;
//GKsfr16   CCU6_TCTR4LH        =  0x9C;
#define CC6_vSetTmrPeriod(TimerNr, uwValue) CC6_vSetTmrPeriod_##TimerNr(uwValue)
#define CC6_vSetTmrPeriod_CC6_TIMER_12(uwValue) CCU6_T12PRLH = uwValue
#define CC6_vSetTmrPeriod_CC6_TIMER_13(uwValue) CCU6_T13PRLH = uwValue
// USER CODE END


//****************************************************************************
// @Macro         CC6_vStartTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro starts the selected CC6 timer. The timer 
//                continues counting from where it stopped. 
//                
//                The following definitions for TimerNr are available: 
//                CC6_TIMER_12
//                CC6_TIMER_13
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Name of the CC6 timer to be started
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

#define CC6_vStartTmr(TimerNr) CC6_vStartTmr_##TimerNr()
#define CC6_vStartTmr_CC6_TIMER_12() CCU6_TCTR4L |= 0x02
#define CC6_vStartTmr_CC6_TIMER_13() CCU6_TCTR4H |= 0x02


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

//   Shared interrupt vector definitions are defined in SHARED_INT.H


// USER CODE BEGIN (CCU6_Header,10)

// USER CODE END


#endif  // ifndef _CC6_H_
