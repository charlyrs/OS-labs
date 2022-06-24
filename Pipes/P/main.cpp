#include <iostream>
#include <string>
#include <sstream>
int main(){
    std::string input, output;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    long long x;
    while(ss>>x){
        output += std::to_string(x * x * x) + ' ';
    }
    std::cout<<output<<'\n';
    return 0;
}

