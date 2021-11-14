#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct no{
    short int numero;
    char naipe;
    struct no *prox;
} tCarta;

tCarta *primMesa[8];
tCarta *primNaipe[4];
tCarta *temp[4];
tCarta *cartas[52];

void inicializaPilhas(){
    int i;
    for(i=0;i<8;i++){
        primMesa[i] = NULL;
    }
    for(i=0;i<4;i++){
        primNaipe[i] = NULL;
        temp[i] = NULL;
    }
}

void gerarBaralho(){
    int i, num = 1;
    tCarta *novo;

    int copas = 3;
    int ouros = 4;
    int paus = 5;
    int espadas = 6;

    for(i=0;i<52;i++){
        novo = (tCarta*)malloc(sizeof(tCarta));
        if(num == 14){
            num = 1;
        }
        novo->numero = num;
        if(i<13){
            novo->naipe = copas;
        }
        if((i>=13) && (i<26)){
            novo->naipe = ouros;
        }
        if((i>=26) && (i<39)){
            novo->naipe = paus;
        }
        if((i>=39) && (i<52)){
            novo->naipe = espadas;
        }
        cartas[i] = novo;
        num++;
    }
}

void embaralhaBaralho(){
    int i, pos;
    tCarta *aux;

    for(i=0;i<52;i++){
        pos = rand() % 52;
        aux = cartas[i];
        cartas[i] = cartas[pos];
        cartas[pos] = aux;
    }
}

void distribuirMesa(){
    int i;
    for(i=0;i<7;i++){
        cartas[i]->prox = primMesa[0];
        primMesa[0] = cartas[i];
    }
    for(i=7;i<14;i++){
        cartas[i]->prox = primMesa[1];
        primMesa[1] = cartas[i];
    }
    for(i=14;i<21;i++){
        cartas[i]->prox = primMesa[2];
        primMesa[2] = cartas[i];
    }
    for(i=21;i<28;i++){
        cartas[i]->prox = primMesa[3];
        primMesa[3] = cartas[i];
    }
    for(i=28;i<34;i++){
        cartas[i]->prox = primMesa[4];
        primMesa[4] = cartas[i];
    }
    for(i=34;i<40;i++){
        cartas[i]->prox = primMesa[5];
        primMesa[5] = cartas[i];
    }
    for(i=40;i<46;i++){
        cartas[i]->prox = primMesa[6];
        primMesa[6] = cartas[i];
    }
    for(i=46;i<52;i++){
        cartas[i]->prox = primMesa[7];
        primMesa[7] = cartas[i];
    }
}

