#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
  if (root == NULL)
    return create_tree_node (title, author, year);

  int comparison = strcmp (title, root->book->title);
  if (comparison == 0)
    return root;
  if (comparison < 0)
    root->left = insert_book (root->left, title, author, year);
  if (comparison > 0)
    root->right = insert_book (root->right, title, author, year);

  return root;
}

int
main (void)
{
  // Library *library = calloc (sizeof (Library), 1);
  Library library = {0};

  library.entry_point
    = insert_book (library.entry_point, "bca", "someone", 2024);

  library.entry_point
    = insert_book (library.entry_point, "abc", "someone2", 2024);

  library.entry_point
    = insert_book (library.entry_point, "bac", "someone3", 2024);

  print_library (library.entry_point);
  free_library (library.entry_point);

  return 1;
}
