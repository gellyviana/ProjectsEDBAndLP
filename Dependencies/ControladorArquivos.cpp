#include "Headers/ControladorArquivos.h"

using namespace std;

ControladorArquivos::ControladorArquivos()
{
    /// Construtor da classe
}

ControladorArquivos::~ControladorArquivos()
{
    // Destrutor da classe
}

/**
    Método que abre um arquivo TXT e lê linha por linha e inseri numa lista duplamente encadeada.
    @param - Nome do arquivo do string.
    @return - Retorna o endereço contendo o inicio de uma lista duplamente encadeada.
*/
LinkedList<string> ControladorArquivos::LerArquivoTXT(string nomeArquivo)
{
    LinkedList<string>* dados = new LinkedList<string>();// Aloca dinamicamente um nova lista do tipo string.

    ifstream arquivo (nomeArquivo);
	if(!arquivo.is_open())// Abre um arquivo.
	{                              
		cout << "Nao foi possivel abrir o arquivo '" << nomeArquivo << "'." << endl;
		return *dados;
	}

    string tempLinha; 
    while (getline (arquivo, tempLinha))//Função que lê linha por linha o arquivo.
    {
        dados->Inserir(tempLinha);//Chama o método Inserir da lista.
    }

    arquivo.close();
    return *dados;
}

/**
    Método que abre um arquivo para leitura e retorna uma lista com especificaçoes do arquivo.
    @param - String que contem o nome do arquivo.
    @return - Retorna o endereço do inicio da lista duplamente encadeada.
*/
LinkedList<Arquivo> ControladorArquivos::LerArquivo(string nomeArquivo)
{
    LinkedList<Arquivo>* dados = new LinkedList<Arquivo>();// Aloca dinamicamente um nova lista do tipo string.

    ifstream arquivo (nomeArquivo);
	if(!arquivo.is_open())// Abre um arquivo.
	{                              
		cout << "Nao foi possivel abrir o arquivo '" << nomeArquivo << "'." << endl;
		return *dados;
	}

    int codigoArquivo = 0;
    string tempLinha; 
    while (getline (arquivo, tempLinha))//Função que lê linha por linha do arquivo.
    {
        Arquivo* tempArquivo = new Arquivo(codigoArquivo++);// Cria um novo arquivo.
        tempArquivo->Deserialize(tempLinha);
        dados->Inserir(*tempArquivo);//Chama o método Inserir da lista.
    }

    arquivo.close();
    return *dados;
}
/**
    Retorna a linha do arquivo que esta numa linha especifica do arquivo.
    @param - String com o nome do arquivo e inteiro com numero da linha a ser trabalhada.
    @return - Retorna um string contendo a frase desejada.
*/
string ControladorArquivos::LerLinha(string nomeArquivo, unsigned int indexLinha)
{
	ifstream arquivo (nomeArquivo);
	if(!arquivo.is_open())// Abre um arquivo.
	{
		cout << "Nao foi possivel abrir o arquivo '" << nomeArquivo << "'." << endl;
		return NULL;
	}
	
    arquivo.seekg(ios::beg);// Seekg indica a posição para buscar caracteres.
    for( int i=0; i < indexLinha; ++i)
	{
        arquivo.ignore(numeric_limits<streamsize>::max(), '\n');// Função que ignora o pular linha e tamanha maximo do arquivo.
    }
    
    string linha;
    getline(arquivo, linha);
    arquivo.seekg(ios::beg);
    arquivo.close();
    return string(linha);
}
/**
    Método que inseri um arquivo.
    @param - Nome da pasta.
    @return - retorna verdadeiro quando consegui inserir o arquivo ou falso quando ja foi inserido ou não existe a pasta.
*/
bool ControladorArquivos::InserirArquivo(string caminhoArquivo)
{
    ofstream stream;
	stream.open(caminhoArquivo, ios_base::in);
	if(!stream)
	{
		cout << "Não foi possível localizar o arquivo '" << caminhoArquivo << "'" << endl;
        return false;
	}

    string nomeArquivo = *Auxiliares::Split("/", caminhoArquivo).LastOrDefault();
    LinkedList<Arquivo> dados = LerArquivo(DADOS_ARQUIVOS);// Recebe uma "cópia" da lista que contem os arquivos.
    bool arquivoJaExiste = dados.Any([&](Arquivo* dado) { return strcmp(dado->nome.c_str(), nomeArquivo.c_str()) == 0; });
    if(arquivoJaExiste)// Verifica se arquivo existe no banco.
    {
        cout << "O arquivo '" << nomeArquivo << "' já existe na Base de Dados" << endl;
        return false;
    }

    Arquivo* arquivo = new Arquivo(0);
    arquivo->nome = nomeArquivo;
    arquivo->caminho = caminhoArquivo;

    ofstream outfile;
    outfile.open(DADOS_ARQUIVOS, ios::binary | ios::app);//Abre para saida.
    outfile << arquivo->Serialize() << endl;// Coloca uma papiline entre o nome do arquivo e o caminho.
    outfile.close();

    ProcessarArquivos();
    return true;
}
/**
    Método responsavel em remover um arquivo especifico.
    @param - String que contem o caminho do arquivo.
    @return - Retorna verdadeiro se conseguir remover o arquivo, caso contrario retorna falso.
*/
bool ControladorArquivos::RemoverArquivo(string caminhoArquivo)
{
    string nomeArquivo = *Auxiliares::Split("/", caminhoArquivo).LastOrDefault();
    LinkedList<Arquivo> dados = LerArquivo(DADOS_ARQUIVOS);//Caminho que contem os arquivos.
    bool arquivoExiste = dados.Any([&](Arquivo* dado) { return strcmp(dado->nome.c_str(), nomeArquivo.c_str()) == 0; });
    if(!arquivoExiste)// Verifica se arquivo existe no banco.
    {
        cout << "O arquivo '" << nomeArquivo << "' não existe na Base de Dados" << endl;
        return false;
    }

    dados.RemoveRange([&](Arquivo* dado) { return strcmp(dado->nome.c_str(), nomeArquivo.c_str()) == 0; }, true);
    // Caso encontre os aruivo que pretende- se remover retorna verdadeiro e remove da lista.
    
    ofstream outfile;
    outfile.open(DADOS_ARQUIVOS_TEMP, ios::binary | ios::app);
    dados.ForEach([&](Arquivo* arquivo)->bool
    { 
        outfile << arquivo->Serialize() << endl;// Faz a cópia do que contem na base para DADOS_ARQUIVOS_TEMP.
    });

    outfile.close();

    remove(DADOS_ARQUIVOS);// Apaga a base original
    rename(DADOS_ARQUIVOS_TEMP, DADOS_ARQUIVOS);// Renomeia para o nome original.

    ProcessarArquivos();
    return true;
}

