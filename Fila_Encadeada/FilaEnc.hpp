	/* Copyright [2015] <Gustavo Tarciso da Silva> */
	//! Classe FilaEnc
	/*! Classe que implementa uma estrutura em Fila com alocação dinâmica
	na memória, cujo os dados são distribuidos de forma espalhada. Ao 
	contrário da fila usando vetores, os dados não estão alocados em sequência,
	portanto mecessitam de ponteiros indicando qual o próximo elemento da
	pilha*/

	#include "Elemento.hpp"
	
	template <typename T>
	
	class FilaEnc {
	 private:
		//! Um ponteiro de elemento do tipo genérico
		/*! Um atributo que representa o inicio da fila, indicando onde
		a fila começa*/
		Elemento<T> *inicio;
		//! Um ponteiro de elemento do tipo genérico
		/*! Um atributo que representa o fim da fila, apontando o ultimo
		elemento contido nela*/
		Elemento<T> *fim;
		//! Um atributo para indicar o tamanho da fila
		/*! Um inteiro que é sempre atualizando quando um elemento é
		adicionado ou retirado, informando o tamanho atual da lista*/
		int size;

	 public:
		//! Construtor da classe
		/*!
		Construtor da classe FilaEnc. A fila é criada vazia, iniciada
		com tamanho "0", inicio e fim vazios
		\sa ~FilaEnc(), limparFila()
		*/
		FilaEnc<T>() {
			inicio = NULL;
			fim = NULL;
			size = 0;
		}
		//! Destrutor da classe
		/*!
		Destrutor da classe FilaEnc. A fila é desalocada e seu tamanho
		passa a indicar "0"
		\sa FilaEnc(), limparFila()
		*/
		~FilaEnc() {
			delete inicio;
			size = 0;
		}
		//! Método que adiciona um elemento no fim da fila
		/*!
		\param dado um elemento a ser adicionado no fim da fila
		\sa retira()
		*/
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
		//! Método que retira um elemento do inicio da fila
		/*!
		\return dados as informações contidas no elemento removido da fila
		\sa inclui()
		*/
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
		//! Método que mostra as informações do ultimo elemento da fila
		/*!
		\return as informações do elemento do fim da fila
		\sa primeiro()
		*/
		T ultimo() {
			if (filaVazia()) {
				throw "fila vazia";
			}
			return fim->getInfo();
		}
		//! Método que mostra as informações do primeiro elemento da fila
		/*!
		\return as informações do elemento no inicio da fila
		\sa ultimo()
		*/
		T primeiro() {
			if (filaVazia()) {
				throw "fila vazia";
			}
			return inicio->getInfo();
		}
		//! Método que informa se a fila está vazia
		/*!
		\return um boolean informando se a lista está vazia
		\sa FilaEnc(), ~FilaEnc(), limparFila()
		*/
		bool filaVazia() {
			return (size == 0);
		}
		//! Método que desaloca todos os elementos da fila
		/*!
		\sa FilaEnc(), ~FilaEnc(), filaVazia()
		*/
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

