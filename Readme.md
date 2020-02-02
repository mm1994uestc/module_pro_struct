sudo mknod /dev/hello_drv c 111 0  
sudo insmod hello_drv.ko  
cat /var/log/sys_log  
sudo rmmod hello_drv.ko  
ls -al /dev/ | grep hello  
sudo ./main /dev/hello  
sudo insmod hello_drv.ko param_str='Hello_World!' param_num=888 # insmod the hello-drv with some params(If not,the default value will be use!)  
ls -al /sys/module/hello_drv/parameters/  
cat /sys/module/hello_drv/parameters/param_num  
cat /sys/module/hello_drv/parameters/param_str  
modinfo hello_drv # show the basic infomations of the hello_drv module  
