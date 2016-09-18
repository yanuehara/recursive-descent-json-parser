#ifndef _AST_OBJECT_H
#define _AST_OBJECT_H

#include <iostream>
#include <list>
#include "ValueNode.h"
#include "Par.h"

namespace AST {
	class Object : public ValueNode {
		private:
			list<ParPtr> pares;
		public:
			Object() {
				//Default constructor
			}

			void insert(ParPtr par) {
				pares.push_back(par);
			}

			void write(Writer& write) const {
				write.beginBlock();

				int i = 0;
				for (list<ParPtr>::const_iterator iterator = pares.begin(); iterator != pares.end(); iterator++) {
					
					AST::ParPtr((*iterator))->write(write);

					if (pares.size() == 1) {
						break;
					}

					if (i == pares.size() - 1) {
						break;
					}
					
					write.write(",\n");
					i++;
				}
				write.endBlock();
			}
	};
	typedef Object* ObjectPtr;
}

#endif