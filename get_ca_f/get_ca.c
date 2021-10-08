#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
# include  "openssl/bio.h"
# include  "openssl/ssl.h"
# include  "openssl/err.h"
int main( int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("./get_ca <server> <port>.insuficient amount of arguments provided. Please provide Server name and port\n");
        exit(0);
    }
    char* server=argv[1];
    char* port=argv[2];
    SSL *ssl=NULL;
    SSL_CTX *ctx = NULL;
    ctx = SSL_CTX_new(SSLv23_method());
    if(ctx == NULL)
    {
        ERR_print_errors_fp(stdout);
        printf("Connection to server failed.\n");
        SSL_CTX_free(ctx);
        exit(0);
    }
    BIO *bio = BIO_new_ssl_connect(ctx);
    if (bio == NULL)
    {
        ERR_print_errors_fp(stdout);
        printf("Connection to server failed. Please check if correct server address is provided.\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        exit(1);
    }
    BIO_set_conn_hostname(bio, server);
    BIO_set_conn_port(bio, port);
    BIO_get_ssl(bio,&ssl);
    if (ssl == NULL)
    {
        printf ("Cannot connect to server\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }
    int still_connecting = 1;
    while(still_connecting)
    {
        int res = SSL_connect(ssl);
        if (res <= 0)
        {
            unsigned long error = SSL_get_error(ssl, res);
            if ( (error != SSL_ERROR_WANT_CONNECT) && (error != SSL_ERROR_WANT_READ) && (error != SSL_ERROR_WANT_WRITE) )
            {
                printf("Connection to server failed. Please check if correct server address is provided.\n");
                ERR_print_errors_fp(stdout);
                still_connecting = 0;
            }
        }
        else {
            still_connecting = 0;
        }
    }
    STACK_OF(X509) * sk = SSL_get_peer_cert_chain(ssl);
    if(sk == NULL)
    {
        printf ("Could not find certificate chain.\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }
    X509* cert = sk_X509_value(sk,sk_X509_num(sk)-1);
    if(cert == NULL)
    {
        printf("Could not retrieve server certificate from server.\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        exit(1);
    }
    PEM_write_X509(stdout, cert);
    SSL_shutdown(ssl);
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}
