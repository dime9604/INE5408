/* Copyright [2015] <Gustavo Tarciso da Silva>*/
//! Classe ListaDuplaCirc
/*! Classe que implementa uma estrutura em lista com alocação dinâmica
na memória, cujo os dados são distribuidos de forma espalhada. Ao contrário
da lista usando vetores, os dados não estão alocados em sequência, portanto,
necessitam de ponteiros indicando qual o próximo elemento da lista, e qual
o elemento anterior*/

#include "ElementoDuplo.hpp"

template<typename T>

class ListaDuplaCirc {
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
    Construtor da classe ListaDuplaCirc. A lista é criada vazia, iniciada
    com tamanho "0" e a cabeça vazia

    */
    ListaDuplaCirc() {
        size = 1;
        head = new ElementoDuplo<T>(0, 0, 0);
        head->setProximo(head);
        head->setAnterior(head);
    }
    //! Destrutor da Classe
    /*!
    Destrutor da classe ListaDuplaCirc. A lista é desalocada e seu tamanho
    passa a indicar "0"
    \sa ListaDuplaCirc(), destroiListaDuplo()
    */
    ~ListaDuplaCirc() {
        delete head;
        size = 1;
    }
    //! Método que adiciona um elemento no inicio da lista
    /*!
    \param dado um elemento a ser adicionado no inicio da lista
    \sa adicionaDuplo(), adicionaEmOrdemDuplo(), adicionaNaPosicaoDuplo()
    */
    void adicionaNoInicioDuplo(const T& dado) {
        ElementoDuplo<T> *aux = new ElementoDuplo<T>(dado, head->getProximo(),
         head);
        if (aux == NULL) {
            throw "elemento não alocado";
        }
        head->setProximo(aux);
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
        }
        aux = head->getProximo();
        dado = aux->getInfo();
        head->setProximo(aux->getProximo());
        head->getProximo()->setAnterior(head);
        size--;
        delete aux;
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
        head->setProximo(aux->getProximo());
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
        ElementoDuplo<T> *novo = new ElementoDuplo<T> (dado, head, NULL);
        ElementoDuplo<T> *anterior = head->getProximo();
        if (novo == NULL) {
            throw "posição inválida";
        }
        if (pos > size-1 || pos < 0) {
            throw "posição inválida";
        }
        if (pos == 0) {
            return adicionaNoInicioDuplo(dado);
        }
        for (int i = 0; i < pos-1; i++) {
            anterior = anterior->getProximo();
        }
        novo->setProximo(anterior->getProximo());
        novo->getProximo()->setAnterior(novo);
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
        ElementoDuplo<T> *aux = head->getProximo();
        if (listaVazia()) {
            throw "lista vazia";
        }
        int i = 0;
        while (i < size && aux->getInfo() != dado) {
            i++;
            aux = aux->getProximo();
        }
        if (i >= size) {
            throw "dado não existe";
        }
        return i;
    }
    /*! Método que retorna a posição de um determinado elemento da
    lista na memória*/
    /*!
    \param dado um elemento a ser verificado sua posição na memória
    \return aux um ponteiro auxiliar que aponta pro elemento verificado
    \sa posicaoDuplo()
    */
    T* posicaoMemDuplo(const T& dado) const {
        ElementoDuplo<T> *aux = head->getProximo();
        if (listaVazia()) {
            throw "lista vazia";
        }
        int i = 0;
        while (i < size && (aux->getInfo() != dado)) {
            i++;
            aux = aux->getProximo();
        }
        if (i >= size) {
            throw "dado não existe";
        }
        return aux;
        }
    //! Método que verifica se determinado elemento está contido na lista
    /*!
    \param dado um elemento a ser verificado se está contido na lista
    \return um valor boolean indicando se o dado está contido na lista
    \sa posicaoDuplo(), posicaoMemDuplo()
    */
    bool contemDuplo(const T& dado) {
        ElementoDuplo<T> *aux = head->getProximo();
        if (listaVazia()) {
            throw "lista vazia";
        }
        for (int i = 0; i < size; i++) {
            if (aux->getInfo() == dado) {
                return true;
            }
            aux = aux->getProximo();
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
        ElementoDuplo<T> *aux = head->getProximo();
        T dado;
        if (pos > size-1 || pos < 0) {
            throw "posicao invalida";
        }
        if (pos == 0) {
            retiraDoInicioDuplo();
        }
        for (int i = 0; i < pos-1; i++) {
            aux = aux->getProximo();
        }
        elementoRetirado = aux->getProximo();
        dado = elementoRetirado->getInfo();
        aux->setProximo(elementoRetirado->getProximo());
        elementoRetirado->getProximo()->setAnterior(aux);
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
        adicionaNaPosicaoDuplo(dado, size-1);
    }
    //! Método que retira o ultimo elemento da lista
    /*!
    \return as informações do elemento retirado do fim da lista
    \sa retiraDoInicioDuplo(), eliminaDoInicioDuplo(),
    retiraDaPosicaoDuplo(), retiraEspecificoDuplo()
    */
    T retiraDuplo() {
        return retiraDaPosicaoDuplo(size-2);
    }
    //! Método que retira um elemento específico da lista
    /*!
    \param dado um elemento a ser retirado da lista
    \return as informações do dado retirado da lista
    \sa retiraDuplo(), retiraDoInicioDuplo(), eliminaDoInicioDuplo(),
    retiraDaPosicaoDuplo()
    */
    T retiraEspecificoDuplo(const T& dado) {
        try {
        return retiraDaPosicaoDuplo(posicaoDuplo(dado));
        } catch (std::exception& e) {
            throw e;
        }
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
        int i;
        while (i != pos) {
            aux = aux->getProximo();
            i++;
        }
        return aux->getInfo();
    }
    //! Método que adiciona um elemento na lista em uma determinada ordem
    /*!
    \param data um elemento a ser inserido em sequência na lista
    \sa adicionaDuplo(), adicionaNoInicioDuplo(), adicionaNaPosicaoDuplo()
    */
    void adicionaEmOrdem(const T& data) {
        ElementoDuplo<T> *aux = head->getProximo();
        if (listaVazia()) {
            return adicionaNoInicioDuplo(data);
        }
        int pos = 1;
        while (pos < size && maior(data, aux->getInfo())) {
            aux = aux->getProximo();
            pos++;
        }
        adicionaNaPosicaoDuplo(data, pos);
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
    \sa ListaDuplaCirc(), ~ListaDuplaCirc, destroiListaDuplo()
    */
    bool listaVazia() const {
        return (size == 1);
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
    \sa ListaDuplaCirc(), ~ListaDuplaCirc(), listaVazia()
    */
    void destroiListaDuplo() {
        for (int i = 0; i < size-1; i++) {
            eliminaDoInicioDuplo();
        }
    }
};

