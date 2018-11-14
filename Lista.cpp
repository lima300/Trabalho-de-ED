/*
 * Trabalho Final de Estrutura de Dados
 * By: Kellyson Santos e Otavio Lima
 * UFLA - 2018/2
 * 
 * Arquivo de Cabeçalho: Lista Encadeada
 * 
 * Esse arquivo contém a implementação dos métodos da classe Lista,
 * em que são armazenadas as temperaturas no decorrer do dia.
 * 
 * A Classe possui os métodos:
 *    - Lista() (Um construtor, que inicia os ponteiros como nulos e o tamanho em zero)
 *    - ~Lista() (Um destrutor que percorre a lista desalocando a memória alocada pelos nós)
 *
 * As listas são armazenadas em uma Árvore AVL, onde cada Noh da AVL é um dia.
 */

/* 
 * File:    Lista.cpp
 * Authors: Otavio Lima, Kellyson Santos
 * 
 * Created on 14 de Novembro de 2018, 12:01
 */

#include "Lista.h"
#include <iostream>
#include <exception>
#include <string>

using namespace std;

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::~Lista(){
    Noh* iter = primeiro;
    Noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->prox;
        delete iter;
        iter = proximo;
    }
};

bool Lista::vazia(){
    if (tamanho){
        return false;
    }
    
    return true;
}

void Lista::inserir(string d, float t){
    Noh* novo = new Noh(d,t);
    
    if (vazia()){
        primeiro = novo;
        ultimo = novo;
        
    } else {
        ultimo->prox = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::remover(string d, float t){
    if (vazia()){
        throw runtime_error ("Impossivel Remover em lista vazia");
    } else {
        Noh* remover = buscar(d, t);
        if(remover == primeiro){
            if (tamanho == 1){
                primeiro = NULL;
                ultimo = NULL;
            } else {
                primeiro = primeiro->prox;
            }
        } else {
            Noh* atual = primeiro;
            Noh* anterior = NULL;
            while (atual != remover){
                anterior = atual;
                atual = atual->prox;
            }
            if (atual == ultimo){
                anterior->prox = NULL;
                ultimo = anterior;
            } else {
                anterior->prox = atual->prox;
            }
        }
        tamanho--;
        delete remover;
    }
}

// metodo basico que *percorre* a lista, imprimindo seus elementos
void Lista::imprime() const {
    Noh* iter = primeiro;
    float t;
    while (iter != NULL) {
        t = iter->getTemp();
        cout << iter->getData() << " -> " << t << endl;
        iter = iter->prox;
    }
}

Noh* Lista::buscar(string d, float t){
    Noh* atual = primeiro;
    bool encontrado = false;
    
    while (atual != NULL and encontrado == false ){
        if (atual->getData() == d and atual->getTemp() == t){
            encontrado = true;
        } else {
            atual = atual->prox;
        }
    }
    
    if (encontrado == false){
        throw invalid_argument ("Elemento não existe");
    } else {
        return atual;
    }
}