#include <iostream>
#include <string>
#include <sstream>
int main(){
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    long long x;
    long long sum = 0;
    while(ss>>x){ sum+=x; }
    std::cout<<sum<<'\n';
    return 0;
}

