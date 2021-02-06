#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

typedef struct tno{
    int freq;
    char obj;
    struct tno *esq;
    struct tno *dir;
}Tno;

typedef struct tlista{
    char obj[20];
    int verif;       //Verifica se esse Nó tem um pai
    struct tno *no;
}TLista;


void contaQtdNos(Tno *raiz, int *n){

    if(raiz == NULL)
        return;

    if(raiz->esq != NULL)
        *n = *n + 1;
    contaQtdNos(raiz->esq, n);

    if(raiz->dir != NULL)
        *n = *n + 1; 
    contaQtdNos(raiz->dir, n);
}

bool MontaString(Tno *raiz, char obj, char *cod, int tam){

    if(raiz->dir == NULL && raiz->esq == NULL && raiz->obj == obj){
        //printf("caraio 3");
        cod[tam] = '\0';
        return true;
    }

    bool encontrado = false;

    if(raiz->esq){
        cod[tam] = '0';
        encontrado = MontaString(raiz->esq, obj, cod, tam+1);
    }

    if(!encontrado && raiz->dir){
        cod[tam] = '1';
        encontrado = MontaString(raiz->dir, obj, cod, tam+1);
    }

    if(!encontrado){
        cod[tam] = '\0';
    }

    return encontrado;


}
void imprimeArvHuffman(Tno *raiz, char obj[], int n){

    int n1=0;
    contaQtdNos(raiz, &n1);
    
    char cod[n1];
    for(int i=0;i<n;i++){
        MontaString(raiz, obj[i], cod, 0);
        printf("%s - %c\n", cod, obj[i]);
    }
}



void imprimePreOrdem(Tno *raiz){

    if(raiz == NULL)
		return;

    printf("%d ", raiz->freq);
    printf("%c\n", raiz->obj);

    imprimePreOrdem(raiz->esq);
    imprimePreOrdem(raiz->dir);
}

void troca(int freq[], char obj[], int i1, int i2){

    int aux;
    char aux2;

    aux=freq[i1];
    aux2=obj[i1];
    freq[i1]=freq[i2];
    obj[i1]=obj[i2];
    freq[i2]=aux;
    obj[i2]=aux2;
}

void bottom_UP_Min(int freq[], char obj[], int n, int n1){

    int meio=(n-1)/2;

    if(meio < 0)
        return;

    for(int i=0;i<n1;i++){

        if(((meio*2 + 2) <= n1)){

            if((freq[meio] > freq[meio*2 + 1]) || (freq[meio] > freq[meio*2 + 2])){
                
                if(freq[meio*2 + 1] < freq[meio*2 + 2]){
                    troca(freq, obj, meio, meio*2+1);
                    meio=meio*2+1;
                }
                else{
                    troca(freq, obj, meio , meio*2+2);
                    meio=meio*2+2;
                }
            }
        }
        else{
            if(((meio*2 + 1) <= n1)){
                if(freq[meio] > freq[meio*2 + 1]){
                    troca(freq, obj, meio , meio*2+1);
                }
            }
            break;
        }
    }

    bottom_UP_Min(freq, obj,n-1,n1);
}

Tno *busca(int freq, int n, TLista *VetNos, TLista **aux){

    for(int i=0; i<n; i++){

        if( (VetNos + i)->no->freq == freq )
            if( (VetNos + i)->no->obj == (char)0 )
                if( !((VetNos + i)->verif) ){
                    *aux = (VetNos + i);
                    return ((VetNos + i)->no);
                }
    }

    return NULL;
}

void criaPai(Tno *filhoesquerdo, Tno *filhodireito, Tno **Pai){

    *Pai=(Tno*)malloc(sizeof(Tno));
    (*Pai)->freq = (filhodireito)->freq + (filhoesquerdo)->freq;
    ((*Pai)->obj) = (char)0;
    (*Pai)->esq = filhoesquerdo;
    (*Pai)->dir = filhodireito;
}

