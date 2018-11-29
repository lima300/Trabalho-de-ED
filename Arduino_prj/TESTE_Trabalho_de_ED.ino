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

#include "AVL.h"
#include "Data.h"
#include "Lista.h"
#include <DS3232RTC.h>
#include <Streaming.h>
#include <Time.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

int CS_PIN = 4;

void setup(void){
  Serial.begin(9600);
  while (not Serial);
  setSyncProvider(RTC.get);
  Serial << F("|------------------| MENU |------------------|") <<  endl
             << F("|                                            |") <<  endl
             << F("|          Opções:                           |") <<  endl
             << F("|          I > Inserir temperatura           |") <<  endl
             << F("|          R > Remover temperatura           |") <<  endl
             << F("|          B > Buscar  temperatura           |") <<  endl
             << F("|          E > Imprimir ordenado             |") <<  endl
             << F("|          S > Salvar dados                  |") <<  endl
             << F("|          C > Carregar dados                |") <<  endl
             << F("|                                            |") <<  endl
             << F("|---------------------//---------------------|") <<  endl
             << F("Escolha uma opção:") << endl;
}

void loop(void){
    AVL arvore;
    
    float valor;
    char operacao;    
       while(!Serial.available());
       operacao = Serial.read();
       Serial.flush();
       if (operacao == 'I'){ // Inserir
           while(!Serial.available());
           int dia = Serial.parseInt();
           Serial.flush();
           while(!Serial.available());
           int mes = Serial.parseInt();
           Serial.flush();
           while(!Serial.available());
           int ano = Serial.parseInt();
           Serial.flush();
           
           Data atual(dia,mes,ano);
           valor = RTC.temperature() / 4.;
           arvore.inserirRec(&atual, valor);
           Serial << F("insercao feita") << endl;
                
       } else if (operacao == 'R'){// Remover
           Serial << F("digite um valor") << endl;
           while(!Serial.available());
           valor = Serial.parseFloat();
           while(!Serial.available());
           int dia = Serial.parseInt();
           Serial.flush();
           while(!Serial.available());
           int mes = Serial.parseInt();
           Serial.flush();
           while(!Serial.available());
           int ano = Serial.parseInt();
           Serial.flush();
           
           Data atual(dia,mes,ano);
           arvore.removerRec(&atual, valor);

       } else if (operacao == 'B'){
           Serial << F("Ainda não implementado!") << endl;
            
       } else if (operacao == 'E'){ // Escrever tudo
           arvore.preOrder();
       } else if (operacao == 'S'){
           Serial << F("Implementação omitida") << endl;
                
            /*if(arvore.save()){
                Serial << F("Salva com sucesso!") << endl;
            } else {
                Serial << F("Não foi possível salvar o arquivo!") << endl;
            }*/
                
       } else if (operacao == 'C'){ //Carregar
           Serial << F("Implementação omitida") << endl;
            
            /*if(arvore.read()){
                Serial << "Carregada com sucesso!\n";
            } else {
                Serial << "Erro na leitura do arquivo!\n";
            }*/
                
       } else if (operacao == 'F'){
       } else {
           Serial.println("OPCAO INVALIDA");
       }
       delay(5000);
}
