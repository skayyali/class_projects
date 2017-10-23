#!/bin/bash
INFILE=$1
COUNTER=1
TAG=1
INDEX=1
ZERO=0
BACKUPS[0]=$INFILE$COUNTER
MAX=$4
if [ -e $INFILE ]
then
	DIRFILE=$2
	if [ -d $DIRFILE ]
	then
		cp $INFILE $DIRFILE/$INFILE$COUNTER
		while [ 1 ]
		do
			sleep $3
			DIFF=$(diff $INFILE $DIRFILE/$INFILE$TAG)
			echo $DIFF > tmp-message
			if [ "$DIFF" != "" ]
			then
				if [ $COUNTER -eq $MAX ]
				then
					rm $DIRFILE/$INFILE$INDEX
					let INDEX=INDEX+1
					let COUNTER=COUNTER-1
				fi
				let TAG=TAG+1
				cp $INFILE $DIRFILE/$INFILE$TAG
				mail -s "Backup Script" $USER < tmp-message
				let COUNTER=COUNTER+1
			fi
		done
	else
		mkdir -p $DIRFILE
		cp $INFILE $DIRFILE/$INFILE$COUNTER
		while [ 1 ]
		do
			sleep $3
			DIFF=$(diff $INFILE $DIRFILE/$INFILE$COUNTER)
			echo $DIFF > tmp-message
			if [ "$DIFF" != "" ]
			then
				if [ $COUNTER -eq $MAX ]
				then
					rm $DIRFILE/$INFILE$INDEX
					let INDEX=INDEX+1
					let COUNTER=COUNTER-1
				fi
				let TAG=TAG+1
				cp $INFILE $DIRFILE/$INFILE$TAG
				mail -s "Backup Script" $USER < tmp-message
				let COUNTER=COUNTER+1
			fi
		done
		
	fi
else
	echo "File not found"
fi
echo "Done?"

