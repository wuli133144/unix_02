


#ifndef  __ERR__H
#define  __ERR__H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>


#define MAXLINE 2048
/*@err_doit create it start @*/
static void err_doit(int,int,const char *,va_list);



/*@err_doit create it end @*/

/*@err_sys@*/
  void err_sys(const char  *fmt,...){
      va_list ap;
      va_start(ap,fmt);
      err_doit(1,errno,fmt,ap);
      va_end(ap);
      exit(1);
  }

/*@err_sys end@*/

/*@err_exit@*/


void err_exit(int error,const char *fmt,...){
      va_list ap;
      va_start(ap,fmt);
      err_doit(1,error,fmt,ap);
      va_end(ap);
      exit(1);
}
/*@err_exit end@*/


/*@err_ret@*/
void err_ret(const char *fmt,...){
  va_list ap;
  va_start(ap,fmt);
  err_doit(0,0,fmt,ap);
  va_end(ap);
}

/*@err_ret end@*/


/*@err_dump@*/


void err_dump(const char *fmt,...){
   va_list ap;
  va_start(ap,fmt);
  err_doit(1,errno,fmt,ap);
  va_end(ap);
  abort();//terninal 
  exit(0);
}

/*@err_dump end@ */

/*@errerr_doit impl@*/


 static void err_doit(int flag,int error,const char*fmt,va_list ap){
    char buf[MAXLINE];
     vsnprintf(buf,MAXLINE-1,fmt,ap);
     if(flag)//whether add errno flag
     {
          vsnprintf(buf+strlen(buf),MAXLINE-strlen(buf)-1,":%s",strerror(error));
     }
     strcat(buf,"\n");
     fflush(stdout);
     fputs(buf,stderr);
     fflush(NULL);

}

/*@err_doit impl end@*/

#endif