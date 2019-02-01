#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N_BOLSAS 10
#define N_DOCENTES 18
#define N_PIB 199
#define N_MED 51185
#define N_SOLD 347

typedef struct {
    char nome[100];
    float chave;
} dados;

void mergeSort(dados *v, int p, int r);
void insertionSort(dados *v, int n);
void quickSort(dados *v, int p, int r);
void quickSort_2(dados *v, int p, int r);
void countingSort(dados *A, int n, float exp);
void radixSort(dados *v, int n);
void heapSort(dados *v, int n);

void intercalar(dados *A, int p, int q, int r);
int particionar(dados *v, int p, int r);
void escolherPivo(dados *v, int p, int r);
void printar(dados *v, int n);
void trocar(dados *v, int i, int j);
float acharMAX(dados *v, int n);
void construirHeap(dados *v, int n);
void refazerHeap(dados *v, int k, int n);

FILE* abrirArq_l(char *nome);
FILE* abrirArq_e(char *nome);
dados* criarVetor(int n);
void lerArq_bolsas(FILE *arq, dados* bolsas, int n);
void lerArq_docentes(FILE *arq, dados *docentes, int n);
void lerArq_pib(FILE *arq, dados *pib);
void lerArq_med(FILE *arq, dados *medicamentos);
void lerArq_sold(FILE *arq, dados *soldado_cidadao);
void retirarCaracteres(FILE *arq);
void substituirS_virgula(char *stringv);
void transformar_emString(dados *soldado_cidadao, char *string_valor, int i);
void retirarAspas(FILE *arq);
void escreverArquivo(char *nome, dados *v, int n);
void escreverArquivo2(char *nome, dados *v, int n);

int main()
{
    /* -------------------------------------------------------- BOLSAS ---------------------------------------------------- */
    char *nomeB="programas-bolsas-2017.txt";
    FILE *arqB=abrirArq_l(nomeB);

    dados *bolsas=criarVetor(N_BOLSAS);
    lerArq_bolsas(arqB, bolsas, N_BOLSAS);
    quickSort(bolsas, 0, N_BOLSAS-1);
	//insertionSort(bolsas, N_BOLSAS);
	//mergeSort(bolsas, 0, N_BOLSAS-1);
	//printar(bolsas, N_BOLSAS);
	fclose(arqB);

	nomeB="-Bolsas.csv";
    escreverArquivo(nomeB, bolsas, N_BOLSAS);

	/* ------------------------------------------------------- DOCENTES -------------------------------------------------- */
     char *nomeD="Total_Docentes_Pos.txt";
	FILE *arqD=abrirArq_l(nomeD);

	dados *docentes=criarVetor(N_DOCENTES);
	lerArq_docentes(arqD, docentes, N_DOCENTES);
	quickSort(docentes, 0, N_DOCENTES-1);
	//insertionSort(docentes, N_DOCENTES);
	//mergeSort(docentes, 0, N_DOCENTES-1);
	//printar(docentes, N_DOCENTES);
	fclose(arqD);

	nomeD="-Docentes.csv";
    escreverArquivo(nomeD, docentes, N_DOCENTES);

	/* ----------------------------------------------------------- PIB --------------------------------------------------- */
    char *nomeP="bcdata.sgs.4509.txt";
	FILE *arqP=abrirArq_e(nomeP);

	dados *pib=criarVetor(N_PIB);
	retirarCaracteres(arqP);
	lerArq_pib(arqP, pib);
	radixSort(pib, N_PIB);
    //quickSort(pib, 0, N_PIB-1);
	//heapSort(pib, N_PIB);
	//mergeSort(pib, 0, N_PIB-1);
    //insertionSort(pib, N_PIB);
    //printar(pib, N_PIB);
    fclose(arqP);

    nomeP="-PIB.csv";
    escreverArquivo2(nomeP, pib, N_PIB);

    /* ---------------------------------------------------- MEDICAMENTOS --------------------------------------------------- */
    char *nomeM="TA_PRECOS_MEDICAMENTOS.txt";
	FILE *arqM=abrirArq_l(nomeM);

	dados *medicamentos=criarVetor(N_MED);
	lerArq_med(arqM, medicamentos);
	quickSort_2(medicamentos, 0, N_MED-1);
	//heapSort(medicamentos, N_MED);
	//mergeSort(medicamentos, 0, N_MED-1);
    //insertionSort(medicamentos, N_MED);
	//printar(medicamentos, N_MED);
	fclose(arqM);

	nomeM="-Medicamentos.csv";
    escreverArquivo2(nomeM, medicamentos, N_MED);

	/* ------------------------------------------------------ SOLDADOS ----------------------------------------------------- */
	char *nomeS="psc2017.txt";
	FILE *arqS=abrirArq_e(nomeS);

	dados *soldado_cidadao=criarVetor(N_SOLD);
	retirarAspas(arqS);
	lerArq_sold(arqS, soldado_cidadao);
	quickSort_2(soldado_cidadao, 0, N_SOLD-1);
	//heapSort(soldado_cidadao, N_SOLD);
	//mergeSort(soldado_cidadao, 0, N_SOLD-1);
	//insertionSort(soldado_cidadao, N_SOLD);
	//printar(soldado_cidadao, N_SOLD);
	fclose(arqS);

	nomeS="-SoldadoCidadao.csv";
    escreverArquivo2(nomeS, soldado_cidadao, N_SOLD);
    free(bolsas), free(docentes), free(medicamentos), free(pib), free(soldado_cidadao);
    bolsas=NULL, docentes=NULL, medicamentos=NULL, pib=NULL, soldado_cidadao=NULL;
    return 0;
}

