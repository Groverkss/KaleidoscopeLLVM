#ifndef _KALIEDOSCOPE_LEXER_H_
#define _KALIEDOSCOPE_LEXER_H_

#include "kaleidoscope/Token.h"

#include <iterator>
#include <memory>

struct Location {
  std::string filename;
  unsigned line, col;
};

class Lexer {
public:
  Lexer(const std::string &filename);

  std::unique_ptr<Token> getNextToken();

private:
  bool atEOF();

  void consume();

  std::string fileBuffer;

  unsigned currPtr = 0;

  char lastChar;
};

#endif
