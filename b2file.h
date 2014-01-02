//
//  b2file.h
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef bf2s_b2file_h
#define bf2s_b2file_h

#include "types.h"

struct s_b2fs_b2file_node
{
    b2fs_ulong offset; //tablesize + paddingsize + offset
    b2fs_ubyte data;
};

struct s_b2fs_b2file
{
    char filename[30];
    unsigned char uid;
    unsigned char gid;
    b2fs_uint permissions;
    b2fs_ulong filesize;
    b2fs_ulong position;
    b2fs_ulong offset;
};

typedef struct s_b2fs_b2file b2file;
typedef struct s_b2fs_b2file_node b2filenode;

#endif
