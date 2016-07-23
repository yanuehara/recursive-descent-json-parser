// P1_pratica.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {	
	if (argc < 2) {
		cout << "ERRO: Numero de argumentos insuficientes!" << endl;
		cout << "Uso: jr.exe <arquivo JSON>" << endl;

		return -1;
	}

	ifstream json(argv[1]);

	if (json.fail()) {
		cout << "ERRO: Erro na abertura do arquivo, verifique o nome e o caminho" << endl;

		return -1;
	}

    return 0;
}

