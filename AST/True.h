#ifndef _AST_TRUE_H
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