#ifndef _TLE4998_SLAVE_H_
#define _TLE4998_SLAVE_H_

#include "MAIN.H"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef SLAVE_BOARDS
extern void SlaveAllocateRelevantMessageObjects( char SlaveName );
extern void SlaveDeallocateAllMessageObjects( void );
extern unsigned int SlaveHasBeenPinged(SlaveData *pSlaveData);
extern void SlaveErrorProcessing(SlaveData *pSlaveData);
extern void SlavePrepareOwnBoardDataForCAN(SlaveData *pSlaveData);
extern char SlaveHasBeenRequested(SlaveData *pSlaveData);
#endif

#endif
