# Quick start, a.k.a. from the template light to a working example
In this tutorial we will learn what tools are available in this library, how to start a new project from a template, compile it and run it.

### Code under `c24/`
The code here contains features you can reuse for different contests. You don't have to really understand this code, its usage should be clear from the examples. If you don't know what a particular class or method is doing, check the header file where it is defined.
#### `c24/communication/`
Here are some classes to deal with communication. There is a class `Stream` that provides some convenient methods such as `SendMsg` and `GetMsg` or some more high-level methods such as `GetMsgWithCheck()` (receive a message and check it has the expected value) or `GetVectorOf<T>(int n)` that recevies a message and extracts `n` numbers of type `T` from it. The constructor of class `Stream` expects pointer to `StreamBackendInterface` which is a virtual class that can be implemented to communicate using different protocols. For example, there is an implementation `StreamTcpClient` for communication over TCP.
#### `c24/toolbar/`
Here are some classes that use SFGUI and that provide you with features that will be likely useful on most of the contests. At this point there is just a tool to display the content of your variables but later there will be for example a tool that enables you to change some variables you can later use in your programs (i.e. you can give commands to your program).

### Script `contest24`
You can find a [bash script](../contest24) in this repository that enables you to create new projects from prepared templates, setting default flags or running your code. We will use it in this tutorial.

