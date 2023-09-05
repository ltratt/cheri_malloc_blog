all: malloc1.so malloc2.so malloc3.so

malloc1.so: malloc1.c
	cc -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc1.c -o malloc1.so

malloc2.so: malloc2.c
	cc -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc2.c -o malloc2.so

malloc3.so: malloc3.c
	cc -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc3.c -o malloc3.so

clean:
	rm -f *.so
