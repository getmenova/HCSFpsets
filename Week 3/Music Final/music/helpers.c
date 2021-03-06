// Helper functions for music

/*assignment keynotes
helpers.h
In this file, now, are declarations for three functions:

duration, which should take as input as a string a fraction (e.g., 1/4) and return as an int a corresponding number of eigths (2, in this case, since 1/4 is equivalent to 2/8);

frequency, which should take as input as a string a note formatted as

XY (e.g., A4), where X is any of A through G and Y is any of 0 through 8, or

XYZ (e.g., A#4), where X is any of A through G, Y is # or b, and Z is any of 0 through 8,

and return as an int the note’s corresponding frequency, rounded to the nearest integer; and

is_rest, which should return true if its input, a string, represents a rest in our machine-readable format, otherwise false.

helpers.c
And in this file there should be implementations of those three functions, but no! Not yet. That’s where you come in!

Specification
bday.txt
In bday.txt, type the ASCII representation of Happy Birthday, translating its sheet music, above, to the machine-readable representation prescribed herein. You should find that the song begins with:

D4@1/8
D4@1/8
E4@1/4
D4@1/4
G4@1/4
F#4@1/2
helpers.c
is_rest
Complete the implementation of is_rest in helpers.c. Recall that blank lines represent rests in our machine-readable format. And recall that synthesize will call this function in order to determine if one of the lines a user has typed in is indeed blank.

What does it mean for a line to be blank? To answer that question, start by looking at cs50.h itself, wherein get_string is documented:

https://github.com/cs50/libcs50/blob/develop/src/cs50.h

What do the comments atop get_string say that the function returns if a user simply hits Enter, thereby inputting only a "line ending" (i.e., \n)?

When is_rest is subsequently passed such a string, s, how should it (nay, you!) recognize as much?

duration
Complete the implementation of duration in helpers.c. Recall that this function should take as input as a string a fraction and convert it into some integral number of eighths. You may assume that duration will only be passed a string formatted as X/Y, whereby each of X and Y is a positive decimal digit, and Y is, moreover, a power of 2.

frequency
Finally, complete the implementation of frequency in helpers.c. Recall that this function should take as input as a string a note (e.g., A4) and return its corresponding frequency in hertz as an int.

And recall that:

The frequency, f, of some note is 2n/12 × 440, where n is the number of semitones from that note to A4.

Each key on a piano is said to be one semitone, otherwise known as a half step, away from its adjacent neighbor, whether white or black.

The effect of # and b, otherwise known as accidentals, is to raise or lower, respectively, the pitch of a note by one semitone.

In implementing this function, you might find pow and round, both declared in math.h, of interest.





*/
//include proper headers
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"

#define A440 440 //cornerstone key


// TODO boolean - if string is NOT EMPTY -  then it is a  NOT a rest
//if it isn't 0 - then false
// OTHERWISE true

// decide if there's even a note being played first
bool is_rest(string s)
{
    if (strlen(s) != 0)
    {
        return false;
    }

    // a rest
    else
    {
        return true;
    }
}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO split num and dom? need to convert from ASCII form to digit form
    int n = fraction[0] - '0';
    int d = fraction[2] - '0';
    //smallest unit of 'MUSICAL NOTE' is 1/8***
    return 8.0 * (double) n / d; //use double over float in this instance - paras? check Order of ops in C
    //num = numerator den = denominator
//note notation: NOTE + OCTAVE @DURATION ==> duration = num/denom - returns a float ==> 1/4 = .25 * 8
//G4@1/4
//C5@1/4
//G4@1/4
//C4@1/4
//G4@1/4
//C5@1/4
//G4@1/4 */
}


