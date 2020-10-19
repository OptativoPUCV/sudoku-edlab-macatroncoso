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
  int i,j,purru,iwi,owo;
 for (i=0; i<9; i++){
   for (j=0; j<9; j++){ 
   if (n->sudo[i][j] == 0) continue;
 purru= 3*(i/3) + (j/3);
 for(int p=0;p<9;p++){
    owo= 3*(purru%3) + (p%3);
        iwi= 3*(purru/3) + (p/3);
   if ((i!=iwi && j!=owo) && n->sudo[i][j] == (n->sudo[iwi][owo])) return 0;}
   for (purru=0; purru<9; purru++){
      if (n->sudo[i][j] == n->sudo[purru][j] && i!=purru) return 0;
      if (n->sudo[i][j] == n->sudo[i][purru] && j!=purru) return 0;
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
          n->sudo[i][j] = k;
          if (is_valid(n)){
          Node * neuwu = copy(n);
          pushBack(list, neuwu);
          }
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
  pop(S);
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