#include "io/parser_utils.h"
#include <assert.h>

void discard_rest_of_line(FILE *file)
{
    assert(file != NULL);

    int ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF)
    {
    }
}