void criaFilhoFolha(Tno **filho, int freq, char obj){

    *filho = (Tno*)malloc(sizeof(Tno));
    if(*filho == NULL)
        return;

    (*filho)->freq = freq;
    (*filho)->obj = obj;
    (*filho)->esq = NULL;
    (*filho)->dir = NULL;
}
 

void ArvHuffman(Tno **raiz, TLista **VetNos, int freq[], char obj[], int fim, int *n){

    if(fim < 1)
        return;


    if((obj[0] != (char)0) && (obj[1] != (char)0)){
        *n = *n + 3;
        *VetNos = (TLista*)realloc(*VetNos, sizeof(TLista) * (*n));
        

        Tno *filhoesq = NULL;
        criaFilhoFolha(&filhoesq, freq[0], obj[0]);
        (*VetNos + ((*n) - 3))->no = filhoesq;
        (*VetNos + ((*n) - 3))->obj[0] = obj[0]; 
        (*VetNos + ((*n) - 3))->obj[1] = '\0';
        (*VetNos + ((*n) - 3))->verif = 1;

        Tno *filhodir = NULL;
        criaFilhoFolha(&filhodir, freq[1], obj[1]);
        (*VetNos + ((*n) - 2))->no = filhodir;
        (*VetNos + ((*n) - 2))->obj[0] = obj[1];
        (*VetNos + ((*n) - 2))->obj[1] = '\0';
        (*VetNos + ((*n) - 2))->verif = 1;

        Tno *Pai = NULL;
        criaPai(filhoesq, filhodir, &Pai);
        (*VetNos + ((*n) - 1))->no = Pai;
        (*VetNos + ((*n) - 1))->obj[0] = obj[0];
        (*VetNos + ((*n) - 1))->obj[1] = obj[1];
        (*VetNos + ((*n) - 1))->obj[2] = '\0';
        (*VetNos + ((*n) - 1))->verif = 0;
        *raiz = Pai;

        Pai = NULL;
        filhodir = NULL;
        filhoesq = NULL;
    }
    else{

        if((obj[0] == (char)0) && (obj[1] != (char)0)){

            *n = *n + 2;
            *VetNos = (TLista*)realloc(*VetNos, sizeof(TLista) * (*n));
            
            Tno *filhodir = NULL;
            criaFilhoFolha(&filhodir, freq[1], obj[1]);
            (*VetNos + ((*n) - 2))->no = filhodir;
            (*VetNos + ((*n) - 2))->obj[0] = obj[1];
            (*VetNos + ((*n) - 2))->obj[1] = '\0';
            (*VetNos + ((*n) - 2))->verif = 1;

            Tno *filhoesq = NULL;
            TLista *aux = NULL;
            filhoesq = busca(freq[0], *n, *VetNos, &aux);   //Busca Um Pai que ainda não seja filho e que tenha a freq correta
            
            Tno *Pai = NULL;
            criaPai(filhoesq, filhodir, &Pai);
            (*VetNos + ((*n) - 1))->no = Pai;
            strcpy((*VetNos + ((*n) - 1))->obj , (*VetNos + ((*n) - 2))->obj);
            strcat((*VetNos + ((*n) - 1))->obj , aux->obj); 
            (*VetNos + ((*n) - 1))->verif = 0;
            *raiz = Pai;

            Pai = NULL;
            filhodir = NULL;
            filhoesq = NULL;
        }
        else{

            if((obj[0] != (char)0) && (obj[1] == (char)0)){

                *n = *n + 2;
                *VetNos = (TLista*)realloc(*VetNos, sizeof(TLista) * (*n));
                
                Tno *filhoesq = NULL;
                criaFilhoFolha(&filhoesq, freq[0], obj[0]);
                (*VetNos + ((*n) - 2))->no = filhoesq;
                (*VetNos + ((*n) - 2))->obj[0] = obj[0];
                (*VetNos + ((*n) - 2))->obj[1] = '\0';
                (*VetNos + ((*n) - 2))->verif = 1;

                Tno *filhodir = NULL;
                TLista *aux = NULL;
                filhodir = busca(freq[1], *n, *VetNos, &aux);   //Busca Um Pai que ainda não seja filho e que tenha a freq correta
                
                Tno *Pai = NULL;
                criaPai(filhoesq, filhodir, &Pai);
                (*VetNos + ((*n) - 1))->no = Pai;
                strcpy((*VetNos + ((*n) - 1))->obj , (*VetNos + ((*n) - 2))->obj);
                strcat((*VetNos + ((*n) - 1))->obj , aux->obj); 
                (*VetNos + ((*n) - 1))->verif = 0;
                *raiz = Pai;

                Pai = NULL;
                filhodir = NULL;
                filhoesq = NULL;
                aux = NULL;
            }
            else{
                if((obj[0] == (char)0) && (obj[1] == (char)0)){

                    *n = *n + 1;
                    *VetNos = (TLista*)realloc(*VetNos, sizeof(TLista) * (*n));
                    
                    Tno *filhoesq = NULL;
                    TLista *aux1 = NULL;
                    filhoesq = busca(freq[0], *n, *VetNos, &aux1);   //Busca Um Pai que ainda não seja filho e que tenha a freq correta

                    Tno *filhodir = NULL;
                    TLista *aux2 = NULL;
                    filhodir = busca(freq[1], *n, *VetNos, &aux2);   //Busca Um Pai que ainda não seja filho e que tenha a freq correta
                    
                    Tno *Pai = NULL;
                    criaPai(filhoesq, filhodir, &Pai);
                    (*VetNos + ((*n) - 1))->no = Pai;
                    strcpy((*VetNos + ((*n) - 1))->obj , aux1->obj);
                    strcat((*VetNos + ((*n) - 1))->obj , aux2->obj); 
                    (*VetNos + ((*n) - 1))->verif = 0;
                    aux1->verif = 1;
                    aux2->verif = 1;
                    *raiz = Pai;

                    Pai = NULL;
                    filhodir = NULL;
                    filhoesq = NULL;
                    aux1 = NULL;
                    aux2 = NULL;
                }
            }
        }
    }
    
    if((fim-1)>0){
        freq[0] = (*raiz) ->freq;
        obj[0] = (char)0;
        freq[1] = freq[fim];
        obj[1] = obj[fim];
    }
    else{
        freq[0] = (*raiz)->freq;
        obj[0] = (char)0;
    }

    bottom_UP_Min(freq, obj, fim-1, fim-1);

    ArvHuffman(raiz, VetNos, freq, obj, fim-1, n);
}

