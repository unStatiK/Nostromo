#include </usr/include/mysql/mysql.h>
#include "dbwrapper.h"
#include <stdio.h>

void wrinit(struct dbwrapper *dbwrp){
      if(*dbwrp->db_t == 1){
        MYSQL *conn;
        conn = mysql_init(NULL);
        dbwrp->addr_m = conn;
        if (!mysql_real_connect(conn, dbwrp->host,dbwrp->user, dbwrp->pass, dbwrp->db, 0, NULL,0)){
          dbwrp->addr_m = NULL;
        }
      }
}
void wrclose(struct dbwrapper *dbwrp){
      if(*dbwrp->db_t == 1){
        mysql_close((MYSQL *)dbwrp->addr_m);
      }
}

int wrquery_select(struct dbwrapper *dbwrp,char *query){
 if(*dbwrp->db_t == 1)
{
   MYSQL_RES *res;
   MYSQL_ROW row;

   /* send SQL query */
   if (mysql_query((MYSQL *)dbwrp->addr_m, query)) {
      fprintf(stderr, "%s\n", mysql_error((MYSQL *)dbwrp->addr_m));
      return 1;
   }

   res = mysql_use_result((MYSQL *)dbwrp->addr_m);

   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);

   /* close connection */
   mysql_free_result(res);
 }
return 0;
}
 
