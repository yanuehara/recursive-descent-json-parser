/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

parser.cpp: Implementa as funcoes das classes

Copyright (c) 2016 Yan Uehara
*/

#include "parser.h"
#include <iostream>

//Parser
void Parser::parse(const char* input) {
	buffer = const_cast<char*>(input);
	lineNumber = 1;
	
	cout << "Começando o parsing..." << endl;

	//Gera o primeiro token
	lookahead = nextToken();

	//Chama o entry-point da gramatica
	Json();

	//Se a funcao terminou mas o lookahead nao e EOF
	//gera um erro e termina
	if (lookahead.type != Token::_EOF)
		error();

	//Imprime as informacoes pedidas
	cout << "Parsing completo sem erros!" << endl;
	cout << "Total de Objetos: " << totalObject << endl;
	cout << "Total de Membros de objetos: " << totalObjectMembers << endl;
	cout << "Total de Arrays: " << totalArray << endl;
	cout << "Total de membros de array: " << totalArrayMembers << endl;

	getchar();
}

//Mostra o aviso de erro com a linha do erro e termina
void Parser::error() {
	cout << "ERRO na linha: " << lineNumber << " abortando... " << endl;
	cout << "Pressione qualquer tecla para sair" << endl;
	
	getchar();

	exit(EXIT_FAILURE);
}

//Entry-point da gramatica
// Json: Valor;
void Parser::Json() {
	Valor();
}

//Parse do Valor
void Parser::Valor() {
	if(lookahead.type == Token::ABRECHAVE)
		Objeto(); //Objeto
	else if(lookahead.type == Token::ABRECOLCHETE)
		Array(); //Array
	else if (lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == Token::_FALSE ||
		lookahead.type == Token::_NULL
		) {
		advance(); //Consome
	}
}

//Faz o parsing de um objeto
void Parser::Objeto() {
	if (lookahead.type == Token::ABRECHAVE)
	{
		totalObject++; //Adiciona 1 ao total de objetos

		MembrosOpt(); //Chama a funcao para fazer o parsing dos membros
		match(Token::FECHACHAVE); //Da match em '}'
	}
	else
		error();
}

void Parser::MembrosOpt() {
	match(Token::ABRECHAVE); //Consome o '{'

	if (lookahead.type == Token::STRING) { //Membro e um par
		Pares(); //Chama a funcao para fazer o parsing
	}
	else
		; //Ou e vazio
}

void Parser::Pares() { //Chama o par e remove a recursao mais a esquerda
	Par();
	P_();
}

void Parser::Par() {
	totalObjectMembers++; //Adiciona 1 ao total de membros de um objeto

	match(Token::STRING); //Consome a string
	match(Token::DOISPONTOS); //Consome o ':'

	Valor(); //Chama a funcao para fazer o parsing
}

void Parser::P_() {
	if (lookahead.type == Token::VIRGULA) {
		match(Token::VIRGULA); //Consome a ','

		Par(); //Faz o parsing de um par
		P_(); //Continua a fazer o parsing da lista (se ela continuar)
	}
	else
		; //Ou e vazio
}

//Faz o parsing de um array
void Parser::Array() {
	if (lookahead.type == Token::ABRECOLCHETE)
	{
		totalArray++; //Soma 1 ao total de arrays

		ElementosOpt(); //Chama a funcao para fazer o parsing dos elementos
		match(Token::FECHACOLCHETE); //Consome o ']'
	}
	else
		error();
}

void Parser::ElementosOpt() {
	match(Token::ABRECOLCHETE); //Consome o '{'

	if (lookahead.type == Token::ABRECHAVE ||
		lookahead.type == Token::ABRECOLCHETE ||
		lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == Token::_FALSE ||
		lookahead.type == Token::_NULL
		) {
		Elementos(); //Chama a funcao para fazer o parsing
	}
	else
		; //Ou e vazio
	
}

void Parser::Elementos() {
	totalArrayMembers++; //Soma 1 ao total de elementos de array

	Valor(); //Faz o parsing do valor
	E_(); //Continua a fazer o parsing dos elementos (se existirem)
}

void Parser::E_() {
	if (lookahead.type == Token::VIRGULA) {
		match(Token::VIRGULA); //Consome uma ','
		
		totalArrayMembers++; //Soma 1 ao total de elementos

		Valor(); //Faz o parsing do valor
		E_(); //Continua a fazer o parsing dos elementos (se existirem)
	}
	else
		; //Ou e vazio
}

