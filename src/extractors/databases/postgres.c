#include "includes/postgres.h"


pg_connection_t *pg_connect(char *db_name) {
    pg_connection_t *connection = malloc(sizeof(pg_connection_t));
    char *conninfo; 
    sprintf(conninfo, "dbnname=%s", db_name); 
    connection->conninfo = malloc(strlen(conninfo)+1 * sizeof(char));
    strcpy(connection->conninfo, conninfo); 
    return connection; 
}