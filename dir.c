#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){
  char* dir = malloc(50);
  if (argc <= 1){ //if argc > 1, then there is an provided entry
      printf("Directory: ");
      fgets(dir, 50, stdin);
      dir[strlen(dir)-1] = 0; // fixes the ending
  } else {
      dir = argv[1];
  }
  printf("Looking into directory: %s\n", dir );

  DIR * d;
  d = opendir(dir);
  struct dirent * entry;
  if (!d){
    printf("The directory you have entered does not exist!\n" );
    return 0;
  }

  struct stat *file = malloc(sizeof(struct stat));
  entry=readdir(d);
  printf("List of Files: \n");
  while(entry){
    printf("---------------\n");
    printf("File Name: %s\n",entry->d_name);
    if(entry->d_type==4){
      printf("File Type: Directory\n");
    }
    else if(entry->d_type==8){
      printf("File Type: Regular\n");
    }
    entry=readdir(d);
  }
  closedir(d);

  return 0;
}
