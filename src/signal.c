#include "signal_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
  
void catch_sigint(int)
{
  signal(SIGINT,SIG_IGN);
  // TODO: File this!
}

void catch_sigtstp(int);
{
  signal(SIGTSTP,SIG_IGN);
  // TODO: File this!
}
