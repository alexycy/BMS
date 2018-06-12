//****************************************************************************
// @Module        MultiCAN Controller 
// @Filename      CAN.C
// @Project       BM_NewSlave.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.6
//
// @Description:  This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          12.08.2009 19:23:27
//
//****************************************************************************

// USER CODE BEGIN (CAN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (CAN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************


// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************


// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
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

void CAN_vInit(void)
{

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - the CAN module clock = 48,00 MHz
  ///  - FCLK runs at 2 times the frequency of PCLK.

  ///  - CMCON - Clock Control Register is Configured in MAIN_vInit

  //   - wait until Panel has finished the initialisation
    CAN_vWriteCANAddress(CAN_PANCTR); // Addressing CAN_PANCTR
    CAN_DATA1 = CAN_PANCTR_BUSY;
    while(CAN_DATA1 & CAN_PANCTR_BUSY){ // wait until Panel has finished the 
                                        // initialisation
      CAN_ADCON &= ~0x01;       
      }                         

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

  //-----------CAN_NCR0 = 0x00000041-------------------------------------

    CAN_vWriteCANAddress(CAN_NCR0); // Addressing CAN_NCR0
    CAN_DATA0 = 0x41;            // load NODE 0 control register[7-0]
    CAN_vWriteEN(D0_VALID+ADR_INC); // Data0 is Valid for transmission and 
                                    // Write is EnabledCAN Address pointing 
                                    // to the CAN_NSR0.

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

  //-----------CAN_NCR1 = 0x00000041-------------------------------------

    CAN_vWriteCANAddress(CAN_NCR1); // Addressing CAN_NCR1
    CAN_DATA0 = 0x41;            // load NODE 1 control register[7-0]
    CAN_vWriteEN(D0_VALID+ADR_INC); // Data0 is Valid for transmission and 
                                    // Write is EnabledCAN Address pointing 
                                    // to the CAN_NSR1.

  //  CAN Address pointing to the CAN_NIPR1
    CAN_ADCON = ADR_INC;         // Auto Increment the current address(+1)

  ///  - load NODE 1 interrupt pointer register
  //-----------CAN_NIPR1 = 0x00006000-------------------------------------

    CAN_DATA0 = 0x00;            // load NIPR1_LECINP, NIPR1_ALINP
    CAN_DATA1 = 0x60;            // load NIPR1_CFCINP, NIPR1_TRINP
    CAN_vWriteEN(D0_VALID+D1_VALID+ADR_INC); // Data0 and Data1 are Valid for 
                                             // with Auto Increment 
                                             // transmission and Write is 
                                             // Enabled CAN Address pointing 
                                             // to the CAN_NPCR1

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAN Input Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - Pin P3.2 is used as RXDC1_1 input

  //-----------CAN_NPCR1 = 0x00000001-------------------------------------
  ///  - Loop-back mode is disabled

    CAN_DATA0 = 0x01;            // Receive Select NPCR1_RXSEL
    CAN_DATA1 = 0x00;            // Loop-back mode is disabled
    CAN_vWriteEN(D0_VALID+D1_VALID+ADR_INC);  //  Data0 & 1 are Valid for 
                                              // transmission and Write is 
                                              // Enabled with AutoIncrement 
                                              // CAN Address pointing to the 
                                              // CAN_NBTR1



  ///  Configuration of the Node 1 Baud Rate:
  ///  - required baud rate = 250,000 kbaud
  ///  - real baud rate     = 250,000 kbaud
  ///  - sample point       = 50,00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 6 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta
  ///  - enable the module clock divider (by 8)

  //-----------CAN_NBTR1 = 0x0000D441-------------------------------------

    CAN_DATA0 = 0x41;            // load NBTR1_SJW, BRP
    CAN_DATA1 = 0xD4;            // load NBTR1_DIV8, TSEG2, TSEG1
    CAN_vWriteEN(D0_VALID+D1_VALID+ADR_INC);  // Data0, 1 are valid for 
                                              // transmission and Write is 
                                              // Enabled with Auto 
                                              // Increment(+1) CAN Address 
                                              // pointing to the CAN_NECNT1

  ///  Configuration of the Node 1 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

  //-----------CAN_NECNT1 = 0x00600000-------------------------------------

    CAN_DATA2 = 0x60;            // load NECNT1_EWRNLVL register
    CAN_vWriteEN(D2_VALID+ADR_INC); // Data2 is Valid for transmission, Auto 
                                    // Increment current address(+1) and 
                                    // Write is Enabled CAN Address pointing 
                                    // to the CAN_NFCR1

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000


  //-----------CAN_NFCR1 = 0x00000000-------------------------------------

    CAN_DATA0 = 0x00;            // load NFCR1_CFCL
    CAN_DATA1 = 0x00;            // load NFCR1_CFCH
    CAN_DATA2 = 0x00;            // load NFCR1_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_vWriteEN(D0_VALID+D1_VALID+D2_VALID); // Data0, 1, 2 are valid for 
                                              // transmission and Write is 
                                              // Enabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAN Output Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - NODE0 TXD Pin's are not used
  ///  Pin P3.3 is used as TXDC1_1 Output 

    SFR_PAGE(_pp2, noSST);       // switch to page 2
      P3_ALTSEL0      |= 0x08;    //  set AltSel0 
      P3_ALTSEL1      |= 0x08;    //  set AltSel1

    SFR_PAGE(_pp0, noSST);       // switch to page 0
      P3_DIR          |= 0x08;        //  set Direction as Output


  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------

    CAN_vWriteCANAddress(CAN_PANCTR); // Addressing CAN_PANCTR

  ///  Allocate MOs for list 2:
    CAN_vSetListCommand(0x02000002);  // MO0 for list 2
    CAN_vSetListCommand(0x02010002);  // MO1 for list 2
    CAN_vSetListCommand(0x02020002);  // MO2 for list 2
    CAN_vSetListCommand(0x02030002);  // MO3 for list 2
    CAN_vSetListCommand(0x02040002);  // MO4 for list 2
    CAN_vSetListCommand(0x02050002);  // MO5 for list 2
    CAN_vSetListCommand(0x02100002);  // MO16 for list 2
    CAN_vSetListCommand(0x02110002);  // MO17 for list 2
    CAN_vSetListCommand(0x02120002);  // MO18 for list 2
    CAN_vSetListCommand(0x02130002);  // MO19 for list 2
    CAN_vSetListCommand(0x02140002);  // MO20 for list 2
    CAN_vSetListCommand(0x02150002);  // MO21 for list 2
    CAN_vSetListCommand(0x02160002);  // MO22 for list 2
    CAN_vSetListCommand(0x02170002);  // MO23 for list 2
    CAN_vSetListCommand(0x02180002);  // MO24 for list 2
    CAN_vSetListCommand(0x02190002);  // MO25 for list 2
    CAN_vSetListCommand(0x021A0002);  // MO26 for list 2
    CAN_vSetListCommand(0x021B0002);  // MO27 for list 2
    CAN_vSetListCommand(0x021C0002);  // MO28 for list 2
    CAN_vSetListCommand(0x021D0002);  // MO29 for list 2
    CAN_vSetListCommand(0x021E0002);  // MO30 for list 2
    CAN_vSetListCommand(0x021F0002);  // MO31 for list 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 31:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  -----------------------------------------------------------------------
  ///  - message object 0 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR0 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR0); // Addressing MO0 control register

    CAN_vWriteAMData(0x0EA80000); // load MO0 control register

  //  CAN Address pointing to the CAN_MOAR0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x648

  //--------------MOAR0 = 0xD9200000---------------------------------------

    CAN_vWriteAMData(0xD9200000); // load MO0 arbitration register

  //  CAN Address pointing to the CAN_MODATAH0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH0 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO0 data register high

  //  CAN Address pointing to the CAN_MODATAL0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL0 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO0 data register low

  //  CAN Address pointing to the CAN_MOAMR0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR0 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO0 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 0

  //--------------MOIPR0 = 0x00000004---------------------------------------

    CAN_vWriteAMData(0x00000004); // load MO0 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR0 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO0 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR0
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR0 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO0  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  -----------------------------------------------------------------------
  ///  - message object 1 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR1 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR1); // Addressing MO1 control register

    CAN_vWriteAMData(0x0EA80000); // load MO1 control register

  //  CAN Address pointing to the CAN_MOAR1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x649

  //--------------MOAR1 = 0xD9240000---------------------------------------

    CAN_vWriteAMData(0xD9240000); // load MO1 arbitration register

  //  CAN Address pointing to the CAN_MODATAH1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH1 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO1 data register high

  //  CAN Address pointing to the CAN_MODATAL1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL1 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO1 data register low

  //  CAN Address pointing to the CAN_MOAMR1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR1 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO1 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 1

  //--------------MOIPR1 = 0x00000104---------------------------------------

    CAN_vWriteAMData(0x00000104); // load MO1 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR1 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO1 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR1
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR1 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO1  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  -----------------------------------------------------------------------
  ///  - message object 2 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR2 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR2); // Addressing MO2 control register

    CAN_vWriteAMData(0x0EA80000); // load MO2 control register

  //  CAN Address pointing to the CAN_MOAR2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x64A

  //--------------MOAR2 = 0xD9280000---------------------------------------

    CAN_vWriteAMData(0xD9280000); // load MO2 arbitration register

  //  CAN Address pointing to the CAN_MODATAH2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH2 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO2 data register high

  //  CAN Address pointing to the CAN_MODATAL2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL2 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO2 data register low

  //  CAN Address pointing to the CAN_MOAMR2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR2 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO2 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 2

  //--------------MOIPR2 = 0x00000204---------------------------------------

    CAN_vWriteAMData(0x00000204); // load MO2 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR2 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO2 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR2
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR2 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO2  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  -----------------------------------------------------------------------
  ///  - message object 3 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR3 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR3); // Addressing MO3 control register

    CAN_vWriteAMData(0x0EA80000); // load MO3 control register

  //  CAN Address pointing to the CAN_MOAR3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x64B

  //--------------MOAR3 = 0xD92C0000---------------------------------------

    CAN_vWriteAMData(0xD92C0000); // load MO3 arbitration register

  //  CAN Address pointing to the CAN_MODATAH3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH3 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO3 data register high

  //  CAN Address pointing to the CAN_MODATAL3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL3 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO3 data register low

  //  CAN Address pointing to the CAN_MOAMR3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR3 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO3 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 3

  //--------------MOIPR3 = 0x00000304---------------------------------------

    CAN_vWriteAMData(0x00000304); // load MO3 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR3 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO3 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR3
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR3 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO3  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  -----------------------------------------------------------------------
  ///  - message object 4 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR4 = 0x00A00000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR4); // Addressing MO4 control register

    CAN_vWriteAMData(0x00A00000); // load MO4 control register

  //  CAN Address pointing to the CAN_MOAR4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x300

  //--------------MOAR4 = 0xCC000000---------------------------------------

    CAN_vWriteAMData(0xCC000000); // load MO4 arbitration register

  //  CAN Address pointing to the CAN_MODATAH4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH4 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO4 data register high

  //  CAN Address pointing to the CAN_MODATAL4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL4 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO4 data register low

  //  CAN Address pointing to the CAN_MOAMR4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR4 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO4 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 4

  //--------------MOIPR4 = 0x00000404---------------------------------------

    CAN_vWriteAMData(0x00000404); // load MO4 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR4 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO4 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR4
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 2 valid data bytes

  //--------------MOFCR4 = 0x02000000---------------------------------------

    CAN_vWriteAMData(0x02000000); // load MO4  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  -----------------------------------------------------------------------
  ///  - message object 5 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR5 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR5); // Addressing MO5 control register

    CAN_vWriteAMData(0x0EA80000); // load MO5 control register

  //  CAN Address pointing to the CAN_MOAR5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x200

  //--------------MOAR5 = 0xC8000000---------------------------------------

    CAN_vWriteAMData(0xC8000000); // load MO5 arbitration register

  //  CAN Address pointing to the CAN_MODATAH5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH5 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO5 data register high

  //  CAN Address pointing to the CAN_MODATAL5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL5 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO5 data register low

  //  CAN Address pointing to the CAN_MOAMR5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR5 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO5 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 5

  //--------------MOIPR5 = 0x00000504---------------------------------------

    CAN_vWriteAMData(0x00000504); // load MO5 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR5 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO5 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR5
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 2 valid data bytes

  //--------------MOFCR5 = 0x02000000---------------------------------------

    CAN_vWriteAMData(0x02000000); // load MO5  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  -----------------------------------------------------------------------
  ///  - message object 6 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  -----------------------------------------------------------------------
  ///  - message object 7 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  -----------------------------------------------------------------------
  ///  - message object 8 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  -----------------------------------------------------------------------
  ///  - message object 9 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  -----------------------------------------------------------------------
  ///  - message object 10 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  -----------------------------------------------------------------------
  ///  - message object 11 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  -----------------------------------------------------------------------
  ///  - message object 12 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  -----------------------------------------------------------------------
  ///  - message object 13 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  -----------------------------------------------------------------------
  ///  - message object 14 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  -----------------------------------------------------------------------
  ///  - message object 15 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------
  ///  - message object 16 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR16 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR16); // Addressing MO16 control register

    CAN_vWriteAMData(0x0EA80000); // load MO16 control register

  //  CAN Address pointing to the CAN_MOAR16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x748

  //--------------MOAR16 = 0xDD200000---------------------------------------

    CAN_vWriteAMData(0xDD200000); // load MO16 arbitration register

  //  CAN Address pointing to the CAN_MODATAH16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH16 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO16 data register high

  //  CAN Address pointing to the CAN_MODATAL16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL16 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO16 data register low

  //  CAN Address pointing to the CAN_MOAMR16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR16 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO16 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 16

  //--------------MOIPR16 = 0x00001000---------------------------------------

    CAN_vWriteAMData(0x00001000); // load MO16 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR16 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO16 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR16
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR16 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO16  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------
  ///  - message object 17 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR17 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR17); // Addressing MO17 control register

    CAN_vWriteAMData(0x0EA80000); // load MO17 control register

  //  CAN Address pointing to the CAN_MOAR17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x749

  //--------------MOAR17 = 0xDD240000---------------------------------------

    CAN_vWriteAMData(0xDD240000); // load MO17 arbitration register

  //  CAN Address pointing to the CAN_MODATAH17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH17 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO17 data register high

  //  CAN Address pointing to the CAN_MODATAL17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL17 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO17 data register low

  //  CAN Address pointing to the CAN_MOAMR17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR17 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO17 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 17

  //--------------MOIPR17 = 0x00001100---------------------------------------

    CAN_vWriteAMData(0x00001100); // load MO17 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR17 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO17 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR17
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR17 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO17  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------
  ///  - message object 18 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR18 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR18); // Addressing MO18 control register

    CAN_vWriteAMData(0x0EA80000); // load MO18 control register

  //  CAN Address pointing to the CAN_MOAR18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74A

  //--------------MOAR18 = 0xDD280000---------------------------------------

    CAN_vWriteAMData(0xDD280000); // load MO18 arbitration register

  //  CAN Address pointing to the CAN_MODATAH18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH18 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO18 data register high

  //  CAN Address pointing to the CAN_MODATAL18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL18 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO18 data register low

  //  CAN Address pointing to the CAN_MOAMR18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR18 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO18 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 18

  //--------------MOIPR18 = 0x00001200---------------------------------------

    CAN_vWriteAMData(0x00001200); // load MO18 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR18 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO18 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR18
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR18 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO18  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------
  ///  - message object 19 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR19 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR19); // Addressing MO19 control register

    CAN_vWriteAMData(0x0EA80000); // load MO19 control register

  //  CAN Address pointing to the CAN_MOAR19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74B

  //--------------MOAR19 = 0xDD2C0000---------------------------------------

    CAN_vWriteAMData(0xDD2C0000); // load MO19 arbitration register

  //  CAN Address pointing to the CAN_MODATAH19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH19 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO19 data register high

  //  CAN Address pointing to the CAN_MODATAL19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL19 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO19 data register low

  //  CAN Address pointing to the CAN_MOAMR19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR19 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO19 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 19

  //--------------MOIPR19 = 0x00001300---------------------------------------

    CAN_vWriteAMData(0x00001300); // load MO19 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR19 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO19 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR19
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR19 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO19  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------
  ///  - message object 20 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR20 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR20); // Addressing MO20 control register

    CAN_vWriteAMData(0x0EA80000); // load MO20 control register

  //  CAN Address pointing to the CAN_MOAR20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74C

  //--------------MOAR20 = 0xDD300000---------------------------------------

    CAN_vWriteAMData(0xDD300000); // load MO20 arbitration register

  //  CAN Address pointing to the CAN_MODATAH20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH20 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO20 data register high

  //  CAN Address pointing to the CAN_MODATAL20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL20 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO20 data register low

  //  CAN Address pointing to the CAN_MOAMR20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR20 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO20 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 20

  //--------------MOIPR20 = 0x00001400---------------------------------------

    CAN_vWriteAMData(0x00001400); // load MO20 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR20 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO20 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR20
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR20 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO20  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------
  ///  - message object 21 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR21 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR21); // Addressing MO21 control register

    CAN_vWriteAMData(0x0EA80000); // load MO21 control register

  //  CAN Address pointing to the CAN_MOAR21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74D

  //--------------MOAR21 = 0xDD340000---------------------------------------

    CAN_vWriteAMData(0xDD340000); // load MO21 arbitration register

  //  CAN Address pointing to the CAN_MODATAH21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH21 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO21 data register high

  //  CAN Address pointing to the CAN_MODATAL21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL21 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO21 data register low

  //  CAN Address pointing to the CAN_MOAMR21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR21 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO21 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 21

  //--------------MOIPR21 = 0x00001500---------------------------------------

    CAN_vWriteAMData(0x00001500); // load MO21 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR21 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO21 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR21
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR21 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO21  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------
  ///  - message object 22 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR22 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR22); // Addressing MO22 control register

    CAN_vWriteAMData(0x0EA80000); // load MO22 control register

  //  CAN Address pointing to the CAN_MOAR22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74E

  //--------------MOAR22 = 0xDD380000---------------------------------------

    CAN_vWriteAMData(0xDD380000); // load MO22 arbitration register

  //  CAN Address pointing to the CAN_MODATAH22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH22 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO22 data register high

  //  CAN Address pointing to the CAN_MODATAL22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL22 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO22 data register low

  //  CAN Address pointing to the CAN_MOAMR22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR22 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO22 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 22

  //--------------MOIPR22 = 0x00001600---------------------------------------

    CAN_vWriteAMData(0x00001600); // load MO22 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR22 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO22 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR22
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR22 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO22  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------
  ///  - message object 23 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR23 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR23); // Addressing MO23 control register

    CAN_vWriteAMData(0x0EA80000); // load MO23 control register

  //  CAN Address pointing to the CAN_MOAR23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x74F

  //--------------MOAR23 = 0xDD3C0000---------------------------------------

    CAN_vWriteAMData(0xDD3C0000); // load MO23 arbitration register

  //  CAN Address pointing to the CAN_MODATAH23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH23 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO23 data register high

  //  CAN Address pointing to the CAN_MODATAL23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL23 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO23 data register low

  //  CAN Address pointing to the CAN_MOAMR23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR23 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO23 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 23

  //--------------MOIPR23 = 0x00001700---------------------------------------

    CAN_vWriteAMData(0x00001700); // load MO23 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR23 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO23 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR23
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR23 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO23  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------
  ///  - message object 24 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR24 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR24); // Addressing MO24 control register

    CAN_vWriteAMData(0x0EA80000); // load MO24 control register

  //  CAN Address pointing to the CAN_MOAR24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x750

  //--------------MOAR24 = 0xDD400000---------------------------------------

    CAN_vWriteAMData(0xDD400000); // load MO24 arbitration register

  //  CAN Address pointing to the CAN_MODATAH24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH24 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO24 data register high

  //  CAN Address pointing to the CAN_MODATAL24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL24 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO24 data register low

  //  CAN Address pointing to the CAN_MOAMR24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR24 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO24 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 24

  //--------------MOIPR24 = 0x00001800---------------------------------------

    CAN_vWriteAMData(0x00001800); // load MO24 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR24 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO24 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR24
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR24 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO24  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------
  ///  - message object 25 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR25 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR25); // Addressing MO25 control register

    CAN_vWriteAMData(0x0EA80000); // load MO25 control register

  //  CAN Address pointing to the CAN_MOAR25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x751

  //--------------MOAR25 = 0xDD440000---------------------------------------

    CAN_vWriteAMData(0xDD440000); // load MO25 arbitration register

  //  CAN Address pointing to the CAN_MODATAH25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH25 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO25 data register high

  //  CAN Address pointing to the CAN_MODATAL25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL25 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO25 data register low

  //  CAN Address pointing to the CAN_MOAMR25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR25 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO25 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 25

  //--------------MOIPR25 = 0x00001900---------------------------------------

    CAN_vWriteAMData(0x00001900); // load MO25 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR25 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO25 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR25
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR25 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO25  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------
  ///  - message object 26 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR26 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR26); // Addressing MO26 control register

    CAN_vWriteAMData(0x0EA80000); // load MO26 control register

  //  CAN Address pointing to the CAN_MOAR26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x752

  //--------------MOAR26 = 0xDD480000---------------------------------------

    CAN_vWriteAMData(0xDD480000); // load MO26 arbitration register

  //  CAN Address pointing to the CAN_MODATAH26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH26 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO26 data register high

  //  CAN Address pointing to the CAN_MODATAL26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL26 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO26 data register low

  //  CAN Address pointing to the CAN_MOAMR26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR26 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO26 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 26

  //--------------MOIPR26 = 0x00001A00---------------------------------------

    CAN_vWriteAMData(0x00001A00); // load MO26 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR26 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO26 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR26
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR26 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO26  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR27 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR27); // Addressing MO27 control register

    CAN_vWriteAMData(0x0EA80000); // load MO27 control register

  //  CAN Address pointing to the CAN_MOAR27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x753

  //--------------MOAR27 = 0xDD4C0000---------------------------------------

    CAN_vWriteAMData(0xDD4C0000); // load MO27 arbitration register

  //  CAN Address pointing to the CAN_MODATAH27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH27 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO27 data register high

  //  CAN Address pointing to the CAN_MODATAL27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL27 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO27 data register low

  //  CAN Address pointing to the CAN_MOAMR27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR27 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO27 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 27

  //--------------MOIPR27 = 0x00001B00---------------------------------------

    CAN_vWriteAMData(0x00001B00); // load MO27 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR27 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO27 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR27
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR27 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO27  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR28 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR28); // Addressing MO28 control register

    CAN_vWriteAMData(0x0EA80000); // load MO28 control register

  //  CAN Address pointing to the CAN_MOAR28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x754

  //--------------MOAR28 = 0xDD500000---------------------------------------

    CAN_vWriteAMData(0xDD500000); // load MO28 arbitration register

  //  CAN Address pointing to the CAN_MODATAH28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH28 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO28 data register high

  //  CAN Address pointing to the CAN_MODATAL28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL28 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO28 data register low

  //  CAN Address pointing to the CAN_MOAMR28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR28 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO28 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 28

  //--------------MOIPR28 = 0x00001C00---------------------------------------

    CAN_vWriteAMData(0x00001C00); // load MO28 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR28 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO28 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR28
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR28 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO28  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR29 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR29); // Addressing MO29 control register

    CAN_vWriteAMData(0x0EA80000); // load MO29 control register

  //  CAN Address pointing to the CAN_MOAR29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x755

  //--------------MOAR29 = 0xDD540000---------------------------------------

    CAN_vWriteAMData(0xDD540000); // load MO29 arbitration register

  //  CAN Address pointing to the CAN_MODATAH29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH29 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO29 data register high

  //  CAN Address pointing to the CAN_MODATAL29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL29 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO29 data register low

  //  CAN Address pointing to the CAN_MOAMR29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR29 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO29 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 29

  //--------------MOIPR29 = 0x00001D00---------------------------------------

    CAN_vWriteAMData(0x00001D00); // load MO29 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR29 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO29 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR29
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR29 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO29  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR30 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR30); // Addressing MO30 control register

    CAN_vWriteAMData(0x0EA80000); // load MO30 control register

  //  CAN Address pointing to the CAN_MOAR30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x756

  //--------------MOAR30 = 0xDD580000---------------------------------------

    CAN_vWriteAMData(0xDD580000); // load MO30 arbitration register

  //  CAN Address pointing to the CAN_MODATAH30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH30 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO30 data register high

  //  CAN Address pointing to the CAN_MODATAL30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL30 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO30 data register low

  //  CAN Address pointing to the CAN_MOAMR30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR30 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO30 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 30

  //--------------MOIPR30 = 0x00001E00---------------------------------------

    CAN_vWriteAMData(0x00001E00); // load MO30 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR30 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO30 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR30
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR30 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO30  function control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  //--------------MOCTR31 = 0x0EA80000---------------------------------------

    CAN_vWriteCANAddress(CAN_MOCTR31); // Addressing MO31 control register

    CAN_vWriteAMData(0x0EA80000); // load MO31 control register

  //  CAN Address pointing to the CAN_MOAR31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x757

  //--------------MOAR31 = 0xDD5C0000---------------------------------------

    CAN_vWriteAMData(0xDD5C0000); // load MO31 arbitration register

  //  CAN Address pointing to the CAN_MODATAH31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MODATAH31 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO31 data register high

  //  CAN Address pointing to the CAN_MODATAL31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  //--------------MODATAL31 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO31 data register low

  //  CAN Address pointing to the CAN_MOAMR31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  //--------------CAN_MOAMR31 = 0x3FFFFFFF------------------------------------

    CAN_vWriteAMData(0x3FFFFFFF); // load MO31 acceptance mask register

  //  CAN Address pointing to the CAN_MOIPR31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - use message pending register 0 bit position 31

  //--------------MOIPR31 = 0x00001F00---------------------------------------

    CAN_vWriteAMData(0x00001F00); // load MO31 interrupt pointer register

  //  CAN Address pointing to the CAN_MOFGPR31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)


  //--------------MOFGPR31 = 0x00000000---------------------------------------

    CAN_vWriteAMData(0x00000000); // load MO31 FIFO/gateway pointer register

  //  CAN Address pointing to the CAN_MOFCR31
    CAN_ADCON = ADR_DEC;         // Auto Decrement the current address(-1)

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  //--------------MOFCR31 = 0x08000000---------------------------------------

    CAN_vWriteAMData(0x08000000); // load MO31  function control register


  ///  -----------------------------------------------------------------------
  ///  Configuration of the Interrupts:
  ///  -----------------------------------------------------------------------
  ///  - CAN interrupt node 0 is disabled
  ///  - CAN interrupt node 1 is disabled
  ///  - CAN interrupt node 2 is disabled
  ///  - CAN interrupt node 3 is disabled
  ///  - CAN interrupt node 4 is enabled
  ///  - CAN interrupt node 5 is disabled
  ///  - CAN interrupt node 6 is disabled
  ///  - CAN interrupt node 7 is disabled


  ///  - MultiCAN Nodex Interrupt enable bit is set in SHINT_vInit() function

  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------


  ///  - -----------CAN_NCR1--------------------------------------------------------

    CAN_vWriteCANAddress(CAN_NCR1); // Addressing CAN_NCR1
    CAN_vReadEN();               // Read Mode is Enabled
    CAN_DATA0  &= ~0x41;         // reset INIT and CCE
    CAN_vWriteEN(D0_VALID);      // Data0 is Valid for transmission and Write 
                                 // is Enabled


  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit

