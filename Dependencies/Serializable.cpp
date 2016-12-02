#ifndef _SERIALIZABLE_
#define _SERIALIZABLE_

#include <iostream>

using namespace std;
/**
    classe responsavel em colocar um delimitador no que for preciso.
*/
class Serializable
{
    public:
        Serializable()
        { 
            // Construtor 
        }
        ~Serializable()
        {
            // Destrutor
        }

        // A função do virtual possibilita que a implementação do método possa variar de acordo com a necessidade.
        virtual string Serialize() = 0;
        virtual void Deserialize(string dados) = 0;
};

#endif