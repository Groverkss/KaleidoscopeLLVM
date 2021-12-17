#include "kaliedoscope/Lexer.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

Lexer::Lexer(const std::string &filename) {
  std::ifstream infile;
  infile.open(filename);

  // Read from file to string stream.
  std::stringstream sstr;
  if (infile.is_open()) {
    infile >> sstr.rdbuf();
  } else {
    // TODO: Emit error.
    std::cerr << "Could not read file " << filename << "\n";
    return;
  }

  // Close initial file.
  infile.close();

  // Transfer contents to `fileBuffer`.
  fileBuffer = std::move(sstr.str());

  // Set first character and ptr;
  consume();
}

bool Lexer::atEOF() { return currPtr >= fileBuffer.size(); }

void Lexer::consume() {
  if (atEOF()) {
    lastChar = EOF;
    return;
  }

  lastChar = fileBuffer[currPtr];
  currPtr++;
}

static std::unique_ptr<Token> createToken(Kind kind,
                                          const std::string &spelling) {
  std::unique_ptr<Token> tkn = std::make_unique<Token>(kind, spelling);
  return std::move(tkn);
}

std::unique_ptr<Token> Lexer::getNextToken() {
  // While loop in case some branch wants to re-execute token getting.
  while(true) {
    // Skip whitespace.
    while (std::isspace(lastChar))
      consume();

    // Identifier: [a-zA-Z][a-zA-Z0-9_]*
    if (std::isalpha(lastChar)) {
      std::string idStr;
      idStr = lastChar;

      consume();
      // Keep getting tokens until regex matches.
      while (std::isalnum(lastChar) || lastChar == '_') {
        idStr += lastChar;
        consume();
      }

      // Create token based on spelling.
      if (idStr == "def")
        return createToken(Kind::def, idStr);
      if (idStr == "extern")
        return createToken(Kind::ext, idStr);
      return createToken(Kind::id, idStr);
    }

    // Number: [0-9.]+
    if (std::isdigit(lastChar) || lastChar == '.') {
      std::string digitStr;
      digitStr = lastChar;

      consume();
      while (std::isdigit(lastChar) || lastChar == '.') {
        digitStr += lastChar;
        consume();
      }

      return createToken(Kind::num, digitStr);
    }

    // If comment, skip till end of line.
    if (lastChar == '#') {
      do {
        consume();
      } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

      // Try getting the token again.
      continue;
    }

    if (lastChar == EOF)
      return createToken(Kind::eof, "EOF");

    // Otherwise return this character
    std::string lastSpelling;
    lastSpelling = lastChar;
    consume();
    return createToken(Kind::unknown, lastSpelling);
  }
}
