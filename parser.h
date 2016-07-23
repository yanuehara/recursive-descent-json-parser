#include <string>

using namespace std;

class Token {
public:
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

	int type;
	string lexeme; // Lexeme

};

class Parser {
public:
	void parse(const char*);

private:
	Token lookahead; //Token corrente
	Token nextToken(); //Analisador léxico em si
	int lineNumber;
	char* buffer;

	void error();

	void advance() {
		lookahead = nextToken();
	}

	void match(int t) {
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
};