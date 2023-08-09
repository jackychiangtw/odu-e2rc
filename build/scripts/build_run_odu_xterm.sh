#!/bin/bash

d=`date +"%m%d_%H%M_odu"`
ODU_PATH=/home/oran/slice_sch/l2
#ODU_PATH=/home/oran/Dennis/l2

# Build odu
cd $ODU_PATH/build/odu

if [ "$1" == "-all" ];
then
	make clean_all
	make odu MACHINE=BIT64 MODE=FDD
	make cu_stub MACHINE=BIT64 NODE=TEST_STUB MODE=FDD
	make ric_stub MACHINE=BIT64 NODE=TEST_STUB MODE=FDD

else
	make clean_odu
	make odu MACHINE=BIT64 MODE=FDD
fi

# Run odu
cd $ODU_PATH/bin
xterm -hold -e "cd cu_stub; ./cu_stub" &
sleep 3
xterm -hold -e "cd ric_stub; ./ric_stub" &
sleep 3
cd odu

if [ "$1" == "-gdb" ] || [ "$2" == "-gdb" ];
then
	echo "Start odu with gdb"
	gdb ./odu
else
	echo "Start record '$d.log' log"
	./odu > $ODU_PATH/../log/$d.log
fi


