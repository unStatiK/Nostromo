#include "config.h"
#include <stdlib.h>
#include <string.h>

void config_init(struct NSTconfig *nst){

/*** To do : implement parsing config file and change it **/
  int size;

  nst->db_t = 1;

  size = strlen("unstatik@x-union.org");
  nst->admin_jid = malloc(size+1);
  strcpy(nst->admin_jid,"unstatik@x-union.org");
  nst->admin_jid[size]= '\0';

  size = strlen("mangos");
  nst->user = malloc(size+1);
  strcpy(nst->user,"mangos");
  nst->user[size]= '\0';

  size = strlen("cat_mangos1666++");
  nst->pass = malloc(size+1);
  strcpy(nst->pass,"cat_mangos1666++");
  nst->pass[size]= '\0';

  size = strlen("realmd");
  nst->db = malloc(size+1);
  strcpy(nst->db,"realmd");
  nst->db[size]= '\0';
/*********************************************************/

}
