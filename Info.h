/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Info.h
 * Author: user-pc
 *
 * Created on 14 de Novembro de 2018, 12:59
 */

#include <string>
#ifndef INFO_H
#define INFO_H

using namespace std;

class Info {
    friend class Noh;
    private:
        string data;
        float temperatura;
};

#endif /* INFO_H */