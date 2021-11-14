#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int main(int agrc, char *argv){
    int i, j, l1, c1, l2, c2, aux;
    int player = 1, score1 = 0, score2 = 0, vencedor;
    bool fimJogo = false;
    char visual[6][6];
    char gabarito[6][6]={
        {'a','a','b','b','c','c'},
        {'d','d','e','e','f','f'},
        {'g','g','h','h','i','i'},
        {'j','j','k','k','l','l'},
        {'m','m','n','n','o','o'},
        {'p','p','q','q','r','r'}
    };
    system("color 0f");
    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
            visual[i][j] = ' ';
        }
    }
    srand(time(NULL));
    for(i=0; i<36; i++){
        l1 = rand() % 6;
        c1 = rand() % 6;
        l2 = rand() % 6;
        c2 = rand() % 6;
        aux = gabarito[l2][c2];
        gabarito[l2][c2] = gabarito[l1][c1];
        gabarito[l1][c1] = aux;
    }
    printf("------- JOGO DA MEMORIA -------");
    while(fimJogo == false){
        printf("\n   0    1    2    3    4    5\n");
        for(i=0; i<6; i++){
            printf("%d",i);
            for(j=0; j<6; j++){
                printf(" [%c] ",visual[i][j]);
            }
            printf("\n");
        }
        printf("Jogador %d = %d\tJogador %d = %d\n",1,score1,2,score2);
        printf("[Jogador %d] (linha 1 coluna 1 linha2 coluna2): ",player);
        scanf("%d %d %d %d",&l1,&c1,&l2,&c2);
        if( (l1 >= 0) && (l1<=5) && (c1 >= 0) && (c1<=5) && (l2 >= 0) && (l2<=5) && (c2 >= 0) && (c2<=5) ){
            if((l1 == l2) && (c1 == c2)){
                printf("As coordenadas sao iguais, JOGUE NOVAMENTE\n");
            }else{
                if((visual[l1][c1] == ' ') && (visual[l2][c2] == ' ')){
                    visual[l1][c1] = gabarito[l1][c1];
                    visual[l2][c2] = gabarito[l2][c2];
                    printf("   0    1    2    3    4    5\n");
                    for(i=0; i<6; i++){
                        printf("%d",i);
                        for(j=0; j<6; j++){
                            printf(" [%c] ",visual[i][j]);
                        }
                        printf("\n");
                    }

                    if(gabarito[l1][c1] == gabarito[l2][c2]){
                        printf("Letras iguais\n\n");
                        if(player == 1){
                            score1 = score1+2;
                        }else{
                            score2 = score2+2;
                        }
                    }else{
                        printf("Letras diferentes\n\n");
                        visual[l1][c1] = ' ';
                        visual[l2][c2] = ' ';
                    }

                    if(player == 1){
                        player = 2;
                    }else{
                        player = 1;
                    }
                    if((score1 > 18) || (score2 > 18)){
                        fimJogo = true;
                        if(score1 > 18){
                            vencedor = 1;
                        }else{
                            vencedor = 2;
                        }
                    }

                    if((score1 == 18 ) && (score2 == 18)){
                       fimJogo = true;
                    }

                }else{
                    printf("Coordenada ja aberta, JOGUE NOVAMENTE\n");
                }
            }
        }else{
            printf("Coordenada invalida, JOGUE NOVAMENTE\n");
        }
        system("pause");
        system("cls");
    }

    printf("   0    1    2    3    4    5\n");
    for(i=0; i<6; i++){
        printf("%d",i);
        for(j=0; j<6; j++){
            printf(" [%c] ",visual[i][j]);
        }
        printf("\n");
    }

    printf("\nJogador %d = %d\tJogador %d = %d\n",1,score1,2,score2);
    if((score1 == 18 ) && (score2 == 18)){
        printf("\nO jogo empatou!\n");
    }else{
        printf("\nO Jogador %d ganhou. Parabens!\n", vencedor);
    }

    return 0;
}
