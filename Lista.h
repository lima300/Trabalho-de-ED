/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: user-pc
 *
 * Created on 14 de Novembro de 2018, 12:01
 */

#ifndef LISTA_H
#define LISTA_H
#include "Noh.h"

using namespace std;

class Lista {
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
    public:
        Lista();
        ~Lista();
        bool vazia ();
        void inserir(string d,float t);
        void remover(string d,float t);
        void imprime() const;
        Noh* buscar(string d,float t);
};

#endif /* LISTA_H */