/**
    Método responsável em usar a base de dados para trabalhar com a tabela Hash.
*/
void ControladorArquivos::ProcessarArquivos()
{
    HashTable<string>* tabela = new HashTable<string>(10);// Aloca a estrutura do tipo HashTable com tamanho pré definido.
    LinkedList<Arquivo> dados = LerArquivo(DADOS_ARQUIVOS);
    dados.ForEach([&](Arquivo* arquivo)->bool
    {
        ProcessarArquivo(*arquivo, tabela);
    });

    tabela->SerializarNoArquivo(DADOS_PALAVRAS);// Todas as palavras do arquivo estarão separados pelo papiline.
}

void ControladorArquivos::ProcessarArquivo(Arquivo arquivo, HashTable<string>* tabela)
{
    ifstream inFile (arquivo.caminho);
	if(!inFile.is_open())
	{                              
		cout << "Nao foi possivel abrir o arquivo '" << arquivo.caminho << "'." << endl;
	}

    int idArquivo = arquivo.GetIdArquivo();
    int idLinha = 0;
    string tempLinha; 
    while (getline (inFile, tempLinha))//Função que lê linha por linha.
    {
        string texto = Auxiliares::RemoverCaracteresEspeciais(tempLinha);// Retira os lixos do texto.
        LinkedList<string> palavras = Auxiliares::Split(" ", texto);//Coloca um espaço entre cada palavra.
        palavras.ForEach([&](string* palavra) -> bool
        {
            ostringstream index;
            index << idArquivo << ";" << idLinha;//Faz a numeração da linha lida.
            tabela->AddItem(Auxiliares::ToLowerCase(*palavra), index.str());// Modifica cada palavra para minusculo.
        });

        idLinha++;
    }

    inFile.close();
}
/**
    Método responsável em criar a pasta que irá conter os arquivos inseridos.
*/
void ControladorArquivos::GarantirBaseDeDados()
{
    // Cria a pasta da BASE DE DADOS.
    string comando = "mkdir -p ";//Comando usado para criar um novo diretorio ou pasta.
	comando += PASTA_BASE_DE_DADOS;//PASTA_BASE_DE_DADOS é uma constante.
	const int dir_err = system(comando.c_str());
	if (-1 == dir_err)
	{
	    cout << "Erro ao criar o diretório da Base de Dados!" << endl;
	}

    // Cria o arquivo que contem as informações dos arquivos inseridos.
    ofstream st;
	st.open(DADOS_ARQUIVOS, ios_base::in); // Abre para leitura.
	if(!st)
	{
		st.open(DADOS_ARQUIVOS); // Se não existe, cria.
	}

    st.close();

    // Cria o arquivo que contem as informações das palavras dos arquivos inseridos.
    ofstream stream;
	stream.open(DADOS_PALAVRAS, ios_base::in); // Abre para leitura.
	if(!stream)
	{
		stream.open(DADOS_PALAVRAS); // Se não existe, cria. 
	}

    stream.close();
}