dados* criarVetor(int n){
	dados *x=(dados*)malloc(n*sizeof(dados));
	return x;
}

FILE* abrirArq_l(char *nome){
    FILE *arq=fopen(nome, "r");
    if(arq==NULL){
        printf("Não foi possível abrir o arquivo.");
        exit(1);
    }
    return arq;
}

FILE* abrirArq_e(char *nome){ //apesar de nome estar "_e", é pra leitura+escrita
    FILE *arq=fopen(nome, "r+");
    if(arq==NULL){
        printf("Não foi possível abrir o arquivo.");
        exit(1);
    }
    return arq;
}

void lerArq_bolsas(FILE *arq, dados* bolsas, int n){
	int ch, i=0, j=0;
	do{
		while((ch=fgetc(arq))!=10){} //percorre a primeira linha até encontrar um caractere de new line (\n)
		fscanf(arq, "%[^;]s", &bolsas[i].nome); //lê a nome da bolsa
		fscanf(arq, ";%f;", &bolsas[i].chave); //lê a quantchave de dados no campus uberlandia
		i++;
	} while(i<n);
}

void lerArq_docentes(FILE *arq, dados *docentes, int n){
	char ch;
	int i, j=0;
	for(i=0; i<n; i++){
		while((ch=fgetc(arq))!=EOF){ //primeira percursão até encontrar o traço, que indica o início do nome da área.
			if(ch==45)
				break;
		}

		while((ch=fgetc(arq))!=59) //inserção do nome da área dentro do array.
			docentes[i].nome[j++]=ch;
        docentes[i].nome[j]='\0';
		fscanf(arq, "%f", &docentes[i].chave); //quantidade de docentes naquela área.
		j=0;
	}
}


void lerArq_pib(FILE *arq, dados *pib){
    rewind(arq);
	int i=0;
	while( (fscanf(arq, " %s ; %f \n", &pib[i].nome, &pib[i].chave)) != EOF){
		i++; //como o arquivo já está previamente formatado, só é necessário ler cada linha e depois aumentar o índice do vetor
	}
}

void retirarCaracteres(FILE *arq){
	int ch;
	while((ch=fgetc(arq))!=EOF){
		if(ch==44){ //tira virgula
            fseek(arq, -1, SEEK_CUR); //o -1 faz com que a leitura do arquivo volte uma posição, se não o ponto seria inserido após a vírgula
			fputc('.', arq);
            fseek(arq, 0, SEEK_CUR); //o fseek foi chamado novamente para que mude do modo "escrita" para "leitura".
		}
		else if(ch==34){ //tira aspas
			fseek(arq, -1, SEEK_CUR);
			fputc(' ', arq);
			fseek(arq, 0, SEEK_CUR);
		}
	}
}

