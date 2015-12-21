/********************************************************************************************/
/* grp_function - Implement a few function that convert a group id to a name and vica-versa */
/* 											    */
/* Author: David Ogor									    */
/* Date: 07-17-2015									    */
/********************************************************************************************/
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>
#include <shadow.h>

/* 
 * Return name corresponding to uid, or NULL on error
 */
char *userName(const uid_t uid)
{
  struct passwd *pwd;

  pwd = getpwuid(uid);
  if (pwd == NULL) {
    if (errno == 0) {
      printf("Cannot locate uid\n");
      return NULL;
    } else {
      perror("getpwuid");
      exit(1);
    }
  }
  return pwd->pw_name;
}

/* 
 * Return the UID  corresponding to name or -1 on error.
 */
uid_t getUID(const char *name) 
{
  uid_t u;
  struct passwd *pwd;
  
  pwd = getpwnam(name);
  
  u = pwd->pw_uid;

  return (pwd == NULL) ? -1 : pwd->pw_uid;
}


/* 
 * Print all the usernames on the system.
 */
void print_usernames(void)
{
  struct passwd *pwd;
  struct spwd *pwds;

  //Iterate through password directory and print username
  while((pwd = getpwent()) != NULL) {
    //    printf("%s - pass: %s\n", pwd->pw_name, pwd->pw_passwd);
  }
  endpwent();

  while ((pwds = getspent()) != NULL) {
    printf("%s - pass %s\n", pwds->sp_namp, pwds->sp_pwdp);
  }
}


int main(void)
{
  print_usernames();
  return 0;
}
