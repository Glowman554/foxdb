all:
	mkdir -p bin

	make -C foxdb
	make -C test
	make -C cli
	
clean:
	rm -rfv bin lib