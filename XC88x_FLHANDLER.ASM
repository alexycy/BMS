;************************************************************************************
;*  FILE        : XC88x_FLHANDLER.ASM                                               *
;*  DESCRIPTION : Flash handler routine for XC88x AA and AB                                *
;*  COPYRIGHT   : (c) 2006 Infineon Technologies AG                                 *
;*  UPDATED     : 14/03/2006                                                        *
;************************************************************************************
$ NOMOD51
$ DEBUG
#include "XC88x_FLADDR.H"  

FLASH_ERASE        CODE  FLASH_ERASE_BROM_ENTRY
FLASH_PROG         CODE  FLASH_PROGRAM_BROM_ENTRY
FLASH_ERASE_ABORT  CODE  FLASH_ERASE_ABORT_BROM_ENTRY
FLASH_READ_STATUS  CODE  FLASH_READ_STATUS_BROM_ENTRY
     
DSEG AT  MAGIC_MEMORY
DS   RESERVED_BYTES                        ; Reserved for FLASH Handler in Boot ROM


PUBLIC WLBuf
WLBuf      IDATA   WORDLINE_BUFFER_ADDRESS ; Fixing the location of the WordLinebuffer
                                           ; User Configurable.
                                           ; needed for programming procedure
DS BYTES_PER_WORDLINE                      ; reserve 64 or 32 byte space - size of one wordline 

;CSEG AT 0xB7E0
;DB 0x12
;CSEG AT 0xB7EC
;DB 0x56
;CSEG AT 0xB000
;DB 0xAA
;CSEG AT 0xB006
;DB 0xAA
;CSEG AT 0xB008
;DB 0xAA
;CSEG AT 0xB00A
;DB 0xAA
;CSEG AT 0xA0C0
;DB 0xAA
;CSEG AT 0xA0E0
;DB 0xAA
;CSEG AT 0xA100
;DB 0xAA
;CSEG AT 0xA120
;DB 0xAA
;CSEG AT 0xA140
;DB 0xAA
;CSEG AT 0xA160
;DB 0xAA
;CSEG AT 0xA180
;DB 0xAA
;CSEG AT 0xA1A0
;DB 0xAA
;CSEG AT 0xA1C0
;DB 0xAA
;CSEG AT 0xA1E0
;DB 0xAA
;CSEG AT 0xA200
;DB 0xAA
;CSEG AT 0xA220
;DB 0xAA
;CSEG AT 0xA240
;DB 0xAA
;CSEG AT 0xA260
;DB 0xAA
;CSEG AT 0xA280
;DB 0xAA
;CSEG AT 0xA2A0
;DB 0xAA
;CSEG AT 0xA2C0
;DB 0xAA
;CSEG AT 0xA2E0
;DB 0xAA
;CSEG AT 0xA300
;DB 0xAA
;CSEG AT 0xA320
;DB 0xAA
;CSEG AT 0xA340
;DB 0xAA
;CSEG AT 0xA360
;DB 0xAA
;CSEG AT 0xA380
;DB 0xAA
;CSEG AT 0xA3A0
;DB 0xAB
;CSEG AT 0xA3C0
;DB 0x14
;CSEG AT 0xA400
;DB 0x12