// Calculateing the freakiness of a note
int frequency(string note)
{

    char keysize[3]; //build our note next in the trust tree
    int octave = 0; // set octave to origin

    if (strlen(note) == 2) // Add in support for 'normal' note played - they call them 'natural' notes in music!
    {
        // indicate key size - (2) characters
        keysize[0] = note[0];
        keysize[1] = '\0';

        octave = note[1] - '0'; // convert the octave out of ASCII form and into digits
    }

    else if (strlen(note) == 3) // Add support for sharps and flats - adding 1 more category to keysize
    {

        keysize[0] = note[0]; //see above, add 1 additional placeholder for the accidental
        keysize[1] = note[1];
        keysize[2] = '\0';

        // Convert octave number from ASCII to digit
        octave = note[2] - '0';
    }

    double f = A440; //waypoint for babysteps

    int babysteps = 0;
    switch (toupper((unsigned char) keysize[0]))

    {
        case 'C':
            babysteps = 3;
            break;
        case 'D':
            babysteps = 5;
            break;
        case 'E':
            babysteps = 7;
            break;
        case 'F':
            babysteps = 8;
            break;
        case 'G':
            babysteps = 10;
            break;

        case 'A':
            octave++; //include support for wraparound keys in next octave
            break;
        case 'B':
            babysteps = 2;
            octave++;
            break;

        default: //provide support for gnarly notes
            f = 0;
    }


//if there is a note, decide if it's natural, sharp or flat and adjust accordingly

    if (keysize[1] == '#') //sharp, increase by 1 babystep
    {
        babysteps++;
    }


    else if (keysize[1] == 'b') // case 2, decrease 1 babystep
    {
        babysteps--;
    }


    // support calc for number of babysteps
// Calculates frequency (in Hz) of a note//

//it's the final count(round)
    return round(f * pow(2.0, babysteps / 12.0 + octave - 5.0));
}
// TODO - need notes, accidentals, and octave// Calculates frequency (in Hz) of a note formatted as XY,
// where X is any of A through G and Y is any of 0 through 8,
// or formatted as XYZ, where X is any of A through G, Y is # or b,
// and Z is any of 0 through 8


//mova an octave - up and down - mult freq by 2 or divide freq by 2 - note is a string

/*first char is a letter, if note is a sharp or flat, include accidental - if there is none, then 2nd char is going to be the octave
if there was an accidental then 3rd char is octave

Bb4, XYZ

A4 = 440hz

to change octave just move by 2 -round decimals to nearest integer

//support A# and Ab mult by 2^1/12, can divide or mult by this to get sharp or flat

A# would be 440 * 2 ^ 1/12  - don't forget octave inclusion. Adjust for sharps and flat and first or second.


A/A# and Ab. Then include it.

Semitones.


Which note has which letter B is diff from A. Octave start at C.
*/ //4.17 - implement note categories and
/* trash way of doing it int frequency(string note)
{

/* NOTES:


// notenotation = NOTE CHAR + ACCIDENTAL (#) + or (b) -!!
// duration notation:

The duration of a note, meanwhile, is implied by its shape. For instance,

eighth note, though when adjacent to one or more other eighth notes, they’re often beamed, a la ;

quarter note, the duration of which is twice that of an eighth note;

is a dotted quarter note, the duration of which is three times that of an eighth note;

is a half note, the duration of which is four times that of an eighth note; and

is a whole note, the duration of which is eight times that of an eighth note.

for every semitone up *2^1/12 - incrementing
and every down one semitone *


12 semitones is an octave . mult by 2^12/12 or just by 2!


Divide by frequency of 2^1/12


//octaves


A4 return 440
To change the octave mult by 2
or divide by 2



two octave moves could be 2^x


round to nearest integer


// support sharps and flats


A4 = 440 hz



mult by 2^1/12
div by 2^1/12


a sharp
a flat
then go for octaves

mult or divide by some power of 2




A5



//support all notes

using A# ab

A as starting point - how many various notes away people are


*octaves start at C

piano keyboardfor guidance


c5 is one semitone above b4


three functions

string represents

what accidental

what octave



a4 = 440  up or down


jump a full octave 2

divide it by 2



floating point number  - - round to the nearest integer
*/










