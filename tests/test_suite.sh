#!/bin/bash

# Usage : ./check.sh | less -r
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -I . *.c -o hsh
function run_check()
{
    echo "--> [" $1 "] <--"
    chars1=$(wc -m < 0_hsh)
    chars2=$(wc -m < 0_sh)
    if diff 0_hsh 0_sh >/dev/null; then
        echo -e "\e[32mSuccess\e[0m"
    else
        echo -e "\e[31mFailed\e[0m"
        echo -e "\e[0m[Got]\e[31m"
        cat 0_hsh
        echo -e "\e[0m[" $chars1 "Chars]\e[31m"
        echo -e "\e[0m[Expected]\e[31m"
        cat 0_sh
        echo -e "\e[0m[" $chars2 "Chars]\e[0m"
    fi
    rm 0_hsh 0_sh;
    echo "************************************"
}
command1=$(echo "ls" | ./hsh 2>&1)
command2=$(echo "ls" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""ls""
command1=$(echo "/bin/ls" | ./hsh 2>&1)
command2=$(echo "/bin/ls" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""/bin/ls""
command1=$(echo "/bin/ls -l" | ./hsh 2>&1)
command2=$(echo "/bin/ls -l" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""ls" with "-l" option"
command1=$(echo "/bin/ls -l /tmp" | ./hsh 2>&1)
command2=$(echo "/bin/ls -l /tmp" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""ls" with "-l" and "/tmp" option"
command1=$(echo "echo /bin/ls" | ./hsh 2>&1)
command2=$(echo "echo /bin/ls" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""echo""
echo -e "This is a\n text" > impossible_name.abcd
command1=$(echo "cat impossible_name.abcd" | ./hsh 2>&1)
command2=$(echo "cat impossible_name.abcd" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check ""cat""
rm -f impossible_name.abcd
echo -e "This is a\n text" > impossible_name.abcd
command1=$(echo "cat impossible_name.abcd" | ./hsh 2>&1)
command2=$(echo "cat impossible_name.abcd" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check "# "exit""
rm -f impossible_name.abcd
command1=$(echo "./ls" | ./hsh 2>&1)
command2=$(echo "./ls" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check "./ls"
command1=$(echo "." | ./hsh 2>&1)
command2=$(echo "." | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check "."
command1=$(echo "BLAbla" | ./hsh 2>&1)
echo "$command1" > 0_hsh
echo "./hsh: 1: BLAbla: not found" > 0_sh
run_check "command not found"
command1=$(echo -e "\n" | ./hsh 2>&1)
command2=$(echo -e "\n" | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check "\n"
command1=$(echo -e "                        " | ./hsh 2>&1)
command2=$(echo -e "                        " | sh 2>&1)
echo "$command1" > 0_hsh
echo "$command2" > 0_sh
run_check "          <spaces>              "
#command1=$(echo "env" | ./hsh 2>&1)
#command2=$(echo "env" | sh 2>&1)
#echo "$command1" > 0_hsh
#echo "$command2" > 0_sh
#run_check "env"
echo "-->" Check documentation
betty-doc *.c *.h
echo "-->" Check style
betty-style *.c *.h
