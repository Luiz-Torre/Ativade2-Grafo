#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista *prox;
}lista;

void inicializar(lista **g, int n){
    for(int i = 0; i<= n;i++){
        g[i] = NULL;
    }
}

lista *InserirLista(lista *l, int d, int c){
    lista *no = (lista *)malloc(sizeof(lista));
    no -> destino = d; no -> custo = c;
    no -> prox = l;
    return no;
}

void InserirAresta(lista **g, int origem, int destino, int custo){
    g[origem] = InserirLista(g[origem], destino, custo);
}

void ImprimirLista(lista *l){
    if(l!= NULL){
        printf("-(%d, %d)", l-> destino, l->custo);
        ImprimirLista(l->prox);
    }
}

void ImprimirGrafo(lista **g, int n){
    int i;
    printf("Grafo");
    for(i = 1;i<n+1;i++){
        printf("\n\t%d", i);
        ImprimirLista(g[i]);
    }
}
void MostraGraus(lista **g,int tam){
   int vetE[tam+1];
    int vetS[tam+1];
    for(int i = 0; i< tam+1;i++){
        vetE[i] = 0;
        vetS[i] = 0;
    }
    for (int i = 1; i <= tam; i++) {
        lista* p = g[i];
        while (p != NULL){
            for (int j = 1; j <= tam; j++) {
                if (p->destino == j){
                    vetS[i]+= 1;
                    vetE[j]+= 1;
                }
            }
            p = p->prox;
        }
    }
    for (int i = 1; i < tam+1; ++i) {
        printf("Vertice %d\n", (i));
        printf("gs (Grau de saida): %d\n",vetS[i]);
        printf("ge (Grau de entrada): %d\n",vetE[i]);
    }
}

void excluirAresta(lista **g, int aux, int aux_dest){
    lista *atual = g[aux];

    lista *lista_aux;

    if (atual -> destino == aux_dest) {
        g[aux] = g[aux] -> prox;
        free(atual);
        return;
    }

    while (atual){
        lista_aux = atual;
        atual = atual -> prox;
        if (atual && atual -> destino == aux_dest){
        lista_aux -> prox = atual -> prox;
        free(atual);
        return;
        }
    }
    
    puts("O valor não se encontra em nenhum no");
}

int existe(int *vet, int valor, int n){
    int i;
    for(i =0; i< n;i++){
        if(vet[i] == valor){
            return 1;
        }
    }
    return 0;
}


void TestaCompleta(lista **g,int tam){
    int vetE[tam+1];
    int vetS[tam+1];
    for(int i = 0; i< tam+1;i++){
        vetE[i] = 0;
        vetS[i] = 0;
    }
    for (int i = 1; i <= tam; i++) {
        lista* p = g[i];

        while (p != NULL){
            for (int j = 1; j <= tam; j++) {
                if (p->destino == j){
                    vetS[i]+= 1;
                    vetE[j]+= 1;
                }
            }
            p = p->prox;
        }
    }

    for(int i = 1;i <= tam; i++) {
        if(vetE[i] != (tam -1) || vetS[i] != (tam - 1)){
            printf("O grafo não é completo");
            return ;
        }
    }
        puts("O grafo é completo");
}

void limpa(lista **g, int tam){
  for(int i=0; i<=tam;i++) {
    free(g[i]);
  }
  free(g);
}
int medeTamanho(int menor, int novoValor){
    if (novoValor < menor && novoValor>0){
        return novoValor;
    }
    else{
        return menor;
    }
}
int medeCusto(int menor, int novoValor){
    if (novoValor < menor && novoValor>0){
        return novoValor;
    }
    else{
        return menor;
    }
}
void calcTodosCaminhos(lista **g, int *vet, int b, int pos) {
  if (vet[pos-1] == b) {
      int i;
    puts("");
    for (i = 0; i < pos; i++)
      printf("%d ", vet[i]);
  }
  else {
    lista *p = g[ vet[pos-1] ];
    while (p!=NULL) {
      if (! existe(vet, p->destino, pos)) {
        vet[pos] = p->destino;
        calcTodosCaminhos(g, vet, b, pos+1);
      }
      p = p->prox;
    }
  }
}

void MenorCaminho(lista **g, int *vet, int b, int pos,int menor) {
    if ( vet[pos-1] == b && pos ==menor) {
        int i;
        puts("");
        for (i = 0; i < pos; i++)
            printf("%d ", vet[i]);
    }
    else {
        lista *p = g[ vet[pos-1] ];
        while (p!=NULL) {
            if (! existe(vet, p->destino, pos)) {
                vet[pos] = p->destino;
                MenorCaminho(g, vet, b, pos+1,menor);
            }
            p = p->prox;
        }
    }
}

