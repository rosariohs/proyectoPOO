# Makefile de P1
# Rosario Heredia Sanchez

VPATH = ../Tests-auto:.

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -pedantic
CPPFLAGS = -DP1 -I ../Tests-auto -I.

all: test-P1-auto test-P1-consola

OBJETOS1 = test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
OBJETOS2 = test-P1-consola.o fecha.o cadena.o


test-P1-auto: $(OBJETOS1)
	$(CXX) $(LDFLAGS) $(OBJETOS1) -o $@

test-P1-consola: $(OBJETOS2)
	$(CXX) $(LDFLAGS) $(OBJETOS2) -o $@

test-P1-auto.o test-P1-consola.o: cadena.hpp fecha.hpp

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

fecha.o: fecha.hpp 
cadena.o: cadena.hpp

checks: check_fecha check_cadena

check_fecha: fecha_check fecha.cpp fecha.hpp
	./fecha_check fecha.cpp -- -std=c++14

check_cadena: cadena_check cadena.cpp cadena.hpp
	./cadena_check cadena.cpp -- -std=c++14


fecha_check cadena_check: 
	${MAKE} -f Make_check.mk $@


.PHONY: clean

clean:
	$(RM) test-P1-auto  test-p1-consola $(OBJETOS1) $(OBJETOS2)  core *~
