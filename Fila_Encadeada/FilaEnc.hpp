#include "Elemento.hpp"
template <typename T>
class FilaEnc {
 private:
	Elemento<T> *inicio;
	Elemento<T> *fim;
	int size;

 public:
	FilaEnc<T>() {
		inicio = NULL;
		fim = NULL;
		size = 0;
	}
	~FilaEnc() {
		delete inicio;
		size = 0;
	}
	void inclui(const T& dado) {
		Elemento<T> *aux;
		aux = new Elemento<T>(dado, NULL);
		if (aux == NULL) {
			throw "fila cheia";
		} else {
		if (filaVazia()) {
			inicio = aux;
		} else {
			fim->setProximo(aux);
		}
		fim = aux;
		size++;
		}
	}
	T retira() {
		Elemento<T> *aux;
		T dado;
		if (filaVazia()) {
			throw "fila vazia";
		} else {
		aux = inicio;
		dado = aux->getInfo();
		inicio = aux->getProximo();
		}
		if (size == 1) {
			fim = NULL;
		}
		size--;
		delete aux;
		return dado;
	}
	T ultimo() {
		if (filaVazia()) {
			throw "fila vazia";
		}
		return fim->getInfo();
	}
	T primeiro() {
		if (filaVazia()) {
			throw "fila vazia";
		}
		return inicio->getInfo();
	}
	bool filaVazia() {
		return (size == 0);
	}
	void limparFila() {
		if (filaVazia()) {
		    throw "lista vazia";
		} else {
		for (int i = 0; i < size; i++) {
		    Elemento<T> *aux;
		    aux = inicio;
		    inicio = aux->getProximo();
		    size--;
		    delete aux;
		    }
	    }
	    size = 0;
	}
};

