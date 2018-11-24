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
#include "AVL.h"
#include "Data.h"
#include "Lista.h"

using namespace std;

typedef string Texto;

int main() { // NÃO MODIFIQUE!
    Data atual = Data(21,11,2018);
    AVL arvore;
    
    float valor;
    char operacao;
    
    do {
        cin >> operacao;
        switch (operacao) {
            case 'I': // Inserir
                cin >> valor;
                arvore.inserirRec(&atual, valor);
                break;
            case 'R': // Remover
                cin >> valor;
                arvore.removerRec(&atual, valor);
                break;
            case 'B': // Buscar
                
                break;
            case 'E': // Escrever tudo
                arvore.preOrder();
                break;
            case 'S':
            
                break;
        }
    } while (operacao != 'F');
    
    return 0;
}