//****************************************************************************
// @Function      void CAN_vWriteAMData(ulong ulValue) 
//
//----------------------------------------------------------------------------
// @Description   This function writes 32-bit Data to CAN Data Register's 
//                0-3respectively. 
//                Note:
//                Write Process :
//                ->Write the address of the MultiCAN kernel register to the 
//                CAN_ADL and CAN_ADH registers.
//                use macro : CAN_vWriteCANAddress. 
//                ->Write the data to the 
//                CAN_DATA0/CAN_DATA1/CAN_DATA2/CAN_DATA3 registers.
//                ->Write the register CAN_ADCON, including setting the valid 
//                bit of the data registers and setting register bit RWEN to 
//                1.
//                ->The valid data will be written to the MultiCAN kernel 
//                only once. Register bit BSY will become 1.
//                ->When Register bit BSY becomes 0, the transmission is 
//                finished.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ulValue: 
//                32-bit Data
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

// USER CODE BEGIN (WriteAMData,1)

// USER CODE END

void CAN_vWriteAMData(ulong ulValue)
{
  un_32bit ulData;
  ulData.ulVal = ulValue;

    CAN_DATA0 = ulData.ubDB[3]; // load CAN Data Register 0
    CAN_DATA1 = ulData.ubDB[2]; // load CAN Data Register 1
    CAN_DATA2 = ulData.ubDB[1]; // load CAN Data Register 2
    CAN_DATA3 = ulData.ubDB[0]; // load CAN Data Register 3
        CAN_vWriteEN(ALL_DATA_VALID); // Writemode is Enabled
} //  End of function CAN_vWriteAMData

