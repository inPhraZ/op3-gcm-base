/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2021 06:15:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>

#include "dwnldr.h"
#include "region.h"

#define REGSIZE     (10 * 1024 * 1024)
uint8_t key[32] = {
    0x5d, 0x0c, 0xea, 0x25,
    0x96, 0xb3, 0x88, 0xa0,
    0xbe, 0xec, 0x27, 0x48,
    0x35, 0x9a, 0x19, 0x78,
    0x69, 0x8e, 0xed, 0x3c,
    0x8f, 0x3a, 0xd1, 0x3e,
    0x90, 0xc8, 0xf9, 0xf6,
    0x7e, 0x25, 0x0a, 0xd5
};

uint8_t iv[16] = {
    0x3a, 0x16, 0xe3, 0x07,
    0x44, 0x7c, 0x66, 0x52,
    0x87, 0x08, 0x2a, 0x0c,
    0x8f, 0xed, 0x8a, 0xfa
};

int main(int argc, char **argv)
{
    dlinfo *dli = dlinfo_new();
    KIWIT *kiwit = kiwit_new(key, iv);
    Region *reg = region_new(REGSIZE);

    if (argc < 2) {
        printf("Usage: %s url-to-gcm-mp3\n");
        printf("key and iv in the source are for a test file\n");
        return 1;
    }

    dlinfo_set_url(dli, argv[1]);
    dlinfo_set_kiwit(dli, kiwit);
    dlinfo_set_region(dli, reg);
    pthread_t t1, t2;
    dlinfo_download(dli, &t1, &t2);

    printf("Wait for threads to terminate...\n");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Threads are done\n");

    FILE *fp = fopen("a.mp3", "w");
    if (!fp) {
        perror("fopen");
        dlinfo_free(dli);
        return 1;
    }

    char *buf = (char *)malloc(dli->filesz);
    printf("copy data from memory in the buffer\n");
    region_read(dli->reg, buf, dli->filesz);
    printf("copy data from buffer in the file\n");
    fwrite(buf, 1, dli->filesz, fp);
    fclose(fp);
    dlinfo_free(dli);

    return 0;

}
