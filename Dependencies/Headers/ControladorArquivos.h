#ifndef _CONTROLADOR_ARQUIVOS_
#define _CONTROLADOR_ARQUIVOS_

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Auxiliares.h"
#include "../LinkedList.cpp"
#include "../HashTable.cpp"
#include "Arquivo.h"

using namespace std;

/**
    Constantes para os tipos de arquivos.
*/
#define DADOS_ARQUIVOS_TEMP "DataBase/Arquivos.data.temp"
#define DADOS_ARQUIVOS "DataBase/Arquivos.data"
#define DADOS_PALAVRAS "DataBase/DadosPalavras.data"
#define PASTA_BASE_DE_DADOS "DataBase"

/**
    Classe responsável em tratar os arquivos usados, transformando na base de busca e depois para as buscas.
*/
class ControladorArquivos
{
    private:
        static void ProcessarArquivo(Arquivo arquivo, HashTable<string>* tabela);

    public:
        ControladorArquivos();
        ~ControladorArquivos();
        static void GarantirBaseDeDados();
        static LinkedList<string> LerArquivoTXT(string nomeArquivo);
        static LinkedList<Arquivo> LerArquivo(string nomeArquivo);
        static string LerLinha(string nomeArquivo, unsigned int indexLinha);
        static bool InserirArquivo(string caminhoArquivo);
        static bool RemoverArquivo(string caminhoArquivo);
        static void ProcessarArquivos();
};
#endif