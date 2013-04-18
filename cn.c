//cn: create note utility
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "notes.h"


void printUsage(char *);

int main (int argc, char * argv[]) {
  if((argc>=2 && (strcmp("-h", argv[1])==0 || strcmp("--help", argv[1])==0)) || argc==1) {
    printUsage(argv[0]);
    return 0;
  }
  char *nh=getenv(NOTES_HOME);
  FILE *fp;
  if (nh==NULL) {
    fprintf(stderr, "%s environment variable is not set\nSending output to stdout.\n\n", NOTES_HOME);
    fp=stdout;
  }
  else {
    fp = fopen(nh,"a");
  }
  int c, i=0;
  time_t t=time(NULL);
  struct tm *z=localtime(&t);
  
  char tc[81];
  fprintf(fp, BEGIN_NOTE);
  strftime(tc, sizeof(tc), "%a-%x-%H:%M:%S%n", z);
  fprintf(fp, "%s", tc);
  if (argc>=2 && strcmp("-",argv[1])!=0) { // use argv[1] as note content

    while ((c=(char)argv[1][i++])!=0) {
      fprintf(fp, "%c", c);
    }
    if (argc>=3) { // use argv[2-...] as tag content
      fprintf(fp, "\nt=");
      int argi;
      for(argi=2;argi<argc;++argi) {
	i=0;
	fprintf(fp,argi==2?"":"~");
	while ((c=(char)argv[argi][i++])!=0) {
	  fprintf(fp,"%c",c);
	}
      }
    }
    fprintf(fp, "\n%s\n\n\n", END_NOTE);
    fclose(fp);
  }
  else {
    if (strcmp("-",argv[1])==0) { // use stdin as all of note content
      fprintf(stderr, "Go ahead and type your note. Ctrl+d will end input.\n");

      while ((c=getchar())!=EOF) {
	fprintf(fp, "%c", c);
	//if(c=='\n') fprintf(fp, "-- ");
      }
      fprintf(fp, "\n%s\n", END_NOTE);
      fclose(fp);
    }
    else printUsage(argv[0]);
  }
  return 0;
}

void printUsage(char *progname) {
  printf("Usage: %s note [tag1 tag2 ... tagN]\n", progname);
  printf("If note is `-' all of note text (including tags) will be read from stdin.\n");
  printf("create note utility\n");
}
