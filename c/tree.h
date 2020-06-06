#ifndef __TREE_H_
#define __TREE_H_

#include <stdio.h>
#include <stdlib.h>


typedef void * Object;

typedef struct node
{
  Object value;
  int b_factor;
  struct node * left;
  struct node * right;
} Node;

typedef Node * Node_ptr;

typedef enum {
  False,
  True
} Bool;

typedef struct
{
  Node_ptr root;
} Tree;

typedef Tree * Tree_ptr;

typedef Bool (*Predicate_ptr)(Object,Object);
typedef void (*Displayer_ptr)(Object);

typedef enum
{
  Equal,
  Lesser,
  Greater
} Inequality;

typedef Inequality (*compare_ptr)(Object,Object);

Node_ptr create_node(Object);
Tree_ptr create_tree(void);
Tree_ptr insert_node(Tree_ptr,Object,Predicate_ptr);
Tree_ptr delete_node(Tree_ptr, Object, compare_ptr);
Tree_ptr right_rotate(Tree_ptr, Object, compare_ptr);
Tree_ptr left_rotate(Tree_ptr, Object, compare_ptr);
Tree_ptr update_node_balance_factor(Tree_ptr);

Node_ptr * get_ptr_of_given_node(Node_ptr *, Object, compare_ptr);

void display_in_order(Node_ptr, Displayer_ptr);
void display_pre_order(Node_ptr, Displayer_ptr);
void display_post_order(Node_ptr, Displayer_ptr);

#endif