#! /bin/sh

if [ $# -lt 1 ]; then
	echo "Summarize multiple tables into one. The mean value of a row is used as the summarized value of that row in the new table"
	echo "Usage: <files>..."
	exit 1
fi

FILES="$*"
DIR=$(realpath $0)
DIR=$(dirname $DIR)

for f in $FILES; do
	echo x$f;
	python3 $DIR/avg-table.py $f | awk '{print $1}';
#	awk '{print $1}' $f;
done > /tmp/$$.txt

python3 $DIR/make-table.py /tmp/$$.txt 

