#!/bin/zsh

g++ --std=c++17 test.cpp -fno-exceptions -o test.bin

echo "Test A: handled AchtungType::DOES_NOT_EXIST"
./test.bin "doesntexist"
echo ""

echo "Test B: unhandled AchtungType::MEMORY"
./test.bin "veryveryverylongfilepath"
echo ""

echo "Test C: handled AchtungType::FD_LIMIT"
./test.bin "run.sh"
