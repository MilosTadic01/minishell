#!/usr/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
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
echo -e ${GREEN}'###<>###'${NC}
echo '$ '

echo
echo -e ${GREEN}'###<New file input for uniq disregards the output of sort>###'${NC}
echo '$ < infile.txt cat | sort | < infile.txt uniq > outfile.txt'
< infile.txt cat | sort | < infile.txt uniq > outfile.txt
echo '$ cat outfile.txt'
cat outfile.txt

echo
