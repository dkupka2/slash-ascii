/* slash-ascii.c - Converts text specified by the user */
/* output to an ASCII text file, to a number of forward */
/* slashes terminated by backslashes - by Dan Kupka  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 1024

int main(int argc, char *argv[]) {

  /* declare some variables */
  FILE *fp = NULL;           /* pointer to type FILE (macro declared in stdio.h for file handling */

  char fw_slash = '/',       /* foward- and backslash char variables */
       bk_slash = '\\',
       *str = NULL;

  int fw_count = 0,         /* declare counter variables for forward- and backslash, and */
      bk_count = 0,         /* overall character count */
      ch_count = 0;

  /* check for possible exceptions trying to parse command line arguments */
  if (argc != 2) {
    printf("Writes forward- and backslashes to a file.\n\nUsage: %s <filename>\n\n", argv[0]);

    return 0;
  }

  str = malloc( BUFF * sizeof(char));

  printf("Enter a string to convert: ");
  fgets(str, BUFF, stdin);
  str[ strlen(str) - 1] = 0;

  /* attempt to open the file for writing (passed in from command line) */
  if ( !(fp = fopen(argv[1], "w")) ) {
    printf("Error: Cannot open '%s'.  Exiting...\n", argv[1]);
    return -1;
  }

  for (int i = 0; str[i] != 0; i++) {
    for (int j = 0; j < str[i]; j++) {
      fputc(fw_slash, fp);
    }
    fputc(bk_slash, fp);
  }

  fclose(fp);
  free(str);

  fp = NULL;
  str = NULL;

  return 0;
}
