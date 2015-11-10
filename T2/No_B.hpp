#ifndef NO_B_HPP
#define NO_B_HPP

#include <stdio.h>
#include <cstdlib>

template <typename T>

class NoBTree {
protected:
    // um array de chaves
    int *chaves;
    // define a quantidade de chaves
    int nivel
    // array com os nodos filhos
    NoBTree **filhos;
    // número de chaves
    int Nchaves;
    // informa se o nodo é uma folha
    bool folha;

public:
    NoBTree(int _nivel, bool _folha) {
        nivel = _nivel;
        folha = _folha;
        chaves = new int[(2*nivel)-1];
        filhos = new NoBTree* [2*nivel];
        Nchaves = 0;
    }
    // destrutor
    virtual ~NoBTree() {}
    // reordena e imprime todos os nodos em uma subárvore deste nodo

    /*
    *****************************************************************************
                                GETTERS AND SETTERS
    *****************************************************************************
    */

    void setChaves(int indice, int chave) {
        chaves[indice] = chave;
    }

    int getChave(int indice) {
        return chaves[indice];
    }

    void setNChaves(int n) {
        Nchaves = n;
    }

    int getNivel() {
        return nivel;
    }

    bool getFolha() {
        return folha;
    }

    int getNChaves() {
        return Nchaves;
    }
    // não sei se o parâmetro tem q ser um ponteiro, achei meio confuso esse set
    void setFilhos(int indice, NoBTree *filho) {
        filhos[indice] = filho;
    }
    // esses ponteiros vão acabar me matando
    // return do tipo NoBTree, NoBTree* ou NoBTree**?
    NoBTree* getFilhos(int indice) {
        return filhos[indice];
    }

    /*
    *****************************************************************************
        Métodos que executam coisas mais relevantes que getters ou setters!!
    *****************************************************************************
    */


    void reordenar ();
    // função que procura uma chave em uma subárvore desse nodo
    NoBTree *buscar(int chave);
    // insere quando o nodo não está cheio
    NoBTree insereNaoCheio(int chave);
    // quando o nodo está cheio, joga o filho pra outro nodo em um nivel acima
    // i é o indice de y no array filhos[]
    // função serve pra separar o filho em dois donos de filhos
    // caso de erros, ver parte no método que ele copia os filhos do ultimo nivel do aux
    void separarFilhos(int i, NoBTree *aux);

};

void NoBTree::reordenar() {
    for (int i = 0; i < Nchaves; i++) {
        if(folha == false) {
            filhos[i]->reordenar();
        }
        printf("%d\n", filhos[i]);
    }
    if(folha == false) {
        filhos[i]->reordenar();
    }
}


void NoBTree::buscar(int chave) {
    int i = 0;
    // busca a primeira chave maior ou igual ao parâmetro
    while(i < Nchaves && chave > chaves[i]) {
        i++;
    }
    // se a chave foi encontrada, retorna este nodo
    if(chaves[i] == chave) {
        return this;
    }
    // se é um nodo folha, retorna NULL
    if(folha == true) {
        return NULL
    }
    // vai para outro nodo
    return filhos[i]->buscar(chave);
}

void NoBTree::insereNaoCheio(int chave) {
    // inicializa o indice com o indice do elemento que está mais à direita
    int indice = Nchaves-1;

    if (folha == true) {
        /*
        o while faz duas coisas:
        1- encontra a localização da nova chave a ser inserida
        2- move todos os que são maiores para um "espaço" a frente
        */
        while (indice >= 0 && chaves[indice] > chave) {
            chaves[indice+1] = chaves[indice];
            indice--;
        }
        // insere a chave na posição encontrada
        chaves[indice+1] = chave;
        Nchaves+=1;
    } else { // se o nodo não é folha
        // encontra o filho que irá receber a nova chave :3
        while (indice >= 0 && chaves[indice] > chave) {
            indice--;
        }
        // verifica se o nodo do filho encontrado está cheio
        if (filhos[indice+1]->getNChaves()) == (2*nivel)-1) {
            // se o filho ta cheio, quebra ele!
            separarFilhos(indice+1, filhos[indice+1]);
            /*  depois de quebrar, a chave média do filhos[indice] vai
                um nivel acima e o filhos[indice] é quebrado em dois, e verifica
                qual dos dois vai ganhar a nova chave
            */
            if (chaves[indice+1] < chave) {
                indice++;
            }
        }
        filhos[indice+1]->insereNaoCheio(chave);
    }
}

void NoBTree::separarFilhos(int i, NoBTree *aux) {
    /*
        cria um novo nodo que vai guardar nivel-1 chaves do auxiliar (aux)
    */
    NoBTree *x = new NoBTree(aux->getNivel(), aux->getFolha());
    x->setNChaves(nivel-1);
    // copia as ultimas (nivel-1) chaves de aux para x
    for (int j = 0; j < nivel-1, j++) {
        x->setChaves(j, aux->getChave(j+nivel));
    }
    // copia os filhos do ultimo nivel de aux para x
    // confuso as fuck, possivel ponto de erros no código, to me perdendo mto fácil aqui
    if (aux->getFolha() == false) {
        for (int j = 0; j < nivel; j++) {
            x->setFilhos(j+1, aux->getFilhos(j+nivel));
        }
    }
    // reduz o número de chaves no aux
    aux->setNChaves(nivel-1);

    /*
        uma vez que esse nodo vai receber um novo filho
        tem que criar espaço pra chegada do recém nascido :^)
    */
    for (int j = Nchaves; j >= i+1; j--) {
        filhos[j+1] = filhos[j];
    }
    // nesse ponto é feita a linkagem do novo filho com o nodo
    filhos[i+1] = x;
    /*
        aqui as chaves vão sendo empurradas para frente para abrir espaço
        para a chave do novo filho
    */
    for (int j = Nchaves-1; j >= i; j--) {
        chaves[j+1] = chaves[j];
    }
    // copia a chave do meio de aux para esse nodo
    chaves[i] = aux->getChave(nivel-1);
    // incrementa a contagem de chaves desse nodo
    Nchaves+=1;
}
