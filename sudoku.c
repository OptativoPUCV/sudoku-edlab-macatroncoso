#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
int i,j,x,y,k;
    for ( i = 0 ; i < 9 ; i+=3){
        for ( j = 0 ; j < 9 ; j+=3){ 
         if (n->sudo[i][j] == n->sudo[i][j+1])  return 0;
            for ( x = i ; x < i + 3 ; x++){
                for ( y = j ; y < j + 3 ; y++){
                  if(n->sudo[x][y]){
                    for (k = 0 ; k < 9 ; k++){ //revisa horizontal
                     if (n->sudo[i][j] == n->sudo[x][y+1]) return 0;
                    for(k = 0 ; k < 9 ; k++){ //revisa vertical
                      if (n->sudo[j][i] == n->sudo[y][x+1])  return 0;
                     }
                    }
                  }  
              }
             }
         }
     }
  return 1;
}


List* get_adj_nodes(Node* n){
List* list=createList();
   int i,j,k; 
   for(i=0;i<9;i++){
     for(j=0;j<9;j++){
       if(n->sudo[i][j] == 0){
         for ( k = 1 ; k <=9 ; k++){
          Node * adj_n = createNode();
          *adj_n = *n;
          adj_n->sudo[i][j] = k;
          pushBack(list, adj_n);
          }
       }
   }
}
  return list;
}


int is_final(Node* n){
  int i,j; 
   for(i=0;i<9;i++){
     for(j=0;j<9;j++){
       if(n->sudo[i][j] == 0){
        return 0;
          }
       }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont){

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/