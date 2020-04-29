#!/bin/bash
#
# Shitty debug program made by siami_a, feel free to improve.
#


if [ "$1" ]
then
    ulimit -c unlimited
    i=1
    while true
    do
	echo "Launching your program, quit with Control + C ;)"
	valgrind --leak-check=full --show-reachable=yes $1 > output.$i.log 2> debug.$i.log&
	wait $!
	echo "Program exited! Did you segfault noob? Relaunching..."
	i=$(($i+1))
    done
else
    echo "Usage : $0 \"command_to_launch\""
fi