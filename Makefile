CC ?= cc

all: malloc1.so malloc2.so malloc3.so

cheri: print_bounds malloc4.so

malloc1.so: malloc1.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc1.c -o malloc1.so

malloc2.so: malloc2.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc2.c -o malloc2.so

malloc3.so: malloc3.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc3.c -o malloc3.so

print_bounds: print_bounds.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC print_bounds.c -o print_bounds

malloc4.so: malloc4.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc4.c -o malloc4.so

clean:
	rm -f *.so
