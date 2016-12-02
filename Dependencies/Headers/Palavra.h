#ifndef _PALAVRA_
#define _PALAVRA_

#include "../Serializable.cpp"
#include <iostream>

using namespace std;

/**
     Classe responsável em trabalhar com a palavra e herda da classe Serializable.
*/
class Palavra : public Serializable
{
    private:
        string texto;
        int idLinha;
        int idArquivo;

    public:
        Palavra(int idLinha, int idArquivo);
        ~Palavra();

        string GetTexto();
        void SetTexto(string value);

        int GetIdLinha();
        int GetIdArquivo();
        virtual string Serialize();
		virtual void Deserialize(string dados);
};

#endif