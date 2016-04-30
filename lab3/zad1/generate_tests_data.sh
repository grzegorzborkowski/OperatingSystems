#!/bin/bash
set -x
Array[0]=5000
Array[1]=25000
Array[2]=100000
Array[3]=1000000

for item in "${Array[@]}"
do
   ./main_fork "${item}" >> tests/main_fork_tests.out
   ./main_vfork "${item}" >> tests/main_vfork_tests.out
   ./clone_fork "${item}" >> tests/clone_fork_tests.out
    ./clone_vfork "${item}" >> tests/clone_vfork_tests.out
done
