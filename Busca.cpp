#include <iostream>
#include <iomanip>
#include "Dependencies/Headers/Arquivo.h"
#include "Dependencies/Headers/ControladorArquivos.h"
#include "Dependencies/Headers/Auxiliares.h"
#include "Dependencies/Headers/Entrada.h"
#include "Dependencies/Headers/Timer.h"
using namespace std;
int main(int argc, char* argv[]){
    
    //Primeira linha do Main, para garantir que não teremos falha de segmentação
    
    //Carrega todos os arquivos que foram inseridos (apenas o nome do arquivo e o caminho)
    //preto.txt|Arquivos TXT/preto.txt
    LinkedList<Arquivo> arquivos = ControladorArquivos::LerArquivo(DADOS_ARQUIVOS);
    HashTable<string>* table = new HashTable<string>(3);
    table->DeserializarDoArquivo(DADOS_PALAVRAS);
ControladorArquivos::GarantirBaseDeDados();
    Timer* timer = new Timer();
    timer->Start();
    Entrada* entrada = new Entrada();
    entrada->ProcessarParametrosBusca(argc, argv);

    LinkedList<string> retorno;
    switch(entrada->GetTipoFuncao())
    {
        case FUNC_AND:
        {
            int index = 0;
            entrada->GetParametros().ForEach([&](string* parametro)->bool
            {
                LinkedList<string> tempRetorno = table->Buscar(Auxiliares::ToLowerCase(*parametro));
                if(index == 0)
                {
                    retorno = tempRetorno;
                }
                else
                {
                    LinkedList<string>* tempList = new LinkedList<string>();
                    retorno.ForEach([&](string* indexPalavra)->bool
                    {
                        bool contains = tempRetorno.Any([&](string* dado) { return strcmp(dado->c_str(), indexPalavra->c_str()) == 0; });
                        if(contains)
                        {
                            tempList->Inserir(indexPalavra);
                        }
                    });

                    retorno = *tempList;
                }

                index++;
            });
            
            break;
        }
        case FUNC_OR:
        {
            int index = 0;
            entrada->GetParametros().ForEach([&](string* parametro)->bool
            {
                LinkedList<string> tempRetorno = table->Buscar(Auxiliares::ToLowerCase(*parametro));
                if(index == 0)
                {
                    retorno = tempRetorno;
                }

                tempRetorno.ForEach([&](string* indexPalavra)->bool
                {
                    bool contains = retorno.Any([&](string* dado) { return strcmp(dado->c_str(), indexPalavra->c_str()) == 0; });
                    if(!contains)
                    {
                        retorno.Inserir(indexPalavra);
                    }
                });

                index++;
            });

            break;
        }
        default:
            break;
    }

    // LinkedList<string> retorno = table->Buscar(argv[1]);
    //Uso do & é para pegar a variável arquivos que está acima e fora do escopo do ForEach
    bool wasRasult = false;
    retorno.ForEach([&](string* item) -> bool
    {
        wasRasult = true;
        //abaixo eu pego o índice do arquivo onde existe ocorrência da palavra
        int indexArquivo = stoi(*Auxiliares::Split(";", *item).FirstOrDefault()); 
        int indexLinha = stoi(*Auxiliares::Split(";", *item).LastOrDefault()); 
        //É criado um objeto chamado arquivo que rece
        Arquivo* arquivo = arquivos.GetElementAtIndex(indexArquivo);
        if(arquivo == NULL)
        {
            cout << "ARQUIVO NAO ENCONTRADO ";
        }
        else
        {
            // string textoLinha =  ControladorArquivos::LerLinha(arquivo->caminho, indexLinha);
            cout << arquivo->nome << ": Linha " << indexLinha << endl;
        }
    });   

    if(!wasRasult)
    {
        cout << "Não houve ocorrencia das palavras nos arquivos" << endl;
    } 
    
    timer->Stop();
    timer->GetTimePrint();
    return 0;
}