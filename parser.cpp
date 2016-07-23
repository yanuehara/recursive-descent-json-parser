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

void
Parser::Json()
{
	Valor();
}

void
Parser::Valor()
{
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

void
Parser::Objeto()
{
	if (lookahead.type == Token::ABRECHAVE)
	{
		MembrosOpt();
		match('}');
	}
	else
		;
}