#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

#define CMDSIZE  64
#define CMDPATH  255

int main(int argc, char **argv) {

  char *input = malloc(CMDSIZE); //taille max de la commande
  char *args[CMDPATH]; //nombre d'argments max que l'utilisateur peux rentrer
  char cwd[1024];
  char *history[100];
  int i=0;
  int j=0;
  int n;
  int k;

  for (n=0;;n++) {
    j = 0;
    getcwd(cwd,sizeof(cwd));
    printf("%s$>",cwd);
    fgets(input, CMDSIZE, stdin);
    input[strlen(input)-1]='\0';
    history[n]=input;
    for(k=0;k<=n;k++){
    printf("history[%d] : %s\n",k+1, history[n]);
    }
    char *arg = strtok(input, " ");
    while (arg != NULL){
        args[j++] = arg;
        arg = strtok(NULL, " "); //découpe les arguments saisie par l'utilisateur
    }
    args[j]=NULL;

    if(strcmp(args[0], "exit")==0){ //permet de quitter le terminal

      break;
    }else if(strcmp(args[0], "cd")==0){
      chdir(args[1]); //fonction en c permettant d'utiliser CD
      continue;
    }else if(strcmp(args[0], "help")==0){
      args[0]="man"; //affiche le manuel man (pour quitter: q)

    }else if(strcmp(args[0], "history")==0){
      for(k=0;k<=n;k++){
        printf("%d : %s\n",k+1,history[k]);
      }
      continue;
    }

    pid_t id = fork(); //sécurise le fork

    if(id>0){
      wait(NULL);
    }else if(id==0){
      int err = execvp(args[0],args);//permet d'executer les arguments un par un rentrer par l'utilisateur
      if(err==-1){
        perror("Erreur de commande"); //affiche ce message d'erreur pour une mauvaise commande
        exit(EXIT_FAILURE);
      }
    }else {
      printf("Erreur de fork");
      break;
    }
  }


  free (input);
  return 0;

}