void imprime(){
    int i;
    tCarta *atual;

    printf("[TEMP] = ");
    for(i=0;i<4;i++){
        if(temp[i]!=NULL){
            printf("%d-[%d/%c] ",i,temp[i]->numero,temp[i]->naipe);
        }
    }
    printf("\n\n");

    for(i=0;i<4;i++){
        atual = primNaipe[i];

        printf("[NAIPE %d] = ",i);
        while(atual != NULL){
            printf("[%2d/%c] ",atual->numero,atual->naipe);
            atual = atual->prox;
        }
        printf("\n");
    }
    printf("\n");

    for(i=0;i<8;i++){
        atual = primMesa[i];

        printf("[MESA %d] = ",i);
        while(atual != NULL){
            printf("[%2d/%c] ",atual->numero,atual->naipe);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void moveMesaTemp(){
    int mesa, posTemp;
    printf("Selecione a MESA(0-7): ");
    scanf("%d",&mesa);
    printf("Digite a posicao do TEMP(0-3): ");
    scanf("%d",&posTemp);

    if((mesa >= 0) && (mesa < 8)){
        if((posTemp >= 0) && (posTemp < 4)){
            tCarta *ant = NULL;
            tCarta *atual = primMesa[mesa];

            if(atual != NULL){

                while(atual->prox != NULL){
                    ant = atual;
                    atual = atual->prox;
                }

                if(temp[posTemp] == NULL){
                        if(ant != NULL){
                            ant->prox = atual->prox;
                            temp[posTemp] = atual;
                        }else{
                            primMesa[mesa] = NULL;
                            temp[posTemp] = atual;
                        }
                    printf("\nA carta foi movida para o TEMP %d\n",posTemp);
                }else{
                    printf("\nA posicao (%d) do temp esta em uso\n",posTemp);
                }

            }
        }else{
            printf("\nPosicao TEMP invalida\n");
        }
    }else{
        printf("\nMESA invalida\n");
    }

}

void moveMesaNape(){
    int mesa, posNape;
    printf("Selecione a MESA(0-7): ");
    scanf("%d",&mesa);
    printf("Digite a posicao do NAIPE(0-3): ");
    scanf("%d",&posNape);

    if((mesa >= 0) && (mesa < 8)){
        if((posNape >= 0) && (posNape < 4)){
            tCarta *ant = NULL;
            tCarta *atual = primMesa[mesa];

            if(atual != NULL){
                while(atual->prox != NULL){
                    ant = atual;
                    atual = atual->prox;
                }

                tCarta *napeAtual = primNaipe[posNape];

                if(napeAtual == NULL){
                    if(atual->numero == 1){
                        if(ant != NULL){
                            ant->prox = atual->prox;
                            atual->prox = primNaipe[posNape];
                            primNaipe[posNape] = atual;
                        }else{
                            primMesa[mesa] = NULL;
                            atual->prox = primNaipe[posNape];
                            primNaipe[posNape] = atual;
                        }
                    }else{
                        printf("\nCarta nao pode ser movida\n");
                    }
                }
                if(napeAtual != NULL){
                    while(napeAtual->prox != NULL){
                        napeAtual = napeAtual->prox;
                    }
                    if((napeAtual->numero == (atual->numero - 1)) && (napeAtual->naipe == atual->naipe)){
                        if(ant != NULL){
                            ant->prox = atual->prox;
                            napeAtual->prox = atual;
                        }else{
                            primMesa[mesa] = NULL;
                            napeAtual->prox = atual;
                        }
                    }else{
                        printf("\nCarta nao pode ser movida\n");
                    }
                }
            }
        }else{
            printf("\nPosicao NAIPE invalida\n");
        }
    }else{
        printf("\nMESA invalida\n");
    }

}

void moveTempMesa(){
    int mesa, posTemp;
    int copas = 3;
    int ouros = 4;
    int paus = 5;
    int espadas = 6;
    int corTemp, corMesa;

    printf("Digite a posicao do TEMP(0-3): ");
    scanf("%d",&posTemp);
    printf("Selecione a MESA(0-7): ");
    scanf("%d",&mesa);

    if((mesa >= 0) && (mesa < 8)){
        if((posTemp >= 0) && (posTemp < 4)){
            tCarta *ant = NULL;
            tCarta *atual = primMesa[mesa];

            if(atual != NULL){
                while(atual->prox != NULL){
                    ant = atual;
                    atual = atual->prox;
                }
                if(temp[posTemp] != NULL){
                    if(temp[posTemp]->numero + 1 == atual->numero){
                        if((temp[posTemp]->naipe == copas) || (temp[posTemp]->naipe == ouros)){
                            corTemp = 0;
                        }else{
                            corTemp = 1;
                        }
                        if((atual->naipe == copas) || (atual->naipe == ouros)){
                            corMesa = 0;
                        }else{
                            corMesa = 1;
                        }
                        if(corTemp != corMesa){
                            atual->prox = temp[posTemp];
                            temp[posTemp] = NULL;
                        }else{
                            printf("\nAs cartas possuem cores iguais\n");
                        }
                    }else{
                        printf("\nMovimento invalido\n");
                    }
                }else{
                    printf("\nSem carta nesta posicao TEMP\n");
                }
            }
            if(primMesa[mesa] == NULL){
                primMesa[mesa] = temp[posTemp];
                primMesa[mesa]->prox = NULL;
                temp[posTemp] = NULL;
            }
        }else{
            printf("\nPosicao TEMP invalida\n");
        }
    }else{
        printf("\nMESA invalida\n");
    }

}

void destroiPilhas(){
    int i;
    for(i=0;i<8;i++){
        tCarta *atual = primMesa[i];
        tCarta *apaga;
        while(atual != NULL){
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }
    }
    for(i=0;i<4;i++){
        tCarta *atual1 = primNaipe[i];
        tCarta *atual2 = temp[i];
        tCarta *apaga;
        while(atual1 != NULL){
            apaga = atual1;
            atual1 = atual1->prox;
            free(apaga);
        }
        while(atual2 != NULL){
            apaga = atual2;
            atual2 = atual2->prox;
            free(apaga);
        }
    }
}

int main(int argc, char **argv){
    int op=0;
    srand(time(NULL));
    inicializaPilhas();
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();
    while(op!=4){
        imprime();
        printf("(1)Move Mesa-Temp\n");
        printf("(2)Move Mesa-Nape\n");
        printf("(3)Move Temp-Mesa\n");
        printf("(4)Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                moveMesaTemp();
                break;
            case 2:
                moveMesaNape();
                break;
            case 3:
                moveTempMesa();
                break;
            case 4:
                printf("Voce saiu do jogo.\n");
                break;
            default:
                printf("Opcao Invalida.\n");
                break;
        }
        system("pause");
        system("cls");
    }
    destroiPilhas();
    return 0;
}
