/*
 * Trabalho Final de Estrutura de Dados
 * By: Kellyson Santos e Otavio Lima
 * UFLA - 2018/2
 * 
 * Arquivo base: Main
 * 
 * O trabalho consiste em uma aplicação que capta os dados de Data e Temperatura
 * de um sensor para Arduino e armazena nas estruturas de dados.
 * 
 * As estruturas utilizadas são:
 *      - Árvore AVL;
 *      - Lista encadeada;
 * 
 *  ~ Cada nó da Árvore armazena as temperaturas de um dia em que a leitura
 *    de dados foi efetuada, ou seja, cada nó é correspondente a um dia.
 *  ~ Cada dia possui uma Lista que armazena em cada um de seus nós uma leitura
 *    de determinado horário do dia.
 * 
 * A leitura dos dados é feita pelo sensor do arduíno e armazenada externamente
 */

#include <iostream>
#include <exception>
#include "Lista.h"

using namespace std;

typedef string Texto;

int main() { // NÃO MODIFIQUE!
    Lista a;
    float t;
    cin >> t;
    
    a.inserir("13/11/2018 11:46", t);
    a.inserir("13/11/2018 11:47", t);
    a.inserir("13/11/2018 11:48", t);
    a.inserir("13/11/2018 11:49", t);
    a.inserir("13/11/2018 11:50", t);
    a.inserir("13/11/2018 11:51", t);
    a.inserir("13/11/2018 11:52", t);
    a.inserir("13/11/2018 11:53", t);
    a.inserir("13/11/2018 11:54", t);
    a.inserir("13/11/2018 11:55", t);
    a.inserir("13/11/2018 11:56", t);
    a.imprime();
    
    a.remover("13/11/2018 11:46", t);
    a.remover("13/11/2018 11:56", t);
    a.remover("13/11/2018 11:52", t);
    
    cout << endl;
    a.imprime();
    return 0;
}

