cmd_/home/ubuntu-bitmain/workspace/module_test/kernel_drv/hello_drv.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/ubuntu-bitmain/workspace/module_test/kernel_drv/hello_drv.ko /home/ubuntu-bitmain/workspace/module_test/kernel_drv/hello_drv.o /home/ubuntu-bitmain/workspace/module_test/kernel_drv/hello_drv.mod.o
