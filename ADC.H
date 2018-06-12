//****************************************************************************
// @Module        Analog / Digital Converter (ADC)
// @Filename      ADC.H
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains all function prototypes and macros for 
//                the ADC module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:26
//
//****************************************************************************

// USER CODE BEGIN (ADC_Header,1)

// USER CODE END



#ifndef _ADC_H_
#define _ADC_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (ADC_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (ADC_Header,4)

// USER CODE END

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7



//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (ADC_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void ADC_vInit(void);
void ADC_vStartSeqReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum);
ubyte ADC_ubGetEventInterruptFlag(void);
void ADC_vClearEventInterruptFlag(ubyte ubChannelNum);

// USER CODE BEGIN (ADC_Header,8)
uword ADC_uwGetResultData0(void);
uword ADC_uwGetResultData1(void);
uword ADC_uwGetResultData2(void);
uword ADC_uwGetResultData3(void);

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (ADC_Header,9)

// USER CODE END


#endif  // ifndef _ADC_H_
