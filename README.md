# :ghost: GHOST :ghost:
### who you gonna call? ghostbusters...
Final project written in collaboration for our C systems level programming class.

# Project Name
Ghost Game

# Team Members and class period
[Fabiha](github.com/tfabiha), [Meredith](github.com/meredeath), and [Milan](github.com/MilanHaiman) pd. 4

## Table of Contents
1. [Project Description](#project-description)
2. [Required Libraries](#required-libraries)
3. [Installing Libraries](#installing-libraries)
4. [How to Use](#how-to-use)
5. [Bugs](#bugs)

## Project Description
We are coding the game Ghost in C. It is a word based game where a player contributes a single letter or chooses
 to challenge the previous previous player per turn, all in the premise of avoiding completing a legal word from the
letters contributed thus far while making sure that the letters thus far forms the fragment of a legal word.
#### More detailed instructions are given in-game. You may read them in the option given on the loading screen.

## Required Libraries
None

## Installing Libraries
Since there are no required libraries, you don't need to install any to get our project to work.

## How to Use
#### (Instructions provided only in bash)
1. In the terminal, after cloning the repository, run:
~~
$ make
~~

## Bugs
 * there is no input parsing, so if you try entering a whole word it won't give you an error, it'll just enter the first letter of the word you tried to enter
 * the game only supports functionality for two players at the moment
 