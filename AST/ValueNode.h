#ifndef _AST_VALUENODE_H
#define _AST_VALUENODE_H

#include <string>
#include "Node.h"
#include "..\utils\Writer.h"

using namespace std;

namespace AST {
	class ValueNode : public Node {
		private:
			string lexeme;
		public:
			ValueNode() {
				//Default constructor
			}

			ValueNode(string lexeme) {
				this->lexeme = lexeme;
			}

			void write(Writer& write) const {
				write.write(lexeme);
			}
	};
	typedef ValueNode* ValueNodePtr;

}

#endif