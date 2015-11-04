#include <stdio.h>
#define MAX_FILE_SIZE 1024

int main(int argc, char*argv[]){

  FILE *f;
  unsigned char buffer[MAX_FILE_SIZE];
  int n;

  f = fopen(argv[1], "rb");
  if (f)
  {
    n = fread(buffer, MAX_FILE_SIZE, 1, f);
  }
  else
  {
    // error opening file
    printf("Error opening file %s\n", argv[1]);
  }

  for (int c=0;c<MAX_FILE_SIZE;c++)
  {
    printf("%.2X ", (int)buffer[c]);

    // put an extra space between every 4 bytes
    if (c % 4 == 3)
    {
      printf(" ");
    }

    // Display 16 bytes per line
    if (c % 16 == 15)
    {
      printf("\n");
    }
  }
  // Add an extra line feed for good measure
  printf("\n");
}
