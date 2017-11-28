/*************************************************************************
* lab6 Klos                                           *
**************************************************************************/


#include <stdio.h>
#include <io.h>
#include <system.h>
#include "includes.h"
#include "definition.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];	// odczyt il. osob + pok0
OS_STK    task2_stk[TASK_STACKSIZE];	// zmiana stanu p1
OS_STK    task3_stk[TASK_STACKSIZE];	// zmiana stanu p2
OS_STK    task4_stk[TASK_STACKSIZE];	// zmiana stanu p3
OS_STK    task5_stk[TASK_STACKSIZE];	// zmiana stanu p4 + pErr

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      3
#define TASK4_PRIORITY      4
#define TASK5_PRIORITY      5

typedef enum POZIOM_TEMP{
POZIOM_0 = 0,
POZIOM_1 = 2,
POZIOM_2 = 4,
POZIOM_3 = 8,
POZIOM_4 = 16,
POZIOM_5 = 32,
POZIOM_6 = 64,
POZIOM_7 = 128,
POZIOM_8 = 256,
POZIOM_9 = 512,
POZIOM_10 = 1024,

}TEMP;

OS_EVENT *SWBoxS;

struct data {
    volatile int p0;
    volatile int p1;
    volatile int p2;
    volatile int p3;
    volatile int p4;
    volatile int pErr;
};

void changeHex(int hexNum, int value){
//------------------- HEXY
	int display = 0;

	if(hexNum == 5){	// ERROR HEX
		if(value == 1)
			IOWR(HEX_BASE,5,_ERROR_E);
		else
			IOWR(HEX_BASE,5,_MINUS);
	}
	else{
		switch(value){
		case 0:
			display = _ZERO;
			break;
		case 1:
			display = _ONE;
			break;
		case 2:
			display = _TWO;
			break;
		case 3:
			display = _THREE;
			break;
		case 4:
			display = _FOUR;
			break;
		case 5:
			display = _FIVE;
			break;
		case 6:
			display = _SIX;
			break;
		case 7:
			display = _SEVEN;
			break;
		case 8:
			display = _EIGHT;
			break;
		case 9:
			display = _NINE;
			break;
		default:
			display = _MINUS;	// jezeli >9 to wyswietla -
			break;

		}

		IOWR(HEX_BASE,hexNum,display);
	}
}

void changeLed(int ledNum, int value){
//------------------- LEDY
	int leds = 0;
	int ledChange = ledNum;

	switch(ledChange){
	  case 0:
		  ledChange = _LED0;
		  break;
	  case 1:
		  ledChange = _LED1;
		  break;
	  case 2:
		  ledChange = _LED2;
		  break;
	  case 3:
		  ledChange = _LED3;
		  break;
	  case 4:
		  ledChange = _LED4;
		  break;
	  case 5:
		  ledChange = _LED9; // error
		  break;
	  default:
		//  printf("Unknow LED! \n");
		  break;
	}

	leds = IORD(LEDS_BASE, 0x0);

	if(value > 0){	// LED ON
	//	printf("LedOn %d!\n", ledNum);
		leds = leds | ledChange;
	}
	else if(value == 0){// LED OFF
	//	printf("LedOff %d!\n", ledNum);
		ledChange = ~ledChange;
		leds = leds & ledChange;
	}

	IOWR(LEDS_BASE,0,leds);

}

