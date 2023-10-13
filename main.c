#include <stdio.h>
#include <time.h>
#include "main.h"

// #define SIMPLE

#define LOG(x) fprintf(loggerFile,"%d\n", (x))
#define LOG2(x,y) fprintf(loggerFile,"%llu\t%d\n",(x), (y))

FILE* loggerFile;


void taskA();
int runAndLog(void (*ptrTask)(void));
uint16 filter(uint16 x);
uint16 increaseBitDepth(uint16 in);


int main(void)
{
    runAndLog(&taskA);
    return 0;
}

int runAndLog(void (*ptrTask)())
{
        // SETUP LOGGER
    loggerFile = fopen("log.txt", "a+");
    if (loggerFile == NULL){return -1;}

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    fprintf(loggerFile, "        %s", asctime (timeinfo));
    fprintf(loggerFile, "==================START==================\n\n");
    fprintf(loggerFile, "=======PARAMS:\n");
    fprintf(loggerFile, "K = %d\t 1/(2^K) = %.4f\n\n", FILT.K, (float)(1.0/(1 << FILT.K)));

    // call function pointer
    ptrTask();

    fprintf(loggerFile, "===================END===================\n\n\n\n\n");

    return 0;
}

void taskA()
{
    fprintf(loggerFile,"i\tstate1\tout\tstate2\tfilteredInput\n");
    for (size_t i = 0; i < 200; i++)
    {

        fprintf(loggerFile,"%zu\t", i);
        filter(100);


        // LOG2(i, filter(200);
    }
        // fprintf(loggerFile,"down\n");

    // for (size_t i = 0; i < 300; i++)
    // {

    //     fprintf(loggerFile,"%zu\t", i);
    //     filter(1);


    //     // LOG2(i, filter(200);
    // }

}

uint16 filter(uint16 x)
{
#ifdef SIMPLE
    sensor.filteredInput = (0.03 * x) + (0.97 * sensor.filteredInput);
    fprintf(loggerFile,"%d\n",sensor.filteredInput);
    return (sensor.filteredInput);

#else

    FILT.state    += increaseBitDepth(x);                                   fprintf(loggerFile,"%d\t",FILT.state);
    // FILT.state    += x;                                   fprintf(loggerFile,"%d\t",FILT.state);
    FILT.out       = (FILT.state + (1 << (FILT.K-1))) >> FILT.K;            fprintf(loggerFile,"%d\t",FILT.out);
    // FILT.out       = (FILT.state ) >> FILT.K;            fprintf(loggerFile,"%d\t",FILT.out);
    FILT.state    -= FILT.out;                                              fprintf(loggerFile,"%d\t",FILT.state);
    sensor.filteredInput = FILT.out >> 5;                                   fprintf(loggerFile,"%d\n",FILT.out >> 5);
    return (sensor.filteredInput);
#endif



}

uint16 increaseBitDepth(uint16 in)
{

  uint8 Bits_out = 15; // ADC_BITS + IncRes
  uint8 Bits_in = 10; //10

  size_t leftShift = Bits_out - Bits_in;
  size_t rightShift = Bits_in - leftShift;
  uint16 ret = ((in << leftShift) | (in >> rightShift));

  return (ret > ((1 << Bits_out) - 1)) ? ((1 << Bits_out) - 1) : ret ;
}