//
//  b2fopen.h
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef bf2s_b2fopen_h
#define bf2s_b2fopen_h

#include "types.h"
#include "b2file.h"

b2file *b2fopen(char *filename);
void b2fclose(b2file *f);

#endif
