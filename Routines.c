/*						 */
/*	 Batteriemanagement  */
/*						 */
#include <stdio.h>
#include <intrins.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "IO.h"
#include "Routines.h"


// function prototypes
//GKvoid DeactivateSek(char SekNo);
void TopBalancing(SlaveData *pSlaveData);
void InterBlockTopBalancing(SlaveData *pSlaveData);
void BottomBalancing(SlaveData *pSlaveData);
void DummyBalancing(SlaveData *pSlaveData);
 
void SortAlgorithm_unsigned(unsigned int *pType, char *pIndex, char loop);
void SortAlgorithm_signed(int *pType, char *pIndex, char loop);
void GetAndSortAllCellVoltages(SlaveData *pSlaveData);
void GetAndSortTemperature(SlaveData *pSlaveData);
unsigned int MDU_Convert_ADC( unsigned int ADC );
int MDU_Convert_ADC2Temp( unsigned int ADC );
unsigned int MDU_Convert_ADC2UBlock(unsigned int ADC);

void SekOn0(void);  
void SekOn1(void);  
void SekOn2(void);  
void SekOn3(void);  
void SekOn4(void);  
void SekOn5(void);  
void SekOn6(void);  
void SekOn7(void);  
void SekOn8(void);  
void SekOn9(void);  
void SekOn10(void);  
void SekOn11(void);

void SekOff0(void);  
void SekOff1(void);  
void SekOff2(void);  
void SekOff3(void);  
void SekOff4(void);  
void SekOff5(void);  
void SekOff6(void);  
void SekOff7(void);  
void SekOff8(void);  
void SekOff9(void);  
void SekOff10(void);  
void SekOff11(void);  
  
// CORDIC register definition
sfr16	CD_CORDX	=	0x9A;	   
sfr16	CD_CORDY	=	0x9C;	   
sfr16	CD_CORDZ	=	0x9E;
// MDU register definition
sfr16   MDU_Operand1 =  0xB2; 
sfr16   MDU_Operand2 =  0xB4;
sfr16   MDU_Operand3 =  0xB6;


extern char idata FLAG_Pin;
extern SlaveData sSlaveData;


pSekOn   SekOn[12]  = {
                       SekOn0, SekOn1, SekOn2,  SekOn3,     \
                       SekOn4, SekOn5, SekOn6,  SekOn7,     \
                       SekOn8, SekOn9, SekOn10, SekOn11
                      };
pSekOff  SekOff[12] = {
                       SekOff0, SekOff1, SekOff2,  SekOff3, \
                       SekOff4, SekOff5, SekOff6,  SekOff7, \
                       SekOff8, SekOff9, SekOff10, SekOff11
                      };

pBal BalancingFunction[4] = {BottomBalancing, TopBalancing, InterBlockTopBalancing, DummyBalancing};

void SekOn0(void)  
{ 
  SekOn_0(); 
}
void SekOn1(void)  
{ 
  SekOn_1(); 
}
void SekOn2(void)  
{ 
  SekOn_2(); 
}
void SekOn3(void)  
{ 
  SekOn_3(); 
}
void SekOn4(void)  
{ 
  SekOn_4(); 
}
void SekOn5(void)  
{ 
  SekOn_5(); 
}
void SekOn6(void)  
{ 
  SekOn_6(); 
}
void SekOn7(void)  
{ 
  SekOn_7(); 
}
void SekOn8(void)  
{ 
  SekOn_8(); 
}
void SekOn9(void)  
{ 
  SekOn_9(); 
}
void SekOn10(void)  
{ 
  SekOn_10();  
}
void SekOn11(void)  
{ 
  SekOn_11(); 
}

