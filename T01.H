//****************************************************************************
// @Module        Timer 0/1
// @Filename      T01.H
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains all function prototypes and macros for 
//                the T01 module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:25
//
//****************************************************************************

// USER CODE BEGIN (T01_Header,1)

// USER CODE END



#ifndef _T01_H_
#define _T01_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (T01_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (T01_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (T01_Header,4)

// USER CODE END

#define T01_TIMER_0          0
#define T01_TIMER_1          1
#define T01_MODE_0           0x00
#define T01_MODE_1           0x10
#define T01_MODE_2           0x20

//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (T01_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (T01_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (T01_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void T01_vInit(void);

// USER CODE BEGIN (T01_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         T01_vStartTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro starts the chosen timer. The timer continues to 
//                count from where it has been stopped the last time. 
//                The following constants are available for 'TimerNr':
//                T01_TIMER_0, T01_TIMER_1
//                
//                Special feature when timer 0 is in mode 3:
//                'T01_TIMER_1' selects the second 8-bit timer TH0. 
//                'T01_vStartTmr1' must be used in order to start TL1/TH1.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Number of timer to be started
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

#define T01_vStartTmr(TimerNr)    _TR(TimerNr) = 1


//****************************************************************************
// @Macro         T01_vStopTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro stops the chosen timer. The timer contents of 
//                the timer register remains unchanged.
//                The following constants are available for 'TimerNr':
//                T01_TIMER_0, T01_TIMER_1
//                
//                Special feature when timer 0 is in mode 3:
//                'T01_TIMER_1' selects the second 8-bit timer TH0. 
//                'T01_vStopTmr1' must be used in order to stop TL1/TH1.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Number of timer to be stopped
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

#define T01_vStopTmr(TimerNr)     _TR(TimerNr) = 0


//****************************************************************************
// @Macro         T01_vClearTmr(TimerNr) 
//
//----------------------------------------------------------------------------
// @Description   This macro sets the timer registers TLx and THx of the 
//                chosen timer to zero.
//                Macro 'T01_vClearTmrH' is the 8-bit version that accesses 
//                timer register THx only.
//                Macro 'T01_vClearTmrL' is the 8-bit version that accesses 
//                timer register TLx only.
//                The following constants are available for 'TimerNr':
//                T01_TIMER_0, T01_TIMER_1
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Number of timer to be cleared
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

#define T01_vClearTmr(TimerNr)    { _TH(TimerNr) = 0; _TL(TimerNr) = 0; }
#define T01_vClearTmrH(TimerNr)   _TH(TimerNr) = 0
#define T01_vClearTmrL(TimerNr)   _TL(TimerNr) = 0


//****************************************************************************
// @Macro         T01_vLoadTmr(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the chosen timer with the passed 16-bit 
//                value by writing it to the timer registers THx and TLx. The 
//                timer will not be stopped. The access of the CPU to the 
//                registers of the timer is of higher priority than a timer 
//                increment. 
//                Macro 'T01_vLoadTmrH' is the 8-bit version that accesses 
//                timer register THx only.
//                Macro 'T01_vLoadTmrL' is the 8-bit version that accesses 
//                timer register TLx only.
//                The following constants are available for 'TimerNr':
//                T01_TIMER_0, T01_TIMER_1
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                Number of timer to be loaded
// @Parameters    Value: 
//                Value to be loaded
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

#define T01_vLoadTmr(TimerNr, Value) \
         { _TH(TimerNr) = (ubyte) ( ((uword) (Value)) >> 8 ); \
           _TL(TimerNr) = ((ubyte) (Value)) & 0xff; }
#define T01_vLoadTmrH(TimerNr, Value) _TH(TimerNr) = Value
#define T01_vLoadTmrL(TimerNr, Value) _TL(TimerNr) = Value


#define _TH(TimerNr) TH##TimerNr
#define _TL(TimerNr) TL##TimerNr
#define _TR(TimerNr) TR##TimerNr
//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


#define T0INT 1
// USER CODE BEGIN (T01_Header,9)

// USER CODE END

#endif  // ifndef _T01_H_
