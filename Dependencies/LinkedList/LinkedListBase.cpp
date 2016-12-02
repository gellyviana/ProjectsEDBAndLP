#ifndef _GENERIC_LINKED_LIST_BASE_
#define _GENERIC_LINKED_LIST_BASE_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "Node.cpp"

using namespace std;

/**
	Classe da lista duplamente encadeada.
*/
template <class T>
class LinkedListBase 
{
    protected:
        Node<T>* cabeca;
		Node<T>* cauda;
		int tamanho;

    public:
        LinkedListBase<T>()
        {
			// Construtor
            this->cabeca = new Node<T>();
			this->cauda = new Node<T>();
			
			this->cabeca->proximo = this->cauda;
			this->cabeca->anterior = NULL;

			this->cauda->anterior = this->cabeca;
			this->tamanho = 0;
        }

        ~LinkedListBase<T>()
        {
            // Destrutor da classe
        }
		
		/**
			Método que retorna tamanho, ou seja, quantidade de elementos inseridos.
			@param Não possui parâmentro.
			@return Retorna quantidade de elementos.
		*/
		int GetTamanho()
		{
			return this->tamanho;
		}

		/**
			Método que pega o primeiro elemento da lista.
			@param Não tem parâmetro.
			@return Retorna o primeiro elemento da lista, caso não exista elementos, retorna NULL.
		*/
		T* FirstOrDefault()
		{
			if(this->cabeca->proximo != this->cauda)
			{
				return this->cabeca->proximo->valor;
			}

			return NULL;
		}

		/**
			Método que pega o último elemento da lista
			@param Não possui parâmetro
			@return Retorna o último elemento, caso não exista elementos, retorna NULL
		*/
		T* LastOrDefault()
		{
			if(this->cauda->anterior != this->cabeca)
			{
				return this->cauda->anterior->valor;
			}

			return NULL;
		}

		/**
			Método que procura um elemento pelo índice e retorna o valor contido.
			@param Índice passado para fazer a busca.
			@return Retorna o elemento, caso não encontre retorna NULL.
		*/
		T* GetElementAtIndex(int indexBuscado)
		{
			int indexElemento = 0;
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(indexElemento == indexBuscado)
				{
					return i->valor;
				}

				indexElemento++;
			}

			return NULL;
		}

		/**
			Método que procura um Node verdadeiro.
			@param recebe um método de qualquer tipo.
			@return Não tem retorno.
		*/
		template<typename Func>
		void ForEach(Func func)
		{
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{		
				int breaked = func(i->valor);
				if(breaked == true) { break; }
			}
		}

        /**
			Método que imprime todos os elementos da lista.
			@param Não tem.
			@return Não tem retorno.
		*/
		void Imprimir()
		{
			cout << "Tamanho " << this->tamanho << endl;
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(i->valor != NULL)
				{
					cout << "[" << i->valor << "]->";
				}
			}

			cout << endl;
		}

		/**
			Método que imprime todos os elementos da lista.
			@param Do tipo string um ponteiro para um método que recebe um Node.
			@return Não tem retorno.
		*/
		void Imprimir(string (*func)(T*))
		{
			cout << "Tamanho " << this->tamanho << endl;
			for(Node<T>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo)
			{
				if(i->valor != NULL)
				{
					cout << "[" << func(i->valor) << "]->";
				}
			}

			cout << endl;
		}
};
#endif