void substituirS_virgula(char *stringv){
	int i;
	for(i=0; i<4; i++){
		if(stringv[i]==','){
			stringv[i]='.';
			break;
		}
	}
}

void lerArq_med(FILE *arq, dados *medicamentos){
	int ch, pntvirg=0, i=0;
	char chave[9];
	while((ch=fgetc(arq))!=10){} //percorre a primeira linha

	while((ch=fgetc(arq))!=EOF){
		if(ch==59){ //armazena a quantidade de ponto e vírgula encontrada
			pntvirg++;
			if(pntvirg==5) {//após 5 ponto e vírgulas, chegou na aba "nome"
				fscanf(arq, "%[^;]s", &medicamentos[i].nome);
			}
			else if(pntvirg==15){ //após 16 ponto e vírgulas, chegou na aba "preço"
				if(fscanf(arq, "%[^\n]s", &chave)){ //fscanf retorna a quantidade de entradas que foram capturadas por ele
                    substituirS_virgula(chave);
                    medicamentos[i].chave=atof(chave);
				}
				else //se fscanf retornar 0, então o campo "preço" daquele medicamento está vazio e o fscanf não capturou nada
                    medicamentos[i].chave=0;
                i++, pntvirg=0; //após ler "preço", volta ao início

			}
		}
	}
}

void transformar_emString(dados *soldado_cidadao, char *string_valor, int i){
    int indicePonto; //armazena onde o primeiro ponto está
    for(indicePonto=0; indicePonto<10; indicePonto++){
        if(string_valor[indicePonto]=='.')
            break;
    }
    /* substitui o ponto pelo número presente na posição anterior, adicionando
     * um 0 na primeira posição do array.*/
    string_valor[indicePonto]=string_valor[indicePonto-1];
    string_valor[indicePonto-1]=string_valor[0];
    string_valor[0]='0';
    soldado_cidadao[i].chave=atof(string_valor);
}

void lerArq_sold(FILE *arq, dados *soldado_cidadao){
    rewind(arq);
	int ch, virgulas, i=0;
	char string_valor[10];
    while((ch=fgetc(arq))!=10){} //percorre a primeira linha
	do{
		virgulas=0;
		/* ------- início da linha ------------- */
		while(virgulas!=4){  //conta a quantidade de vírgulas até aquele momento
			if((ch=fgetc(arq))==44){
				virgulas++;
			}
		}
		//ao encontrar 4 vírgulas, inicia-se o nome do nome
		fscanf(arq, "%[^,]s", &soldado_cidadao[i].nome);

		/* ------ após ler o nome ------------ */
		while((ch=fgetc(arq))!=10){ //percorre até o final da linha
			if(ch==36){ //captura o campo "valores totais"
				/* o arquivo é percorrido até encontrar um "$", que indica o início dos campos
				 * valores. contudo, o primeiro campo valor capturado será o "valor por hora",
				 * o que não queremos, então ele é capturado em "string_valor" mas depois
				 * é sobrescrito pelo "valor total". */
				fscanf(arq, " %s , R$ %s", &string_valor, &string_valor);
				transformar_emString(soldado_cidadao, string_valor, i);
			}
		}
		i=i+1;;
	} while(i<N_SOLD);
}

void retirarAspas(FILE *arq){
    int ch;
    while((ch=fgetc(arq))!=EOF){
		if(ch==34){
			fseek(arq, -1, SEEK_CUR);
			fputc(' ', arq);
			fseek(arq, 0, SEEK_CUR);
		}
    }
}

void escreverArquivo(char *nome, dados *v, int n){
    FILE *arq=fopen(nome, "w+");
    if(arq==NULL){
        printf("Falha ao criar arquivo.");
        exit(1);
    }

    int i=0;
    while(i<n){
        fprintf(arq, "%s;%.2f\n", v[i].nome, v[i].chave);
        i++;
    }
    fclose(arq);
}

