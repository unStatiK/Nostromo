struct plugin_list{
  char *name;
  int n_par;
  int p_foo;
//  plugin_list *next;
};

void add_plugin(char *name,int n,int add_f);
int get_plugin(char *data);
void plugin_advizor(char *data);
void init_pl();
