#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MemoryXC8.h"
#include "Routines.h"
#include "Flash.h"

// external functions
extern void ScanTempAndBlockVoltage(SlaveData *pSlaveData);
extern void ScanCells(SlaveData *pSlaveData);
extern void PrintAll(SlaveData *pSlaveData);
extern void CellBalancing(SlaveData *pSlaveData);
extern void IsAnyCellOutOfRange(SlaveData *pSlaveData);
extern void IsTemperatureAndBlockOutOfRange(SlaveData *pSlaveData);
extern void Print(SlaveData *pSlaveData);
extern void PrintDigit(SlaveData *pSlaveData);
// external variable
extern char idata FLAG_Pin;


void ServiceMode(SlaveData *pSlaveData)
{
  unsigned long loop;
  unsigned char i, c;		   
  char argsread;  

  // clear read interrupt
  RI=0;
   
  //**********************************************************
  //				             MENUE
  //**********************************************************
  do
  {
     printf("\n\n- Service Mode - press any key to start\n");
     printf("s   = single scan\n");	    		
     printf("b   = bottom 1x\n");
     printf("t   = top 1x\n");
     printf("i   = inter block 1x\n");
     printf("m   = scan+balancing (select mode)\n");
	 printf("u   = scan+balancing (normal mode)\n");
     printf("c   = calibration\n");
	 printf("r   = write/read flashed errors\n");
	 printf("ST  = board SelfTest switch S3 to F\n");

	 do
	 { 
//#ifdef SM_LIGHT       
//	   // LED on -> only for debug
//	   LED_ON;
//	   // pause									 
//	   for(loop=0; loop<20000; loop++);
//	   // LED off -> only for debug
//	   LED_OFF;
//#endif
	   // pause
	   for(loop=0; loop<20000; loop++);
	   // scan temp
	   ScanTempAndBlockVoltage(pSlaveData);
	   // sort temp
	   GetAndSortTemperature(pSlaveData); 
	 }while( ((RI==0) && !(pSlaveData->Uident < U2_48V)));
	 
	 //*********************
	 //         menue
	 //*********************
	 if(RI)
     { 
	    RI=0;

		// 'b' = bottom balancing
		if(SBUF==0x62) 
		{
		  do
		  {
		   printf("\n BottomBalancing 1x... enter the battery cell: ");
		   argsread = scanf ("%bu", &i);
		  }while( getchar() != '\n' );			
		  
		  if(argsread==0)
		    continue;						 
		  
		  do
		  {		
			 pSlaveData->LowestCellIndex = i;
			 pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex] = i;
			 BottomBalancing(pSlaveData);
			 printf(" press any key to repeat or ESC\n");
				
			 // press 's' for stop 
			 do{ _nop_(); }while(RI==0 );					  					  
			 
			 RI=0;		  	
			 // escape
			 if(SBUF==0x1B)
			 {
	           printf("\nEscape.....\n");
	           break;
			 }		  
		  }while(1);
		} // end bottom balancing
     	
		// 't' = top	balancing
		if(SBUF==0x74) 
		{
		  do
		  {
		   printf("\n TopBalancing 1x... enter the battery cell: ");
		   argsread = scanf ("%bu", &i);
		  }while( getchar() != '\n' );			
		  
		  if(argsread==0)
		    continue;						 
		    		  
		  do
		  {					 
			 pSlaveData->BalanceCellIndex[0] = i;
			 TopBalancing(pSlaveData);
			 printf(" press any key to repeat or ESC\n");
				
			 // press 's' for stop 
			 do{ _nop_(); }while(RI==0 );					  					  
			 
			 RI=0;		  	
			 // escape
			 if(SBUF==0x1B)
			 {
	           printf("\nEscape.....\n");
	           break;
			 }		  
		  }while(1);
		} // end top balancing
		
		// 'i' = inter block balancing
		if(SBUF==0x69) 
		{
		  do
		  {
		   printf("\n InterBlockBalancing 1x... enter the battery cell: ");
		   argsread = scanf ("%bu", &i);
		  }while( getchar() != '\n' );			
		  
		  if(argsread==0)
		    continue;						 
		  
		  do
		  {					
			pSlaveData->BalanceCellIndex[0] = i;
			InterBlockTopBalancing(pSlaveData);
			printf(" press any key to repeat or ESC\n");
			
			// press 's' for stop 
			do{ _nop_(); }while(RI==0 );					  					  
			
			RI=0;		  	
			// escape
			if(SBUF==0x1B)
			{
	          printf("\nEscape.....\n");
	          break;
			}		  
		  }while(1);
		} // end inter block balancing 
		
		// 'r' = read flashed errors
		if(SBUF==0x72)  
		{		    												           		  
		  printf("\n Write/Read flashed errors / ESC\n");
       	  
       	  // simulated errors
          pSlaveData->Error   |= CellOverLevel;  
          pSlaveData->Error   |= CellUnderLevel; 
          pSlaveData->Error   |= TempOverLevel;	    
       	  pSlaveData->Error   |= SlaveGetsNoPing;
		  pSlaveData->Warning |= TempShortCut;
       	  pSlaveData->Warning |= TempOpen;

       	  // read flash
       	  FlashCalculateAdr(pSlaveData);	 	     	 
       	  // and buffer errors
          FlashBufferErrors(pSlaveData);	           	 										 
       	  // flash errors
       	  FlashErrors(pSlaveData);     	 	         
		  
		  do
		  {		    			
			// read flashed errors
			FlashReadErrors(pSlaveData);
			printf(" press any key to repeat or ESC\n");		    
		    // press 's' for stop 
		    do{ _nop_(); }while(RI==0 );					  					  
		    
		    RI=0;
		    // escape 
		    if(SBUF==0x1B)
		    {
              printf("\nEscape.....\n");
              break;
		    }
		  }while(1);
		} // end read flashed errors
		
		// 's' = single scan		    
		if(SBUF==0x73)  
		{
		  // read factors  												  
          FlashReadBoardCorrValues(pSlaveData);

		  do{
		    printf("\n Single scan...\n");
			// scan all Temperature sensors
            ScanTempAndBlockVoltage(pSlaveData);
			// scan all cells
            ScanCells(pSlaveData);
			// calculate min/max cells
			GetAndSortAllCellVoltages(pSlaveData);
			// calculate min/max temperature
			GetAndSortTemperature(pSlaveData);
		    // print digit values
		    PrintDigit(pSlaveData);			
			// print
			PrintAll(pSlaveData);

			printf(" press any key to repeat or ESC\n");		    
		    // press 's' for stop 
		    do{ _nop_(); }while(RI==0 );					  					  
		    
		    RI=0;
		    // escape 
		    if(SBUF==0x1B)
		    {
              printf("\nEscape.....\n");
              break;
		    }
		  }while(1);
		} // end single scan

		// 'm' = scan + balancing
		if(SBUF==0x6d)  
		{
		  // read factors  												  
          FlashReadBoardCorrValues(pSlaveData);
		
		  do
		  {
		    printf("\n Balancing 1x... enter the battery cell (0-11): ");
		    argsread = scanf ("%bu", &i);
		  }while( getchar() != '\n' );					  
		  if(argsread==0)
		    continue;						 
		  
		  do
		  {
		    printf(" Top / Bottom / Inter Balancing (t/b/i): ");
		    argsread = scanf ("%c", &c);
		  }while( getchar() != '\n' );					  
		  if(argsread==0)
		    continue;						 
		  
		  do{
		    printf("\n Scan+Balancing...(select mode)\n");
			// scan all Temperature sensors
			ScanTempAndBlockVoltage(pSlaveData);
			// scan all cells
			ScanCells(pSlaveData);
            // sort all cells
			GetAndSortAllCellVoltages(pSlaveData);
	        // calculate min/max temperature
			GetAndSortTemperature(pSlaveData);
		    // print
			PrintAll(pSlaveData); 
						
			// preparation
			switch(c)
			{
			  case 'b':pSlaveData->BLOCK_BALANCING &= ~INTER_BLOCK;
			           pSlaveData->Uaver_u = U_Level_aver1; 
			           pSlaveData->Umax_u  = UmaxLevel;
			           pSlaveData->Umin_u  = UminLevel;
					   pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex] = i;
					   break;
			  case 't':pSlaveData->BLOCK_BALANCING &= ~INTER_BLOCK;
			           pSlaveData->Uaver_u = U_Level_aver2; 
			           pSlaveData->Umax_u  = UmaxLevel;
			           pSlaveData->Umin_u  = UminLevel;
			           pSlaveData->BalanceCellIndex[0] = i;
			           break;
			  case 'i':pSlaveData->BLOCK_BALANCING |= INTER_BLOCK;
			           pSlaveData->Uaver_u = U_Level_aver2; 
			           pSlaveData->Umax_u  = UmaxLevel;
			           pSlaveData->Umin_u  = UminLevel;
					   pSlaveData->BalanceCellIndex[0] = i;
			           break;
			  default: printf("fault\n");
			}
						
			// use Top- or BottomBalancing
            CellBalancing(pSlaveData);	
            printf(" press any key to repeat or ESC\n");	
		    
		    // press 's' for stop 
		    do{ _nop_(); }while(RI==0 );					  					  		    	 
	        RI=0;		  	
		    
		    // escape 'ESC'
		    if(SBUF==0x1B)
		    {
              printf("\nEscape.....\n");
              break;
		    }
		  }while(1);
		} // end scan + balancing
     
		// 'u' = scan + balancing (normal)
		if(SBUF==0x75)  
		{
		  // read factors  												  
          FlashReadBoardCorrValues(pSlaveData);		  
		  printf("\n Scan+Balancing...(normal mode) / ESC\n");
		  
		  do{		    
			// scan all Temperature sensors
			ScanTempAndBlockVoltage(pSlaveData);
			// scan all cells
			ScanCells(pSlaveData);
            // sort all cells
			GetAndSortAllCellVoltages(pSlaveData);
	        // calculate min/max temperature
			GetAndSortTemperature(pSlaveData);
		    // print
			PrintAll(pSlaveData); 
            
			// clear INTER Block BALANCING
            pSlaveData->BLOCK_BALANCING &= ~INTER_BLOCK;		                 				 				 				  	 			 												
			// use Top- or BottomBalancing
            CellBalancing(pSlaveData);	
                        
		    RI=0;
		    // escape 
		    if(SBUF==0x1B)
		    {
              printf("\nEscape.....\n");
              break;
		    }
		  }while(1);
		} // end scan + balancing (normal)


		// 'c' = calibration
		if(SBUF==0x63)  
		{
		   float Multi_f[Cells+1], Multi_f_temp[Cells+1], Multi_Block_f;
		   float Uadc_f_temp[Cells+1], Ufac[Cells+1], Uadc_Block_f_temp, Ufac_Block;
		   unsigned int Ufac_u[Cells+1], p, Ufac_Block_u;
		   char i, j, argsread, c;
		   			 
		   // Factors=0,5 as Q.15
		   for(i=0; i<Cells; i++)
		     pSlaveData->Ufac_u[i] = Ucell_Grade*32;   //=16384	   
		   // block: 10.946f*4096
		   pSlaveData->Ufac_u[Cells] = Ublock_Grade;
		   
		   // ((0.5f*U+offset)*4096+delta);
		   for(p=0; p<3; p++)
		   {
		     // scan all Temperature sensors
		     ScanTempAndBlockVoltage(pSlaveData);
		     // scan all cells
		     ScanCells(pSlaveData);     
		   }  						
		   
		   // sort all cells
		   GetAndSortAllCellVoltages(pSlaveData);
		   // calculate min/max temperature
		   GetAndSortTemperature(pSlaveData);  	 
		   // print	digit values
		   PrintDigit(pSlaveData);
		   // print
		   PrintAll(pSlaveData);
		   	        
  // CALIBRATE VOLTAGE BLOCK		   
		   // read block voltage
		   for (i=0; i<1; i++)
		   { 						 
		     do
		     {
		       printf ("Enter the block voltage:");
		       argsread = scanf ("%f", &Multi_Block_f);
		       printf ("value %.3f \n", Multi_Block_f);
		     }while( getchar() != '\n' );
		    
		     if(argsread==0)
		     {
		       i--;
		       continue;						 
		     }
		   }

		   // calculation		   		   
		   // U_scan float
		   Uadc_Block_f_temp = (float)pSlaveData->Ublock/(float)256;	//Q.8
		   // m=y1/yo											
		   Ufac_Block = (Multi_Block_f/Uadc_Block_f_temp);
		   
		   printf ("go'[%bu]:%.4f\n", i, Ufac_Block);
		   Ufac_Block_u = (unsigned int)((float)Ufac_Block*pSlaveData->Ufac_u[Cells]+delta);			          	  
  // BLOCK_END		   
	  
	   #if defined (A123_BATTERY_10_CELLS)	   
		   //***************************
		   //	Cell U0-U4, U7-U11
		   //***************************						    			    	
		   for(j=0; j<8; j=j+7)
		   {
		     for (i=0+j; i<Cell_5+j; i++)
		     { 						 
		       do
		       {
		         printf ("Enter the %bu. battery cell:", i);
		         argsread = scanf ("%f", &(Multi_f+i));
		         printf ("value %.3f \n", Multi_f[i]);
		       }while( getchar() != '\n' );
		    	 
		       if(argsread==0)
		       {
		         i--;
		         continue;						 
		       }
		     }
		   }
		
		   // calculation
		   for (i=0; i<Cells; i++)
		   {
		     // Umultimeter float (y1-off)
		     Multi_f_temp[i]= (float)Multi_f[i]- Uoff_f;
		     // U_scan float (yo-off)
		     Uadc_f_temp[i] = (float)pSlaveData->Umux_u[i]/(float)4096- Uoff_f;
		     // m=g1/g0 =(y1-off)/(yo-off)											
		     Ufac[i] = (Multi_f_temp[i]/Uadc_f_temp[i]);
		     // new factor go'=m*go=factor*0.5
		     //Ufac[i] *= 0.5f;
		     printf ("go'[%bu]:%.4f\n", i, Ufac[i]);

		     //if( (Ufac[i] > 1.0f) || (Ufac[i] < 0.0f) )
		     //   printf ("Ufac[%bu]:%.3f > 1 !!!\n", i, Ufac[i]);
		     // unsigned int has the format 2^15
		     Ufac_u[i] = (unsigned int)((float)Ufac[i]*(Ucell_Grade*32)+delta);			          	  
		   }
		   	
		   //***************************
		   //		  Cell U5-U6=0
		   //***************************						    			    
		   for (i=Cell_5; i<Cell_7; i++)
		   {
		     Multi_f[i] = 0;
		     pSlaveData->Ufac_u[i] = 0;
		   }
	   #elif defined (MAXWELL_9_CELLS)   
		   //***************************
		   //	Cell U0-U4, U8-U11
		   //***************************						    			    	
		   for(j=0; j<9; j=j+8)
		   {
		     for (i=0+j; i<Cell_5+j; i++)
		     { 						 
		       do
		       {
		         printf ("Enter the %bu. battery cell:", i);
		         argsread = scanf ("%f", &(Multi_f+i));
		         printf ("value %.3f \n", Multi_f[i]);
		       }while( getchar() != '\n' );
		    	 
		       if(argsread==0)
		       {
		         i--;
		         continue;						 
		       }
		     }
		   }
		
		   // calculation
		   for (i=0; i<Cells; i++)
		   {
		     // Umultimeter float (y1-off)
		     Multi_f_temp[i]= (float)Multi_f[i]- Uoff_f;
		     // U_scan float (yo-off)
		     Uadc_f_temp[i] = (float)pSlaveData->Umux_u[i]/(float)4096- Uoff_f;
		     // m=g1/g0 =(y1-off)/(yo-off)											
		     Ufac[i] = (Multi_f_temp[i]/Uadc_f_temp[i]);
		     // new factor go'=m*go=factor*0.5
		     //Ufac[i] *= 0.5f;
		     printf ("go'[%bu]:%.3f\n", i, Ufac[i]);

		     //if( (Ufac[i] > 1.0f) || (Ufac[i] < 0.0f) )
		     //   printf ("Ufac[%bu]:%.3f > 1 !!!\n", i, Ufac[i]);
		     // unsigned int has the format 2^15
		     Ufac_u[i] = (unsigned int)((float)Ufac[i]*(Ucell_Grade*32)+delta);			          	  
		   }
		   	
		   //***************************
		   //		  Cell U5-U7=0
		   //***************************						    			    
		   for (i=Cell_5; i<Cell_8; i++)
		   {
		     Multi_f[i] = 0;
		     pSlaveData->Ufac_u[i] = 0;
		   }
	   #elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
		   //***************************
		   //	Cell U0-U11
		   //***************************						    			    			   
		   for(j=0; j<Cells; j++)
		   {
		      do
		      {
		         printf ("Enter the %bu. battery cell:", j);
		         argsread = scanf ("%f", &(Multi_f+j));
		         printf ("value %.3f \n", Multi_f[j]);
		      }while( getchar() != '\n' );
		    	 
		      if(argsread==0)
		      {
		        j--;
		        continue;						 
		      }
		   }
		    
		   // calculation
		   for (i=0; i<Cells; i++)
		   {
		     // Umultimeter float (y1-off)
		     Multi_f_temp[i]= (float)Multi_f[i]- Uoff_f;
		     // U_scan float (yo-off)
		     Uadc_f_temp[i] = (float)pSlaveData->Umux_u[i]/(float)4096- Uoff_f;
		     // m=g1/g0 =(y1-off)/(yo-off)											
		     Ufac[i] = (Multi_f_temp[i]/Uadc_f_temp[i]);
		     // new factor go'=m*go=factor*0.5
		     //Ufac[i] *= 0.5f;
		     printf ("go'[%bu]:%.3f\n", i, Ufac[i]);

		     //if( (Ufac[i] > 1.0f) || (Ufac[i] < 0.0f))
		     //   printf ("Ufac[%bu]:%.3f > 1 !!!\n", i, Ufac[i]);
		     // unsigned int has the format 2^15
		     Ufac_u[i] = (unsigned int)((float)Ufac[i]*(Ucell_Grade*32)+delta);			          	  
		   }		    		    
		#endif

		   //***************************
		   //	  flash	corr values
		   //***************************						    			    
		   // copy block voltage corr factor
		   Ufac_u[Cells] = Ufac_Block_u;
		   
		   do
		   {
		      printf ("Do you want to flash y/n?\n", i);
		      c = getchar();                                                        
		   }while( c!='y' && c!='n');
		    
		   if( c=='y' )
		     FlashBoardCorrValues(&Ufac_u);			
			// read factors
		   FlashReadBoardCorrValues(pSlaveData);
		   // check
		   for(i=0; i<Cells; i++)
		   {		      
			  if(Ufac_u[i] != pSlaveData->Ufac_u[i])
				printf("error - cal.fac. cell%bd !!!\n", i);
           }		   
		   if(Ufac_u[Cells] != pSlaveData->Ufac_u[Cells])
		     printf("error - cal.fac. block: !!!\n");
                       		 		  
		   printf("Calibration closed\n");
		} // end calibration

     } // end menue 					  					  

     // POSITION F
	 if(pSlaveData->Uident < U2_48V)
	 {
	   printf("Self-Test:\n");
	   // scan all Temperature sensors
       ScanTempAndBlockVoltage(pSlaveData);
       // sort all Temp
       GetAndSortTemperature(pSlaveData);
	   // scan all cells
	   ScanCells(pSlaveData);
       // sort all cells
       GetAndSortAllCellVoltages(pSlaveData);                                         
     
       // cell processing
       IsAnyCellOutOfRange(pSlaveData);
       // temp processing	>75°C
       IsTemperatureAndBlockOutOfRange(pSlaveData);
	   							 	 
	   // printf
	   Print(pSlaveData);

	   // LEDs
	   if(pSlaveData->Error & CellOverLevel)
	     printf("\n LED_CellOverLevel\n");
       else if(pSlaveData->Error & CellUnderLevel)
	     printf("\n LED_CellUnderLevel\n");
	   else if(pSlaveData->Error & BlockUnderLevel) 
	     printf("\n LED_BlockUnderLevel\n");
       else if(pSlaveData->Error & TempOverLevel)
	     printf("\n LED_TempOverLevel\n");
	   else if(pSlaveData->Warning & (TempOpen | TempShortCut) )
	     printf("\n LED_TempSensor\n");
	   else printf("\n LED_BOARD_OKAY\n");	   		 
	   // no errors	   
	   pSlaveData->Error = 0; 
	   // pause
	   for(loop=0; loop<500000; loop++);
	 }	 
  }while( 1 );	// go out
}
