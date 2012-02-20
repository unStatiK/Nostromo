/* bot.c
** test work bot with libstrophe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/strophe.h"
#include "core/dataheap.h"
#include "core/dbwrapper.h"
#include "core/config.h"
#include "plugins/plugins.h"

struct dbwrapper dbwr;
struct NSTconfig nstr;

void userdata_handler(xmpp_conn_t * const conn,xmpp_ctx_t *ctx,xmpp_stanza_t * const stanza,char const *data){
 int i = -1;
 if(!strcmp(data,"ping")) i=0;
 else if(!strcmp(data,"join")) i=1;
 else if(!strcmp(data,"add"))  i=2;
 else if(!strcmp(data,"exit")) i=3;
  switch(i){
    case 0:{
//       plugin_advizor(conn,ctx,data);

/*        xmpp_stanza_t *reply, *body;
	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "iq");
	xmpp_stanza_set_attribute(reply, "from","nostrome@x-union.org/Bot");
	xmpp_stanza_set_attribute(reply, "to","jabber.org");
	xmpp_stanza_set_attribute(reply, "id","2221");
	xmpp_stanza_set_type(reply, "get");

	body = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(body, "ping");
	xmpp_stanza_set_attribute(body, "xmlns","urn:xmpp:ping");

	xmpp_stanza_add_child(reply, body);
	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	xmpp_stanza_release(body);
*/
        break;
     }
    case 1:{
        plugin_advizor(conn,ctx,data);
        break;
    }
    case 2:{
         
	xmpp_stanza_t *group,*reply, *body, *text;

	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "iq");
	xmpp_stanza_set_type(reply, "set");
	xmpp_stanza_set_id(reply, "set1");

	text = xmpp_stanza_new(ctx);
      	xmpp_stanza_set_name(text,"query");
	xmpp_stanza_set_attribute(text, "xmlns", "jabber:iq:roster");


        body = xmpp_stanza_new(ctx);
        xmpp_stanza_set_name(body, "item");
	xmpp_stanza_set_attribute(body, "jid", "unstatik@x-union.org");
	xmpp_stanza_set_attribute(body, "name", "unStatiK");


	group = xmpp_stanza_new(ctx);
      	xmpp_stanza_set_name(group,"group");
      	xmpp_stanza_set_text(group,"General");


	xmpp_stanza_add_child(body,group);
	xmpp_stanza_add_child(text,body);
	xmpp_stanza_add_child(reply, text);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);


	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "presence");
	xmpp_stanza_set_type(reply, "subscribe");

	xmpp_stanza_set_attribute(reply, "to", "unstatik@x-union.org");

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	xmpp_stanza_release(body);
	xmpp_stanza_release(text);
	xmpp_stanza_release(group);
       
        break;
    }
    case 3:{
	xmpp_stanza_t *reply, *body, *text;
        char *replytext;
	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "message");
	xmpp_stanza_set_type(reply, "chat");
	xmpp_stanza_set_attribute(reply, "to", xmpp_stanza_get_attribute(stanza, "from"));

	body = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(body, "body");

	replytext = malloc(strlen("Bye Admin!")+1);
        strcpy(replytext,"Bye Admin!");

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, replytext);
	xmpp_stanza_add_child(body, text);
	xmpp_stanza_add_child(reply, body);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	free(replytext);

        xmpp_disconnect(conn);
      
        break;
    }
    default:{

	xmpp_stanza_t *reply, *body, *text;
        char *replytext;
     	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "message");
	xmpp_stanza_set_type(reply, "chat");
	xmpp_stanza_set_attribute(reply, "to", xmpp_stanza_get_attribute(stanza, "from"));

	body = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(body, "body");

	replytext = malloc(strlen(" to you too!") + strlen(data) + 1);
	strcpy(replytext, data);
	strcat(replytext, " to you too!");

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, replytext);
	xmpp_stanza_add_child(body, text);
	xmpp_stanza_add_child(reply, body);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	xmpp_stanza_release(body);
	xmpp_stanza_release(text);


	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "message");
	xmpp_stanza_set_type(reply, "groupchat");
//	xmpp_stanza_set_attribute(reply, "from", "nostrome@x-union.org");
	xmpp_stanza_set_attribute(reply, "to", "test@conference.x-union.org");

        body = xmpp_stanza_new(ctx);
        xmpp_stanza_set_name(body, "body");

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, replytext);

	xmpp_stanza_add_child(body,text);
	xmpp_stanza_add_child(reply, body);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);


	free(replytext);

        break;
    }
  }
}


