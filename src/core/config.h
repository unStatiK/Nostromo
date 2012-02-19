struct NSTconfig{
  int db_t;
  char *admin_jid;
  char *host ;
  char *user ;
  char *pass ;
  char *db ;
};
void config_init(struct NSTconfig *nst);
