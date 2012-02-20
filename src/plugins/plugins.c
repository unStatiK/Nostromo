#include "plugins.h"
#include "core_plugin.c"

struct plugin_list pl;

void init_pl(){
//add_plugin("ping",0,&ping_handler);
add_plugin("join",0,&join_handler);
}

void add_plugin(char *name,int n,int add_f){

  pl.name=name;
  pl.n_par=n;
  pl.p_foo=add_f;

//  pl.next;

//(int (*)(void *))(int t);
}

int get_plugin(char *data){
  return pl.p_foo;
}

void plugin_advizor(xmpp_conn_t *conn,xmpp_ctx_t *ctx,char *data){
 void (*i)() = get_plugin(data);
 (*i)(conn,ctx);
}

