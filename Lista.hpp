    /*Copyright [2015] <Gustavo Tarciso da Silva>*/
    //!Classe Lista
    /*!Classe que implementa uma estrutura do tipo lista utilizando vetores*/

    #define MAX_LISTA 100

    #define ERROLISTACHEIA -1
    #define ERROLISTAVAZIA -2
    #define ERROPOSICAO -3

    template <typename T>

    class Lista {
    private:
     //!Um vetor
     /*!Um vetor genérico usado para armazenar os dados da estrutura do tipo lista*/
      T* dados;
      //!Um atributo para definir posição
      /*!Atributo que define a posição atual do ultimo elemento da lista*/
      int ultimo;
      //!Um atributo para definir tamanho
      /*!Atributo que define o tamanho da estrutura do tipo lista*/
      int tamanho;

    public:
     //!Construtor
     /*!Construtor sem parâmetros que inicializa a lista com um tamanho estabelecido*/
    Lista() {
      ultimo = -1;
      tamanho = MAX_LISTA;
      dados = new T[tamanho];
    }
    //!Construtor
    /*!Construtor que inicia a lista com tamanho variavel
      \param tam o tamanho do vetor (quantidade máxima de elementos na lista)
      \sa Lista()
    */
    explicit Lista(int tam) {
      ultimo = -1;
      tamanho = tam;
      dados = new T[tamanho];
    }
    //!Método que adiciona um elemento no final da lista
    /*!
      \param dado um elemento a ser adicionado no final da lista
      \sa adicionaNoInicio(), adicionaNaPosicao(), adicionaEmOrdem(),
      retira(), retiraDoInicio(), retiraDaPosicao(), retiraEspecifico()
    */
    void adiciona(T dado) {
      if (listaCheia()) {
        throw ERROLISTACHEIA;
      } else {
        ultimo++;
        dados[ultimo] = dado;
      }
    }
    //!Método que adiciona um elemento no inicio da lista
    /*!
      \param dado um elemento a ser adicionado no inicio da lista
      \sa adiciona(), adicionaNaPosicao(), adicionaEmOrdem(),
      retira(), retiraDoInicio(), retiraDaPosicao(), retiraEspecifico()
    */
    void adicionaNoInicio(T dado) {
      int posicao;
      if (listaCheia()) {
        throw ERROLISTACHEIA;
      } else {
        ultimo++;
        posicao = ultimo;
        while (posicao > 0) {
          dados[posicao] = dados[posicao-1];
          posicao--;
        }
        dados[0] = dado;
      }
    }
    //!Método que adiciona um elemento em uma posição específica da lista
    /*!
      \param dado um elemento a ser adicionado na lista
      \param posicao a posição da lista onde um dado elemento será adicionado
      \sa adiciona(), adicionaNoInicio(), adicionaEmOrdem(),
      retira(), retiraDoInicio(), retiraDaPosicao(), retiraEspecifico()
    */
    void adicionaNaPosicao(T dado, int posicao) {
      int posicaoAuxiliar;
      if (listaCheia()) {
        throw ERROLISTACHEIA;
      } else if (posicao > ultimo+1 || posicao < 0) {
          throw ERROPOSICAO;
      } else {
          ultimo++;
          posicaoAuxiliar = ultimo;
          while (posicaoAuxiliar > posicao) {
            dados[posicaoAuxiliar] = dados[posicaoAuxiliar-1];
            posicaoAuxiliar--;
          }
          dados[posicao] = dado;
      }
    }
    //!Método que adiciona um elemento na lista levando em consideração uma ordem estabelecida
    /*!
      \param dado um elemento a ser adicionado na lista
      \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao(),
      retira(), retiraDoInicio(), retiraDaPosicao(), retiraEspecifico()
    */
    void adicionaEmOrdem(T dado) {
      int posicao = 0;
      if (listaCheia()) {
        throw ERROLISTACHEIA;
      } else {
        while (posicao <= ultimo && (dado > dados[posicao])) {
          posicao++;
        }
        adicionaNaPosicao(dado, posicao);
      }
    }
    //!Método que retira um elemento do fim da lista
    /*!
      \return um elemento que ocupava o final da lista
      \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao(), adicionaEmOrdem(),
      retiraDoInicio(), retiraDaPosicao(), retiraEspecifico()
    */
    T retira() {
      if (listaVazia()) {
        throw ERROLISTAVAZIA;
      }
      ultimo--;
      return dados[ultimo+1];
    }
    //!Método que retira um elemento do inicio da lista
    /*!
      \return um elemento que ocupava o inicio da lista
      \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao(), adicionaEmOrdem(),
      retira(), retiraDaPosicao(), retiraEspecifico()
    */
    T retiraDoInicio() {
      int posicaoAuxiliar = 0;
      T valor;
      if (listaVazia()) {
        throw ERROLISTAVAZIA;
      } else {
        ultimo--;
        valor = dados[0];
        while (posicaoAuxiliar <= ultimo) {
          dados[posicaoAuxiliar] = dados[posicaoAuxiliar+1];
          posicaoAuxiliar++;
        }
        return valor;
      }
    }
    //!Método que retira um elemento do inicio da lista
    /*!
      \param posicao a posicão na lista onde dado elemento será retirado
      \return um elemento que ocupava a posição escolhida na lista
      \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao(), adicionaEmOrdem(),
      retira(), retiraDoInicio(), retiraEspecifico()
    */
    T retiraDaPosicao(int posicao) {
      int posicaoAuxiliar;
      T valor;
      if (posicao > ultimo || posicao < 0) {
        throw ERROPOSICAO;
      } else if (listaVazia()) {
        throw ERROLISTAVAZIA;
      } else {
        ultimo--;
        valor = dados[posicao];
        posicaoAuxiliar = posicao;
        while (posicaoAuxiliar <= ultimo) {
          dados[posicaoAuxiliar] = dados[posicaoAuxiliar+1];
          posicaoAuxiliar++;
        }
        return valor;
      }
    }
    //!Método que retira um elemento específico da lista
    /*!
      \param dado um elemento específico a ser retirado da lista
      \return um elemento específico que foi retirado da lista
      \sa adiciona(), adicionaNoInicio(), adicionaNaPosicao(), adicionaEmOrdem(),
      retira(), retiraDoInicio(), retiraDaPosicao()
    */
    T retiraEspecifico(T dado) {
      int posicaoDado = 0;
      if (listaVazia()) {
        throw ERROLISTAVAZIA;
      } else {
        while (dado != dados[posicaoDado] && posicaoDado <= ultimo) {
            posicaoDado++;
          }
        }
        if (posicaoDado < 0) {
          throw ERROPOSICAO;
        } else {
          return retiraDaPosicao(posicaoDado);
        }
    }
    //!Método que identifica a posição do elemento a ser verificado
    /*!
      \param dado um elemento específico a ser verificado na lista
      \return um inteiro correspondente a posição do elemento a ser verificado
      \sa contem(), destroiLista()
    */
    int posicao(T dado) {
      int posicaoAuxiliar = 0;
      while (posicaoAuxiliar <= ultimo && !(dado == dados[posicaoAuxiliar])) {
        posicaoAuxiliar++;
      }
      if (posicaoAuxiliar > ultimo) {
        throw ERROPOSICAO;
      } else {
        return posicaoAuxiliar;
      }
    }
    //!Método que identifica se um dado elemento está na lista
    /*!
      \param dado um elemento específico a ser verificado na lista
      \return um boolean indicando se o elemento está contido na lista
      \sa posicao()
    */
    bool contem(T dado) {
      int posicaoDado = 0;
      if (listaVazia()) {
        throw ERROLISTAVAZIA;
      } else {
        while (dado != dados[posicaoDado] && posicaoDado <= ultimo) {
          posicaoDado++;
        }
      }
      return (dado == dados[posicaoDado]);
    }
    //!Método que compara dois elementos e verifica se são iguais
    /*!
      \param dado1 primeiro elemento a ser comparado
      \param dado2 segundo elemento a ser comparado
      \return um boolean indicando se os elementos são iguais
      \sa maior(), menor()
    */
    bool igual(T dado1, T dado2) {
      return (dado1 == dado2);
    }
    //!Método que compara dois elementos e verifica se o primeiro elemento é maior que o outro
    /*!
      \param dado1 primeiro elemento a ser comparado
      \param dado2 segundo elemento a ser comparado
      \return um boolean indicando se o primeiro elemento é maior que o segundo
      \sa igual(), menor()
    */
    bool maior(T dado1, T dado2) {
      return (dado1 > dado2);
    }
    //!Método que compara dois elementos e verifica se o primeiro elemento é menor que o outro
    /*!
      \param dado1 primeiro elemento a ser comparado
      \param dado2 segundo elemento a ser comparado
      \return um boolean indicando se o primeiro elemento é menor que o segundo
      \sa igual(), maior()
    */
    bool menor(T dado1, T dado2) {
      return (dado1 < dado2);
    }
    //!Método que informa se a lista está cheia
    /*!
      \return um boolean
      \sa listaVazia()
    */
    bool listaCheia() {
      return (ultimo == tamanho-1);
    }
    //!Método que informa se a lista está vazia
    /*!
      \return um boolean
      \sa listaCheia()
    */
    bool listaVazia() {
      return (ultimo == -1);
    }
    //!Método que limpa os elementos da lista
    /*!
      \sa posicao()
    */
    void destroiLista() {
      ultimo = -1;
    }
    };