/* Odczyt ilosci osob */
void task1(void* pdata)
{
	int sw;
	int S[5] = {0};
	int errFlag = 0;
	short state = 0;
	int swFlag[10] = {0};
	int i;

	struct data data1;

	while (1)
	{
		// odczyt pokoi

		if(IORD(PUSHBUTTON_BASE, 0) == 14){
			state = 0;	// wychodzenie
		}
		else
			state = 1;	// wchodzenie

		sw = IORD(SW_SLIDERS_BASE, 0);

		switch (sw) {
			case 0:
				for(i = 0; i < 10; i++){
					swFlag[i] = 0;
				}
				if(errFlag)
					errFlag = 0;
				break;
			case 1:
				if(swFlag[0] == 0){
					 printf("Drzwi 1\n");
					 if(state){
						 S[4]++;

					 }
					 else if(S[4]<1){
						 errFlag = 1;
						 printf("Error Drzwi 1\n");
					 }
					 else
						 S[4]--;
					 swFlag[0] = 1;

				}
				 break;
			case 2:
				if(swFlag[1] == 0){
					 printf("Drzwi 2\n");
					 if(state){
						 S[0]++;

					 }
					 else if(S[0] < 1){
						 errFlag = 1;
						 printf("Error Drzwi 2\n");
					 }
					 else
						 S[0]--;
					 swFlag[1] = 1;

				}
				 break;
			case 4:
				if(swFlag[2] == 0){
					 printf("Drzwi 3\n");
					 if(state){
						 S[2]++;

					 }
					 else if(S[2] < 1){
						 errFlag = 1;
						 printf("Error Drzwi 3\n");
					 }
					 else
						 S[2]--;
					 swFlag[2] = 1;

				}
				 break;
			case 8:
				if(swFlag[3] == 0){
					 printf("Drzwi 4\n");
					 if(state){	// s0 -> s2
						 if(S[0] < 1){
							errFlag = 1;
							printf("Error Drzwi 4\n");
						 }
						 else{
							 S[0]--;
							 S[2]++;

						 }
					 }
					 else{	//s2 -> s0
						 if(S[2] < 1){
							errFlag = 1;
							printf("Error Drzwi 4\n");
						 }
						 else{
							 S[2]--;
							 S[0]++;

						 }
					 }
					 swFlag[3] = 1;

				}
				 break;
			case 16:
				if(swFlag[4] == 0){
				 printf("Drzwi 5\n");
					 if(state){	// s0 -> s4
						 if(S[0] < 1){
							errFlag = 1;
							printf("Error Drzwi 5\n");
						 }
						 else{
							 S[0]--;
							 S[4]++;

						 }
					 }
					 else{	//s4 -> s0
						 if(S[4] < 1){
							errFlag = 1;
							printf("Error Drzwi 5\n");
						 }
						 else{
							 S[4]--;
							 S[0]++;

						 }
					 }
					 swFlag[4] = 1;

				}
				 break;
			case 32:
				if(swFlag[5] == 0){
					 printf("Drzwi 6\n");
					 if(state){	// s3 -> s4
						 if(S[3] < 1){
							errFlag = 1;
							printf("Error Drzwi 6\n");
						 }
						 else{
							 S[3]--;
							 S[4]++;

						 }
					 }
					 else{	//s4 -> s3
						 if(S[4] < 1){
							errFlag = 1;
							printf("Error Drzwi 6\n");
						 }
						 else{
							 S[4]--;
							 S[3]++;

						 }
					 }
					 swFlag[5] = 1;

				}
				 break;
			case 64:
				if(swFlag[6] == 0){
					 printf("Drzwi 7\n");
					 if(state){
						 S[3]++;

					 }
					 else if(S[3] < 1){
						 errFlag = 1;
						 printf("Error Drzwi 7\n");
					 }
					 else
						 S[3]--;
					 swFlag[6] = 1;

				}
				 break;
			case 128:
				if(swFlag[7] == 0){
					 printf("Drzwi 8\n");
					 if(state){
						 S[1]++;

					 }
					 else if(S[1] < 1){
						 errFlag = 1;
						 printf("Error Drzwi 8\n");
					 }
					 else
						 S[1]--;
					 swFlag[7] = 1;

				}
				 break;
			case 256:
				if(swFlag[8] == 0){
					 printf("Drzwi 9\n");
					 if(state){
						 S[1]++;

					 }
					 else if(S[1] < 1){
						 errFlag = 1;
						 printf("Error Drzwi 9\n");
					 }
					 else
						 S[1]--;
					 swFlag[8] = 1;

				}
				 break;
			case 512:
				if(swFlag[9] == 0){
					 printf("Drzwi 10\n");
					 if(state){	// s1-> s3
						 if(S[1] < 1){
							errFlag = 1;
							printf("Error Drzwi 10\n");
						 }
						 else{
							 S[1]--;
							 S[3]++;

						 }
					 }
					 else{	//s3 -> s1
						 if(S[3] < 1){
							errFlag = 1;
							printf("Error Drzwi 10\n");
						 }
						 else{
							 S[3]--;
							 S[1]++;
						 }
					 }
					 swFlag[9] = 1;

				}
				 break;

			default:
				//printf("Error 2 slidery wlaczone");
				errFlag = 1;
				break;
		}


		// wyslij wartosci pokoi
		// OS_POST_OPT_NONE or broadcast - none tylko do 1
		data1.p0 = S[0];
		data1.p1 = S[1];
		data1.p2 = S[2];
		data1.p3 = S[3];
		data1.p4 = S[4];
		data1.pErr = errFlag;
		OSMboxPostOpt(SWBoxS, &data1, OS_POST_OPT_BROADCAST);

		/* Pok0 */
		changeLed(0,data1.p0);
		changeHex(0,data1.p0);

		// Sleep -> Hours, Minutes, Seconds, Miliseconds
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}

/* Pok1 */
void task2(void* pdata)
{
	INT8U err0;
	struct data *Pok;
	while (1)
	{	// odczyt
		Pok = OSMboxPend(SWBoxS, 0, &err0);

		changeLed(1,Pok->p1);
		changeHex(1,Pok->p1);

		// DELAY
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}
/* Pok2 */
void task3(void* pdata)
{
	INT8U err0;
	struct data *Pok;
	while (1)
	{	// odczyt
		Pok = OSMboxPend(SWBoxS, 0, &err0);

		changeLed(2,Pok->p2);
		changeHex(2,Pok->p2);

		// DELAY
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}
/* Pok3 */
void task4(void* pdata)
{
	INT8U err0;
	struct data *Pok;
	while (1)
	{	// odczyt
		Pok = OSMboxPend(SWBoxS, 0, &err0);

		changeLed(3,Pok->p3);
		changeHex(3,Pok->p3);

		// DELAY
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}
/* Pok4 + Error */
void task5(void* pdata)
{
	INT8U err0;
	struct data *Pok;
	while (1)
	{	// odczyt
		Pok = OSMboxPend(SWBoxS, 0, &err0);

		changeLed(4,Pok->p4);
		changeHex(4,Pok->p4);

		changeLed(5,Pok->pErr);
		changeHex(5,Pok->pErr);

		// DELAY
		OSTimeDlyHMSM(0, 0, 0, 300);
	}
}

/* The main function creates two task and starts multi-tasking */
int main(void)
{
    int k = 0;
    for(k = 0; k <= 6; k++){
        IOWR(HEX_BASE, k, SEGG);
    }
    IOWR(LEDS_BASE,0,0x0);

    SWBoxS = OSMboxCreate((void*)0);

  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
              
               
  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSTaskCreateExt(task3,
                  NULL,
                  (void *)&task3_stk[TASK_STACKSIZE-1],
                  TASK3_PRIORITY,
                  TASK3_PRIORITY,
                  task3_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task4,
                  NULL,
                  (void *)&task4_stk[TASK_STACKSIZE-1],
                  TASK4_PRIORITY,
                  TASK4_PRIORITY,
                  task4_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSTaskCreateExt(task5,
                  NULL,
                  (void *)&task5_stk[TASK_STACKSIZE-1],
                  TASK5_PRIORITY,
                  TASK5_PRIORITY,
                  task5_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSStart();
  return 0;
}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
