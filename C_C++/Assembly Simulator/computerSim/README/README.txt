NAME: Ben Schoeler & Thomas Yu & Luke Spieler
=============================================
CLASS: ECE 2524
===============
DATE: 12/12/2012
================
TITLE: Assembly Compiler/Simulator/Interpreter/Assembler)
============================================================================



REQUIRED PACKAGES
=================
* g++  
* pandoc (for pdf)  
* markdown (for html)  
* texlive-latex3 (for pdf)  

ex: "sudo apt-get install g++ pandoc markdown textlive-latex3"




TO CREATE THE README IN HTML OR PDF:
------------------------------------
cd to the directory that contains this file.  

there are several options for making the readme:  

1) 'make html' will produce an html version of the readme  
2) 'make pdf' will produce a pdf version of the readme  
3) 'make preview' will preview the readme in whatever editor is
defined in the
EDITOR environment variable  
4) 'make all' or 'make' will make both the html file and the PDF



HOW TO COMPILE APPLICATION
--------------------------
1) cd to the working directory that contains the "computerSim.pro" file  
2) >> "qmake"  
3) >> "make"  
4) >> "./computerSim"  
5) To delete all generated files: >> "make distclean"


GENERAL USAGE
-------------
This program is a 'pseudo' Assembly Language Compiler/Simulator/Interpreter/Assembler.  
It recognizes many different Assembly Language commands.  They are listed below:

1) LOAD <hex-data-address> [loads the value from the memory address <hex-data-address> to the accumulator]  
2) STORE <hex-data-address> [stores the value in the accumulator to the memory address <hex-data-address>]  
3) ADDV <decimal-number> [adds the number to the value currently stored in the accumulator]  
4) ADD <hex-data-address> [adds the value stored at the address specified to the value in the accumulator]  
5) BGTZ <decimal-instruction-address> [sets the PC to the value given by the <instruction address> to the value currently in the accumulator only if the value in the accumulator is > 0.  If the value is not > 0, then the PC is incremented by 1]  
6) NOP [does nothing but increment the PC by 1]  
7) CLEAR [sets the value in the accumulator to 0]  
8) HALT [halts the Compiler/Simulator/Interpreter/Assembler.  This should usually be the last instruction of a program]  
9) OUT [outputs a string to the output box in the GUI.  %A represents the value in the accumulator.  For example if the value in the accumulator was 20, the instruction OUT "The value in the accumulator is %A" would print out "The value in the accumulator is 20."  
10) LOADA [this takes the value in the accumulator to be an address in data memory and loads the value at said address into the accumulator]  
11) STOREA <hex-data-address> [this takes the value stored at the data address specifies and treats it as another address.  It then stores the value in the accumulator at the address given by the second address]

EXTRA CAPABILITIES
------------------

1) Single Breakpoint

Set a breakpoint at any line of the instruction memory.  
First, use the arrows to select the line desired.  Then click the 'click to set' button.
When Run is clicked next, the program will run to the desired Breakpoint that was set.
The BP can then we set again in the same manner.  The BP will reset on clear or reset buttons.
The BP must be in a valid range in program memory for it to work in a correct manner.

2) Reset Button

Reinitializes the PC, ACC, and data memory to 0.  Also, if a HALT instruction has been run, it takes it out of the HALT'ed state.  The user can then rerun the program already loaded.

3) Clear Button

Does the same as the reset button but also resets the instruction memory.

4) Interpreter

Allows the user to input assembly function one-by-one if an input file is not provided.  The instruction must be valid in order to be run.  By pressing return or enter, the instruction will be sent to the compiler.

5) Save States

Allows the user to save the current instruction memory into a text editor.  The contents of the text editor can be written to or retrieved from.

6) File Input/Output

Existing instruction input files can be used.  To load a file, hover over the menu bar and click file->load. Saving a file will take the contents of the text editor and place it into a predefined file called "saveFile" in the source code directory


