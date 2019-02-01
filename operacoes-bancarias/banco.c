#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define TR 0

typedef struct data{
    int dia,
        mes,
        ano;
} data;

typedef struct pilha{
    struct data calendario;
    char historico[50];
    float valor;
    char simbolo[11];
    struct pilha *prox;
} pilha;

typedef struct dados{
    char nome[100];
    char cpf[13];
    unsigned int num_conta;
    struct data data_nascimento;
    char telefone[12];
    float saldo_cor;
    float saldo_poup;
} dados;

typedef struct lista{
    struct dados clientes;
    struct pilha *head_extrato;
    struct lista *prox;
} lista;

void abrir_Conta(dados *pessoa, int *x, lista *head, lista **end_conta);
void verificar_Nome(dados *pessoa);
void insere_Inicio(dados pessoa, lista *head);
void escolha(int *x);
void deslogar(int *x, lista *head, dados pessoa, lista **end_conta);
void inserir_Pilha(lista *end_conta, char *tipo, char *simbolo, int dia, int mes, int ano, float valor);
int deposito(lista *end_conta);
int saque(lista *end_conta);
void saldo(lista *end_conta);
void recargacel(lista *end_conta);
void rendimento_poup(lista *end_conta);
void exibirLista(lista *head);
int conferir_Data(int dia, int mes, int ano);
void exibir_Extrato(lista *end_conta);
void cancelar_Contrato(lista **end_conta, lista*head);
int transferencia(lista *end_conta, lista *head);
void liberar_memoria(lista *head);
void escreverArquivo(lista *head, FILE *arq);
void inser_listaArquivo(lista *head, FILE *arq, dados x);
void lerArquivo(lista *head, FILE *arq);
void montante(lista *head);
void clientes_aniversario(lista *head);
int lista_vazia(lista *head);
void clientes_negativados(lista *head);
void cliente_maiorS(lista *head);
void escolha2(int *x);
pilha* inicializar_Pilha();
lista* buscar_Conta(lista *head, unsigned nconta);


int main()
{
    int x; dados pessoa; lista *end_conta=NULL;
    lista *head=(lista*)malloc(sizeof(lista)); //INICIALIZACAO LISTA
    head->prox=NULL;

    printf("Deseja abrir uma conta? Digite:\n1) Sim.\nQualquer outra tecla para nao.\n--> ");
    scanf("%d", &x);
    getchar();

    if(x==1){
        abrir_Conta(&pessoa, &x, head, &end_conta); //PRIMEIRA INICIALIZACAO DE ABRIR CONTA
        end_conta->head_extrato=inicializar_Pilha();
        printf("\n\n\n\nSeja bem vinda(o) ao MiniBank, %s.", pessoa.nome);
        escolha(&x); //ESCOLHA APOS O PRIMEIRO CLIENTE TER SIDO CADASTRADO


        do{
            switch (x){
                case 0: abrir_Conta(&pessoa, &x, head, &end_conta);
                        end_conta->head_extrato=inicializar_Pilha();
                        break;
                case 1: deposito(end_conta);
                        break;
                case 2: saque(end_conta);
                        break;
                case 3: saldo(end_conta);
                        break;
                case 4: transferencia(end_conta, head);
                        break;
                case 5: rendimento_poup(end_conta);
                        break;
                case 6: recargacel(end_conta);
                        break;
                case 7: exibir_Extrato(end_conta);
                        break;
                case 8: deslogar(&x, head, pessoa, &end_conta);
                        break;
                case 9: cancelar_Contrato(&end_conta, head);
                        deslogar(&x, head, pessoa, &end_conta);
                        break;
                case 10: break;
                case 11: exibirLista(head);
                        break;
                default: printf("Digite uma opcao valida.");
                        break;
            }
            escolha(&x);
        } while (x!=10);

        FILE *arq;
        char *url="dadosclientes.dll";
        if( (arq=fopen(url, "w+b")) == NULL){
            printf("Erro ao abrir arquivo.");
            exit(1);
        }
        escreverArquivo(head, arq);
        rewind(arq);
        liberar_memoria(head);
        free(head);
        head=NULL;

        lista *head2=(lista*)malloc(sizeof(lista));
        head2->prox=NULL;
        lerArquivo(head2, arq);

        escolha2(&x);
        do{
            switch(x){
                case 1: exibirLista(head2);
                        break;
                case 2: cliente_maiorS(head2);
                        break;
                case 3: clientes_negativados(head2);
                        break;
                case 4: clientes_aniversario(head2);
                        break;
                case 5: montante(head2);
                        break;
                case 6: printf("\nTchau, tchau!! =D");
                        break;
                default: printf("\nEscolha uma opcao valida.");
                        break;
                } if(x!=6) escolha2(&x);
        } while(x!=6);

        fclose(arq);
        liberar_memoria(head2);
        free(head2);
        head2=NULL;

    }
        else
            printf("\nAte mais!");
        return 0;
}

