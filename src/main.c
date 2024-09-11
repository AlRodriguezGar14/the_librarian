#include "../includes/library.h"

int
main (void)
{
  test_create_book ();
  test_insert_and_search_book ();
  test_remove_book ();
  test_edge_cases ();
  return 0;
}
