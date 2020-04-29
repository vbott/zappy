#!/bin/sh

if [ "$1" ] && [ "$2" ] && [ "$3" ] && [ "$4" ]
then
    trap '/bin/kill `cat /tmp/floodpids` 2> /dev/null;exit' 2 3
    i=1
    dd if=/dev/urandom of=/tmp/zappyrandom bs=512 count=10
    echo $3 > /tmp/zappyshit
    cat /tmp/zappyrandom >> /tmp/zappyshit
    rm /tmp/floodpids
    while [ $i -le $4 ]
    do
	echo "Connecting client $i..."
	nc -vv "$1" "$2" < /tmp/zappyshit > /dev/null &
	echo $! >> /tmp/floodpids
	i=$(($i+1))
    done
    wait `cat /tmp/floodpids`
    echo "Flooding done!"
else
    echo "This short program makes many connections to your zappy server with random shit inside"
    echo "Usage : $0 host port team number_of_connections"
fi