int  CaminhoCurto(lista **g, int *vet, int b, int pos,int *vet2,int menor,int menorValor) {
    if (vet[pos-1] == b) {
        menor = medeTamanho(menor,pos);
    }
    else {
        lista *p = g[ vet[pos-1] ];
        while (p!=NULL){
            if (! existe(vet, p->destino, pos)) {
                vet[pos] = p->destino;
                menor = CaminhoCurto(g, vet, b, pos+1,vet2,menor,menorValor);
            }
            p = p->prox;
        }
    }
    return menor;
}

int  CaminhoMenorCusto(lista **g, int *vet, int b, int pos,int *vet2,int menor,int menorValor) {
    if (vet[pos-1] == b) {
        menor = medeCusto(menor,menorValor);

    }
    else {
        lista *p = g[ vet[pos-1] ];

        while (p!=NULL){
            if (! existe(vet, p->destino, pos)) {
                vet[pos] = p->destino;
                if(pos == 1){
                    menorValor = 0;
                }
                menorValor += p->custo;
                menor = CaminhoMenorCusto(g, vet, b, pos+1,vet2,menor,menorValor);

            }
            p = p->prox;
        }
    }
    return menor;
}

int main(){
    int var, tam;
    int pos = 1;
    int menor = 1000;
    int custo = 1000;
    int destino_caminho;
    int *origem_caminho;
    int *custo_caminho;
    int *num_caminho;
    int origem, destino, aux, aux_dest;
    lista **g;
    puts("Informe quantos nós terá seu grafo: \n");
    scanf("%d", &tam);
    g = (lista**)malloc((tam+1)*sizeof(lista*));

    num_caminho = (int*) malloc(tam*sizeof(int));

    for (int i = 0; i < tam; i++) {
        num_caminho[i] = 0;
    }
    origem_caminho = (int*) malloc(tam*sizeof(int));
    custo_caminho = (int*) malloc(tam*sizeof(int));
    inicializar(g, tam);
    printf("Informe: \n 1- Inserir Aresta\n 2- Remover uma aresta\n 3- Imprimir grafo\n 4- Imprimir os graus de entrada e saída de um vértice\n 5- Verificar se um grafo é completo\n 6- Para imprimir todos os caminhos entre uma origem e seu destino\n7- Imprimir o caminho mais curto( com o menor número de arestras)\n8-Imprimir o caminho de menor custo( menor soma dos custos das arestas )\n9 - Sair ");

    scanf("%d", &var);
    while(var != 9){
        switch(var){
            case 1:
                puts("Informe qual a origem: \n");
                scanf("%d", &origem);
                puts("Informe qual o destino: \n");
                scanf("%d", &destino);
                puts("Informe qual o custo: \n");
                scanf("%d", &custo);
                InserirAresta(g, origem, destino, custo);
                break;
            case 2:
                puts("Informe de qual no de origem que você deseja excluir a arestra");
                scanf("%d", &aux);
                puts("Informe de qual no de destino que você deseja excluir a arestra");
                scanf("%d", &aux_dest);
                excluirAresta(g, aux, aux_dest );
                break;
            case 3:
                ImprimirGrafo(g, tam);
                break;
            case 4:

                MostraGraus(g,tam);
                break;
            case 5:
                TestaCompleta(g,tam);
                break;
            case 6:
                puts("Informe a origem");
                scanf("%d", &origem);
                origem_caminho[0] = origem;
                puts("Informe o destino");
                scanf("%d", &destino_caminho);
                calcTodosCaminhos(g, origem_caminho, destino_caminho, 1);
                break;
             case 7:
                 puts("Informe a origem");
                 scanf("%d", &origem);
                 origem_caminho[0] = origem;
                 puts("Informe o destino");
                 scanf("%d", &destino_caminho);
                 menor = CaminhoCurto(g, origem_caminho, destino_caminho,1,num_caminho,menor,0);
                 MenorCaminho(g, origem_caminho, destino_caminho, pos,menor);

                 break;
             case 8:
                 puts("Informe a origem");
                 scanf("%d", &origem);
                 origem_caminho[0] = origem;
                 puts("Informe o destino");
                 scanf("%d", &destino_caminho);
                 custo = CaminhoMenorCusto(g, origem_caminho, destino_caminho,pos,num_caminho,menor,custo);
                 printf("%d",custo);
                 break;
            case 9:
                limpa(g, tam);
                exit(0);
                break;
            default:
                printf("\nValor Invalido");
                break;
        }
        printf("\nInforme: \n 1- Inserir Aresta\n 2- Remover uma aresta\n 3- Imprimir grafo\n 4- Imprimir os graus de entrada e saída de um vértice\n 5- Verificar se um grafo é completo\n 6- Para imprimir todos os caminhos entre uma origem e seu destino\n7- Imprimir o caminho mais curto( com o menor número de arestras)\n8-Imprimir o caminho de menor custo( menor soma dos custos das arestas )\n9 - Sair\n");
        scanf("%d", &var);
    }
    return 0;
}




// 4 1 1 2 5 1 1 3 8 1 1 4 30 1 2 4 18 1 3 4 1