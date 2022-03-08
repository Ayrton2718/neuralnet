//
//  main.c
//  neuralNetwork
//
//  Created by matsushita sena on 2019/06/15.
//  Copyright © 2019年 matsushita sena. All rights reserved.
//

#include <string.h>
#include "NN_Nerve.h"
#include "SC_Random.h"
#include "math.h"
#include "time.h"

//---------------------------------------
float reru(float val)
{
	if ((float)0 <= val)
	{
		return (float)val;
	}
	else {
		return (float)0;
	}
}

float d_reru(float val)
{
	if ((float)0 <= val)
	{
		return (float)1.0;
	}
	else {
		return (float)0.0;
	}
}


static unsigned long coef1, coef2, coef3, bias;
float AiFunc(float x1, float x2, float x3)
{
	return (float)(x1*((float)coef1*0.1) + x2*((float)coef2*0.1) + x3*((float)coef3*0.1) + ((float)bias*0.1));
}

unsigned long AiFuncToUserFunc(float output)
{
	return lroundf((output * 1000 - (float)bias * 99));
}

unsigned long userfunc(unsigned long x1, unsigned long x2, unsigned long x3)
{
	return x1*coef1 + x2*coef2 + x3*coef3 + bias;
}

int main(int argc, const char * argv[])
{
	unsigned int randSeed = (unsigned int)time(NULL);
	//    printf( "%d\n", randSeed );
    SC_RandomSetSeed(randSeed);

	NN_Object neauralNet = NN_NerveAllocInit( 3, 3);
	NN_NerveAppendLayer(neauralNet, 32, reru, d_reru);
	NN_NerveAppendLayer(neauralNet, 8, reru, d_reru);
	NN_NerveAppendLayer(neauralNet, 1, reru, d_reru);

	srand(randSeed);

	coef1 = rand() % 10;
	coef2 = rand() % 10;
	coef3 = rand() % 10;
	bias = rand() % 10;

	unsigned long x1, x2, x3, y;

	NN_Var input[3];
	NN_Var teacher[1];
	NN_Var output[1];
	NN_Var LRate = (NN_Var)0.1;

	// signed long startTime, nowTime, AITime, userTime;

	printf("AILeaning");

	size_t counter = 0, dotCount = 0;
	for (size_t i = 0; i<1000000; i++)
	{
		x1 = rand() % 100;
		x2 = rand() % 100;
		x3 = rand() % 100;
		input[0] = (float)x1*(float)0.01;
		input[1] = (float)x2*(float)0.01;
		input[2] = (float)x3*(float)0.01;

		teacher[0] = AiFunc(input[0], input[1], input[2]);
		y = userfunc(x1, x2, x3);

		NN_NerveRun(neauralNet, input, output);
		if (y == AiFuncToUserFunc(output[0]))
		{
			counter++;
			if (dotCount < counter)
			{
				dotCount++;
				LRate *= (NN_Var)0.97;
				printf(".");
			}
			if (50 < counter)
			{
				printf("Finish!!\n");
				break;
			}
		}
		else {
			counter = 0;
		}

		NN_NerveLearn(neauralNet, teacher, LRate);

		// while ( true )
		// {
		// 	QueryPerformanceFrequency(&freq_pc);
		// 	QueryPerformanceCounter(&now_pc);
		// 	nowTime = (signed long)((now_pc.QuadPart / (double)freq_pc.QuadPart) * 1000);
		// 	if ( 5 < (nowTime-waitStartTime) )
		// 	{
		// 		break;
		// 	}
		// }
	}


	// for (size_t i = 0; i<10; i++)
	// {
	// 	x1 = rand() % 100;
	// 	x2 = rand() % 100;
	// 	x3 = rand() % 100;
	// 	y = userfunc(x1, x2, x3);
	// 	printf("f(%ld, %ld, %ld)=%ld\n", x1, x2, x3, y);
	// }

	// x1 = rand() % 100;
	// x2 = rand() % 100;
	// x3 = rand() % 100;
	// y = userfunc(x1, x2, x3);
	// printf("user answer wait 2 min\n");
	// startTime = (signed long)((now_pc.QuadPart / (double)freq_pc.QuadPart) * 1000);

	// for (size_t i = 0; i<3; i++)
	// {
	// 	unsigned long userInput;
	// 	printf("f(%ld, %ld, %ld)=", x1, x2, x3);

	// 	/*QueryPerformanceFrequency(&freq_pc);
	// 	QueryPerformanceCounter(&now_pc);
	// 	size_t answerTime = (size_t)((now_pc.QuadPart / (double)freq_pc.QuadPart) * 1000);*/
	// 	// bool successFlg = false;
	// 	// for ( unsigned long i = 0; i<6400*2; i++ )
	// 	// {
	// 	// 	if (kbhit())
	// 	// 	{
	// 	// 		successFlg = true;
	// 	// 		break;
	// 	// 	}
			
	// 	// 	Sleep(1);
	// 	// }

	// 	if ( successFlg == false )
	// 	{
	// 		printf("\ngame over\n");
	// 		break;
	// 	}

	// 	scanf_s("%ld", &userInput);
	// 	if (y == userInput)
	// 	{
	// 		printf("userFinish!!\n");
	// 		QueryPerformanceFrequency(&freq_pc);
	// 		QueryPerformanceCounter(&now_pc);
	// 		nowTime = (signed long)((now_pc.QuadPart / (double)freq_pc.QuadPart) * 1000);
	// 		userTime = nowTime - startTime;
	// 		break;
	// 	}else {
	// 		if (i != 2)
	// 		{
	// 			printf("one more\n");
	// 		}
	// 		else {
	// 			printf("give up\n");
	// 			userTime = 10000000;
	// 			break;
	// 		}
	// 	}
	// }

	for (size_t i = 0; i<10; i++)
	{
		x1 = rand() % 100;
		x2 = rand() % 100;
		x3 = rand() % 100;
		input[0] = (float)x1*(float)0.01;
		input[1] = (float)x2*(float)0.01;
		input[2] = (float)x3*(float)0.01;
		teacher[0] = AiFunc(input[0], input[1], input[2]);
		y = userfunc(x1, x2, x3);
		NN_NerveRun(neauralNet, input, output);
		printf("f(%ld, %ld, %ld)=%ld\tAI=%ld\n", x1, x2, x3, y, AiFuncToUserFunc( output[0] ));
	}

	// printf("f(x1, x2, x3)=%ld*x1+%ld*x2+%ld*x3+%ld\n", coef1, coef2, coef3, bias);

	// if ( userTime < AITime )
	// {
	// 	printf("user win\n");
	// }
	// else {
	// 	printf("AI win\n");
	// }

	// if (userTime == 10000000)
	// {
	// 	printf("AITime--%ld, userTime--game over\n", AITime);
	// }else {
	// 	printf("AITime--%ld, userTime--%ld\n", AITime, userTime);
	// }

	// NN_NerveDtor(neauralNet);

	return 0;
}
