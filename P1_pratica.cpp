/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

P1_pratica.cpp: Arquivo principal / entry-point da solucao

Copyright (c) 2016 Yan Uehara
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
	//Checa se foi passado o número incorreto de argumentos
	if (argc < 2) {
		cout << "ERRO: Numero de argumentos insuficientes!" << endl;
		cout << "Uso: jr.exe <arquivo JSON>" << endl;

		return -1;
	}

	ifstream json(argv[1], ios::ios_base::in | ios::ios_base::binary); //Abre o arquivo de entrada

	if (json.fail()) { //Se houver falha, mostra mensagem de erro e termina
		cout << "ERRO: Erro na abertura do arquivo, verifique o nome e o caminho" << endl;

		return -1;
	}

	//Declara o parser
	Parser json_parser;

	//Obtem o tamanho do arquivo
	int file_length;
	json.seekg(0, ios::end);
	file_length = json.tellg();           //Esse e o length
	json.seekg(0, ios::beg);
	char *buffer = new char[file_length]; //Aloca buffer de tamanho suficiente
	memset(buffer, 0, file_length); //Zera o buffer
	json.read(buffer, file_length);       // Lê o arquivo para o buffer
	json.close(); //Fecha o arquivo
	buffer[file_length] = '\0'; //Termina a string com '\0'

	json_parser.parse(buffer); //Chama o parser

    return 0;
}

