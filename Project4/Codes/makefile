main:main.o common.o control.o calculate.o command_deal.o
	g++ main.o common.o control.o calculate.o command_deal.o -o main
main.o:
	g++ -c main.cpp
common.o:
	g++ -c common.cpp
control.o:
	g++ -c control.cpp
calculate.o:
	g++ -c calculate.cpp
command_deal.o:
	g++ -c command_deal.cpp
clean:
	rm main
	rm *.o

