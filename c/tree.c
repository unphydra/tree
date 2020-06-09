#include "tree.h"

Node_ptr create_node(Object value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->b_factor = 0;
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
  return update_node_balance_factor(tree);
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

Node_ptr * get_ptr_of_given_node(Node_ptr * location_ptr, Object value, compare_ptr compare)
{
  Node_ptr * ptr_to_get = location_ptr;
  Inequality status = (*compare)(value,(*ptr_to_get)->value);
  while (status != Equal)
  {
  ptr_to_get = status == Lesser ? &(*ptr_to_get)->left : &(*ptr_to_get)->right;
  status = (*compare)(value,(*ptr_to_get)->value);
  }
  return ptr_to_get;
}

Tree_ptr delete_node(Tree_ptr tree, Object value, compare_ptr compare)
{
  Node_ptr * ptr_to_delete = get_ptr_of_given_node(&tree->root, value, compare);
  Node_ptr *  ptr_to_swap = ptr_to_delete;
  if ((*ptr_to_swap)->right==NULL){
     (*ptr_to_delete) = (*ptr_to_swap)->left;
     return update_node_balance_factor(tree);
  }
  ptr_to_swap = &(*ptr_to_swap)->right;
  while ((*ptr_to_swap)->left!=NULL)
  {
    ptr_to_swap = &(*ptr_to_swap)->left;
  };
  (*ptr_to_delete)->value = (*ptr_to_swap)->value;
  Node_ptr temp = (*ptr_to_swap);
  (*ptr_to_swap) = (*ptr_to_swap)->right;
  free(temp);
  return update_node_balance_factor(tree);
}

Tree_ptr right_rotate_on_given_node(Tree_ptr tree, Node_ptr * node_ptr_to_set)
{
  Node_ptr temp = (*node_ptr_to_set)->left;
  (*node_ptr_to_set)->left = temp->right;
  temp->right = (*node_ptr_to_set);
  (*node_ptr_to_set) = temp;
  return tree;
}

Tree_ptr right_rotate(Tree_ptr tree, Object value, compare_ptr compare)
{
  Node_ptr * ptr_to_set = get_ptr_of_given_node(&tree->root, value, compare);
  if ((*ptr_to_set)->left==NULL) return tree;
  right_rotate_on_given_node(tree,ptr_to_set);
  return update_node_balance_factor(tree);
}

Tree_ptr left_rotate_on_given_node(Tree_ptr tree, Node_ptr * node_ptr_to_set)
{
  Node_ptr temp = (*node_ptr_to_set)->right;
  (*node_ptr_to_set)->right = temp->left;
  temp->left = (*node_ptr_to_set);
  (*node_ptr_to_set) = temp;
  return tree;
}

Tree_ptr left_rotate(Tree_ptr tree, Object value, compare_ptr compare)
{
  Node_ptr * ptr_to_set = get_ptr_of_given_node(&tree->root, value, compare);
  if ((*ptr_to_set)->right==NULL) return tree;
  left_rotate_on_given_node(tree, ptr_to_set);
  return update_node_balance_factor(tree);
}

int get_update_height(Node_ptr node)
{
  if (node==NULL) return 0;
  int left_height = get_update_height(node->left);
  int right_height = get_update_height(node->right);
  node->b_factor = left_height - right_height;
  return (left_height > right_height ? left_height : right_height) + 1;
}

Tree_ptr update_node_balance_factor(Tree_ptr tree)
{
  int left_height = get_update_height(tree->root->left);
  int right_height = get_update_height(tree->root->right);
  tree->root->b_factor = left_height - right_height;
  return tree;
}

Node_ptr * get_unbalanced_node(Node_ptr * node_address)
{
  Node_ptr * ub_node_address = malloc(sizeof(Node_ptr));
  (*ub_node_address) = NULL;
  if ((*node_address)==NULL) return node_address;

  if ((*node_address)->b_factor > 1 || (*node_address)->b_factor < -1)
  {
    ub_node_address = node_address;
  }
  Node_ptr * left = get_unbalanced_node(&((*node_address)->left));
  Node_ptr * right = get_unbalanced_node(&((*node_address)->right));
  return (*left)!=NULL?left:(*right)!=NULL?right:ub_node_address;
}

Tree_ptr left_right_rotate_on_given_node(Tree_ptr tree, Node_ptr * node_ptr_to_set)
{
  left_rotate_on_given_node(tree, &(*node_ptr_to_set)->left);
  return right_rotate_on_given_node(tree, node_ptr_to_set);
}

Tree_ptr right_left_rotate_on_given_node(Tree_ptr tree, Node_ptr * node_ptr_to_set)
{
  right_rotate_on_given_node(tree, &(*node_ptr_to_set)->right);
  return left_rotate_on_given_node(tree, node_ptr_to_set);
}

Tree_ptr balance_tree(Tree_ptr tree)
{
  return tree;
}