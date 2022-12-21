# Final_Project
Object-Oriented Programming project.
Save The King Project

Intro
At this game your goal is to get the king to its throne. 
The king is accompanied by some other members of the realm such as 
a mighty warrior, a wise old mage, and a sneaky Thief. 
Each member of the realm holds a special ability that can help the King get to its throne. 
To get the king to the throne you will have to use the skills of the realm members wisely. 
Realm members abilities
The mighty warrior can kill those green disgusting orcs that drop keys.
The wise old mage had studied the elements and can now put out fire.
The sneaky thief can pick up keys dropped by orcs and use those keys to open gates.
Finally, there's the king, who has no special abilities because, well, he's a king.
Design
The fundamentals of this code are based on class “Controller”. 
At first, Controller uses class "Menu" to display the client which contains three options. 
The options are: Start a new game, get help and exit client.
If the user chooses to start a new game, the menu is closed and now class controller starts using class “Board”. 
By using a vector of unique_ptr, after using the function "loadLevel", class board creates and holds all the game objects in the same position that was read from the file. 
In order to display all the game objects, class Board uses class "Textures" which creates all the textures by using a singleton (a method to load texture only once).
The next layer of the code is class “GameObject” which is the base class for any in-game object. 
By using polymorphism and inheritance all game objects are created by the C-tor of this class.
Afterwards, all objects are divided to two classes: Class "MovableObject" and class "UnmovableObject".  Those two classes are the gist of the difference between moving game objects such as king, thief, warrior, mage and elf and still objects such as wall, fire, orc, etc.
The other responsibilities of class "controller" is to take care of all the sounds and special effects such as win level sound effect, etc. it does that by using classes "Buffers"  and "Sound" which contain all the sound effects and background music.
MovableObject: (inherits from "GameObject")
The in-game movement is different between the elf and the realm members. Hence, we have class Player which inherits the public functions of "MovableObject". The objects that inherit from "player" are the realm members (king, warrior, mage and thief).
On the other side we have the class Elf which also inherits from "MovableObject" but overruns the move function in a way that allows it to move randomly.

UnmovableObject: (inherits from "GameObject")
The unmovable objects such as wall, fire, orc, gate, throne, key and gifts inherit the public functions of class "UnmovableObject". The difference between all the objects is the way the overrun collision functions are implemented at the leaves of the inheritance tree.
For an example, the collision of a throne with a king is different from a collision between a warrior and a wall.
Note: You can press "Help" on the menu to see all possible collisions

Small classes:
Class Throne: Collision with a king will win the current level.
Class Wall: No one can pass through a wall.
Class Key: Collision with a thief will grant the thief the ability to open a single gate.
Class Gate: Collision with a thief will open the gate if the thief had already obtained a key.
Class Orc: Collision with a warrior will result in the orc’s death. Once the orc dies, he drops a key.
Class Fire: Collision with a mage will put out the fire.
Class Portal: Each portal has its pair, any realm member besides the mage can use the portal and teleport to the right of the paired portal position. Hence, you can only use the Portal once the paired portal tile is empty to the right.
Class Gifts: The two subclasses "ElfGift" and "TimeGift" inherit from this class. 
If a player had collected a Time-Gift:  The gift is a randomized time added to the clock.
Note that the gift can either add or decrease time, depends on your luck! 
If a player had collected an ElfGift:  all elves will be instantly eliminated.




Collision Table between Movable objects and Unmovable objects:
*	Key 	Fire 	Teleport	Throne	Orc	Gate	Gift
King	    V	   X	    V	    V(win)	   X	    X	  V
Mage	    V	   V	    V
(can’t pass)	    X	   X	    X	  V
Warrior	    V	   X	     V	    X	   V(kill)	    X	  V
Thief	    V(take)	   X 	     V	    X	   X	 V 
(with key)	  V

Data structures used in the program:
All the in-game data is held by vectors. Each vector contains a unique type of object or method. The main vectors are as described below.
Class Board: Contains four different vectors which relate to the objects read from the given level (current file read).
 Those are: 
1.	Vector (using unique ptr) of movable objects which contains the players.
2.	Vector (using unique ptr) of the elves that are currently on the board.
3.	Vector (using unique ptr) of the unmovable objects on the board.
4.	Vector of sf::Vector2f which contains all portal locations.
Class Controller contains a vector of sprites, each sprite contains a level-background.
Note, there are 3 level backgrounds. If a level is added by the user, this level will receive one of the 3 possible backgrounds.

Input file format:
To add new levels to the game add the new level’s name to the file named “Levels.txt”.
To edit levels open the file and insert chars by this format:
	king = 'K', thief = 'T', mage = 'M',
	warrior = 'W', elf = '^', orc = '!',
	throne = '@', portal = 'X', key = 'F',
	wall = '=', fire = '*', gate = '#', timeGift = '+', elfGift = '/'
