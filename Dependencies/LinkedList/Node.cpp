#ifndef _GENERIC_NODE_
#define _GENERIC_NODE_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

/**
 Classe responsável pela armazenagem de valores de qualquer tipo.
 */
template <class T>
class Node
{
    private:
        void InicializarDados(T* valor = NULL)
        {
            //Construtor
            this->proximo = NULL;
            this->anterior = NULL;
            this->valor = valor;
        }

    public:
        T* valor;
        Node<T>* proximo;
        Node<T>* anterior;

        Node<T>()
		{
            this->InicializarDados();
		}

        Node<T>(T* valor)
		{
            this->InicializarDados(valor);
		}

        Node<T>(T valor)
		{
            this->InicializarDados(new T(valor));
		}

		~Node<T>()
		{
			// Destrutor da classe
		}
};
#endif