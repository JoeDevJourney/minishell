#!/bin/bash

cc echo.c ../../../include/libft/src/ft_split.c ../../../include/libft/src/ft_strlen.c ../../../include/libft/src/ft_strlcpy.c ../../../include/libft/src/ft_strjoin.c ../../../include/libft/src/ft_strncmp.c ../../../include/libft/src/ft_strlcat.c -g -Wall -Werror -Wextra
echo

echo -ne "Test 1: echo Hello World\t\t"
RES1=$(echo Hello World | cat -e)
RES2=$(./a.out "echo" "Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 2: echo -n Hello World\t\t"
RES1=$(echo -n Hello World | cat -e)
RES2=$(./a.out "echo" "-n Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 3: echo -n -n Hello World\t\t"
RES1=$(echo -n -n Hello World | cat -e)
RES2=$(./a.out "echo" "-n -n Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 4: echo -nn Hello World\t\t"
RES1=$(echo -nn Hello World | cat -e)
RES2=$(./a.out "echo" "-nn Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 5: echo -nn -nn Hello World\t"
RES1=$(echo -nn -nn Hello World | cat -e)
RES2=$(./a.out "echo" "-nn -nn Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

RES1=$(echo -x Hello World | cat -e)
RES2=$(./a.out "echo" "-x Hello World" | cat -e)
echo -ne "Test 6: echo -x Hello World\t\t"
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 7: echo -x -n Hello World\t\t"
RES1=$(echo -x -n Hello World | cat -e)
RES2=$(./a.out "echo" "-x -n Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 8: echo -xn Hello World\t\t"
RES1=$(echo -xn Hello World | cat -e)
RES2=$(./a.out "echo" "-xn Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi
echo
echo "-------------------------------------------"
echo
RES1=$(echo Hello World | cat -e)
RES2=$(./a.out "Echo" "Hello World" | cat -e)
echo -ne "Test 9: Echo Hello World\t\t"
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 10: Echo -n Hello World\t\t"
RES1=$(echo -n Hello World | cat -e);
RES2=$(./a.out "Echo" "-n Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 11: Echo -n -n Hello World\t\t"
RES1=$(echo -n "-n Hello World" | cat -e);
RES2=$(./a.out "Echo" "-n -n Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"	
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 12: Echo -nn Hello World\t\t"
RES1=$(echo "-nn Hello World" | cat -e)
RES2=$(./a.out "Echo" "-nn Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 13: Echo -nn -nn Hello World\t"
RES1=$(echo "-nn -nn Hello World" | cat -e)
RES2=$(./a.out "Echo" "-nn -nn Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

echo -ne "Test 14: Echo -x Hello World\t\t"
RES1=$(echo -x Hello World | cat -e)
RES2=$(./a.out "Echo" "-x Hello World" | cat -e)
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

RES1=$(echo "-x -n Hello World" | cat -e)
RES2=$(./a.out "Echo" "-x -n Hello World" | cat -e)
echo -ne "Test 15: Echo -x -n Hello World\t\t"
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi

RES1=$(echo "-xn Hello World" | cat -e)
RES2=$(./a.out "Echo" "-xn Hello World" | cat -e)
echo -ne "Test 16: Echo -xn Hello World\t\t"
if [ "$RES1" = "$RES2" ]; then
	echo -e "\033[42mOK\033[0m"
else
	echo -e "\033[41mKO\033[0m"
	echo
	echo "$RES1"
	echo "$RES2"
	echo
fi
echo