#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Takes a hash table and key and 
// returns 1 more than the current 
// value associated with that key
int* get_next_count(GHashTable *d, gpointer key){
    int* count = malloc(sizeof(int *));
    if (g_hash_table_contains(d, key))
    {
        *count = *(int *)g_hash_table_lookup(d, key) + 1;
    }
    else{
        *count = 1;
    }
    return count;
}

// Takes a key, value, and dummy var, prints the key value pair
void print_pair(gpointer key, gpointer val, gpointer data){
    printf("word:%s\tfreq:%i\n", (char *)key, *(int *)val);
}

// Prints all the key value pairs in hashtable d
void print_words(GHashTable *d){
    g_hash_table_foreach(d, print_pair, NULL);
}

// Makes a hashtable mapping all words in a text file, then prints them.
int main(int argc, char const *argv[])
{
    GHashTable *word_map = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    GIOChannel *channel = g_io_channel_new_file("merchantofvenice.txt","r",NULL);
    gchar *text = NULL;
    gsize len = 0;
    g_io_channel_read_to_end(channel, &text, &len, NULL);
    gchar** words = g_strsplit_set(text, " \n\t,./:;'\"+-_`~1234567890!@#$%^&*()=+<>?", 0);
    int i;
    int *count;
    for (i=0; words[i]; i++){
        if (strcmp(words[i],"") != 0)
        {
            count = get_next_count(word_map, (gpointer)words[i]);
            g_hash_table_replace(word_map, (gpointer)g_ascii_strdown(words[i],-1), (gpointer)count);
        }
        free(words[i]);
    }
    free(words);
    free(text);
    free(channel);
    print_words(word_map);
    g_hash_table_destroy(word_map);

    return 0;
}

// I had fun fixing memory leaks, and valgrind is saying that
// I definitely lost only 6 bytes, and possibly lost 4032. I can't
// find those, but I feel like they might be GLib's fault, or just something I missed.