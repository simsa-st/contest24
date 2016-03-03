# Problem Statement of Candy Eaters example

The game is played on board of size **n x n**. On some cells there can be several candies (new candies occur during the game). In every turn player can either move to a neighbouring cell or eat a candy.

The server is (more or less) behaving according to [Marathon24 rules](https://marathon24.com/static/attachment/Marathon24_Finals_rules.pdf). During the authentication it accepts any nonempty login and password.

Commands specific for this task:
* GET_INIT &ndash; after sending OK, server responds with one number representing the size of the board. It remains the same during the whole round.
* GET_MY_POS &ndash; server responds with two numbers representing the x and y coordinate (0-based) of the player's position.
* GET_CANDY_COUNT &ndash; server responds with one number representing the number of candies at the current position.
* EAT_CANDY &ndash; in the current turn, eat candy at this position. If ther is no candy at this position, server responds with error.
* MOVE x y &ndash; move to the position [x, y]. It has to be inside of the board and this cell must be a neighbour of the cell where the player currently is.

From the last two commands, only one can be sent during each turn. Players moves are processed in random order. If more players try to eat candy at the same position and there are not enought candies for all of them, only the first few are successful but no error is sent to the remaining players.

Here are the errors the server can return:
* ERROR 1 Incorrect login or password.
* ERROR 3 Unknown command name.
* ERROR 4 Wrong number of arguments.
* ERROR 9 No current round.
* ERROR 101 You can do only one move per turn.
* ERROR 102 Invalid move.
* ERROR 103 No candy at this position.
