#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vertex int
#define MAX 50

typedef struct users{
    vertex v;
    char nome[100];
    struct users *next;
} users;

typedef struct graph{
    int V;
    int A;
    struct node **contatos;
}   graph;

typedef struct node{
    vertex w;
    struct node *next;
} node;

graph* inicializar_Grafo();
void criar_Aresta(vertex v, vertex w, graph *G, int *grauVertices);
node* nova_Amizade(vertex w, node *next);
void arestas_Random(int A, graph* G, int *grauVertices);
node* inserirAmizade_0();
void zerar_Graus(int *x);
void exibirGrau(int *x, users *head);
node* inicializar_Fila();
void inserir_Fila(int x, node *head);
void limpar_Fila(node* head);
int remover_Fila(node *head);
int filaVazia(node *head);
void buscar_Largura(int x, int distancia[MAX][MAX], graph *G);
users* inicializar_Lista();
void inserir_Nomes(users *head);
void inserir_Fim(char *nome, users *head);
char* buscar_Nome(users *head, vertex v);
void exibirDistancia(int distancia[MAX][MAX], users* head);
void exibirMatriz(int a[MAX][MAX]);
void liberar_memoria(graph *G);

int main()
{
    int A, grauVertices[MAX];
    zerar_Graus(grauVertices);
    users *contatosHead=inicializar_Lista();
    inserir_Nomes(contatosHead);

    graph *G=inicializar_Grafo();
    srand((unsigned)time(NULL));
    A=rand() % 700;
    arestas_Random(A, G, grauVertices);

    int distancia[MAX][MAX], i, j;
    for(i=0; i<MAX; i++)
        buscar_Largura(i, distancia, G);

    exibirGrau(grauVertices, contatosHead);
    exibirDistancia(distancia, contatosHead);
    liberar_memoria(G);
    return 0;
}

void inserir_Nomes(users *head){
    inserir_Fim("Eu", head);
    inserir_Fim("Ana", head);
    inserir_Fim("Flavia", head);
    inserir_Fim("Julia", head);
    inserir_Fim("Joao", head);
    inserir_Fim("Larissa", head);
    inserir_Fim("Melanie", head);
    inserir_Fim("Lily", head);
    inserir_Fim("Maria", head);
    inserir_Fim("Jose", head);
    inserir_Fim("Danielle", head);
    inserir_Fim("Zelita", head);
    inserir_Fim("Sergio", head);
    inserir_Fim("Fabiana", head);
    inserir_Fim("Juan", head);
    inserir_Fim("Julia", head);
    inserir_Fim("Sabrina", head);
    inserir_Fim("Rose", head);
    inserir_Fim("Rosilaine", head);
    inserir_Fim("Jairo", head);
    inserir_Fim("Sofia", head);
    inserir_Fim("Fabiana", head);
    inserir_Fim("Tiago", head);
    inserir_Fim("Gabriela", head);
    inserir_Fim("Jean", head);
    inserir_Fim("Adriana", head);
    inserir_Fim("Adelaide", head);
    inserir_Fim("Claudia", head);
    inserir_Fim("Cristiane", head);
    inserir_Fim("Debora", head);
    inserir_Fim("Cristina", head);
    inserir_Fim("Barbara", head);
    inserir_Fim("Ana Paula", head);
    inserir_Fim("Ana Beatriz", head);
    inserir_Fim("Analisa", head);
    inserir_Fim("Elisangela", head);
    inserir_Fim("Fernanda", head);
    inserir_Fim("Rafaela", head);
    inserir_Fim("Paloma", head);
    inserir_Fim("Yuri", head);
    inserir_Fim("Ana Debora", head);
    inserir_Fim("Gabriele", head);
    inserir_Fim("Elizete", head);
    inserir_Fim("Enoque", head);
    inserir_Fim("Marcos", head);
    inserir_Fim("Vitoria", head);
    inserir_Fim("Samuel", head);
    inserir_Fim("Raimundo", head);
    inserir_Fim("Paulo", head);
    inserir_Fim("Patricia", head);
}

char* buscar_Nome(users *head, vertex v){
    users *tmp;
    for(tmp=head->next; tmp!=NULL; tmp=tmp->next){
        if(tmp->v==v)
            break;
    }
    return tmp->nome;
}

void inserir_Fim(char *nome, users *head){
    static int v=0;
    users *novo=(users*)malloc(sizeof(users));
    novo->v=v;
    strcpy(novo->nome, nome);
    novo->next=NULL;
    v++;

    if(head->next==NULL){
        head->next=novo;
    }
    else{
        users *tmp=head->next;
        while(tmp->next!=NULL)
            tmp=tmp->next;
        tmp->next=novo;
    }
}

users* inicializar_Lista(){
    users *a=(users*)malloc(sizeof(users));
    a->next=NULL;
    return a;
}


void exibirGrau(int *x, users *head){
    int i;
    for(i=1; i<MAX; i++)
        printf("%s, amigos em comum: %d\n", buscar_Nome(head, i), x[i]);
}

void zerar_Graus(int *x){
    int i;
    x[0]=MAX-1; //COMO O VERTICE "0" É AMIGO DE TODOS, ELE POSSUI GRAU N-1.
    for(i=1; i<MAX; i++)
        x[i]=0;

}

