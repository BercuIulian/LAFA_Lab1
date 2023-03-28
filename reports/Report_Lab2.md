# NFA to DFA Conversion

### Course: Formal Languages & Finite Automata
### Author: Bercu Iulian

----

## Theory
In NFA, when a specific input is given to the current state, the machine goes to multiple states. It can have zero, one or more than one move on a given input symbol.
On the other hand, in DFA, when a specific input is given to the current state, the machine goes to only one state. DFA has only one move on a given input symbol.


## Objectives:

Understand what an automaton is and what it can be used for.

Continuing the work in the same repository and the same project, the following need to be added: a. Provide a function in your grammar type/class that could classify the grammar based on Chomsky hierarchy.

b. For this you can use the variant from the previous lab.

According to your variant number (by universal convention it is register ID), get the finite automaton definition and do the following tasks:

a. Implement conversion of a finite automaton to a regular grammar.

b. Determine whether your FA is deterministic or non-deterministic.

c. Implement some functionality that would convert an NDFA to a DFA.

d. Represent the finite automaton graphically (Optional, and can be considered as a bonus point):

You can use external libraries, tools or APIs to generate the figures/diagrams.

Your program needs to gather and send the data about the automaton and the lib/tool/API return the visual representation.

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