//Analisador sintatico
Token Parser::nextToken() {
	//"Come" os espaços em branco
	while (isspace(*buffer))
		if (*buffer++ == '\n')
			++lineNumber;

	Token t; //Declara um token

	//Fim da string de parsing
	if (*buffer == '\0') {
		t.type = Token::_EOF;
		return t;
	}

	//Marca o começo de uma lexeme
	char* beginLexeme = buffer;
	
	//Testa se o token é true
	if (*buffer == 't') {
		for (int i = 0; i < 4; i++)
			++buffer;
		t.type = Token::_TRUE; //Associa o tipo
		t.lexeme = string(beginLexeme, buffer); //Gera a lexeme
		
		if (t.lexeme != "true")
			error(); //Token incorreto, da erro

		return t; //Retorna
	}else if (*buffer == 'f') { //Testa se o token é false
		for (int i = 0; i < 5; i++)
			++buffer;
		t.type = Token::_FALSE; //Associa o tipo
		t.lexeme = string(beginLexeme, buffer); //Gera a lexeme

		if (t.lexeme != "false")
			error(); //Token incorreto, da erro

		
		return t; //Retorna
	}else if (*buffer == 'n') { //Testa se o token é null
		for (int i = 0; i < 4; i++)
			++buffer;
		t.type = Token::_NULL; //Associa o tipo
		t.lexeme = string(beginLexeme, buffer); //Gera a lexeme

		if (t.lexeme != "null") //Token incorreto da erro
			error();

		return t; //Retorna
	}else if (isdigit(*buffer) || *buffer == '-') {//Testa se o token e um numero
		if (*buffer == '-') ++buffer; //Se o numero for negativo consome o '-'

		//Testa se o numero comeca com 0, considerado invalido
		if (*buffer == '0' && isdigit(*(++buffer))) {
			error();
		}

		//Consome os digitos
		while (isdigit(*buffer))
			++buffer;
		
		//Tem parte fracionária
		if (*buffer == '.') {
			++buffer; //Consome o '.'
			
			if (!isdigit(*buffer)) error();//Tem que ter pelo menor um numero depois do ponto
			
			//Consome os outros digitos
			while (isdigit(*buffer))
				++buffer;
		}

		//Tem parte exponencial
		if (*buffer == 'e' || *buffer == 'E') {
			++buffer; //Consome o 'e' ou 'E's

			if (*buffer == '+' || *buffer == '-') //Testa se tem sinal e consome
				++buffer;
			
			if (!isdigit(*buffer)) error();//Tem que ter pelo menor um numero depois do sinal/expoente

			//Consome o resto dos digitos
			while (isdigit(*buffer))
				++buffer;
		}

		t.type = Token::NUMERO; //Associa o tipo
		t.lexeme= string(beginLexeme, buffer); //Gera a lexeme

		return t; //Retorna
	} else if (*buffer == '\"') { //É uma string
		++buffer;

		while (1) {
			if (!isascii(*buffer) || iscntrl(*buffer)) error(); //Se o caracter nao for ascii ou for de controle, da erro

			if (*buffer == '\\') { //Testa se o caracter é '\'
				++buffer; //Consome

				switch (*buffer){ //Deve ser seguida de outra barra, n, t, ou "
					case '\\':
					case 'n':
					case 't':
					case '\"':
						++buffer; //Consome e passa pra prox intercao
						continue;
					default: //Senao gera um erro
						error();
						break;

				}
			}
			
			//Testa o final da string
			if (*buffer == '\"') {
				++buffer;
				break;
			}

			++buffer;
		}

		t.type = Token::STRING; //Associa o tipo
		t.lexeme = string(beginLexeme, buffer); //Gera a lexeme

		return t; //Retorna
	}
	
	//Se nao cair em nenhum dos casos acima, e um caracter simples
	//Pega o caracter
	char c = *buffer++;
	
	//Faz o match e associa o tipo
	switch (c) {
		case '{':
			t.type = Token::ABRECHAVE;
			break;
		case '}':
			t.type = Token::FECHACHAVE;
			break;
		case '[':
			t.type = Token::ABRECOLCHETE;
			break;
		case ']':
			t.type = Token::FECHACOLCHETE;
			break;
		case ',':
			t.type = Token::VIRGULA;
			break;
		case ':':
			t.type = Token::DOISPONTOS;
			break;
	}
	
	t.lexeme = string(beginLexeme, buffer); //Gera a lexeme
	
	return t; //Retorna
}