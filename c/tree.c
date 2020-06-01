#include "tree.h"

Node_ptr create_node(Object value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

Node_ptr insert_node(Node_ptr tree, Object value, Predicate_ptr predicate)
{
  if (tree == NULL) return create_node(value);
  
  Node_ptr * ptr_to_set = &tree;
  while ((*ptr_to_set) != NULL)
  {
    if ((*predicate)(value,(*ptr_to_set)->value))
    {
      ptr_to_set = &(*ptr_to_set)->left;
    } else
    {
      ptr_to_set = &(*ptr_to_set)->right;
    }
  }
      (*ptr_to_set) = create_node(value);
      return tree;
}

void display_in_order(Node_ptr tree, Displayer_ptr displayer)
{
  if (tree!=NULL)
  {
    display_in_order(tree->left, displayer);
    (*displayer)(tree->value);
    display_in_order(tree->right, displayer);
  }
}

void display_pre_order(Node_ptr tree, Displayer_ptr displayer)
{
  if (tree!=NULL)
  {
    (*displayer)(tree->value);
    display_pre_order(tree->left, displayer);
    display_pre_order(tree->right, displayer);
  }
}

void display_post_order(Node_ptr tree, Displayer_ptr displayer)
{
  if (tree!=NULL)
  {
    display_post_order(tree->left, displayer);
    display_post_order(tree->right, displayer);
    (*displayer)(tree->value);
  }
}