#include "Headers/Entrada.h"

using namespace std;

Entrada::Entrada()
{
    // Construtor
    this->_index = 0;
    this->_iarg = 0;
    this->_opterr = 0;
    this->_tipoFuncao = FUNC_PARAM_INVALIDO;
    this->_parametros = new LinkedList<string>();
}

Entrada::~Entrada()
{
    // Destrutor da classe
}

/**
    Método que retorna um tipo de função, que é uma das opções desejada pela usuario.
    @param - Não possui parâmetro.
    @return - Retorna um tipo de função.
*/
Funcao Entrada::GetTipoFuncao()
{
    return this->_tipoFuncao;
}

/**
    Método que retorna um ponteiro para uma lista.
    @param - Não possui parâmetro.
    @return - Retorna endereço para uma lista encadeada.
*/
LinkedList<string> Entrada::GetParametros()
{
    return *this->_parametros;
}

/**
    Método que rebece a entrada do usuario.
    @param - n_argc é o número de parametros e n_argv os parametros do usuario.
    @return - Não possui retorno.

*/
void Entrada::ProcessarParametros(int n_argc, char* n_argv[])
{
    this->_argc = n_argc;
    this->_argv = n_argv;
    this->ValidaParametros();
}

/**
    Método responsavel em chamar a funçao deseja pelo usuario coforme a opção de entrada.
*/
void Entrada::ValidaParametros()
{
    if(this->_argc == 1)
    {
        this->ExibeAjuda();
        exit(1);
    }

    bool _flag = false;
    int long_index =0;
    // while((this->_iarg = getopt_long(this->_argc, this->_argv, ":i:r:b:p:t:l:amsh", longopts, &long_index)) != -1)
    while((this->_iarg = getopt(this->_argc, this->_argv, ":i:r:b:p:t:l:amsh")) != -1)
    { 
        if(Verify(_iarg, 'i')) //INSERIR
        {
            this->_tipoFuncao = FUNC_INSERIR;
            this->ValidarArgumentos();
        }
        else if(Verify(_iarg, 'r')) //REMOVER
        {
            this->_tipoFuncao = FUNC_REMOVER;
            this->ValidarArgumentos();
        }
        else if(Verify(_iarg, 'b') || Verify(_iarg, 'p') || Verify(_iarg, 't')) //BUSCA ou IMPRESSÃO ou TEMPO
        {
            this->_tipoFuncao = FUNC_BUSCAR;
        }
        else if(Verify(_iarg, 'l')) //LISTAR
        {
            if(strcmp(optarg,"I") == 0) this->_tipoFuncao = FUNC_LISTAR;
            if(strcmp(optarg,"A") == 0) this->_tipoFuncao = FUNC_LISTAR_ORDEM_ALFABETICA;
            if(strcmp(optarg,"T") == 0) this->_tipoFuncao = FUNC_LISTAR_ORDEM_QTD_PALAVRAS;
        }
        else if(Verify(_iarg, 'h')) //HELP
        {
            this->ExibeAjuda();
        }
        else if(Verify(_iarg, ':'))
        {
            switch (optopt)
            {
                case 'i': //LISTAR S/ PARAMETRO
                case 'r': //REMOVER S/ PARAMETRO
                    this->MSGParamObrigNaoInformado();
                    break;
                default:
                    this->MsgParamInvalido();
                    break;
            }
        }
        else if(this->_iarg == -1)
        {
            return;
        }
        else 
        {
            this->MsgParamInvalido();
        }
    }
}

/**
    Método responsavel em chamar a função buscar.
*/
void Entrada::ValidarArgumentos()
{
    this->CarregaArgumentos();

    if(this->_tipoFuncao == FUNC_BUSCAR) return;
}

/**
    Método que recebe varios argumentos.
*/
void Entrada::CarregaArgumentos()
{
    if(this->_tipoFuncao != FUNC_BUSCAR)
    { 
        this->_parametros->Inserir(optarg); // Adiciona o primeiro argumento 
    }

    // Adiciona os argumentos em excesso
    int index = optind;
    if (this->_argv[index] != NULL && this->_argv[index][0] != '-')
    {
        while(index < this->_argc && this->_argv[index][0] != '-')
        {
            this->_parametros->Inserir(this->_argv[index]);
            index++;
        }

        optind = index-1;
    }
}

