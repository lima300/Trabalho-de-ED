/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de cabeçalho: Data.h
 *
 * Criado em 23 de Novembro de 2018
 */

#ifndef DATA_H
#define DATA_H
#include "Arduino.h"

using namespace std;

class Data {
    friend class info;
    friend class Noh;
    friend class Lista;
    friend class AVL;
    friend class NohAVL;
    private:
        int dia;
        int mes;
        int ano;
    public:
    Data (int d, int m, int a);
    void set(int d, int m, int a);
    bool operator < (Data* d);
    bool operator > (Data* d);
    bool operator == (Data* d);
    bool operator != (Data* d);
};

#endif /* DATA_H */
