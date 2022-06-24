#include <iostream>
#include <string>
#include <sstream>
int main(){
    std::string input, output;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    int x;
    while(ss>>x){
        output += std::to_string(x * 7) + ' ';
    }
    std::cout<<output<<'\n';
    return 0;
}
