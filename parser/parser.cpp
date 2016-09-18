/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

parser.cpp: Implementa as funcoes das classes

Copyright (c) 2016 Yan Uehara
*/

#include "parser.h"
#include <iostream>

//Parser
AST::JsonPtr Parser::parse(const char* input) {
	buffer = const_cast<char*>(input);
	lineNumber = 1;
	
	cout << "Começando o parsing..." << endl;

	//Gera o primeiro token
	lookahead = nextToken();

	AST::JsonPtr json = new AST::Json;

	//Chama o entry-point da gramatica
	Json(json);

	//Se a funcao terminou mas o lookahead nao e EOF
	//gera um erro e termina
	if (lookahead.type != Token::_EOF)
		error();

	//Imprime as informacoes pedidas
	/*
	cout << "Parsing completo sem erros!" << endl;
	cout << "Total de Objetos: " << totalObject << endl;
	cout << "Total de Membros de objetos: " << totalObjectMembers << endl;
	cout << "Total de Arrays: " << totalArray << endl;
	cout << "Total de membros de array: " << totalArrayMembers << endl;
	
	getchar();
	*/

	Writer write;
	json->write(write);
}

//Mostra o aviso de erro com a linha do erro e termina
void Parser::error() {
	cout << "ERRO na linha: " << lineNumber << " abortando... " << endl;
	cout << "Pressione qualquer tecla para sair" << endl;

	exit(EXIT_FAILURE);
}

//Entry-point da gramatica
// Json: Valor;
void Parser::Json(AST::JsonPtr json) {
	json->add(Valor());
}

//Parse do Valor
AST::ValuePtr Parser::Valor() {
	AST::ValuePtr value = new AST::Value;
	AST::ValueNodePtr valuenode = nullptr;

	switch (lookahead.type) {
		case Token::ABRECHAVE:
			valuenode = Objeto();
			break;
		case Token::ABRECOLCHETE:
			valuenode = Array();
			break;
		case Token::STRING:
			valuenode = new AST::String(lookahead.lexeme);
			advance();
			break;
		case Token::NUMERO:
			valuenode = new AST::Numero(lookahead.lexeme);
			advance();
			break;
		case Token::_TRUE:
			valuenode = new AST::True();
			advance();
			break;
		case Token::_FALSE:
			valuenode = new AST::False();
			advance();
			break;
		case Token::_NULL:
			valuenode = new AST::Null();
			advance();
			break;
		default:
			error();
	}

	value->add(valuenode);
	return value;
}

//Faz o parsing de um objeto
AST::ValueNodePtr Parser::Objeto() {
	AST::ValueNodePtr objeto = new AST::Object;
	
	if (lookahead.type == Token::ABRECHAVE)
	{
		totalObject++; //Adiciona 1 ao total de objetos

		MembrosOpt(objeto); //Chama a funcao para fazer o parsing dos membros

		match(Token::FECHACHAVE); //Da match em '}'
	}
	else
		error();
	
	return objeto;
}

void Parser::MembrosOpt(AST::ValueNodePtr objeto) {
	match(Token::ABRECHAVE); //Consome o '{'

	if (lookahead.type == Token::STRING) { //Membro e um par
		
		while (1) {

			AST::ObjectPtr(objeto)->insert(Par());

			if (lookahead.type == Token::VIRGULA) {
				match(Token::VIRGULA);
			} else {
				break;
			}
		}

	}
	else
		; //Ou e vazio
}

AST::ParPtr Parser::Par() {
	AST::ParPtr par = new AST::Par;

	par->setChave(lookahead.lexeme);
	match(Token::STRING);
	match(Token::DOISPONTOS); //Consome o ':'

	par->setValor(Valor());
	totalObjectMembers++; //Adiciona 1 ao total de membros de um objeto

	return par;
}

//Faz o parsing de um array
AST::ValueNodePtr Parser::Array() {
	AST::ValueNodePtr array = new AST::Array;

	if (lookahead.type == Token::ABRECOLCHETE)
	{
		totalArray++; //Soma 1 ao total de arrays

		ElementosOpt(array); //Chama a funcao para fazer o parsing dos elementos
		match(Token::FECHACOLCHETE); //Consome o ']'
	}
	else
		error();

	return array;
}

void Parser::ElementosOpt(AST::ValueNodePtr array) {
	match(Token::ABRECOLCHETE); //Consome o '{'

	if (lookahead.type == Token::ABRECHAVE ||
		lookahead.type == Token::ABRECOLCHETE ||
		lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == Token::_FALSE ||
		lookahead.type == Token::_NULL
		) {

		while (1) {

			AST::ArrayPtr(array)->insert(Elemento());

			if (lookahead.type == Token::VIRGULA) {
				match(Token::VIRGULA); //Consome uma ','
			}
			else {
				break;
			}
		}
	}
	else
		; //Ou e vazio
	
}

AST::ValuePtr Parser::Elemento() {
	totalArrayMembers++; //Soma 1 ao total de elementos
	return Valor();
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