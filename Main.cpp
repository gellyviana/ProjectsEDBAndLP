#include <iostream>
#include "Dependencies/LinkedList.cpp"
#include "Dependencies/Headers/Arquivo.h"
#include "Dependencies/Headers/ControladorArquivos.h"
#include "Dependencies/Headers/Auxiliares.h"
#include "Dependencies/Headers/Entrada.h"
#include "Dependencies/HashTable.cpp"

using namespace std;

int main(int argc, char* argv[])
{    
    // HashTable<string>* table = new HashTable<string>(3);
    // table->AddItem("gato", "1;1");
    // table->AddItem("gato", "1;2");
    // table->AddItem("gata", "2;1");
    // table->AddItem("gata", "2;1");
    // table->AddItem("gata", "3;1");
    // table->AddItem("gato", "12;90");
    // table->AddItem("gata", "4;1");
    // table->AddItem("gata", "5;1");
    // table->AddItem("gata", "6;1");
    // table->AddItem("gato", "2;2");
    // table->AddItem("gata", "7;1");
    // table->AddItem("gata", "8;1");
    // table->AddItem("gato", "12;80");
    // table->AddItem("gata", "9;1");
    // cout << table->Serialize() << endl;
    // // table->RemoveItem("gata");
    // table->PrintTable();
    // LinkedList<string> retorno = table->Buscar("gata");
    // retorno.ForEach([](string* item) -> bool
    // {
    //     cout << *item << endl;
    // });
    
    // HashTable<string>* table = new HashTable<string>(3);
    // table->DeserializarDoArquivo(DADOS_PALAVRAS);
    // LinkedList<string> retorno = table->Buscar("que");
    // retorno.ForEach([](string* item) -> bool
    // {
    //     cout << *item << endl;
    // });
    // return 0;

    ControladorArquivos::GarantirBaseDeDados();

    Entrada* entrada = new Entrada();
    entrada->ProcessarParametros(argc, argv);

    switch(entrada->GetTipoFuncao())
    {
        case FUNC_INSERIR:
        {
            entrada->GetParametros().ForEach([](string* parametro)->bool
            {
                ControladorArquivos::InserirArquivo(*parametro);
            });
            
            break;
        }
        case FUNC_LISTAR:
        {
            LinkedList<Arquivo> dados = ControladorArquivos::LerArquivo(DADOS_ARQUIVOS);
            dados.ForEach([](Arquivo* arquivo)->bool
            {
                cout << arquivo->nome << endl;
            });

            break;
        }
        case FUNC_LISTAR_ORDEM_ALFABETICA:
        {
            LinkedList<Arquivo> dados = ControladorArquivos::LerArquivo(DADOS_ARQUIVOS);
            dados.Ordenar([](Arquivo* item1, Arquivo* item2) { return item1->nome < item2->nome; });
            dados.ForEach([](Arquivo* arquivo)->bool
            {
                cout << arquivo->nome << endl;
            });

            break;
        }
        case FUNC_REMOVER:
        {
            entrada->GetParametros().ForEach([](string* parametro)->bool
            {
                ControladorArquivos::RemoverArquivo(*parametro);
            });

            break;
        }
        default:
            break;
    }
}

// int main(int argc, char* argv[])
// {    
//     ControladorArquivos::GarantirBaseDeDados();
//     // ControladorArquivos::InserirArquivo("Arquivos TXT/teste.txt");
//     // ControladorArquivos::InserirArquivo("Arquivos TXT/teste com espaços.txt");
//     // ControladorArquivos::InserirArquivo("Arquivos TXT/teste.2.txt");
//     ControladorArquivos::InserirArquivo("Arquivos TXT/teste.3.txt");
//     LinkedList<Arquivo> dados = ControladorArquivos::LerArquivo("DataBase/Arquivos.data");
//     ControladorArquivos::RemoverArquivo("Arquivos TXT/teste com espaços.txt");
    
//     for(int i=0; i < dados.GetTamanho() ; i++)
//     {
//         // cout << dados.GetElementAtIndex(i)->nome << endl;
//     }

//     dados.ForEach([](Arquivo* arquivo)->bool
//     {
//         cout << arquivo->nome << endl;
//         // return true;
//     });
    
//     // Arquivo* arquivo = new Arquivo(1);
//     // Linha* linha = new Linha(arquivo->GetIdArquivo(), 1);

//     // Palavra* palavra = new Palavra(linha->GetIdArquivo(), linha->GetIdLinha());
//     // palavra->SetTexto("Manoel");
//     // Palavra* palavra2 = new Palavra(linha->GetIdArquivo(), linha->GetIdLinha());
//     // palavra2->SetTexto("Dinab");

//     // linha->GetPalavras()->Inserir(palavra);
//     // linha->GetPalavras()->Inserir(palavra2);
//     // arquivo->GetLinhas()->Inserir(linha);

//     // arquivo->GetLinhas()->Imprimir();
//     // arquivo->GetLinhas()->FirstOrDefault()->GetPalavras()->Imprimir([](Palavra* i) { return i->GetTexto(); });
//     // lista->Inserir(10);
//     // lista->Inserir(55);
//     // int* item = lista->Buscar_First([](int* i) { return *i == 10; });
//     return 0;
// }