#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "library.h"

int
main ()
{
  test_create_book ();
  test_insert_and_search_book ();
  test_remove_book ();
  test_edge_cases ();
  return 0;
}
