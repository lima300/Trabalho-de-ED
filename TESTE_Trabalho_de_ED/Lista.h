/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de cabeçalho: Lista.h
 *
 * Criado em 23 de Novembro de 2018
 */

#ifndef LISTA_H
#define LISTA_H
#include "Noh.h"
//#include <string>

using namespace std;

class Lista {
    friend class AVL;
    private:
        Noh* mPtPrimeiro;
        Noh* mPtUltimo;
        int mTamanho;
    public:
        Lista();
        ~Lista();
        bool vazia ();
        void inserir(float t);
        void remover(float t);
        void imprime() const;
        Noh* buscar(float t);
};

#endif /* LISTA_H */
