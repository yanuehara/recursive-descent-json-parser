#ifndef _AST_ARRAY_H
#define _AST_ARRAY_H

#include <iostream>
#include <list>
#include "ValueNode.h"

namespace AST {
	class Array : public ValueNode {
		private:
			list<ValueNode> elementos;
		public:
			Array() {
				//Default constructor
			}

			void insert(ValueNode& elemento) {
				elementos.push_front(elemento);
			}

			void write(Writer& write) const {
				write.write('[');
				write.tab();
				
				for (list<ValueNode>::const_iterator iterator = elementos.begin(); iterator != elementos.end(); iterator++) {
					iterator->write(write);

					if (elementos.size() == 1) {
						break;
					}

					write.write(L"%s", ',\n');
				}

				write.backspace();
				write.write(']');
			}
	};
}

#endif