/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.cpp
 * Author: kellyson
 * 
 * Created on 23 de Novembro de 2018, 21:18
 */

#include <iostream>
#include <fstream>
#include "NohAVL.h"
#include "Lista.h"
#include "AVL.h"
#include "Data.h"

using namespace std;

AVL::AVL(){
    raiz = NULL;
}

AVL::~AVL(){
    delete raiz;
}

int AVL::informaAltura(NohAVL* umNoh){
    if (umNoh == NULL){
        return 0;
    } else {
        return umNoh->altura;
    }
}

void AVL::atualizarAltura(NohAVL* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    umNoh->altura = 1 + maximo(altEsq, altDir);
}

int AVL::maximo(int a, int b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

int AVL::fatorBalanceamento(NohAVL* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    return altEsq - altDir;
}

NohAVL* AVL::rotacaoEsquerda(NohAVL* umNoh){
    NohAVL* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    
    if (aux->esq != NULL){
        aux->esq->pai = umNoh;
    }
    aux->pai = umNoh->pai;
    
    if (umNoh == raiz){
        raiz = aux;
    } else if (umNoh == umNoh->pai->esq){
        umNoh->pai->esq = aux;
    } else {
        umNoh->pai->dir = aux;
    }
    
    aux->esq = umNoh;
    umNoh->pai = aux;
    
    atualizarAltura(aux);
    atualizarAltura(umNoh);
    
    return aux;
}

NohAVL* AVL::rotacaDireita(NohAVL* umNoh){
    NohAVL* aux = umNoh->esq;
    umNoh->dir = aux->dir;
    
    if (aux->dir != NULL){
        aux->dir->pai = umNoh;
    }
    aux->pai = umNoh->pai;
    
    if (umNoh == raiz){
        raiz = aux;
    } else if (umNoh == umNoh->pai->esq){
        umNoh->pai->esq = aux;
    } else {
        umNoh->pai->dir = aux;
    }
    
    aux->dir = umNoh;
    umNoh->pai = aux;
    
    atualizarAltura(aux);
    atualizarAltura(umNoh);
    
    return aux;
}

NohAVL* AVL::rotacaoEsquerdaDireita (NohAVL* umNoh){
    umNoh->esq = rotacaoEsquerda(umNoh->esq);
    return rotacaDireita(umNoh);
}

NohAVL* AVL:: rotacaoDireitaEsquerda (NohAVL* umNoh){
    umNoh->dir = rotacaDireita(umNoh->dir);
    return rotacaoEsquerda(umNoh);
}

void AVL::inserirRec(Data* d, float t){
    raiz = inserirRecAux(raiz, d, t);
}

NohAVL* AVL::inserirRecAux (NohAVL* umNoh, Data* d, float t){
    if (umNoh == NULL){
        NohAVL* novo = new NohAVL(d);
        novo->lista->inserir(t);
        return novo;
    } else if (*d == umNoh->chave){
        umNoh->lista->inserir(t);
    }else if (*d < umNoh->chave){
        umNoh->esq = inserirRecAux(umNoh->esq, d, t);
        umNoh->esq->pai = umNoh;
    } else {
        umNoh->dir = inserirRecAux(umNoh->dir, d, t);
        umNoh->dir->pai = umNoh;
    }
    return arrumarBalanceamento(umNoh);
}

NohAVL* AVL::arrumarBalanceamento(NohAVL* umNoh){
    atualizarAltura(umNoh);
    int bal = fatorBalanceamento(umNoh);
    
    if ((bal >= -1) and (bal <= 1)){
        return umNoh;
    }
    
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) >= 0)){
        return rotacaDireita(umNoh);
    }
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh);
        return rotacaDireita(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) <= 0)){
        return rotacaoEsquerda(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) > 0)){
        umNoh->dir = rotacaDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}

void AVL::OrderAux(NohAVL* umNoh){
    if(umNoh != NULL) { 
        OrderAux(umNoh->esq); 
        cout << umNoh->chave->dia << "/" <<umNoh->chave->mes << "/"
             << umNoh->chave->ano << " : " ;
        umNoh->lista->imprime();
        cout << endl; 
        OrderAux(umNoh->dir); 
    }
}

void AVL::removerRec(Data* d, float t){
    /*Lista* buscado = busca(d);
    if (buscado != NULL){
        if (buscado->mTamanho == 1){
            buscado->remover(t);
            raiz = removerRecAux(raiz, d);
        } else {
            buscado->remover(t);
        }
    } else {
        throw invalid_argument ("Elemento nao encontrado");
    }*/
}

NohAVL* AVL::removerRecAux(NohAVL* umNoh, Data* d){
    if (umNoh == NULL){
        return umNoh;
    } 
    if ( d < umNoh->chave ){ 
        umNoh->esq = removerRecAux(umNoh->esq, d);
    } else if( d > umNoh->chave ) { 
        umNoh->dir = removerRecAux(umNoh->dir, d);
    } else { 
        // node with only one child or no child 
        if ((umNoh->esq == NULL) or (umNoh->dir == NULL)){ 
            NohAVL* temp = umNoh->esq ? umNoh->esq : 
                                             umNoh->dir; 
  
            if (temp == NULL) { 
                temp = umNoh; 
                umNoh = NULL; 
            } 
            else { // One child case 
                *umNoh = *temp;
            }
            delete temp;
        } else { 
            NohAVL* temp = minimoAux(umNoh->dir); 
            umNoh->chave = temp->chave; 
            umNoh->dir = removerRecAux(umNoh->dir, temp->chave); 
        } 
    } 
    if (umNoh == NULL){ 
        return umNoh; 
    }
    
    return arrumarBalanceamento(umNoh);
}

NohAVL* AVL::minimoAux(NohAVL* atual){
    //Retorna o minimo da arvore
    while(atual -> esq != NULL){
        atual = atual -> esq;
    }
    return atual;
}

void AVL::busca(Data* d){
    NohAVL* atual = raiz;
    
    while(atual != NULL and *atual->chave != d){
        
        if(*atual->chave > d){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
        
    }
    
    
    if (atual != NULL){
        cout << "Lista encontrada!\n";
        atual->lista->imprime();
    } else {
        cout << "Lista encontrada!\n";
    }
}

bool AVL::recursiveSave(NohAVL* noh, string nome){
    ofstream arch(nome.c_str(), ios::app);
    
    string data = noh->chave->get();
    arch << " " << data << " ";
    
    string lista = noh->lista->get();
    arch << lista << "# ";
    
    arch.close();
    
    bool savedE = true;
    bool savedD = true;
    
    if(noh->esq){
        savedE = recursiveSave(noh->esq, nome);
    }
    
    if(noh->dir){
        savedD = recursiveSave(noh->dir, nome);
    }
    
    if(savedE && savedD){
        return true;
    } else {
        return false;
    }
}

bool AVL::save(string nome){
    if(recursiveSave(raiz, nome)){
        ofstream arch(nome.c_str(), ios::app);
        arch << '|';
        arch.close();
        
        return true;
    } else {
        return false;
    }
}

bool AVL::read(string nome){
    ifstream arch(nome.c_str());
    
    if(arch){
        string reader;
        arch >> reader;
        
        while(reader != "|"){
            
            string dia = reader;
            arch >> reader;
            string mes = reader;
            arch >> reader;
            string ano = reader;

            Data* date = new Data(stoi(dia),stoi(mes),stoi(ano));

            while (reader != "#"){
                arch >> reader;

                if (reader != "#"){
                    inserirRec(date,stof(reader));
                }
            }
            
            arch >> reader;
            
        };
        
        arch.close();
        return true;
    } else {
        return false;
    }
}