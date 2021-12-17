#ifndef _KALIEDOSCOPE_TOKEN_H_
#define _KALIEDOSCOPE_TOKEN_H_

#include <string>

enum Kind {
  eof,
  def,
  ext,
  id,
  num,
  unknown,
};

class Token {
public:
  Token(Kind kind, const std::string &spelling)
      : kind(kind), spelling(spelling) {}

  std::string &getSpelling() { return spelling; }

  Kind getKind() const { return kind; }

private:
  Kind kind;

  std::string spelling;
};

#endif
