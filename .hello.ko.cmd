cmd_/home/lazariev-study/AK_LABS/lab7/hello.ko := ccache arm-linux-gnueabihf-ld -r  -EL -z noexecstack  -T ./scripts/module-common.lds -T ./arch/arm/kernel/module.lds  --build-id  -o /home/lazariev-study/AK_LABS/lab7/hello.ko /home/lazariev-study/AK_LABS/lab7/hello.o /home/lazariev-study/AK_LABS/lab7/hello.mod.o ;  true