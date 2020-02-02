#!/bin/bash

if [ $# == 0 ];then
	sudo rmmod hello_drv.ko > /dev/null
	sudo insmod hello_drv.ko > /dev/null
	exit 0
fi

if [ $# == 1 ];then
	if [ $1 == 're' ];then
		sudo rmmod hello_drv.ko > /dev/null
		sudo insmod hello_drv.ko > /dev/null
	fi
        if [ $1 == 'rm' ];then
		sudo rmmod hello_drv.ko > /dev/null
	fi
	if [ $1 == 'in' ];then
		sudo insmod hello_drv.ko > /dev/null
	fi
	if [ $1 == 'pk' ];then
		cat /var/log/syslog
	fi
	exit 0
fi

if [ $# -ge 2 ];then
	if [ $1 == 'in' ];then
		sudo insmod hello_drv.ko $2 $3
		exit 0
	fi
	if [ $1 == 're' ];then
		sudo rmmod hello_drv.ko
		sudo insmod hello_drv.ko $2 $3
		exit 0
	fi
	if [ $1 == 'ps' ];then
		grep $2 /proc/kallsyms | while read tmp
		do
			echo $tmp
		done
	fi
	exit 0
fi
