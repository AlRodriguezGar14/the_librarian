#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/* Book */

typedef struct Book
{
  char *title;
  char *author;
  uint16_t publication_year;
} Book;

char *
ft_strdup (const char *source, size_t source_length)
{
  char *duplicate = malloc ((source_length + 1) * sizeof (char));
  if (duplicate == NULL)
  {
    fprintf (stderr, "Could not duplicate '%s'\n", source);
    return NULL;
  }
  strncpy (duplicate, source, source_length);
  duplicate[source_length] = '\0';

  return duplicate;
}

void
free_book (Book *book)
{
  if (book == NULL)
    return;

  if (book->title)
    free (book->title);
  if (book->author)
    free (book->author);
  free (book);
}

Book *
create_book (const char *title, const char *author,
             const uint16_t publication_year)
{
  if (title == NULL || author == NULL)
  {
    fprintf (stderr, "Title or author cannot be NULL\n");
    return NULL;
  }
  Book *new_book = malloc (sizeof (Book));
  if (new_book == NULL)
  {
    fprintf (stderr, "Could not allocate memory for a new book\n");
    return NULL;
  }
  size_t title_length = strlen (title);
  size_t author_length = strlen (author);

  new_book->title = ft_strdup (title, title_length);
  if (new_book->title == NULL)
  {
    fprintf (stderr, "Could not allocate memory for the title\n");
    free_book (new_book);
    return NULL;
  }
  new_book->author = ft_strdup (author, author_length);
  if (new_book->title == NULL)
  {
    fprintf (stderr, "Could not allocate memory for the author\n");
    free_book (new_book);
    return NULL;
  }
  new_book->publication_year = publication_year;

  return new_book;
}

/* Library - bst (Potentially upgrade it to red-black tree once it's working)*/
typedef struct TreeNode
{
  Book *book;
  struct TreeNode *left;
  struct TreeNode *right;

} TreeNode;

typedef struct
{
  TreeNode *entry_point;
} Library;

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
print_library (TreeNode *root)
{
  if (root == NULL)
    return;
  print_library (root->left);
  printf ("Title: %s\n\tAuthor: %s\n\tPublication year: %d\n",
          root->book->title, root->book->author, root->book->publication_year);
  print_library (root->right);
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
insert_book (TreeNode *root, const char *title, const char *author,
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
    root->left = insert_book (root->left, title, author, year);
  if (comparison > 0)
    root->right = insert_book (root->right, title, author, year);

  return root;
}

TreeNode *
find_book (TreeNode *root, const char *title)
{
  if (root == NULL)
    return NULL;

  int comparison = strcmp (title, root->book->title);
  if (comparison < 0)
    return find_book (root->left, title);
  if (comparison > 0)
    return find_book (root->right, title);

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

/* TESTS */

void
test_create_book ()
{
  puts ("Testing create_book...");
  Book *book = create_book ("Test Title", "Test Author", 2022);
  assert (strcmp (book->title, "Test Title") == 0);
  assert (strcmp (book->author, "Test Author") == 0);
  assert (book->publication_year == 2022);
  puts ("create_book passed\n");
  free_book (book);
}

void
test_insert_and_find_book ()
{
  puts ("Testing insert_book and find_book...");
  TreeNode *root = NULL;
  root = insert_book (root, "Test Title", "Test Author", 2022);
  puts ("Library after inserting a book:");
  print_library (root);
  TreeNode *found = find_book (root, "Test Title");
  assert (found != NULL);
  assert (strcmp (found->book->title, "Test Title") == 0);
  assert (strcmp (found->book->author, "Test Author") == 0);
  assert (found->book->publication_year == 2022);
  puts ("insert_book and find_book passed\n");
  free_library (root);
}

void
test_remove_book ()
{
  puts ("Testing remove_book...");
  TreeNode *root = NULL;
  root = insert_book (root, "Test Title", "Test Author", 2022);
  puts ("Library before removing a book:\n");
  print_library (root);
  root = remove_book (root, "Test Title");
  puts ("Library after removing a book:");
  print_library (root);
  TreeNode *found = find_book (root, "Test Title");
  assert (found == NULL);
  puts ("remove_book passed\n");
  free_library (root);
}

void
test_edge_cases ()
{
  puts ("Testing edge cases...");
  Book *book = create_book (NULL, NULL, 0);
  assert (book == NULL);
  TreeNode *root = insert_book (NULL, NULL, NULL, 0);
  assert (root == NULL);
  TreeNode *found = find_book (root, NULL);
  assert (found == NULL);
  root = remove_book (root, NULL);
  assert (root == NULL);
  puts ("Edge cases test passed.\n");
}

int
main ()
{
  test_create_book ();
  test_insert_and_find_book ();
  test_remove_book ();
  test_edge_cases ();
  return 0;
}
