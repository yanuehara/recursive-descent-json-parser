#ifndef _AST_NUMERO_H
#define _AST_NUMERO_H

#include <string>
#include "ValueNode.h"
#include "..\utils\Writer.h"

namespace AST {
	class Numero : public ValueNode {
	public:
		Numero(string lexeme) : ValueNode(lexeme) {
		}
		void write(Writer& write) const {
			write.write('"');
			ValueNode::write(write);
			write.write('"');
		}
	};
}

#endif // !_AST_NUMERO_H
