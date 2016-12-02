#include "Headers/Auxiliares.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <locale>
#include <regex>

using namespace std;

/**
	Realiza a separação de uma string de acordo com o delimitador especificado.
	@param - char - delimitador.
	@param - string - texto a ser separado.
	@return -  LinkedList<string> - List com os valores separados.
*/
LinkedList<string> Auxiliares::Split(const char* delimitador, string texto)
{	 
	if (!texto.empty() && (texto[texto.size() - 1] == '\r' || texto[texto.size() - 1] == '\n'))
	{
		texto.erase(texto.size() - 1);
	}

	char* valorChar = strdup(texto.c_str());//Strdup é uma função que aloca diretamente um string.
	char* valorSplited = strtok(valorChar, delimitador);
    
	LinkedList<string>* valores = new LinkedList<string>();
	while(valorSplited != NULL)
	{
		valores->Inserir(valorSplited);// Inseri juntamente com o delimitador.
		valorSplited = strtok(NULL, delimitador);
	}

	return *valores;
}

/**
	Método que Retorna uma string sem os "lixos" como: ,./_
	@param Recebe um string que contêm o texto para ser limpo.
	@return Retorna o texto sem os lixos.
*/
string Auxiliares::RemoverCaracteresEspeciais(string texto)
{
    regex patern("[^0-9a-zA-Z- áàâãéèêíïóôõöúçñÁÀÂÃÉÈÍÏÓÔÕÖÚÇÑ]+");
    texto = regex_replace(texto, patern, "");
	return texto;
}

/**
	Transforma todas as letras do texto em minusculo
	@param - string - texto a ser tratado.
	@return - string - Texto utilizado o lowercase.
*/
string Auxiliares::ToLowerCase(string texto)
{
	stringstream stream;	
	locale loc;
	for (string::size_type i=0; i < texto.length(); ++i)
	{
		stream << tolower(texto[i], loc); 
	}

	return stream.str();
}
