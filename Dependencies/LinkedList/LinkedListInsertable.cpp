#ifndef _GENERIC_LINKED_LIST_INSERTABLE_
#define _GENERIC_LINKED_LIST_INSERTABLE_

#include "LinkedListBase.cpp"

using namespace std;

/**
	Classe que herda LinkedListBase, com alguns métodos especificos.
*/
template <class T>
class LinkedListInsertable : public LinkedListBase<T>
{
    public:
		LinkedListInsertable<T>()
		{
			/// Construtor da classe
		}

		~LinkedListInsertable<T>()
		{
			// Destrutor da classe
		}

        /**
			Método que insere um valor no fim da lista. Após a execução desta função, o elemento inserido será o último elemento da lista.
			@param valor - valor a ser inserido na lista
			@return true se inseriu com sucesso, false caso contrário
		*/
		bool Inserir(T valor)
		{
			return this->Inserir(new T(valor));
		}

		/**
			Método que insere um valor no fim da lista. Após a execução desta função, o elemento inserido será o último elemento da lista.
			@param valor - valor a ser inserido na lista
			@return true se inseriu com sucesso, false caso contrário
		*/
		bool Inserir(T* valor)
		{
			Node<T>* no = new Node<T>(valor);
			if(no == NULL)
			{
				return false;
			}

			Node<T>* ultimo = this->cauda->anterior;
			no->anterior = ultimo;
			no->proximo = ultimo->proximo;
			ultimo->proximo = no;
			this->cauda->anterior = no;
			this->tamanho++;

			return true;
		}
};
#endif