#include <iostream>
#include <exception>

using namespace std;

typedef string Texto;

class info {
    friend class noh;
    public:
        string mData;
        float mTemperatura;
};

class Noh {
    friend class Lista;
    private:
        info mValor;
        Noh* mPtProx;
    public:
        Noh(string d,float t);
};

Noh::Noh(string d, float t){
    mValor.mData = d;
    mValor.mTemperatura = t;
    mPtProx = NULL;
}

class Lista {
    private:
        Noh* mPtPrimeiro;
        Noh* mPtUltimo;
        int mTamanho;
    public:
        Lista();
        ~Lista();
        bool Vazia ();
        void Inserir(string d,float t);
        void Remover(string d,float t);
        void Imprime() const;
        bool Buscar(string d,float t);
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

void Lista::Inserir(string d, float t){
    Noh* novo = new Noh(d,t);
    
    if (Vazia()){
        mPtPrimeiro = novo;
        mPtUltimo = novo;
        
    } else {
        mPtUltimo->mPtProx = novo;
        mPtUltimo = novo;
    }
    mTamanho++;
}

// metodo basico que *percorre* a lista, imprimindo seus elementos
void Lista::Imprime() const {
    Noh* iter = mPtPrimeiro;
    float t;
    while (iter != NULL) {
        t = iter->mValor.mTemperatura;
        cout << iter->mValor.mData << " -> " << t << endl;
        iter = iter->mPtProx;
    }
}

bool Lista::Buscar(string d, float t){
    Noh* atual = mPtPrimeiro;
    
    while (atual != NULL){
        if (atual->mValor.mData == d and atual->mValor.mTemperatura == t){
            cout << atual->mValor.mData << " : " << atual->mValor.mTemperatura << endl;
            return true;
        }
        atual = atual->mPtProx;
    }
    return false;
}
    

int main() { // NÃO MODIFIQUE!
    Lista a;
    float t;
    cin >> t;
    a.Inserir("13/11/2018 11:46", t);
    a.Inserir("13/11/2018 11:47", t);
    a.Inserir("13/11/2018 11:48", t);
    a.Inserir("13/11/2018 11:49", t);
    a.Inserir("13/11/2018 11:50", t);
    a.Inserir("13/11/2018 11:51", t);
    a.Inserir("13/11/2018 11:52", t);
    a.Inserir("13/11/2018 11:53", t);
    a.Inserir("13/11/2018 11:54", t);
    a.Inserir("13/11/2018 11:55", t);
    a.Inserir("13/11/2018 11:56", t);
    
    a.Imprime();
    return 0;
}
