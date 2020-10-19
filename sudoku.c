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
    int i, j, k;
    
    //Linear check
    for (i=0; i<9; i++){
      //Create an array, it saves numbers to compare
      //int * numbers= (int*) malloc(10 * sizeof(int));

      for (j=0; j<9; j++){ 
        if (n->sudo[i][j] == 0) continue;

        for (k=0; k<9; k++){

            if (n->sudo[i][j] == n->sudo[i][k] && j != k){
              return 0;
            }
            if (n->sudo[i][j] == n->sudo[k][j] && i != k){
              return 0;
            }
        }
        k= 3*(i/3) + (j/3);
        for(int p=0;p<9;p++){
            int x= 3*(k/3) + (p/3) ;
            int d= 3*(k%3) + (p%3) ;
            if (n->sudo[i][j] == n->sudo[x][d] && (i!=x && j!=d)){
              return 0;
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
  Stack* S = createStack();
  push(S,initial);
  while (get_size(S) != 0){
  Node * aux  = top(S);
  popFront(S);
  if ((is_final(aux)) == 1) return aux;
  List* adj=get_adj_nodes(aux);
   Node* aux2= first(adj);
     while(aux2 != NULL){
        push(S,aux2);
        aux2=next(adj);
     }
   free(aux);
   *cont = *cont +1;
  } 
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