/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

parser.h: Declara as classes Token e Parser

Copyright (c) 2016 Yan Uehara
*/

#include <string>
#include "..\AST\AST.h"

using namespace std;

//Classe Token
class Token {
public:
	//Enumera os tipos de token que serao usados
	enum TokenType {
		_EOF = 256,
		_TRUE,
		_FALSE,
		_NULL,
		STRING,
		NUMERO,
		ABRECHAVE,
		FECHACHAVE,
		ABRECOLCHETE,
		FECHACOLCHETE,
		VIRGULA,
		DOISPONTOS
	};

	int type; //Tipo do token de acordo com o enum acima
	string lexeme; // Lexeme

};

//Classe parser
class Parser {
public:
	AST::JsonPtr parse(const char*); //Parser

private:
	Token lookahead; //Token corrente
	Token nextToken(); //Analisador léxico em si
	int lineNumber; //Numero da linha atual

	int totalObject = 0; //Total de objetos
	int totalObjectMembers = 0; //Total de membros de objetos
	int totalArray = 0; //Total de arrays
	int totalArrayMembers = 0; //Total de membros de arrays

	char* buffer; //Buffer de entrada

	void error(); //Mostra mensagem de erro com a linha do erro e termina

	void advance() {  //Avanca um token
		lookahead = nextToken();
	}

	void match(int t) { //Consome um token
		if (lookahead.type == t)
			advance();
		else
			error();
	}

	//Funções do analisador sintatico
	void Json();
	void Valor();
	void Objeto();
	void MembrosOpt();
	void Pares();
	void P_();
	void Par();
	void Array();
	void ElementosOpt();
	void Elementos();
	void E_();
};