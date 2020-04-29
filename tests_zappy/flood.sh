#/bin/sh

if [ $1 ] && [ $2 ] && [ $3 ] && [ $4 ]
then
    trap '/bin/kill -9 `cat /tmp/flood2pids` 2> /dev/null;exit' 2 3
    rm /tmp/flood2pids
    i=1
    while [ $i -le $4 ]
    do
	nc -vv $1 $2 >/dev/null << EOF &
$3
`cat floodfile`
EOF
	echo $! >> /tmp/flood2pids
	i=$(($i+1))
    done
    wait `cat /tmp/flood2pids`
    echo "Flooding done!"
else
    echo "This script allows to flood the zappy server with many clients at the same time"
    echo "Usage : $0 host port team nb_clients"
fi
