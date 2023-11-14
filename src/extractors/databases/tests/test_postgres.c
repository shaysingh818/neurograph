#include "includes/test_postgres.h"


void test_connection() {
    printf("Testing PG connection"); 
    // pg_connection_t *connect = pg_connect("postgres");
    PGconn *conn; 
    PGresult *res; 
    const char* conninfo; 
    conninfo = "dbname=postgres"; 
    conn = PQconnectdb(conninfo); 

     /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(conn));
        PQfinish(conn);
    }

    /* show tables */
    res = PQexec(conn, "SELECT * FROM pg_catalog.pg_tables");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
    }

    int nFields = PQnfields(res);
    for (int i = 0; i < nFields; i++){
        printf("%-15s", PQfname(res, i));
    }
    printf("\n\n"); 
}