// void Entrada::ValidaArgumentosBusca()
// {
//          if(strcmp(optarg,"AND") == 0) this->SetParamBusca(AND);
//     else if(strcmp(optarg, "OR") == 0) this->SetParamBusca(OR);
//     else if(strcmp(optarg, "A" ) == 0) this->SetParamBusca(IMP_ORDEM_ALFABETICA);
//     else if(strcmp(optarg, "C" ) == 0) this->SetParamBusca(IMP_ORDEM_DECRESCENTE_N_OCORRENCIAS);
//     else if(strcmp(optarg, "I" ) == 0) this->SetParamBusca(IMP_ORDEM_INSERCAO_ARQUIVO);
//     else if(strcmp(optarg, "A" ) == 0) this->SetParamBusca(IMP_ORDEM_ALFABETICA);
//     else if(strcmp(optarg, "C" ) == 0) this->SetParamBusca(IMP_ORDEM_DECRESCENTE_N_OCORRENCIAS);
//     else if(strcmp(optarg, "I" ) == 0) this->SetParamBusca(IMP_ORDEM_INSERCAO_ARQUIVO);
//     else if(strcmp(optarg, "T" ) == 0) this->SetParamBusca(EXIBIR);
//     else if(strcmp(optarg, "F" ) == 0) this->SetParamBusca(NAO_EXIBIR);
//     else MSGParamInvalido();
//     this->ValidaArgumentos();
// }

/**
    Método que rebecebe a entrada do usuario, para realizar a busca.
    @param - n_argc é o número de parametros e n_argv os parametros do usuario.
    @return - Não possui retorno.
*/
void Entrada::ProcessarParametrosBusca(int n_argc, char* n_argv[])
{
    this->_argc = n_argc;
    this->_argv = n_argv;
    this->ValidaParametrosBusca();
}

/**
    Método usado para opções de busca selecionado pelo usuario, passando por algumas validações, antes que seja executado.
*/
void Entrada::ValidaParametrosBusca()
{
    if(this->_argc == 1)
    {
        cout << "Não foram informados parâmetros válidos" << endl;
        exit(1);
    }

    if(this->_argc == 2 && this->_argv[1][0] == '-')
    {
        cout << "Argumento obrigatorio não foi informado." << endl;
        exit(1); 
    }
    else if(this->_argc >= 2 && this->_argv[1][0] != '-')
    {
        this->_tipoFuncao = FUNC_OR;
    }
    else if(this->_argc > 2 && this->_argv[1][0] == '-')
    {
        if(strcmp(this->_argv[1], "-AND") == 0)
        {
            this->_tipoFuncao = FUNC_AND;// Método da busca AND.
        }
        else if(strcmp(this->_argv[1], "-OR") == 0)
        {
            this->_tipoFuncao = FUNC_OR;// Método da busca OR.
        }
        else
        {
            cout << "Parametro Invalido. Utilize -AND ou -OR" << endl;
            exit(1); 
        }
    }

    int index = this->_argv[1][0] == '-' ? 2 : 1;
    if (this->_argv[index] != NULL && this->_argv[index][0] != '-')
    {
        while(index < this->_argc)
        {
            if(this->_argv[index][0] == '-')
            {
                cout << "Parametro Invalido" << endl;
                exit(1);
            }

            this->_parametros->Inserir(this->_argv[index]);//Método da basebusca para inserir arquivo.
            index++;
        }
    }
}

/**
    Método que mostra as opções validas que o usuario pode usar.
*/
void Entrada::ExibeAjuda()
{
    char* s = this->_argv[0];
    cout<<"\t>> Ajuda:   " << endl;
    cout<<"\tUse:   "<< s <<" [-opção] [argumento]"<< endl;
    cout<<"\tOpção:  "<<"-h  Exibe informações de ajuda"<< endl;
    cout<<"\t        "<<"-i  Insere um novo arquivo na base de buscas"<< endl;
    cout<<"\t        "<<"-r  Remove um arquivo da base de buscas"<< endl;
    cout<<"\t        "<<"-lI Lista todos os arquivos contidos na base de buscas na ordem em que foram inseridos à base"<< endl;
    cout<<"\t        "<<"-lA Lista todos os arquivos contidos na base de buscas em ordem alfabética"<< endl;
    cout<<"\t        "<<"-lT Lista todos os arquivos contidos na base de buscas em ordem decrescente da quantidade de palavras em cada arquivo"<< endl;
    cout<<"\tExemplo: "<< s <<" -i teste.txt notas.txt"<< endl;
    exit(1);
}
/**
    Método invocado caso o usuario tente efetuar alguma ação não permitida pelo programa.
*/
void Entrada::MsgParamInvalido()
{
    cerr << "\t>> Parametro Invalido! use -h ou --help para ajuda.\n" << /*this->_argv[0] << (char)optopt <<*/ endl;
    exit(1);
}
/**
    Método invocado para informar algo que não realizado pelo usuario.
*/
void Entrada::MSGParamObrigNaoInformado()
{
    cout << "\t>> Argumento obrigatorio não foi informado. use -h ou --help para mais informações.\n" << endl;
    exit(1);
}

/**
    Método para averiguar se a opção do usuario é valida.
    @param - value1 opção do usuario e value2 opção definida no programa.
    @return - Verdadeiro se os dois valores forem iguais ou falso caso contrario.
*/
bool Entrada::Verify(char value1, char value2)
{
    return value1 == value2;
}