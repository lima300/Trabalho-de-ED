#include <iostream>
#include <exception>
using namespace std;
class Noh{
    friend class AVL;
    private:
        Data chave;
        Lista lista;
        Noh* esq;
        Noh* dir;
        Noh* pai;
        unsigned int altura;
    public:
        Noh(int d);
        ~Noh();
};

Noh::Noh(Data d){
    chave = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
};

Noh::~Noh(){
    delete esq;
    delete dir;
}

class AVL {
    friend class Noh;
    private:
        Noh* raiz;
    public:
        AVL();
        ~AVL();
        int informaAltura(Noh* umNoh);
        void atualizarAltura(Noh* umNoh);
        int maximo(int a, int b);
        int fatorBalanceamento(Noh* umNoh);
        Noh* rotacaoEsquerda(Noh* umNoh);
        Noh* rotacaDireita(Noh* umNoh);
        Noh* rotacaoEsquerdaDireita (Noh* umNoh);
        Noh* rotacaoDireitaEsquerda (Noh* umNoh);
        void inserirRec (int d);
        Noh* inserirRecAux (Noh* umNoh, int d);
        Noh* arrumarBalanciamento(Noh* umNoh);
        void removerRec(int d);
        Noh* removerRecAux(Noh* umNoh, int d);
        void preOrder(){ preOrderAux(raiz);}
        void preOrderAux(Noh* umNoh);
        Noh* minimoAux (Noh* atual);
};

AVL::AVL(){
    raiz = NULL;
}

AVL::~AVL(){
    delete raiz;
}

int AVL::informaAltura(Noh* umNoh){
    if (umNoh == NULL){
        return 0;
    } else {
        return umNoh->altura;
    }
}

void AVL::atualizarAltura(Noh* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    umNoh->altura = 1 + maximo(altEsq, altDir);
}

int AVL::maximo(int a, int b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

int AVL::fatorBalanceamento(Noh* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    return altEsq - altDir;
}

Noh* AVL::rotacaoEsquerda(Noh* umNoh){
    Noh* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    
    if (aux->esq != NULL){
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

Noh* AVL::rotacaDireita(Noh* umNoh){
    Noh* aux = umNoh->esq;
    umNoh->dir = aux->dir;
    
    if (aux->dir != NULL){
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

Noh* AVL::rotacaoEsquerdaDireita (Noh* umNoh){
    umNoh->esq = rotacaoEsquerda(umNoh->esq);
    return rotacaDireita(umNoh);
}

Noh* AVL:: rotacaoDireitaEsquerda (Noh* umNoh){
    umNoh->dir = rotacaDireita(umNoh->dir);
    return rotacaoEsquerda(umNoh);
}

void AVL::inserirRec(int d){
    raiz = inserirRecAux(raiz, d);
}

Noh* AVL::inserirRecAux (Noh* umNoh, int d){
    if (umNoh == NULL){
        Noh* novo = new Noh(d);
        return novo;
    } else if (d < umNoh->chave){
        umNoh->esq = inserirRecAux(umNoh->esq, d);
        umNoh->esq->pai = umNoh;
    } else {
        umNoh->dir = inserirRecAux(umNoh->dir, d);
        umNoh->dir->pai = umNoh;
    }
    return arrumarBalanciamento(umNoh);
}

Noh* AVL::arrumarBalanciamento(Noh* umNoh){
    atualizarAltura(umNoh);
    int bal = fatorBalanceamento(umNoh);
    
    if ((bal >= -1) and (bal <= 1)){
        return umNoh;
    }
    
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) >= 0)){
        return rotacaDireita(umNoh);
    }
    if ((bal > 1) and (fatorBalanceamento(umNoh->esq) < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh);
        return rotacaDireita(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) <= 0)){
        return rotacaoEsquerda(umNoh);
    }
    if ((bal < -1) and (fatorBalanceamento(umNoh->dir) > 0)){
        umNoh->dir = rotacaDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}

void AVL::preOrderAux(Noh* umNoh){
    if(umNoh != NULL) { 
        cout << umNoh->chave << endl; 
        preOrderAux(umNoh->esq); 
        preOrderAux(umNoh->dir); 
    }
}

void AVL::removerRec(int d){
    raiz = removerRecAux(raiz, d);
}

Noh* AVL::removerRecAux(Noh* umNoh, int d){
    if (umNoh == NULL){
        return umNoh;
    } 
    if ( d < umNoh->chave ){ 
        umNoh->esq = removerRecAux(umNoh->esq, d);
    } else if( d > umNoh->chave ) { 
        umNoh->dir = removerRecAux(umNoh->dir, d);
    } else { 
        // node with only one child or no child 
        if ((umNoh->esq == NULL) or (umNoh->dir == NULL)){ 
            Noh *temp = umNoh->esq ? umNoh->esq : 
                                             umNoh->dir; 
  
            if (temp == NULL) { 
                temp = umNoh; 
                umNoh = NULL; 
            } 
            else { // One child case 
                *umNoh = *temp;
            }
            delete temp;
        } else { 
            Noh* temp = minimoAux(umNoh->dir); 
            umNoh->chave = temp->chave; 
            umNoh->dir = removerRecAux(umNoh->dir, temp->chave); 
        } 
    } 
    if (umNoh == NULL) 
        return umNoh; 
    return arrumarBalanciamento(umNoh);
}

Noh* AVL::minimoAux(Noh* atual){
    //Retorna o minimo da arvore
    while(atual -> esq != NULL){
        atual = atual -> esq;
    }
    return atual;
}

int main(){
    AVL a;
    a.inserirRec(1); 
    a.inserirRec(2); 
    a.inserirRec(3); 
    a.inserirRec(4); 
    a.inserirRec(5); 
    a.inserirRec(6);
    a.removerRec(3);
    a.removerRec(4);
    a.preOrder();
    
    
    
return 0;
}
