#include "io.h"
#include "code.h"
#include "endian.h"

uint8_t buffersym[4096];
uint8_t bufferpair[4096];

int bits = 0;

int symindex = 0;
int tempbyte = 5000;

void read_header(int infile, FileHeader *header) {
  read(infile, header, sizeof(FileHeader));
  if (header->magic == MAGIC | header->magic == swap32(MAGIC)) {
    if (is_little() != true) {
      header->magic = swap32(MAGIC);
      header->protection = swap16(header->protection);
    }
  }
  else {
    printf("Magic number not match up... Exiting.");
    exit(1);
  }
}

void write_header(int outfile, FileHeader *header) {
  if (is_little() != true) {
    header->magic = swap32(header->magic);
    header->protection = swap16(header->protection);
  }
  write(outfile, header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
  ssize_t readbyte;

  // Reads a symbol from the input file.
  if (symindex == 0) {
    readbyte = read(infile, buffersym, 4096);
    
    if (readbyte <= 0) {
      return false;
    }
    if (readbyte < 4096) {
      tempbyte = readbyte;
    }
    
  }
  if (tempbyte == symindex) {
    return false;
  }
  *sym = buffersym[symindex];
  
  if (sym == '\0') {
    return false;
  }
  symindex++;
  
  if (symindex == 4096) {
    symindex = 0;
  }
  return true;
}

// stores the pair (code and sym) in binary
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  uint32_t tempbin, tempbin1;
  uint8_t length = 0;
  // finding the bit length of the code
  if (code >= 1) {
    length = floor(log10(code) / log10(2)) + 1;
  }
  else if (code == 0) {
    length = 1;
  }
  
  // inputing code in binary into the buffer.
  for (int i = 0; i < bitlen; i++) {
    // padding it with zeros if needed
    if (length > i) {
      tempbin1 = code;
      tempbin = (tempbin1 >> i & 0x1);
    }
    else {
      tempbin = 0;
    }
    // Setting the bit from the least significant bit.
    if (tempbin == 1) {
      bufferpair[bits / 8] |= 0x1 << (7 - (bits%8));
    }
    else if (tempbin == 0) {
      bufferpair[bits / 8] &= ~(0x1 << (7 - (bits%8)));
    }
    // Writing the code out if the buffer if full.
    if ((bits / 8) == 4096) {
      write(outfile, bufferpair, 4096);
      for (int i = 0; i < 4096; i++) {
        bufferpair[i] = 0b00000000;
      }
      bits = -1;
    }
    bits++;
  }
  
  // inputing symbols in binary into the buffer.
  for (uint32_t j = 0; j < 8; j++) {
    tempbin1 = sym;
    // Getting the bit.
    tempbin = tempbin1 >> j & 0x1;
    // Setting the bit.
    if (tempbin == 1) {
      bufferpair[bits / 8] |= 0x1 << (7 - (bits%8));
    }
    else {
      bufferpair[bits / 8] &= ~(0x1 << (7 - (bits%8)));
    }
    // Writing the bit if the buffer is full.
    if ((bits / 8) == 4096) {
      write(outfile, bufferpair, 4096);
      for (int i = 0; i < 4096; i++) {
        bufferpair[i] = 0b00000000;
      }
      bits = -1;
    }
    bits++;
  }
}

// Writes out the remainder pairs of symbols and codes to the output file.
void flush_pairs(int outfile) {
  
  write(outfile, bufferpair, (bits/8) + 1);
  // Resetting the buffer.
  for (int i = 0; i < (bits/8) + 1; i++) {
    bufferpair[i] = 0x0;
  }
  bits = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  uint16_t codebin = 0, tempcode = 0, tempbin = 0, tempbin1 = 0;
  uint8_t symbin = 0, tempsym = 0;
  
  // Reading the binary from the infile.
  for (uint8_t i = 0; i < bitlen; i++) {
    if (bits == 0) {
      read(infile, bufferpair, 4096);
    }
    // Getting the bit and setting it
    tempbin1 = bufferpair[bits/8];
    tempbin = (tempbin1 >> (i % 8) & 0x1);
    
    if (tempbin == 1) {
      codebin |= 0x1 << ((bitlen - 1) - i);
      tempcode += pow(2, i);
    }
    else {
      codebin &= ~(1 << ((bitlen - 1) - i));
    }
    if (bits / 8 == 4095 && bits % 8 == 7) {
      for (int j = 0; j < 4096; j++) {
        bufferpair[j] = 0b00000000;
      }
      bits = -1;
    }
    bits++;
  }
  // Getting the bit for the code and setting it
  *code = tempcode;
  for (int i = 0; i < 8; i++) {
    if (bits == 0) {
      read(infile, bufferpair, 4096);
    }
    tempbin1 = bufferpair[bits/8];
    tempbin = (tempbin1 >> (bits % 8) & 0x1);
    if (tempbin == 1) {
      symbin |= 0b00000001 << (7 - i);
      tempsym += pow(2, i);
    }
    else {
      symbin &= ~(0x00000001 << (7 - i));
    }
    if (bits / 8 == 4095 && bits % 8 == 7) {
      for (int j = 0; j < 4096; j++) {
        bufferpair[j] = 0b00000000;
      }
      bits = -1;
    }
    bits++;
  }
  
  *sym = tempsym;
  
  // Read_pairs stops once code equals STOP_CODe
  if (code != STOP_CODE) {
    return true;
  }
  else {
    return false;
  }

}

// Stores the symbols of the words into a symbols buffer and writes it out ocne
// its full to the outfile
void buffer_word(int outfile, Word *w) {
  for (uint32_t i = 0; i < w->len; i++) {
    if (symindex == 4095) {
      write(outfile, buffersym, 4096);
      for (int i = 0; i < 4096; i++) {
        buffersym[i] = 0;
      }
      symindex = 0;
    }
    buffersym[symindex] = w->syms[i];
    symindex++;
  }
}

// Writes rest of the words
void flush_words(int outfile) {
  write(outfile, buffersym, symindex);
  for (int i = 0; i < symindex; i++) {
    buffersym[i] = 0;
  }
}
