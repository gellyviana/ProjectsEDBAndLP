#ifndef _GENERIC_LINKED_LIST_REMOVABLE_
#define _GENERIC_LINKED_LIST_REMOVABLE_

#include "LinkedListInsertable.cpp"

using namespace std;
/**
 Classe que herda LinkedListInsertable
 */
template <class T>
class LinkedListRemovable : public LinkedListInsertable<T>
{
    public:
		LinkedListRemovable<T>()
		{
			// Construtor da classe
		}

		~LinkedListRemovable<T>()
		{
			// Destrutor da classe
		}
		/**
			Método que remove um Node específico.
			@param Recebe como parâmetro um Node de qualquer tipo.
			@return Não tem retorno.
		*/
		void Remove(T* element)
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(element == i->valor)
				{
					Node<T>* temp = i;
					i->anterior->proximo = i->proximo;
					i->proximo->anterior = i->anterior;
					this->tamanho--;
					delete temp;
					break;
				}
			}
		}
		/**
			Método que remove um Node da lista.
			@param - Func de qualquer tipo e um boleano para parar o a remoção quando for verdadeiro.
			@return Não tem retorno.
		*/
		template<typename Func>
		void RemoveRange(Func func, bool removeOneElement = false)
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(func(i->valor))
				{
					Node<T>* temp = i;
					i->anterior->proximo = i->proximo;
					i->proximo->anterior = i->anterior;
					this->tamanho--;
					
					delete temp;
					if(removeOneElement) { break; }
				}
			}
		}
};
#endif