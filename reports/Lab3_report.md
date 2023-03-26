# Implementing a simple lexer

### Course: Formal Languages & Finite Automata
### Author: Bercu Iulian

----

## Theory
The process of turning a series of characters into a sequence of lexical tokens is known as lexical analysis, lexing, or tokenization in the field of computer science.
Lexer, tokenizer, or scanner are all terms for programs that conduct lexical analysis; however, scanner is also a term for a lexer's initial stage.


## Objectives:

* Understand what lexical analysis [1] is.
* Get familiar with the inner workings of a lexer/scanner/tokenizer.
* Implement a sample lexer and show how it works.


## Implementation description

*  The 'Lexer' class takes in a string 'text' in its constructor and 'tokenizes' it using the tokenize method, which returns a vector of 'Token' objects.
   Each 'Token' object contains a 'TokenType' enum value and a 'string' value
   
   ```
   enum TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    LParen,
    RParen,
    };

    struct Token {
      TokenType type;
      string value;

    Token(TokenType type, const string& value)
        : type(type), value(value) {}
    };
   ```


* The 'advance' method increments the current position in the input string, while 'current_char' returns the current character at that position.The 'skip_whitespace'
  method moves the current position past any whitespace characters, while 'collect_digits' collects a sequence of digits starting from the current position.

   ```
    class Lexer {
    public:
      explicit Lexer(const string& text) : text_(text), pos_(0) {}

    void advance() { pos_++; }

    char current_char() { return pos_ < text_.size() ? text_[pos_] : '\0'; }

    void skip_whitespace() {
      while (isspace(current_char())) {
        advance();
      }
    }

    string collect_digits() {
      string result = "";
      while (isdigit(current_char())) {
        result += current_char();
        advance();
      }
      return result;
    }
   ```

* The 'collect_token' method collects the next token by checking the current character and either advancing the position and returning a corresponding 'Token' object
  or throwing an error if the character is invalid.
  
  ```
    Token collect_token() {
    char current = current_char();
    switch (current) {
      case '+':
        advance();
        return Token(Plus, "+");
      case '-':
        advance();
        return Token(Minus, "-");
      case '*':
        advance();
        return Token(Multiply, "*");
      case '/':
        advance();
        return Token(Divide, "/");
      case '(':
        advance();
        return Token(LParen, "(");
      case ')':
        advance();
        return Token(RParen, ")");
      default:
        if (isdigit(current)) {
          return Token(Number, collect_digits());
        } else {
          throw runtime_error("Invalid character");
        }
    }
  }

  vector<Token> tokenize() {
    vector<Token> tokens;
    while (pos_ < text_.size()) {
      skip_whitespace();
      if (pos_ >= text_.size()) break;
      tokens.push_back(collect_token());
    }
    return tokens;
  }

   private:
    const string text_;
    size_t pos_;
  };
  ```
  
* Finally, in the 'main' function, we create a 'Lexer' object with a sample input string, tokenize it, and print out each token's type and value using a 'for' loop.
  
  ```
    string formula = "3 + 4 * 2 / ( 1 - 5 )";
    Lexer lexer(formula);
  vector<Token> tokens = lexer.tokenize();

  for (const Token& token : tokens) {
    cout << "Token(" << token.type << ", " << token.value << ")" << endl;
  }
  ```


## Conclusions / Screenshots / Results

![image](https://user-images.githubusercontent.com/113422203/227787900-f0f917cf-73cf-4aec-9aa5-65125314dcd5.png)
