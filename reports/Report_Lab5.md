# Parser & Building an AST

### Course: Formal Languages & Finite Automata
### Author: Bercu Iulian

----

## Theory
A parser is a software component that analyzes the structure of a program or a piece of code written in a specific programming language. Its primary task is to take the input code and transform it into a more structured representation, known as an Abstract Syntax Tree (AST).


## Objectives:

* Get familiar with parsing, what it is and how it can be programmed [1].
* Get familiar with the concept of AST [2].
* In addition to what has been done in the 3rd lab work do the following:

  i In case you didn't have a type that denotes the possible types of tokens you need to:
  
    a. Have a type TokenType (like an enum) that can be used in the lexical analysis to categorize the tokens.
    
    b. Please use regular expressions to identify the type of the token.
    
  ii Implement the necessary data structures for an AST that could be used for the text you have processed in the 3rd lab work.
  
  iii Implement a simple parser program that could extract the syntactic information from the input text.


## Implementation description

*  In this example, the getTokenType function takes a token as input and matches it against different regular expressions to determine its type. The regular expressions used are:
    1) integerRegex to match integers (e.g., 123); 
    2) floatRegex to match floating-point numbers (e.g., 3.14); 
    3) identifierRegex to match identifiers (e.g., variable_name);
    4) operatorRegex to match operators (e.g., +, -, *, /);
   
   The function returns the corresponding TokenType enum value based on the match. The main function prompts the user to enter a token, calls getTokenType to determine its type, and displays the result.
   
   ```
     enum TokenType {
    INTEGER,
    FLOAT,
    IDENTIFIER,
    OPERATOR,
    UNKNOWN
    };

    TokenType getTokenType(const std::string& token) {
      std::regex integerRegex(R"(\d+)");
      std::regex floatRegex(R"(\d+\.\d+)");
      std::regex identifierRegex(R"([a-zA-Z_][a-zA-Z0-9_]*)");
      std::regex operatorRegex(R"([+\-*/])");

      if (std::regex_match(token, integerRegex)) {
          return INTEGER;
      } else if (std::regex_match(token, floatRegex)) {
          return FLOAT;
      } else if (std::regex_match(token, identifierRegex)) {
          return IDENTIFIER;
      } else if (std::regex_match(token, operatorRegex)) {
          return OPERATOR;
      } else {
          return UNKNOWN;
      }
    }
     ```


  * In this example, we have two classes representing different types of AST nodes: BinaryOpNode for binary operations (such as addition, multiplication), and NumberNode for numeric values. The base class ASTNode defines a pure virtual function print(), which is implemented by the derived classes.
  
   The BinaryOpNode class contains the operator (op) and pointers to the left and right child nodes, while the NumberNode class stores the numeric value (value).
   
   In the main() function, a simple AST is constructed representing the expression (2 + 3) * 4. The AST nodes are created dynamically using new and linked together according to the desired structure. Finally, the print() function is called on the root node (multiplyNode) to visualize the AST structure.

       ```
          class ASTNode {
    public:
        virtual ~ASTNode() {}
        virtual void print() const = 0;
    };

    class BinaryOpNode : public ASTNode {
    private:
        char op;
        ASTNode* left;
        ASTNode* right;

    public:
        BinaryOpNode(char op, ASTNode* left, ASTNode* right)
            : op(op), left(left), right(right) {}

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " " << op << " ";
        right->print();
        std::cout << ")";
    }
    };

    class NumberNode : public ASTNode {
    private:
        double value;

    public:
        NumberNode(double value) : value(value) {}

    void print() const override {
        std::cout << value;
    }
    };
     ```   

* This parser program takes a sentence as input and extracts the syntactic information: subject, verb, and object. It assumes a simple sentence structure of "subject verb object." The program reads the input sentence, tokenizes it based on whitespace, and then extracts the relevant parts.
  
  ```
  class Parser {
  private:
    std::string input;
    size_t position;

    public:
        Parser(const std::string& text) : input(text), position(0) {}

    void parse() {
        parseSentence();
    }

    private:
        void parseSentence() {
            parseSubject();
            parseVerb();
            parseObject();
            parseEndOfSentence();
        }

    void parseSubject() {
        std::cout << "Subject: ";
        parseWord();
        std::cout << std::endl;
    }

    void parseVerb() {
        std::cout << "Verb: ";
        parseWord();
        std::cout << std::endl;
    }

    void parseObject() {
        std::cout << "Object: ";
        parseWord();
        std::cout << std::endl;
    }

    void parseWord() {
        skipSpaces();
        std::string word;
        while (position < input.length() && !isspace(input[position])) {
            word += input[position];
            position++;
        }
        std::cout << word;
    }

    void parseEndOfSentence() {
        skipSpaces();
        if (input[position] == '.') {
            std::cout << "End of Sentence" << std::endl;
            position++;
        } else {
            std::cerr << "Error: Expected end of sentence" << std::endl;
        }
    }

    void skipSpaces() {
        while (position < input.length() && isspace(input[position])) {
            position++;
        }
    }
    };
  ```
 


## Conclusions / Screenshots / Results
```
  In conclusion, parsers analyze the syntax of input text based on grammar rules. They break down the input and ensure compliance.
  Parsers often generate an Abstract Syntax Tree (AST) to represent the parsed structure. ASTs enable further analysis and interpretation.
  Parsers are crucial for language processing and facilitate the extraction of syntactic information for subsequent processing.
```

