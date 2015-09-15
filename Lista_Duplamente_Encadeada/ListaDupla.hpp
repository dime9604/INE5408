#include "ElementoDuplo.hpp"

template<typename T>

class ListaDupla {
 private:
    ElementoDuplo<T> *head;
    int size;

 public:
	ListaDupla() {
		head = NULL;
		size = 0;
	}
	~ListaDupla() {
		delete head;
		size = 0;
	}
	void adicionaNoInicioDuplo(const T& dado) {
		ElementoDuplo<T> *aux = new ElementoDuplo<T>(dado, head, NULL);
		if (aux == NULL) {
			throw "elemento não alocado";
		}
		head = aux;
		if (aux->getProximo() != NULL){
			aux->setProximo(aux);
			aux->setAnterior(aux);
		}
		size++;
	}
	T retiraDoInicioDuplo() {
		ElementoDuplo<T> *aux;
		T dado;
		if (listaVazia()) {
			throw "lista vazia";
		} else {
			aux = head;
			dado = head->getInfo();
			head = aux->getProximo();
			if (head != NULL) {
				head->setAnterior(NULL);
			}
			size--;
			delete aux;
		}
		return dado;
	}
	void eliminaDoInicioDuplo() {
		ElementoDuplo<T> *aux;
		if (listaVazia()) {
			throw "lista vazia";
		}
		aux = head;
		head = aux->getProximo();
		if (head != NULL) {
			head->setAnterior(NULL);
		}
		size--;
		delete aux;
	}
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		ElementoDuplo<T> *novo = new ElementoDuplo<T> (dado, NULL, NULL);
		ElementoDuplo<T> *anterior = head;
		if (novo == NULL) {
			throw "posição inválida";
		}
		if (pos > size || pos < 0) {
			throw "posição inválida";
		}
		if (pos == 0) {
			return adicionaNoInicioDuplo(dado);
		}
		for (int i = 0; i < pos-1; i++) {
			anterior = anterior->getProximo();
		}
		novo->setProximo(anterior->getProximo());
		if (novo->getProximo() != NULL) {
			novo->getProximo()->setAnterior(novo);
		}
		anterior->setProximo(novo);
		novo->setAnterior(anterior);
		size++;
	}
	int posicaoDuplo(const T& dado) const {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			throw "lista vazia";
		}
		for (int i = 0; i < size; i++) {
			if (dado != aux->getInfo()) {
				aux = aux->getProximo();
			} else {
				return i;
			}
		}
		throw "dado não encontrado";
	}
	T* posicaoMemDuplo(const T& dado) const {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			throw "lista vazia";
		}
		int pos = posicaoDuplo(dado);
		for (int i = 0; i < size; i++) {
			if (dado != aux->getInfo()) {
			aux = aux->getProximo();
			} else return &aux->getInfo();
		}
		throw "dado não encontrado";
	}
	bool contemDuplo(const T& dado) {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			throw "lista vazia";
		}
		for (int i = 0; i < size; i++) {
			if (igual(dado, aux->getInfo())) {
				return true;
			} else {
				aux = aux->getProximo();
			}
		}
    	return false;
	}
	T retiraDaPosicaoDuplo(int pos) {
		ElementoDuplo<T> *elementoRetirado;
		ElementoDuplo<T> *aux = head;
		T dado;
		if (pos > size || pos < 0) {
			throw "posicao invalida";
		}
		if (pos == 0) {
			retiraDoInicioDuplo();
		}
		for (int i = 0; i < pos-2; i++) {
			aux = aux->getProximo();
		}
		elementoRetirado = aux->getProximo();
		dado = elementoRetirado->getInfo();
		aux->setProximo(elementoRetirado->getProximo());
		if (elementoRetirado->getProximo() != NULL) {
			elementoRetirado->getProximo()->setAnterior(aux);
		}
		size--;
		delete elementoRetirado;
		return dado;
	}
	void adicionaDuplo(const T& dado) {
		adicionaNaPosicaoDuplo(dado, size);
	}
	T retiraDuplo() {
		return retiraDaPosicaoDuplo(size);
	}
	T retiraEspecificoDuplo(const T& dado) {
		if (listaVazia()) {
			throw "lista vazia";
		}
		return retiraDaPosicaoDuplo(posicaoDuplo(dado)+1);
	}
	T mostra(int pos) {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			throw "lista vazia";
		}
		for (int i = 0; i < pos; i++) {
			aux = aux->getProximo();
		}
		return aux->getInfo();
	}
	void adicionaEmOrdem(const T& data) {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			return adicionaNoInicioDuplo(data);
		}
		int pos = 1;
		while (aux->getProximo() != NULL && maior(data, aux->getInfo())) {
			aux = aux->getProximo();
			pos++;
		}
		if (maior(data, aux->getInfo())) {
			adicionaNaPosicaoDuplo(data, pos+1);
		} else {
			adicionaNaPosicaoDuplo(data, pos);
		}
	}
	int verUltimo() {
		return size;
	}
	bool listaVazia() const {
		return (size == 0);
	}
	bool igual(T dado1, T dado2) {
		return (dado1 == dado2);
	}
	bool maior(T dado1, T dado2) {
		return (dado1 > dado2);
	}
	bool menor(T dado1, T dado2) {
		return (dado1 < dado2);
	}
	void destroiListaDuplo() {
		while (!listaVazia()) {
			eliminaDoInicioDuplo();
		}
	}
};

