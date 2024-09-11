#include "../../includes/library.h"

void
test_create_book (void)
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
test_insert_and_search_book (void)
{
  puts ("Testing add_book and search_book...");
  TreeNode *root = NULL;
  root = add_book (root, "Test Title", "Test Author", 2022);
  puts ("Library after inserting a book:");
  list_books (root);
  TreeNode *found = search_book (root, "Test Title");
  assert (found != NULL);
  assert (strcmp (found->book->title, "Test Title") == 0);
  assert (strcmp (found->book->author, "Test Author") == 0);
  assert (found->book->publication_year == 2022);
  puts ("add_book and search_book passed\n");
  free_library (root);
}

void
test_remove_book (void)
{
  puts ("Testing remove_book...");
  TreeNode *root = NULL;
  root = add_book (root, "Test Title", "Test Author", 2022);
  puts ("Library before removing a book:\n");
  list_books (root);
  root = remove_book (root, "Test Title");
  puts ("Library after removing a book:");
  list_books (root);
  TreeNode *found = search_book (root, "Test Title");
  assert (found == NULL);
  puts ("remove_book passed\n");
  free_library (root);
}

void
test_edge_cases (void)
{
  puts ("Testing edge cases...");
  Book *book = create_book (NULL, NULL, 0);
  assert (book == NULL);
  TreeNode *root = add_book (NULL, NULL, NULL, 0);
  assert (root == NULL);
  TreeNode *found = search_book (root, NULL);
  assert (found == NULL);
  root = remove_book (root, NULL);
  assert (root == NULL);
  puts ("Edge cases test passed.\n");
}