void SekOff0(void)  
{ 
  SekOff_0(); 
}
void SekOff1(void)  
{ 
  SekOff_1(); 
}
void SekOff2(void)  
{ 
  SekOff_2(); 
}
void SekOff3(void)  
{ 
  SekOff_3(); 
}
void SekOff4(void)  
{ 
  SekOff_4(); 
}
void SekOff5(void)  
{ 
  SekOff_5(); 
}
void SekOff6(void)  
{ 
  SekOff_6(); 
}
void SekOff7(void)  
{ 
  SekOff_7(); 
}
void SekOff8(void)  
{ 
  SekOff_8();
}
void SekOff9(void)  
{ 
  SekOff_9(); 
}
void SekOff10(void)  
{ 
  SekOff_10(); 
}
void SekOff11(void)  
{ 
  SekOff_11();
}


//GKvoid DeactivateSek(char SekNo)    
//GK{  
//GK  switch(SekNo)
//GK  {
//GK    case 0:  SekOff_0();  
//GK             break;
//GK   	case 1:  SekOff_1();  
//GK   	         break;
//GK    case 2:  SekOff_2();  
//GK             break;
//GK   	case 3:  SekOff_3();  
//GK   	         break;
//GK   	case 4:  SekOff_4();  
//GK   	         break;
//GK   	case 5:  SekOff_5();  
//GK   	         break;
//GK   	case 6:  SekOff_6();  
//GK   	         break;
//GK   	case 7:  SekOff_7();  
//GK   	         break;
//GK   	case 8:  SekOff_8();  
//GK   	         break;
//GK   	case 9:  SekOff_9(); 
//GK   	         break;
//GK   	case 10: SekOff_10(); 
//GK   	         break;
//GK   	case 11: SekOff_11(); 
//GK   	         break;
//GK	default: break;
//GK  }   
//GK}

unsigned int MDU_Convert_ADC( unsigned int ADC )
{
  unsigned int idata res_ac;
     
//  //--- Multiplication ---
//  SYSCON0 |= 0x01;				        // switch into mapped area   
//  MDU_Operand1 = (ADC * 40);		    // 5 * 2^3
//  MDU_Operand3 = sSlaveData.Ufac_u[FLAG_Pin]; // floatFactor * 2^15
//  MDU_MDUCON = 0x10;  				    // unsigned 16-bit Multiplication   
//  while((MDU_MDUSTAT & 0x04)== 0x04);	// Polling until MDU is ready	
//  res_ac = MDU_Operand2;				// high part
//  _nop_();
//  SYSCON0 &= 0xFE;
//  return (res_ac+Uoff_u);				// format Q4.12 => 1/4096
  
  //--- Multiplication ---
  SYSCON0 |= 0x01;				        // switch into mapped area   
  MDU_Operand1 = (ADC * 32);		    
  MDU_Operand3 = sSlaveData.Ufac_u[FLAG_Pin]; // floatFactor * 2^15
  MDU_MDUCON = 0x10;  				    // unsigned 16-bit Multiplication   
  while((MDU_MDUSTAT & 0x04)== 0x04);	// Polling until MDU is ready	
  res_ac = MDU_Operand2;				// high part

   printf(" Ucorr:%5.2fV \n",(float)res_ac/4096);
//added by XI


  _nop_();
  SYSCON0 &= 0xFE;
  return (res_ac+Uoff_u);				// format Q4.12 => 1/4096

}

//#ifdef SLAVE_BOARDS
//unsigned int MDU_Convert_ADC_rough( unsigned int ADC )
//{
//  unsigned int idata res_ac;
//     
//  //--- Multiplication ---
//  SYSCON0 |= 0x01;				        // switch into mapped area   
//  MDU_Operand1 = (ADC * 32);			// 2^5
//  MDU_Operand3 = 40960;    	            // 5 * 2^13
//  MDU_MDUCON = 0x10;  				    // unsigned 16-bit Multiplication   
//  while((MDU_MDUSTAT & 0x04)== 0x04);	// Polling until MDU is ready	
//  res_ac = MDU_Operand2;				// high part
//  SYSCON0 &= 0xFE;
//  return res_ac;						// format Q4.12
//}
//#endif

