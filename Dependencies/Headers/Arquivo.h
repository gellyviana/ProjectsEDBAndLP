#ifndef _ARQUIVO_
#define _ARQUIVO_

#include "../LinkedList.cpp"
#include "../Serializable.cpp"
#include "Linha.h"
#include "Auxiliares.h"
#include <iostream>

using namespace std;

/**
	Classe que herda de Serializable e trabalha especificamente com os arquivos.
*/
class Arquivo : public Serializable
{
	private:
		int idArquivo;
		LinkedList<Linha>* linhas;

	public:
		string caminho;
		string nome;

		Arquivo(int idArquivo);
		~Arquivo();

		int GetIdArquivo();
		LinkedList<Linha>* GetLinhas();
		virtual string Serialize();
		virtual void Deserialize(string dados);
};

#endif