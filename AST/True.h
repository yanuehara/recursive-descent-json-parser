#include "Node.h"
#include "ValueNode.h"

namespace AST {
	class True : public ValueNode{
		public:
			True() : ValueNode("true") {
			}
	};
}