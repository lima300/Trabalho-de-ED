/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de cabeçalho: Noh.h
 *
 * Criado em 23 de Novembro de 2018
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
