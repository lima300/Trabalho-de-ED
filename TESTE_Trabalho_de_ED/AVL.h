/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de cabeçalho: AVL.h
 *
 * Criado em 23 de Novembro de 2018
 */

#ifndef AVL_H
#define AVL_H
#include "NohAVL.h"

using namespace std;

class AVL {
    friend class NohAVL;
    private:
        NohAVL* raiz;
    public:
        AVL();
        ~AVL();
        int informaAltura(NohAVL* umNoh);
        void atualizarAltura(NohAVL* umNoh);
        int maximo(int a, int b);
        int fatorBalanceamento(NohAVL* umNoh);
        NohAVL* rotacaoEsquerda(NohAVL* umNoh);
        NohAVL* rotacaDireita(NohAVL* umNoh);
        void inserirRec (Data* d, float t);
        NohAVL* inserirRecAux (NohAVL* umNoh, Data* d, float t);
        NohAVL* arrumarBalanceamento(NohAVL* umNoh);
        void removerRec(Data* d);
        NohAVL* removerRecAux(NohAVL* umNoh, Data* d);
        void Order();
        void OrderAux(NohAVL* umNoh);
        NohAVL* minimoAux (NohAVL* atual);
        void busca (Data* d);
        void save();
        int recursiveSave(NohAVL* noh);
};

#endif /* AVL_H */
