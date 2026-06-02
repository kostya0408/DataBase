
all:
	mkdir build
	cd build && cmake ..
	cd build && cmake --build .

start:
	cd build && ./MyExe
	

clean:
	rm -rf build
