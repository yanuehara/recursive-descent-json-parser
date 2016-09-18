#ifndef _AST_ARRAY_H
#define _AST_ARRAY_H

#include <iostream>
#include <list>
#include "ValueNode.h"

namespace AST {
	class Array : public ValueNode {
		private:
			list<ValuePtr> elementos;
		public:
			Array() {
				//Default constructor
			}

			void insert(ValuePtr elemento) {
				elementos.push_back(elemento);
			}

			void write(Writer& write) const {
				write.write('[');
				write.tab();
				
				int i = 0;
				for (list<ValuePtr>::const_iterator iterator = elementos.begin(); iterator != elementos.end(); iterator++) {
					AST::ValuePtr((*iterator))->write(write);

					if (elementos.size() == 1) {
						break;
					}

					if (i == elementos.size() - 1) {
						break;
					}

					write.write(",\n");
					i++;
				}

				write.backspace();
				write.write(']');
			}
	};
	typedef Array* ArrayPtr;
}

#endif