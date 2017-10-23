#!/bin/bash
PASSWORD=$1
if [ -e $1 ]
then
	PASSSTR=$(cat $1)
	STRLEN=${#PASSSTR}
	if [ $STRLEN -gt 6 ] && [ $STRLEN -lt 32 ]
	then
		SCORE=$STRLEN
		if egrep [#$+%@] $1 > /dev/null
		then
			let SCORE=SCORE+5
		fi

		if egrep [0-9] $1 > /dev/null
		then
			let SCORE=SCORE+5
		fi

		if egrep [A-Za-z] $1 > /dev/null
		then
			let SCORE=SCORE+5
		fi

		if egrep "([A-Za-z0-9])\1+" $1 > /dev/null
		then
			let SCORE=SCORE-10
		fi

		if egrep "[a-z]{3}" $1 > /dev/null
		then
			let SCORE=SCORE-3
		fi
		if egrep "[A-Z]{3}" $1 > /dev/null
		then
			let SCORE=SCORE-3
		fi
		if egrep "[0-9]{3}" $1 > /dev/null
		then
			let SCORE=SCORE-3
		fi

		echo "Password Score: $SCORE"
	else
		echo "Error: Password length invalid"	
	fi
else
	echo "File not found"
fi
