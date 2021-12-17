#include "kaleidoscope/Lexer.h"

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: kaleidoscope <filename>\n";
    return 1;
  }

  Lexer lexer(argv[1]);
  std::unique_ptr<Token> currToken = lexer.getNextToken();
  while (currToken->getKind() != Kind::eof) {
    std::string kind;
    if (currToken->getKind() == Kind::def)
      kind = "def";
    else if (currToken->getKind() == Kind::ext)
      kind = "extern";
    else if (currToken->getKind() == Kind::id)
      kind = "identifier";
    else if (currToken->getKind() == Kind::num)
      kind = "number";
    else if (currToken->getKind() == Kind::unknown)
      kind = "unknown";
    else
      kind = "???";

    std::cout << currToken->getSpelling() << " " << kind << "\n";
    currToken = lexer.getNextToken();
  }
}
