#! /bin/zsh

source ~/.zshrc

now=`pwd`
file_path="/home/yzlin/Shells/cdex/scripts/ChangeExistedDir.py"
recover="/home/yzlin/Shells/cdex/recover"
action="/home/yzlin/Shells/cdex/action"
pyerr_tmp="/home/yzlin/Shells/cdex/pyerr.tmp"
# set for recover
echo ${now} > ${recover}

if [ "$1" = "recover" ] || [ "$1" = "-r" ]
then
	previous=`cat < ${recover}`
	cd $previous
else
	case "$#" in
		(0) CEDout=`pythonWin ${file_path} 2> ${pyerr_tmp}`
			;;
		(1) CEDout=`pythonWin ${file_path} $1 2> ${pyerr_tmp}`
			;;
		(2) CEDout=`pythonWin ${file_path} $1 $2 2> ${pyerr_tmp}`
			;;
		(3) CEDout=`pythonWin ${file_path} $1 $2 $3 2> ${pyerr_tmp}`
			;;
		(*) echo "Wrong on commands input..."
	esac

	# judge action
	act=`cat < ${action}`

	if [ $act = "go" ]
	then
		echo "go to ${CEDout}..."
		cd $CEDout
	else
		echo "${CEDout}"
	fi

	pyerr=`cat < ${pyerr_tmp}`
	if [ "$pyerr" != "" ]
	then
	        echo "${pyerr}"
	fi
	rm ${pyerr_tmp}
fi

