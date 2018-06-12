#ifndef _BATTERY_H_
#define _BATTERY_H_


#include "MAIN.H"
#include <stdio.h>


typedef unsigned char 	 uchar;
typedef signed char      schar; 
typedef unsigned int 	 uint16;
typedef signed int 	     Sint16;



#if defined (A123_BATTERY_10_CELLS) && defined (SLAVE_BOARDS)
   #define VERSION "v3.1 A123 BatteryManagement-S"
#elif defined (LITEC_BATTERY_12_CELLS) && defined (SLAVE_BOARDS)
   #define VERSION "v3.1 Litec BatteryManagement-S"
#elif defined (PANASONIC_12_CELLS) && defined (SLAVE_BOARDS)
   #define VERSION "v3.1 Panasonic BatteryManagement-S"
#elif defined (MAXWELL_12_CELLS) && defined (SLAVE_BOARDS)
   #define VERSION "v3.1 Maxwell (12 Cells) BMS-S"
#elif defined (MAXWELL_9_CELLS) && defined (SLAVE_BOARDS)
   #define VERSION "v3.1 Maxwell (9 Cells) BMS-S"
#else
   #define VERSION "v?.?"
   #message "Version: wrong version"
#endif

// Escape Sequences
#define CLEAR   	     printf("\033[2J")
#define HOME             printf("\033[H")
#define POS              printf("\033[2;2H")
#define POSITION(Ze, Sp) printf("\033[%d;%dH",Ze,Sp)
#define UNDERLINE        printf("\033[4m")
#define BLACK		     printf("\033[30m")
#define BLUE             printf("\033[34m") 
#define RED              printf("\33[31m")
#define GREEN            printf("\033[32m")
#define MAGENTA          printf("\033[35m")  
#define BOLD             printf("\033[1m") 
#define BOLD_INVERSE     printf("\033[1;7m")
#define ATTRIBUTE_OFF    printf("\033[0m")
#define BLINK            printf("\033[5m")

// LED STATE-MACHINE				//  green   red
#define LED_Normal				     (P1_2=0, P1_6=0)                   // (P0_0=1, P0_1=1, P0_2=1)	 //=0
#define LED_CellConditionInvalid     (P1_2=1, P1_6=0)                   // (P0_0=1, P0_1=1, P0_2=0)	 //=1
#define LED_NoCommunication		     (P1_2=0, P1_6=1)                   // (P0_0=1, P0_1=0, P0_2=1)	 //=2
#define LED_BlockConditionInvalid    (P1_2=1, P1_6=1)                   // (P0_0=1, P0_1=0, P0_2=0)	 //=3
#define LED_Init				     (P1_2=0, P1_6=0)                   // (P0_0=0, P0_1=1, P0_2=0)	 //=5
#define LED_Reset				     (P1_2=0, P1_6=0)                   // (P0_0=0, P0_1=0, P0_2=0)	 //=7
// BALANCING TYPE
#define LED_INTERBLOCK				 LED_NoCommunication	   //red
#define LED_BOTTOM					 LED_CellConditionInvalid  //green
#define LED_TOP						 LED_BlockConditionInvalid //red+green
#define LED_NOBALANCING				 LED_Normal				   //LEDs off
// STATE-MACHINE
#define State_Normal				           0
#define State_CellConditionInvalid	           1
#define State_NoCommunication		           2
#define State_BlockConditionInvalid            3
#define State_Reset					           4
#define State_Synch					           5


// 0,1
#define ON   1
#define HIGH ON
#define OFF  0
#define LOW  OFF
#define false FALSE
#define true  TRUE

// Temperature
#define TempSensors   4		   // TempNo. Sensor
#define ShortCut (int)280	   //(unsigned int)832     // =280캜
#define QuasiShortCut (int)ShortCut-10
#define T80      (int)80	   //(unsigned int)0x3540  // =80캜
#define T75      (int)75	   //(unsigned int)0x3680  // =75캜
#define Open     (int)-220	   //(unsigned int)0x8040  // =(-220캜) ADC= -(t-293)*64

#define delta  (float)0.5

