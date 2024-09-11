#include "library.h"

void
free_library (TreeNode *root)
{
  if (root == NULL)
    return;

  free_library (root->left);
  free_library (root->right);
  free_book (root->book);
  free (root);
}

void
list_books (TreeNode *root)
{
  if (root == NULL)
    return;
  list_books (root->left);
  printf ("Title: %s\n\tAuthor: %s\n\tPublication year: %d\n",
          root->book->title, root->book->author, root->book->publication_year);
  list_books (root->right);
}

TreeNode *
create_tree_node (const char *title, const char *author, const uint16_t year)
{
  TreeNode *new_node = malloc (sizeof (TreeNode));
  if (new_node == NULL)
  {
    fprintf (stderr, "Could not allocate memory for a new tree node\n");
    return NULL;
  }
  new_node->book = create_book (title, author, year);
  if (new_node == NULL)
    return NULL;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

TreeNode *
add_book (TreeNode *root, const char *title, const char *author,
          const uint16_t year)
{
  if (title == NULL || author == NULL)
  {
    fprintf (stderr, "Title or author cannot be NULL\n");
    return NULL;
  }
  if (root == NULL)
    return create_tree_node (title, author, year);

  int comparison = strcmp (title, root->book->title);
  if (comparison < 0)
    root->left = add_book (root->left, title, author, year);
  if (comparison > 0)
    root->right = add_book (root->right, title, author, year);

  return root;
}

TreeNode *
search_book (TreeNode *root, const char *title)
{
  if (root == NULL)
    return NULL;

  int comparison = strcmp (title, root->book->title);
  if (comparison < 0)
    return search_book (root->left, title);
  if (comparison > 0)
    return search_book (root->right, title);

  return root;
}

TreeNode *
find_minimum_node (TreeNode *root)
{
  TreeNode *current = root;
  while (current && current->left)
    current = current->left;
  return current;
}

TreeNode *
remove_book (TreeNode *root, const char *title)
{
  if (title == NULL || root == NULL)
    return NULL;

  int comparison = strcmp (title, root->book->title);
  if (comparison < 0)
    root->left = remove_book (root->left, title);
  else if (comparison > 0)
    root->right = remove_book (root->right, title);
  else
  {
    if (root->left == NULL)
    {
      TreeNode *tmp = root->right;
      free_book (root->book);
      free (root);
      return tmp;
    }
    else if (root->right == NULL)
    {
      TreeNode *tmp = root->left;
      free_book (root->book);
      free (root);
      return tmp;
    }
    TreeNode *tmp = find_minimum_node (root->right);
    free_book (root->book);
    root->book = tmp->book;
    root->right = remove_book (root->right, tmp->book->title);
  }

  return root;
}
