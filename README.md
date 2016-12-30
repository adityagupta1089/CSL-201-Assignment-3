# Instructions

First enter "src"

To build -> "make"
To run -> "make run"'

Note: For problem 2 only 1 pattern is required.

# Questions:
1. [20 marks] In this assignment you need to implement and analyze a string matching
algorithm. Given a text string T[0...n1]
and a pattern string P[0...m1],
your program
should print location (index) of all the occurrences of P in T.
Examples 1
Input 1: T = “A man's ego is the fountainhead of human progress.”
P = “ego”
Output:
Pattern found at index 8
Examples 2
Input 1: T = “AABAACAADAABAAABAA”
P = “AABA”
Output:
Pattern found at index 0
Pattern found at index 9
Pattern found at index 13
A naive solution to this problem is exhaustive search using string comparison method at
each index of the input string. This method would be O(mn). A better approach is to use
Rabin–Karp algorithm. The Rabin–Karp algorithm works as follows:
a. Hash all the substrings of size m, starting at index 0.
b. Hash P and compare its hash value with all the hashes calculated in step a.
c. If the hash values match, you further compare to see if the strings also match.
You can find the details of the algorithm and a C++ implementation here:
http://www.geeksforgeeks.org/searchingforpatternsset3rabinkarpalgorithm/
You are allowed to use this code as your starting point.
As you can see, in the worst case all substrings of T can have the same hash value as
P. Hence, the worst case time is still O(mn). But in practise, RabinKarm
Algorithm is
much faster.
You task is to implement the RabinKarp
algorithm using: (1) all four hash codes
(Integer casting, Component sum, Polynomial sum, Cyclic sum) and (2) all three hash
functions (Division, MAD, Multiplication). You can use linear probing to handle
collisions. For each of the cases above (there will be 12), count:
● False positives. The number of times hash value matches but not the actual
string.
● Comparisons: The number of string comparisons including the one’s that return
true.
Input will be given as a raw text file. The pattern will be given to you during the demo.
The output should be two 4X3 matrices. You should display as well as store the results
in a file named EntryNumOutput1.txt.
2. [10 marks] Modify the the above algorithm (and program) to be able to search for
incomplete words. You would like to type in something like ?orcius and have the
program match this pattern quickly to the correct answer Porcius. What modifications
are needed in the RabinKarp
algorithm for this to work? You will take input from the
user and display output at run time. Not “?” denotes the missing alphabet.
