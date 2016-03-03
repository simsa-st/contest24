# Quick start, a.k.a. from the template light to a working example
In this tutorial we will learn what tools are available in this library, how to start a new project from a template, compile it and run it.

### Code under <code>c24/</code>
The code here contains features you can reuse for different contests. You don't have to really understand this code, its usage should be clear from the examples. If you don't know what a particular class or method is doing, check the header file where it is defined.
#### <code>c24/communication/</code>
Here are some classes to deal with communication. There is a class <code>Stream</code> that provides some convenient methods such as <code>SendMessage</code> and <code>GetMessage</code> or some more high-level methods such as <code>GetMessageWithCheck()</code> (receive a message and check it has the expected value) or <code>GetVectorOf\<T\>(int n)</code> that recevies a message and extracts <code>n</code> numbers of type T from it. The constructor of class <code>Stream</code> expects pointer to <code>StreamBackendInterface</code> which is a virtual class that can be implemented to communicate using different protocols. For example, there is an implementation <code>StreamTcpClient</code> for communication over TCP.
#### <code>c24/toolbar/</code>
Here are some classes that use SFGUI and that provide you with features that will be likely useful on most of the contests. At this points there is just a tool to display the content of your variables but later there will be for example a tool that enables you to change some variables you can later use in your programs (i.e. you can give commands to your program).

### Script <code>contest24</code>
You can find a [bash script](../contest24) in this repository that enables you to create new projects from prepared templates, managing the projects, setting default flags or running your code. We will use it in this tutorial.

