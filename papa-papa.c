// Nome : Jorge Christino dos Santos Ferreira
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
   int i, j, nj, na, alimento, cont, a, b;
   char tab[9][9];
   srand(time(NULL));

   // inicializando tabuleiro
   printf("BEM VINDO AO JOGO PAPA-PAPA!!!\n");
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
            tab[i][j]= ' ';
        }
   }
   tab[4][4] = 'O';
   cont = 1;

   //sorteio das comidas
   while(cont <= 40){
      i = rand() % 9;
      j = rand() % 9;
      if ((i == 4) && (j == 4)){
         cont--;
      }else{
         if (tab[i][j] == '-'){
            cont--;
         }else{
            tab[i][j] = '-';
         }
      }
      cont++;
   }

   na = 0;
   alimento = 1;

   //inicio do jogo
   for(nj=1;nj<=65;nj++){
      printf("  0  1  2  3  4  5  6  7  8\n");
      for(i=0;i<9;i++){
         printf("%d",i);
         for(j=0;j<9;j++){
            printf("[%c]",tab[i][j]);
            if(tab[i][j] == 'O'){
               a = i;
               b = j;
            }
         }
         printf("\n");
      }
      printf("\n");
      printf("Jogada: %d\tAlimento: %d\n",nj,alimento);
      printf("[Linha Coluna]: ");
      scanf("%d %d",&i,&j);

      //movimentacao do comilao
      if((i>=0) && (i<9) && (j>=0) && (j<9)){
         if((i==a-1) && (j==b) || (i==a) && (j==b-1) || (i==a) && (j==b+1) || (i==a+1) && (j==b)){
            if(tab[i][j]=='-'){
               tab[i][j]='O';
               tab[a][b]=' ';
               alimento++;
               na++;
            }else{
               tab[i][j]='O';
               tab[a][b]=' ';
               alimento--;
            }
         }else{
            printf("\nSalto invalido\n");
            nj--;
         }
      }else{
         printf("\nSalto invalido\n");
         nj--;
      }

      //condiçoes de vitoria
      if ((alimento == 0) || (nj == 65) && (na != 40)){
         system("cls");
         printf("\n");
         printf("  0  1  2  3  4  5  6  7  8\n");
         for(i=0;i<9;i++){
            printf("%d",i);
            for(j=0;j<9;j++){
               printf("[%c]",tab[i][j]);
            }
            printf("\n");
         }
         printf("\nJogada: %d\tAlimento: %d\n",nj,alimento);
         printf("\nVOCE PERDEU!\n");
         break;
         }else{
         if(na == 40){
            system("cls");
            printf("\n");
            printf("  0  1  2  3  4  5  6  7  8\n");
            for(i=0;i<9;i++){
               printf("%d",i);
               for(j=0;j<9;j++){
                  printf("[%c]",tab[i][j]);
               }
               printf("\n");
            }
            printf("\nJogada: %d\tAlimento: %d\n",nj,alimento);
            printf("\nPARABENS, VOCE GANHOU!\n");
            break;
         }
      }
      system("pause");
      system("cls");
   }
   return 0;
}
