#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Book
{
  char *title;
  char *author;
  uint16_t publication_year;
} Book;

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

/* Book */
char *
ft_strdup (const char *source, size_t source_length);

void
free_book (Book *book);

Book *
create_book (const char *title, const char *author,
             const uint16_t publication_year);

/* Librarian */
void
free_library (TreeNode *root);

void
list_books (TreeNode *root);

TreeNode *
create_tree_node (const char *title, const char *author, const uint16_t year);

TreeNode *
add_book (TreeNode *root, const char *title, const char *author,
             const uint16_t year);

TreeNode *
search_book (TreeNode *root, const char *title);

TreeNode *
find_minimum_node (TreeNode *root);

TreeNode *
remove_book (TreeNode *root, const char *title);

/* Tests */
void
test_create_book ();

void
test_insert_and_search_book ();

void
test_remove_book ();

void
test_edge_cases ();
