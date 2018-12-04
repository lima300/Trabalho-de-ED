/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 * Author: kellyson
 *
 * Created on 23 de Novembro de 2018, 21:18
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
        NohAVL* rotacaoEsquerdaDireita (NohAVL* umNoh);
        NohAVL* rotacaoDireitaEsquerda (NohAVL* umNoh);
        void inserirRec (Data* d, float t);
        NohAVL* inserirRecAux (NohAVL* umNoh, Data* d, float t);
        NohAVL* arrumarBalanceamento(NohAVL* umNoh);
        void removerRec(Data* d);
        NohAVL* removerRecAux(NohAVL* umNoh, Data* d);
        void Order();
        void OrderAux(NohAVL* umNoh);
        NohAVL* minimoAux (NohAVL* atual);
        void busca (Data* d);
        NohAVL copy(NohAVL no);
        /*bool save(String nome = "output.txt");
        bool recursiveSave(NohAVL* noh, String nome);
        /*bool read(string nome = "output.txt");*/
};

#endif /* AVL_H */
