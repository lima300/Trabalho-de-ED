/*
 * Trabalho Final de Estrutura de Dados
 * 
 * Por: Kellyson Santos (201820366) e Otavio Lima (201811022)
 * UFLA - 2018/2
 *
 * Arquivo de código fonte: AVL.cpp
 * 
 * Implementação dos métodos da Classe AVL:
 *      - construtor
 *      - destrutor
 *      - informaAltura
 *      - atualizarAltura
 *      - maximo
 *      - fatorBalanceamento
 *      - rotacaoEsquerda
 *      - roracaoDireira
 *      - inserirRec
 *      - inserirRecAux
 *      - arrumarBalanceamento
 *      - removerRec
 *      - removerRecAux
 *      - order
 *      - orderAux
 *      - minimoAux
 *      - busca
 *      - save
 *      - recursiveSave
 * 
 *  A descrição de cada método se encontra em sua implementação
 * 
 *  O arquivo possui duas funções auxiliares, que não são métodos, e são
 * utilizadas para facilitar o manuseio do arquivo no método de salvamento
 *
 * Criado em 23 de Novembro de 2018
 */

#include "Arduino.h"
#include "Streaming.h"
#include "NohAVL.h"
#include "Lista.h"
#include "AVL.h"
#include "Data.h"
#include <SPI.h>
#include <SD.h>

File file; //Declara a variável para salvamento do arquivo

//Inicializa a raiz
AVL::AVL(){
    raiz = nullptr;
}

//Destrutor: desaloca a raiz
AVL::~AVL(){
    delete raiz;
}

// Método que retorna a altura de um Noh
int AVL::informaAltura(NohAVL* umNoh){
    if (umNoh == nullptr){
        return 0;
    } else {
        return umNoh->altura;
    }
}

// Método que atualiza a altura de um Noh
// Utilizado após a inserção e a remoção de um novo Noh
void AVL::atualizarAltura(NohAVL* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    umNoh->altura = 1 + maximo(altEsq, altDir);
}

// Retorna a maior altura entre subárvore
// à esquerda e à direita de um Noh
int AVL::maximo(int a, int b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

// Calcula o fator de balanceamento de uma subárvore
// Utilizado pela função de balanceamento
int AVL::fatorBalanceamento(NohAVL* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    return altEsq - altDir;
}

// Efetua a rotação em sentido anti-horário entre
// nós quando necessário
NohAVL* AVL::rotacaoEsquerda(NohAVL* umNoh){
    NohAVL* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    
    if (aux->esq != nullptr){
        aux->esq->pai = umNoh;
    }
    aux->pai = umNoh->pai;
    
    if (umNoh == raiz){
        raiz = aux;
    } else if (umNoh == umNoh->pai->esq){
        umNoh->pai->esq = aux;
    } else {
        umNoh->pai->dir = aux;
    }
    
    aux->esq = umNoh;
    umNoh->pai = aux;
    
    atualizarAltura(aux);
    atualizarAltura(umNoh);
    
    return aux;
}

// Efetua a rotação em sentido horário entre
// nós quando necessário
NohAVL* AVL::rotacaDireita(NohAVL* umNoh){
    NohAVL* aux = umNoh->esq;
    umNoh->dir = aux->dir;
    
    if (aux->dir != nullptr){
        aux->dir->pai = umNoh;
    }
    aux->pai = umNoh->pai;
    
    if (umNoh == raiz){
        raiz = aux;
    } else if (umNoh == umNoh->pai->esq){
        umNoh->pai->esq = aux;
    } else {
        umNoh->pai->dir = aux;
    }
    
    aux->dir = umNoh;
    umNoh->pai = aux;
    
    atualizarAltura(aux);
    atualizarAltura(umNoh);
    
    return aux;
}

// Chama o método recursivo passando a raiz como parâmetro
void AVL::inserirRec(Data* d, float t){
    raiz = inserirRecAux(raiz, d, t);
}

// Procura o lugar para inserção e insere recursivamente
NohAVL* AVL::inserirRecAux (NohAVL* umNoh, Data* d, float t){
    if (umNoh == NULL){ //Data ainda não existe, insere um novo Noh
        NohAVL* novo = new NohAVL(d);
        novo->lista->inserir(t);
        return novo;
        
    } else if (*d == umNoh->chave){ //Data já existe, insere na lista
        umNoh->lista->inserir(t);
        
    }else if (*d < umNoh->chave){ //Procura à esquerda
        umNoh->esq = inserirRecAux(umNoh->esq, d, t);
        umNoh->esq->pai = umNoh;
        
    } else { //Procura à direita
        umNoh->dir = inserirRecAux(umNoh->dir, d, t);
        umNoh->dir->pai = umNoh;
    }
 
    return arrumarBalanceamento(umNoh); //Arruma o balanceamento caso a árvore degenere
}

//Faz o balanceamento da árvore quando necessário
NohAVL* AVL::arrumarBalanceamento(NohAVL* umNoh){
    atualizarAltura(umNoh);
    int bal = fatorBalanceamento(umNoh);
    
    if ((bal >= -1) and (bal <= 1)){ //Balanceada
        return umNoh;
    }
    
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) >= 0)){ //Desbalanceada à esquerda
        return rotacaDireita(umNoh);
    }
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) < 0)){ //Rotação Esquerda/Direita
        umNoh->esq = rotacaoEsquerda(umNoh);
        return rotacaDireita(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) <= 0)){ //Desbalanceada à direita
        return rotacaoEsquerda(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) > 0)){ //Rotação Direita/Esquerda
        umNoh->dir = rotacaDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    
    return umNoh;
}

