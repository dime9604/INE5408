/* Copyright [2015] <Gustavo Tarciso da Silva>*/
//! Classe ElementoDuplo
/*! Classe que implementa um objeto elemento duplo usado para definir
uma estrutura encadeada, tendo ponteiros que indicam o próximo e
o anterior deste elemento na estrutura*/

#ifndef ELEMENTODUPLO_HPP
#define ELEMENTODUPLO_HPP

#include <stdlib.h>

template<typename T>

class ElementoDuplo {
	private:
	//! Um elemento genérico
	/*! Um atributo contendo as informações do elemento*/
	T *info;
	//! Um ponteiro de elementoDuplo do tipo genérico
	/*! Um atributo que aponta pro elemento na frente deste*/
	ElementoDuplo<T> *_next;
	//! Um ponteiro de elementoDuplo do tipo genérico
	/*! Um atributo que aponta pro elemento anterior a este*/
	ElementoDuplo<T> *_previous;

	public:
	//! Construtor da classe
	/*! Construtor com os 3 parâmetros para criação de um Elemento duplo*/
	ElementoDuplo(const T& info, ElementoDuplo<T> *next,ElementoDuplo<T>
	*previous) : info(new T(info)), _next(next), _previous(previous) {}
	//! Destrutor da classe
	/*! Destrutor da classe ElementoDuplo. Desaloca as informações do elemento*/
	~ElementoDuplo() {
		delete info;
	}
	//! Método que informa o próximo elemento na estrutura encadeada
	/*!
	\return próximo elemento da estrutura
	\sa getAnterior(), getInfo()
	*/
	ElementoDuplo<T> *getProximo() const {
		return _next;
	}
	//! Método que informa o elemento anterior na estrutura encadeada
	/*!
	\return elemento anterior da estrutura
	\sa getProximo(), getInfo()
	*/
	ElementoDuplo<T> *getAnterior() const {
		return _previous;
	}
	//! Método que retorna as informações do ElementoDuplo
	/*!
	\return as informações do elemento
	\sa getProximo(), getAnterior()
	*/
	T getInfo() const {
		return *info;
	}
	//! Método que define o próximo elemento na estrutura encadeada
	/*!
	\param next o próximo elemento da estrutura encadeada
	\sa setAnterior()
	*/
	void setProximo(ElementoDuplo<T> *next) {
		_next = next;
	}
	//! Método que define o elemento anterior na estrutura encadeada
	/*!
	\param previous o elemento anterior da estrutura encadeada
	\sa setProximo()
	*/
	void setAnterior(ElementoDuplo<T> *previous) {
		_previous = previous;
	}
};

#endif

