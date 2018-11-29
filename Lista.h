/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: kellyson
 *
 * Created on 23 de Novembro de 2018, 20:58
 */

#ifndef LISTA_H
#define LISTA_H
#include "Noh.h"
#include <iostream>
#include <string>

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
        string get();
};

#endif /* LISTA_H */