int MDU_Convert_ADC2Temp( unsigned int ADC )
{
  unsigned int idata res_ac;
    
  //--- Multiplication ---
  // T = (u-2,2517)/0,009551
  // T = (ADC/1024 *5 -2,251701)/0,009551
  // T = 104,7*(5/1024*ADC) - 236
  SYSCON0 |= 0x01;				        // switch into mapped area
  MDU_Operand1 = (40 * ADC);	     	// 5V   * 2^3
  MDU_Operand3 = 53606;	            	// 104,7* 2^9
  MDU_MDUCON = 0x10;  				    // unsigned 16-bit Multiplication
  while((MDU_MDUSTAT & 0x04)==  0x04);	// Polling until MDU is ready
  res_ac = MDU_Operand2;
  SYSCON0 &= 0xFE;  
  return (res_ac/64 - 236);		        // format Q10.6->Q16.0
}


unsigned int MDU_Convert_ADC2UBlock(unsigned int ADC)			  //In a loop 
{
  unsigned int idata res_ac;

  //--- Multiplication ---
  SYSCON0 |= 0x01;				        // switch into mapped area
  MDU_Operand1 = (40 * ADC);	     	// 5V * 2^3
  //MDU_Operand3 = 45056;	            // 11 * 2^12
  //MDU_Operand3 = 44835;	            // 10.946 * 2^12=	44834.82	  
  //MDU_Operand3 = sSlaveData.Ufac_u[Cells];


  //modified by Ningyi
  MDU_Operand3 = 44835;	            // 10.946 * 2^12=	44834.82	  
  //MDU_Operand3 = sSlaveData.Ufac_u[Cells];


   printf(" ADC=%d\n\n",(int)ADC);
//added by LIU

    //printf(" cal.fac. block: %.4f\n", (float)pSlaveData->Ufac_u[Cells]/Ublock_Grade);      
//	printf(" cal.fac. block.ADCconvert: %.4f\n", (float)pSlaveData->Ufac_u[Cells]/Ublock_Grade);						
//	printf(" cal.fac. block.ADCconvert: %.4f\n", (float)sSlaveData.Ufac_u[Cells]);											
	//cal.fac.block.ADCconvert: 65535.000	=2^16 				 
	
	printf(" cal.fac. block.ADCconvert: %.4f\n", (float)sSlaveData.Ufac_u[Cells]/Ublock_Grade);

	//added by XI    


  MDU_MDUCON = 0x10;  				    // unsigned 16-bit Multiplication
  while((MDU_MDUSTAT & 0x04)==  0x04);	// Polling until MDU is ready
  res_ac = MDU_Operand2;


printf(" res_ac=MDU_Operand2:%.4f\n", (float)MDU_Operand2);
//added by Ningyi


//printf(" res_ac/512:%5.3fV\n\n",  (float)res_ac/512); 		   //=0.00
//added by XI 


  SYSCON0 &= 0xFE;  
  return (res_ac/2);                    // format Q.9 -> Q.8
}

