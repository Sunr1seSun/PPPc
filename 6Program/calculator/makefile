calculator.exe:calculator.o Token_stream.o Token.o
	g++ -o .\calculator .\calculator.o .\Token_stream.o .\Token.o
	del *.o
	.\calculator.exe
calculator.o:calculator.cpp
	g++ -c .\calculator.cpp
Token_stream.o:Token_stream.cpp
	g++ -c .\Token_stream.cpp
Token.o:Token.cpp
	g++ -c .\Token.cpp