// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.
// INIT SCREEN TO WHITE
(WHITE)
	@8192
	D=A
	@I
	M=D
(WHITE1)
	@I
	D=M
	@SCREEN
	D=D+A
	A=D
	M=0
	@I
	M=M-1
	D=M
	@WHITE1
	D;JGT
	
(LISTEN)
	@KBD
	D=M
	@LISTEN
	D;JEQ

(BLACK)
	@8192
	D=A
	@I
	M=D
(BLACK1)
	@I
	D=M
	@SCREEN
	D=D+A
	A=D
	M=1
	@I
	M=M-1
	D=M
	@BLACK1
	D;JGT

(LISTEN1)
	@KBD
	D=M
	@WHITE
	D;JEQ
	@BLACK
	0;JMP
	
	
