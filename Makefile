all:
	mkdir -p bin

	make -C foxdb
	make -C test
	
clean:
	rm -rfv bin lib