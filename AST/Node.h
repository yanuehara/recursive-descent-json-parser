/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

Node.h: Node class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_NODE_H
#define _AST_NODE_H

#include "..\utils\Writer.h"

namespace AST {
	class Node {
		public:
			virtual void write(Writer& write) const = 0;
	};
}

#endif