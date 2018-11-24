/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.cpp
 * Author: kellyson
 * 
 * Created on 23 de Novembro de 2018, 20:58
 */

#include <iostream>
#include "Lista.h"
#include "Noh.h"

using namespace std;

Lista::Lista(){
    mPtPrimeiro = NULL;
    mPtUltimo = NULL;
    mTamanho = 0;
}

Lista::~Lista(){
    Noh* iter = mPtPrimeiro;
    Noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->mPtProx;
        delete iter;
        iter = proximo;
    }
};

bool Lista::vazia(){
    return mPtPrimeiro == NULL and mPtUltimo == NULL and mTamanho == 0;
}

void Lista::inserir(float t){
    Noh* novo = new Noh(t);
    if (mPtPrimeiro == NULL){
        mPtPrimeiro = novo;
        mPtUltimo = novo;
    } else {
        mPtUltimo->mPtProx = novo;
        mPtUltimo = novo;
    }
    mTamanho++;
}

void Lista::remover(float t){
    if (vazia()){
        throw runtime_error ("Impossivel Remover em lista vazia");
    } else {
        Noh* remover = buscar(t);
        if(remover == mPtPrimeiro){
            if (mTamanho == 1){
                mPtPrimeiro = NULL;
                mPtUltimo = NULL;
            } else {
                mPtPrimeiro = mPtPrimeiro->mPtProx;
            }
        } else {
            Noh* atual = mPtPrimeiro;
            Noh* anterior = NULL;
            while (atual != remover){
                anterior = atual;
                atual = atual->mPtProx;
            }
            if (atual == mPtUltimo){
                anterior->mPtProx = NULL;
                mPtUltimo = anterior;
            } else {
                anterior->mPtProx = atual->mPtProx;
            }
        }
        mTamanho--;
        delete remover;
    }
}

void Lista::imprime() const {
    Noh* iter = mPtPrimeiro;
    while (iter != NULL) {
        cout << iter->mTemperatura << " ";
        iter = iter->mPtProx;
    }
}

Noh* Lista::buscar(float t){
    Noh* atual = mPtPrimeiro;
    bool encontrado = false;
    
    while (atual != NULL and encontrado == false ){
        if (atual->mTemperatura == t){
            encontrado = true;
        } else {
            atual = atual->mPtProx;
        }
    }
    if (encontrado == false){
        throw invalid_argument ("Elemento não existe");
    } else {
        return atual;
    }
}