/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース
static char *execpath = "/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  
  int status = 0;
  // ここにプログラムを書く
  pid_t pid;
  if((pid=fork())<0){
    return -1;
  }
  if(pid!=0){
    while(wait(&status)!=pid)
      ;
      
  }else{
    execl(execpath, "sh", "-c", command, (char *)NULL);
    exit(127);
  }
  return status;
  
}

/* 実行例

ここに実行例を書く
takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ls -l
total 616
-rw-r--r--  1 takemotoai  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takemotoai  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takemotoai  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takemotoai  staff   50392  7  9 10:09 mysysmain
-rw-r--r--@ 1 takemotoai  staff     925  7  4 10:12 mysysmain.c
-rw-r--r--@ 1 takemotoai  staff    1751  7  9 10:14 mysystem.c
-rw-r--r--  1 takemotoai  staff      90  7  4 09:43 mysystem.h

takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 takemotoai  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takemotoai  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takemotoai  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takemotoai  staff   50392  7  9 10:09 mysysmain
-rw-r--r--@ 1 takemotoai  staff     925  7  4 10:12 mysysmain.c
-rw-r--r--@ 1 takemotoai  staff     720  7  9 10:09 mysystem.c
-rw-r--r--  1 takemotoai  staff      90  7  4 09:43 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 takemotoai  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takemotoai  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takemotoai  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takemotoai  staff   50392  7  9 10:09 mysysmain
-rw-r--r--@ 1 takemotoai  staff     925  7  4 10:12 mysysmain.c
-rw-r--r--@ 1 takemotoai  staff     720  7  9 10:09 mysystem.c
-rw-r--r--  1 takemotoai  staff      90  7  4 09:43 mysystem.h
retval = 00000000

takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ./mysysmain 
使い方 : ./mysysmain コマンド文字列

takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ./mysysmain aaa
mysystem:
sh: aaa: command not found
retval = 00007f00
system:
sh: aaa: command not found
retval = 00007f00

takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ./mysysmain echo a.txt
使い方 : ./mysysmain コマンド文字列

takemotoai@takemotoainoMacBook-Air kadai10-i21takemoto % ./mysysmain "rm"             
mysystem:
usage: rm [-f | -i] [-dIPRrvWx] file ...
       unlink [--] file
retval = 00004000
system:
usage: rm [-f | -i] [-dIPRrvWx] file ...
       unlink [--] file
retval = 00004000

*/
