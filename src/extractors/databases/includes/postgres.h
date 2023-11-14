#ifndef POSTGRES_H
#define POSTGRES_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>
#include <postgresql/libpq-fe.h>

struct PostgresConnection {
    int num_fields, i, j; 
    char *conninfo; 
    PGconn *conn; 
    PGresult *res; 
}; 

typedef struct PostgresConnection pg_connection_t; 

/* connect to db */
pg_connection_t *pg_connect(char *db_name); 

#endif