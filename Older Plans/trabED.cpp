#include <iostream>
#include <exception>
using namespace std;

class Data {
    friend class info;
    friend class Noh;
    friend class Lista;
    friend class AVL;
    private:
        int dia;
        int mes;
        int ano;
    public:
    Data (int d, int m, int a);
    bool operator < (Data* d);
    bool operator > (Data* d);
};

Data::Data(int d , int m, int a){
    dia = d;
    mes = m;
    ano = a;
}

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

class Noh {
    friend class Lista;
    private:
        float mTemperatura;
        Noh* mPtProx;
    public:
        Noh(float t);
};

Noh::Noh(float t){
    mTemperatura = t;
    mPtProx = NULL;
}

class Lista {
    friend class AVL;
    private:
        Noh* mPtPrimeiro;
        Noh* mPtUltimo;
        int mTamanho;
    public:
        Lista();
        ~Lista();
        bool Vazia ();
        void Inserir(float t);
        void Remover(float t);
        void Imprime() const;
        Noh* Buscar(float t);
};

Lista::Lista(){
    mPtPrimeiro = NULL;
    mPtUltimo = NULL;
    mTamanho = 0;
}

Lista::~Lista(){
    Noh* iter = mPtPrimeiro;
    Noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->mPtProx;
        delete iter;
        iter = proximo;
    }
};

bool Lista::Vazia(){
    return mPtPrimeiro == NULL and mPtUltimo == NULL and mTamanho == 0;
}

void Lista::Inserir(float t){
    Noh* novo = new Noh(t);
    if (Vazia()){
        mPtPrimeiro = novo;
        mPtUltimo = novo;
        
    } else {
        mPtUltimo->mPtProx = novo;
        mPtUltimo = novo;
    }
    mTamanho++;
}

void Lista::Remover(float t){
    if (Vazia()){
        throw runtime_error ("Impossivel Remover em lista vazia");
    } else {
        Noh* remover = Buscar(t);
        if(remover == mPtPrimeiro){
            if (mTamanho == 1){
                mPtPrimeiro = NULL;
                mPtUltimo = NULL;
            } else {
                mPtPrimeiro = mPtPrimeiro->mPtProx;
            }
        } else {
            Noh* atual = mPtPrimeiro;
            Noh* anterior = NULL;
            while (atual != remover){
                anterior = atual;
                atual = atual->mPtProx;
            }
            if (atual == mPtUltimo){
                anterior->mPtProx = NULL;
                mPtUltimo = anterior;
            } else {
                anterior->mPtProx = atual->mPtProx;
            }
        }
        mTamanho--;
        delete remover;
    }
}

// metodo basico que *percorre* a lista, imprimindo seus elementos
void Lista::Imprime() const {
    Noh* iter = mPtPrimeiro;
    float t;
    while (iter != NULL) {
        t = iter->mTemperatura;
        cout << t << endl;
        iter = iter->mPtProx;
    }
}

Noh* Lista::Buscar(float t){
    Noh* atual = mPtPrimeiro;
    bool encontrado = false;
    
    while (atual != NULL and encontrado == false ){
        if (atual->mTemperatura == t){
            encontrado = true;
        } else {
            atual = atual->mPtProx;
        }
    }
    if (encontrado == false){
        throw invalid_argument ("Elemento não existe");
    } else {
        return atual;
    }
}

class NohAVL{
    friend class AVL;
    private:
        Data* chave;
        Lista* lista;
        NohAVL* esq;
        NohAVL* dir;
        NohAVL* pai;
        unsigned int altura;
    public:
        NohAVL(Data* d);
        ~NohAVL();
};

NohAVL::NohAVL(Data* d){
    chave = d;
    lista = NULL;
    esq = NULL;
    dir = NULL;
    pai = NULL;
};

NohAVL::~NohAVL(){
    delete esq;
    delete dir;
}

class AVL {
    friend class NohAVL;
    private:
        NohAVL* raiz;
    public:
        AVL();
        ~AVL();
        int informaAltura(NohAVL* umNoh);
        void atualizarAltura(NohAVL* umNoh);
        int maximo(int a, int b);
        int fatorBalanceamento(NohAVL* umNoh);
        NohAVL* rotacaoEsquerda(NohAVL* umNoh);
        NohAVL* rotacaDireita(NohAVL* umNoh);
        NohAVL* rotacaoEsquerdaDireita (NohAVL* umNoh);
        NohAVL* rotacaoDireitaEsquerda (NohAVL* umNoh);
        void inserirRec (Data* d, float t);
        NohAVL* inserirRecAux (NohAVL* umNoh, Data* d, float t);
        NohAVL* arrumarBalanciamento(NohAVL* umNoh);
        void removerRec(Data* d, float t);
        NohAVL* removerRecAux(NohAVL* umNoh, Data* d);
        void preOrder(){ preOrderAux(raiz);}
        void preOrderAux(NohAVL* umNoh);
        NohAVL* minimoAux (NohAVL* atual);
        Lista* busca (Data* d);
};

