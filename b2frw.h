//
//  b2frw.h
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef bf2s_b2frw_h
#define bf2s_b2frw_h

#include "types.h"
#include "b2file.h"

b2fs_int b2fread(void *data, b2fs_int size, b2file *f);
void b2fwrite(void *data, b2fs_int size, b2file *f);
void b2fseek(b2file *f, b2fs_long pos);

#endif
