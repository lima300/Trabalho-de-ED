/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 * 
 *  Arquivo principal
 * 
 * O trabalho consiste em uma aplicação que capta os dados de Data e
 * Temperatura de um sensor para Arduino (Real Time Clock RTC DS3231)
 * e armazena nas estruturas de dados.
 * 
 * As estruturas utilizadas são:
 *      - Árvore AVL;
 *      - Lista encadeada;
 * 
 *  ~ Cada nó da Árvore possui como chave uma data, e armazena as
 *    temperaturas do dia em que a leitura dos dados foi efetuada,
 *    ou seja, cada nó é correspondente a um dia;
 *  ~ Cada dia possui uma Lista que armazena em seus nós uma temperatura
 *    medida no momento da inserção.
 * 
 *  O programa funciona através do Monitor Serial do Arduino, onde o usuário
 * escolhe entre as opções dispostas para a execução de operações.
 *      - I: Insere uma nova temperatura
 *      - R: Remove o dia atual
 *      - E: Escreve as temperaturas dos dias
 *      - B: Buscar as temperaturas de um dia
 *      - S: Salva os dados em um arquivo no SD
 *      - D: Reconfigura a data do sensor
 */

//Inclusão das bibliotecas e classes necessárias
//para funcionamento do programa
#include "AVL.h"
#include "Data.h"
#include "Lista.h"
#include <Time.h>
#include <Wire.h>
#include <DS3232RTC.h> //Biblioteca utilizada pelo sensor
#include <Streaming.h> //Biblioteca para facilitar o uso do Serial (Semelhante à <iostream>)
#include <SPI.h> //Biblioteca para sincronia de periféricos
#include <SD.h> //Biblioteca para uso do Cartão Micro SD

int pino = 4;
time_t t = now();
tmElements_t tm;
int dia = day(t);
int mes = month(t);
int ano = year(t);
Data* atual = new Data(dia,mes,ano);
AVL arvore;

void setup(void){ //Configurar o Arduino
    
    Serial.begin(9600); //Inicia a Serial
    while (not Serial); //Aguarda a Serial estar pronta
    startSD(); //Inicializa o cartão SD
    
    setSyncProvider(RTC.get); //Inicializa o Sensor RTC e sincroniza com a biblioteca Time
    Serial << F("Sincronizando sensor RTC...");
    if (timeStatus() != timeSet)
        Serial << F(" Falha!");
    else
        Serial << F(" OK!");
    Serial << endl << endl << endl;
    
    //Impressão do menu de opções
    Serial  << F("|------------------| MENU |------------------|") <<  endl
            << F("|                                            |") <<  endl
            << F("|          Opções:                           |") <<  endl
            << F("|          I > Inserir temperatura           |") <<  endl
            << F("|          R > Remover temperatura           |") <<  endl
            << F("|          E > Imprimir ordenado             |") <<  endl
            << F("|          B > Buscar  temperatura           |") <<  endl
            << F("|          S > Salvar dados                  |") <<  endl
            << F("|          D > Configurar data               |") <<  endl
            << F("|                                            |") <<  endl
            << F("|---------------------//---------------------|") <<  endl
            << F("Escolha uma opção:") << endl;
}

char lastOp = ' '; //Utilizado para controle do loop

void loop(void){
    float temperatura;
    char operacao;
    
    while(!Serial.available()); //Aguarda um valor ser digitado na Serial
    operacao = Serial.read();
    Serial.flush(); //Limpa o histórico da Serial
    
    if (operacao != lastOp){ //Condição para controlar o loop
         Serial.flush();
         if (operacao == 'I' or operacao == 'i'){ // Inserir
             temperatura = RTC.temperature() / 4.;
             arvore.inserirRec(atual, temperatura);
             Serial.println("Inserido com sucesso!");

             Serial << endl;
         } else if (operacao == 'R' or operacao == 'r'){// Remover
             arvore.removerRec(atual);

             Serial << F("operação realizada") << endl;
         }else if (operacao == 'E' or operacao == 'e'){ // Escrever
               arvore.Order();
               
               Serial << endl;
         } else if (operacao == 'B' or operacao == 'b'){ // Buscar
             Serial.flush();
             Serial << F("Insira Data a ser pesquisada : (YYYY, MM, DD)") << endl;
             delay(5000);
             
             ano = Serial.parseInt();
             mes = Serial.parseInt();
             dia = Serial.parseInt();

             Serial << F("Pesquisando a data: ") << dia << F("/") << mes << F("/") << ano << endl;
             
             Data buscar(dia, mes, ano);
             while (Serial.available() > 0) Serial.read();

             arvore.busca(&buscar);

             Serial << endl;
         } else if (operacao == 'S' or operacao == 's'){ //Salvar os dados em arquivo
              arvore.save();
              
              Serial << F("Salvo") << endl;    
         } else if (operacao == 'D' or operacao == 'd'){ //Configurar a Data do sensor
             setDate();
             
             Serial << endl;
         }
         
         lastOp = operacao; //Atualiza o controle do loop
    }
}

//Função para iniciar o módulo SD
void startSD(){
    pinMode(pino, OUTPUT);
 
    if (SD.begin()){
    } else {
        return;
    }
}

//Função de configuração da data no RTC e inserção
void setDate(){
    Serial.flush();
    Serial << F("Insira data : (YYYY, MM, DD)") << endl;
    delay(7000);
    
    if (Serial.available() >= 12) {
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("O ano deve possuir dois, ou quatro dígitos!") <<endl;
        else {
            if (y >= 1000) //Se ano tiver quatro dígitos, altera o ano
                tm.Year = CalendarYrToTm(y);
            else    //(y < 100) //Se ano tiver dois dígitos, converte e altera o ano
                tm.Year = y2kYearToTm(y);

            //Comandos da biblioteca do sensor para configuração
            tm.Month = Serial.parseInt(); 
            tm.Day = Serial.parseInt();
            t = makeTime(tm);
            RTC.set(t);
            setTime(t);
            t = now();
            dia = day(t);
            mes = month(t);
            ano = year(t);
            atual->set(dia, mes, ano);
            
            Serial << F("Data modificada para: ");
            Serial << day(t) << F("/") << month(t)<< F("/") << year(t)<< F(".");
            Serial << endl;
            while (Serial.available() > 0) Serial.read();
        }
    }
}
