


#include "common.h"

#include <signal.h>


/*@doit interface@*/
int doit(int argc,char **argv);

/*@doit impl end@*/


/*@sig_usr@*/

static void sig_usr(int);

/*@sig_usr end@*/


/*@doit impl@*/
int doit(int argc,char **argv){
  
    if(signal(SIGUSR1,sig_usr)==SIG_ERR){
        err_sys("signal error");
    }

      if(signal(SIGUSR2,sig_usr)==SIG_ERR){
        err_sys("signal error");
    }
   for(;;)
    pause();
}
/*@doit impl end@*/

static void sig_usr(int sig){

if(sig==SIG_USR1){
    printf("sig_user1 handler\n");
}else if(sig==SIG_USR2){
    printf("sig_usr2 hangler\n ");
}else {
    err_dump("receive signal=%d\n",sig);
}

}