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
    for (int i=0; i<9; i++)
    {
        int num[9] = {0};
        for (int j=0; j<9; j++)
        {
            if (n->sudo[i][j] == 0) continue;
            if (num[n->sudo[i][j] - 1] & n->sudo[i][j]) return 0;
            num[n->sudo[i][j] - 1] = n->sudo[i][j];
        }
    }

    for (int j=0; j<9; j++)
    {
        int num[9] = {0};
        for (int i=0; i<9; i++)
        {
            if (n->sudo[i][j] == 0) continue;
            if (num[n->sudo[i][j] - 1] & n->sudo[i][j]) return 0;
            num[n->sudo[i][j] - 1] = n->sudo[i][j];
        }
    }

    for (int k=0; k<9; k++)
    {
        int num[9] = {0};
        for(int p=0;p<9;p++)
        {
            int i=3*(k/3) + (p/3);
            int j=3*(k%3) + (p%3);

            if (num[n->sudo[i][j] - 1] & n->sudo[i][j]) return 0;
            num[n->sudo[i][j] - 1] = n->sudo[i][j];
        }
    }
    return 1;
}
  

List* get_adj_nodes(Node* n){
    List* list=createList();
    for (int i=0; i<9; i++)
    {
        for (int k=0; k<9; k++)
        {
            if (n->sudo[i][k] == 0)
            {
                for (int num=1; num<=9; num++)
                {
                    Node *nCopy = copy(n);
                    nCopy->sudo[i][k] = num;
                    if (!is_valid(nCopy)) continue;
                    pushBack(list, nCopy);
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if (!n->sudo[i][j]) return 0;
        }
    }
    return 1;
}


Node* DFS(Node* initial, int* cont){
    Stack *stack = createStack();
    push(stack, initial);
    *cont = 0;
    Node *node;
    while (top(stack))
    {
        node = top(stack); pop(stack);
        if (is_final(node)) return node;

        List *adyacentes = get_adj_nodes(node);
        Node *adyacente = first(adyacentes);
        while (adyacente)
        {
            push(stack, adyacente);
            adyacente = next(adyacentes);
        }
        free(node);
        (*cont)++;
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