;------------------------------------------------------------------------------------------
;;#if (XC88xAA)
;------------------------------------------------------------------------------------------
; Function Name   : bit PFlErase (unsigned char B0Sector, unsigned char B1Sector, unsigned char B2Sector)
; Description     : Erase PFlash Sectors (Bank0, Bank1, and Bank2)
; Input Parameter : B0Sector => Bit0 = Erase Sector0
;                               Bit1 = Erase Sector1
;                               Bit2 = Erase Sector2
;                   B0Sector => Bit0 = Erase Sector0
;                               Bit1 = Erase Sector1
;                               Bit2 = Erase Sector2
;                   B2Sector => Bit0 = Erase Sector0
;                               Bit1 = Erase Sector1
;                               Bit2 = Erase Sector2
;                                                   
;                   (e.g: B0Sector = 0x2, B1Sector = 0x01, B2Sector = 0x3
;                         ==> Will erase Bank0 Sector 1
;                                  erase Bank1 Sector 0
;                                  erase Bank2 Sector 0
;                                  erase Bank2 Sector 1
; Return Value    : Bit => 1 = Successfull
;                          0 = Fail
; Required Stack Size = 12
;------------------------------------------------------------------------------------------
;GK#if USE_PFLERASE
;GK?PR?_PFlErase?XC88x_FLHANDLER SEGMENT CODE    
;GKRSEG ?PR?_PFlErase?XC88x_FLHANDLER
;GKPUBLIC _PFlErase
;GK_PFlErase:
;GK  USING  USE_BANK
;GK  MOV  AR6,R5  ; BANK1
;GK  MOV  AR5,R7  ; BANK0
;GK  MOV  AR7,R3  ; BANK2
;GK
;GK  CLR    A
;GK  MOV    AR1, A;  Bank3
;GK  MOV    AR0, A;  Bank3
;GK  MOV    AR4, A;  Bank4
;GK  MOV    AR3, A;  Bank4
;GK  PUSH   PSW
;GK#if (USE_BANK == 0)
;GK  ANL    PSW, #0xE7      ; Set to Bank0
;GK#elif (USE_BANK == 1)
;GK  SETB   PSW.3
;GK  CLR    PSW.4
;GK#elif (USE_BANK == 2)
;GK  CLR    PSW.3
;GK  SETB   PSW.4
;GK#elif (USE_BANK == 3)
;GK  ORL    PSW, #0x18
;GK#endif
;GK 
;GK ;MOV    FLASH_VAR, A    ; FLASH_READY
;GK  LCALL  FLASH_ERASE
;GK  JC     _perase_fail
;GK  POP    PSW
;GK  SETB   C
;GK  RET
;GK_perase_fail:
;GK  POP    PSW
;GK  CLR    C
;GKRET
;GK#endif

;------------------------------------------------------------------------------------------
; Function Name   : bit DFlErase (unsigned int DFlash0Sector, unsigned int DFlash1Sector)
; Description     : Erase DFlash Sectors (Bank3 and Bank4)
; Input Parameter : DFlash0Sector => Bit0 = Erase Sector0
;                                    Bit1 = Erase Sector1
;                                    Bit2 = Erase Sector2
;                                    Bit3 = Erase Sector3
;                                    Bit4 = Erase Sector4
;                                    Bit5 = Erase Sector5
;                                    Bit6 = Erase Sector6
;                                    Bit7 = Erase Sector7
;                                    Bit8 = Erase Sector8
;                                    Bit9 = Erase Sector9
;                   DFlash1Sector => Bit0 = Erase Sector0
;                                    Bit1 = Erase Sector1
;                                    Bit2 = Erase Sector2
;                                    Bit3 = Erase Sector3
;                                    Bit4 = Erase Sector4
;                                    Bit5 = Erase Sector5
;                                    Bit6 = Erase Sector6
;                                    Bit7 = Erase Sector7
;                                    Bit8 = Erase Sector8
;                                    Bit9 = Erase Sector9
;                                                   
;                   e.g: DFlash0Sector = 0x202
;                        DFlash1Sector = 0x380
;                         ==> Will erase Bank3 Sector 1
;                                  erase Bank3 Sector 9
;                                  erase Bank4 Sector 7
;                                  erase Bank4 Sector 8
;                                  erase Bank4 Sector 9
; Return Value    : Bit => 1 = Successfull
;                          0 = Fail
; Required Stack Size = 12
;------------------------------------------------------------------------------------------
#if USE_DLFERASE
?PR?_DFlErase?XC88x_FLHANDLER SEGMENT CODE    
RSEG ?PR?_DFlErase?XC88x_FLHANDLER
PUBLIC _DFlErase
_DFlErase:
  USING  USE_BANK
  MOV  AR1,R6  ; BANK3
  MOV  AR0,R7  ; BANK3

  MOV  AR4,R4 ; BANK4
  MOV  AR3,R5 ; BANK4

  CLR    A
  MOV    AR5, A ; BANK0
  MOV    AR6, A ; BANK1
  MOV    AR7, A ; BANK2

  PUSH   PSW
#if (USE_BANK == 0)
  ANL    PSW, #0xE7      ; Set to Bank0
#elseif (USE_BANK == 1)
  SETB   PSW.3
  CLR    PSW.4
#elif (USE_BANK == 2)
  CLR    PSW.3
  SETB   PSW.4
#elif (USE_BANK == 3)
  ORL    PSW, #0x18
#endif
 ;MOV    FLASH_VAR, A   ; FLASH_READY
  LCALL  FLASH_ERASE
  JC     _derase_fail
  POP    PSW
  SETB   C
  RET
_derase_fail:
  POP    PSW
  CLR    C
RET
#endif

;------------------------------------------------------------------------------------------
; Function Name:   bit FlProg(unsigned char idata *WlBuf)
; Description:     Program the 32byte data in the WlBuf to the EEPROM
;                  When calling this function, user should already programmed
;                  the DPTR with the EEPROM address (aligned to 32byte boundary)
; Input Parameter: *WlBuf  ==> The pointer to the starting location of the buffer
;                              in the IDATA memory.
; Return Value:    Bit => 1 = Successfull
;                         0 = Fail
; Required Stack Size = 12
;------------------------------------------------------------------------------------------
?PR?_FlProg?XC88x_FLHANDLER SEGMENT CODE    
RSEG ?PR?_FlProg?XC88x_FLHANDLER
PUBLIC _FlProg
_FlProg:
using USE_BANK
  MOV   AR0,R7          ; move C51 parameter registers to AR0
                       ; this is the pointer to the WLBuf
  PUSH   PSW
#if (USE_BANK == 0)
  ANL    PSW, #0xE7      ; Set to Bank0
#elif (USE_BANK == 1)
  SETB   PSW.3
  CLR    PSW.4
#elif (USE_BANK == 2)
  CLR    PSW.3
  SETB   PSW.4
#elif (USE_BANK == 3)
  ORL    PSW, #0x18
#endif
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  LCALL  FLASH_PROG     ; LCALL FLASH_PROG
  JC     _prog_fail
  POP    PSW
  SETB   C
  RET
_prog_fail:
  POP    PSW
  CLR    C
RET


;------------------------------------------------------------------------------------------
; Function Name:   bit FlReady(unsigned char BankNum)
; Description:     Check if the flash bank is ready for reading or not
; Input Parameter: BankNum => 0 = Bank0
;                             1 = Bank1
;                             2 = Bank2
;                             3 = Bank3
; Return Value:    1  ==> Flash is ready for reading
;                  0  ==> Flash is not ready for reading
; Required Stack Size = 6
;------------------------------------------------------------------------------------------
?PR?_FlReady?XC88x_FLHANDLER SEGMENT CODE    
RSEG ?PR?_FlReady?XC88x_FLHANDLER
PUBLIC _FlReady
_FlReady:
  PUSH    PSW
  MOV     A, R7
  LCALL   FLASH_READ_STATUS
  JNC    _read_fail
  POP    PSW
  SETB   C
  RET
_read_fail:
  POP    PSW
  CLR    C 
RET

;------------------------------------------------------------------------------------------
; Function Name:   bit FlEraseAbort (void)
; Description:     Abort the existing erase process
;                  The aborting can be done only after about 5ms of the start of erase
; Input Parameter: none
; Return Value:    1 = Success
;                  0 = Fail - No abort can be done
;                           - Maybe it is not yet 5ms.
; Required Stack Size = 6
;------------------------------------------------------------------------------------------
;GK?PR?FlEraseAbort?XC88x_FLHANDLER SEGMENT CODE    
;GKRSEG ?PR?FlEraseAbort?XC88x_FLHANDLER
;GKPUBLIC FlEraseAbort
;GKFlEraseAbort:
;GK  PUSH   PSW
;GK  LCALL  FLASH_ERASE_ABORT
;GK  JC     _abort_fail
;GK  POP    PSW
;GK  SETB   C
;GK  RET
;GK_abort_fail:
;GK  POP    PSW
;GK  CLR    C
;GKRET


END
        
;;#endif    ;;#if (XC88xAA)
