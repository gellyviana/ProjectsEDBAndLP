all:
	g++ -std=c++11 Main.cpp Dependencies/Entrada.cpp Dependencies/Auxiliares.cpp Dependencies/ControladorArquivos.cpp Dependencies/LinkedList.cpp Dependencies/Models/Arquivo.cpp Dependencies/Models/Linha.cpp Dependencies/Models/Palavra.cpp Dependencies/Timer.cpp -o basedebusca
	g++ -std=c++11 Busca.cpp Dependencies/Entrada.cpp Dependencies/Auxiliares.cpp Dependencies/ControladorArquivos.cpp Dependencies/LinkedList.cpp Dependencies/Models/Arquivo.cpp Dependencies/Models/Linha.cpp Dependencies/Models/Palavra.cpp Dependencies/Timer.cpp -o busca
compile: