


g++ -std=c++17 -O2 -Wall -Wextra -g -fsanitize=address $1.cpp -o $1.out -g
./$1.out < $1.in
