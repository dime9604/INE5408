    /*Copyright [2015] <Gustavo Tarciso da Silva>*/
    //! Classe ListaEnc
    /*! Classe que implementa uma estrutura em Lista com alocação dinâmica
    na memória, cujo os dados são distribuidos de forma espalhada. Ao contrário
    da lista usando vetores, os dados não estão alocados em sequência, portanto
    necessitam de ponteiros indicando qual o próximo elemento da lista*/

    #include "Elemento.hpp"

    template<typename T>

    class ListaEnc {
    private:
     //! Um ponteiro de elemento do tipo genérico
     /*! Um atributo que representa a cabeça da lista, indicando onde
     a lista começa*/
     Elemento<T> *head;
     //! Um atributo para indicar o tamanho da lista
     /*! Um inteiro que é sempre atualizado sempre que um elemento é
     adicionado ou retirado, informando o tamanho atual da lista*/
     int size;

    public:
     //! Construtor
     /*!
     Construtor da classe ListaEnc. A lista é criada vazia, iniciada
     com tamanho "0" e a cabeça vazia
     \sa ~ListaEnc(), destroiLista()
     */
    ListaEnc() {
    		size = 0;
    		head = NULL;
    }
    //! Destrutor
    /*!
    Destrutor da classe ListaEnc. A lista é desalocada e seu tamanho
    passa a indicar "0"
    \sa ListaEnc(), destroiLista()
    */
    ~ListaEnc() {
    	size = 0;
      delete head;
    }
    //! Método que adiciona um elemento no início da lista
    /*!
    \param dado um elemento a ser adicionado no início da lista
    \sa adiciona(), adicionaEmOrdem(), adicionaNaPosicao()
    */
    void adicionaNoInicio(const T& dado) {
    	Elemento<T> *aux = new Elemento<T>(dado, head);
    	if (aux != NULL) {
    		head = aux;
        size++;
    	} else {
    			throw "variavel não alocada";
    	}
    }
    /*! Métodos que retira um elemento do inicio da lista e desaloca o
    endereço de memória que estava sendo usado pelo elemento*/
    /*!
    \return dado as informações contidas no elemento que foi retirado da lista
    \sa eliminaDoInicio(), retira(), retiraDaPosicao(), retiraEspecifico()
    */
    T retiraDoInicio() {
      T dado;
      if (listaVazia()) {
    		throw "Lista vazia";
    	} else {
          //guarda as informações do elemento a ser retirado
    	    dado = head->getInfo();
          eliminaDoInicio();
    	    return dado;
    	}
    }
    /*! Métodos que retira um elemento do inicio da lista e desaloca o
    endereço de memória que estava sendo usado pelo elemento*/
    /*!
    \sa retiraDoInicio(), retira(), retiraDaPosicao(), retiraEspecifico()
    */
    void eliminaDoInicio() {
    	Elemento<T> *aux;
      if (listaVazia()) {
    		throw "Lista vazia";
    	} else {
          //aux aponta para o endereço de head
    		   aux = head;
           size--;
           //head passa a apontar pro próximo elemento da lista
           head = aux->getProximo();
           /*desaloca o ponteiro auxiliar e o elemento para qual ele
           apontava (o antigo primeiro elemento da lista)*/
           delete aux;
    	}
    }
    //! Método que adiciona um elemento numa dada posição desejada na lista
    /*!
    \param dado um elemento a ser inserido
    \param pos a posição onde o dado vai ser inserido
    \sa adiciona(), adicionaNoInicio(), adicionaEmOrdem()
    */
    void adicionaNaPosicao(const T& dado, int pos) {
    	Elemento<T> *anterior, *novo;
      if (pos > size || pos < 0) {
    		throw "Posição inválida";
    	} else {
    		if (pos == 0) {
    			return adicionaNoInicio(dado);
    		} else {
          //aloca um novo elemento
          novo = new Elemento<T> (dado, NULL);
          //testa se o elemento foi alocado
          if (novo != NULL) {
    			anterior = head;
          //percorre a lista até chegar na posição onde o dado deve ser inserido
    			for (int i = 0; i < pos-1; i++) {
            anterior = anterior->getProximo();
    			}
          //elemento inserido passa a apontar para o próximo elemento da lista
          novo->setProximo(anterior->getProximo());
    			//elemento anterior ao dado inserido passa a apontar pra ele
          anterior->setProximo(novo);
    			size++;
    		} else {
          throw "Dado não alocado";
        }
    	}
     }
    }
    //! Método que retorna a posição de um determinado elemento na lista
    /*!
    \param dado um elemento a ser verificado sua posição na lista
    \return cont um contador indicando a posição do elemento na lista
    \sa posicaoMem()
    */
    int posicao(const T& dado)  const {
    	if (listaVazia()) {
    		throw "Lista vazia";
    	}
      //contador da posição
    	int cont = 0;
      //ponteiro auxiliar para percorrer a lista
    	Elemento <T> *aux = head;
    	while (cont < size && !(dado == aux->getInfo())) {
    		cont++;
        aux = aux->getProximo();
    	}
    	if (cont >= size) {
              throw "Dado não existente";
          } else {
              return cont;
          }
    }
    /*! Método que retorna a posição de um determinado elemento da
    lista na memória*/
    /*!
    \param dado um elemento a ser verificado sua posição na memória
    \return aux um ponteiro auxiliar que aponta pro elemento verificado
    \sa posicao()
    */
    T* posicaoMem(const T& dado) const {
    	if (listaVazia()) {
    		throw "Lista vazia";
    	}
      //ponteiro auxiliar para percorrer a lista
    	Elemento <T> *aux = head;
      //contador da posição
      int cont = 0;
    	while (cont < size && !(dado == aux->getInfo())) {
    		cont++;
           aux = aux->getProximo();
    	}
      if (cont > size) {
        throw "Erro na posição";
      } else {
        return aux;
      }
    }
    //! Método que verifica se determinado elemento está contido na lista
    /*!
    \param dado um dado a ser verificado se ele está contido na lista
    \return um valor boolean indicando se o dado está contido na lista
    \sa posicao(), posicaoMem()
    */
    bool contem(const T& dado) {
        if (listaVazia()) {
          throw "Lista vazia";
        }
        //ponteiro auxiliar para percorrer a lista
        Elemento<T> *aux = head;
        for (int i = 0; i < size; i++) {
          if (aux->getInfo() == dado) {
            return true;
            aux = aux->getProximo();
          }
        }
        return false;
    }
    //! Método que retira um elemento de uma posição determinada da lista
    /*!
    \param pos um inteiro indicando a posição do elemento a ser retirado
    \return dado um elemento a ser retirado da lista
    \sa retira(), retiraDoInicio(), retiraEspecifico()
    */
    T retiraDaPosicao(int pos) {
      T dado;
      Elemento <T> *anterior, *elementoRetirado;
      if (listaVazia()) {
        throw "Lista vazia";
      } else if (pos > size+1) {
        throw "Posição inválida";
      } else {
        if (pos == 0) {
          return retiraDoInicio();
        } else {
          anterior = head;
          for (int i = 0; i < pos-1; i++) {
    				anterior = anterior->getProximo();
    			}
          //ponteiro auxiliar que aponta pro dado a ser retirado
          elementoRetirado = anterior->getProximo();
          dado = elementoRetirado->getInfo();
          anterior->setProximo(elementoRetirado->getProximo());
          size--;
          //desaloca o ponteiro auxiliar e o elemento retirado da lista
          delete elementoRetirado;
          return dado;
        }
      }
    }
    //! Método que adiciona um elemento no final da lista
    /*!
    \param dado um elemento a ser adicionado no fim da lista
    \sa adicionaNoInicio(), adicionaEmOrdem(), adicionaNaPosicao()
    */
    void adiciona(const T& dado) {
      if (listaVazia()) {
        adicionaNoInicio(dado);
      } else {
      adicionaNaPosicao(dado, size);
      }
    }
    //! Método que retira o elemento do fim da lista
    /*!
    \return as informações do elemento retirado do fim da lista
    \sa retiraDoInicio(), eliminaDoInicio(),
    retiraDaPosicao(), retiraEspecifico()
    */
    T retira() {
      if (listaVazia()) {
        throw "Lista vazia";
      } else {
        try {
    	      return retiraDaPosicao(size-1);
        } catch (std::exception& e) {
          throw e;
        }
      }
    }
    //! Método que retira um elemento específico da lista
    /*!
    \param dado um elemento a ser retirado da lista
    \return as informações do dado retirado da lista
    \sa retira(), eliminaDoInicio(), retiraDoInicio(), retiraDaPosicao()
    */
    T retiraEspecifico(const T& dado) {
      if (listaVazia()) {
        throw "Lista vazia";
      }
      try {
        return retiraDaPosicao(posicao(dado));
      } catch (std::exception& e) {
        throw e;
      }
    }
    //! Método que adiciona um dado na lista seguindo uma determinada sequência
    /*!
    \param data um elemento a ser inserido seguindo uma determinada sequência
    \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao()
    */
    void adicionaEmOrdem(const T& data) {
      //ponteiro auxiliar para percorrer a lista
      Elemento<T>* atual;
      if (listaVazia()) {
        adicionaNoInicio(data);
      } else {
        atual = head;
        int pos = 1;
        while (pos < size && maior(data, atual->getInfo())) {
          atual = atual->getProximo();
          pos++;
        }
          adicionaNaPosicao(data, pos);
      }
    }
    //! Método que verifica se a lista está vazia
    /*!
    \return um boolean informando se a lista está vazia
    \sa ListaEnc(), ~ListaEnc(), destroiLista()
    */
    bool listaVazia() const {
    	return (size == 0);
    }
    //! Método que compara e verifica se dois elementos são iguais
    /*!
    \param dado1 primeiro dado a ser comparado
    \param dado2 segundo dado a ser comparado
    \return um boolean informando se os dados comparados são iguais
    \sa maior(), menor()
    */
    bool igual(T dado1, T dado2) {
    	return (dado1 == dado2);
    }
    //! Método que compara e verifica se o primeiro elemento é maior que o segundo
    /*!
    \param dado1 primeiro dado a ser comparado
    \param dado2 segundo dado a ser comparado
    \return um boolean informando se o primeiro elemento é maior que o segundo
    \sa igual(), menor()
    */
    bool maior(T dado1, T dado2) {
    	return (dado1 > dado2);
    }
    //! Método que compara e verifica se o primeiro elemento é menor que o segundo
    /*!
    \param dado1 primeiro dado a ser comparado
    \param dado2 segundo dado a ser comparado
    \return um boolean informando se o primeiro elemento é menor que o segundo
    \sa igual(), maior()
    */
    bool menor(T dado1, T dado2) {
    	return (dado1 < dado2);
    }
    //! Método que desaloca todos os elementos da lista
    /*
    \sa ListaEnc(), ~ListaEnc(), listaVazia()
    */
    void destroiLista() {
    	while(!listaVazia()) {
    		eliminaDoInicio();
    	}
    }
    };
