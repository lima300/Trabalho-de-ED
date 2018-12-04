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
    int dia = 0;
    int mes = 0;
    int ano = 0;
    
    Data atual = Data(dia,mes, ano);
    AVL arvore;
    
    float valor;
    char operacao;
    
    do {
        //string dataAtual = atual.get();
        
        /*cout << "|------------------| MENU |------------------|" <<  endl
             << "|                                            |" <<  endl
             << "|          Opções:                           |" <<  endl
             << "|          I > Inserir temperatura           |" <<  endl
             << "|          R > Remover temperatura           |" <<  endl
             << "|          B > Buscar  temperatura           |" <<  endl
             << "|          E > Imprimir ordenado             |" <<  endl
             << "|          S > Salvar dados                  |" <<  endl
             << "|          C > Carregar dados                |" <<  endl
             << "|                                            |" <<  endl
             /*<< "|         Data a inserir: "
                                     << dataAtual <<"         |" <<  endl
             << "|                                            |" <<  endl
             << "|---------------------//---------------------|" <<  endl
             << "Escolha uma opção:\n";*/
        
        cin >> operacao;
        switch (operacao) {
            case 'I': // Inserir
                cout << "DATA" << endl;
                
                cin >> dia >> mes >> ano;
                
                atual.alterar(dia, mes, ano);
                
                cout << "Digite a temperatura a ser inserida:\n";
                
                cin >> valor;
                
                arvore.inserirRec(&atual, valor);
                break;
            case 'R': // Remover
                cin >> valor;
                arvore.removerRec(&atual, valor);
                break;
            case 'B': // Buscar
                cout << "DATA" << endl;
                cin >> dia >> mes >> ano;
                atual.alterar(dia, mes, ano);
                arvore.busca(&atual);
                break;
                
            case 'E': // Escrever tudo
                arvore.Order();
                break;
            case 'S':
                
                if(arvore.save()){
                    cout << "Salva com sucesso!\n";
                } else {
                    cerr << "Não foi possível salvar o arquivo!\n";
                }
                
                break;
            case 'C':
                if(arvore.read()){
                    cout << "Carregada com sucesso!\n";
                } else {
                    cerr << "Erro na leitura do arquivo!\n";
                }
                
                break;
            default:
                cout << "Opção inválida! Tente novamente!" << endl;
                
                break;
        }
    } while (operacao != 'F');
    
    return 0;
}

