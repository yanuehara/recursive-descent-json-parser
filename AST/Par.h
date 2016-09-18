#ifndef _AST_PAR_H
#define _AST_PAR_H

#include <string>
#include "Node.h"
#include "String.h"

using namespace std;

namespace AST {
	class Par : public Node {
		private:
			std::string chave;
			ValuePtr valor;
		public:
			Par() {
				//Default constructor
			}
			
			Par(std::string chave, ValuePtr valor) {
				this->chave = chave;
				this->valor = valor;
			}
			
			void setChave(std::string chave) {
				this->chave = chave;
			}

			void setValor(ValuePtr valor) {
				this->valor = valor;
			}

			void write(Writer& write) const {
				write.beginLine();
				write.write(chave);
				write.write(':');
				valor->write(write);
			}
	};
	typedef Par* ParPtr;
}

#endif