void escolha(int *x){
    if(*x!=0 && *x!=10){
        printf("\n\nDigite:\n1) Realizar deposito.\n2) Saque.\n3) Verificar saldo.\n4) Transferencia.\n5) Verificar rendimento da poupanca.\n6) Recarga de celular.\n7) Extrato da conta.\n8) Deslogar. \n9) Cancelar contrato.\n--> ");
        do{
            scanf("%d", x);
            getchar();
            if(x==0)
                printf("Insira uma das opcoes valida acima: ");
            }while(x==0); //PARA TORNAR O CAMPO ABRIR CONTA INACESSIVEL SEM ANTES DESLOGAR
    }
}

void deslogar(int *x, lista *head, dados pessoa, lista **end_conta){
    unsigned int nconta;
    printf("Ate mais, %s.", pessoa.nome);
    printf("\n--------------------------\n");
    printf("\n\nSeja bem vinda(o) ao MiniBank!");
    do{
        printf("\nDigite:\n1) Abrir nova conta.\n2) Acessar conta ja cadastrada.\n3) Fechar programa.");
        scanf("%d", x);
        getchar();
        switch(*x){
            case 1: *x=0; /*CADASTRO. O 0 SERVE PARA NAO APARECER O MENU PRESENTE NA MAIN NOVAMENTE*/
                    break;
            case 2:
                    printf("Numero da conta: "); /*ACESSAR CONTA EXISTENTE*/
                    scanf("%d", &nconta);
                    *end_conta=buscar_Conta(head, nconta);
                    if((*end_conta)==0){
                        printf("Conta nao existente. Escolha outra opcao ou entre com uma conta valida.");
                        *x=2; //CONTA NAO ENCONTRADA. X=2 PARA CONTINUAR NO WHILE E O USUARIO TER QUE DIGITAR A CONTA NOVAMENTE
                    }
                    else{
                        *x=1; /*O 1 SERVE PARA ENTRAR NO MENU DA MAIN LOGO APOS ESSA PARTE, CASO O USUARIO TENHA DECIDIDO
                                ACESSAR UMA CONTA EXISTENTE*/
                        printf("\n---- Seja bem vinda(o) ao MiniBank, %s!", (*end_conta)->clientes.nome);
                    }
                    break;
            case 3: *x=10; /*FECHAR O PROGRAMA*/
                    break;
            default:
                    printf("Escolha uma opcao valida.");
                    *x=2;
        }
    } while(*x==2);
}