## Start a new project and get it working
Templates *light* and *stepan-m24* that are the only ones currently present are both created for the contest Marathon24. If you are not familiar with the technical aspects of this contest, read it [here](https://marathon24.com/static/attachment/Marathon24_Finals_rules.pdf).

Now copy the script `contest24` to your `bin/` directory so you can use it easily everywhere (and possible rename it to *c24* as me to save some keystrokes).

Now we are ready to start a new project. Go to your favorite directory and run:
```bash
$ contest24 project new quick_start DIRECTORY_WITH_CONTEST24_PROJECT/templates/light new_folder
```
This will create a project in folder `new_folder` and copy the code from the template *light*. In this new folder you will also find the copy of the `c24` library (taken from `DIRECTORY_WITH_CONTEST24_PROJECT/c24`) and folders `build` and `tmp` for build/temporary files.

Let's compile the project just to check everything is ok. In this template, CMakeLists.txt is present for compiling with `cmake` but there is also a *Makefile* for those who don't want to use `cmake`.

To compile the project with `cmake`, run
```bash
$ cd build
$ cmake ..
$ make
```
This creates executable *quick_start* under `build/bin`.

To compile the project using the *Makefile*, you first need to install the libraries *gflags* and *SFGUI*. Then you can just run `make` from the project directory to compile the code. It creates an executable *quick_start* in this directory.

Note that the code under `c24/` is also compiled rather than used as a library because it might be necessary to make some changes to this code during the contest.

### Understanding the code

Now we will look at the code and try to understand what it does. Lets start with the file `main.cpp`. After the includes, we initialize Easylogging++ with the macro `INITIALIZE_EASYLOGGINGPP`. Now move to the function `main()`. First we parse the command line flags, and then we just create a new instance of class `Game` giving it the host and port we want to connect to. Then we call its method `Run()` with parameters that say if we want to run the visualizer window and toolbar window (these bool variables are specified with flags `--vis` and `--toolbar`).

In the constructor of class `Game`, we initialize class `GameStream` (at this point it is just some black box through which we send the commands and receive the answers to/from the server) and run the method `NewRound()` that does the initialization we want to do at the beginning of each round.

In the method `Run()` we consider two cases. If we don't want to use neither the visualizer nor the toolbar window, we just simply run the method `RunGame()` that controls the game itself. Otherwise we run this method in different thread and in the main thread we start the visualizer and/or toolbar windows. We will get to these windows later.

The `RunGame()` method is very simple, it just periodically calls `Move()` &ndash; the method that decides what move to do (it is empty at this point) and `WaitForNewTurn()` &ndash; method that waits for the new turn to start and detects the beginning of new round.

The class `GameStream` is also very simple. It just wraps the class `Stream` and provides its `LastStatus()` method for checking if there was some error during the communication. Then it defines the commands we want to send to the server and as seen on the method `Wait()`, that is already implemented, it is pretty straightforward.

Now lets return to the visualization. In the method `Run()` we see the main loop that runs while all of the windows that were initially open are still open. Inside the loop we repeat `ProcessEvents()` &ndash; check for the user input from keyboard/mouse and process it &ndash; and `Render()` &ndash; display the game state in the window. In methods `InitVisualizer()` and `InitToolbar()` we just initialize the respective windows and in the latter method we also add a `ToolPrintVariables` to the window and specify we want to print the value of `current_turn_` variable. For more information on this tool, look in the [respective header file](../c24/toolbar/print_variables.h).

### Change the template to a working example for Candy Eaters
Now that we understand what is going on, we can edit the code into a working example for the Candy Eaters game (that is the example game prepared under [examples/candy_eaters](../examples/candy_eaters/)). First read the [problem statement](../examples/candy_eaters/ProblemStatement.md).

Now open the `main.cpp` file again. You can see there is a TODO comment in two places. First when we define the constant `kErrorNoCurrentRound`. We need to set it to the correct value, which is 9 in our example. The second occurence is in the method `NewRound()`. Here we are waiting for the new round to start and we need to put there some command that we want to send to the server periodically until the new round starts. Any command will do so we could put there `game_stream_.Wait()`. But that would mean we would miss the first turn so better choice is to define the method `GetInit()` in `GameStream` and use that instead. It is already in the source code, we just need to uncomment it and add variable `board_size_` among the members of the class `Game`.

Because the Candy Eaters server expects us to authenticate when we connect, we need to do that as well. We can just copy the `GameStream` method from the Candy Eaters example:
```cpp
bool Authenticate(const string& login, const string& password) {
  if (!stream_.GetMsgWithCheck("LOGIN")) return false;
  if (!stream_.SendMsg(login)) return false;
  if (!stream_.GetMsgWithCheck("PASSWORD")) return false;
  return stream_.SendMsgWithCheck(password);
}
```

The server accepts any nonempty string as the login and password, so we can simply call `game_stream_.Authenticate("login", "password");` in the constructor of `Game`.

Now we are prepared to run the game for the first time. First start the server from the Candy Eaters example (make sure you are in the correct directory -- in `build/bin/` subdirectory of the directory where you have the copy of this project):
```bash
./candy_eaters_server --ports=5500
```
And while it's still running, start your client (remember to compile it first):
```bash
./quick_start --port=5500
```
If you kill the server before the client, the server will be unable to bind to the used port for some time, so avoid that.

You can also run the server with visualizer (flag `--vis`) to see that the player is not moving (just as expected). If you run the client with the toolbar window (flag `--toolbar`) you can see the current value of variable `current_turn_`.

Now it's time to start moving. We will implement very easy strategy &ndash; if there is a candy at my position, eat it. Otherwise move in a random direction.

First we need to implement the commands in `GameStream`:
```cpp
bool GetMyPos(int* x, int* y) {
  if (!stream_.SendMsgWithCheck("GET_MY_POS")) return false;
  vector<int> pos = stream_.GetVectorOf<int>(2);
  *x = pos[0]; *y = pos[1];
  return LastStatus().Ok();
}
bool GetCandyCount(int *candy_count) {
  if (!stream_.SendMsgWithCheck("GET_CANDY_COUNT")) return false;
  *candy_count = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}
bool EatCandy() {
  return stream_.SendMsgWithCheck("EAT_CANDY");
}
bool Move(int x, int y) {
  return stream_.SendMsgWithCheck("MOVE " + to_string(x) + " " + to_string(y));
}
```

Now we will create a method of the `Game` class that chooses a random neighbouring cell:
```cpp
void Game::ChooseWhereToMoveRandom(int x, int y, int* new_x, int* new_y) {
  *new_x = *new_y = -1;
  if (x < 0 || x >= board_size_ || y < 0 || y >= board_size_) return;
  while (*new_x < 0 || *new_x >= board_size_ || *new_y < 0 || *new_y >= board_size_) {
    int random_dir = rand() % 4;
    *new_x = x; *new_y = y;
    if (random_dir == 0) ++*new_x;
    if (random_dir == 1) --*new_y;
    if (random_dir == 2) --*new_x;
    if (random_dir == 3) ++*new_y;
  }
}
```

Now we implement the method `Move()` according to the described strategy:
```cpp
void Game::Move() {
  int x, y;
  game_stream_.GetMyPos(&x, &y);
  int candies;
  game_stream_.GetCandyCount(&candies);
  if (candies > 0) game_stream_.EatCandy();
  else {
    int new_x, new_y;
    ChooseWhereToMoveRandom(x, y, &new_x, &new_y);
    game_stream_.Move(new_x, new_y);
  }
}
```

And that's it! If we run the server with visualizer and then our code we should see the player moving according to the intended strategy.

## More `contest24` script features
We can check the configuration for the current project (you need to be somewhere under the project directory):
```bash
$ contest24 config show
CLIENT_BINARY "/tmp/quick_start/quick_start"
CLIENT_DEFAULT_FLAGS "--vis --toolbar"
SERVER_BINARY "/tmp/quick_start/quick_start_server"
SERVER_DEFAULT_FLAGS "--vis"
CLIENT_MEMORY_LIMIT "-1"
SERVER_MEMORY_LIMIT "-1"
```

Of course, the paths will be different in your case. Lets set CLIENT_BINARY and SERVER_BINARY to the correct paths of the respective binaries. In my case, I would run:
```bash
$ contest24 config set CLIENT_BINARY /tmp/new_folder/quick_start
$ contest24 config set SERVER_BINARY /home/gorli/projects/contest24/build/bin/candy_eaters_server
```
You can also change the default flags for the client and server. Now you can run the server/client with:
```bash
$ contest24 server 5500
$ contest24 client --port=5500
```
