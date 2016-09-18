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