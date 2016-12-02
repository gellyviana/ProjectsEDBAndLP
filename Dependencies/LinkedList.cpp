#ifndef _GENERIC_LINKED_LIST_
#define _GENERIC_LINKED_LIST_

#include "LinkedList/LinkedListRemovable.cpp"

using namespace std;
/**
	Classe que herda de LinkedListRemovable os métodos que removem um Node da lista.
*/
template <class T>
class LinkedList : public LinkedListRemovable<T>
{
	private:

    public:
		LinkedList<T>()
		{
			// Construtor da classe
		}

		~LinkedList<T>()
		{
			// Destrutor da classe
		}

		/**
			Método que busca um item na lista - Busca apenas itens de tipos primitivos, EX: (int, char, double...).
			@param valor - Valor do item que está sendo buscado.
			@return O primeiro item cujo valor foi encontrado ou retorna NULL caso o item não seja encontrado na lista.
		*/
		T* Buscar_First(T valor)
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(i->valor != NULL && *i->valor == valor)
				{
					return i->valor;
				}
			}

			return NULL;
		}

		/**
			Método que busca um item na lista. EX: 
			@param func - Função que define se o item é o que está sendo buscado, retorna um bool se o item foi encontrado.
			@return O primeiro item cujo valor foi encontrado. Retorna NULL caso o item não seja encontrado na lista.
			Exemplo de uso: Buscar([](int* i) { return *i == 10; });
		*/
		T* Buscar_First(bool (*func)(T*))
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(func(i->valor))
				{
					return i->valor;
				}
			}

			return NULL;
		}

		/**
			Método que busca um item na lista. EX: 
			@param func - Função que define se o item é o que está sendo buscado, retorna um bool se o item foi encontrado.
			@return O primeiro item cujo valor foi encontrado. Retorna NULL caso o item não seja encontrado na lista.
			Exemplo de uso: Buscar([](int* i) { return *i == 10; });
		*/
		LinkedList<T> Buscar_ToList(bool (*func)(T*))
		{
			LinkedList<T>* tempList = new LinkedList();
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(func(i->valor))
				{
					tempList->Inserir(i->valor);
				}
			}

			return *tempList;
		}

		/**
			Método que retorna falso se um valor não estiver numa lista.
			@param - Func pode ser qualquer tipo que contenha uma lista.
			@return - Retorna verdadeiro enquando valor estiver na lista, caso contrario retorna falso.
		*/
		template<typename Func>
		bool Any(Func func)
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(func(i->valor))
				{
					return true;
				}
			}

			return false;
		}

		/**
			Método que ordena lista duplamente encadeada
			@param - Duas lista de qualquer tipo e um retorno boleano.
			@return - Não possui retorno.
		*/
		void Ordenar(bool (*func)(T*, T*))
		{
			for(Node<T>* item1 = this->cabeca->proximo; item1 != this->cauda; item1 = item1->proximo)
			{
				Node<T>* temp = item1->proximo;
				for(Node<T>* item2 = temp; item2 != this->cauda; item2 = item2->proximo)
				{
					if(func(item1->valor, item2->valor))
					{
						this->Intercalar(item1, item2);
					}
				}

				item1 = temp->anterior;
			}
		}

		/**
			Método que intercala valores contido nos Node.
			@param item1 e item2 do tipo Node.
			@return Inverte valores e passa por referência, pois o método é void.
		*/
		void Intercalar(Node<T>* item1, Node<T>* item2)
		{
			T* temp = item1->valor;
			item1->valor = item2->valor;
			item2->valor = temp;
		}

		/**
			Método que chama outro para Ordenar.
			@param troca os Node's retornando um boleano, método que imprime a lista.
			@return Os valores trocados pro referência, pois é void.
		*/
		void OrdenarQuick(bool (*func)(T*, T*), void (*print)(T*))
		{
			this->QuickSort(this->cabeca->proximo, this->cauda->anterior, func, print);
		}

		void QuickSort(Node<T>* item1, Node<T>* item2, bool (*func)(T*, T*), void (*print)(T*))
		{
			if(item1 != NULL && item2 != NULL && item1 != item2->proximo)
			{
				Node<T>* no = this->Particionar(item1, item2, func, print);
				this->QuickSort(item1, no->anterior, func, print);
				this->QuickSort(no->proximo, item2, func, print);
			}
		}

		Node<T>* Particionar(Node<T>* item1, Node<T>* item2, bool (*func)(T*, T*), void (*print)(T*))
		{
			T* pivo = item2->valor;
			Node<T>* i = item1->anterior;

			for(Node<T>* item = item1; item != item2; item = item->proximo)
			{
				Node<T>* temp = item->proximo;
				if(func(item->valor, pivo))
				{			
					i = (i == this->cabeca || i == this->cauda) ? item1 : i->proximo;
					if(i != item)
					{
						this->Intercalar(i, item);
					}
					// print(i->valor);
				}
				item = temp->anterior;
			}
			
			i = (i == this->cabeca || i == this->cauda) ? item1 : i->proximo;
			this->Intercalar(i, item2);

			return i;
		}
};
#endif