The maximum size of a level is a 13 x 30 matrix.
There’s no minimum size but it needs to make sense.



Files created by us:
Almost every picture was designed or edited by us.
Cpp files and header files:
Board.cpp + Board.h: In charge of the game board’s functionality.
Buffers.cpp + Buffers.h: In charge of the sound buffers (singleton method).
Controller.cpp + Controller.h: In charge of running and managing the game.
Elf.cpp + Elf.h: In charge of the elves.
ElfGift.cpp + ElfGift.h: In charge of the gift which removes the elves.
Fire.cpp + Fire.h: In charge of the fire object.
GameObject.cpp + GameObject.h: Base class for the game objects.
Gate.cpp + Gate.h: In charge of the gate object.
Key.cpp + Key.h: In charge of the key object.
King.cpp + King.h: In charge of the king character.
Mage.cpp + Mage.h: In charge of the mage character.
Menu.cpp + Menu.h: In charge of running and managing the menu.
MovableObject.cpp + MovableObject.h: In charge of objects which can move.
Orc.cpp + Orc.h: In charge of the orc object.
Player.cpp + Player.h: In charge of the players (king, thief, mage, warrior).
Portal.cpp + Portal.h: In charge of the portal object.
Sound.cpp + Sound.h: In charge of the sounds and musics of the game.
Textures.cpp + Textures.h: In charge of the textures (singleton method).
Thief.cpp + Thief.h: In charge of the thief character.
Throne.cpp + Throne.h: In charge of the throne object.
TimeGift.cpp + TimeGift.h: In charge of the time gift object.
Wall.cpp + Wall.h: In charge of the wall object.
Warrior.cpp + Warrior.h: In charge of the warrior character.



Worth Mentioning Functions:
Controller::run(): 
Run function starts with displaying the menu to the user (the menu is as described above). If the user clicks on "New game": The run function will start with loading the first level and initiating all the variables and methods needed (such as the window and the buttons). The function then proceeds to the game loop which updates, renders and deletes what needs to be deleted every iteration.
Menu::runMenu():
Similar to Controller’s run() function.
Creates a separated window for the menu which runs as the game’s client (launcher) and then runs the menu loop, which updates and renders the menu’s window.
Board::loadLevel():
This function first updates the index of the current level (which starts in 0).
The function then opens a file (knows which file to open by the index of the current level) which contains the data of the level.
The function then proceeds to read the data from the file and translate it into game objects by inserting them into the right vector (based on type).
In the end, saves the game board size and returns true if the level was loaded.
Controller::hightlightButton(sf::Vector2i loc) and Menu::hightlight(sf::Vector2i loc):
These functions oversee “highlighting” (or marking) of the currently hovered-on button. It receives the current location of the mouse as input.
They use an array of booleans (of a size equal to the number of used buttons) which initiates as false in every cell of the array.
And then, the booleans array in the place of the index of the button which is currently being hovered on turns to true.
The function then switches between the “highlighted” version of the button to the regular version of the button in the vector of the used buttons.
Controller::handleSounds(GameObject* object):
This function oversees sounds handling. It receives a pointer to the base class of every object and uses the methods of RTTI and dynamic_cast to decide which sound should be played.
The sounds which are played are initially loaded to m_sound, which is a member of the Controller class.

Worth Mentioning Algorithms:
The Teleport Algorithm: 
Portals are read from the file as X's and those come in pairs. Hence, the number of portals in the game will always be even.
Each portal will teleport to the nearby portal which is read right after him from the file.
Therefore, we want to send the even portals to the odd portals and the other way around.
The way it is implemented in the program is by using f(x)= x+1 for each teleport located in an even location and by using f^-1(x) = x-1 for each teleport located in an odd location. Using a bijective function, we made each teleport to have a teleport image which belongs only to it.
And by using the "image" teleport we go back to the domain which is the first teleport of the two. 
Buttons-highlight function:
By mouse-hovering over a button, the button shall be highlighted. 
The way it is implemented in the program is:
Creates two vectors of sprites. One vector for currently used buttons, other vector contains buttons in general use. 
Creates an array of Boolean variables and is in the same size of the used buttons vector.
For each button in used_button[i] we say that rehoveredButton[i] is true if and only if the mouse hovers above the location of used_button[i] (which also means that only one cell in the array is 1 at a time).
Now, the function runs in a for loop on the vector of the used buttons,
For each index I <  amount of used buttons:
 Do  if : button[i] contains the location of the mouse then rehoveredButton[i] is true.
{
Second: we check for each index J < amount of hovered buttons
Do if : rehoveredButton[J] is true than display hovered button sprite.
}
Do else : if button[i] doesn’t contain the location of the mouse then rehoveredButton[i] = false and display non hovered button sprite.

Known bugs:
There are currently no known bugs to us.
Other notes:
None.
