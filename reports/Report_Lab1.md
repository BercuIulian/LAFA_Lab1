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
    S → aS;
    S → bS;
    S → cD;
    S → dL;
    S → e;
    L → eL;
    L → fL;
    L → jD;
    L → e;
    D → eD;
    D → d;
}

*  Class 'grammar' has a 'string' function for each non-terminal variable S, L, D that will return one of the global variables declared as a const string above. The 'string' function calls to a 'switch' that will randomly generate a global variable.
   ```
    string S();
    string L();
    string D();
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
   ```


* The 'check' void is a function that checks if a entered string is a valid one. The function works based on an aux variable that will increment if the next variable obeys the low of the grammar. If the 'aux' is the same as the length of the string then it is a valid string.

   ```
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
   ```
## Conclusions / Screenshots / Results

![image](https://user-images.githubusercontent.com/113422203/228898812-f0fa1791-9f74-4bbb-9b6d-f5c88e5e03ff.png)