// Verifica se a árvore está vazia
// Se não estiver, imprime a árvore com o método auxiliar
void AVL::Order(){
  if(raiz){
    OrderAux(raiz);
  } else {
    Serial.println("Opa! Sua estrutura está vazia!");
  }
}

// Percorre a árvore imprimindo os nós ordenados pela chave recursivamente
void AVL::OrderAux(NohAVL* umNoh){
    if(umNoh != nullptr) {
        //Caso não seja nulo, visita o Noh à esquerda
        //imprime seu dado
        //caso não seja nulo, visita o Noh à direita
        OrderAux(umNoh->esq); 
        
        Serial.print(umNoh->chave->dia);
        Serial.print('/');
        Serial.print(umNoh->chave->mes);
        Serial.print('/');
        Serial.print(umNoh->chave->ano);
        umNoh->lista->imprime();
        
        OrderAux(umNoh->dir); 
    }
}

//Chama o método auxiliar recursivo passando a raiz como parâmetro
void AVL::removerRec(Data* d){
    raiz = removerRecAux(raiz, d);
}


NohAVL* AVL::removerRecAux(NohAVL* umNoh, Data* d){
    if (umNoh == nullptr){ //Fim da árvore
        return umNoh;
    }

    if (*d == umNoh->chave){ //Encontrou o Noh para remover
        
        // Nó com um ou nenhum filho
        if ((umNoh->esq == nullptr) or (umNoh->dir == nullptr)){ 
            //Operador ternário (Funciona como uma estrutura condicional)
            //Caso o filho à esquerda seja nulo, Noh auxiliar recebe o filho à direita
            //Caso seja válido, Noh auxiliar recebe o próprio filho à esquerda
            NohAVL* aux = umNoh->esq ? umNoh->esq : umNoh->dir;

            //Compara o Noh auxiliar
            if (aux == nullptr) { //Caso não tenha filhos
                aux = umNoh; 
                umNoh = nullptr; 
            } else { // Caso tenha um filho
                *umNoh = *aux;
            }
            
            delete aux;
        } else { //Caso tenha dois filhos
            NohAVL* aux = minimoAux(umNoh->dir); 
            umNoh->chave = aux->chave; 
            umNoh->dir = removerRecAux(umNoh->dir, aux->chave); 
        }
        
    } else if (*d < umNoh->chave ){ //Procura na subárvore à esquerda
        umNoh->esq = removerRecAux(umNoh->esq, d);
    } else { //Procura na subárvore à direita
        umNoh->dir = removerRecAux(umNoh->dir, d);
    }

    if (umNoh == nullptr){
          return umNoh;
    }
      
    return arrumarBalanceamento(raiz);
}

//Retorna o minimo da arvore recebida
NohAVL* AVL::minimoAux(NohAVL* atual){
    while(atual -> esq != NULL){
        atual = atual->esq;
    }
    return atual;
}

//Procura por uma data e imprime a lista caso encontrado
void AVL::busca(Data* d){
    NohAVL* atual = raiz;
    
    while(atual != nullptr and *atual->chave != d){
        
        if(*atual->chave > d){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    if (atual != nullptr){
        Serial.println("Data encontrada!");
        Serial.print("[");
        Serial.print(d->dia);
        Serial.print("/");
        Serial.print(d->mes);
        Serial.print("/");
        Serial.print(d->ano);
        Serial.print("]");
        
        atual->lista->imprime();
    } else {
        Serial.println("Data não encontrada!");
    }
}

//Percorre a lista em ordem salvando as temperaturas em arquivo recursivamente
int AVL::recursiveSave(NohAVL* noh){
    if(noh != nullptr){
        recursiveSave(noh->esq);

        openArq();
        file.print("[");
        file.print(noh->chave->dia);
        file.print("/");
        file.print(noh->chave->mes);
        file.print("/");
        file.print(noh->chave->ano);
        file.print("]");

        Noh* aux = noh->lista->mPtPrimeiro;

        while(aux){
          file.print(" -> ");
          file.print(aux->mTemperatura);
          aux = aux->mPtProx;
        }

        closeArq();

        recursiveSave(noh->dir);

        return 1;
    }
    
    return 0;
}

//Chama a função recursiva passando a raiz como parâmetro
void AVL::save(){
    if(recursiveSave(raiz)){
        Serial.println("Salvo com sucesso!");
    } else {
        Serial.println("Erro ao salvar arquivos");
    }
}

//Função auxiliar que abre o arquivo para escrita
int openArq(){
    file = SD.open("output.txt", FILE_WRITE);

    if (file){
        return 1;
    } else {
        return 0;
    }
}

//Função auxiliar para fechar o arquivo aberto
void closeArq(){
  if (file){
    file.close();
  }
}
