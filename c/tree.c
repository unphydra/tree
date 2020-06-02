#include "tree.h"

Node_ptr create_node(Object value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

Tree_ptr create_tree(void)
{
  Tree_ptr tree = malloc(sizeof(Tree));
  tree->root = NULL;
  return tree;
}

Tree_ptr insert_node(Tree_ptr tree, Object value, Predicate_ptr predicate)
{
  Node_ptr * ptr_to_set = &tree->root;
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

void display_in_order(Node_ptr node, Displayer_ptr displayer)
{
  if (node!=NULL)
  {
    display_in_order(node->left, displayer);
    (*displayer)(node->value);
    display_in_order(node->right, displayer);
  }
}

void display_pre_order(Node_ptr node, Displayer_ptr displayer)
{
  if (node!=NULL)
  {
    (*displayer)(node->value);
    display_pre_order(node->left, displayer);
    display_pre_order(node->right, displayer);
  }
}

void display_post_order(Node_ptr node, Displayer_ptr displayer)
{
  if (node!=NULL)
  {
    display_post_order(node->left, displayer);
    display_post_order(node->right, displayer);
    (*displayer)(node->value);
  }
}