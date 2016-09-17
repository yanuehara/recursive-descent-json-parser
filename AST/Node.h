#include "..\utils\Writer.h"

namespace AST {
	class Node {
		public:
			virtual void write(Writer& write) const = 0;
	};
}