#if defined (A123_BATTERY_10_CELLS)	 // working range 2,0V-3,6V
	// LEVELS
	#define UoverLevel       (unsigned int)0x3999 //=3.6V Q.12
	#define UunderLevel      (unsigned int)0x2800 //=2.5V Q.12
	#define U50mV            (unsigned int)0xCC   //=50mV Q.12
	#define U100mV           (unsigned int)0x1A   //=0.1V Q.8
    #define UblockUnderLevel (unsigned int)0x1900 //=25V  Q.8  
	// for test purposes
	#define UmaxLevel        (unsigned int)0x3999 //=3.6V Q.12 // -|-> Aver=2,9V
	#define UminLevel        (unsigned int)0x2333 //=2.2V Q.12 // -|
	#define U_Level_aver1	 (unsigned int)0x3000 //=3.0V Q.12
	#define U_Level_aver2 	 (unsigned int)0x2999 //=2.6V Q.12
	// for balancing
	#define TopSekPulse		 (char)32  //=32 탎ec
	#define TopPrimPulse     (char) 7  //= 7 탎ec
	#define InterSekPulse	 TopSekPulse
	#define InterPrimPulse   TopPrimPulse
	#define BottomPrimPulse	 (char)1   //=10 탎ec
	#define BottomSekPulse	 (char)21  //=20 탎ec
	// for cell calibration
    #define Uoff_f (float)2.084       //1.7	  // analog offset
    #define Uoff_u (unsigned int)8536 //6963  // 4096*Uoff_f
	#define Ucell_Grade (unsigned int)512
	// for block calibration
	#define Ublock_Grade (unsigned int)44835	
#endif

#if defined (LITEC_BATTERY_12_CELLS) // working range 3,0V-4,2V
	// LEVELS
	#define UoverLevel       (unsigned int)0x4333 //=4.2V Q.12
	#define UunderLevel      (unsigned int)0x3000 //=3.0V Q.12
	#define U50mV            (unsigned int)0xCC   //=50mV Q.12
	#define U100mV           (unsigned int)0x1A   //=0.1V Q.8
    #define UblockUnderLevel (unsigned int)0x2400 //=3V*12=36V  Q.8  
	// for test purposes
	#define UmaxLevel        (unsigned int)0x4333 //=4.2V Q.12 // -|-> Aver=3,6V
	#define UminLevel        (unsigned int)0x3000 //=3.0V Q.12 // -|
	#define U_Level_aver1	 (unsigned int)0x3b33 //=3.7V Q.12
	#define U_Level_aver2 	 (unsigned int)0x3800 //=3.5V Q.12
    // for balancing
	#define TopSekPulse		 (char)27  //=25 탎ec
	#define TopPrimPulse     (char)4   //=4 탎es
	#define InterSekPulse	 TopSekPulse
	#define InterPrimPulse   TopPrimPulse
	#define BottomPrimPulse	 (char)3   //=10 탎ec
	#define BottomSekPulse	 (char)30  //=26 탎ec
	// for cell calibration
    #define Uoff_f (float)2.455		    // analog offset
    #define Uoff_u (unsigned int)10055  // 4096*Uoff_f
	#define Ucell_Grade  (unsigned int)512
	// for block calibration
	#define Ublock_Grade (unsigned int)44835	
#endif
     
#if defined (PANASONIC_12_CELLS)  // working range 2.0V-2,3V
	// LEVELS
	#define UoverLevel       (unsigned int)0x24cc //=2.3V  Q.12
	#define UunderLevel      (unsigned int)0x0199 //=0.1V  Q.12
	#define U50mV            (unsigned int)0xCC   //=50mV  Q.12
	#define U100mV           (unsigned int)0x1A   //=0.1V  Q.8
    #define UblockUnderLevel (unsigned int)0x0500 //=5.0V  Q.8  
	// for test purposes
	#define UmaxLevel        (unsigned int)0x24cc //=2.3V Q.12 // -|-> Aver=1.2V
	#define UminLevel        (unsigned int)0x0199 //=0.1V Q.12 // -|
	#define U_Level_aver1	 (unsigned int)0x1666 //=1.4V Q.12
	#define U_Level_aver2 	 (unsigned int)0x1000 //=1.0V Q.12
    // for balancing
	#define TopSekPulse		 (char)27  //=25 탎ec
	#define TopPrimPulse     (char)8   //=8 탎es
	#define InterSekPulse	 TopSekPulse
	#define InterPrimPulse   TopPrimPulse
	#define BottomPrimPulse	 (char)13  //=12 탎ec
	#define BottomSekPulse	 (char)32  //=30 탎ec
	// for cell calibration
    #define Uoff_f (float)0.042		   // analog offset
    #define Uoff_u (unsigned int)172   // 4096*Uoff_f
	#define Ucell_Grade  (unsigned int)512
	// for block calibration
	#define Ublock_Grade (unsigned int)44835	
