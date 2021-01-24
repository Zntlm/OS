#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

#define CMDSIZE  64
#define CMDPATH  255

int main(int argc, char **argv) {

  char *input = malloc(CMDSIZE);
  char *args[CMDPATH];
  int i=0;
  int j=0;

  for (;;) {
    // protection du fork a faire
    //fork();
    j = 0;
    printf("$>");
    fgets(input, CMDSIZE, stdin);
    fflush(stdin);

    char *arg = strtok(input, " ");
    while (arg != NULL){
        args[j++] = arg;
        arg = strtok(NULL, " ");
    }
    args[j]=NULL;

    if(strcmp(args[0], "exit")==0){

      break;
    }

    pid_t id = fork();

    if(id>0){
      wait(NULL);
    }else if(id==0){
      int err = execvp(args[0],args);
      if(err==-1){
        perror("Erreur de commande");
        exit(EXIT_FAILURE);
      }
    }else {
      printf("Erreur de fork");
      break;
    }
//Rajouter un wait

    //execvp( argv[position],&argv[position]);

  }


free (input);
  return 0;

}
