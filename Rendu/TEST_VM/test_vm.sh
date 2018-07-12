#!/bin/sh ******************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    script_test_vm.sh                                .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/12 19:03:24 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/07/12 19:03:24 by clcreuso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NC='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
FILES=$(ls -1 ./Champs)

if [ ! -d ./MCOREWARE_OUTPUT ]; then
	mkdir ./MCOREWARE_OUTPUT
fi

if [ ! -d ./RCOREWARE_OUTPUT ]; then
	mkdir ./RCOREWARE_OUTPUT
fi

if [[ $1 = "clear" ]]; then
	rm -rf ./RCOREWARE_OUTPUT
	rm -rf ./MCOREWARE_OUTPUT
	printf "The directory are clear.\n"
	exit 1
fi

if [[ -z $1 ]] || ! echo $1 | egrep -q '^[0-9]+$' ; then
    printf "usage: sh $0 \"nb >= 0\" || \"clear\"\n"
    exit 0
fi

for P1 in $FILES
do

	NAME1=$(echo $P1 | rev | cut -c5- | rev)

	for P2 in $FILES
	do

		NAME2=$(echo $P2 | rev | cut -c5- | rev)

		OUTPUT="${NAME1}_vs_${NAME2}.output"

		./corewar ./Champs/$P1 ./Champs/$P2 -d $1 > ./MCOREWARE_OUTPUT/$OUTPUT
		./r_corewar ./Champs/$P1 ./Champs/$P2 -d $1 > ./RCOREWARE_OUTPUT/$OUTPUT

		DIFF=$(diff ./RCOREWARE_OUTPUT/$OUTPUT ./MCOREWARE_OUTPUT/$OUTPUT)

		if [ "$DIFF" = "" ]; then
			printf "${GREEN}$NAME1 VS $NAME2 ✔ ${NC}\n"
		else
			printf "${RED}$NAME1 VS $NAME2 ✘ ${NC}\n"
			read -p "Press any key to continue... " -n1 -s
		fi

	done

done
