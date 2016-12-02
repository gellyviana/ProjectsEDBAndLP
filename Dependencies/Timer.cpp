#include "Headers/Timer.h"
#include <iomanip>
using namespace std;

Timer::Timer()
{
    // Construtor
    this->_tempo = 0;
}

Timer::~Timer()
{
    // Destrutor da classe
}

/**
    Método que pega o tempo inicial da execução do programa.
*/
void Timer::Start()
{
    gettimeofday(&this->_inicio, NULL);
}

/**
    Método que pega o tempo final apos o termino da execução do programa.
*/
void Timer::Stop()
{
    gettimeofday(&this->_fim, NULL);
}

/**
    Método que retorna o tempo de execução apos o calculo feito.
    @param - Não possui parametro.
    @return - Retorna um inteiro.
*/
int Timer::GetTime()
{
    this->_tempo = (int) (1000 * (this->_fim.tv_sec - this->_inicio.tv_sec) + (this->_fim.tv_usec - this->_inicio.tv_usec) );
    return this->_tempo;
}

/**
    Método imprime o tempo decorrido entre o inicio e fim da contagem.
    @param - Não possui parametro.
    @return -  Retorna um inteiro.
*/
int Timer::GetTimePrint()

{
    double segundos =  this->GetTime()/1000.0;//Converte para double.
    cout << "\t >> tempo de execução " << setprecision(7) << segundos << " segundos" << endl;//Imprime com 7 casas de precisão. 
    return this->_tempo;
}