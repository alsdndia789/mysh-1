#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>

#include "built_in.h"

int do_vim(int argc, char **argv) {
  int pid;

  pid = fork();
  if (pid > 0)
  {
    wait(NULL);
  }
  else if (pid == 0)
  {
  execv(argv[0], argv);
  wait(NULL);
  }
}

int do_cat(int argc, char **argv) {
  int pid;

  pid = fork();
  if (pid > 0)
  {
    wait(NULL);
  }
  else if (pid == 0)
  {
  execv(argv[0], argv);
  wait(NULL);
  }
}

int do_ls(int argc, char **argv) {
  int pid;
  if (strcmp(argv[argc-1], "&") != 0) {

    pid = fork();
    if (pid > 0)
    {
      wait(NULL);
    }
    else if (pid == 0)
    {
    execv(argv[0], argv);
    wait(NULL);
    }
  }
  else  {
	argv[argc-1]='\0';
	argc=argc-1;

    pid = fork();
    if (pid > 0)
    {
 	for(int i=0;i<5;i++) {
	 printf("%d\n",i);
	sleep(1);
	}
	execv(argv[0],argv);
	wait(NULL);
	}
    else if(pid == 0)
    {
 	exit(-1);
    }
  }
}

int do_cd(int argc, char** argv) {
  if (!validate_cd_argv(argc, argv))
    return -1;
 
  if(argv[1]=="~") return 0;

  else if (chdir(argv[1]) == -1) {
    return -1;
  }
  else

  return 0;
}

int do_pwd(int argc, char** argv) {
  if (!validate_pwd_argv(argc, argv))
    return -1;

  char curdir[PATH_MAX];

  if (getcwd(curdir, PATH_MAX) == NULL)
    return -1;

  printf("%s\n", curdir);

  return 0;
}

int do_fg(int argc, char** argv) {
  if (!validate_fg_argv(argc, argv))
    return -1;

  return 0;
}

int validate_ls_argv(int argc, char** argv) {
  if (argc < 1) return 0;
  if ((strcmp(argv[0], "/bin/ls") != 0) && (strcmp(argv[0], "ls") != 0)) return 0;


  return 1;
}


int validate_cat_argv(int argc, char** argv) {
  if (argc < 1) return 0;
  if (strcmp(argv[0], "/bin/cat") != 0) return 0;
  
  return 1;
} 

int validate_vim_argv(int argc, char** argv) {
  if (argc < 1) return 0;
  if (strcmp(argv[0], "/usr/bin/vim") != 0) return 0;
  
  return 1;
} 

int validate_cd_argv(int argc, char** argv) {
  if (argc != 2) return 0;
  if (strcmp(argv[0], "cd") != 0) return 0;

  struct stat buf;
  stat(argv[1], &buf);

  if ((strcmp(argv[0],"cd")==0) && (strcmp(argv[1],"~")==0)) {
    return 1;
  }

  if (!S_ISDIR(buf.st_mode)) return 0;

  return 1;
}

int validate_pwd_argv(int argc, char** argv) {
  if (argc != 1) return 0;
  if (strcmp(argv[0], "pwd") != 0) return 0;

  return 1;
}

int validate_fg_argv(int argc, char** argv) {
  if (argc != 1) return 0;
  if (strcmp(argv[0], "fg") != 0) return 0;
  
  return 1;
}
