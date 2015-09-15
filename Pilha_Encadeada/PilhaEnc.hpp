/* Copyright [2015] <Gustavo Tarciso da Silva> */
//! Classe PilhaEnc
/*! Classe que implementa uma estrutura em pilha com alocação dinâmica na 
memória, cujo os dados são distribuidos de forma espalhada. Ao contrário da
pilha usando vetores, os dados não estão alocados em sequência, portanto 
necessitam de ponteiros indicando qual o próximo elemento da lista*/

#include "Elemento.hpp"
template<typename T>

class PilhaEnc {
 private:
 	//! Um ponteiro de elemento do tipo genérico
	/*! Um atributo que representa o topo da pilha, indicando onde 
	os elementos devem entrar e sair na pilha*/
    Elemento<T> *top;
	//! Um atributo para indicar o tamanho da pilha
	/*! Um inteiro que é sempre atualizado quando um elemento é adicionado
	ou retirado, informando o tamanho atual da lista*/
    int size;

 public:
 	//! Construtor da classe
	/*!
	Construtor da classe PilhaEnc. A pilha é criada vazia, iniciada com tamanho
	"0" e o topo vazio
	\sa ~PilhaEnc(), limparPilha()
	*/
	PilhaEnc() {
		top = NULL;
		size = 0;
	}
	//! Destrutor da classe
	/*!
	Destrutor da classe PilhaEnc. A pilha é desalocada e seu tamanho passa
	a indica "0"
	\sa PilhaEnc(), limparPilha()
	*/
	~PilhaEnc() {
		size = 0;
		delete top;
	}
	//! Método que adiciona elementos no topo da pilha
	/*!
	\param dado um elemento a ser adicionado no topo da pilha
	\sa desempilha(), topo()
	*/
	void empilha(const T& dado) {
		Elemento<T> *aux = new Elemento<T>(dado, top);
		if (aux != NULL) {
			top = aux;
			size++;
		} else {
			throw "variavel não alocada";
		}
	}
	//! Método que retira elementos do topo da pilha
	/*!
	\return as informações do elemento retirado da pilha
	\sa empilha(), topo()
	*/
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
	//! Método que retorna as informações do elemento no topo da pilha
	/*!
	\return informações do elemento no topo da pilha
	\sa empilha(), desempilha()
	*/
	T topo() {
		if (PilhaVazia()) {
			throw "Pilha Vazia";
		}
		return top->getInfo();
	}
	//! Método que desaloca todos os elementos da pilha
	/*!
	\sa PilhaEnc(), ~PilhaEnc(), PilhaVazia()
	*/
	void limparPilha() {
		while (!PilhaVazia()) {
			desempilha();
		}
	}
	//! Método que verifica se a pilha está vazia
	/*!
	\return um boolean informando se a lista está vazia
	\sa PilhaEnc(), ~PilhaEnc(), limparPilha()
	*/
	bool PilhaVazia() {
		return (size == 0);
	}
};
