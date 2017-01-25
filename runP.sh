>listpid
xterm -e ./main_Control  &
xterm -e ./main_PM  &
xterm -e ./main_Com_ST  &
echo '***** WAITING FOR INSTALL TO COMPLETE  *****'
for i in `seq 20`
do
 sleep 1
 echo -n '*-'
done
echo   
echo "Liste des pid"
ps | grep -e xterm | grep -v grep | awk '{ print $1 }' > listpid
echo '***** LIST OF PROCESSES *****'
cat listpid

xterm -e ./goK.sh
