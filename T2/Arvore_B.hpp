#ifndef ARVORE_B_HPP
#define ARVORE_B_HPP

#include "No_B.hpp"

class ArvoreB {
 protected:
    // nodo raíz da árvore
    NoBTree *raiz;
    // nível da árvore
    int nivel;

 public:
    ArvoreB(int _nivel) {
        raiz = NULL;
        nivel = _nivel;
    }

    void reordenar() {
        if (raiz != NULL) {
            raiz->reordenar();
        }
    }

    NoBTree *buscar(int chave) {
        if (raiz != NULL) {
            return raiz->buscar(chave);
        } else return NULL;
    }

    // função que insere uma nova chave na árvore B
    void insere(int chave);

    // função que remove uma chave na árvore B
    void remove(int chave);

};

void ArvoreB::insere(int chave) {
    // condicional para verificar se a árvore está vazia
    if (raiz == NULL) {
        raiz = new NoBTree(nivel, true);
        raiz->setChaves(0, chave);
        raiz->setNChaves(1);
    } else {
        if (raiz->getNchaves() == 2*nivel-1) {
            // cria uma nova raíz
            NoBTree *aux = new NoBTree(nivel, false);
            // ver método na classe NoBTree, não to confiante no pointer do parâmetro
            aux->setFilhos(0, raiz);
            aux->separarFilhos(0, raiz);
            int i = 0;
            if (aux->getChave(i) < chave) {
                i++;
            }
            // insere recursivamente
            aux->getFilhos(i)->insereNaoCheio(chave);
            // atualiza a raiz
            raiz = aux;
        } else {
            // se a raiz não estiver cheia insere na raiz mesmo
            raiz->insereNaoCheio(chave);
        }
    }
}

