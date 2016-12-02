#include "../Headers/Linha.h"

using namespace std;

Linha::Linha(int idLinha, int idArquivo)
{
    // Construtor
    this->idLinha = idLinha;
    this->idArquivo = idArquivo;
    this->palavras = new LinkedList<Palavra>();
}

Linha::~Linha()
{
    // Destrutor
    delete this->palavras;
}

/**
    Método que retorna uma identidade unica de cada Linha.
    @param - Não possui parametro.
    @return - Retorna um inteiro.
*/
int Linha::GetIdLinha()
{
    return this->idLinha;
}

/**
    Método que retorna uma identidade unica para cada arquivo.
    @param - Não possui parametro.
    @return - Retorna um inteiro.
*/
int Linha::GetIdArquivo()
{
    return this->idArquivo;
}

/**
    Método que retorna a palavra, passando para um lista.
    @param - Não possui parametro.
    @return - Retorna um ponteiro para uma lista.
*/
LinkedList<Palavra>* Linha::GetPalavras()
{
    return this->palavras;
}

string Linha::Serialize()
{
    cout << "A função SERIALIZE não foi implementada  na classe Linha" << endl;
	return NULL;
}

void Linha::Deserialize(string texto)
{
    cout << "A função DESERIALIZE não foi implementada na classe Linha" << endl;
}