## Start a new project and get it working
Templates *light* and *stepan-m24* that are the only ones currently present are both created for the contest Marathon24. If you are not familiar with the technical aspects of this contest, read it [here](https://marathon24.com/static/attachment/Marathon24_Finals_rules.pdf).

Now copy the script <code>contest24</code> to your <code>bin/</code> directory so you can use it easily everywhere (and possible rename it to *c24* as me to save some keystrokes) and edit the variables on the first few lines as explained in the script (you have to specify where is you copy of the contest24 project and where some configuration files can be stored).

Now we are ready to start a new project. Go to your favorite directory and run:
<pre><code>$ c24 project new quick_start new_folder light</code></pre>
This will create a project in folder <code>new_folder</code> and copy the code from the template *light*. In this new folder you will also find the copy of the <code>c24</code> library and folders <code>build</code> and <code>tmp</code> for build/temporary files.

Let's compile the project just to check everything is ok. In this template, CMakeLists.txt is present for compiling with <code>cmake</code> but there is also a *Makefile* for those who don't want to use <code>cmake</code>. So you can just run <code>make</code> from the project directory to compile the code and create an executable *quick_start*. The code under <code>c24/</code> is also compiled rather than used as a library because it might be necessary to make some changes to this code during the contest.

### Understanding the code

Now we will look in the code and try to understand what it does. Lets start in the function <code>main()</code> of the file <code>main.cpp</code>. After we initialize google logging and parse the command line flags, we just create a new instance of class <code>Game</code> giving it the host and port we want to connect to. Then we call its method <code>Run()</code> with parameters that say if we want to run the visualizer window and toolbar window (these bool variables are specified with flags <code>--vis</code> and <code>--toolbar</code>).

In the constructor of class <code>Game</code>, we initialize class <code>GameStream</code> (at this point it is just some black box through which we send the commands and receive the answers to/from the server) and run the method <code>NewRound()</code> that does the initialization we want to do at the beginning of each round.

In the method <code>Run()</code> we consider two cases. If we don't want to use neither the visualizer nor the toolbar window, we just simply run the method <code>RunGame()</code> that controls the game itself. Otherwise we run this method in different thread and in the main thread we start the visualizer and/or toolbar windows. We will get to the windows later.

The <code>RunGame()</code> method is very simple, it just periodically calls <code>Move()</code> &ndash; the method that decides what move to do (it is empty at this point) and <code>WaitForNewTurn()</code> &ndash; method that waits for the new turn to start and detects the beginning of new round.

The class <code>GameStream</code> is also very simple. It just wraps the class <code>Stream</code> and provides its <code>LastStatus()</code> method for checking if there was some error during the communication. Then it defines the commands we want to send to the server and from the method <code>Wait()</code>, that is already implemented, we see it is pretty straightforward.

Now lets return to the visualization. In the method <code>Run()</code> we see the main loop that runs while all of the windows that were initially open are still open. Inside the loop we repeat <code>ProcessEvents()</code> &ndash; check for the user input from keyboard/mouse and process it &ndash; and <code>Render()</code> &ndash; display the game state in the window. In methods <code>InitVisualizer()</code> and <code>InitToolbar()</code> we just initialize the respective windows and in the latter method we also add a <code>ToolPrintVariables</code> to the window and say we want to print the value of <code>current_turn_</code> variable. For more information about this tool, look in the [respective header file](../c24/toolbar/print_variables.h).

### Change the template to a working example for Candy Eaters
Now that we understand what is going on, we can edit the code into a working example for the Candy Eaters game (that is the example game programmed under [examples/candy_eaters](../examples/candy_eaters/)). First read the [problem statement](../examples/candy_eaters/ProblemStatement.md).

Now open the <code>main.cpp</code> file again. You can see there is a TODO comment in two places. First when we define the constant <code>kErrorNoCurrentRound</code>. We need to set it to the correct value, which is 9 in our example. The second occurence is in the method <code>NewRound()</code>. Here we are waiting for the new round to start and we need to put there some command that we want to send to the server periodically until the new round starts. Any command will do so we could put there <code>game_stream_.Wait()</code>. But that would mean we would miss the first turn so better choice is to define the method <code>GetInit()</code> in <code>GameStream</code> and use that instead. It is already in the source code, we just need to uncomment it and add variable <code>board_size_</code> among the members of the class <code>Game</code>.

Because the Candy Eaters server expects us to authenticate when we connect, we need to do that as well. We can just copy the <code>GameStream</code> method from the Candy Eaters example:
<pre><code>bool Authenticate(const string& login, const string& password) {
  if (!stream_.GetMessageWithCheck("LOGIN")) return false;
  if (!stream_.SendMessage(login)) return false;
  if (!stream_.GetMessageWithCheck("PASSWORD")) return false;
  return stream_.SendMessageWithCheck(password);
}</code></pre>

The server accepts any nonempty string as the login and password, so we can simply call <code>game_stream_.Authenticate("login", "password");</code> in the constructor of <code>Game</code>.

Now we are prepared to run the game for the first time. First start the server from the Candy Eaters example (make sure you are in the correct directory -- in <code>build/bin/</code> subdirectory of the directory where you have the copy of this library):
<pre><code>./candy_eaters_server --ports=5500 --logtostderr</code></pre>
And while it's still running, start your client (after you compile it again):
<pre><code>./quick_start --port=5500 --logtostderr</code></pre>
If you kill the server before the client, the server will be unable to bind to the used port for some time.

You can also run the server with visualizer (flag <code>--vis</code>) to see that the player is not moving as expected. If you run the client with the toolbar window (flag <code>--toolbar</code>) you can see the current value of variable <code>current_turn_</code>.

Now it's time to start moving. We will implement very easy strategy &ndash; if there is a candy at my position, eat it. Otherwise move in a random direction.

First we need to implement the commands in <code>GameStream</code>:
<pre><code>bool GetMyPos(int* x, int* y) {
  if (!stream_.SendMessageWithCheck("GET_MY_POS")) return false;
  vector&lt;int&gt; pos = stream_.GetVectorOf&lt;int&gt;(2);
  *x = pos[0]; *y = pos[1];
  return LastStatus().Ok();
}
bool GetCandyCount(int *candy_count) {
  if (!stream_.SendMessageWithCheck("GET_CANDY_COUNT")) return false;
  *candy_count = stream_.GetVectorOf&lt;int&gt;(1)[0];
  return LastStatus().Ok();
}
bool EatCandy() {
  return stream_.SendMessageWithCheck("EAT_CANDY");
}
bool Move(int x, int y) {
  return stream_.SendMessageWithCheck("MOVE " + to_string(x) + " " + to_string(y));
}</code></pre>

Now we will create a method of the <code>Game</code> class that chooses a random neighbouring cell:
<pre><code>void Game::ChooseWhereToMoveRandom(int x, int y, int* new_x, int* new_y) {
  *new_x = *new_y = -1;
  if (x < 0 || x >= board_size || y < 0 || y >= board_size_) return;
  while (*new_x < 0 || *new_x >= board_size_ || *new_y < 0 || *new_y >= board_size_) {
    int random_dir = rand() % 4;
    *new_x = x; *new_y = y;
    if (random_dir == 0) ++*new_x;
    if (random_dir == 1) --*new_y;
    if (random_dir == 2) --*new_x;
    if (random_dir == 3) ++*new_y;
  }
}
</code></pre>

Now we implement the method <code>Move()</code> according to the described strategy:
<pre><code>void Game::Move() {
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
</code></pre>

And that's it! If we run the server with visualizer and then our code we should see the player moving according to the promised strategy.

## More <code>contest24</code> script features
There are few commands for managing your projects. You can list all the project with <code>c24 project show</code>, use <code>c24 project change project_name</code> to change what project is the active one and <code>c24 project forget project_name</code> if you want to delete a project (this just forgets about its existance and configuration, you have to delete the files yourself).

Now we will look what is the configuration for this project:
<pre><code>$ c24 config show
PROJECT_DIRECTORY "/tmp/new_folder"
CLIENT_BINARY "/tmp/new_folder/build/bin/quick_start"
CLIENT_DEFAULT_FLAGS "--logbuflevel=-1 --stderrthreshold=0 --vis --toolbar --log_dir=/tmp/new_folder/tmp"
SERVER_BINARY "/tmp/new_folder/build/bin/quick_start_server"
SERVER_DEFAULT_FLAGS "--logbuflevel=-1 --vis"
CLIENT_MEMORY_LIMIT "-1"
SERVER_MEMORY_LIMIT "-1"</code></pre>

Of course, the paths will be different in your case. Lets set CLIENT_BINARY and SERVER_BINARY to the correct paths of the respective binaries. In my case, I would run:
<pre><code>$ c24 config set CLIENT_BINARY /tmp/new_folder/quick_start
$ c24 config set SERVER_BINARY /home/gorli/projects/contest24/build/bin/candy_eaters_server</code></pre>
You can also change the default flags for the client and server. Now you can run the server/client with:
<pre><code>$ c24 server 5500
$ c24 client --port=5500</code></pre>