void GetAndSortAllCellVoltages(SlaveData *pSlaveData)
{			     
  unsigned int *pBalanceCell = &pSlaveData->BalanceCell_u[0];
  char    *pBalanceCellIndex = &pSlaveData->BalanceCellIndex[0];  
  unsigned int *pUmux        = &pSlaveData->Umux_u[0];
  char i;
  
  for(i=0; i<Cells; i++)												   
  {	
   	*pBalanceCell++ = *pUmux;															   
	*pBalanceCellIndex++ = i;
	pUmux++;
  }	
   
  // sort all voltages 
  SortAlgorithm_unsigned((unsigned int *)&pSlaveData->BalanceCell_u[0], &pSlaveData->BalanceCellIndex[0], Cells);

  #if defined (A123_BATTERY_10_CELLS)
  {
    char idata index;

    // search for the index of the lowest voltage cell
    for(i=(Cells-1); i>0; i--)
	{
	  // cell 5 & 6 are not connected and 0V
	  if( (pSlaveData->BalanceCellIndex[i]==Cell_5) || (pSlaveData->BalanceCellIndex[i]==Cell_6) )
	    continue;
	  else
	  { 
	    // lowest cell counting from the last up to the first cell
	    index =	i;
	    break; 
	  }
	}

    // save lowest cell index
    pSlaveData->LowestCellIndex = index;
  }
  #elif defined (MAXWELL_9_CELLS)
  {
    char idata index;

    // search for the index of the lowest voltage cell
    for(i=(Cells-1); i>0; i--)
	{
	  // cell 5 & 6 are not connected and 0V
	  if( (pSlaveData->BalanceCellIndex[i]==Cell_5) || (pSlaveData->BalanceCellIndex[i]==Cell_6) || (pSlaveData->BalanceCellIndex[i]==Cell_7))
	    continue;
	  else
	  { 
	    // lowest cell counting from the last up to the first cell
	    index =	i;
	    break; 
	  }
	}

    // save lowest cell index
    pSlaveData->LowestCellIndex = index;
  }
  #elif defined (LITEC_BATTERY_12_CELLS) || defined (PANASONIC_12_CELLS) || defined (MAXWELL_12_CELLS)
    // save lowest cell index
    pSlaveData->LowestCellIndex = Cells-1;
  #endif  																	

  // max-Voltage
  pSlaveData->Umax_u = pSlaveData->BalanceCell_u[0];
  // min-Voltage
  pSlaveData->Umin_u = pSlaveData->BalanceCell_u[pSlaveData->LowestCellIndex];
}

void SortAlgorithm_signed(int *pType, char *pIndex, char loop)
{
  char idata k, i, j, temp_index;
  int idata temp_type;
  
  k=1;

  for(i=0; i<loop-1; i++)									
  {															
    for(j=0; j<loop-k; j++)									
    {														
      if(*(pType+j+1) > *(pType+j)) 			
      { 													
  	    // sort diff voltage								
  	    temp_type = *(pType+j);						
        *(pType+j) = *(pType+j+1);			
        *(pType+j+1) = temp_type;						

        // sort diff voltage index							
  	    temp_index = *(pIndex+j);					
        *(pIndex+j) = *(pIndex+j+1);
        *(pIndex+j+1) = temp_index;					
      }														
    }														
    k++;													
  }	
}

void SortAlgorithm_unsigned(unsigned int *pType, char *pIndex, char loop)
{
  char idata k, i, j, temp_index;
  unsigned int idata temp_type;
  
  k=1;

  for(i=0; i<loop-1; i++)									
  {															
    for(j=0; j<loop-k; j++)									
    {														
      if(*(pType+j+1) > *(pType+j)) 			
      { 													
  	    // sort diff voltage								
  	    temp_type = *(pType+j);						
        *(pType+j) = *(pType+j+1);			
        *(pType+j+1) = temp_type;						

        // sort diff voltage index							
  	    temp_index = *(pIndex+j);					
        *(pIndex+j) = *(pIndex+j+1);
        *(pIndex+j+1) = temp_index;					
      }														
    }														
    k++;													
  }	
}

void GetAndSortTemperature(SlaveData *pSlaveData)
{
  // initialization	of Temp	0  
  pSlaveData->Temp[0] = pSlaveData->T_R5;	  pSlaveData->TempIndex[0] = 1; 
  // initialization	of Temp	1  
  pSlaveData->Temp[1] = pSlaveData->T_R6;	  pSlaveData->TempIndex[1] = 2; 
  // initialization	of Temp	2  				  
  pSlaveData->Temp[2] = pSlaveData->T_R7;  	  pSlaveData->TempIndex[2] = 3;  
  // initialization	of Temp	3
  pSlaveData->Temp[3] = pSlaveData->T_Rboard; pSlaveData->TempIndex[3] = 4;

  // sort signed all temperatures
  SortAlgorithm_signed((int *)&pSlaveData->Temp[0], &pSlaveData->TempIndex[0], TempSensors);

  // temp max
  pSlaveData->Tmax = pSlaveData->Temp[0];
  // temp min
  pSlaveData->Tmin = pSlaveData->Temp[TempSensors-1];  
}

