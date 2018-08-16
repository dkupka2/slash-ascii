/* slash-ascii.c - Outputs text from ASCII text file */
/* specified by the user based on numbers of forward */
/* slashes terminated by backslashes - by Dan Kupka  */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /* declare some variables */
  FILE *fp;                 /* pointer to type FILE (macro declared in stdio.h for file handling */

  char fw_slash = '/',       /* foward- and backslash char variables, along with a temp char */
       bk_slash = '\\',      /* variable (ch) to store each character read from a file */
       ch;                  /* (inefficient, but it works!) */

  int fw_count = 0,         /* declare counter variables for forward- and backslash, and */
      bk_count = 0,         /* overall character count */
      ch_count = 0;

  /* check for possible exceptions trying to parse command line arguments */
  if (argc > 2) {
    printf("Too many arguments.\n\nUsage: %s <filename>\n\n", argv[0]);

    return -1;
  }

  if (argc < 2) {
    printf("Parses a file.\n\nUsage: %s <filename>\n\n", argv[0]);

    return 0;
  }

  /* attempt to open the file for reading (passed in from command line) */
  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Error: Cannot open '%s'.  Exiting...\n", argv[1]);

    return -1;
  }

  /* count the number of backslashes in the file */
  while ( ( ch = fgetc(fp) ) != EOF ) {
    if (ch == bk_slash) {
      bk_count++;
    }
  }
  printf("bk_count: %d\n", bk_count);

  /* declare a pointer to a buffer, and allocate memory the size of which is */
  /* the number of backslashes counted from the previous loop */
  char *buffer = malloc( bk_count * sizeof(char) );

  /* make sure that buffer did or did not return NULL (in the latter case, exit) */
  if (buffer == NULL) {
    printf("Sorry, unable to allocate memory.\n");
    return -1;
  } else {
    printf( "Allocated memory: %d byte(s)\n", bk_count * sizeof(char) );
  }

  /* reset the position of the file pointer in the file read to position 0 */
  fseek(fp, 0L, SEEK_SET);
  bk_count = 0;

  /* run through the file read again */
  while ( ( ch = fgetc(fp) ) != EOF ) {

    /* keep incrememnting forward-slash count if char is a forward slash... */
    if (ch == fw_slash) {
      fw_count++;
    }

    /* until a backslash is encountered, then reset the forward-slash count to 0, */
    /* store the forward-slash count in the appropriate element of the buffer array, */
    /* increment the position on the array to the next element, and increment */
    /* backslash count */

    if (ch == bk_slash) {
      printf("fw_count for set %d: %d\n", bk_count, fw_count);
      buffer[bk_count] = fw_count;
      bk_count++;
      fw_count = 0;
    }

  }

  fclose(fp);

  for (int i = 0; i < ch_count; i++) {
    printf("%d ", buffer[i]);
  }

  printf("\nFile contents:\n%s\n", buffer);

  printf("\n");  

  /* ensure that any memory that was allocated is freed !!! */
  free(buffer);

  return 0;
}
