#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    GHashTable *d = g_hash_table_new(NULL, NULL);
    int josh = 1;
    g_hash_table_insert(d,"Josh",&josh);
    josh = *(int *)g_hash_table_lookup(d,"Josh");
    printf("%i\n", josh);
    return 0;
}