void exibirDistancia(int distancia[MAX][MAX], users* head){
    int i, j, **proximas, **distantes, nP=0, nD=0;
    proximas=(int**)malloc(MAX*sizeof(int*));
    distantes=(int**)malloc(MAX*sizeof(int*));
    for(i=0; i<MAX; i++){
        proximas[i]=(int*)malloc(2*sizeof(int));
        distantes[i]=(int*)malloc(2*sizeof(int));
    }

    for(i=1; i<MAX; i++){
        if(i!=1){
            proximas[i][0]=distancia[i][1], proximas[i][1]=1;
            distantes[i][0]=distancia[i][1], distantes[i][1]=1;
        }
        else{
            proximas[i][0]=distancia[i][2], proximas[i][1]=2;
            distantes[i][0]=distancia[i][2], distantes[i][1]=2;
        }

        for(j=1; j<MAX; j++){
            if(distancia[i][j]>distantes[i][0]){
                distantes[i][0]=distancia[i][j];
                distantes[i][1]=j;
            }
            else if(distancia[i][j]<proximas[i][0] && distancia[i][j]!=0 && distancia[i][j]!=distantes[i][0]){
                proximas[i][0]=distancia[i][j];
                proximas[i][1]=j;
            }
        }
    }

    for(i=1; i<MAX; i++){
        for(j=1; j<MAX; j++){
            if(distancia[i][j]==proximas[i][0] && j!=proximas[i][1]){
                nP++;
                proximas[i]=(int*)realloc(proximas[i], (2+nP)*sizeof(int));
                proximas[i][nP+1]=j;
            }
            else if(distancia[i][j]==distantes[i][0] && j!=distantes[i][1]){
                nD++;
                distantes[i]=(int*)realloc(distantes[i], (2+nD)*sizeof(int));
                distantes[i][nD+1]=j;
            }
        }
        printf("\n\n--- %s:\n", buscar_Nome(head, i));
       printf("Mais proximas:");
        for(j=1; j<nP+2; j++)
            printf("%s ", buscar_Nome(head, proximas[i][j]));
        printf("\nMais distantes: ");
         for(j=1; j<nD+2; j++)
            printf("%s ", buscar_Nome(head, distantes[i][j]));
        nD=0, nP=0;
    }

}


void arestas_Random(int A, graph *G, int *grauVertices){
    srand((unsigned)time(NULL));
    while(G->A < A){
        vertex v=rand() % MAX;
        vertex w=rand() % MAX;
        if(v!=w && v!=0 && w!=0)
            criar_Aresta(v, w, G, grauVertices);
    }
}

node* inserirAmizade_0(){
    node *novo=(node*)malloc(sizeof(node));
    novo->w=0;
    novo->next=NULL;
    return novo;
}

graph* inicializar_Grafo(){
    int y, i;
    graph *g=(graph*)malloc(sizeof(graph));
    g->A=MAX-1;
    g->V=MAX;
    g->contatos=(node**)malloc(MAX*sizeof(node*));
    g->contatos[0]=NULL;

    for(i=1; i<MAX; i++){ //ADICIONA O VERTICE 0 NA LISTA DE CONTATO DE TODOS E VICE-VERSA
        g->contatos[i]=inserirAmizade_0();
        g->contatos[0]=nova_Amizade(i, g->contatos[0]);
    }

    return g;
}

void criar_Aresta(vertex v, vertex w, graph *G, int *grauVertices){
    node *tmp=G->contatos[v];
    while(tmp!=NULL){
        if(tmp->w == w)
            return;
        tmp=tmp->next;
    }
    G->contatos[v]=nova_Amizade(w, G->contatos[v]);
    grauVertices[v]++;
    G->contatos[w]=nova_Amizade(v, G->contatos[w]);
    grauVertices[w]++;
    G->A++;
}

node* inicializar_Fila(){
    node *a=(node*)malloc(sizeof(node));
    a->next=NULL;
    return a;
}

void inserir_Fila(int x, node *head){
    node *novo=(node*)malloc(sizeof(node));
    novo->next=NULL;
    novo->w=x;

    if(head->next==NULL)
        head->next=novo;
    else{
        node *tmp=head->next;
        while(tmp->next!=NULL)
            tmp=tmp->next;
        tmp->next=novo;
    }
}

int remover_Fila(node *head){
    int y;
    node *tmp=head->next;
    head->next=tmp->next;

    y=tmp->w;
    free(tmp);
    return y;
}

void limpar_Fila(node *head){
    node *prox=head->next; node *ant;
    while(prox!=NULL){
        ant=prox;
        prox=prox->next;
        free(ant);
    }
}

int filaVazia(node *head){
    if(head->next==NULL)
        return 1;
    else
        return 0;
}

void buscar_Largura(int x, int distancia[MAX][MAX], graph *G){
    int i, v;
    for(i=0; i<MAX; i++)
        distancia[x][i]=-1;
    distancia[x][x]=0;
    node *head=inicializar_Fila();
    inserir_Fila(x, head);
    while(!filaVazia(head)){
        v=remover_Fila(head);
        for(node *tmp=G->contatos[v]; tmp!=NULL; tmp=tmp->next){
            if(distancia[x][tmp->w]==-1){
                distancia[x][tmp->w]=distancia[x][v]+1;
                inserir_Fila(tmp->w, head);
            }
        }
    }
    limpar_Fila(head);
}

node* nova_Amizade(vertex w, node *next){
    node *novo=(node*)malloc(sizeof(node));
    novo->w=w;
    novo->next=next;
    return novo;
}

void liberar_memoria(graph *G){
    node *atual, *prox;
    int i;
    for(i=0; i<MAX; i++){
        for(atual=G->contatos[i]; atual!=NULL; ){
            prox=atual->next;
            free(atual);
            atual=prox;
            }
    }
    free(G->contatos);
}

