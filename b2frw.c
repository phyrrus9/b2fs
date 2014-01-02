//
//  b2frw.c
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "b2frw.h"
#include "b2global.h"
#include "b2fstable.h"

/*
 b2fs_int b2fread(void *data, b2fs_int size, b2file *f);
 void b2fwrite(void *data, b2fs_int size, b2file *f);
 */

b2filenode * b2fsfileseek(b2file *f, b2fs_ulong seek)
{
    FILE *g;
    b2fs_ulong i;
    b2fs_long seekbytes = (sizeof(b2file) * B2FSTBLNUM) + B2FSPADDING;
    b2filenode *node = malloc(sizeof(b2filenode));
    if (f == NULL || (g = fopen(B2DISK, "r")) == NULL || seek == 0)return NULL;
    fseek(g, seekbytes + f->offset, SEEK_SET);
    fread(&node, sizeof(b2filenode), 1, g);
    for (i = 0; i < seek; i++)
    {
        fseek(g, seekbytes + f->offset, SEEK_SET);
        fread(&node, sizeof(b2filenode), 1, g);
    }
    return node;
}

void b2fseek(b2file *f, b2fs_long pos) { f->position = pos; }

b2fs_int b2fread(void *data, b2fs_int size, b2file *f)
{
    FILE *g;
    b2fs_int i;
    b2fs_long seekbytes = (sizeof(b2file) * B2FSTBLNUM) + B2FSPADDING;
    b2filenode node;
    b2fs_ubyte *save = data;
    if (f == NULL || (g = fopen(B2DISK, "r")) == NULL)return 0;
    if (f->position > 0){
        b2filenode *tmpnode = b2fsfileseek(f, f->position);
        node = *tmpnode;
        free(tmpnode);
    } else {
        fseek(g, seekbytes + f->offset, SEEK_SET);
        fread(&node, sizeof(b2filenode), 1, g);
    }
    for (i = 0; i < size; i++)
    {
        save[i] = node.data;
        f->position++;
        if (f->position > f->filesize) break;
        fseek(g, seekbytes + f->offset, SEEK_SET);
        fread(&node, sizeof(b2filenode), 1, g);
    }
    fclose(g);
    return i;
}

void b2fwrite(void *data, b2fs_int size, b2file *f)
{
    FILE *g;
    b2fs_int i;
    b2fs_long seekbytes = (sizeof(b2file) * B2FSTBLNUM) + B2FSPADDING;
    b2filenode node;
    b2filenode newnode;
    b2fs_ubyte *writedata = data;
    if (f == NULL || (g = fopen(B2DISK, "r+")) == NULL) { printf("[b2frw.c] Error, could not open disks\n"); return; }
    if (f->position > 0){
        b2filenode *tmpnode = b2fsfileseek(f, f->position);
        node = *tmpnode;
        free(tmpnode);
    } else {
        fseek(g, seekbytes + f->offset, SEEK_SET);
        fread(&node, sizeof(b2filenode), 1, g);
    }
    for (i = 0; i < size; i++)
    {
        if (f->position > f->filesize)
        {
            f->filesize++;
            newnode.offset = ++b2fscurptr;
            newnode.data = writedata[i];
            fseek(g, newnode.offset + seekbytes, SEEK_SET);
        }
    }
    fclose(g);
}
