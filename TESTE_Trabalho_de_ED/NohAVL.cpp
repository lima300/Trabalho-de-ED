/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NohAVL.cpp
 * Author: kellyson
 * 
 * Created on 23 de Novembro de 2018, 21:14
 */

#include "NohAVL.h"
#include "Lista.h"
#include "Data.h"

using namespace std;

NohAVL::NohAVL(Data* d){
    chave = new Data(d->dia, d->mes, d->ano);
    lista = new Lista();
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
};

NohAVL::~NohAVL(){
    delete lista;
    delete esq;
    delete dir;
}
