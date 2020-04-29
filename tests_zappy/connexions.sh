#!/bin/sh

if [ "$1" ] && [ "$2" ] && [ "$3" ] && [ "$4" ]
then
    i=1
    while [ $i -le $4 ]
    do
	echo "Connecting client $i..."
	nc -vv "$1" "$2" <<EOF > /dev/null
$3
EOF
	i=$(($i+1))
    done
else
    echo "This short program makes many connections to your zappy server"
    echo "Usage : $0 host port team number_of_connections"
fi