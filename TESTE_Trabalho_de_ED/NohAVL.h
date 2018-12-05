/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de cabeçalho: NohAVL.h
 *
 * Criado em 23 de Novembro de 2018
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

