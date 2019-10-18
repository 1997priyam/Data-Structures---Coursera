#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket obj = Bracket(next, position);
            opening_brackets_stack.push(obj);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()){
                std::cout<<++position;
                return 0;
            } 
            Bracket temp = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if(!temp.Matchc(next)){
                std::cout<<++position;
                return 0;
            } 
        }
    }


    // Printing answer, write your code here
    if(opening_brackets_stack.empty()) std::cout<<"Success";
    else{
        Bracket ans = Bracket('a', 1);
        while(!opening_brackets_stack.empty()){
            ans = opening_brackets_stack.top();
            opening_brackets_stack.pop();
        }
        std::cout<<++ans.position;

    }
    return 0;
}
