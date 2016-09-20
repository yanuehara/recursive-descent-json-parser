/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

String.h: String class definition (AST::String)

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_STRING_H
#define _AST_STRING_H

#include "ValueNode.h"

namespace AST {
	class String : public ValueNode {
	public:
		String(string lexeme) : ValueNode(lexeme) {
		}
		void write(Writer& write) const {
			//write.write('"');
			ValueNode::write(write);
			//write.write('"');
		}
	};
}

#endif