#ifndef _HASH_OBJECT_
#define _HASH_OBJECT_

#include "../LinkedList.cpp"

/**
    Estrutura do objeto armazenado na tabela de dispersão. 
*/
template <class T>
class HashObject
{
    public:
        LinkedList<T>* itens;

        HashObject<T>()
        {
            // Construtor
            this->itens = new LinkedList<T>();
        }

        ~HashObject<T>()
        {
            // Destrutor da classe
        }

        /**
            Método para Inserir um item de qualquer tipo da lista.
            @param - Item de qualquer tipo contido na lista.
            @return - não retorna.
        */
        void InserirValor(T* item)
        {
            this->itens->Inserir(item);
        }
        
        /**
            Método para Remove um item de qualquer tipo da lista.
            @param - Item de qualquer tipo contido na lista.
            @return - não retorna.
        */
        void RemoverValor(T* item)
        {
            this->itens->Remove(item);
        }
};

#endif