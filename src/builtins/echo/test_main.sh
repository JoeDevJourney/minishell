#!/bin/bash

cc ../echo.c ../../../include/libft/src/ft_split.c ../../../include/libft/src/ft_strlen.c ../../../include/libft/src/ft_strlcpy.c ../../../include/libft/src/ft_strjoin.c ../../../include/libft/src/ft_strncmp.c ../../../include/libft/src/ft_strlcat.c -g -Wall -Werror -Wextra
echo
args=("Hello World" " " "")

for arg in "${args[@]}"
do
	echo "arg= \"$arg\""
	echo -------------------------------------
	echo -ne "Test 1: echo $arg\t\t"
	if [ "$(echo $arg | cat -e)" = "$(./a.out "echo" "$arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo $arg | cat -e)"
		echo "$(./a.out "echo" "$arg" | cat -e)"
		echo
	fi

	echo -ne "Test 2: echo -n $arg\t\t"
	if [ "$(echo -n $arg | cat -e)" = "$(./a.out "echo" "-n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -n $arg | cat -e)"
		echo "$(./a.out "echo" "-n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 3: echo -n -n $arg\t\t"
	if [ "$(echo -n -n $arg | cat -e)" = "$(./a.out "echo" "-n -n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -n -n $arg | cat -e)"
		echo "$(./a.out "echo" "-n -n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 4: echo -nn $arg\t\t"
	if [ "$(echo -nn $arg | cat -e)" = "$(./a.out "echo" "-nn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -nn $arg | cat -e)"
		echo "$(./a.out "echo" "-nn $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 5: echo -nn -nn $arg\t"
	if [ "$(echo -nn -nn $arg | cat -e)" = "$(./a.out "echo" "-nn -nn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -nn -nn $arg | cat -e)"
		echo "$(./a.out "echo" "-nn -nn $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 6: echo -x $arg\t\t"
	if [ "$(echo -x $arg | cat -e)" = "$(./a.out "echo" "-x $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -x $arg | cat -e)"
		echo "$(./a.out "echo" "-x $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 7: echo -x -n $arg\t\t"
	if [ "$(echo -x -n $arg | cat -e)" = "$(./a.out "echo" "-x -n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -x -n $arg | cat -e)"
		echo "$(./a.out "echo" "-x -n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 8: echo -xn $arg\t\t"
	if [ "$(echo -xn $arg | cat -e)" = "$(./a.out "echo" "-xn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -xn $arg | cat -e)"
		echo "$(./a.out "echo" "-xn $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 9: Echo $arg\t\t"
	if [ "$(echo $arg | cat -e)" = "$(./a.out "Echo" "$arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo $arg | cat -e)"
		echo "$(./a.out "Echo" "$arg" | cat -e)"
		echo
	fi

	echo -ne "Test 10: Echo -n $arg\t\t"
	if [ "$(echo -n $arg | cat -e)" = "$(./a.out "Echo" "-n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -n $arg | cat -e)"
		echo "$(./a.out "Echo" "-n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 11: Echo -n -n $arg\t\t"
	if [ "$(echo -n "-n $arg" | cat -e)" = "$(./a.out "Echo" "-n -n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"	
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -n "-n $arg" | cat -e)"
		echo "$(./a.out "Echo" "-n -n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 12: Echo -nn $arg\t\t"
	if [ "$(echo "-nn $arg" | cat -e)" = "$(./a.out "Echo" "-nn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo "-nn $arg" | cat -e)"
		echo "$(./a.out "Echo" "-nn $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 13: Echo -nn -nn $arg\t"
	if [ "$(echo "-nn -nn $arg" | cat -e)" = "$(./a.out "Echo" "-nn -nn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo "-nn -nn $arg" | cat -e)"
		echo "$(./a.out "Echo" "-nn -nn $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 14: Echo -x $arg\t\t"
	if [ "$(echo -x $arg | cat -e)" = "$(./a.out "Echo" "-x $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo -x $arg | cat -e)"
		echo "$(./a.out "Echo" "-x $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 15: Echo -x -n $arg\t\t"
	if [ "$(echo "-x -n $arg" | cat -e)" = "$(./a.out "Echo" "-x -n $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\033[41mKO\033[0m"
		echo
		echo "$(echo "-x -n $arg" | cat -e)"
		echo "$(./a.out "Echo" "-x -n $arg" | cat -e)"
		echo
	fi

	echo -ne "Test 16: Echo -xn $arg\t\t"
	if [ "$(echo "-xn $arg" | cat -e)" = "$(./a.out "Echo" "-xn $arg" | cat -e)" ]; then
		echo -e "\033[42mOK\033[0m"
	else
		echo -e "\b \033[41mKO\033[0m"
		echo
		echo "$(echo "-xn $arg" | cat -e)"
		echo "$(./a.out "Echo" "-xn $arg" | cat -e)"
		echo
	fi
	echo
	echo
done