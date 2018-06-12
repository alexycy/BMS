#ifndef _TLE4998_FLASH_H_
#define _TLE4998_FLASH_H_

#include "MAIN.H"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


extern void FlashErrors(SlaveData *pSlaveData);
extern void FlashCalculateAdr(SlaveData *pSlaveData);
extern void FlashReadErrors( SlaveData *pSlaveData );
extern void FlashBufferErrors( SlaveData *pSlaveData);
extern void FlashBoardCorrValues( unsigned int *buffer );
extern void FlashReadBoardCorrValues( SlaveData *pSlaveData );
 

#endif