void abrir_Conta(dados *pessoa, int *x, lista *head, lista **end_conta){
    int invalido=0, i, ch, zeros=0;
    printf("Nome:");
    verificar_Nome(pessoa);

    printf("CPF: ");
    do{
        invalido=0;
        scanf("%s[^\n]", &pessoa->cpf);
        getchar();
        if( (strlen(pessoa->cpf)) < 11 || (strlen(pessoa->cpf) > 11)){
            printf("CPF invalido. Insira novamente: ");
            invalido=1;
        }
        else{
            for(i=0; i<11; i++){
                ch=pessoa->cpf[i];
                if(ch<48 || ch>57){
                    printf("CPF invalido. Insira apenas numeros: ");
                    invalido=1;
                    break;
                }
            }
        }
    }while(invalido==1);

    printf("Data de nascimento, insira no formato xx/xx/xxxx: ");
    do{
        invalido=0;
        scanf("%d/%d/%d", &pessoa->data_nascimento.dia, &pessoa->data_nascimento.mes, &pessoa->data_nascimento.ano);
        getchar();
        invalido=conferir_Data(pessoa->data_nascimento.dia, pessoa->data_nascimento.mes, pessoa->data_nascimento.ano);
    } while(invalido==1);


    printf("Telefone (com DDD, apenas numeros): ");
    do{
        invalido=0, zeros=0;
        scanf("%s[^\n]", &pessoa->telefone);
        getchar();
        if(strlen(pessoa->telefone)<10){ //CASO TENHA MENOS DIGITOS
            printf("Numero invalido. Insira novamente: ");
            invalido=1;
        }
        else{ //CASO TENHA CARACTERES OU SÓ SEJA COMPOSTO DE ZEROS
            for(i=0; i<10; i++){
                ch=pessoa->telefone[i];
                if(ch<48 || ch>57){
                    printf("Numero invalido.\nInsira apenas numeros: ");
                    invalido=1;
                    break;
                }
                if(pessoa->telefone[i]=='0'){ //CONTA QUANTAS VEZES O 0 APARECE
                    zeros++;
                }
                if(zeros==2 && i==1){ //CASO O DDD SEJA 00
                    printf("\nDDD invalido. Digite um telefone valido: ");
                    invalido=1;
                    break;
                }
            }
            if(zeros==10){
                printf("\nNumero invalido. Insira novamente: ");
                invalido=1;
            }
        }
    } while(invalido==1);

    srand( (unsigned)time(NULL) );
    pessoa->num_conta=10000+(rand() % RAND_MAX);
    printf("\n\nCadastro efetuado com sucesso.\n------ O numero da sua conta eh: %u \nAnote-o com cuidado, ele sera necessario para acessar sua conta mais tarde.\n", pessoa->num_conta);

    *x=1; /*QUANDO A PESSOA ESCOLHE ABRIR CADASTRO NA FUNCAO 'DESLOGAR',
            O X FICA IGUAL A 0 PARA O MENU DA MAIN NAO APARECER LOGO APOS.
            SE O X NAO FOSSE DECLARADO COMO 1 AQUI, O MENU NAO APARECERIA MAIS*/
    insere_Inicio(*pessoa, head);
    *end_conta=head->prox; //GUARDAR ENDERECO
}

void insere_Inicio(dados pessoa, lista *head){
    lista *novo=(lista*)malloc(sizeof(lista));
    strcpy(novo->clientes.nome, pessoa.nome);
    strcpy(novo->clientes.cpf, pessoa.cpf);
    strcpy(novo->clientes.telefone, pessoa.telefone);
    novo->clientes.data_nascimento.dia=pessoa.data_nascimento.dia;
    novo->clientes.data_nascimento.mes=pessoa.data_nascimento.mes;
    novo->clientes.data_nascimento.ano=pessoa.data_nascimento.ano;
    novo->clientes.num_conta=pessoa.num_conta;
    novo->clientes.saldo_cor=0;
    novo->clientes.saldo_poup=0;

    if(head->prox==NULL){
        head->prox=novo;
        novo->prox=NULL;
    }
    else{
        novo->prox=head->prox;
        head->prox=novo;
    }
}

lista* buscar_Conta(lista *head, unsigned nconta){
    lista *tmp;
    tmp=head->prox;
    while(tmp!=NULL){ //CASO ENCONTRE A CONTA DESEJADA
        if(tmp->clientes.num_conta==nconta)
            break;
        tmp=tmp->prox;
    }

    if(tmp==NULL){ //CASO NAO ENCONTRE A CONTA DESEJADA
        printf("Conta nao existente.");
        return NULL;
    }
    else{
        return tmp;
    }
}

void exibirLista(lista *head){
    lista *tmp;
    tmp=head->prox;
    while(tmp!=NULL){
        printf("NOME:%s\nCPF:%s\nTELEFONE:%s\nDATA DE NASCIMENTO:%d/%d/%d\n-------------\n", tmp->clientes.nome, tmp->clientes.cpf, tmp->clientes.telefone, tmp->clientes.data_nascimento.dia, tmp->clientes.data_nascimento.mes, tmp->clientes.data_nascimento.ano);
        tmp=tmp->prox;
    }
}

