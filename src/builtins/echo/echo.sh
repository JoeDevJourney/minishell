#!/bin/bash
echo
echo "command		  		output"
echo
echo "1"
echo "echo Hello World:		"$(echo Hello World | cat -e);
echo "echo \"Hello World\":		"$(echo "Hello World" | cat -e);
echo "echo \"\"Hello World\"\":		"$(echo ""Hello World"" | cat -e);
echo "echo : "$(echo | cat -e);
echo "echo \"\": "$(echo "" | cat -e);
echo "echo \" \": "$(echo " " | cat -e);
echo
echo
echo "2"
echo 'echo -n Hello World:		'$(echo -n Hello World | cat -e);
echo 'echo -n "Hello World":        	'$(echo -n "Hello World" | cat -e);
echo 'echo -n \"\"Hello World\"\":	'$(echo -n ""Hello World"" | cat -e);
echo "echo -n : "$(echo -n | cat -e);
echo "echo -n \"\": "$(echo -n "" | cat -e);
echo "echo -n \" \": "$(echo -n " " | cat -e);
echo
echo
echo "3"
echo 'echo -n -n Hello World:		'$(echo -n -n Hello World | cat -e);
echo 'echo -n -n "Hello World":       '$(echo -n -n "Hello World" | cat -e);
echo 'echo -n -n \"\"Hello World\"\":	'$(echo -n -n ""Hello World"" | cat -e);
echo "echo -n -n : "$(echo -n -n | cat -e);
echo "echo -n -n \"\": "$(echo -n -n "" | cat -e);
echo "echo -n -n\" \": "$(echo -n -n " " | cat -e);
echo
echo
echo "4"
echo 'echo -nn Hello World:		'$(echo -nn Hello World | cat -e);
echo 'echo -nn "Hello World":        	'$(echo -nn "Hello World" | cat -e);
echo 'echo -nn \"\"Hello World\"\":	'$(echo -nn ""Hello World"" | cat -e);
echo "echo -nn : "$(echo -nn | cat -e);
echo "echo -nn \"\": "$(echo -nn "" | cat -e);
echo "echo -nn \" \": "$(echo -nn " " | cat -e);
echo
echo
echo "5"
echo 'echo -x Hello World:		'$(echo -x Hello World | cat -e);
echo 'echo -x "Hello World":        	'$(echo -x "Hello World" | cat -e);
echo 'echo -x \"\"Hello World\"\":	'$(echo -x ""Hello World"" | cat -e);
echo "echo -x : "$(echo -x | cat -e);
echo "echo -x \"\": "$(echo -x "" | cat -e);
echo "echo -x \" \": "$(echo -x " " | cat -e);
echo
echo
echo "6"
echo 'Echo Hello World:		'$(Echo Hello World | cat -e);
echo 'Echo "Hello World":        	'$(Echo "Hello World" | cat -e);
echo 'Echo \"\"Hello World\"\":	'$(Echo ""Hello World"" | cat -e);
echo "Echo : "$(Echo | cat -e);
echo "Echo \"\": "$(Echo "" | cat -e);
echo "Echo \" \": "$(Echo " " | cat -e);
echo
echo
echo "7"
echo 'Echo -n Hello World:		'$(Echo -n Hello World | cat -e);
echo 'Echo -n "Hello World":        	'$(Echo -n "Hello World" | cat -e);
echo 'Echo -n \"\"Hello World\"\":	'$(Echo -n ""Hello World"" | cat -e);
echo "Echo -n : "$(Echo -n | cat -e);
echo "Echo -n \"\": "$(Echo -n "" | cat -e);
echo "Echo -n \" \": "$(Echo -n " " | cat -e);
echo
echo
echo "8"
echo 'Echo -n -n Hello World:		'$(Echo -n -n Hello World | cat -e);
echo 'Echo -n -n "Hello World":       '$(Echo -n -n "Hello World" | cat -e);
echo 'Echo -n -n \"\"Hello World\"\":	'$(Echo -n -n ""Hello World"" | cat -e);
echo "Echo -n -n : "$(Echo -n -n | cat -e);
echo "Echo -n -n \"\": "$(Echo -n -n "" | cat -e);
echo "Echo -n -n\" \": "$(Echo -n -n " " | cat -e);
echo
echo
echo "9"
echo 'Echo -nn Hello World:		'$(Echo -nn Hello World | cat -e);
echo 'Echo -nn "Hello World":        	'$(Echo -nn "Hello World" | cat -e);
echo 'Echo -nn \"\"Hello World\"\":	'$(Echo -nn ""Hello World"" | cat -e);
echo "Echo -nn : "$(Echo -nn | cat -e);
echo "Echo -nn \"\": "$(Echo -nn "" | cat -e);
echo "Echo -nn \" \": "$(Echo -nn " " | cat -e);
echo
echo
echo "10"
echo 'Echo -x Hello World:		'$(Echo -x Hello World | cat -e);
echo 'Echo -x "Hello World":        	'$(Echo -x "Hello World" | cat -e);
echo 'Echo -x \"\"Hello World\"\":	'$(Echo -x ""Hello World"" | cat -e);
echo "Echo -x : "$(Echo -x | cat -e);
echo "Echo -x \"\": "$(Echo -x "" | cat -e);
echo "Echo -x \" \": "$(Echo -x " " | cat -e);
#
#
#
#	echo = echo -x = Echo = Echo -nn = Echo -x				(1 = 5 = 6 = 9 = 10)
#	echo -n = echo -n -n = echo -nn = Echo -n = Echo -n -n 	(2 = 3 = 4 = 7 = 8)
# 	
# 	
#	
