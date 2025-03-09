#ifndef MY_TAR_H
#define MY_TAR_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define OCTAL_BASE 8
#define DEC_BASE 10
#define BLOCKSIZE 512

typedef struct posix_header
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
                                /* 500 */
} tar_header;

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#define XHDTYPE  'x'            /* Extended header referring to the
                                   next file in the archive */
#define XGLTYPE  'g'            /* Global extended header */

typedef struct s_opt
{
    bool create;
    bool extract;
    char *archive_name;
    struct s_argument *args;
} tar_options;

typedef struct s_argument
{
    char *filename;
    struct s_argument *next;
} t_argument;

// File_manipulation.c
int open_archive_file(tar_options *options);

// get_opt.c
tar_options *get_opt(int, char **);
void delete_options(tar_options *);

// arguments_list.c
void add_to_list(t_argument **, char *);
t_argument *init_argument();
void delete_argument_list(t_argument **);

// Conversion.c
char *my_itoa_base(char *, unsigned int, int, int);
long oct_to_dec(long);
long dec_to_oct(long);
long my_atol(const char *, int);

int write_file_content(int fd_archive, char *filename);
void end_of_archive(int);
int create_archive(int fd_archive, tar_options *options);

#endif