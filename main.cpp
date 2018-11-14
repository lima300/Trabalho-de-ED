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

