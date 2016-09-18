#ifndef _AST_PAR_H
#define _AST_PAR_H

#include <string>
#include "Node.h"
#include "String.h"

using namespace std;

namespace AST {
	class Par : public Node {
		private:
			String* chave ;
			ValueNodePtr valor;
		public:
			Par() {
				//Default constructor
			}
			
			Par(String* chave, ValueNodePtr valor) {
				this->chave = chave;
				this->valor = valor;
			}
			
			void setChave(String* chave) {
				this->chave = chave;
			}

			void setValor(ValueNodePtr valor) {
				this->valor = valor;
			}

			void write(Writer& write) const {
				chave->write(write);
				write.write(':');
				valor->write(write);
			}
	};
}

#endif