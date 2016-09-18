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