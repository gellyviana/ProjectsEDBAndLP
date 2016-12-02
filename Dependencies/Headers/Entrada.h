#ifndef __BUSCA_EM_ARQUIVOS_ENTRADA_H_
#define __BUSCA_EM_ARQUIVOS_ENTRADA_H_

#include <getopt.h>
#include "Auxiliares.h"
#include "../LinkedList.cpp"

const int MAX = 1000;
/**
	Estrutura que converte algumas opções quando recebida pelo usúario.
*/
const struct option longopts[] =
{
	{"i",      optional_argument,  0, 'i'}, 
	{"r",      optional_argument,  0,'r'},
	{"lI",     no_argument,  0, 'l'},
	{"lA",     no_argument,  0, 'm'},
	{"lT",     no_argument,  0, 's'},
	{"help",   no_argument,  0, 'h'},
	{"b",   required_argument,  0, 'b'},
	{"p",   required_argument,  0, 'p'},
	{"t",   required_argument,  0, 't'},
	{0,0,0,0},
};
/**
	Constantes do tipo inteiro para medir tempo de execução. 
*/
enum tpTempo{
	EXIBIR = 0,
	NAO_EXIBIR = 1
} ;

/**
	Constantes do tipo inteiro para opções de impressão.
*/
enum tpImpressao{
	IMP_ORDEM_ALFABETICA = 0,
	IMP_ORDEM_DECRESCENTE_N_OCORRENCIAS = 1,
	IMP_ORDEM_INSERCAO_ARQUIVO = 2
};

/**
	Classe que recebe como entrada as escolhas do usúario.
*/

class Entrada 
{
    private:
        int _iarg;
		int _argc; 
		int _index;
		int _opterr;
		char** _argv;
		Funcao _tipoFuncao;
		LinkedList<string>* _parametros;
		bool Verify(char, char);
		void ValidaParametros();
		void ValidaParametrosBusca();
		void ValidarArgumentos();
		void CarregaArgumentos();
		void ExibeAjuda();
		void MsgParamInvalido();
		void MSGParamObrigNaoInformado();
        
    public:
        Entrada();
		~Entrada();
		void ProcessarParametros(int n_argc, char* n_argv[]);
		void ProcessarParametrosBusca(int n_argc, char* n_argv[]);
		LinkedList<string> GetParametros();
		Funcao GetTipoFuncao();
};
#endif