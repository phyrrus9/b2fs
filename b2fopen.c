//
//  b2fopen.c
//  bf2s
//
//  Created by Ethan Laur on 1/2/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "b2fopen.h"
#include "b2global.h"
#include "b2fstable.h"

/*
 b2file *b2fopen(char *filename);
 void b2fclose();
 */

b2file *b2fopen(char *filename)
{
    return b2fstbl_get(filename);
}

void b2fclose(b2file *f)
{
    free(f);
}
