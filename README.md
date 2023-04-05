# Drawing a graph, C++

My first gui C++ app

## Requirements
[SFML](https://github.com/SFML/SFML), Git, CMake, Clang, 
[nlohmann-json](https://github.com/nlohmann/json), QT-6:

```bash
yes | sudo apt-get install libsfml-dev
yes | sudo apt-get install git
yes | sudo apt install cmake
yes | sudo apt install clang
yes | sudo apt-get install nlohmann-json3-dev
yes | sudo apt install qt6-base-dev
```

## Building and running

```bash
cd {dir_you_need}
```
```bash
git clone https://github.com/93mmm/plotting
cd plotting
mkdir build
cd build
cmake ..
make
```
Wait until project end compiling
```bash
mv notepad ../exec
```

To run application:
```bash
cd ..
cd exec
./notepad
```