// = In-BlockBalancing                                             
void TopBalancing(SlaveData *pSlaveData)
{
   char idata pause, CellNo;
  
   // disable Interrupts
   EA = 0;

   CellNo = pSlaveData->BalanceCellIndex[0];
//***********************************
//			  NEW
//***********************************
/*
   PrimH_Off();
   // switch port pin on
   SekOn[pSlaveData->BalanceCellIndex[0]]();
   // wait 
   TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
   // primH on
   PrimH_On();
   // delay
   DELAY_10();
   // deactivate sek
   SekOff[pSlaveData->BalanceCellIndex[0]]();
*/
   
  
   switch( CellNo )
   {
     case 0:  //PrimH_Off();
              // switch port pin on
              SekOn_0();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_0();
              break;

     case 1:  //PrimH_Off();
              // switch port pin on   	
              SekOn_1(); 
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_1();
    	      break;

     case 2:  //PrimH_Off();
              // switch port pin on   	
              SekOn_2();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_2();      
              break;

     case 3:  //PrimH_Off();
              // switch port pin on   	
              SekOn_3();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_3();   	  
    	      break;

     case 4:  //PrimH_Off();
              // switch port pin on   	
              SekOn_4();  
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_4();
    	      break;

     case 5:  //PrimH_Off();
              // switch port pin on   	
              SekOn_5();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_5();   	  
    	      break;

     case 6:  //PrimH_Off();
              // switch port pin on   	
              SekOn_6();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_6();   	  
    	      break;

    case 7:   //PrimH_Off();
              // switch port pin on   	
              SekOn_7();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_7();   	  
    	      break;

    case 8:   //PrimH_Off();
              // switch port pin on   	
              SekOn_8(); 
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_8();   	 
    	      break;

    case 9:   //PrimH_Off();
              // switch port pin on   	
              SekOn_9();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_9();   	 
    	      break;

    case 10:  // primH off
       	      //PrimH_Off();    
              // switch port pin on   	
              SekOn_10();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_10();   	 
    	      break;

    case 11:  // primH off
       	      //PrimH_Off();
              // switch port pin on   	
              SekOn_11();
              // wait 
              TTick(pause=0, pause<TopSekPulse, pause++, _nop_());
              // primH on
              PrimH_On();
			  // delay
			  DELAY_10();
       		  // deactivate sek
       		  SekOff_11();   	 
    	      break;
  	default: break;
   }

   // Prim On
   PrimOn();
   // wait 
   TTick(pause=0, pause<TopPrimPulse, pause++, _nop_());
 
PrimH_Off();

   // Prim Off
   PrimOff();

   // enable Interrupts
   EA = 1;
}
   
    
void InterBlockTopBalancing(SlaveData *pSlaveData)
{
   char idata pause;
  
   // disable Interrupts
   EA = 0;
   // primH permanent low
   PrimH_Off();

//***********************************
//			  NEW
//***********************************
/*
   // switch port pin on
   SekOn[pSlaveData->BalanceCellIndex[0]]();
   // wait
   TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
   // deactivate sek
   SekOff[pSlaveData->BalanceCellIndex[0]]();
*/      
   
   switch( pSlaveData->BalanceCellIndex[0] )
   {
     case 0:  // switch port pin on
              SekOn_0();
              // wait
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_0();
              break;

     case 1:  // switch port pin on   	
              SekOn_1(); 
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_1();
    	      break;

     case 2:  // switch port pin on   	
              SekOn_2();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_2();      
              break;

     case 3:  // switch port pin on   	
              SekOn_3();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_3();   	  
    	      break;

     case 4:  // switch port pin on   	
              SekOn_4();  
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_4();
    	      break;

     case 5:  // switch port pin on   	
              SekOn_5();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_5();   	  
    	      break;

     case 6:  // switch port pin on   	
              SekOn_6();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_6();   	  
    	      break;

    case 7:   // switch port pin on   	
              SekOn_7();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_7();   	  
    	      break;

    case 8:   // switch port pin on   	
              SekOn_8(); 
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_8();   	 
    	      break;

    case 9:   // switch port pin on   	
              SekOn_9();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_9();   	 
    	      break;

    case 10:  // switch port pin on   	
              SekOn_10();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_10();   	 
    	      break;

    case 11:  // switch port pin on   	
              SekOn_11();
              // wait 
              TTick(pause=0, pause<InterSekPulse, pause++, _nop_());
       		  // deactivate sek
       		  SekOff_11();   	 
    	      break;

  	default: break;
   }

   // Prim On
   PrimOn();   
   // wait
   TTick(pause=0, pause<InterPrimPulse, pause++, _nop_());
   // Prim Off
   PrimOff();   
   // enable Interrupts
   EA = 1;
}

