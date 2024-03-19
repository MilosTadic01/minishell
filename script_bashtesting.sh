#!/usr/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m'

echo
echo -e ${GREEN}'###<Setup the infile.txt>###'${NC}
echo '$ echo -e '\''banana\napple\nbanana\napple\ncherry'\'' > infile.txt'
echo -e 'banana\napple\nbanana\napple\ncherry' > infile.txt
echo '$ cat infile.txt'
cat infile.txt

echo
echo -e ${GREEN}'###<echo>###'${NC}
echo '$ echo -e'
echo -e

echo
echo -e ${GREEN}'###<echo>###'${NC}
echo '$ echo -x'
echo -x

echo
echo -e ${GREEN}'###<echo multiple space-delimited words>###'${NC}
echo '$ echo banana apple'
echo banana apple

echo
echo -e ${GREEN}'###<echo multiple space-delimited strings>###'${NC}
echo '$ echo '\''banana apple'\'' '\''cherry durian'\'''
echo 'banana apple' 'cherry durian'

echo
echo -e ${GREEN}'###<echo -e before the string>###'${NC}
echo -e '$ echo' ${RED}'-e'${NC} \''banana\\napple'\'
echo -e 'banana\napple'

echo
echo -e ${GREEN}'###<echo -e after the string>###'${NC}
echo -e '$ echo '\''banana\\napple'\' ${RED}'-e' ${NC}
echo 'banana\napple' -e

echo
echo -e ${GREEN}'###<echo w/ invalid option after a valid one>###'${NC}
echo '$ echo -e -x '\''banana\napple'\'
echo -e -x 'banana\napple'

echo
echo -e ${GREEN}'###<echo w/ invalid option before a valid one>###'${NC}
echo '$ echo -x -e '\''banana\napple'\'
echo -x -e 'banana\napple'

echo
echo -e ${GREEN}'###<echo w/ invalid option after a valid one in an options cluster>###'${NC}
echo '$ echo -ex '\''banana\napple'\'
echo -ex 'banana\napple'

echo
echo -e ${GREEN}'###<echo w/ invalid option before a valid one in an options cluster>###'${NC}
echo '$ echo -xe '\''banana\napple'\'
echo -xe 'banana\napple'

echo
echo -e ${GREEN}'###<echo -e /n -E /n>###'${NC}
echo '$ echo -e '\''banana\napple'\' -E '\''banana\napple'\'''
echo -e 'banana\napple' -E 'banana\napple'

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<New file input for uniq disregards the output of sort>###'${NC}
echo '$ < infile.txt cat | sort | < infile.txt uniq > outfile.txt'
< infile.txt cat | sort | < infile.txt uniq > outfile.txt
echo '$ cat outfile.txt'
cat outfile.txt

echo
echo -e ${RED}'###<CONCLUSIONS>###'${NC}
echo 'Any options must come before any arguments.'
echo 'Any invalid option will be interpreted as an argument.'
echo -e 'Fig 4. Shell Grammar in Backus­Naur Form:' ${CYAN}
echo 'cmd [arg]* [ | cmd [arg]* ]*
    [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]'

echo -e ${RED}'###<UNSORTED BITS OF KNOWLEDGE>###'${NC}
echo 'ctrl+d should exit a process. How did I not notice this before?'
echo 'tab character is not ascii tab when it is input on the bas cmd line, its sth special'

echo -e ${NC}

echo
