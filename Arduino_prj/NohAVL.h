/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NohAVL.h
 * Author: kellyson
 *
 * Created on 23 de Novembro de 2018, 21:14
 */

#ifndef NOHAVL_H
#define NOHAVL_H
#include "Data.h"
#include "Lista.h"

using namespace std;

class NohAVL{
    friend class AVL;
    private:
        Data* chave;
        Lista* lista;
        NohAVL* esq;
        NohAVL* dir;
        NohAVL* pai;
        unsigned int altura;
    public:
        NohAVL(Data* d);
        ~NohAVL();
};

#endif /* NOHAVL_H */

