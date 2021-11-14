#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<locale.h>

int ramo = 1;
int farinha_de_osso = 0;
int baga = 0;
int jogadas = 1;
char caverna[25][90];

//funcao inicializa a caverna
void inicializa(){
    int i, j, lin, col;
    //espaco
    for(i=0; i<25; i++){
        for(j=0; j<90; j++){
            caverna[i][j]=' ';
        }
    }
    //10 ramos na linha 0
    for(i=0; i<10; i++){
        lin = 0;
        col = rand() % 90;
        if(caverna[lin][col]==' '){
            caverna[lin][col]=':';
        }else{
            i--;
        }

    }
    //4 rochas 2-2-2-2-2
    for(i=0; i<4; i++){
        lin = 20;
        col = rand() % 89;
        caverna[lin][col] = '.';
        caverna[lin][col+1] = '.';
        caverna[lin+1][col] = '.';
        caverna[lin+1][col+1] = '.';
        caverna[lin+2][col] = '.';
        caverna[lin+2][col+1] = '.';
        caverna[lin+3][col] = '.';
        caverna[lin+3][col+1] = '.';
        caverna[lin+4][col] = '.';
        caverna[lin+4][col+1] = '.';
    }
    //3 rochas 3-3-3-3-3-3
    for(i=0; i<3; i++){
        lin = 19;
        col = rand() % 88;
        caverna[lin][col] = '.';
        caverna[lin][col+1] = '.';
        caverna[lin][col+2] = '.';
        caverna[lin+1][col] = '.';
        caverna[lin+1][col+1] = '.';
        caverna[lin+1][col+2] = '.';
        caverna[lin+2][col] = '.';
        caverna[lin+2][col+1] = '.';
        caverna[lin+2][col+2] = '.';
        caverna[lin+3][col] = '.';
        caverna[lin+3][col+1] = '.';
        caverna[lin+3][col+2] = '.';
        caverna[lin+4][col] = '.';
        caverna[lin+4][col+1] = '.';
        caverna[lin+4][col+2] = '.';
        caverna[lin+5][col] = '.';
        caverna[lin+5][col+1] = '.';
        caverna[lin+5][col+2] = '.';
    }
    //10 estalagmites
    for(i=0; i<10; i++){
        lin = 24;
        col = rand() % 90;
        if(caverna[lin][col]==' '){
            caverna[lin][col] = '^';
        }else{
            i--;
        }
    }
    //13 corujas
    for(i=0; i<13; i++){
        lin = 6 + rand() % 13;
        col = rand() % 90;
        if(caverna[lin][col]==' '){
            caverna[lin][col] = 'V';
        }else{
            i--;
        }
    }
    //31 morcegos
    for(i=0; i<31; i++){
        lin = 6 + rand() % 13;
        col = rand() % 90;
        if(caverna[lin][col]==' '){
            caverna[lin][col] = 'W';
        }else{
            i--;
        }
    }
}
//funcao imprime a caverna
void imprime(){
    int i, j;
    printf("              11111111112222222222333333333344444444445555555555666666666677777777778888888888\n");
    printf("    012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
    for(i=0; i<25; i++){
        printf("[%2d]",i);
        for(j=0; j<90; j++){
            printf("%c",caverna[i][j]);
        }
        printf("\n");
    }
}
//funcao fertilizar
void fertilizar(){
    int lin, col;
    if(farinha_de_osso > 0){
        printf("Fertilizar ramo [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        if( (lin>0) && (lin<=24) && (col>=0) && (col<=89) ){
            if(caverna[lin][col] == ':'){
                caverna[lin][col] = '%';
                farinha_de_osso--;
                jogadas++;
            }else{
                printf("Sem ramo na posição indicada\n");
            }
        }else{
            printf("Coordenadas inválidas\n");
        }
    }else{
        printf("Saldo insuficiente de farinha de osso\n");
    }
}
//funcao colher
void colher(){
    int i, lin, col;
    printf("Colher ramo/baga [linha coluna]: ");
    scanf("%d %d", &lin, &col);
    if( (lin>0) && (lin<=24) && (col>=0) && (col<=89) ){
        if((caverna[lin][col] == ':') || (caverna[lin][col] == '%')){
            for(i=lin;i<25;i++){
               if(caverna[i][col] == ':'){
                    caverna[i][col] = ' ';
                    ramo++;
                    jogadas++;
               }
               if(caverna[i][col] == '%'){
                    caverna[i][col] = ' ';
                    baga++;
                    jogadas++;
                }
            }
        }else{
            printf("Sem ramo ou baga na posição indicada\n");
        }
    }else{
        printf("Coordenadas inválidas\n");
    }
}
//funcao ninho
void ninho(){
    int lin, col;
    if(ramo >= 4){
        printf("Construir ninho [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        if( (lin>=0) && (lin<=23) && (col>=0) && (col<=89) ){
            if(caverna[lin+1][col] == '.'){
                if(caverna[lin][col] == ' '){
                    caverna[lin][col] = '#';
                    ramo-=4;
                    jogadas++;
                }else{
                    printf("Posição inválida\n");
                }
            }else{
                printf("O ninho só pode ser construído em cima de uma pedra elavada\n");
            }
        }else{
            printf("Coordenadas inválidas\n");
        }
    }else{
        printf("Saldo insuficiente de ramos\n");
    }
}
//funcao alimentar
void alimentar(){
    int lin, col;
    if(baga>0){
        printf("Alimentar coruja [linha coluna]: ");
        scanf("%d %d", &lin, &col);
        if((lin>=0) && (lin<=24) && (col>=0) && (col<=89)){
            if((caverna[lin][col] == 'v') || (caverna[lin][col] == 'V')){
                    if(caverna[lin][col] == 'V'){
                        if((lin<=22) && (caverna[lin+1][col]=='V') && (caverna[lin+2][col]=='#')){
                            caverna[lin+2][col]='v';
                            baga--;
                            jogadas++;
                        }else{
                            printf("Não é possivel alimentar\n");
                        }
                    }
                    if(caverna[lin][col] == 'v'){
                        caverna[lin][col] = 'V';
                        baga--;
                        jogadas++;
                    }
            }else{
                printf("Posição sem coruja\n");
            }
        }else{
            printf("Coordenadas inválidas\n");
        }
    }else{
        printf("Saldo insuficiente de bagas\n");
    }
}
//funcao mover
void mover(){
    int l1,c1,l2,c2;
    printf("Coodernadas de origem [linha coluna]: ");
    scanf("%d %d", &l1, &c1);
    if((l1>=0) && (l1<=24) && (c1>=0) && (c1<=89)){
        if((caverna[l1][c1]=='v') || (caverna[l1][c1]=='V')){
            printf("Coodernadas de destino [linha coluna]: ");
            scanf("%d %d", &l2, &c2);
            if((l2>=0) && (l2<=24) && (c2>=0) && (c2<=89)){
                if((l2-l1>=-1)&&(l2-l1<=1)&&(c2-c1>=-1)&&(c2-c1<=1)){
                    if((caverna[l2][c2]==' ')||(caverna[l2][c2]=='W')){
                        if(caverna[l2][c2]==' '){
                            caverna[l2][c2]=caverna[l1][c1];
                            caverna[l1][c1]=' ';
                            jogadas++;
                        }
                        if((caverna[l1][c1]=='V')&&(caverna[l2][c2]=='W')){
                            caverna[l2][c2]=caverna[l1][c1];
                            caverna[l1][c1]=' ';
                            farinha_de_osso++;
                            jogadas++;
                        }
                        if((caverna[l1][c1]=='v')&&(caverna[l2][c2]=='W')){
                            printf("Movimento inválido\n");
                        }
                    }else{
                        printf("Movimento inválido\n");
                    }
                }else{
                    printf("Coordenada de destino inválida\n");
                }
            }else{
                printf("Coordenada de destino inválida\n");
            }
        }else{
            printf("Posição sem coruja\n");
        }
    }else{
        printf("Coordenada de origem inválida\n");
    }
}
//funcao dia
void dia(){
    int i,j,lin,col;
    jogadas = 1;
    for(i=0;i<25;i++){
        for(j=0;j<90;j++){
            if(caverna[i][j]=='W'){
                caverna[i][j] = ' ';
            }
        }
    }
    for(j=0;j<90;j++){
        if(caverna[0][j]==':'){
            for(i=0;i<25;i++){
                if((caverna[i][j]==':')||(caverna[i][j]=='%')){
                    if((rand()%100<15)&&(i<12)&&(caverna[i+1][j]==' ')){
                        caverna[i+1][j] = ':';
                        break;
                    }
                }
            }
        }
    }
    for(j=0;j<90;j++){
        if(caverna[24][j]=='^'){
            for(i=0;i<25;i++){
                if((caverna[i][j]=='^')&&(rand()%100<15)&&(i>20)&&(caverna[i-1][j]==' ')){
                    caverna[i-1][j] = '^';
                    break;
                }
            }
        }
    }
    for(i=0; i<31; i++){
        lin = 6 + rand() % 13;
        col = rand() % 90;
        if((caverna[lin][col]==' ')||(caverna[lin][col]=='v')||(caverna[lin][col]=='V')||(caverna[lin][col]=='#')){
            caverna[lin][col] = 'W';
        }else{
            i--;
        }
    }

}
int main(int argc, char * argv[]){
    char opcao;
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    inicializa();
    system("color 0f");
    while(opcao != 's'){
        imprime();
        printf("ramo = %d  farinha de osso = %d  baga = %d\n",ramo,farinha_de_osso,baga);
        printf("(f)ertilizar / (c)olher / (n)inho / (a)limentar / (m)over / (s)air ");
        printf("[Jogada %d] Opção: ",jogadas);
        opcao = getch();
        printf("%c\n",opcao);
        switch(opcao){
        case 'f' :
            fertilizar();
            break;
        case 'c' :
            colher();
            break;
        case 'n' :
            ninho();
            break;
        case 'a' :
            alimentar();
            break;
        case 'm' :
            mover();
            break;
        case 'd' :
            dia();
            break;
        case 's' :
            break;
        default :
            printf("Opção inválida\n");
        }
        if(jogadas > 7){
            dia();
        }
        system("pause");
        system("cls");
    }
    imprime();
    printf("Você saiu do jogo\n");
    return 0;
}
