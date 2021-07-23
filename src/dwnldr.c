/*
 * =====================================================================================
 *
 *       Filename:  dwnldr.c
 *       Created:  07/18/2021 05:38:33 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <curl/curl.h>
#include <openssl/evp.h>

#include "dwnldr.h"
#include "kiwit.h"

dlinfo *dlinfo_new()
{
    dlinfo *dli;

    dli = (dlinfo *)malloc(sizeof(dlinfo));
    if (!dli)
        return NULL;

    memset(dli, 0, sizeof(dlinfo));

    return dli;
}

int dlinfo_set_url(dlinfo *dli, const char *url)
{
    size_t urlen;

    if (!dli || !url)
        return 1;

    free(dli->url);

    urlen = strlen(url);
    dli->url = (char *)malloc(urlen + 1);
    if (!dli->url)
        return 1;

    memset(dli->url, 0, urlen + 1);
    strncpy(dli->url, url, urlen);

    return 0;
}

int dlinfo_set_kiwit(dlinfo *dli, KIWIT *kiwit)
{
    if (!dli || !kiwit)
        return 1;
    
    kiwit_free(dli->kiwit);
    dli->kiwit = kiwit;

    return 0;
}

#if 0
int dlinfo_set_region(dlinfo *dli, Region *reg)
{
    if (!dli || !reg)
        return 1;

    region_free(dli->reg);
    dli->reg = reg;

    return 0;
}
#endif

dlinfo *dlinfo_free(dlinfo *dli)
{
    if (!dli)
        return NULL;
    free(dli->url);
    kiwit_free(dli->kiwit);
    // etc...
    free(dli);

    return NULL;
}

// curl header callback. get size of the file
static size_t
downloadhcb(void *data, size_t size, size_t nmemb, void *userdata)
{
    if (strstr((const char *)data, "content-length"))
        sscanf((const char *)data, "content-length: %d", (size_t *)userdata);
    return size * nmemb;
}

// curl write callback. write data to pipe
static size_t
downloadwcb(void *data, size_t size, size_t nmemb, void *userdata)
{
    int fd = *(int *)userdata;
    size_t sz = size * nmemb;
    write(fd, data, sz);
    return sz;
}

// Thread function: download file
static void *download_file(void *dliptr)
{
    dlinfo *dli = (dlinfo *)dliptr;
    int wfd = dli->wfd;

    CURL *curl;
    CURLcode cres;
    curl = curl_easy_init();
    if (!curl)
        return NULL;
    curl_easy_setopt(curl, CURLOPT_URL, dli->url);
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, downloadhcb);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &dli->filesz);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadwcb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wfd);
    cres = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    // EOF on pipe
    close(wfd);
    pthread_exit(&cres);
    return NULL;
}

// read data from pipe and decrypt it
static void *decrypt_file(void *dliptr)
{
    dlinfo *dli = (dlinfo *)dliptr;
    EVP_CIPHER_CTX *ctx;
    size_t plen;
    int inlen;
    int outlen;
    int fd;

    KIWIT *kiwit = dli->kiwit;

    fd = dli->rfd;
    plen = fcntl(fd, F_GETPIPE_SZ);
    
    int status = 1;
    if(!(ctx = EVP_CIPHER_CTX_new()))
        pthread_exit(&status);
    
    EVP_CIPHER_CTX_init(ctx);
    
    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        pthread_exit(&status);

    if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, NULL))
        pthread_exit(&status);

    if(1 != EVP_DecryptInit_ex(ctx, NULL, NULL, kiwit->key, kiwit->iv))
        pthread_exit(&status);

    uint8_t inbuf[plen];
    uint8_t outbuf[plen + EVP_MAX_BLOCK_LENGTH];

    for(;;){
        inlen = read(fd, inbuf, plen);
        if (inlen <= 0)
            break;
        if (!EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen)){
            EVP_CIPHER_CTX_cleanup(ctx);
            break;
        }
        // write
    }

    // close pipe
    close(fd);

    status = 0;
    pthread_exit(&status);
    return NULL;
}

// download and decrypt file using two threads
int dlinfo_download(dlinfo *dli, pthread_t *doth, pthread_t *deth)
{
    pthread_t   _doth, _deth;
    int pipefds[2];

    if (!dli)
        return 1;

    if (pipe(pipefds) != 0)
        return 1;

    dli->rfd = pipefds[0];
    dli->wfd = pipefds[1];

    if (pthread_create(&_doth, NULL, download_file, dli))
        return 1;
    if (pthread_create(&_deth, NULL, decrypt_file, dli))
        return 1;

    if (doth)
        *doth = _doth;
    if (deth)
        *deth = _deth;

    return 0;
}
