mkdir build
echo  [Building Number...]

g++ -c Number/Number.cpp -o build/Number.o
ar rc build/Number.lib build/Number.o

echo [Building Vector...]

g++ -c -INumber Vector/Vector.cpp -o build/Vector.o
g++  build/Vector.o build/Number.lib -shared -o build/Vector.dll

echo [Building Main...]

g++ lab1console/lab1.cpp -o build/lab1 -INumber -IVector build/Vector.dll build/Number.lib

.\build\lab1

echo [FINISHED]

rm -R build
