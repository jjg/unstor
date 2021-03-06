#include <stdio.h>
#include <string.h>
#include <time.h>

void Pearson16(const unsigned char *x, size_t len, char *hex, size_t hexlen);
void all_combinations( char* x, const int len, char *target_hash, char *match);

int main(int argc, char *argv[]){

  int total_hash_time = 0;
  int total_generate_time = 0;

  // generate a hash of the supplied string
  char output_hash[8];
  size_t output_len = 8;

  Pearson16(argv[1], strlen(argv[1]), output_hash, output_len);

  printf("Original input hash: %s\n", output_hash);

  printf("Thinking...\n");
  int start_time = time(NULL);

  // loop through all possible input data to find 
  // data that returns a matching hash and track how
  // long this takes
  const int maxlen = strlen(argv[1]);
  char match[maxlen];
  char x[maxlen+1];
  for(int thislen=1; thislen <= maxlen; thislen++){
    x[thislen] = 0;
    all_combinations(x, thislen-1, output_hash, match);
  }

  int end_time = time(NULL);

  printf("\nReconstituted original input: %s\n", match);
  printf("Elapsed time: %ds\n", end_time - start_time);
  return 0;
}

void Pearson16(const unsigned char *x, size_t len, char *hex, size_t hexlen) {
  size_t i, j;
  unsigned char hh[8];
  static const unsigned char T[256] = {
  // 256 values 0-255 in any (random) order suffices
   98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219, //  1
   61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, //  2
   90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10, //  3
  237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, //  4
  123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, //  5
   59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, //  6
  197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, //  7
   39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99, //  8
  154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, //  9
  133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, // 10
  189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
  183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
  221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
    3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
  238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
   43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  // 16
  };

  for (j = 0; j < 8; j++) {
     unsigned char h = T[(x[0] + j) % 256];
     for (i = 1; i < len; i++) {
        h = T[h ^ x[i]];
     }
     hh[j] = h;
  }

  snprintf(hex, hexlen, "%02X%02X%02X%02X%02X%02X%02X%02X",
     hh[0], hh[1], hh[2], hh[3],
     hh[4], hh[5], hh[6], hh[7]);
}

void all_combinations(char* x, const int len, char* target_hash, char* match)
{
  for (char c = 97; c < 122; ++c){
    x[len] = c;
    if(len>0){
        all_combinations(x, len - 1, target_hash, match );
    } else {
      //printf("\t%d\n", strncmp(x, target_hash, strlen(target_hash)));

      // test input candidate
      char test_hash[8];
      size_t test_hash_len = 8;
      Pearson16(x, strlen(x), test_hash, test_hash_len);

      if(strncmp(test_hash, target_hash, strlen(test_hash)) == 0){
        strcpy(match, x);
      }
    }
  }
}
