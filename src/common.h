
#ifndef __COMMON_H
#define __COMMON_H
 



#ifndef  __UNIX_STD_
    #include <unistd.h>
#else 
   #define  __UNIX_STD_

#endif



#ifndef  __UNIX_WAIT_
  #include <sys/wait.h>
#else 
   #define  __UNIX_WAIT_

#endif


#ifndef  __UNIX_SIGNAL_
   #include <signal.h>
#else 
   #define  __UNIX_SIGNAL_

#endif



#include "err.h"



/*@wait start@*/
pid_t Wait(int *staloc){
    
    pid_t pid;
    if((pid=waitpid(-1,NULL,0))<0){
        err_sys("waitpid error");
    }
    return pid;
}
/*@wait end@*/


/*@err_exit() start@*/

#define err_exit(m) do{\
   perror(m);\
   exit(0);\
}while(0)
/*@err_exit() end@*/


/*@_error()@*/

#define __info(fmt,...)do{\
   printf("[%s]<%s> [%d]:",__FILE__,__func__,__LINE__);\
   printf(fmt,__VA_ARGS__);\
}while(0)


#define _pos()  __info("%s","\n")

#define mkstr(symbol)    #symbol

#define   _error(cond,err_table,fmt,...)         do{\
          if(cond){\
                __info("******error occured******|%s",mkstr(cond));  \
               printf(fmt,__VA_ARGS__);           \
               goto err_table;                    \ 
          }\
}while(0)

/*@_error() end@*/


/*@Fork start@*/
 
 pid_t Fork(){
   pid_t pid;
   if((pid=fork())<0){
     err_sys("%s error","fork");
   }
   return pid;
 }


/*@Fork end@*/


/*@system impl@*/

/*-version 0.1*/
int System(const char *cmd){
 pid_t pid;
 int status;
 if(cmd==NULL){
   err_sys("cmd error");
 }
 pid=Fork();
 if(pid==0){
   execl("/bin/sh","sh","-c",cmd,0);
   _exit(127);
 }else {
   //wait child
   while((waitpid(pid,NULL,0))<0){
     if(errno!=EINTR){
        status=-1;
        break;
     }
   }

 }
}
/*@system impl end@*/



#endif