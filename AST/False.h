/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

False.h: False class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_FALSE_H
#define _AST_FALSE_H

#include "ValueNode.h"

namespace AST {
	class False : public ValueNode {
	public:
		False() : ValueNode("false") {
		}
	};
}

#endif