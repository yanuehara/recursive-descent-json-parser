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