#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char *strrev(char *str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}


int palin(char * a ){
	  char  b[100];
	  strcpy(b, a); 
	  strrev(b);  
	 
	  if (strcmp(a, b) == 0)  {
		return 1;
	}
	  else{
	 	return 0;
	 }
}
int main(int argc, char const *argv[])
{
    char str[100];
    printf("enter the word t be checked\n");
    scanf("%s",str);

    int res=palin(str);

    if(res==1){
        printf("Palindrome");
    }
    else{
        printf("Not Plaindrome");
    }

    return 0;
}
