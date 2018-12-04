/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Noh.h
 * Author: kellyson
 *
 * Created on 23 de Novembro de 2018, 20:55
 */

#ifndef NOH_H
#define NOH_H

using namespace std;

class Noh {
    friend class Lista;
    friend class AVL;
    private:
        float mTemperatura;
        Noh* mPtProx;
    public:
        Noh(float t);
};

#endif /* NOH_H */
