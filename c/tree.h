#ifndef __TREE_H_
#define __TREE_H_

#include <stdio.h>
#include <stdlib.h>


typedef void * Object;

typedef struct node
{
  Object value;
  struct node * left;
  struct node * right;
} Node;

typedef Node * Node_ptr;

typedef enum {
  False,
  True
} Bool;

typedef Bool (*Predicate_ptr)(Object,Object);
typedef void (*Displayer_ptr)(Object);

Node_ptr create_node(Object);
Node_ptr insert_node(Node_ptr,Object,Predicate_ptr);
void display_in_order(Node_ptr tree, Displayer_ptr displayer);
void display_pre_order(Node_ptr tree, Displayer_ptr displayer);
void display_post_order(Node_ptr tree, Displayer_ptr displayer);

#endif