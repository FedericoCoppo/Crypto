/*
    UniSFED Copyright (C) 2007 Involutive http://www.involutive.com
    author: Paolo Ardoino < paolo@involutive.com >

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"


/* Miscellaneous functions */
int fexists(char *file);
void help(char *name);

/* RSA fucntions */
void* readpemkeys(int type, char *pemfile); /*RSA*/
int rsa_encrypt(void *key, unsigned char *plain, int len, unsigned char **cipher);/*RSA*/
int rsa_decrypt(void *key, unsigned char *cipher, int len, unsigned char **plain);/*RSA*/


#include "rsa.c"
#include "misc.c"
