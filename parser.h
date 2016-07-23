#include <string>

using namespace std;

class Token {
public:
	enum TokenType {
		EOS = 256,
		_EOF,
		_TRUE,
		_FALSE,
		_NULL,
		STRING,
		NUMERO,
		ABRECHAVE,
		FECHACHAVE,
		ABRECOLCHETE,
		FECHACOLCHETE,
		VIRGULA
	};

	int type;
	string lexeme; // Lexeme
	char c; // Valor de char simples

};

class Parser {
public:
	void parse(const char*);

private:
	Token lookahead; //Token corrente
	Token nextToken(); //Analisador léxico em si
	int lineNumber;

	void error();

	void advance()
	{
		lookahead = nextToken();
	}

	void match(int t)
	{
		if (lookahead.type == t)
			advance();
		else
			error();
	}

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
	void Boolean();

};