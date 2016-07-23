#include "parser.h"

void Parser::parse(const char* input) {
	buffer = const_cast<char*>(input);
	lineNumber = 1;
	lookahead = nextToken();
	Json();

	if (lookahead.type != Token::EOS)
		error();

	cout << "Parsing completo sem erros!" << endl;
	getchar();
}

void Parser::error() {
	cout << "ERRO na linha: " << lineNumber << " abortando... " << endl;
	cout << "Pressione qualquer tecla para sair" << endl;
	
	getchar();

	return -1;
}

void Parser::Json() {
	Valor();
}

void Parser::Valor() {
	//'{', '[', string, numero, TRUE, FALSE, null }
	switch (lookahead.type) {
	case Token::ABRECHAVE:
		Objeto();
		break;
	case Token::ABRECOLCHETE:
		Array();
		break;
	case Token::STRING:
	case Token::NUMERO:
	case Token::_TRUE:
	case Token::_FALSE:
	case Token::_NULL:
		break;
	}
}

void Parser::Objeto() {
	if (lookahead.type == Token::ABRECHAVE)
	{
		MembrosOpt();
		match('}');
	}
	else
		;
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
	if (lookahead.type = Token::VIRGULA) {
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
		;
}

void Parser::ElementosOpt() {
	match(Token::ABRECOLCHETE);

	if (lookahead.type == Token::ABRECHAVE ||
		lookahead.type == Token::ABRECOLCHETE ||
		lookahead.type == Token::STRING ||
		lookahead.type == Token::NUMERO ||
		lookahead.type == Token::_TRUE ||
		lookahead.type == _FALSE ||
		lookahead.type == _NULL
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
	if (lookahead.type = Token::VIRGULA) {
		match(Token::VIRGULA);
		
		Valor();
		E_();
	}
	else
		;
}