#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void readable_form(float size){
  int index = 0;
  char * sizes[] = {"B", "KB", "MB", "GB"};
  while (size >= 1024){
    size /= 1024;
    index+=1;
  }
  printf("%f%s\n",size,sizes[index]);
  return;
}

int main(int argc, char *argv[]){
  char* dir = malloc(50);

  //USER INPUT
  if (argc <= 1){ //if argc > 1, then there is an provided entry
      printf("Type a directory (or . for current directory): ");
      fgets(dir, 50, stdin);
      dir[strlen(dir)-1] = 0; // fixes the ending
  } else {
      dir = argv[1];
  }
  printf("Looking into directory: %s\n", dir );


  DIR * d;
  d = opendir(dir);
  struct dirent * entry;

  //User does not knows what they are doing.
  if (!d){
    printf("Error! %s. Follow the (dir)ections next time. File this error away for later purposes. \n", strerror(errno));
    return 0;
  }

  struct stat *file = malloc(sizeof(struct stat));
  entry=readdir(d);
  int filesize, rfilesize = 0;
  printf("---List of Files--- \n");

  while(entry){
    // creates "dir/file_name" format to be used in size later
    char *filename = calloc(sizeof(char),100);
    strcat(filename,dir);
    strcat(filename,"/");
    strcat(filename,entry->d_name);
    stat(filename,file);

    // prints out the file name and type! if entry is regular, add its size to rfilesize
    printf("File Name: %s\n",entry->d_name);
    if(entry->d_type==4){
      printf("File Type: Directory\n");
    }
    else if(entry->d_type==8){
      printf("File Type: Regular\n");
      rfilesize += file->st_size;
    }

    // prints out the file size of all files in bytes and human form, updates total filesize
    printf("File Size: %lld or ",file->st_size);
    readable_form((float)file->st_size);
    filesize += file->st_size;

    //updates entry with next file
    entry=readdir(d);
    printf("---------------\n");

  }

  //prints out total size for regular and everything
  printf("Total Regular File Size: %d bytes or ",rfilesize);
  readable_form(rfilesize);
  printf("Total File Size: %d bytes or ",filesize);
  readable_form(filesize);
  closedir(d);
  return 0;
}
