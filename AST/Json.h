#include "Node.h"
#include "Value.h"

namespace AST {
	class Json :public Node {
		private:
			ValuePtr value;
		public:
			Json() {
				value = nullptr;
			}
			void write(Writer& write) const {
				value->write(write);
			}
			void add(ValuePtr value) {
				this->value = value;
			}
	};
	typedef Json* JsonPtr;

}