AVL::AVL(){
    raiz = NULL;
}

AVL::~AVL(){
    delete raiz;
}

int AVL::informaAltura(NohAVL* umNoh){
    if (umNoh == NULL){
        return 0;
    } else {
        return umNoh->altura;
    }
}

void AVL::atualizarAltura(NohAVL* umNoh){
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

int AVL::fatorBalanceamento(NohAVL* umNoh){
    int altEsq = informaAltura(umNoh->esq);
    int altDir = informaAltura(umNoh->dir);
    
    return altEsq - altDir;
}

NohAVL* AVL::rotacaoEsquerda(NohAVL* umNoh){
    NohAVL* aux = umNoh->dir;
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

NohAVL* AVL::rotacaDireita(NohAVL* umNoh){
    NohAVL* aux = umNoh->esq;
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

NohAVL* AVL::rotacaoEsquerdaDireita (NohAVL* umNoh){
    umNoh->esq = rotacaoEsquerda(umNoh->esq);
    return rotacaDireita(umNoh);
}

NohAVL* AVL:: rotacaoDireitaEsquerda (NohAVL* umNoh){
    umNoh->dir = rotacaDireita(umNoh->dir);
    return rotacaoEsquerda(umNoh);
}

void AVL::inserirRec(Data* d, float t){
    Lista* buscado = busca (d);
    if (buscado != NULL){
        buscado->Inserir(t);
    } else {
        raiz = inserirRecAux(raiz, d, t);
    }
}

NohAVL* AVL::inserirRecAux (NohAVL* umNoh, Data* d, float t){
    if (umNoh == NULL){
        NohAVL* novo = new NohAVL(d);
        novo->lista->Inserir(t);
        return novo;
    } else if (d < umNoh->chave){
        umNoh->esq = inserirRecAux(umNoh->esq, d, t);
        umNoh->esq->pai = umNoh;
    } else {
        umNoh->dir = inserirRecAux(umNoh->dir, d, t);
        umNoh->dir->pai = umNoh;
    }
    return arrumarBalanciamento(umNoh);
}

NohAVL* AVL::arrumarBalanciamento(NohAVL* umNoh){
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

void AVL::preOrderAux(NohAVL* umNoh){
    if(umNoh != NULL) { 
        cout << umNoh->chave->dia << "/" <<umNoh->chave->mes << "/"
             << umNoh->chave->ano <<endl; 
        preOrderAux(umNoh->esq); 
        preOrderAux(umNoh->dir); 
    }
}

void AVL::removerRec(Data* d, float t){
    Lista* buscado = busca(d);
    if (buscado != NULL){
        if (buscado->mTamanho == 1){
            buscado->Remover(t);
            raiz = removerRecAux(raiz, d);
        } else {
            buscado->Remover(t);
        }
    } else {
        throw invalid_argument ("Elemento não encontrado");
    }
}

NohAVL* AVL::removerRecAux(NohAVL* umNoh, Data* d){
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
            NohAVL* temp = umNoh->esq ? umNoh->esq : 
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
            NohAVL* temp = minimoAux(umNoh->dir); 
            umNoh->chave = temp->chave; 
            umNoh->dir = removerRecAux(umNoh->dir, temp->chave); 
        } 
    } 
    if (umNoh == NULL) 
        return umNoh; 
    return arrumarBalanciamento(umNoh);
}

NohAVL* AVL::minimoAux(NohAVL* atual){
    //Retorna o minimo da arvore
    while(atual -> esq != NULL){
        atual = atual -> esq;
    }
    return atual;
}

Lista* AVL::busca(Data* d){
    NohAVL* atual = raiz;
    while(atual != NULL and atual->chave == d){
        if(atual->chave > d){
            atual = atual->esq;
        }
        else{
            atual = atual->dir;
        }
    }
    if (atual != NULL){
        cout << "achei";
        return atual->lista;
    } else {
        cout << "nao achei";
        return NULL;
    }
}
    

int main() { // NÃO MODIFIQUE!
    Data atual = Data(21,11,2018);
    
    AVL a;
    float t;
    cin >> t;
    
    a.inserirRec(&atual, t);
    
    return 0;
}