void escreverArquivo2(char *nome, dados *v, int n){ //escreve os 100 maiores primeiros
    FILE *arq=fopen(nome, "w+");
    if(arq==NULL){
        printf("Falha ao criar arquivo.");
        exit(1);
    }

    int i=n-1;
    while(i>(n-101)){
        fprintf(arq, "%s;%.2f\n", v[i].nome, v[i].chave);
        i--;
    }
    fclose(arq);
}



/* -------------------------------------------------- ALGORITMOS DE ORDENAÇÃO --------------------------------------------- */

void quickSort(dados *v, int p, int r){
/* A condição p<r serve para cobrir dois casos:
 * 1) Quando não existem números menores aos do pivô. Nesse caso, r=p-1 e 'p' será maior que 'r'.
 * 2) Quando existe apenas um elemento. Nesse caso, p=r. */

	if(p<r){
		int q=particionar(v, p, r);
		quickSort(v, p, q-1); //O 'q-1' torna-se o novo >r< do próximo pedacinho.
		quickSort(v, q+1, r); //O 'q+1' torna-se o novo >p< do próximo pedacinho.
	}
}

void quickSort_2(dados *v, int p, int r){
/* A condição p<r serve para cobrir dois casos:
 * 1) Quando não existem números menores aos do pivô. Nesse caso, r=p-1 e 'p' será maior que 'r'.
 * 2) Quando existe apenas um elemento. Nesse caso, p=r. */

	if(p<r){
		if(r-p+1<20) //se a partição for menor do que 20 elementos o insertionSort é utilizado.
			insertionSort(v, N_DOCENTES);
		else{
			int q=particionar(v, p, r);
			quickSort(v, p, q-1); //O 'q-1' torna-se o novo >r< do próximo pedacinho.
			quickSort(v, q+1, r); //O 'q+1' torna-se o novo >p< do próximo pedacinho.
		}
	}
}

int particionar(dados *v, int p, int r){
    if(r-p+1>2)
        escolherPivo(v, p, r);
	int i=p-1, j=p; //j: elemento atual. O 'i' fica sempre atrás do 'j'.
	for(; j<r; j++){ //j só vai até r-1, de forma que no término do laço a posição j será j=r;
		if(v[j].chave<v[r].chave){
			i++; //o 'i' só prossegue quando o elemento atual é menor do que o pivô.
			trocar(v, i, j);
		} //se não, o j prossegue sozinho e o i fica parado.
	}
	trocar(v, i+1, r); //i+1: é onde termina os elementos menores e começam os maiores.
	return i+1; //q=i+1.
}

void trocar(dados *v, int i, int j){
	dados x;
	x=v[i];
	v[i]=v[j];
	v[j]=x;
}

void escolherPivo(dados *v, int p, int r){
	/* ordena o primeiro, o do meio e o último elemento da partição de forma crescente.
	 * depois de ordenados, pega o que ficou no meio entre eles e coloca na
	 * última posição da partição (r). */
	dados minivetor[3];
	minivetor[0]=v[p], minivetor[1]=v[(p+r)/2], minivetor[2]=v[r];

	int menorNum;
	dados x;
	for(int i=0; i<2; i++){
        menorNum=i;
		for(int j=i+1; j<3; j++){
			if(minivetor[j].chave<minivetor[menorNum].chave)
				menorNum=j;
		}
		trocar(minivetor, menorNum, i);
	}
	v[p]=minivetor[0], v[(p+r)/2]=minivetor[2], v[r]=minivetor[1];
}

void printar(dados *v, int n){
	printf("\n");
	for(int i=0; i<n; i++){
		printf("%.2f ", v[i].chave);
	}
}

void insertionSort(dados *v, int n){
    int j, i;
    dados x;
    for(j=1; j<n; j++){
        x=v[j];
        i=j-1; //"i" fica sempre atrás do "j"
        while(v[i].chave>x.chave && i>=0){
            v[i+1]=v[i];
            i--;
        }
        v[i+1]=x;
    }
}

