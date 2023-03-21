#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;

//---5 random strings---

// Function declarations
string S();
string L();
string D();

// Global variables
const string VT = "abcdefj";

class grammar {
    public:
    string S() {
        int r = rand() % 5;
        switch (r) {
            case 0:
                return "e";
            case 1:
                return "a" + S();
            case 2:
                return "b" + S();
            case 3:
                return "c" + D();
            case 4:
                return "d" + L();
        }
    }

    string L() {
        int r = rand() % 4;
        switch (r) {
            case 0:
                return "e";
            case 1:
                return "e" + L();
            case 2:
                return "f" + L();
            case 3:
                return "j" + D();
        }
    }

    string D() {
        int r = rand() % 2;
        switch (r) {
            case 0:
                return "d";
            case 1:
                return "e" + D();
        }
    }

    //---check if string valid---

    void check(string str){
        int aux=1;
        if ((str[0]=='a'||str[0]=='b'||str[0]=='c'||str[0]=='d'||str[0]=='e')&&(str[str.length()-1]=='e'||str[str.length()-1]=='d')){
            for (int i=0; i<str.length()-1;i++)
            {
                if ((str[i]=='a'||str[i]=='b')&&(str[i+1]=='a'||str[i+1]=='b'||str[i+1]=='c'||str[i+1]=='d'||str[i+1]=='e')) aux++;
                if ((str[i]=='c'||str[i]=='j'||str[i]=='e')&&(str[i+1]=='e'||str[i+1]=='d')) aux++;
                if ((str[i]=='d'||str[i]=='f')&&(str[i+1]=='f'||str[i+1]=='j')) aux++;
            }
        }
    if (aux==str.length())cout<<"true\n";
    else cout<<"false\n";
    }
};

    // ---classify grammar based on Chomsky hierarchy---
string classify_grammar(vector<string> productions) {
    bool is_chomsky = true;

    for (string production : productions) {
        if (production.length() == 1) {
            if (!isupper(production[0])) {
                // if the production rule has a single terminal symbol
                // then the grammar is type-3 (regular)
                return "Type-3 (Regular)";
            }
        } else if (production.length() == 2) {
            if (!isupper(production[0]) || !isupper(production[1])) {
                // if the production rule has two symbols, and at least one of them is terminal
                // then the grammar is type-3 (regular)
                return "Type-3 (Regular)";
            }
        } else {
            // if the production rule has more than two symbols
            // then the grammar is not type-3 (regular)
            is_chomsky = false;

            for (int i = 0; i < production.length(); i++) {
                if (!isupper(production[i])) {
                    // if any symbol in the production rule is not a non-terminal symbol
                    // then the grammar is not type-2 (context-free)
                    return "Type-3 (Regular)";
                }
            }
        }
    }

    if (is_chomsky) {
        // if all production rules are of the form A -> BC (where A, B, C are non-terminals)
        // then the grammar is type-0 (unrestricted)
        return "Type-0 (Unrestricted)";
    } else {
        // if some production rule violates the above conditions
        // then the grammar is type-1 (context-sensitive)
        return "Type-1 (Context-sensitive)";
    }
}

//---conversion of FA to RG

// A state in the finite automaton
struct State {
    string id;
    unordered_map<char, set<string>> transitions;
};

// A regular grammar production rule
struct Rule {
    char nonTerminal;
    string production;
};

