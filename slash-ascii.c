/* slash-ascii.c - Outputs text from ASCII text file */
/* specified by the user based on numbers of forward */
/* slashes terminated by backslashes - by Dan Kupka  */
/* 8/16/2018 - Bug fix by github.com/iridiumblue     */  
/*           - Null terminate string.                */                        



#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /* declare some variables */
  FILE *fp = NULL;   // CJR always set a pointer to NULL while declaring.

  char fw_slash = '/',       /* foward- and backslash char variables, along with a temp char */
       bk_slash = '\\',      /* variable (ch) to store each character read from a file */
       ch=0;    // CJR good form to always assign to something in declaration, even if the value makes no sense.

  int fw_count = 0,         /* declare counter variables for forward- and backslash, and */
      bk_count = 0,         /* overall character count */
      ch_count = 0;

  /* check for possible exceptions trying to parse command line arguments */
  if (argc != 2) { // argument check usually combined.
    printf("Parses a file.\n\nUsage: %s <filename>\n\n", argv[0]);
    return -1;
  }



  /* attempt to open the file for reading (passed in from command line) */
  if (!(fp = fopen(argv[1], "r"))) {  // CJR file open and error logic usually combined like this.
                                      // note that assignment operator returns a value, so that printf("%d",(a=2)) would print 2.
                                      // note also that NULL is always false, so we can do these compact if-tests on them.
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
  char *buffer = NULL;  // CJR - It's considered bad form to call a function in a declaration.  This becomes clear later
                        // as you encounter garbage collection and things like file collection pooling.

  if (!(buffer=malloc( (bk_count+1) * sizeof(char) ))) {  // same trick here as in file open above.  Notice how the NULL/false thing
                                                         // gives the same code pattern in two different contexts.
    /* make sure that buffer did or did not return NULL (in the latter case, exit) */
   
    printf("Sorry, unable to allocate memory.\n");
    return -1;
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
  buffer[bk_count]=0; // NULL terminate buffer, otherwise results are unpredictable when printed, etc.

  fclose(fp); fp=NULL; // CJR good form to set file handle to NULL after closing, to avoid writing to a closed file by mistake later.

  for (int i = 0; i < ch_count; i++) {
    printf("%d ", buffer[i]);
  }

  printf("\nFile contents:\n%s\n", buffer);  // Good thing we NULL terminated, else at this stage we could
                                             // get garbage text appearing after the string, or the program could
                                             // segmentation fault.

  printf("\n");  

  /* ensure that any memory that was allocated is freed !!! */
  free(buffer);  buffer=NULL;  // CJR good form to prevent the dreaded invalid memory write.

  return 0;
}
