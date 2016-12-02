#include "../LinkedList.cpp"
#include "../Headers/Arquivo.h"
#include "../Headers/Linha.h"
#include <iostream>
#include <sstream>

using namespace std;

Arquivo::Arquivo(int idArquivo)
{	
	//Contrutor
	this->idArquivo = idArquivo;
	this->linhas = new LinkedList<Linha>();
}

Arquivo::~Arquivo()
{
	//Destrutor 
	delete this->linhas;
}

/**
	Método que retorna um inteiro diretamente ligado ao arquivo que esta sendo trabalhado.
	@param - Não passui parametro.
	@return - Retorno o número que representa o arquivo.
*/
int Arquivo::GetIdArquivo()
{
    return this->idArquivo;
}

/**
	Método pega as linhas dos arquivos.
	@param - Não possui parametro.
	@return - Retorna o endereço para uma lista duplamente encadeada contendo as linhas. 
*/
LinkedList<Linha>* Arquivo::GetLinhas()
{
    return this->linhas;
}

/**
	Método que coloca um papiline entre o nome do arquivo e o seu caminho.
	@param - Não possui parametro.
	@return - Retorna uma string.
*/
string Arquivo::Serialize()
{
	stringstream stream;
	stream << this->nome << "|" << this->caminho;
	return stream.str();
}

/**
	Método que retira um delimitador especifico.
	@param - String que contém o texto.
	@return - Não possui retorno.
*/
void Arquivo::Deserialize(string texto)
{
	LinkedList<string> dados = Auxiliares::Split("|", texto);// Retorna somente a lista com as palavras.
	if(dados.GetTamanho() != 2)
	{
		cout << dados.GetTamanho() << endl;
		for(int i=0; i < dados.GetTamanho() ; i++)
		{
			cout << *dados.GetElementAtIndex(i) << endl;
		}
		
		cout << "Não foi possível Deserializar o arquivo, os dados são inválidos" << endl;
		return;
	}

	this->nome = *dados.GetElementAtIndex(0);
	this->caminho = *dados.GetElementAtIndex(1);
}