#ifndef _GENERIC_HASH_TABLE_
#define _GENERIC_HASH_TABLE_

#include "HashTable/HashObject.cpp"
#include "HashTable/HashItem.cpp"

using namespace std;

/**
    Classe que é a estrutura escolhida para manter constante as buscas.
*/
template <class T>
class HashTable
{
	private:
        typedef HashObject<HashItem<T>>* HashObjectPtr;
        int tamanho;
        int qtdObjetos;
        HashObjectPtr* tabela;

    public:
		HashTable<T>(int tamInicial)
		{
            //Construtor
            this->tamanho = tamInicial;
            this->qtdObjetos = 0;
            this->tabela = new HashObjectPtr[tamInicial];

            for(int i = 0 ; i < tamInicial ; i++)
            {
                this->tabela[i] = NULL;
            }
		}

		~HashTable<T>()
		{
			// Destrutor da classe
		}
        /**
            Método que retorna o tamanho inicial da tabela.
            @param - Não possui parametro.
            @return - Retorna um inteiro.
        */
        int getTamanho() {
            return this->tamanho;
        }

        /**
            Método que retorna a quantidade total de objetos.
            @param - Não possui parametro.
            @return - Retorna um inteiro.
        */
        int getQtdObjetos() {
            return this->qtdObjetos;
        }

        /**
            Método que retorna um ponteiro com o tamanho alocado para a tabela.
            @param - Não possui parametro.
            @return - Retorna um ponteiro.
        */
        HashObjectPtr* getTabela() {
            return this->tabela;
        }

        /**
            Método que retorna um inteiro calculado através da palavra.
            @param - String que é a palavra.
            @return - Retorna um inteiro.
        */
        int Hash(string chave)
        {		
            const char* str = chave.c_str();
            long hash = 0;
            int c;
            while ((c = *str++))
            {
                hash += (c + (hash << 6) + (hash << 16) - hash);
            }

            int indice = (hash & 0x7FFFFFFF) % this->tamanho;
            return indice;
        }

        /**
            Método que adiciona uma palavra na tabela.
            @param - String que é a palavra e item de qualquer tipo.
            @return - Não possui retorno.
        */
        void AddItem(string chave, T item)
        {
            this->AddItem(chave, new T(item)); // Aloca uma estrutura de qualquer tipo.
        }

        /**
            Método que inseri a chave.
            @param - String que é a palavra e uma item que é uma lista.
            @return - Retorna um inteiro.
        */
        void AddItem(string chave, T* item)
        {		
            int index = this->Hash(chave);// Calcula um endereço unico.
            if (this->tabela[index] == NULL)// Se for vazia naquele endereço da tabela.
            {	
                this->tabela[index] = new HashObject<HashItem<T>>();// Aloca dentro desse index HashObject que é uma lista.
            }

            this->tabela[index]->InserirValor(new HashItem<T>(chave, item));// Inseri chave e item 
            this->qtdObjetos++;// Incrementa após inserção.
            this->Expandir();// Se precisar expandi tabela.
        }

        /**
            Método que remove uma chave da tabela.
            @param - String que contém a palavra.
            @return - Não possui retorno.
        */
        void RemoveItem(string chave)
        {		
            int index = this->Hash(chave);//Calcula o hash da palavra.
            if (this->tabela[index] == NULL)//Se o endereço estiver vazio.
            {	
                cout << "'" << chave << "' não existe na lista" << endl;
                return;
            }

            bool chaveExiste = this->tabela[index]->itens->Any([&](HashItem<T>* item) { return strcmp(chave.c_str(), item->chave.c_str()) == 0; });
            if(!chaveExiste)//Se chave não esta na lista.
            {	
                cout << "'" << chave << "' não existe na lista" << endl;
                return;
            }

            this->tabela[index]->itens->RemoveRange([&](HashItem<T>* item) { return strcmp(chave.c_str(), item->chave.c_str()) == 0; });

            if(this->tabela[index]->itens->GetTamanho() == 0)
            {
                HashObjectPtr temp = this->tabela[index];//Passa uma "cópia" do que tem neste endereço da tabela.
                delete temp;//Deleta a cópia.
                this->tabela[index] = NULL;//Neste endereço recebe NULL.
            }

            this->qtdObjetos--;//Decrementa a quantidade de objetos.
            this->Reduzir();//Avalia se precisa reduzir.
        }

        /**
            Método que busca por uma chave na lista.
            @param - String que é a palavra.
            @return - Retorna endereço para uma lista.
        */
        LinkedList<T> Buscar(string chave)
        {
            LinkedList<T>* tempItens = new LinkedList<T>();
            if (chave.empty())//Se a chave é vazia.
            {
                cout << "Não é possível buscar itens com chave nula" << endl;	
                return *tempItens;
            }

            int index = this->Hash(chave);
            if ( this->tabela[index] == NULL)//Se no endereço for vazio.
            {
                cout << "'" << chave << "' não existe na lista" << endl;
                return *tempItens;
            }

            bool chaveExiste = this->tabela[index]->itens->Any([&](HashItem<T>* item) { return strcmp(chave.c_str(), item->chave.c_str()) == 0; });
            if(!chaveExiste)//Se não existe chave nesse endereço.
            {	
                cout << "'" << chave << "' não existe na lista" << endl;
                return *tempItens;
            }

            this->tabela[index]->itens->ForEach([&](HashItem<T>* item) -> bool
            {
                if(strcmp(chave.c_str(), item->chave.c_str()) == 0)
                {
                    tempItens->Inserir(*item->dado);//Inseri na lista.
                }
            });

            return *tempItens;
        }
        /**
            Método responsável por expandir a tabela caso tenha necessidade.
        */
        void Expandir()
        {
            double overflow = (double)this->qtdObjetos / this->tamanho;
            if(overflow > 0.5)
            {
                this->Redimensionar(this->tamanho * 2);
            }
        }

