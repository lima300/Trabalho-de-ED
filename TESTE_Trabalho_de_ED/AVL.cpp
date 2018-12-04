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

#include "Arduino.h"
#include "Streaming.h"
#include "NohAVL.h"
#include "Lista.h"
#include "AVL.h"
#include "Data.h"
/*#include "SdFat.h"
#include "sdios.h"
#include <SPI.h> */



AVL::AVL(){
    raiz = nullptr;
}

AVL::~AVL(){
    delete raiz;
}

int AVL::informaAltura(NohAVL* umNoh){
    if (umNoh == nullptr){
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
    
    if (aux->esq != nullptr){
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
    
    if (aux->dir != nullptr){
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

void AVL::Order(){
  if(raiz){
    OrderAux(raiz);
  } else {
    Serial.println("Opa! Sua estrutura está vazia!");
  }
}

void AVL::OrderAux(NohAVL* umNoh){
    if(umNoh != nullptr) {
        OrderAux(umNoh->esq); 
        
        Serial.print(umNoh->chave->dia);
        Serial.print('/');
        Serial.print(umNoh->chave->mes);
        Serial.print('/');
        Serial.print(umNoh->chave->ano);
        Serial.print(" : ");
        umNoh->lista->imprime();
        
        OrderAux(umNoh->dir); 
    }
}

void AVL::removerRec(Data* d){
    raiz = removerRecAux(raiz, d);
}

NohAVL* AVL::removerRecAux(NohAVL* umNoh, Data* d){
    if (umNoh == nullptr){
        return umNoh;
    }

    if (*d == umNoh->chave){
        // Nó com um ou nenhum filho
        if ((umNoh->esq == nullptr) or (umNoh->dir == nullptr)){ 
            NohAVL* aux = umNoh->esq ? umNoh->esq : umNoh->dir; 
    
            if (aux == nullptr) { //Caso não tenha filhos
                aux = umNoh; 
                umNoh = nullptr; 
            } else { // Caso tenha um filho 
                //*umNoh = copy(*aux);
                *umNoh = *aux;
            }
            
            delete aux;
        } else { //Caso tenha dois filhos
            NohAVL* aux = minimoAux(umNoh->dir); 
            umNoh->chave = aux->chave; 
            umNoh->dir = removerRecAux(umNoh->dir, aux->chave); 
        }
    } else if (*d < umNoh->chave ){
        umNoh->esq = removerRecAux(umNoh->esq, d);
    } else {
        umNoh->dir = removerRecAux(umNoh->dir, d);
    }

    if (umNoh == nullptr){
          return umNoh;
    }
      
    return arrumarBalanceamento(raiz);
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
    
    while(atual != nullptr and *atual->chave != d){
        
        if(*atual->chave > d){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    if (atual != nullptr){
        Serial.println("Data encontrada!");
        Serial.print("[");
        Serial.print(d->dia);
        Serial.print("/");
        Serial.print(d->mes);
        Serial.print("/");
        Serial.print(d->ano);
        Serial.print("] -> ");
        
        atual->lista->imprime();
    } else {
        Serial.println("Data não encontrada!");
    }
}

NohAVL AVL::copy(NohAVL noh){
    int d, m, a;
    d = noh.chave->dia;
    m = noh.chave->mes;
    a = noh.chave->ano;
    Data date(d, m, a);

    Lista temps;

    Noh* auxl = noh.lista->mPtPrimeiro;

    while(auxl){
        temps.inserir(auxl->mTemperatura);
        auxl = auxl->mPtProx;
    }

    Serial.println("SAIU DO WHILE");
    
    NohAVL novoNo(&date);
    novoNo.lista = &temps;
    novoNo.dir = noh.dir;
    novoNo.esq = noh.esq;
    
    return novoNo;
}


/*bool AVL::recursiveSave(NohAVL* noh, String nome){
    ofstream arch(nome.c_str(), ios::app);
    
    arch << "[" << noh->chave->dia << "/" << noh->chave->mes << "/" << noh->chave->ano << "] -";
    
    Noh* aux = noh->lista->mPtPrimeiro;

    while(aux){
      arch << " -> " << aux->mTemperatura;
      aux = aux->mPtProx;
    }
    
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

bool AVL::save(String nome){
    if(recursiveSave(raiz, nome)){
        ofstream arch(nome.c_str(), ios::app);
        arch << '|';
        arch.close();
        
        return true;
    } else {
        return false;
    }
}

/*bool AVL::read(string nome){
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
}*/
