#ifndef _TIMER_
#define _TIMER_

#include <stdio.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

 /**
     Classe utilizada para controlar as operações que utilizam medição de tempo.
 */    

class Timer
{
    private:
        struct timeval _inicio;
        struct timeval _fim;
        int _tempo; // Tempo em milissegundos
    public:
        Timer();
        ~Timer();
        void Start();
        void Stop();
        int GetTime();
        int GetTimePrint();
};
#endif