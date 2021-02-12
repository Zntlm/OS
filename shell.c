#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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
  int h, min, s, day, mois, an;
  time_t now;
  struct tm *local;
  FILE *fp;
  fp = fopen("tes_shell_history.txt","ab");

  for (n=0;;n++) {
    j = 0;

    time(&now);
    local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;

    getcwd(cwd,sizeof(cwd));
    printf("%s$>",cwd);
    fgets(input, CMDSIZE, stdin);
    //char *firstPart = malloc(6);
    input[strlen(input)-1]='\0';
    //history[n]=input;
    //for(k=0;k<=n;k++){
    //printf("history[%d] : %s\n",k+1, history[n]);
    //}

    if(strcmp(input, "exit")==0){ //permet de quitter le terminal
      break;
    }

    if(fp!=NULL){
        fprintf(fp, "%02d/%02d/%d - %02d:%02d:%02d -> %s\n",day,mois,an,h,min,s,input);
    }

    char *arg = strtok(input, " ");
    while (arg != NULL){
        args[j++] = arg;
        arg = strtok(NULL, " "); //découpe les arguments saisie par l'utilisateur
    }
    args[j]=NULL;

    if(strcmp(args[0], "cd")==0){
      chdir(args[1]); //fonction en c permettant d'utiliser CD
      continue;
    }else if(strcmp(args[0], "help")==0){
      args[0]="man"; //affiche le manuel man (pour quitter: q)

    }else if(strcmp(args[0], "history")==0){
      args[0]="cat";
      args[1]="tes_shell_history.txt";
      execvp(args[0], args);
      continue;
    }
    //else if(strcmp(args[0], "history")==0){
      //for(k=0;k<=n;k++){
        //printf("%d : %s\n",k+1,history[k]);
      //}
      //continue;
    //}

//Changement de la couleur du shell
    /* if(strcmp(args[0], "color")==0){
          char *colorCmd = malloc(20);
          char *firstPart = malloc(6);
          char *bgc = malloc(5);
          char *tc = malloc(5);
          firstPart = "color";
          printf("Background color : ");
          fgets(bgc, 5, stdin);
          bgc[strlen(bgc)-1]='\0';
          printf("\nText color : ");
          fgets(tc, 5, stdin);
          tc[strlen(tc)-1]='\0';
          strcpy(colorCmd, firstPart);
          strcat(colorCmd, " ");
          strcat(colorCmd, bgc);
          strcat(colorCmd, tc);
          system(colorCmd);
          system("color 0a");
          free(colorCmd);
          free(firstPart);
          free(bgc);
          free(tc);
          continue;
    } */



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
  fclose(fp);
  return 0;

}
