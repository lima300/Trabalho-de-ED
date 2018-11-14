/*
 * Trabalho Final de Estrutura de Dados
 * By: Kellyson Santos e Otavio Lima
 * UFLA - 2018/2
 * 
 * Arquivo de Classe: Noh da Lista Encadeada
 * 
 * Esse arquivo contém a implementação da classe Noh, que compõe as listas do programa.
 * Cada Noh da lista armazena a temperatura de determinado horário de um dia.
 * 
 * A Classe possui os métodos:
 *    - Construtor
 *    - Destrutor
 * 
 * As listas são armazenadas em uma Árvore AVL, onde cada Noh da AVL é um dia.
 */

/* 
 * File:   Noh.cpp
 * Author: user-pc
 * 
 * Created on 14 de Novembro de 2018, 12:28
 */

#include "Noh.h"

Noh::Noh(string d, float t){
    valor.data = d;
    valor.temperatura = t;
    prox = NULL;
}

float Noh::getTemp(){
    return valor.temperatura;
}

string Noh::getData(){
    return valor.data;
}