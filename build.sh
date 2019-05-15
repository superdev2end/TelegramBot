yes | sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev zlib1g-dev
mkdir build
cd build
cmake ..
make -j4
cd ..

g++ telecommand_bot.cpp -o telecommand_bot --std=c++11 -I./include -L./build -lTgBot -lboost_system -lssl -lcrypto -lpthread