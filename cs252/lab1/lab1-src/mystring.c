#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */


char *mystrcpy(char * s1, const char * s2)
{
  /* Complete procedure */
	int i=0;
	while(s2[i] != '\0'){
		s1[i]=s2[i];
		i++;
	}
	s1[i]='\0';
	return s1;
}

size_t mystrlen(const char *s)
{
  /* Complete procedure */
	int i=0;
	while(s[i]!='\0'){
		i++;
	}
	return i;
}

char *mystrdup(const char *s1)
{
  /* Complete procedure */
	int i=0;
	while (s1[i] != '\0'){
		i++;
	}
	char *s2 = (char *)malloc(i+1);
	int j=0;
	while(j<i+1){
		s2[j]=s1[j];
		j++;
	}
	return s2;
}

char *mystrcat(char * s1, const char * s2)
{
  /* Complete procedure */
	int i=0;
	while(s1[i] != '\0'){
		i++;
	}

	int j=0;
	while(s2[j] != '\0')
	{
		s1[i]=s2[j];
		j++;
		i++;
	}
	s1[i]=s2[j];
	
}

char *mystrstr(char * s1, const char * s2)
{
	if (mystrlen(s2) == 0)
	{
		return s1;
	}
	/* Complete procedure */
	int i=0;
	while(s1[i] != '\0')
	{
		if(s1[i]==s2[0])
		{
			int j = 0;
			int k=i;
			while(s1[k]==s2[j])
			{
				j++;
				k++;
			}
			if(s2[j] == '\0')
				return &s1[i];
		}

		i++;
	}

	return NULL;

}

int mystrcmp(const char *s1, const char *s2) 
{

  /* Complete procedure */
	int j = 0;
	int k = 0;
	while(s1[k]==s2[j] && s1[k] != '\0' && s2[j] != '\0')
	{
		j++;
		k++;
	}
	return (int)s1[k] - (int)s2[j];
}

