#ifndef _LINHA_
#define _LINHA_

#include "../LinkedList.cpp"
#include "../Serializable.cpp"
#include "../Headers/Palavra.h"
using namespace std;

/**
    Classe que herda de Serializable e responsável em trabalhar com arquivo e transformando nas linhas.
*/
class Linha : public Serializable
{
    private:
    int idLinha;
    int idArquivo;
    LinkedList<Palavra>* palavras;

    public:
        Linha(int idLinha, int idArquivo);
        ~Linha();

        int GetIdLinha();
        int GetIdArquivo();
        LinkedList<Palavra>* GetPalavras();
        virtual string Serialize();
		virtual void Deserialize(string dados);
};

#endif