The design of the program:
	For the Y86 emulator, the first thing is to check if the input is correct and if there is -h. If so, print the help message to the terminal. If the format of the input is wrong, complain. 
	Then use FILE pointer to open the input file. I wrote a function called "read" to read the input file one line every time and devide the input string into 3 parts, the specifier, the address and the value and store them into 3 string.
	Then for every line I wrote a switch to check the specifier, and do as the specifier specifies. If the specifier is not any of the case, complain.
	Then for the specifier of ".text" I wrote an individual part of code and leave that part as the last part of the program. I use an array of pointer to emulate the register. I wrote a switch to check the first character of string to determine how long that piece of code need and decode that line and run. And then decode next piece of code.
	At the very end I free the memory space of malloc and close the file and return.

That is my design of my program and I did achieved most of that.  However, in the decoding part, I wrote the code for "nop", "halt", "rrmovl", "irmovl", "mrmovl" and "op1" without"cmpl" successfully. But I cannot come up with a method to decode the rest part of the code and run that in C. So I leave that part of the code empty. I don't know how much point I can get but I have to say I have make my best.