// Convert a finite automaton to a regular grammar
vector<Rule> fa_to_rg(const vector<State>& states, string startState, set<string> acceptStates) {
    vector<Rule> rules;
    unordered_map<string, char> stateToNonTerminal;

    // Assign a unique non-terminal to each state
    int nonTerminalId = 0;
    for (const auto& state : states) {
        if (state.id == startState) {
            stateToNonTerminal[state.id] = 'S';  // Start symbol
        } else {
            stateToNonTerminal[state.id] = 'A' + nonTerminalId;
            ++nonTerminalId;
        }
    }

    // Add productions for each state
    for (const auto& state : states) {
        char nonTerminal = stateToNonTerminal[state.id];
        for (const auto& transition : state.transitions) {
            char inputSymbol = transition.first;
            for (const auto& nextState : transition.second) {
                char nextNonTerminal = stateToNonTerminal[nextState];
                if (acceptStates.count(nextState)) {
                    // Accept state
                    rules.push_back({ nonTerminal, string(1, inputSymbol) + nextNonTerminal });
                } else {
                    // Non-accept state
                    rules.push_back({ nonTerminal, string(1, inputSymbol) + nextNonTerminal });
                    rules.push_back({ nextNonTerminal, "" });
                }
            }
        }
    }

    return rules;
}

//---deterministic or non-deterministic---

// define the finite automata as a tuple
typedef tuple<set<string>, set<char>, map<pair<string, char>, set<string>>, string, set<string>> finite_automata;
bool is_deterministic(finite_automata AF) {
    set<string> Q;
    set<char> sigma;
    map<pair<string, char>, set<string>> delta;
    string q0;
    set<string> F;

    tie(Q, sigma, delta, q0, F) = AF;

    map<string, map<char, string>> transitions;  // a map to keep track of transitions

    for (auto q : Q) {
        for (auto a : sigma) {
            auto next_states = delta[{q, a}];

            if (next_states.empty()) {
                return false;  // transition function is not total
            }

            if (next_states.size() > 1) {
                return false;  // non-deterministic
            }

            string next_state = *next_states.begin();  // get the next state

            if (transitions[q].count(a) > 0) {
                if (transitions[q][a] != next_state) {
                    return false;  // non-deterministic
                }
            } else {
                transitions[q][a] = next_state;  // add transition to the map
            }
        }
    }

    return true;  // deterministic
}


int main() {
    // Set the random seed
    srand(time(NULL));
    grammar obj;
    string input;
    int i;

    vector<string> productions = {"S → aS","S → bS","S → cD","S → dL","S → e","L → eL","L → fL","L → jD","L → e","D → eD","D → d"};

    string classification = classify_grammar(productions);

    cout << "The given grammar is of type: " << classification << endl;

    cout << "5 random strings:"<<endl;
    // Generate five strings
    for (int i = 0; i < 5; i++) {
        string str = obj.S();
        cout << str << endl;
    }
    cout<< "Enter string:";
    cin>>input;
    obj.check(input);

    vector<State> states = {
        { "q0", { { 'a', { "q1", "q2" } } } },
        { "q1", { { 'b', { "q1" } }, { 'a', { "q2" } } } },
        { "q2", { { 'a', { "q1" } }, { 'b', { "q3" } } } },
        { "q3", {} }
    };
    string startState = "q0";
    set<string> acceptStates = { "q3" };

    auto rules = fa_to_rg(states, startState, acceptStates);
    for (const auto& rule : rules) {
        cout << rule.nonTerminal << " -> " << rule.production << endl;
    }

    set<string> Q = {"q0", "q1", "q2", "q3"};
    set<char> sigma = {'a', 'b'};
    map<pair<string, char>, set<string>> delta = {{{"q0", 'a'}, {"q1"}},
                                                   {{"q0", 'a'}, {"q2"}},
                                                   {{"q1", 'b'}, {"q1"}},
                                                   {{"q1", 'a'}, {"q2"}},
                                                   {{"q2", 'a'}, {"q1"}},
                                                   {{"q2", 'b'}, {"q3"}}};
    string q0 = "q0";
    set<string> F = {"q3"};

    finite_automata AF = make_tuple(Q, sigma, delta, q0, F);

    // check whether the finite automata is deterministic
    if (is_deterministic(AF)) {
        cout << "The finite automata is deterministic." << endl;
    } else {
        cout << "The finite automata is non-deterministic." << endl;
    }

    return 0;
}

