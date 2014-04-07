#include <stdio.h>
#include "mongo.h"

static void find_actor_movies( mongo *conn, char *name ) {
  // Print out the name of an actor and all of that actor's movies
  // conn: mongo connection
  // name: actor name
  bson query[1];
  mongo_cursor cursor[1];

  bson_init( query );
  bson_append_string( query, "name", name );
  bson_finish( query );

  mongo_cursor_init( cursor, conn, "makinbacon.actors" );
  mongo_cursor_set_query( cursor, query );

  while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    bson_iterator iterator[1];
    bson_iterator sub[1];
    if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
        printf( "name: %s\n", bson_iterator_string( iterator ) );
    }
    if ( bson_find( iterator, mongo_cursor_bson( cursor ), "movies" )) {
        bson_iterator_subiterator( iterator, sub );
        while( bson_iterator_next( sub ) ){
          printf( "movie: %s\n", bson_iterator_string( sub ) );
        }
    }
  }

  bson_destroy( query );
  mongo_cursor_destroy( cursor );
}

int main() {
  // Connect to mongo, then search for one actor's movies.
  mongo conn[1];
  int status = mongo_client( conn, "127.0.0.1", 27017 );

  if( status != MONGO_OK ) {
      switch ( conn->err ) {
        case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
        case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
        case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
      }
  }

  char *actor = "Urban, Karl";
  find_actor_movies(conn, actor);

  mongo_destroy( conn );

  return 0;
}