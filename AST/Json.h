/*
Aluno: Yan Uehara de Moraes
RGA: 2014.1904.013-8

Json.h: Json class definition

Copyright (c) 2016 Yan Uehara
*/

#ifndef _AST_JSON_H
#define _AST_JSON_H

#include "Node.h"
#include "Value.h"

namespace AST {
	class Json :public Node {
		private:
			ValuePtr value;
		public:
			Json() : Node(){
				value = nullptr;
			}
			void write(Writer& write) const {
				value->write(write);
			}
			void add(ValuePtr value) {
				this->value = value;
			}
	};
	typedef Json* JsonPtr;

}

#endif