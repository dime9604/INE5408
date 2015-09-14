#include "Elemento.hpp"
template<typename T>

class PilhaEnc {
 private:
    Elemento<T> *top;
    int size;

 public:
	PilhaEnc() {
		top = NULL;
		size = 0;
	}
	~PilhaEnc() {
		size = 0;
		delete top;
	}
	void empilha(const T& dado) {
		Elemento<T> *aux = new Elemento<T>(dado, top);
		if (aux != NULL) {
			top = aux;
			size++;
		} else {
			throw "variavel não alocada";
		}
	}
	void desempilha() {
		Elemento<T> *aux;
		if (PilhaVazia()) {
			throw "pilha vazia";
		} else {
			aux = top;
			size--;
			top = aux-> getProximo();
			delete aux;
		}
	}
	T topo() {
		if (PilhaVazia()) {
			throw "Pilha Vazia";
		}
		return top->getInfo();
	}
	void limparPilha() {
		while (!PilhaVazia()) {
			desempilha();
		}
	}
	bool PilhaVazia() {
		return (size == 0);
	}
};
