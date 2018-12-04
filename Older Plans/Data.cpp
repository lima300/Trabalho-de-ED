/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data.cpp
 * Author: kellyson
 * 
 * Created on 23 de Novembro de 2018, 20:50
 */

#include "Data.h"
#include <sstream>

Data::Data(int d , int m, int a){
    dia = d;
    mes = m;
    ano = a;
}

void Data::alterar(int d, int m, int a){
    dia = d;
    mes = m;
    ano = a;
}

bool Data::operator < (Data* d){
    
    cout << "TO COMPARANDO SE EH MENOR!\n";
    
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

bool Data::operator > (Data* d){
    
    cout << "TO COMPARANDO SE EH MAIOR!\n";
    
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

bool Data::operator == (Data* d){
    
    cout << "TO COMPARANDO SE EH IGUAL!\n";
    
    return ano == d->ano and mes == d->mes and dia == d->dia;
}

bool Data::operator != (Data* d){
    
    cout << "TO COMPARANDO SE EH DIFERENTE!\n";
    
    if (ano == d->ano and mes == d->mes and dia == d->dia){
        cout << "NÃO É!\n";
        return false;
    }
    
    return true;
}

string Data::get(){
    string da = to_string(dia);
    string mo = to_string(mes);
    string ye = to_string(ano);
    return da + " " + mo + " " + ye;
}