CC ?= cc

all: malloc1.so malloc2.so malloc3.so

cheri: print_bounds malloc4.so exceed_bounds

malloc1.so: malloc1.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc1.c -o malloc1.so

malloc2.so: malloc2.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc2.c -o malloc2.so

malloc3.so: malloc3.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc3.c -o malloc3.so

print_bounds: print_bounds.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter print_bounds.c -o print_bounds

malloc4.so: malloc4.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc4.c -o malloc4.so

realloc: realloc.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter realloc.c -o realloc

malloc5.so: malloc5.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter -shared -fPIC malloc5.c -o malloc5.so

exceed_bounds: exceed_bounds.c
	${CC} -O3 -g -W -Wall -Wextra -Wno-unused-parameter exceed_bounds.c -o exceed_bounds

clean:
	rm -f *.so
