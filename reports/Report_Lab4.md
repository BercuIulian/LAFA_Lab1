# Chomsky Normal Form

### Course: Formal Languages & Finite Automata
### Author: Bercu Iulian

----

## Theory
In formal language theory, a context-free grammar, G, is said to be in Chomsky normal form if all of its production rules are of the form: A → BC, or A → a, or S → ε, where A, B, and C are nonterminal symbols, the letter a is a terminal symbol, S is the start symbol, and ε denotes the empty string.


## Objectives:

* Learn about Chomsky Normal Form (CNF) [1].
* Get familiar with the approaches of normalizing a grammar.
* Implement a method for normalizing an input grammar by the rules of CNF.

  The implementation needs to be encapsulated in a method with an appropriate signature (also ideally in an appropriate class/type)

  The implemented functionality needs executed and tested.

  A BONUS point will be given for the student who will have unit tests that validate the functionality of the project.

  Also, another BONUS point would be given if the student will make the aforementioned function to accept any grammar, not only the one from the student's variant.


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


  * The convertToCNF function takes in the grammar and start symbol as inputs. It first creates a set of non-terminal symbols and their productions by iterating through all productions in the original grammar and determining which ones can be expressed in CNF. It then iterates through all possible lengths of substrings and starting positions, and for each substring, it determines which pairs of non-terminals can produce the left and right substrings. It then creates a new non-terminal symbol to represent the combined substring and adds a new production to the grammar for that symbol.

       ```
          void convertToCNF(map<char, vector<string>> &grammar, char startSymbol) {
          map<string, vector<pair<char, char>>> nonTerminals;

          for (auto &rule : grammar) {
              char lhs = rule.first;
              for (auto &rhs : rule.second) {
                  if (rhs.length() == 0) {
                      continue;
                  }
                  if (rhs.length() == 1 && islower(rhs[0])) {
                      nonTerminals[string(1, rhs[0])].push_back({lhs, ' '});
                  }              else if (rhs.length() == 1 && isupper(rhs[0])) {
                      nonTerminals[string(1, rhs[0])].push_back({lhs, ' '});
                  }
                  else if (rhs.length() == 2 && islower(rhs[0]) && islower(rhs[1])) {
                      nonTerminals[string(rhs)].push_back({lhs, ' '});
                  }
                  else if (rhs.length() == 2 && isupper(rhs[0]) && islower(rhs[1])) {
                      nonTerminals[string(1, rhs[1])].push_back({lhs, rhs[0]});
                  }
                  else if (rhs.length() == 2 && isupper(rhs[0]) && isupper(rhs[1])) {
                      nonTerminals[string(rhs)].push_back({lhs, ' '});
                  }
              }
          }

          for (int len = 2; len <= 3; len++) {
              for (int i = 0; i <= (int) startSymbol; i++) {
                  for (int j = i + 1; j < i + len; j++) {
                      vector<pair<char, char>> leftNonTerminals = nonTerminals[string({(char) i, (char) j})];
                      vector<pair<char, char>> rightNonTerminals = nonTerminals[string({(char) j, (char) i + len})];

                  for (auto &leftNT : leftNonTerminals) {
                      for (auto &rightNT : rightNonTerminals) {
                          char newNT = (char) nonTerminals.size() + 'A';
                          nonTerminals[string({(char) i, (char) i + len})].push_back({newNT, ' '});

                          string newProduction = string(1, leftNT.first) + string(1, rightNT.first);
                          if (leftNT.second != ' ') {
                              newProduction = string(1, leftNT.second) + newProduction;
                          }
                          if (rightNT.second != ' ') {
                              newProduction = newProduction + string(1, rightNT.second);
                          }
                          grammar[newNT].push_back(newProduction);
                      }
                  }
              }
          }
       }
     ```   

* The code then removes all productions that are not in CNF by iterating through all productions in the modified grammar and checking their length and composition. Productions that are already in CNF or have length 0 or 1 are kept. Productions that have length 2 but are not in CNF are modified by adding a new non-terminal symbol and a new production. Productions that have length 3 and are not in CNF are modified by adding two new non-terminal symbols and two new productions.
  
  ```
      for (auto &rule : grammar) {
      vector<string> newProductions;
      for (auto &rhs : rule.second) {
          // If the production has length 0 or 1, it is already in CNF
          if (rhs.length() == 0 || rhs.length() == 1) {
              newProductions.push_back(rhs);
          }
          // If the production has length 2 and is already in CNF, keep it
          else if (rhs.length() == 2 && isupper(rhs[0]) && isupper(rhs[1])) {
              newProductions.push_back(rhs);
          }
          // If the production has length 2 and is not in CNF, add a new non-terminal
          else if (rhs.length() == 2 && islower(rhs[0]) && islower(rhs[1])) {
              char newNT = (char) nonTerminals.size() + 'A';
              grammar[newNT].push_back(rhs);
              newProductions.push_back(string(1, newNT));
          }
          // If the production has length 3 and is not in CNF, add two new non-terminals
          else if (rhs.length() == 3 && isupper(rhs[0]) && isupper(rhs[1]) && isupper(rhs[2])) {
              char newNT1 = (char) nonTerminals.size() + 'A';
              char newNT2 = (char) nonTerminals.size() + 'A';
              grammar[newNT1].push_back(string(1, rhs[0]) + string(1, rhs[1]));
              grammar[newNT2].push_back(string(1, rhs[2]));
              newProductions.push_back(string(1, newNT1) + string(1, newNT2));
          }
      }
      rule.second = newProductions;
    }
  }
  ```
  
* The 'main' function
  
  ```
  map<char, vector<string>> grammar = {
  {'S', {"aB", "bA", "A"}},
  {'A', {"B", "AS", "bBAB", "b"}},
  {'B', {"bS", "aD", ""}},
  {'D', {"AA"}},
  {'C', {"Ba"}}
  };
  convertToCNF(grammar, 'S');

  for (auto &rule : grammar) {
      cout << rule.first << " -> ";
      for (auto &rhs : rule.second) {
          cout << rhs << " | ";
          }
      cout << endl;
      }
  ```


## Conclusions / Screenshots / Results
```
  The overall effect of this code is to convert a context-free grammar to CNF, which is a form of grammar that is easier to work
  with in parsing algorithms. The code achieves this by identifying which productions in the original grammar can be expressed in
  CNF and creating new non-terminal symbols and productions to represent those that cannot.
```

