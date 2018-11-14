/*
 * Trabalho Final de Estrutura de Dados
 * By: Kellyson Santos e Otavio Lima
 * UFLA - 2018/2
 * 
 * Arquivo de Cabeçalho: Lista Encadeada
 * 
 * Esse arquivo contém a declaração da classe Lista, em que são armazenadas as temperaturas de cada dia.
 * Cada Noh da lista armazena a temperatura de determinado horário de um dia.
 * 
 * A Classe possui os atributos:
 *    - Primeiro (Um ponteiro apontando para o primeiro Noh da Lista)
 *    - Ultimo (Um ponteiro apontando para o último Noh da lista - Facilita a inserção no fim da lista)
 *
 * As listas são armazenadas em uma Árvore AVL, onde cada Noh da AVL é um dia.
 */

/* 
 * File:   Lista.h
 * Author: Kellyson Santos / Otavio Lima
 *
 * Created on 14 de Novembro de 2018, 12:28
 */

#ifndef LISTA_H
#define LISTA_H
#include "Noh.h"

using namespace std;

class Lista {
    private:
        Noh* primeiro;
        Noh* ultimo;
        int tamanho;
    public:
        Lista();
        ~Lista();
        bool vazia ();
        void inserir(string d,float t);
        void remover(string d,float t);
        void imprime() const;
        Noh* buscar(string d,float t);
};

#endif /* LISTA_H */

