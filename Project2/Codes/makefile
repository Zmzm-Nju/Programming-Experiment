main:main.o function.o cp.o wc.o sh.o man.o cat.o cmp.o 
	g++ main.o function.o cp.o wc.o sh.o man.o cat.o cmp.o -o shell
main.o:main.cpp 
	g++ -g -c main.cpp
function.o:function.cpp 
	g++ -g -c function.cpp
cp.o:cp.cpp
	g++ -g -c cp.cpp
wc.o:wc.cpp
	g++ -g -c wc.cpp
sh.o:sh.cpp
	g++ -g -c sh.cpp
man.o:man.cpp
	g++ -g -c man.cpp
cat.o:cat.cpp
	g++ -g -c cat.cpp
cmp.o:cmp.cpp
	g++ -g -c cmp.cpp


clean:
	rm *.o
	rm shell


