mkdir build
echo  [ Building Number... ]

g++ -c Number/Number.cpp -o build/Number.exe
ar rc build/Number.lib build/Number.exe

echo [ Building Vector... ]

g++ -c -INumber Vector/Vector.cpp -o build/Vector.exe
g++  build/Vector.exe build/Number.lib -shared -o build/Vector.dll

echo [ Building Main... ]

g++ -o lab1.exe lab1console/lab1.cpp -INumber -IVector build/Vector.dll build/Number.lib;
.\lab1.exe


