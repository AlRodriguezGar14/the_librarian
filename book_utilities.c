#include "library.h"

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