        /**
            Método responsável por reduzir a tabela caso tenha necessidade.
        */
        void Reduzir()
        {
            double overflow = (double)this->qtdObjetos / this->tamanho;
            if(overflow < 0.25)
            {
                this->Redimensionar(this->tamanho / 2);
            }
        }

        /**
            Método que redimensiona a tabela conforme o tamanho passado.
            @param - Recebe um inteiro sendo o tamanho.
            @return - Não possui retorno.
        */
        void Redimensionar(int tamanho)
        {
            HashTable<T>* novaTabela = new HashTable<T>(tamanho + 1); //Aloca uma nova tabela com o tamanho passado.
            for(int i = 0; i < this->tamanho; i++)
            {
                if(this->tabela[i] != NULL)
                {
                    this->tabela[i]->itens->ForEach([&](HashItem<T>* item) -> bool
                    {
                        novaTabela->AddItem(item->chave, item->dado);//Inseri na nova tabela o item e chave.
                    });
                }
            }
            
            this->tabela = novaTabela->getTabela();//Devolve tudo para a tabela antiga
            this->tamanho = novaTabela->getTamanho();
            this->qtdObjetos = novaTabela->getQtdObjetos();
        }

        /**
            Imprime o que contêm na tabela.
        */
        void PrintTable()
        {		
            for (int i = 0; i < this->tamanho; i++)
            {
                if(this->tabela[i] != NULL)
                {
                    cout << "-----------------\n";
                    cout << "tamanho = " << this->tamanho << endl;
                    cout << "index = " << i << endl;
                    cout << "# of words in bucket = " << this->tabela[i]->itens->GetTamanho() << endl;
                    this->tabela[i]->itens->ForEach([](HashItem<T>* item) -> bool
                    {
                        cout << item->chave << " - " << *item->dado << endl;
                    });
                    cout << "-----------------\n";
                }
            }
        }
        /**
            Método que inseri numa lista duplamente encadeada a chave e dado.
            @param - Não possui parametro.
            @return - Retorna o endereço um lista.
        */
        LinkedList<string> Serialize()
        {
            LinkedList<string>* dados = new LinkedList<string>();
            for (int i = 0; i < this->tamanho; i++)
            {
                if(this->tabela[i] != NULL)
                {
                    stringstream stream;
                    string chave = "";
                    this->tabela[i]->itens->Ordenar([](HashItem<T>* item1, HashItem<T>* item2) { return item1->chave < item2->chave; });
                    this->tabela[i]->itens->ForEach([&](HashItem<T>* item) -> bool
                    {
                        if(chave == "")
                        {
                            chave = item->chave;
                            stream << chave;
                        }
                        else if(strcmp(chave.c_str(), item->chave.c_str()) != 0)
                        {
                            stream << endl;
                            chave = item->chave;
                            stream << chave;
                        }

                        stream << "|" << *item->dado;
                    });

                    dados->Inserir(stream.str());
                }
            }

            return *dados;
        }

        /**
            Método que coloca uma papiline chave e dado.
            @param - Recebe como parametro o caminho do arquivo.
            @return - Não possui retorno.
        */
        void SerializarNoArquivo(string caminhoArquivo)
        {
            ofstream outfile (caminhoArquivo, ios::out);
            for (int i = 0; i < this->tamanho; i++)
            {
                if(this->tabela[i] != NULL)
                {
                    stringstream stream;//Concatena uma string
                    string chave = "";
                    this->tabela[i]->itens->Ordenar([](HashItem<T>* item1, HashItem<T>* item2) { return item1->chave < item2->chave; });
                    this->tabela[i]->itens->ForEach([&](HashItem<T>* item) -> bool
                    {
                        if(chave == "")
                        {
                            chave = item->chave;
                            stream << chave;
                        }
                        else if(strcmp(chave.c_str(), item->chave.c_str()) != 0)
                        {
                            stream << endl;
                            chave = item->chave;
                            stream << chave;
                        }

                        stream << "|" << *item->dado;
                    });
    
                    outfile << stream.str() << endl;
                }
            }

            outfile.close();
        }
        /**
            Método que retira a papiline.
            @param - Recebe como parametro o caminho para o arquivo.
            @return - Não possui retorno.
        */
        void DeserializarDoArquivo(string caminhoArquivo)
        {
            ifstream inFile (caminhoArquivo);
            if(!inFile.is_open())
            {                              
                cout << "Nao foi possivel abrir o arquivo '" << caminhoArquivo << "'." << endl;
            }

            string tempLinha; 
            while (getline (inFile, tempLinha))
            {
                LinkedList<string> dados = Auxiliares::Split("|", tempLinha);
                string* chave = dados.FirstOrDefault();

                bool ignoreChave = false;
                dados.ForEach([&](string* index) -> bool
                {
                    if(ignoreChave)
                    {
                        this->AddItem(*chave, *index);
                    }
                    else
                    {
                        ignoreChave = true;    
                    }
                });
            }

            inFile.close();
        }
};
#endif