#include "ValueNode.h"

namespace AST {
	class Null : public ValueNode {
	public:
		Null() : ValueNode("null") {
		}
	};
}