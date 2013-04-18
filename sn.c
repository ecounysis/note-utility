//sn: search note utility
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"


void scanfile(FILE *);

char note_buff[NOTE_BUF_SIZE];
char word_buff[SEARCH_STRING_SIZE];
char search_string[SEARCH_STRING_SIZE];

int main(int argc, char *argv[]) {
  if (argc==1) {
    printf("Usage: %s string\n", argv[0]);
    return 0;
  }
  char *nh=getenv(NOTES_HOME);
  FILE *fp=fopen(nh,"r");
  if (nh==NULL) {
    fprintf(stderr, "%s environment variable not set. Cannot search notes.", NOTES_HOME);
    return 0;
  }
  if (fp==NULL) {
    fprintf(stderr, "%s file does not exist. Cannot search notes.", nh);
    return 0;
  }
  strncpy(search_string, argv[1], SEARCH_STRING_SIZE);
  scanfile(fp);
  return 0;
}

void scanfile(FILE *fp) {
  char c;
  int notep = 0;
  int wordp = 0;
  int word_found = 0;
  while ((c=getc(fp)) != EOF) { // loop while not at end of file
    note_buff[notep++] = c; // add c to note_buff
    if (c<'!' || c>'~') { // end of word
      word_buff[wordp++] = 0; // terminate the string
      if (strcmp(word_buff, search_string)==0) { // word found
	word_found=1;
      }
      if (strcmp(word_buff, END_NOTE)==0) { // end of note
	note_buff[notep] = 0; // terminate the string
	if (word_found==1)
	  printf("'%s' found:\n%s%s\n\n", search_string, BEGIN_NOTE, note_buff); // print it
	notep=0; // reset notep
	word_found=0;
      } // end of note
      wordp=0; // reset wordp
      if (strcmp(word_buff, BEGIN_NOTE) == 0) { // beginning of note
	notep=0;
      }
    } // end of word
    else { // not the end of a word
      word_buff[wordp++]=c; // add to word_buff
    }   
  } // end of file 
}