void BottomBalancing(SlaveData *pSlaveData)
{
   char idata pause;
   
   // disable Interrupts
   EA = 0;
   
   // Prim On
   PrimH_On();   
   PrimOn();
   // wait
   TTick(pause=0, pause<BottomPrimPulse, pause++, _nop_());

//***********************************
//			  NEW
//***********************************
/*
   // Prin Off - Sek On    
   PrimOff();
   PrimH_Off();
   // activate sek
   SekOn[pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex]]();              
   // wait
   TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
   // deactivate sek
   SekOff[pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex]]();
*/

   switch( pSlaveData->BalanceCellIndex[pSlaveData->LowestCellIndex] )
   {
     case 0:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
              SekOn_0();              
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_0();
              break;

     case 1:  // Prin Off - Sek On                 
    	      PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_1();
              // wait 
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_1();
			
    	      break;

     case 2:  // Prin Off - Sek On                 
              PrimOff();
              PrimH_Off();
			  // activate sek
              SekOn_2();
              // wait 
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_2();
              
              break;

     case 3:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_3();
              // wait 
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_3();
 			                 	           
    	      break;

     case 4:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_4();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_4();                        
    	      
    	      break;

     case 5:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
    	      // activate sek
    	      SekOn_5();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_5();
    	      
    	      break;

     case 6:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_6();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_6();
			
    	      break;

     case 7:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
    	      // activate sek
    	      SekOn_7();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_7();
			
    	      break;

     case 8:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_8();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_8();
			
    	      break;

     case 9:  // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
    	      // activate sek
    	      SekOn_9();
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_9();
    	      
    	      break;

     case 10: // Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_10();             
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_10();
    	      
    	      break;

     case 11:// Prin Off - Sek On    
              PrimOff();
              PrimH_Off();
			  // activate sek
    	      SekOn_11();              
              // wait
              TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
 			  // deactivate sek
 			  SekOff_11();
    	      
    	      break;

 	 default: break;
   }   

   // enable Interrupts   
   EA = 1;
}

void DummyBalancing(SlaveData *pSlaveData)
{
   char idata pause;
   
   // disable Interrupts
   EA = 0;
   // dummy
   _nop_();   
   _nop_();
   // wait
   TTick(pause=0, pause<BottomPrimPulse, pause++, _nop_());
   // dummy    
   _nop_();   
   _nop_();
   // wait
   TTick(pause=0, pause<BottomSekPulse, pause++, _nop_());               
   // enable Interrupts   
   EA = 1;
}
