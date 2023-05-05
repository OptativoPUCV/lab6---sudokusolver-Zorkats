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
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
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
  int f[10];
  int c[10];
  int matriz[10];

  for(int i = 0; i < 9; i++){
    
    for(int ceros = 0; ceros < 10; ceros++){
      f[ceros] = 0;
      c[ceros] = 0;
      matriz[ceros] = 0;
    }
    
    for(int k = 0; k < 9; k++){
      
      if(n->sudo[i][k] != 0){
        if(f[n->sudo[i][k]] == 1) return 0;
        else f[n->sudo[i][k]] = 1;
      }

      if(n->sudo[k][i] != 0){
        if(c[n->sudo[k][i]] == 1) return 0;
        else c[n->sudo[k][i]] = 1;
      }
      
      int matrizI = 3*(i/3) + (k/3);
      int matrizJ = 3*(i%3) + (k%3);

      if(n->sudo[matrizI][matrizJ] != 0){
        if(matriz[n->sudo[matrizI][matrizJ]] == 1) return 0;
        else matriz[n->sudo[matrizI][matrizJ]] = 1;
      } 
      
    }
    
  }
  
  return 1;
    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
        
      if(n->sudo[i][j] == 0 ){
          
        for(int aux = 1; aux < 10; aux++){
          n->sudo[i][j] = aux;
          Node* nuevoNodo = copy(n);
          if(is_valid(nuevoNodo) == 1){
            pushBack(list,nuevoNodo);
          }
        }
          
      }
        
    }
  }
  return list;
}


int is_final(Node* n){
    for(int i = 0 ; i < 9 ; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0) return 0;
      }  
    }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila,initial);

  while(is_empty(pila) != 1){
    Node* first = top(pila);
    pop(pila);

    if(is_final(first) == 1) return first;
    List* lista = get_adj_nodes(first);
    
    Node* nodes = first(lista);
    while(nodes != NULL){
      push(pila,nodes);
      nodes = next(lista);
    }
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