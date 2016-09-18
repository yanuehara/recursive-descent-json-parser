#include "Node.h"
#include "ValueNode.h"

namespace AST {
	class Value : public Node {
		private:
			ValueNodePtr value;
		public:
			Value() : Node(){
				value = nullptr;
			}
			void write(Writer& write) const {
				value->write(write);
			}
			void add(ValueNodePtr value) {
				this->value = value;
			}
	};
	typedef Value* ValuePtr;

}
