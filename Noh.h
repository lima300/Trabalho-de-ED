/*
 * Trabalho Final de Estrutura de Dados
 * By: Kellyson Santos e Otavio Lima
 * UFLA - 2018/2
 * 
 * Arquivo de Cabeçalho: Noh da Lista Encadeada
 * 
 * Esse arquivo contém a declaração da classe Noh, que compõe as listas do programa.
 * Cada Noh da lista armazena a temperatura de determinado horário de um dia.
 * 
 * A Classe Noh é amiga da classe Lista, permitindo que a classe Lista acesse seus dados privados.
 * 
 * A Classe possui os atributos:
 *    - Valor
 *    - Próximo
 */

/* 
 * File:   Noh.h
 * Author: Kellyson Santos / Otavio Lima
 *
 * Created on 14 de Novembro de 2018, 12:28
 */

#include <string>
#ifndef NOH_H
#define NOH_H
#include "Info.h"

using namespace std;

class Noh {friend class Lista;
    private:
        Info valor;
        Noh* prox;
    public:
        Noh(string d,float t);
        float getTemp();
        string getData();
};

#endif /* NOH_H */

