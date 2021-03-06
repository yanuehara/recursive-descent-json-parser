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
	Token nextToken(); //Analisador l�xico em si
	int lineNumber; //Numero da linha atual

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

	//Fun��es do analisador sintatico
	AST::JsonPtr Json();
	AST::ValuePtr Valor();
	AST::ValueNodePtr Objeto();
	void MembrosOpt(AST::ValueNodePtr);
	AST::ParPtr Par();
	AST::ValueNodePtr Array();
	void ElementosOpt(AST::ValueNodePtr);
	AST::ValuePtr Elemento();
};