//****************************************************************************
// @Function      void CAN_vSetListCommand(ulong ulVal) 
//
//----------------------------------------------------------------------------
// @Description   This function write's 32-bit Data to CAN_PANCTR Register.
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ulVal: 
//                32-bit Data
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

// USER CODE BEGIN (SetListCommand,1)

// USER CODE END

void CAN_vSetListCommand(ulong ulVal)
{
    CAN_vWriteAMData(ulVal);  // - load Panel Control Register
    CAN_DATA1 = CAN_PANCTR_BUSY;
    while(CAN_DATA1 & CAN_PANCTR_BUSY){ // wait until Panel has finished the 
                                        // initialisation
      CAN_ADCON &= ~0x01;       
      }                         
} //  End of function CAN_vSetListCommand

//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-31)
//
//----------------------------------------------------------------------------
// @Date          12.08.2009
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{
    CAN_pushAMRegs();    //   PUSH the CAN Access Mediator Register

    CAN_vWriteCANAddress(CAN_MOCTR(ubObjNr));  //Addressing CAN_MOCTR register
    CAN_vWriteCANData(0x07200000);      // set TXRQ,TXEN0,TXEN1,MSGVAL

    CAN_popAMRegs();    //   POP the CAN Access Mediator Register

} //  End of function CAN_vTransmit


// USER CODE BEGIN (CAN_General,10)

// USER CODE END

