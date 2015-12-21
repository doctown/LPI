/************************************************/
/* Ex6-3 An implementation of setenv & unsetenv */
/* 					        */
/* Author: David Ogor			        */
/* Date: 07-01-2015			        */
/************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char ** environ;

/* 
 * Set an environment variable based on parameters.
 *
 * params: name - the name of the environment variable
 *         value - the value to be stored
 *         overwrite - 0 indicates that the value will not be overwritten, 
 *                     any other value will allow overwritting
 * returns 0 on success, -1 no value was changed
 */
int set(char *name, char *value, int overwrite) 
{
  char buf[BUFSIZ];		/* buffer */
  char *bufp = buf;
  int res = 0; 			/* results from functions */

  /* Determine overwritting allowed and prevent if not allowed */
  if (overwrite != 0) {
    if (getenv(name) != NULL) {
      return -1;
    }
  }

  /* Add value to environment */
  strcpy(buf, name);
  strcat(buf, "=");
  strcat(buf, value);
  res = putenv(buf);

  return res;
}

/* 
 * Removes all occurences of a variable from the environment.
 *
 * param: name - name of variable to be removed.
 * 
 * Returns 0 if successfull, otherwise -1 on error.
 */
int unset(const char *name) {
  char **ep = NULL;
  char tname[BUFSIZ];
  char *tnamep = tname;
			     
  for (ep = environ; *ep != NULL; ++ep) {
    printf("%s\t", *ep);
    
    /* locate the variable name */
    strncpy(tnamep, *ep, BUFSIZ);
    strtok(tnamep, "=");

    if (strcmp(tnamep, name) == 0) {
      /* set to NULL and update environ */ 
      *ep = *(ep + 1);

      char **cur = ep + 1;
      char **prev = cur;
      *prev = *cur;
      for (; *cur != NULL; ++cur) {
	*prev = *cur;
      }
    }    
  }
  printf("\n");
}

int main(int argc, char *argv) {
  /*  */
  printf("test = %s\n", getenv("test"));
  set("test", "t1", 0);
  //set("test", "t1", 0);
  printf("test = %s\n", getenv("test"));

  unset("test");
  printf("test = %s\n", getenv("test"));

  return 0;
}