#endif

#if defined (MAXWELL_12_CELLS) || defined (MAXWELL_9_CELLS) // working range up to 2,7V
	// LEVELS
	#define UoverLevel       (unsigned int)0x2b33 //=2.7V  Q.12
	#define UunderLevel      (unsigned int)0x0199 //=0.1V  Q.12
	#define U50mV            (unsigned int)0xCC   //=50mV  Q.12
	#define U100mV           (unsigned int)0x1A   //=0.1V  Q.8
    #define UblockUnderLevel (unsigned int)0x0500 //=5.0V  Q.8  
	// for test purposes
	#define UmaxLevel        (unsigned int)0x24cc //=2.7V Q.12 // -|-> Aver=1.4V
	#define UminLevel        (unsigned int)0x0199 //=0.1V Q.12 // -|
	#define U_Level_aver1	 (unsigned int)0x1999 //=1.6V Q.12
	#define U_Level_aver2 	 (unsigned int)0x1333 //=1.2V Q.12
    // for balancing
	#define TopSekPulse		 (char)27  //=25 탎ec
	#define TopPrimPulse     (char)8   //=8 탎es
	#define InterSekPulse	 TopSekPulse
	#define InterPrimPulse   TopPrimPulse
	#define BottomPrimPulse	 (char)13  //=12 탎ec
	#define BottomSekPulse	 (char)32  //=30 탎ec
	// for cell calibration
    #define Uoff_f (float)0.13	      // analog offset
    #define Uoff_u (unsigned int)532  // 4096*Uoff_f
	#define Ucell_Grade  (unsigned int)512
	// for block calibration
	#define Ublock_Grade (unsigned int)44835	
#endif
     
      
// delay
#define DELAY_2()      (_nop_(), _nop_())
#define DELAY_3()      (_nop_(), _nop_(), _nop_())
#define DELAY_5()      (_nop_(), _nop_(), _nop_(), _nop_(), _nop_())
#define DELAY_10()     (_nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_())
#define DELAY_20()     (DELAY_10(), DELAY_10())
#define DELAY_25()     (DELAY_10(), DELAY_10(), DELAY_5())
#define DELAY_30()     (DELAY_20(), DELAY_10())
#define DELAY_40()     (DELAY_20(), DELAY_20())
#define DELAY_50()     (_nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_(), \
                        _nop_(), _nop_(), _nop_(), _nop_(), _nop_() )
#define DELAY_80()     (DELAY_50(), DELAY_10(), DELAY_10(), DELAY_10())
#define DELAY_150()    (DELAY_50(), DELAY_50(), DELAY_50())
#define DELAY_200()    (DELAY_50(), DELAY_50(), DELAY_50(), DELAY_50())
#define DELAY_300()    (DELAY_150(), DELAY_150())
#define DELAY_350()    (DELAY_50(), DELAY_150(), DELAY_150())

// defines loop
#define TTick(start, test, inc, body)   for (start; test; inc) body;  


//  - ADC Interrupt disabled/enabled
#define DisableADCInterrupt() (IEN1 &= ~0x01)
#define EnableADCInterrupt()  (IEN1 |= 0x01)    
//  - MultiCAN Node 4, 5 Interrupt disabled/enabled
#define DisableCANInterrupt() (IEN1 &= ~0x30)
#define EnableCANInterrupt()  (IEN1 |= 0x30)
// - Timer 0/1 Interrupt disabled/enabled
#define	DisableTimer0Interrupt() (IEN0 &= ~0x0A)
#define	EnableTimer0Interrupt()  (IEN0 |= 0x0A)
// - Timer 2 Interrupt disabled/enabled
#define	DisableTimer2Interrupt() (IEN0 &= ~0x20)
#define	EnableTimer2Interrupt()  (IEN0 |= 0x20)

#define SlaveBoard0     0
#define SlaveBoard1     1
#define SlaveBoard2     2
#define SlaveBoard3     3
#define SlaveBoard4     4
#define SlaveBoard5     5
#define SlaveBoard6     6
#define SlaveBoard7     7
#define SlaveBoard8     8
#define SlaveBoard9     9
#define SlaveBoard10   10
#define SlaveBoard11   11  
#define SlaveBoard12   12  
#define SlaveBoard13   13  

