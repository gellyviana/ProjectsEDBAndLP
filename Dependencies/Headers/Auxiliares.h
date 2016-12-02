#ifndef _FUNCOES_AUXILIARES_
#define _FUNCOES_AUXILIARES_

#include "../LinkedList.cpp"

/**
	Estrutura para tratamento do tipo da função.
*/
typedef enum tpFuncao{
	FUNC_INSERIR = 1,
	FUNC_REMOVER = 2,
	FUNC_LISTAR = 3,
	FUNC_LISTAR_ORDEM_ALFABETICA = 4,
	FUNC_LISTAR_ORDEM_QTD_PALAVRAS = 5,
	FUNC_BUSCAR = 6,
	FUNC_HELP = 7,
	FUNC_PARAM_INVALIDO = 8,
	FUNC_ARQUIVO_JA_EXISTE = 9,
	FUNC_ARQUIVO_N_EXISTE = 10,
	FUNC_AND = 11,
	FUNC_OR = 12
} Funcao;

/**
	Classe com métodos auxiliares.
*/
class Auxiliares
{
	public:
		
		static LinkedList<string> Split(const char* delimitador, string texto);
		static string RemoverCaracteresEspeciais(string texto);
		static string ToLowerCase(string texto);
};
#endif