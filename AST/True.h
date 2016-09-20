/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

True.h: True class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_TRUE_
#define _AST_TRUE_H

#include "Node.h"
#include "ValueNode.h"

namespace AST {
	class True : public ValueNode{
		public:
			True() : ValueNode("true") {
			}
	};
}

#endif