/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

Numero.h: Numero class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_NUMERO_H
#define _AST_NUMERO_H

#include <string>
#include "ValueNode.h"
#include "..\utils\Writer.h"

namespace AST {
	class Numero : public ValueNode {
	public:
		Numero(string lexeme) : ValueNode(lexeme) {
		}
		void write(Writer& write) const {
			ValueNode::write(write);
		}
	};
}

#endif // !_AST_NUMERO_H
