#ifndef _AST_NODE_H
#define _AST_NODE_H

#include "..\utils\Writer.h"

namespace AST {
	class Node {
		public:
			virtual void write(Writer& write) const = 0;
	};
}

#endif