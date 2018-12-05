/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de código fonte: Noh.cpp
 * 
 * Implementação dos métodos da Classe Noh:
 *      - construtor
 *
 * Criado em 23 de Novembro de 2018
 */
 
#include "Noh.h"

using namespace std;

//Construtor
Noh::Noh(float t){
    mTemperatura = t;
    mPtProx = nullptr;
}
