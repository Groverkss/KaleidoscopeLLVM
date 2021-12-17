# Kaledioscope LLVM

My second attempt at trying to finish Kaleidoscope since the first one didn't
work out due to my laziness :(

## Resources

Stuff I found useful:

- [To understand a recursive descent parsing](https://stackoverflow.com/questions/2245962/is-there-an-alternative-for-flex-bison-that-is-usable-on-8-bit-embedded-systems/2336769#2336769)

- [Building an AST with a parser](https://stackoverflow.com/questions/25049751/constructing-an-abstract-syntax-tree-with-a-list-of-tokens/25106688#25106688)

## Random Notes

- While lexing, use could enum values for characters like '+', '-' as their
  ASCII value. This can simplify the tokenizing implementation. Something like:

```cpp
enum Token : int {
  tok_semicolon = ';',
  tok_parenthese_open = '(',
  .
  .
  .

  tok_eof = -1

  tok_return = -2
  tok_var = -3
  .
  .
  .
}
```

This way, you only have to check regex for the negative enums and rest you can just
return as:

```cpp
return Token(lastChar)
```