void freeArvRec(Tno **raiz){

    if(*raiz ==  NULL)
        return;

    freeArvRec(&((*raiz)->esq));
    freeArvRec(&((*raiz)->dir));
    (*raiz)->esq=NULL;
    (*raiz)->dir=NULL;
    free(*raiz);
}

void main(){

    int n;
    printf("Digite o tamanho do vetor:");
    scanf("%d", &n);

    int freq[n];
    char obj[n];
    char objAux[n];

    srand(time(NULL));

    for(int i=0;i<n;i++){
       freq[i] = (rand() % 100) + 1;
       obj[i] = (char)((rand() % 95) + 32);
       objAux[i] = obj[i]; 
    }

    for(int i=0;i<n;i++){
        printf("%d ", *(freq+i));
        printf("%c\n", *(obj+i));
    }

    bottom_UP_Min(freq, obj, n-1, n-1);

    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ", *(freq+i));
        printf("%c\n", *(obj+i));
    }

    Tno *raiz = NULL;
    TLista *VetNos = (TLista*)malloc(sizeof(TLista));
    int TamListaContigua = 0;
    ArvHuffman(&raiz, &VetNos, freq, obj, n-1, &TamListaContigua);
    
    printf("\n\n\n");
    imprimeArvHuffman(raiz, objAux, n);

   free(obj);
   free(objAux);
   free(freq);
   free(VetNos);
   VetNos=NULL;
   freeArvRec(&raiz);
   raiz=NULL;
} 