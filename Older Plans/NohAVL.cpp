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

#include <iostream>
#include "NohAVL.h"
#include "Lista.h"
#include "Data.h"

using namespace std;

NohAVL::NohAVL(Data* d){
    chave = d;
    lista = new Lista();
    esq = NULL;
    dir = NULL;
    pai = NULL;
};

NohAVL::~NohAVL(){
    delete esq;
    delete dir;
}