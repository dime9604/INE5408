    /*Copyright [2015] <Gustavo Tarciso da Silva>*/
    //!Classe Fila
    /*!Classe que implementa uma estrutura em Fila*/

    #define MAX_FILA 100

    template <typename T>

    class Fila {
    private:
     //!Um atributo para definir a posição
     /*!Atributo que define a posição atual do ultimo elemento da fila*/
      int last;
      //!Um vetor
      /*!Um vetor genérico usado para armazenar os dados da estrutura em fila*/
      T* dados;
      //!Um atributo para definir o tamanho
      /*!Atributo que define o tamanho da estrutura em fila*/
      int tamanho;

    public:
     //!Construtor
     /*!Construtor sem parâmetros que inicializa a fila com um tamanho estabelecido*/
    Fila() {
       last = -1;
       tamanho = MAX_FILA;
       dados = new T[tamanho];
    }
    //!Construtor
    /*!Construtor com tamanho variavel
      \param t o tamanho do vetor (quantidade máxima de elementos na fila)
      \sa Fila()
    */
    Fila<T>(int tam) {
      last = -1;
      tamanho = tam;
      dados = new T[tamanho];
    }
    //!Método que adiciona um elemento no final da fila
    /*!
      \param dado um elemento a ser adicionado no final da fila
      \sa retira(), inicializaFila()
    */
    void inclui(T dado) {
      if (filaCheia()) {
        throw "Fila Cheia";
      }
      last++;
      dados[last]= dado;
    }
    //!Método que retira um elemento da fila
    /*!
      \return um elemento que ocupava o começo da fila
      \sa inclui(), inicializaFila()
    */
    T retira() {
      if (filaVazia()) {
        throw "Fila Vazia";
      } else {
      T first = dados[0];
      last--;
      for (int i = 0; i < last; i++) {
        dados[i-1] = dados[i];
      }
      return first;
      }
    }
    //!Método que identifica o elemento no fim da fila
    /*!
      \return um elemento que ocupa o final da fila
      \sa getUltimo()
    */
    T ultimo() {
      if (filaVazia()) {
        throw "Fila Vazia";
      }
      return (dados[last]);
    }
    //!Método que identifica a posição do ultimo elemento da fila
    /*!
      \return um inteiro correspondente a posição do ultimo elemento
      \sa ultimo()
    */
    int getUltimo() {
      if (filaVazia()) {
        throw "Fila Vazia";
      }
      return last;
    }
    //!Método que informa se a fila está cheia
    /*!
      \return um boolean
      \sa filaVazia()
    */
    bool filaCheia() {
      return (last == tamanho-1);
    }
    //!Método que informa se a fila está vazia
    /*!
      \return um boolean
      \sa filaCheia()
    */
    bool filaVazia() {
      return (last == -1 );
    }
    //!Método que limpa os elementos da fila
    /*!
      \sa inclui(), retira()
    */
    void inicializaFila() {
      last = -1;
    }
    };
