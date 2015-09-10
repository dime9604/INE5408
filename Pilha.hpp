    /*Copyright [2015] <Gustavo Tarciso da Silva>*/
    //!Classe Pilha
    /*!Classe que implementa uma estrutura em Pilha*/

    #define PILHA_MAX 100

    template<typename T>

    class Pilha {
    private:
    //!Um atributo para definir a posição
    /*!Atributo que define a posição atual do topo(ultimo elemento) da pilha*/
    int top;
    //!Um vetor
    /*!Um vetor genérico usado para armazenar os dados da estrutura em pilha*/
    T* dados;
    //!Um atributo para definir o tamanho
    /*!Atributo que define o tamanho da estrutura em pilha*/
    int tamanho;

    public:
    //!Construtor
    /*!Construtor sem parâmetros que inicializa a pilha com um tamanho estabelecido*/
    Pilha() {
    tamanho = PILHA_MAX;
    top = -1;
    dados = new T[tamanho];
    }
    //!Construtor
    /*!Construtor com tamanho variavel
      \param t o tamanho do vetor (quantidade máxima de elementos na pilha)
      \sa Pilha()
    */
    Pilha<T>(int t) {
    tamanho = t;
    top = -1;
    dados = new T[tamanho];
    }
    //!Método que adiciona um elemento no topo da pilha
    /*!
      \param dado um elemento a ser adicionado no topo da pilha
      \sa desempilha(), limparPilha()
    */
    void empilha(T dado) {
      if (PilhaCheia()) {
        throw "Pilha Cheia";
      }
        top++;
        dados[top] = dado;
    }
    //!Método que retira um elemento do topo da pilha
    /*!
      \return um elemento que ocupava o topo da pilha
      \sa empilha(), limparPilha()
    */
    T desempilha() {
      if (PilhaVazia()) {
        throw "Pilha Vazia";
      }
        top--;
        return dados[top+1];
    }
    //!Método que identifica o elemento no topo da pilha
    /*!
      \return um elemento que ocupa o topo da pilha
      \sa getPosTopo()
    */
    T topo() {
      if (PilhaVazia()) {
        throw "Pilha Vazia";
      }
        return (dados[top]);
    }
    //!Método que identifica a posição do ultimo elemento da pilha
    /*!
      \return um inteiro correspondente a posição do ultimo elemento
      \sa topo()
    */
    int getPosTopo() {
    if (PilhaVazia()) {
        throw "Pilha Vazia";
    }
      return top;
    }
    //!Método que limpa os elementos da pilha
    /*!
      \sa empilha(), desempilha()
    */
    void limparPilha() {
      top = -1;
    }
    //!Método que informa se a pilha está vazia
    /*!
      \return um boolean
      \sa PilhaCheia()
    */
    bool PilhaVazia() {
      return (top == -1);
    }
    //!Método que informa se a pilha está cheia
    /*!
      \return um boolean
      \sa PilhaVazia()
    */
    bool PilhaCheia() {
      return (top == tamanho-1);
    }
    };
