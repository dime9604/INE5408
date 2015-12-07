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

    void incrementaNchaves() {
        Nchaves+=1;
    }

    void decrementaNchaves() {
        Nchaves-=1;
    }

    void aumentaNChaves(int valor) {
        Nchaves += valor;
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

    /*
    *****************************************************************************
                            Métodos exclusivos da deleção
    *****************************************************************************
    */

    // método que retorna o indice da primeira chave maior ou igual a "chave"
    int encontrarChave(int chave);

    // um wrapper para remover a chave em subárvores deste nodo
    void remover(int chave);

    /*
        método para remover a chave presente na n-ésima posição desse nodo
        caso seja um nodo folha
    */
    void removerDeFolha(int n);

    /*
        método para remover a chave presente na n-ésima posição desse nodo
        caso não seja um nodo folha
    */
    void removerDeNaoFolha(int n);

    /*
        função que retorna o sucessor da chave presente na n-ésima posição do nodo
    */
    int getSucessor(int n);

    /*
        função que retorna o antecessor da chave presente na n-ésima posição do nodo
    */
    int getAntecessor(int n);

    /*
        função para preencher o nodo filho presente na n-ésima posição no array
        filhos[] se esse filho tem menos que nivel-1 chaves
    */
    void preencher(int n);

    /*
        função que pega emprestado uma chave do nodo filhos[n-1] e coloca no nodo
        filhos[n]
    */
    void emprestarDoProximo(int n);

    /*
        função que pega emprestado uma chave do nodo filhos[n+1] e coloca no nodo
        filhos[n]
    */
    void emprestarDoAnterior(int n);

    /*
        função que funde o n-ésimo filho com o nodo do n+1-ésimo filho do nodo
    */
    void fundir(int n);


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

/*
    *****************************************************************************
                            Métodos exclusivos da deleção
    *****************************************************************************
*/
int NoBTree::encontrarChave(int chave) {
    int i = 0;
    while(i < Nchaves && chaves[i] < chave) {
        ++i;
    }
    return i;
}
void NoBTree::remover(int chave) {
    int indice = encontrarChave(chave);
    // se for verdadeiro, a chave a ser removida está presente neste nodo
    if(indice < Nchaves && chaves[indice] == chave) {
        /*
            1- se for um nodo folha, chama a função removerDeFolha()
            2- se não for um nodo folha, chama a função removerDeNaoFolha()
        */
        if(folha) {
            removerDeFolha(indice);
        } else {
            removerDeNaoFolha(indice);
        }
    } else {
        // se o nodo é folha, então a chave não está presente
        if(folha) {
            throw 666;
        }
        /* A chave a ser removida está presente em uma subárvore deste nodo,
           a flag indica se a chave está na subárvore enraizada com o último
           filho deste nodo
        */
        bool flag = false;
        if(indice = Nfolhas) {
            flag = true;
        }
        /* Se o nodo filho onde esta chave supostamente está tem menos que "nivel"
        chaves, será preenchido aquele nodo filho
        */
        if(filhos[indice]->getNChaves() < nivel) {
            preencher(indice);
        }
        /*
            Se o ultimo filho foi fundido, ele tem que se fundir com o filho anterior e
            então usamos recursão no (indice-1)-ésimo filho, caso contrário, nós usamos
            recursão no indice-ésimo filho que agora tem pelo menos (nivel) chaves
        */
        if(flag && indice < Nchaves) {
            filhos[indice-1]->remover(chave);
        } else {
            filhos[indice]->remover(chave);
        }
    }
    return;
}
void NoBTree::removerDeFolha(int chave) {
    // move todas as chaves depois da (chave)-ésima posição
    for(int i = chave+1; i < Nchaves; i++) {
        chaves[i-1] = chaves[i];
        // reduz a contagem de chaves
        Nchaves--;
    }
    return;
}
void NoBTree::removerDeNaoFolha(int chave) {
    int k = chaves[chave];
    /*
        se o filho que precede k (filhos[chave]) tem pelo menos "nivel" chaves, encontra
        o predecessor de k na subárvore de filhos[chave]. Substitui k pelo predecessor, e
        recursivamente deleta o predecessor em filhos[chave]
    */
    if(filhos[chave]->getNChaves() >= nivel) {
        int ant = getAntecessor(chave);
        chaves[chave] = ant;
        filhos[chave]->remover(ant);
    }
    /*
        se o filho "filhos[chave]" tem menos que "nivel" chaves, verifique filhos[chame+1].
        se filhos[chave+1] tem pelo menos "nivel" chaves, procura o sucessor de k na subárvore
        de filhos[chave+1]. substitui k pelo sucessor, e recursivamente deleta o sucessor em
        filhos[chave+1]
    */
    else if(filhos[chave+1]->getNChaves() >= nivel) {
        int suc = getSucessor(chave);
        chaves[chave] = suc;
        filhos[chave+1]->remover(suc);
    }
    /*
        caso filhos[chave] e filhos[chave+1] tenham menos que nivel chaves, junta k e todos
        de filhos[chave+1] em filhos[chave], então filhos[chave] contém 2nivel-1 chaves
        desaloca filhos[chave+1] e deleta recursivamente k de filhos[chave]
    */
    else {
        fundir(chave);
        filhos[chave]->remover(k);
    }
    return;
}
int NoBTree::getAntecessor(int chave) {
    NoBTree *aux = filhos[chave];
    while(!aux->getFolha()) {
        aux = aux->getFilhos(aux->getNChaves());
    }
    return aux->getChave(aux->getNChaves()-1);
}
int NoBTree::getSucessor(int chave) {
    NoBTree *aux = filhos[chave+1];
    while(!aux->getFolha()) {
        aux = aux->getFilhos(0);
    }
    return aux->getChave(0);
}
void NoBTree::preencher(int chave) {
    /*
        Se o filho anterior (filhos[chave-1]) tem menos que nivel-1 chaves, pega uma chave
        emprestada desse filho
    */
    if(chave != 0 && filhos[chave-1]->getNChaves() >= nivel) {
        emprestarDoAnterior(chave);
    }
    /*
        Se o próximo filho (filhos[chave+1]) tem mais que nivel-1 chaves, pega uma chave
        emprestada desse filho
    */
    else if(chave != Nchaves && filhos[chave+1]->getNChaves() >= nivel) {
        emprestarDoProximo(chave);
    }
    /*
        Se filhos[chave] é o ultimo filho, "funde" com seu "ramo" anterior, caso contrário
        funde com o próximo
    */
    else {
        if (chave != Nchaves) {
            fundir(chave);
        }
        else {
            fundir(chave-1);
        }
    }
    return;
}
void NoBTree::emprestarDoAnterior(int chave) {

    NoBTree *filho = filhos[chave];
    NoBTree *ramo = filhos[chave-1];

    /*
        a ultima chave de filhos[chave-1] vai para o pai e a chaves[chave-1] do pai é
        inserida como a primeira chave em filhos[chave].
    */

    // movendo todas as chaves de filhos[chave] para a frente
    for(int i = (filho->getNChaves())-1; i >= 0; i++) {
        filho->setChaves(i+1, filho->getChave(i));
    }

    // se filhos[chave] não é uma folha, move todos os ponteiros filho para frente

    if(!filho->getFolha()) {
        for(int i = filho->getNChaves(); i >= 0; i++) {
            filho->setFilhos(i+1, filho->getFilhos(i));
        }
    }

    // colocando a primeira chave do filho igual a chaves[chave-1] do nodo atual

    filho->setChaves(0, chaves[chave-1]);

    // movendo o ramo do ultimo filho como filhos[chave] do primeiro filho (confuso)

    if(!folha) {
        // VAI DAR DOR DE CABEÇA
        filho->setFilhos(0, ramo->getFilhos(ramo->getNChaves());// PONTO DE OBSERVAÇÃO
    }

    // movendo a chave do ramo pro pai, isso reduz o número de chaves do ramo

    chaves[chave-1] = ramo->getChave(ramo->getNChaves()-1);

    filho->incrementaNchaves();
    ramo->decrementaNchaves();

    return;
}
void NoBTree::emprestarDoProximo(int chave) {

    NoBTree *filho = filhos[chave];
    NoBTree *ramo = filhos[chave+1];

    // chaves[chave] é inserido como ultima chave em filhos[chave]
    filho->setChaves(filho->getNChaves(), chaves[chave]);

    // o primeiro filho do ramo é inserido como o ultimo filho de filhos[chave]
    if(!(filho->getFolha()) {
        filho->setFilhos(filho->getNChaves()+1, ramo->getFilhos(0));
    }

    // A primeira chave do ramo é inserida em chaves[chave]
    chaves[chave] = ramo->getChave(0);

    // Move todas as chaves no ramo para trás
    for(int i = 1; i < ramo->getNChaves(), ++i) {
        ramo->setChaves(i-1, ramo->getChave(i));
    }

    // Move os ponteiros dos filhos para trás
    if(!ramo->getFolha()) {
        for(int i = 1; i < ramo->getNChaves(); ++i) {
            ramo->setFilhos(i-1, ramo->getFilhos(i));
        }
    }

    // incrementando a contagem de chaves de filhos[chave]
    filho->incrementaNchaves();

    // decrementando a contagem de chaves de filhos[chave+1]
    ramo->decrementaNchaves();
}
void fundir(int chave) {

    NoBTree *filho = filhos[chave];
    NoBTree *ramo = filhos[chave+1];

    // tira uma chave do nodo atual e coloca na posição (nivel-1) de filhos[chave]
    filho->setChaves(nivel-1, chaves[chave]);

    // copia as chaves de filhos[chave+1] para filhos[chave]
    for(int i = 0; i < ramo->getNChaves(); ++i) {
        filho->setChaves(i+nivel; ramo->getChave(i));
    }

    // copia os ponteiros dos filhos de filhos[chave+1] para filhos[chave]
    if(!filho->getFolha()) {
        for(int i = 0; i <= ramo->getNChaves()); ++i) {
            filhos->setFilhos(i+nivel, ramo->getFilhos(i));
        }
    }

    /*
        move todas as chaves depois de "chave" no nodo atual para trás para preencher
        a lacuna criada movendo chaves[chave] para filhos[chave]
    */
    for(int i = chave+2; i < Nchaves; ++i) {
        chaves[i-1] = chaves[i];
    }

    // move todos os ponteiros filhos depois de (chave+1) no nodo atual para trás
    for(int i = chave+2; i<= Nchaves; ++i) {
        filhos[i-1] = filhos[i];
    }

    // atualiza o contador de chaves do nodo atual
    filho->aumentaNChaves(ramo->getNChaves()+1);
    Nchaves--;

    // desaloca a memória ocupada pelo ramo
    delete(ramo);
    return;
} #endif
/*
    TO DO LIST:

    FUNDIR

    FAZER A MAIN E TESTAR SE ESSA PORRA FUNCIONA
*/
