# tictactoe_bot
Side project to practice C programming.

### Basic Gameplay
The user is first asked if they want to play the game. Then if they answer y the user is asked what level they want to play at; if they don't enter a number between 1 and 3 it defaults to the hardest level. Finally the user then enters a position on the board where they want to make their move. If the position is invalid or already taken they are asked to enter another number.

### The Bot
The Bot that the user plays against uses an implementation of the [MiniMax Algorithm](https://en.wikipedia.org/wiki/Minimax). This algorithm recursively builds a tree of game states and then scores them by who won and how many layers deep the algorithm had to go to get an end result. The easier the level the less levels deep the algorithm goes. 

### Running the Game
If you want to try out the game on your computer here are the steps to get it running.
1. ``` git clone https://github.com/apache8080/tictactoe_bot.git ```
2. ``` make build ```
3. ``` ./tictactoe ``` 

If you run in to any issues running ``` make clean build ``` will clean up the workspace and rebuild the code.
