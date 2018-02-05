#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char *stringBuffer = 0; // buffer to hold string for string for inputString()

char inputChar()
{
    char chars[9] = {'a', 'x', '[', ']', '(', ')', '{', '}', ' '};
    int choice = rand() % (9);
    return chars[choice];
}

char *inputString()
{
    int i, choice;

    // free previously allocated space for buffer
    if(stringBuffer != 0) {
      free(stringBuffer);
    }

    stringBuffer = malloc(6); // allocate space for string

    char chars[5] = {'r','e','s','t', '\0'}; // chars to choose from
    
    // select random chars from chars array to build string
    for(i = 0; i <= 5; i++) {
      choice = rand() % (5);
      stringBuffer[i] = chars[choice];
    } 

    return stringBuffer;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
