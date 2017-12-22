if [ $# -lt 3 ] || [ $# -gt 4 ] ; then
	echo 'Run given command with at most given time-out. If it does not finish in time, the command (or the note if given) will be recorded in a given file.'
	echo 'Hit: if a shell script is used as command, it is highly RECOMMAND to use "/bin/sh" or "bash" to start the script'
	echo 'Usage: <time-out> <failed-file> <command> [note]'
	echo 'Example: 3s failed.txt "sleep 4"'
	echo 'Example: 3s failed.txt "sleep 4" "command s4"'
	echo "  <time-out>: support suffix: 's' for seconds (the default), 'm' for minutes, 'h' for hours or 'd' for days"
	echo "  <command>: if there are multiple components like parameters, remember to use \""
	echo "  <note>: if it is given, the note instead of command will be recorded. Remember to use \", if necessary"
	exit 0
fi

NORMAL_TIME=$1
FAILED_FILE="$2"
TASK="$3"
NOTE=""
if [ $# -ge 4 ]; then
	NOTE="$4"
fi

timeout --foreground $NORMAL_TIME $TASK
if [ $? -ge 124 ]; then
  echo "failed"
  if [ -z "$NOTE" ]; then
    echo $TASK >> $FAILED_FILE
  else
    echo $NOTE >> $FAILED_FILE
  fi
fi

