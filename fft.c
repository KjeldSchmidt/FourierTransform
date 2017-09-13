#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "fft.h"

#define FILE_BUFFER_SIZE 1000


unsigned char *buffer;
unsigned char channelCount = 0;

int main() {
  buffer = malloc( sizeof(char) * FILE_BUFFER_SIZE );
  if ( buffer == NULL ) {
    error(0, 0, "Problems allocating file buffer");
  }
  FILE *ptr;
  ptr = fopen("sound.wav", "r");

  print_file_metadata( ptr );

  return 0;
}

int print_file_metadata( FILE *file ) {
  size_t chunkSize;
  size_t subchunkTwoOffset = 20;
  int read = fread(buffer, 1, 100, file);

  if ( read < 44 ) {
    error(0, 0, "Problems reading file header");
  }

  printf("RIFF HEADER:\n" );
  printf("ChunkID (Should be RIFF): %.4s\n", buffer);
  chunkSize = (buffer[7] << 24) + (buffer[6] << 16) + (buffer[5] << 8) + (buffer[4] << 0);
  printf("ChunkSize (Should be >>36): %lu\n", chunkSize);
  printf("Format (should be WAVE): %.4s\n", buffer + 8);
  printf("\n");


  printf("SUBCHUNK 1:\n");
  printf("Subchunk 1 ID (Should be \"fmt \"): %.4s\n", buffer + 12 );
  chunkSize = (buffer[19] << 24) + (buffer[18] << 16) + (buffer[17] << 8) + (buffer[16] << 0);
  subchunkTwoOffset += chunkSize;
  printf("Subchunk 1 Size (Should be >16): %lu\n", chunkSize);
  printf("AudioFormat (Should be 1): %d\n", (buffer[21] << 8) + (buffer[20]));
  channelCount = (buffer[23] << 8) + (buffer[22]);
  printf("Number of Channels: %d\n", channelCount);
  printf("Sample Rate: %d\n", (buffer[27] << 24) + (buffer[26] << 16) + (buffer[25] << 8) + (buffer[24]));
  printf("Byte Rate: %d\n", (buffer[31] << 24) + (buffer[30] << 16) + (buffer[29] << 8) + (buffer[28]));
  printf("Block Align: %d\n", (buffer[33] << 8) + (buffer[32]));
  printf("Bits per Sample: %d\n", (buffer[35] << 8) + (buffer[34]));

  printf("\n");
  printf("SUBCHUNK 2:\n");
  printf("Subchunk 2 ID (Should be \"data\"): %.4s\n", buffer + subchunkTwoOffset );
  chunkSize = (buffer[subchunkTwoOffset + 7] << 24) + (buffer[subchunkTwoOffset + 6] << 16) + (buffer[subchunkTwoOffset + 5] << 8) + (buffer[subchunkTwoOffset + 4] << 0);
  printf("Subchunk 2 Size (Should be >>0): %lu\n", chunkSize);


  return 0;
}
