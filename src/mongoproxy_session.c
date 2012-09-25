/*
 * file   : mongoproxy_session.c
 * author : ning
 * date   : 2012-09-24 00:54:30
 */


#include "mongoproxy.h"

mongoproxy_session_t * mongoproxy_session_new(){
    mongoproxy_session_t * sess;

    sess = malloc(sizeof(*sess));
    if (!sess){
        ERROR("error on malloc");
        return NULL;
    }

    sess->proxy_state = SESSION_STATE_UNSET;
    sess->buf = buffer_new(MONGOPROXY_DEFAULT_BUF_SIZE);
    return sess;
}

void mongoproxy_session_free(mongoproxy_session_t * sess){
    if (!sess) 
        return;
    if (sess->buf){
        buffer_free(sess->buf);
        sess->buf = NULL;
    }
    
    free(sess); 
    sess = NULL;

    return;
}

int mongoproxy_session_close(mongoproxy_session_t * sess){

    return 0;
}

int mongoproxy_session_select_backend(mongoproxy_session_t * sess, int primary){
    if (sess->backend_conn){
        mongo_replset_release_conn(sess->backend_conn);
        sess->backend_conn = NULL;
    }
    mongo_replset_t * replset = &(g_server.replset);
    sess->backend_conn = mongo_replset_get_conn(replset, primary);
    return 0;
}
