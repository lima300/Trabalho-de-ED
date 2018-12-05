/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de código fonte: Data.cpp
 * 
 * Implementação dos métodos da Classe Data:
 *      - construtor
 *      - set
 * 
 * Implementação da sobrecarga dos operadores:
 *      <  - Menor (Retorna true caso a data seja anterior à comparada)
 *      >  - Maior (Retorna true caso a data seja posterior à comparada)
 *      == - Igual (Retorna caso as datas comparadas sejam iguais)
 *      != - Diferente (Retorna true caso as datas comparadas não sejam as mesmas)
 *
 * Criado em 23 de Novembro de 2018
 */

#include "Data.h"
#include "Arduino.h" //Biblioteca para uso do Serial

// Construtor
Data::Data(int d , int m, int a){
    dia = d;
    mes = m;
    ano = a;
}

// Altera os atributos atuais pelos recebidos
void Data::set(int d , int m, int a){
    dia = d;
    mes = m;
    ano = a;
}

// Sobrecarga do operador MENOR
bool Data::operator < (Data* d){
    if (ano > d->ano){
        return false;
    } else if (ano < d->ano){
        return true;
    } else {
        if (mes > d->mes){
            return false;
        } else if (mes < d->mes){
            return true;
        } else {
            if (dia >= d->dia){
                return false;
            } else {
                return true;
            }
        }
    }
}

// Sobrecarga do operador MAIOR
bool Data::operator > (Data* d){
    if (ano > d->ano){
        return true;
    } else if (ano < d->ano){
        return false;
    } else {
        if (mes > d->mes){
            return true;
        } else if (mes < d->mes){
            return false;
        } else {
            if (dia >= d->dia){
                return true;
            } else {
                return false;
            }
        }
    }
}

// Sobrecarga do operador IGUAL
bool Data::operator == (Data* d){
    return ano == d->ano and mes == d->mes and dia == d->dia;
}

// Sobrecarga do operador DIFERENTE
bool Data::operator != (Data* d){
    if (ano == d->ano and mes == d->mes and dia == d->dia){
        return false;
    }
    return true;
}