void mergeSort(dados *v, int p, int r){
	if(p<r){
		int q=((p+r)/2);
		mergeSort(v, p, q);
		mergeSort(v, q+1, r);
		intercalar(v, p, q, r);
	}
}

void intercalar(dados *A, int p, int q, int r){
	int n=(r-p)+1;
	int i, j;
	/* O índice 'j' acompanha o vetor auxiliar B, enqnt o índice 'i' acompanha o vetor A.
	 * Nem sempre a parte do vetor que será intercalada será do mesmo tamanho que o vetor
	 * original pois são feitas várias divisoes, pra isso são necessários dois índices.*/

	dados *B=(dados*)malloc(n*sizeof(dados));
	for(i=p, j=0; i<=q; i++, j++) // Inserção da primeira parte no vetor B. Ocorre normalmente.
		B[j]=A[i];

	for(i=r; i>q; i--, j++){ //  O índice j continua do mesmo ponto em que ele parou no for anterior.
		B[j]=A[i]; //Os elementos são inseridos ao contrário, começando por r até q+1.
	}

	int k; //A partir daqui começa a ordenação dentro do vetor A. O índice k acompanha o vetor A.
	i=0, j=n-1; //Os índices 'i' e 'j' passam a acompanhar o vetor B.
	for(k=p; k<=r; k++){
        /* Se o elemento 'i' for menor, ele é passado pra A e 'i' aumenta.
		 * A condição <= faz com que entre nesse if caso os dois sejam iguais, tornando
		 * a ordenação estável. Se não, o elemento 'j' é passado pra A.*/
		if(B[i].chave <= B[j].chave){
			A[k]=B[i++];
		}
		else{
			A[k]=B[j--];
        }// Lembre-se que o 'j' está na ponta, então 'j' diminui!
	}
}

float acharMAX(dados *v, int n){
	float max=v[0].chave;
	for(int i=0; i<n; i++){
		if(v[i].chave>max)
			max=v[i].chave;
	}
	return max;
}

void radixSort(dados *v, int n){
	//encontra o maior número para saber com até quantos digitos iremos trabalhar
	float max=acharMAX(v, n);
	float expoente;

	for(expoente=0.01; max/expoente>0; expoente*=10){ //começa em 1/100 já que os elementos são decimais
		countingSort(v, n, expoente);
	}
}

void countingSort(dados *A, int n, float exp){
    int i;
	int *B=(int*)calloc(10,sizeof(int));

	for(i=0; i<n; i++){ //soma cada posição do vetor A no respectivo índice no vetor B.
		B[(int)fmod(A[i].chave/exp, 10)]+=1;
	}
	for(i=1; i<10; i++){ //soma cada i-ésimo valor na posição seguinte.
		B[i]+=B[i-1];
	}

	dados *C=(dados*)malloc(n*sizeof(dados));
	for(i=n-1; i>=0; i--){ //insere os elementos de forma ordenada chave novo vetor.
		C[B[(int)fmod(A[i].chave/exp, 10)]-1]=A[i];
		B[(int)fmod(A[i].chave/exp, 10)]--;
	}
	for(i=0; i<n; i++)
		A[i]=C[i];
}


void refazerHeap(dados *v, int k, int n){ //k: elemento "errado"
    dados x=v[k]; //x=chave, usado pra armazenar o valor de v[k] pra comparar mais tarde
    int i=k, j=(2*i)+1;
    while(j<n){
    	if(v[j].chave<v[j+1].chave && (j+1)<n)
    		j++;
    	if(x.chave>=v[j].chave) break; //o elemento já está na posição correta
    	v[i]=v[j];
    	i=j, j=(2*i)+1;
    }
    v[i]=x;
}

void construirHeap(dados *v, int n){
    int i=n/2;
    while(i>=0){
        refazerHeap(v, i, n);
        i--;
    }
}

void heapSort(dados *v, int n){
    construirHeap(v, n);
    int i=n-1;
    while(i>0){
        trocar(v, 0, i); //muda a raiz com a última posição
        refazerHeap(v, 0, i-1); //passa a usar i como "n" do refazerHeap
        i--;
    }
}
