#include "ValueNode.h"

namespace AST {
	class False : public ValueNode {
	public:
		False() : ValueNode("false") {
		}
	};
}