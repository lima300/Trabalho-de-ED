if (umNoh == NULL){
        return umNoh;   
    }
    if (d < umNoh->chave){
        umNoh->esq = removerRecAux(umNoh->esq, d);
    } else if (d > umNoh->chave){
        umNoh->dir = removerRecAux(umNoh->dir, d);
    } else {
        Noh* novo = NULL;
        if (umNoh->esq == NULL){
            novo = umNoh->dir;
            transplanta(umNoh, umNoh->dir);
        } else if (umNoh->dir == NULL){
            novo = umNoh->esq;
            transplanta(umNoh, umNoh->esq);
        } else {
            Noh* sucessor = minimoAux(umNoh->dir);
            novo = sucessor;
            if (sucessor->pai != umNoh){
                transplanta(sucessor, sucessor->dir);
                Noh* aux = sucessor->pai;
                while (aux != umNoh->dir){
                    atualizarAltura(aux);
                    aux = aux->pai;
                }
                sucessor->dir = arrumarBalanciamento(umNoh->dir);
                sucessor->dir->pai = sucessor;
            }
            transplanta(umNoh, sucessor);
            sucessor->esq = umNoh->esq;
            sucessor->esq->pai = sucessor;
        }
        delete umNoh;
    
        if (novo == NULL){
            return novo;
        } else {
            return arrumarBalanciamento(novo);
        }
    }
    return arrumarBalanciamento(
