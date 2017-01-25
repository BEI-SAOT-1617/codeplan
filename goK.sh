trap 'echo \*\*\* END ; kill -9 $PID ; exit' INT
echo '***** LIST OF PARTITION IDS *****'
PID=`cat listpid`
echo $PID
./a.out $PID
sleep 60
