#ifndef _HASH_ITEM_
#define _HASH_ITEM_

#include "../LinkedList.cpp"

/** 
    Estrutura do item armazenado no objeto da tabela de dispersão. 
*/
template <class T>
class HashItem
{
    public:
        string chave;
        T* dado;

        HashItem<T>(string chave, T* dado)
        {
            // Construtor
            this->chave = chave;
            this->dado = dado;
        }

        ~HashItem<T>()
        {
            // Destrutor da classe
        }
};

#endif