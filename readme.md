# Test Problem 

We ask candidates to provide a solution to the enclosed C++ programming question: We're looking for how you break down the scenario and apply OO methods. It shouldn't take more than a few hours to complete.
 
Create a text based Monopoly game using the following guidelines:

* Two players begin the game with: $ or £ 1500 and all properties randomly divided between them
* Each property has a random number of houses on it, 0 - 5 (hotel)
* Players take alternate turns, rolling two dice and moving that number of spaces around the board
* Rents are paid to the other player
* All Chance spaces cost the player $ or £ 50
* All Community Chest spaces move the player back 3 spaces
* Play continues until either one player is broke or 50 turns have been taken
* Use a standard Monopoly US or UK board and property card values

Outputs:

* Initial board configuration (who owns which properties, number of houses)
* Results of each roll 

These guidelines are intentionally incomplete. Please describe and add to the requirements those features and assumptions you feel are necessary to create the solution you wish to present. 

Please send all source code and an executable (either Windows or Linux) back to me. In case you are left without a compiler on your PC, note that Microsoft offers free, but limited editions of their Visual Studio from their webpages: http://www.microsoft.com/express/download/

---

# Steven Yau 13/05/2010

Compiled using MinGw GCC and Code::Blocks IDE

# Assumptions 

* All players can have houses on their properties despite not owning a full set of streets.
* Pressing or landing on Go square means a player will receive $ or £200.
* 50 turns means 50 turns total and not 50 turns per player.
* Properties cannot be mortgaged.
* Properties cannot be brought.
* When a player owns an entire set of properties, they will receive double the standard base rent if no houses have been built.
* This program will be running on a PC-like architecture and OS. If this was on an embedded platform, the memory allocation would be done differently to minimise fragmentation and overflows.
* If the game reaches the turn cap, it is the player who has the most money in the bank that wins which does not include the property values.

# What isn't implemented

* Jail / Go to Jail
* Free Parking
* Utility Companies

# About the Solution

The architecture is a data driven composite design pattern to make it easier to create now board squares and new functionality that isn't just limited to to just Monopoly. More details: http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/

However, the data parsing currently lacks full error checking and isn't particularly robust so it is prone to failing if the formatting in the BoardData.txt is wrong.