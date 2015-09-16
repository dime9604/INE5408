/* Copyright [2015] <Gustavo Tarciso da Silva>*/
//! Classe ListaDupla
/*! Classe que implementa uma estrutura em lista com alocação dinâmica
na memória, cujo os dados são distribuidos de forma espalhada. Ao contrário
da lista usando vetores, os dados não estão alocados em sequência, portanto,
necessitam de ponteiros indicando qual o próximo elemento da lista, e qual
o elemento anterior*/

#include "ElementoDuplo.hpp"

template<typename T>

class ListaDupla {
 private:
	//! Um ponteiro de ElementoDuplo do tipo genérico
	/*! Um atributo que representa a cabeça da lista, indicando onde
	a lista começa*/
	ElementoDuplo<T> *head;
	//! Um atributo para indicar o tamanho da lista
	/*! Um inteiro que é sempre atualizado quando um elemento é adicionado
	ou retirado, informando o tamanho atual da lista*/
    int size;

 public:
 	//! Construtor da classe
	/*!
	Construtor da classe ListaDupla. A lista é criada vazia, iniciada
	com tamanho "0" e a cabeça vazia

	*/
	ListaDupla() {
		head = NULL;
		size = 0;
	}
	//! Destrutor da Classe
	/*!
	Destrutor da classe ListaDupla. A lista é desalocada e seu tamanho
	passa a indicar "0"
	\sa ListaDupla(), destroiListaDuplo()
	*/
	~ListaDupla() {
		delete head;
		size = 0;
	}
	//! Método que adiciona um elemento no inicio da lista
	/*!
	\param dado um elemento a ser adicionado no inicio da lista
	\sa adicionaDuplo(), adicionaEmOrdemDuplo(), adicionaNaPosicaoDuplo() 
	*/
	void adicionaNoInicioDuplo(const T& dado) {
		ElementoDuplo<T> *aux = new ElementoDuplo<T>(dado, head, NULL);
		if (aux == NULL) {
			throw "elemento não alocado";
		}
		head = aux;
		if (aux->getProximo() != NULL) {
			aux->setProximo(aux);
			aux->setAnterior(aux);
		}
		size++;
	}
	/*! Método que retira um elemento do inicio da lista e desaloca o
	endereço de memória que estava sendo usado pelo elemento*/
	/*!
	\return dado as informações contidas no elemento removido da lista
	\sa eliminaDoInicioDuplo(), retiraDuplo(), retiraDaPosicaoDuplo(),
	retiraEspecificoDuplo()
	*/
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
	/*! Método que retira um elemento do inicio da lista e desaloca o 
	endereço de memória que estava sendo usado pelo elemento*/
	/*!
	\sa retiraDoInicioDuplo(), retiraDuplo(), retiraDaPosicaoDuplo(),
	retiraEspecificoDuplo()
	*/
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
	//! Método que adiciona um elmento numa posição determinada
	/*!
	\param dado um elemento a ser inserido
	\param pos a posicao onde o dado vai ser inserido
	\sa adicionaDuplo(), adicionaNoInicioDuplo(), adicionaEmOrdemDuplo()
	*/
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
	//! Método que retorna a posição de um determinado elemento na lista
	/*!
	\param dado um elemento a ser verificado sua posição na lista
	\return i um contador indicando a posição do elemento na lista
	\sa posicaoMemDuplo()
	*/
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
	/*! Método que retorna a posição de um determinado elemento da 
	lista na memória*/
	/*!
	\param dado um elemento a ser verificado sua posição na memória
	\return aux um ponteiro auxiliar que aponta pro elemento verificado
	\sa posicaoDuplo()
	*/
	T* posicaoMemDuplo(const T& dado) const {
		ElementoDuplo<T> *aux = head;
		if (listaVazia()) {
			throw "lista vazia";
		}
		int pos = posicaoDuplo(dado);
		for (int i = 0; i < size; i++) {
			if (dado != aux->getInfo()) {
			aux = aux->getProximo();
			} else {
			    return &aux->getInfo();
		    }
		}
		throw "dado não encontrado";
	}
	//! Método que verifica se determinado elemento está contido na lista
	/*!
	\param dado um elemento a ser verificado se está contido na lista
	\return um valor boolean indicando se o dado está contido na lista
	\sa posicaoDuplo(), posicaoMemDuplo()
	*/
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
	//! Método que retira um elemento de uma posição determinada da lista
	/*!
	\param pos um inteiro indicando a posição do elemento a ser retirado
	\return dado as informações do elemento retirado da lista
	\sa retiraDuplo(), retiraDoInicioDuplo(),eliminaDoInicioDuplo(),
	retiraEspecificoDuplo()
	*/
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
	//! Método que adiciona um elemento no final da lista
	/*!
	\param dado um elemento a ser retirado do fim da lista
	\sa adicionaNoInicioDuplo(), adicionaEmOrdemDuplo(),
	adicionaNaPosicaoDuplo()
	*/
	void adicionaDuplo(const T& dado) {
		adicionaNaPosicaoDuplo(dado, size);
	}
	//! Método que retira o ultimo elemento da lista
	/*!
	\return as informações do elemento retirado do fim da lista
	\sa retiraDoInicioDuplo(), eliminaDoInicioDuplo(),
	retiraDaPosicaoDuplo(), retiraEspecificoDuplo()
	*/
	T retiraDuplo() {
		return retiraDaPosicaoDuplo(size);
	}
	//! Método que retira um elemento específico da lista
	/*!
	\param dado um elemento a ser retirado da lista
	\return as informações do dado retirado da lista
	\sa retiraDuplo(), retiraDoInicioDuplo(), eliminaDoInicioDuplo(),
	retiraDaPosicaoDuplo()
	*/
	T retiraEspecificoDuplo(const T& dado) {
		if (listaVazia()) {
			throw "lista vazia";
		}
		return retiraDaPosicaoDuplo(posicaoDuplo(dado)+1);
	}
	//! Método que mostra o elemento contido em determinada posição da lista
	/*!
	\param pos a posição do elemento na lista
	\return aux as informações do elemento contido na posição desejada
	\sa verUltimo()
	*/
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
	//! Método que adiciona um elemento na lista em uma determinada ordem
	/*!
	\param data um elemento a ser inserido em sequência na lista
	\sa adicionaDuplo(), adicionaNoInicioDuplo(), adicionaNaPosicaoDuplo()
	*/
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
	//! Método que informa o tamanho da lista
	/*!
	\return size o tamanho da lista
	\sa mostra()
	*/
	int verUltimo() {
		return size;
	}
	//! Método que informa se a lista está vazia
	/*!
	\return um valor boolean informando se a lista está ou não vazia
	\sa ListaDupla(), ~ListaDupla, destroiListaDuplo()
	*/
	bool listaVazia() const {
		return (size == 0);
	}
	//! Método que compara e verifica se dois elementos são iguais
	/*!
	\param dado1 primeiro elemento a ser comparado
	\param dado2 segundo elemento a ser comparado
	\return um boolean informando se os elementos são iguais
	\sa maior(), menor()
	*/
	bool igual(T dado1, T dado2) {
		return (dado1 == dado2);
	}
	//! Método que compara e verifica se um elemento é maior que o outro
	/*!
	\param dado1 primeiro elemento a ser comparado
	\param dado2 segundo elemento a ser comparado
	\return um boolean informando se o primeiro elemento é maior que 
	o segundo
	\sa igual(), menor()
	*/
	bool maior(T dado1, T dado2) {
		return (dado1 > dado2);
	}
	//! Método que compara e verifica se um elemento é menor que o outro
	/*!
	\param dado1 primeiro elemento a ser comparado
	\param dado2 segundo elemento a ser comparado
	\return um boolean informando se o primeiro elemento é menor que
	o segundo
	\sa igual(), maior()
	*/
	bool menor(T dado1, T dado2) {
		return (dado1 < dado2);
	}
	//! Método que desaloca todos os elementos da lista
	/*!
	\sa ListaDupla(), ~ListaDupla(), listaVazia()
	*/
	void destroiListaDuplo() {
		while (!listaVazia()) {
			eliminaDoInicioDuplo();
		}
	}
};

