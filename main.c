#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define VARIENT {3, 5, 7}

unsigned int getch(void) {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

int main(int argc, char **argv){
  if (argc<2){
    fputs("No file provided\n", stderr);
    exit(1);
  }

  FILE *fp = fopen(argv[1], "r");
  if(fp!=NULL){
    unsigned int v[] = VARIENT;
    unsigned int vs = sizeof(v)/sizeof(*(v)), vi = 0;
    char c;
    while( c!=EOF ) {
      getch();
      for(unsigned int i=0; i<v[vi]; i++){
        c=fgetc(fp);
        putchar(c);
      }
      vi++;
      if(vi==vs) vi=0;
    }
    fclose(fp);
  }
  else {
    puts("Unable to open file\n");
    exit(2);
  }
}
