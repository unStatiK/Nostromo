struct dbwrapper{
 int *db_t ;
 int addr_m;
 char *host ;
 char *user ;
 char *pass ;
 char *db ;
};

void wrinit(struct dbwrapper *dbwrp);
void wrclose(struct dbwrapper *dbwrp);
int wrquery_select(struct dbwrapper *dbwrp,char *query);
