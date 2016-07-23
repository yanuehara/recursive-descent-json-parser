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

	FILE *json;
	errno_t error;
	error = fopen_s(&json, argv[1], "r");

	if (json == nullptr ) {
		cout << "ERRO: Erro na abertura do arquivo, verifique o nome e o caminho" << endl;

		return -1;
	}

    return 0;
}

