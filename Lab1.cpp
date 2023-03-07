#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    if (aux==str.length())cout<<"posible";
    }
};

int main() {
    // Set the random seed
    srand(time(NULL));
    grammar obj;
    string input;
    int i;

    // Generate five strings
    for (int i = 0; i < 5; i++) {
        string str = obj.S();
        cout << str << endl;
    }
    cout<< "Enter string:";
    cin>>input;
    obj.check(input);

    return 0;
}

