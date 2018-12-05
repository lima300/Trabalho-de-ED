/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de código fonte: Lista.cpp
 * 
 * Implementação dos métodos da Classe Lista:
 *      - construtor
 *      - destrutor
 *      - vazia
 *      - inserir
 *      - remover
 *      - imprime
 *      - buscar
 *
 * Criado em 23 de Novembro de 2018
 */

//#include <iostream>
#include "Lista.h"
#include "Noh.h"
#include <Arduino.h>
//#define nullptr 0;

using namespace std;

//Inicia uma lista com os atributos necessários
Lista::Lista(){
    mPtPrimeiro = nullptr;
    mPtUltimo = nullptr;
    mTamanho = 0;
}

// Percorre a lista desalocando os ponteiros
Lista::~Lista(){
    Noh* iter = mPtPrimeiro;
    Noh* proximo = nullptr;
    while (iter != nullptr) {
        proximo = iter->mPtProx;
        delete iter;
        iter = proximo;
    }
};

// Retorna true caso a lista esteja vazia
bool Lista::vazia(){
    return mPtPrimeiro == nullptr and mPtUltimo == nullptr and mTamanho == 0;
}

// Insere um novo elemento no fim da lista
void Lista::inserir(float t){
    Noh* novo = new Noh(t);
    if (mPtPrimeiro == nullptr){
        mPtPrimeiro = novo;
        mPtUltimo = novo;
    } else {
        mPtUltimo->mPtProx = novo;
        mPtUltimo = novo;
    }
    mTamanho++;
}

// Remove um elemento da lista
void Lista::remover(float t){
    if (vazia()){
        Serial.println("Impossível imprimir em lista vazia");
    } else {
        Noh* remover = buscar(t);
        if(remover == mPtPrimeiro){
            if (mTamanho == 1){
                mPtPrimeiro = nullptr;
                mPtUltimo = nullptr;
            } else {
                mPtPrimeiro = mPtPrimeiro->mPtProx;
            }
        } else {
            Noh* atual = mPtPrimeiro;
            Noh* anterior = nullptr;
            while (atual != remover){
                anterior = atual;
                atual = atual->mPtProx;
            }
            if (atual == mPtUltimo){
                anterior->mPtProx = nullptr;
                mPtUltimo = anterior;
            } else {
                anterior->mPtProx = atual->mPtProx;
            }
        }
        Serial.println("removido com sucesso");
        mTamanho--;
        delete remover;
    }
}

//Imprime a lista
void Lista::imprime() const {
    Noh* iter = mPtPrimeiro;
    while (iter != nullptr) {
        Serial.print(" -> ");
        Serial.print(iter->mTemperatura);
        iter = iter->mPtProx;
    }
}

//Procura por um nó com valor específico na lista
Noh* Lista::buscar(float t){
    Noh* atual = mPtPrimeiro;
    bool encontrado = false;
    
    while (atual != nullptr and encontrado == false ){
        if (atual->mTemperatura == t){
            encontrado = true;
        } else {
            atual = atual->mPtProx;
        }
    }
    if (encontrado == false){
        Serial.println("Elemento não existe");
    } else {
        return atual;
    }
}
