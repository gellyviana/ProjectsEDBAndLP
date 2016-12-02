#include "../Headers/Palavra.h"

using namespace std;

Palavra::Palavra(int idLinha, int idArquivo)
{
    //Construtor
    this->idLinha = idLinha;
    this->idArquivo = idArquivo;
}

Palavra::~Palavra()
{
    //Destrutor
}

/**
    Método que retorna uma string.
    @param - Não possui parametro.
    @return - Retorna uma string.
*/
string Palavra::GetTexto()
{
    return this->texto;
}

/**
    Método que pega uma string.
    @param - Uma string.
    @return - Não possui retorno.
*/
void Palavra::SetTexto(string value)
{
    this->texto = value;
}
/**
    Método que retorna uma identidade unica para cada linha.
    @param - Não possui parametro.
    @return - Retorna um inteiro.
*/
int Palavra::GetIdLinha()
{
    return this->idLinha;
}

/**
    Método que retorna uma identidade unica para cada arquivo.
    @param - Não possui parametro.
    @return - Retorna um inteiro.
*/
int Palavra::GetIdArquivo()
{
    return this->idArquivo;
}

string Palavra::Serialize()
{
    cout << "A função SERIALIZE não foi implementada  na classe Palavra" << endl;
	return NULL;
}

void Palavra::Deserialize(string texto)
{
    cout << "A função DESERIALIZE não foi implementada na classe Palavra" << endl;
}