void inserir_Pilha(lista *end_conta, char *tipo, char *simbolo, int dia, int mes, int ano, float valor){
    pilha *novo=(pilha*)malloc(sizeof(pilha));
    strcpy(novo->historico, tipo);
    strcpy(novo->simbolo, simbolo);
    novo->valor=valor;
    novo->calendario.dia=dia;
    novo->calendario.mes=mes;
    novo->calendario.ano=ano;
    novo->prox=NULL;

    if(end_conta->head_extrato->prox==NULL) //SE FOR O PRIMEIRO ELEMENTO
        end_conta->head_extrato->prox=novo;
    else{ //SE NAO FOR, BUSCA O ULTIMO
        pilha *tmp=end_conta->head_extrato->prox;
        while(tmp->prox!=NULL)
            tmp=tmp->prox;
        tmp->prox=novo;
    }
}

pilha* inicializar_Pilha(){
    pilha *cabeca; //INICIALIZACAO DA PILHA DO EXTRATO
    cabeca=(pilha*)malloc(sizeof(pilha));
    cabeca->prox=NULL;
    return cabeca;
}

int deposito(lista *end_conta){
    float valor; int y;
    char simbolo[2]="+", tipo[9]="deposito";

    printf("\n---- Digite:\n1) Deposito na conta corrente.\n2) Deposito na poupanca.\n--> ");
    do{
        scanf("%d", &y);
        getchar();
        if(y!=1 && y!=2)
            printf("\nDigite um valor valido:\n1) Deposito na conta corrente.\n2) Deposito na poupanca.\n--> ");
        } while(y!=1 && y!=2);

    SYSTEMTIME calendario;
    GetSystemTime(&calendario);

    printf("Valor do deposito:\n--> ");
    do{
        scanf("%f", &valor);
        getchar();
        if(valor<0)
            printf("Digite um valor valido:\n--> ");
        else if(valor>1000000000)
            printf("Digite um valor menor do que R$1.000.000.000:\n--> ");
        else if( (end_conta->clientes.saldo_cor)+valor >=10000000000)
            printf("O MiniBank ainda nao trabalha com valores tao altos, o saldo limite possivel eh de R$10.000.000.000.\nVoce so pode depositar mais %.2f, digite novamente:\n--> ", (10000000000.0-end_conta->clientes.saldo_poup) );
        else if( (end_conta->clientes.saldo_cor)+valor==10000000000){
            printf("O MiniBank ainda nao trabalha com valores tao altos. Sua conta atingiu o saldo limite de R$10.000.000.000");
            return 0;
            }
    } while (valor<0 || valor>1000000000 || (end_conta->clientes.saldo_cor)+valor >=10000000000);

    if(y==1){
        end_conta->clientes.saldo_cor+=valor;
    }
    else{
        end_conta->clientes.saldo_poup+=valor;
    }
    inserir_Pilha(end_conta, tipo, simbolo, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
    printf("---- Deposito realizado com sucesso.");
    return 1;
}

void saldo(lista *end_conta){
    int y;
    printf("\nDigite:\n1) Verificar saldo conta corrente.\n2) Verificar saldo poupanca.\n----> ");
    do{
        scanf("%d", &y);
        if(y!=1 && y!=2)
            printf("\nDigite um valor valido:\n1) Deposito na conta corrente.\n2) Deposito na poupanca.");
        } while(y!=1 && y!=2);
    if(y==1)
        printf("\nSALDO: R$%.2f", end_conta->clientes.saldo_cor);
    if(y==2)
        printf("\nSALDO: R$%.2f", end_conta->clientes.saldo_poup);
}

void exibir_Extrato(lista *end_conta){
    pilha *tmp=end_conta->head_extrato->prox;
    printf("\n");
    while(tmp!=NULL){
        printf("\nDIA:%d/%d/%d HISTORICO:%s VALOR: R$%.2f SIMBOLO: %s", tmp->calendario.dia, tmp->calendario.mes, tmp->calendario.ano, tmp->historico, tmp->valor, tmp->simbolo);
        tmp=tmp->prox;
    }
}

void cancelar_Contrato(lista **end_conta, lista *head){
    if(head->prox==*end_conta){
        head->prox=NULL;
        free(*end_conta);
    }
    else{
        lista *tmp;
        tmp=head->prox;
        while(tmp->prox!=(*end_conta))
            tmp=tmp->prox;
        tmp->prox=(*end_conta)->prox;
        free(*end_conta);
    }
    printf("\nFoi bom ter voce conosco. =(\nContrato cancelado com sucesso. ");
}

int saque(lista *end_conta){
    float valor; int y;
    char simbolo[2]="-", tipo[6]="saque";

    printf("\n---- Digite:\n1) Saque na conta corrente.\n2) Saque na poupanca.\n--> ");
    do{
        scanf("%d", &y);
        getchar();
        if(y!=1 && y!=2)
            printf("\nDigite um valor valido:\n1) Saque na conta corrente.\n2) Saque na poupanca.\n--> ");
        } while(y!=1 && y!=2);

    SYSTEMTIME calendario;
    GetSystemTime(&calendario);

    printf("Valor do saque: ");
    do{
        scanf("%f", &valor);
        getchar();
        if(valor<0)
            printf("Digite um valor valido: ");
        if(valor>5000)
            printf("Para sua seguranca, nao eh possivel realizar saques de valor superior a R$5000.\nDigite um valor menor ou 0 para sair: ");
    } while (valor<0 || valor>5000);

    if( (y==1 && (end_conta->clientes.saldo_cor)<valor-100) || (y==2 && (end_conta->clientes.saldo_poup)<valor) ){
        printf("Saldo insuficiente.");
        return 0;
    }

    if(y==1)
        end_conta->clientes.saldo_cor-=valor;
    else
        end_conta->clientes.saldo_poup-=valor;
    inserir_Pilha(end_conta, tipo, simbolo, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
    printf("---- Saque realizado com sucesso.");
    return 1;
}

void verificar_Nome(dados *pessoa){
    int n, ch, repetido=0, i;
    do{
        fgets(pessoa->nome, 100, stdin);
        pessoa->nome[strlen(pessoa->nome)-1]='\0';
        n=pessoa->nome[0];
        for(i=0; i<strlen(pessoa->nome); i++){
            ch=pessoa->nome[i];

            if(ch<65 || ch>122){  //CASO SEJA ALGUM SIMBOLO OU NUMERO
                    if(ch!=32){
                    printf("Nome invalido. Insira apenas letras: ");
                    repetido=3;
                    break;
                    }
                }

            else if(pessoa->nome[i]==n && i!=0){ //CASO TENHA LETRAS REPETIDAS
                repetido++;
                if(repetido>=3){
                    printf("Nome invalido. Digite novamente: ");
                    break;
                }
            }
            else if(pessoa->nome[i]!=n && repetido<=3){
                repetido=1;
                n=pessoa->nome[i];
            }
        }

    } while(repetido>=3);
}

int conferir_Data(int dia, int mes, int ano){
    if(dia<1 || dia>31){
        printf("Data invalida. Insira novamente: ");
        return 1;
        }
    else if(mes<=0 || mes >= 13){
        printf("Data invalida. Insira novamente: ");
        return 1;
        }
    else if(ano<1900 || ano>1999){
        printf("Data invalida. Insira novamente (idade minima 18 anos): ");
        return 1;
        }
    else
        return 0;
}

int transferencia(lista *end_conta, lista *head){
    float valor;
    int y, invalido; unsigned acc;
    lista *acc_transf;

    printf("\n---- Digite:\n1) Transferencia com saldo da conta corrente.\n2) Transferencia com saldo da poupanca.\n--> ");
    do{
        scanf("%d", &y);
        getchar();
        if(y!=1 && y!=2)
            printf("\nDigite um valor valido:\n1) Transferencia na conta corrente.\n2) Transferencia na poupanca.\n--> ");
        } while(y!=1 && y!=2);

    SYSTEMTIME calendario;
    GetSystemTime(&calendario);

    invalido=0;
    printf("Digite o numero da conta em que deseja fazer a transferencia: ");
    do{
        scanf("%u", &acc);
        getchar();
        if(acc==end_conta->clientes.num_conta){ //CASO O CLIENTE QUEIRA TRANSFERIR PARA A PROPRIA POUPANCA//CONTA CORRENTE
                break;
                }
        acc_transf=buscar_Conta(head, acc);
        if(acc_transf==NULL){
            printf("Conta nao existente. Digite novamente: ");
            invalido++;
        }
        else
            invalido=0;
        if(invalido>=2){
            printf("Conta nao existente. Maximo de tentativas atingido.");
            return 0;
        }
    } while(invalido!=0);

    printf("Valor da transferencia: ");
    do{
        scanf("%f", &valor);
        getchar();
        if(valor<0)
            printf("Digite um valor valido: ");
        if( (y==1 && valor>(end_conta->clientes.saldo_cor)+100) || (y==2 && valor>(end_conta->clientes.saldo_poup) )){
            printf("Saldo insuficiente.");
            return 0;
        }
    } while (valor<0);

    if(acc!=end_conta->clientes.num_conta){ //DEBITACAO CONTAS DISTINTAS
        acc_transf->clientes.saldo_cor+=valor;
        if(y==1){
            end_conta->clientes.saldo_cor-=valor;
            }
        else{
            end_conta->clientes.saldo_poup-=valor;
            }
        char simbolo[]="-", tipo[]="transferencia", simbolo2[]="+";
        inserir_Pilha(end_conta, tipo, simbolo, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
        inserir_Pilha(acc_transf, tipo, simbolo2, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
    }

    else{ //DEBITACAO TRANSF ENTRE COR/POUP E POUP/COR
        char simbolo[3], tipo[]="transferencia", simbolo2[3];
        if(y==1){
            end_conta->clientes.saldo_cor-=valor;
            end_conta->clientes.saldo_poup+=valor;
            strcpy(simbolo, "-C");
            strcpy(simbolo2, "+P");
        }
        if(y==2){
            end_conta->clientes.saldo_poup-=valor;
            end_conta->clientes.saldo_cor+=valor;
            strcpy(simbolo, "-P");
            strcpy(simbolo2, "+C");
        }
        inserir_Pilha(end_conta, tipo, simbolo, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
        inserir_Pilha(end_conta, tipo, simbolo2, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
    }

    printf("---- Transferencia realizado com sucesso.");
    return 1;
}

void recargacel(lista *end_conta){
    char celular[12], tipo[]="recarga cel", simbolo[]="-";
    float valor; int invalido, zeros=0, i, ch;
    printf("Digite o numero do celular (apenas numeros, junto ao ddd):");
    do{
        invalido=0;
        scanf("%s^[\n]", &celular);
        getchar();
        if(strlen(celular)<11){
            printf("Digite um numero de celular valido. ");
            invalido=1;
            }
        else{
            for(i=0; i<11; i++){
                ch=celular[i];
                if(ch<48 || ch>57){
                    printf("Numero invalido.\nInsira apenas numeros: ");
                    invalido=1;
                    break;
                }
                if(celular[i]=='0'){ //CONTA QUANTAS VEZES O 0 APARECE
                    zeros++;
                }
            }
        if(zeros==11)
            invalido=1;
        } } while(invalido==1);

    printf("Digite o valor de desejado para a recarga: ");
    do{
        invalido=0;
        scanf("%f", &valor);
        if(valor<0 || valor>300){
            printf("Valor invalido. O valor maximo de recarga eh R$300.00.\nInsira novamente: ");
            invalido=1;
            }
    }while(valor<0 || valor>300);

    SYSTEMTIME calendario;
    GetSystemTime(&calendario);

    end_conta->clientes.saldo_cor-=valor;
    inserir_Pilha(end_conta, tipo, simbolo, calendario.wDay, calendario.wMonth, calendario.wYear, valor);
    printf("---- Recarga realizada com sucesso.");
}

void rendimento_poup(lista *end_conta){
    float taxaselic;
    printf("Para realizar a simulacao, digite o valor da taxa selic atual:\n--> ");
    do{
        scanf("%f", &taxaselic);
        getchar();
        if(taxaselic<0)
            printf("Valor invalido. Insira novamente: ");
        else if(taxaselic>20)
            printf("Valor invalido. Insira novamente: ");
    }while(taxaselic<0 || taxaselic>20);

    if(taxaselic>8.5){
        printf("\nRENDIMENTO MENSAL DA SUA POUPANCA: R$%f", end_conta->clientes.saldo_poup*(TR + 0.5) );
    }
    else{
        printf("\nRENDIMENTO MENSAL DA SUA POUPANCA: R$%f", end_conta->clientes.saldo_poup*(TR + (taxaselic*0.7) ) );
    }
}

void escreverArquivo(lista *head, FILE *arq){
    lista *tmp=head->prox;
    struct dados usuarios;
    if(lista_vazia(head))
        exit(2);
    while(tmp!=NULL){
        usuarios=tmp->clientes;
        if( (fwrite(&usuarios, sizeof(dados), 1, arq)) != 1){
            printf("Erro ao escrever no arquivo.");
            exit(3);
        }
        tmp=tmp->prox;
    }
}

void inser_listaArquivo(lista *head, FILE *arq, dados x){
    lista *novo=(lista*)malloc(sizeof(lista));
    novo->prox=NULL;
    novo->clientes=x;
    if(head->prox==NULL)
        head->prox=novo;
    else{
        novo->prox=head->prox;
        head->prox=novo;
    }
}

void lerArquivo(lista *head, FILE *arq){
    struct dados usuarios;
    while(fread(&usuarios, sizeof(dados), 1, arq)){
        inser_listaArquivo(head, arq, usuarios);
    }
}

void liberar_memoria(lista *head){
    lista *atual, *proximo;
    if(head->prox==NULL)
        printf("Lista vazia.");
    else{
        atual=head->prox;
        while(atual!=NULL){
            proximo=atual->prox;
            free(atual);
            atual=NULL;
            atual=proximo;
        }
    }

}

void escolha2(int *x){
    printf("\n\nDigite:\n1) Exibir todos os clientes.\n2) Exibir cliente com maior saldo na conta corrente e na poupanca.\n3) Exibir clientes com saldo negativo.\n4) Exibir clientes de aniversario em certo mes.\n5) Exibir montante.\n6)Fechar programa.\n--> ");
    scanf("%d", x);
}

void cliente_maiorS(lista *head){
    lista *tmp=head->prox, *endmaior_c=head->prox, *endmaior_p=head->prox; //GUARDAR O ENDERECO DOS CLIENTES COM MAIORES SALDOS
    float maior_cor=tmp->clientes.saldo_cor, maior_poup=tmp->clientes.saldo_poup,
          menor_cor=tmp->clientes.saldo_cor, menor_poup=tmp->clientes.saldo_poup;

    if(!lista_vazia(head)){
        while(tmp!=NULL){
            if( (tmp->clientes.saldo_cor) > maior_cor ){
                maior_cor=tmp->clientes.saldo_cor;
                endmaior_c=tmp;
            }
            else if( (tmp->clientes.saldo_cor) < menor_cor ){
                menor_cor=tmp->clientes.saldo_cor;
            }

            if( (tmp->clientes.saldo_poup) > maior_poup){
                maior_poup=tmp->clientes.saldo_poup;
                endmaior_p=tmp;
            }
            else if( (tmp->clientes.saldo_poup) < menor_poup){
                menor_poup=tmp->clientes.saldo_poup;
            }
            tmp=tmp->prox;
        }

        if(maior_cor!=0 || maior_poup!=0){
                //CASO TENHA ENCONTRADO ALGUM MAIOR POSITIVO, PROCURA POR CONTAS COM SALDOS IGUAIS.
                tmp=head->prox;
                while(tmp!=NULL){
                        if ( (tmp->clientes.saldo_cor) == maior_cor && maior_cor!=0 && tmp!=endmaior_c)
                            printf("\nNOME:%s, SALDO CORRENTE:R$%f, CONTA:%u\n", tmp->clientes.nome, tmp->clientes.saldo_cor, tmp->clientes.num_conta);
                        if ( (tmp->clientes.saldo_poup) == maior_poup && maior_poup!=0 && tmp!=endmaior_c)
                            printf("\nNOME:%s, SALDO POUPANCA:R$%f, CONTA:%u", tmp->clientes.nome, tmp->clientes.saldo_poup, tmp->clientes.num_conta);
                        tmp=tmp->prox;

                }
                if(maior_cor!=0)
                    printf("\nNOME:%s, SALDO CORRENTE:R$%f, CONTA:%u", endmaior_c->clientes.nome, endmaior_c->clientes.saldo_cor, endmaior_c->clientes.num_conta);
                else if(maior_cor==0 && menor_cor==tmp->clientes.saldo_cor)
                    printf("\nNENHUM CLIENTE POSSUI SALDO NA CONTA CORRENTE.");
                if(maior_poup!=0)
                    printf("\nNOME:%s, SALDO POUPANCA:R$%f, CONTA:%u", endmaior_p->clientes.nome, endmaior_p->clientes.saldo_poup, endmaior_p->clientes.num_conta);
                else if(maior_poup==0 && menor_cor==tmp->clientes.saldo_poup)
                    printf("\nNENHUM CLIENTE POSSUI SALDO NA CONTA POUPANCA.");
        }

        else if(menor_cor!=0 || menor_poup!=0){ //CASO TENHA ENCONTRADO SALDOS MENORES DO QUE 0.
            tmp=head->prox;
                while(tmp!=NULL){
                        if ( (tmp->clientes.saldo_cor) == maior_cor && tmp!=endmaior_c)
                            printf("\nNOME:%s, SALDO CORRENTE:R$%f, CONTA:%u", tmp->clientes.nome, tmp->clientes.saldo_cor, tmp->clientes.num_conta);
                        if ( (tmp->clientes.saldo_poup) == maior_poup && tmp!=endmaior_c)
                            printf("\n%NOME:%s, SALDO POUPANCA:R$%f, CONTA:%u", tmp->clientes.nome, tmp->clientes.saldo_poup, tmp->clientes.num_conta);
                        tmp=tmp->prox;
                }
        }

        else if(maior_cor==0 || maior_poup==0){ //CASO NAO TENHA NENHUM SALDO, NEM NEGATIVO
            printf("NENHUM CLIENTE POSSUI SALDO.");
        }
} }

void clientes_negativados(lista *head){
    lista *tmp=head->prox; int n=0;
    if(!lista_vazia(head)){
        printf("\nCLIENTES COM SALDO NEGATIVADO:\n");
        while(tmp!=NULL){
            if( (tmp->clientes.saldo_cor) < 0 ){
                printf("%s, SALDO:R$%f, CONTA:%u", tmp->clientes.nome, tmp->clientes.saldo_cor, tmp->clientes.num_conta);
                n++;}
            tmp=tmp->prox;
        }
         if(n==0)
            printf("NENHUM.");
    }
}

int lista_vazia(lista *head){
    if(head->prox==NULL){
        printf("Nenhum cliente encontrado.");
        return 1;
    }
    else{
        return 0;
    }
}

void clientes_aniversario(lista *head){
    lista *tmp=head->prox;
    int mes, vezes=0;
    if(!lista_vazia(head)){
        printf("\nDigite o mes desejado(em numeros):\n--> ");
        do{
            scanf("%d", &mes);
            getchar();
            if(mes<1 || mes>12)
                printf("Mes invalido. Insira novamente:\n--> ");
        }while(mes<1 || mes>12);

        while(tmp!=NULL){
            if(tmp->clientes.data_nascimento.mes==mes){
                printf("CLIENTE: %s, CONTA: %u, ANIVERSARIO: %d/%d/%d\n", tmp->clientes.nome, tmp->clientes.num_conta, tmp->clientes.data_nascimento.dia, tmp->clientes.data_nascimento.mes, tmp->clientes.data_nascimento.ano);
                vezes++;
            }
            tmp=tmp->prox;
        }
        if(vezes==0){
            printf("NENHUM CLIENTE FAZ ANIVERSARIO NO MES %d", mes);
        }
    }
}

void montante(lista *head){
    lista *tmp=head->prox;
    float montante=0;
    if(!lista_vazia(head)){
        while(tmp!=NULL){
            if( (tmp->clientes.saldo_cor)>0)
                montante+=tmp->clientes.saldo_cor;
            montante+=tmp->clientes.saldo_poup;
            tmp=tmp->prox;
        }
        printf("\nMONTANTE: R$%f", montante);
    }
}
