/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data.h
 * Author: kellyson
 *
 * Created on 23 de Novembro de 2018, 20:50
 */

#include <iostream>
#ifndef DATA_H
#define DATA_H

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
        void alterar(int d, int m, int a);
        bool operator < (Data* d);
        bool operator > (Data* d);
        bool operator == (Data* d);
        bool operator != (Data* d);
        string get();
};

#endif /* DATA_H */

