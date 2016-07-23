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

	ifstream json(argv[1], ios::ios_base::in | ios::ios_base::binary);

	if (json.fail()) {
		cout << "ERRO: Erro na abertura do arquivo, verifique o nome e o caminho" << endl;

		return -1;
	}

	Parser json_parser;

	int file_length;
	json.seekg(0, ios::end);    // go to the end
	file_length = json.tellg();           // report location (this is the length)
	json.seekg(0, ios::beg);    // go back to the beginning
	char *buffer = new char[file_length];    // allocate memory for a buffer of appropriate dimension
	memset(buffer, 0, file_length);
	json.read(buffer, file_length);       // read the whole file into the buffer
	json.close();
	buffer[file_length] = '\0';

	json_parser.parse(buffer);

    return 0;
}

