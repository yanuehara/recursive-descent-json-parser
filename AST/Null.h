/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

Null.h: Null class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_NULL_H
#define _AST_NULL_H

#include "ValueNode.h"

namespace AST {
	class Null : public ValueNode {
	public:
		Null() : ValueNode("null") {
		}
	};
}

#endif