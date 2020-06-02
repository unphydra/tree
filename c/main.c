#include "tree.h"

Bool int_predicate(Object a, Object b)
{
  return *(int*)a < *(int*)b;
}

void int_displayer(Object a)
{
  printf("%d\n",*(int*)a);
}

int main(void)
{
  int ar[] = {5,3,8,1,4,7,9};
  Tree_ptr tree = create_tree();
  for (size_t i = 0; i < 7; i++)
  {
    tree = insert_node(tree,&ar[i],int_predicate);
  }
  display_in_order(tree->root, int_displayer);
  return 0;
}
