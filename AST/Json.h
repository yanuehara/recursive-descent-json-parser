#include "Node.h"
#include "ValueNode.h"

namespace AST {
	class Json :public Node {
		private:
			ValueNodePtr value;
		public:
			Json() {
				value = nullptr;
			}
			void write(Writer& write) const {
				value->write(write);
			}
			void add(ValueNodePtr value) {
				this->value = value;
			}
	};
	typedef Json* JsonPtr;

}