// output, high active, impulse, on/off
#define SekOn_0()   P0_7=1  
#define SekOn_1()   P3_0=1
#define SekOn_2()   P3_1=1
#define SekOn_3()   P3_4=1
#define SekOn_4()   P3_5=1
#define SekOn_5()   P0_5=1
#define SekOn_6()   P0_4=1 
#define SekOn_7()   P3_6=1 
#define SekOn_8()   P4_3=1
#define SekOn_9()   P1_5=1
#define SekOn_10()  P1_4=1
#define SekOn_11()  P1_3=1

#define SekOff_0()  P0_7=0  
#define SekOff_1()  P3_0=0
#define SekOff_2()  P3_1=0
#define SekOff_3()  P3_4=0
#define SekOff_4()  P3_5=0
#define SekOff_5()  P0_5=0
#define SekOff_6()  P0_4=0 
#define SekOff_7()  P3_6=0 
#define SekOff_8()  P4_3=0
#define SekOff_9()  P1_5=0
#define SekOff_10() P1_4=0
#define SekOff_11() P1_3=0

#define PrimL_On()  P0_3=1
#define PrimL_Off() P0_3=0
#define PrimOn()	PrimL_On()
#define PrimOff()	PrimL_Off()
#define PrimH_On()  P3_7=1
#define PrimH_Off() P3_7=0

//GK  #define NSTB_Low()  P1_2=0
//GK  #define NSTB_High() P1_2=1
//GK  #define EN_Low()    P1_6=0
//GK  #define EN_High()   P1_6=1
//GK  #define CanTranceiverSleep() (NSTB_Low(), DELAY_300(), EN_Low())

#define U4_84V (unsigned int)0x3DF	 // POSITION 0	 Uadc=u/1024*5V
#define U4_53V (unsigned int)0x3A0	 // POSITION 1
#define U4_25V (unsigned int)0x366	 // POSITION 2
#define U4_02V (unsigned int)0x337	 // POSITION 3
#define U3_81V (unsigned int)0x30C	 // POSITION 4
#define U3_61V (unsigned int)0x2E3	 // POSITION 5
#define U3_43V (unsigned int)0x2BE	 // POSITION 6
#define U3_28V (unsigned int)0x2A0	 // POSITION 7
#define U3_14V (unsigned int)0x283	 // POSITION 8
#define U3_00V (unsigned int)0x266	 // POSITION 9
#define U2_88V (unsigned int)0x24E	 // POSITION A
#define U2_77V (unsigned int)0x237	 // POSITION B
#define U2_67V (unsigned int)0x223	 // POSITION C
#define U2_57V (unsigned int)0x20E	 // POSITION D
#define U2_48V (unsigned int)0x1FC	 // POSITION E

//// output, high active
//#define VuC_On        P1_6 = 1
//#define VuC_Off		  P1_6 = 0
//#define SetSleep(on)  ( (on==1)?(VuC_Off):(VuC_On) )

#define BOTTOM_BALANCING	 0
#define TOP_BALANCING		 1
#define INTERBLOCK_BALANCING 2
#define DUMMY_BALANCING      3

#define INTER_BLOCK   1
#define IN_BLOCK      0
#define Cells        12  
#define Cell_5		  5
#define Cell_6		  6
#define Cell_7		  7
#define Cell_8		  8

// Flash ranges
#define FlashB000	           0xB000
#define FlashB000_20           0xB020
#define FlashB400	           0xB400
#define FlashB400_20           0xB420
#define FlashB7E0		       0xB7E0
#define FlashB800	           0xB800
#define FlashAddress_BFEO      0xBFE0

// Timer
#define Time_CellConditionInvalid       10
#define Time_BlockConditionInvalid      50	//400
#define Time_NoCommunication	       150	//200

typedef void(*pSekOn) (void);
typedef void(*pSekOff)(void);

typedef struct
{
 uchar res1           :1;	// [11.0]
 uchar SlaveGetsNoPing:1;	// [11.1]
 uchar res2           :1;   // [11.2]
 uchar BlockUnderLevel:1;   // [11.3] 
 uchar TempShortCut   :1;   // [11.3]
 uchar TempOpen       :1;	// [11.5]
 uchar empty1         :2;   // [11.6-7]
}TBitField;

typedef struct
{  
  unsigned int NextSectorAdr;	   // 2 Byte [0]	
  unsigned int CurrentSectorAdr;   // 2 Byte [2]	
  unsigned long NOP_1;             // 4 Byte [4]
  unsigned char NOP_2;             // 1 Byte [8]
  unsigned char CellOverLevel;     // 1 Byte [9]
  unsigned char CellUnderLevel;    // 1 Byte [10]
  unsigned char TempOverLevel;     // 1 Byte [11]  
  TBitField FurtherErrorBits;      // 1 Byte [12]   
}TFlashData;

