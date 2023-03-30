# Regular Grammars & Finite Automata

### Course: Formal Languages & Finite Automata
### Author: Bercu Iulian

----

## Theory
Regular grammar is a type of grammar in which every production rule has only one non-terminal symbol on its left-hand side, and on the right-hand side, it can have either a single terminal symbol or a combination of a single terminal and a single non-terminal symbol.


## Objectives:

Understand what a language is and what it needs to have in order to be considered a formal one.

Provide the initial setup for the evolving project that you will work on during this semester. I said project because usually at lab works, I encourage/impose students to treat all the labs like stages of development of a whole project. Basically you need to do the following:

a. Create a local && remote repository of a VCS hosting service (let us all use Github to avoid unnecessary headaches);

b. Choose a programming language, and my suggestion would be to choose one that supports all the main paradigms;

c. Create a separate folder where you will be keeping the report. This semester I wish I won't see reports alongside source code files, fingers crossed;

According to your variant number (by universal convention it is register ID), get the grammar definition and do the following tasks:

a. Implement a type/class for your grammar;

b. Add one function that would generate 5 valid strings from the language expressed by your given grammar;

c. Implement some functionality that would convert and object of type Grammar to one of type Finite Automaton;

d. For the Finite Automaton, please add a method that checks if an input string can be obtained via the state transition from it;
## Implementation description
* The grammar I had for this Lab is Variant 4

VN={S, L, D}, 

VT={a, b, c, d, e, f, j}

P={ 
    S → aS
    S → bS
    S → cD
    S → dL
    S → e
    L → eL
    L → fL
    L → jD
    L → e
    D → eD
    D → d
}

*  The 'State' struct is the finite automaton and 'Rule' a regular grammar production rule. Then there follows 'fa_to_rg' that is a vector ment to covnert a finite 
   automaton to a regular grammar. Next it assigns a unique non-terminal to each state and Adds productions for each state.
   ```
      struct State {
    string id;
    unordered_map<char, set<string>> transitions;
   };

   struct Rule {
       char nonTerminal;
       string production;
   };

   vector<Rule> fa_to_rg(const vector<State>& states, string startState, set<string> acceptStates) {
       vector<Rule> rules;
       unordered_map<string, char> stateToNonTerminal;

       int nonTerminalId = 0;
       for (const auto& state : states) {
           if (state.id == startState) {
               stateToNonTerminal[state.id] = 'S'; 
           } else {
               stateToNonTerminal[state.id] = 'A' + nonTerminalId;
               ++nonTerminalId;
           }
       }

       for (const auto& state : states) {
           char nonTerminal = stateToNonTerminal[state.id];
           for (const auto& transition : state.transitions) {
               char inputSymbol = transition.first;
               for (const auto& nextState : transition.second) {
                   char nextNonTerminal = stateToNonTerminal[nextState];
                   if (acceptStates.count(nextState)) {
                       rules.push_back({ nonTerminal, string(1, inputSymbol) + nextNonTerminal });
                   } else {
                       rules.push_back({ nonTerminal, string(1, inputSymbol) + nextNonTerminal });
                       rules.push_back({ nextNonTerminal, "" });
                   }
               }
           }
       }
       return rules;
   }
   ```


* The 'is_deterministic' is a typedef that defines the finite automata as a tuple, then there is a map 'transitions' that will keep track of the transitions.
   At the end a 'for' that will loop throuhg all the states to check if it is deterministic or non-deterministic.

   ```
   typedef tuple<set<string>, set<char>, map<pair<string, char>, set<string>>, string, set<string>> finite_automata;
   bool is_deterministic(finite_automata AF) {
       set<string> Q;
       set<char> sigma;
       map<pair<string, char>, set<string>> delta;
       string q0;
       set<string> F;

       tie(Q, sigma, delta, q0, F) = AF;

       map<string, map<char, string>> transitions; 
       
       for (auto q : Q) {
           for (auto a : sigma) {
               auto next_states = delta[{q, a}];
               if (next_states.empty()) {
                   return false;
               }
               if (next_states.size() > 1) {
                   return false;
               }
               string next_state = *next_states.begin();
               if (transitions[q].count(a) > 0) {
                   if (transitions[q][a] != next_state) {
                       return false;
                   }
               } else {
                   transitions[q][a] = next_state;
               }
           }
       }
       return true;
   }
   ```
## Conclusions / Screenshots / Results

![image](https://user-images.githubusercontent.com/113422203/228363573-1d8ad6f0-df80-48e8-a3d7-19997e685742.png)
