tetris

This is a game I created with my classmate Timmy(Jinyao) Lu and Ryan Misiak.

Instructions

A game of Quadris consists of a board, 11 columns wide and 15 rows high. Blocks consisting of
four cells (tetrominoes) appear at the top of the screen, and you must drop them onto the board
so as not to leave any gaps. Once an entire row has been filled, it disappears, and the blocks above
move down by one unit.

Getting Started

Install all .h, .cc, and Makefile. Enter $make to compile and then enter $./reversi to play the game on terminal. The following are the commands to play the game:

 "left" moves the current block one cell to the left. If this is not possible (left edge of the board,
or block in the way), the command has no eect.
 "right" as above, but to the right.
 "down" as above, but one cell downward.
 "clockwise" rotates the block 90 degrees clockwise, as described earlier. If the rotation cannot
be accomplished without coming into contact with existing blocks, the command has no eect.
 "counterclockwise" as above, but counterclockwise.
 "drop" drops the current block. It is (in one step) moved downward as far as possible until
it comes into contact with either the bottom of the board or a block. This command also
triggers the next block to appear. Even if a block is already as far down as it can go (as a
result of executing the down command), it still needs to be dropped in order to get the next
block.
 "levelup" Increases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no higher
level, this command has no efect.
 "leveldown" Decreases the difficulty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no lower
level, this command has no effect.
 "norandom" file Relevant only during levels 3 and 4, this command makes these levels non-
random, instead taking input from the sequence file, starting from the beginning. This is
to facilitate testing.
 "random" Relevant only during levels 3 and 4, this command restores randomness in these levels.
 "sequence" file Executes the sequence of commands found in file. This is to facilitate the
construction of test cases.
 "I, J, L, etc." Useful during testing, these commands replace the current undropped block with
the stated block. Heaviness is detemined by the level number. Note that, for heavy blocks,
these commands do not cause a downward move.
 "restart" Clears the board and starts a new game.

Service

If you have any further questions please do not hesitate to contact me by my email, jamesi1998.js@gmail.com, available 24 hours 7 days a week.

© 2017 Enze Si, Timmy(Jinyao) Lu, and Ryan MisiakAll rights reserved.
