#include <iostream>
#include <list>
#include "ValueNode.h"
#include "Par.h"

namespace AST {
	class Object : public ValueNode {
		private:
			list<Par> pares;
		public:
			Object() {
				//Default constructor
			}

			void insert(Par& par) {
				pares.push_front(par);
			}

			void write(Writer& write) const {
				write.beginBlock();
				for (list<Par>::const_iterator iterator = pares.begin(); iterator != pares.end(); iterator++) {
					iterator->write(write);

					if (pares.size() == 1) {
						break;
					}
					
					write.write(L"%s",',\n');
				}
				write.endBlock();
			}
	};
}