typedef struct
{
  unsigned int Delta_u;
  char  Flag;
}TCell;

typedef enum
{
  // WARNING  
  TempShortCut = 0x01,    
  TempOpen     = 0x02	   
}TWarning;

typedef enum
{
  // ERRORS
  NoError              = 0x00,	// everthing okay = 0x00  
  CellOverLevel        = 0x01,  // Ucell over xV = 0x01	  
  CellUnderLevel       = 0x02,  // Ucell under xV = 0x02	 
  TempOverLevel        = 0x04,	// temperature > 80 = 0x4
  SlaveGetsNoPing      = 0x10,  // No request from Master
  BlockUnderLevel      = 0x40,  // Block under Level 
  SlaveGetsNoReq       = 0x80	// slave can't re accessed
}TError;

typedef enum
{
  NoErrorType          = 0x0,
  BoardFailure         = 0x1,  
  CommunicationFailure = 0x4,
}TErrorType;

typedef struct
{
  unsigned char MinCell, MaxCell;  
  int MinTemp, MaxTemp;
  unsigned int BoardVoltage;  
}TCanSlave;

typedef struct
{
  unsigned char MinCell, MaxCell;
  int MinTemp, MaxTemp;
  unsigned int BoardVoltage;   
}TCanDataOfAllBoards;

typedef struct
{
  unsigned int Umux_u[Cells], U0_u, Ublock, Uident, Umux_dig[Cells];
  unsigned int Umux_dig_block;	//ADDed by Dr. Xi
  unsigned int Umax_u, Umin_u, Udiff_u, Uaver_u;
  unsigned long Umux_scale_ul;
    
  int T_R5, T_R6, T_R7;
  int T_Rboard;  
  int Tmax, Tmin, Temp[TempSensors];
  char TempIndex[TempSensors];

  char Name;
  char Charge;
  char LowestCellIndex;
  
  unsigned char BLOCK_BALANCING;
  unsigned int Ufac_u[Cells+1]; // 1x Offset + 1x gradient 12x CellCorrValues

  TCell U_Cell[Cells]; 
  unsigned int BalanceCell_u[Cells];
  char  BalanceCellIndex[Cells];
  
  TError Error;
  TWarning Warning;
  TErrorType ErrorType;
  TCanSlave CanData;
  TFlashData FlashData;
}SlaveData;


typedef void(*pBal)(SlaveData *);


// external function to include
//GKextern void DeactivateSek(char SekNo);
extern void TopBalancing(SlaveData *pSlaveData);
extern void BottomBalancing(SlaveData *pSlaveData); 
extern void DummyBalancing(SlaveData *pSlaveData);
extern void SortAllCellVoltages(SlaveData *pSlaveData);
extern unsigned int MDU_Convert_ADC(unsigned int ADC);
extern int MDU_Convert_ADC2Temp(unsigned int ADC);
extern unsigned int MDU_Convert_ADC2UBlock(unsigned int ADC);
extern void GetAndSortTemperature(SlaveData *pSlaveData);
extern void GetAndSortAllCellVoltages(SlaveData *pSlaveData);
extern void InterBlockTopBalancing(SlaveData *pSlaveData);
//extern unsigned int MDU_Convert_ADC_rough( unsigned int ADC );

extern void SekOn0(void);  
extern void SekOn1(void);  
extern void SekOn2(void);  
extern void SekOn3(void);  
extern void SekOn4(void);  
extern void SekOn5(void);  
extern void SekOn6(void);  
extern void SekOn7(void);  
extern void SekOn8(void);  
extern void SekOn9(void);  
extern void SekOn10(void);  
extern void SekOn11(void);

extern void SekOff0(void);  
extern void SekOff1(void);  
extern void SekOff2(void);  
extern void SekOff3(void);  
extern void SekOff4(void);  
extern void SekOff5(void);  
extern void SekOff6(void);  
extern void SekOff7(void);  
extern void SekOff8(void);  
extern void SekOff9(void);  
extern void SekOff10(void);  
extern void SekOff11(void);  
  
extern pSekOn  SekOn[12];
extern pSekOff SekOff[12];
extern pBal    BalancingFunction[4];
#endif
