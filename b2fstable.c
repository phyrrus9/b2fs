//
//  b2fstable.c
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b2fstable.h"

/*
 static b2file b2fstable[B2FSTBLNUM];
 void b2fstbl_init();
 void b2fstbl_update(b2file *data);
 b2file *b2fstbl_get(char *filename);
 void b2fstbl_write();
*/

void b2fstbl_init()
{
    FILE *f;
    b2fs_int i;
    if ((f = fopen(B2DISK, "r")) == NULL){ printf("[b2fstable.c] Error opening disk\n"); return; }
    fseek(f, 0L, SEEK_SET);
    fread(&b2fscurptr, sizeof(b2fs_uint), 1, f);
    for (i = 0; i < B2FSTBLNUM; i++)
        fread(&b2fstable[i], sizeof(b2file), 1, f);
    fclose(f);
}

void b2fstbl_update(b2file *data)
{
    b2fs_int i;
    for (i = 0; i < B2FSTBLNUM; i++)
        if (strcmp(b2fstable[i].filename, data->filename) == 0)
            b2fstable[i] = *data;
    b2fstbl_write();
}

void b2fstbl_write()
{
    FILE *f;
    b2fs_int i;
    if ((f = fopen(B2DISK, "r+")) == NULL){ printf("[b2fstable.c] Error opening disk\n"); return; }
    fseek(f, 0L, SEEK_SET);
    fwrite(&b2fscurptr, sizeof(b2fs_uint), 1, f);
    for (i = 0; i < B2FSTBLNUM; i++)
        fwrite(&b2fstable[i], sizeof(b2file), 1, f);
    fclose(f);
}

b2file *b2fstbl_get(char *filename)
{
    FILE *f;
    b2file *ret = NULL;
    b2file *src = NULL;
    b2fs_int i;
    if ((f = fopen(B2DISK, "r")) == NULL) return NULL;
    for (i = 0; i < B2FSTBLNUM; i++)
    {
        fread(src, sizeof(b2file), 1, f);
        if (strcmp(filename, src->filename) == 0)
        {
            ret = src;
            break;
        }
    }
    fclose(f);
    if (ret == NULL) //create it if not exist
    {
        ret = malloc(sizeof(b2file));
        strcpy(ret->filename, filename);
        ret->filesize = 0;
        ret->offset = ++b2fscurptr;
        b2fstbl_update(ret);
    }
    ret->position = 0;
    return ret;
}
