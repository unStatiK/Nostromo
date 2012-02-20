#include <stdio.h>
void ping_handler( /*char **args*/){
   printf("\nPING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
} 
void join_handler( xmpp_conn_t * const conn,xmpp_ctx_t *ctx /*char **args*/){

        xmpp_stanza_t *reply, *body;
        reply = xmpp_stanza_new(ctx);
        xmpp_stanza_set_name(reply, "presence");
        xmpp_stanza_set_attribute(reply, "to", "test@conference.x-union.org/Nostrome");

        body = xmpp_stanza_new(ctx);
        xmpp_stanza_set_name(body, "x");
        xmpp_stanza_set_attribute(body, "xmlns", "http://jabber.org/protocol/muc");


        xmpp_stanza_add_child(reply,body);

        xmpp_send(conn, reply);
        xmpp_stanza_release(reply);
        xmpp_stanza_release(body);

}
