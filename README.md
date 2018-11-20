# pset-4

Whodunit


Implement a program called whodunit that reveals Mr. Boddy’s drawing in such a way that you can recognize whodunit.

Implement your program in a file called whodunit.c in a directory called whodunit.

Your program should accept exactly two command-line arguments: the name of an input file to open for reading followed by the name of an output file to open for writing.

If your program is executed with fewer or more than two command-line arguments, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.

If the input file cannot be opened for reading, your program should inform the user as much, as with fprintf (to stderr), and main should return 2.

If the output file cannot be opened for writing, your program should inform the user as much, as with fprintf (to stderr), and main should return 3.

If the input file is not a 24-bit uncompressed BMP 4.0, your program should inform the user as much, as with fprintf (to stderr), and main should return 4.

Upon success, main should 0.

Recover


Implement a program called recover that recovers JPEGs from a forensic image.

Implement your program in a file called recover.c in a directory called recover.

Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs. + If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, as with  fprintf (to stderr), and main should return 1.

If the forensic image cannot be opened for reading, your program should inform the user as much, as with fprintf (to stderr), and main should return 2.

Your program, if it uses malloc, must not leak any memory.

Resize


Implement a program called resize that resizes (i.e., enlarges) 24-bit uncompressed BMPs by a factor of n.

Implement your program in a file called resize.c in a directory called resize.

Your program should accept exactly three command-line arguments, whereby

the first (n) must be a positive integer less than or equal to 100,

the second must be the name of a BMP to be resized, and

the third must be the name of the resized version to be written.

+ If your program is not executed with such, it should remind the user of correct usage, as with fprintf (to stderr), and main should return 1.

Your program, if it uses malloc, must not leak any memory.