int version_handler(xmpp_conn_t * const conn, xmpp_stanza_t * const stanza, void * const userdata)
{
	xmpp_stanza_t *reply, *query, *name, *version, *text;
	char *ns;
	xmpp_ctx_t *ctx = (xmpp_ctx_t*)userdata;

	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "iq");
	xmpp_stanza_set_type(reply, "result");
	xmpp_stanza_set_id(reply, xmpp_stanza_get_id(stanza));
	xmpp_stanza_set_attribute(reply, "to", xmpp_stanza_get_attribute(stanza, "from"));

	query = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(query, "query");
        ns = xmpp_stanza_get_ns(xmpp_stanza_get_children(stanza));

        if (ns) {
          xmpp_stanza_set_ns(query, ns);
        }

	name = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(name, "name");
	xmpp_stanza_add_child(query, name);

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, "Nostrome bot");
	xmpp_stanza_add_child(name, text);

	version = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(version, "version");
	xmpp_stanza_add_child(query, version);

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, "1.0");
	xmpp_stanza_add_child(version, text);

	xmpp_stanza_add_child(reply, query);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	return 1;
}

int message_handler(xmpp_conn_t * const conn, xmpp_stanza_t * const stanza, void * const userdata)
{
	xmpp_stanza_t *reply, *body, *text;
	char *intext, *replytext;
	xmpp_ctx_t *ctx = (xmpp_ctx_t*)userdata;

	if(!xmpp_stanza_get_child_by_name(stanza, "body")) return 1;
	if(!strcmp(xmpp_stanza_get_attribute(stanza, "type"), "error")) return 1;

	intext = xmpp_stanza_get_text(xmpp_stanza_get_child_by_name(stanza, "body"));

         if(strlen(intext)>=100) return 1;

        if(strcmp(get_jid(xmpp_stanza_get_attribute(stanza,"from")),nstr.admin_jid)) return 1;


        userdata_handler(conn,ctx,stanza,intext);
/*	reply = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(reply, "message");
	xmpp_stanza_set_type(reply, xmpp_stanza_get_type(stanza)?xmpp_stanza_get_type(stanza):"chat");
	xmpp_stanza_set_attribute(reply, "to", xmpp_stanza_get_attribute(stanza, "from"));

	body = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(body, "body");

	replytext = malloc(strlen("ping?? Oh shit~~~~")+1);
        strcpy(replytext,"ping?? Oh shit~~~~");

	text = xmpp_stanza_new(ctx);
	xmpp_stanza_set_text(text, replytext);
	xmpp_stanza_add_child(body, text);
	xmpp_stanza_add_child(reply, body);

	xmpp_send(conn, reply);
	xmpp_stanza_release(reply);
	free(replytext);
*/

	return 1;
}

/* define a handler for connection events */
void conn_handler(xmpp_conn_t * const conn, const xmpp_conn_event_t status,
		  const int error, xmpp_stream_error_t * const stream_error,
		  void * const userdata)
{
    xmpp_ctx_t *ctx = (xmpp_ctx_t *)userdata;

    if (status == XMPP_CONN_CONNECT) {
	xmpp_stanza_t* pres;
	fprintf(stderr, "DEBUG: connected\n");
	xmpp_handler_add(conn,version_handler, "jabber:iq:version", "iq", NULL, ctx);
	xmpp_handler_add(conn,message_handler, NULL, "message", NULL, ctx);

	/* Send initial <presence/> so that we appear online to contacts */
	pres = xmpp_stanza_new(ctx);
	xmpp_stanza_set_name(pres, "presence");
	xmpp_send(conn, pres);
	xmpp_stanza_release(pres);
    }else{
	fprintf(stderr, "DEBUG: disconnected\n");
	xmpp_stop(ctx);
    }
}

int main(int argc, char **argv)
{
    xmpp_ctx_t *ctx;
    xmpp_conn_t *conn;
    xmpp_log_t *log;
    char *jid, *pass;

    /* take a jid and password on the command line */
    if (argc != 3) {
	fprintf(stderr, "Usage: bot <jid> <pass>\n\n");
	return 1;
    }

    jid = argv[1];
    pass = argv[2];
    init_pl();
    config_init(&nstr);

    dbwr.host = nstr.host;
    dbwr.user = nstr.user;
    dbwr.pass = nstr.pass;
    dbwr.db = nstr.db;
    dbwr.db_t = &nstr.db_t;

    wrinit(&dbwr);

    /* init library */
    xmpp_initialize();

    /* create a context */
    log = xmpp_get_default_logger(XMPP_LEVEL_DEBUG); /* pass NULL instead to silence output */
    ctx = xmpp_ctx_new(NULL, log);

    /* create a connection */
    conn = xmpp_conn_new(ctx);

    /* setup authentication information */
    xmpp_conn_set_jid(conn, jid);
    xmpp_conn_set_pass(conn, pass);

    /* initiate connection */
    xmpp_connect_client(conn, NULL, 0, conn_handler, ctx);

    /* enter the event loop -
       our connect handler will trigger an exit */
    xmpp_run(ctx);

    wrclose(&dbwr);

    /* release our connection and context */
    xmpp_conn_release(conn);
    xmpp_ctx_free(ctx);

    /* final shutdown of the library */
    xmpp_shutdown();

    return 0;
}
