/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de código fonte: NohAVL.cpp
 * 
 * Implementação dos métodos da Classe NohAVL:
 *      - Construtor
 *      - Destrutor
 *
 * Criado em 23 de Novembro de 2018
 */

#include "NohAVL.h"
#include "Lista.h"
#include "Data.h"

using namespace std;

// Construtor: Aloca os ponteiros necessários
NohAVL::NohAVL(Data* d){
    chave = new Data(d->dia, d->mes, d->ano);
    lista = new Lista();
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
};

// Destrutor
NohAVL::~NohAVL(){
    delete chave;
    delete lista;
    delete esq;
    delete dir;
}
