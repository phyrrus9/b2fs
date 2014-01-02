//
//  b2fstable.h
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef bf2s_b2fstable_h
#define bf2s_b2fstable_h

#include "types.h"
#include "b2file.h"
#include "b2global.h"

static b2file b2fstable[B2FSTBLNUM];
static b2fs_uint b2fscurptr;
void b2fstbl_init();
void b2fstbl_update(b2file *data);
b2file *b2fstbl_get(char *filename);
void b2fstbl_write();

#endif
