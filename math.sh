#!/bin/bash -
if [ $# -ne 2 ]; then
    echo "Usage:"
    echo "$0 a+b 20"
    exit 1
fi

RESULT=$(./math $1 $2)
if [ $? -ne 0 ]; then
    echo "ERROR"
    exit
fi

echo  "${RESULT}"
echo "Print?"
read YESNO
if [ $YESNO = "yes" ]; then
    echo "${RESULT}" | \
    enscript --no-header \
	     --margins=72:72:72:72 \
		 --font=Courier16 \
         --media=Letter \
         --output=- \
         | lpr 
fi
