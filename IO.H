//****************************************************************************
// @Module        GPIO
// @Filename      IO.H
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains all function prototypes and macros for 
//                the IO module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:24
//
//****************************************************************************

// USER CODE BEGIN (IO_Header,1)

// USER CODE END



#ifndef _IO_H_
#define _IO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (IO_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_Header,4)

// USER CODE END

//   Port 0

sbit P0_0       = 0x80;    
sbit P0_1       = 0x81;    
sbit P0_2       = 0x82;    
sbit P0_3       = 0x83;    
sbit P0_4       = 0x84;    
sbit P0_5       = 0x85;    
sbit P0_7       = 0x87;    

//   Port 1

/*
******************************************************************************
@Note

P1_2 output for LED
P1_6 output for LED




******************************************************************************
*/


sbit P1_0       = 0x90;    
sbit P1_1       = 0x91;    
sbit P1_2       = 0x92;    
sbit P1_3       = 0x93;    
sbit P1_4       = 0x94;    
sbit P1_5       = 0x95;    
sbit P1_6       = 0x96;    
sbit P1_7       = 0x97;    

//   Port 2

sbit P2_0       = 0xA0;    
sbit P2_1       = 0xA1;    
sbit P2_2       = 0xA2;    
sbit P2_3       = 0xA3;    
sbit P2_4       = 0xA4;    
sbit P2_5       = 0xA5;    
sbit P2_6       = 0xA6;    
sbit P2_7       = 0xA7;    

//   Port 3

sbit P3_0       = 0xB0;    
sbit P3_1       = 0xB1;    
sbit P3_2       = 0xB2;    
sbit P3_3       = 0xB3;    
sbit P3_4       = 0xB4;    
sbit P3_5       = 0xB5;    
sbit P3_6       = 0xB6;    
sbit P3_7       = 0xB7;    

//   Port 4

/*
******************************************************************************
@Note

P4_0 output for LED
P4_1 output for LED


******************************************************************************
*/


sbit P4_0       = 0xC8;    
sbit P4_1       = 0xC9;    
sbit P4_3       = 0xCB;    

//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void IO_vInit(void);


// USER CODE BEGIN (IO_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (IO_Header,9)

// USER CODE END


#endif  // ifndef _IO_H_
