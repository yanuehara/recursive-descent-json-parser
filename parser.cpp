#include "stdafx.h"
#include "parser.h"
#include <iostream>

void Parser::parse(const char* input) {
	buffer = const_cast<char*>(input);
	lineNumber = 1;
	
	cout << "Começando o parsing..." << endl;

	lookahead = nextToken();

	Json();

	if (lookahead.type != Token::_EOF)
		error();

	cout << "Parsing completo sem erros!" << endl;
	getchar();
}

void Parser::error() {
	cout << "ERRO na linha: " << lineNumber << " abortando... " << endl;
	cout << "Pressione qualquer tecla para sair" << endl;
	
	getchar();

	exit(EXIT_FAILURE);
}

void Parser::Json() {
	Valor();
}

void Parser::Valor() {
	//'{', '[', string, numero, TRUE, FALSE, null }
	if(lookahead.type == Token::ABRECHAVE)
		Objeto();
	else if(lookahead.type == Token::ABRECOLCHETE)
		Array();
	if (lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == Token::_FALSE ||
		lookahead.type == Token::_NULL
		) {
		advance();
	}
}

void Parser::Objeto() {
	if (lookahead.type == Token::ABRECHAVE)
	{
		MembrosOpt();
		match(Token::FECHACHAVE);
	}
	else
		error();
}

void Parser::MembrosOpt() {
	match(Token::ABRECHAVE);

	if (lookahead.type == Token::STRING) {
		Pares();
	}
	else
		;
}

void Parser::Pares() {
	Par();
	P_();
}

void Parser::Par() {
	match(Token::STRING);
	match(Token::DOISPONTOS);

	Valor();
}

void Parser::P_() {
	if (lookahead.type == Token::VIRGULA) {
		match(Token::VIRGULA);

		Par();
		P_();
	}
	else
		;
}

void Parser::Array() {
	if (lookahead.type == Token::ABRECOLCHETE)
	{
		ElementosOpt();
		match(Token::FECHACOLCHETE);
	}
	else
		error();
}

void Parser::ElementosOpt() {
	match(Token::ABRECOLCHETE);

	if (lookahead.type == Token::ABRECHAVE ||
		lookahead.type == Token::ABRECOLCHETE ||
		lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == Token::_FALSE ||
		lookahead.type == Token::_NULL
		) {
		Elementos();
	}
	else
		;
	
}

void Parser::Elementos() {
	Valor();
	E_();
}

void Parser::E_() {
	if (lookahead.type == Token::VIRGULA) {
		match(Token::VIRGULA);
		
		Valor();
		E_();
	}
	else
		;
}

Token Parser::nextToken() {
	//"Come" os espaços em branco
	while (isspace(*buffer))
		if (*buffer++ == '\n')
			++lineNumber;

	Token t;

	//Fim da string de parsing
	if (*buffer == '\0') {
		t.type = Token::_EOF;
		return t;
	}

	//Marca o começo de uma lexeme
	char* beginLexeme = buffer;
	
	//Teste se o token é true
	if (*buffer == 't') {
		for (int i = 0; i < 4; i++)
			++buffer;
		t.type = Token::_TRUE;
		t.lexeme = string(beginLexeme, buffer);
		
		if (t.lexeme != "true")
			error();

		return t;
	}else if (*buffer == 'f') { //Testa se o token é false
		for (int i = 0; i < 5; i++)
			++buffer;
		t.type = Token::_FALSE;
		t.lexeme = string(beginLexeme, buffer);

		if (t.lexeme != "false")
			error();

		
		return t;
	}else if (*buffer == 'n') { //Testa se o token é null
		for (int i = 0; i < 4; i++)
			++buffer;
		t.type = Token::_NULL;
		t.lexeme = string(beginLexeme, buffer);

		if (t.lexeme != "null")
			error();

		return t;
	}else if (isdigit(*buffer) || *buffer == '-') {//É um número
		if (*buffer == '-') ++buffer;

		if (*buffer == '0' && isdigit(*(++buffer))) {
			error();
		}

		while (isdigit(*buffer))
			++buffer;

		if (*buffer == '.') { //Tem parte fracionária
			++buffer;
			
			if (!isdigit(*buffer)) error();//Tem que ter pelo menor um numero depois do ponto
			
			while (isdigit(*buffer))
				++buffer;
		}

		if (*buffer == 'e' || *buffer == 'E') {//Tem parte exponencial
			++buffer;

			if (*buffer == '+' || *buffer == '-')
				++buffer;
			
			if (!isdigit(*buffer)) error();//Tem que ter pelo menor um numero depois do sinal/expoente

			while (isdigit(*buffer))
				++buffer;
		}

		t.type = Token::NUMERO;
		t.lexeme= string(beginLexeme, buffer);

		return t;
	} else if (*buffer == '\"') { //É uma string
		++buffer;

		while (1) {
			if (!isascii(*buffer) || iscntrl(*buffer)) error();

			if (*buffer == '\\') {
				++buffer;

				switch (*buffer){
					case '\\':
					case 'n':
					case 't':
					case '\"':
						++buffer;
						continue;
					default:
						error();
						break;

				}
			}
			
			if (*buffer == '\"') {
				++buffer;
				break;
			}

			++buffer;
		}

		t.type = Token::STRING;
		t.lexeme = string(beginLexeme, buffer);

		return t;
	}
	
	char c = *buffer++;
	switch (c) {
		case '{':
			t.type = Token::ABRECHAVE;
			t.lexeme = string(beginLexeme, buffer);
			break;
		case '}':
			t.type = Token::FECHACHAVE;
			t.lexeme = string(beginLexeme, buffer);
			break;
		case '[':
			t.type = Token::ABRECOLCHETE;
			t.lexeme = string(beginLexeme, buffer);
			break;
		case ']':
			t.type = Token::FECHACOLCHETE;
			t.lexeme = string(beginLexeme, buffer);
			break;
		case ',':
			t.type = Token::VIRGULA;
			t.lexeme = string(beginLexeme, buffer);
			break;
		case ':':
			t.type = Token::DOISPONTOS;
			t.lexeme = string(beginLexeme, buffer);
			break;
	}

	return t;
}