# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any

# Meeting 11.11.2021 13:00
**Participants**: 
1. Tino Korpelainen
2. Nuutti Nykänen
3. Patrik Ahola

# Summary of works
1.	Tino Korpelainen
-	Added the SFML -library to the project
-	Made a prototype SFML -window
-	Added boilerplate Gui -class

2.	Nuutti Nykänen & Elias Kauranen
- LevelMap class base laid out
  - Constructor 
    - Initializes the map to be full of FreeSquares 
    - Initializes the enemy path from given (edge) coordinates No validity checks yet 
  - Get() any subclass of MapSquare 
  - Can Get() enemies or a tower at given (x, y)
  - Can change MapSquares on the map
- MapSquare (abstract)
  - Subclasses FreeSquare, EnemySquare, TowerSquare
- Enemy 
  - Base class and a few enemy subclasses
- Tower 
  - Base class

3. Patrik Ahola
- Game class basic structure 
- Definition of some basic functions and variables (mostly pseudo code)
  - Constructor 
  - UpdateState-function to update the game’s state 
  - Run-function to run the game loop 
  - SpawnEnemy, SpawnTower, StartWave

## Challenges
- Current project is not runnable on a Linux machine due to SFML -library. The final project will need to run in a Linux machine for grading. 
  - Tino will contact the group advisor for help.
## Project status 
The project has been successfully started smoothly. Each team member has worked on important aspects to build the game on.  LevelMap has seen considerable progress and will hopefully be functional in a game setting next week. 

## TODOs
1.	Tino Korpelainen
-	Add different scenes to the window (eg. MenuScene, GameScene, LevelSelectorScreen, LevelEditorScene.)
-	A working game loop in the Gui which updates the game state and then updates the screen
2.	Nuutti Nykänen & Elias Kauranen
- Continue working on the LevelMap. 
  - Tower, Enemy integration 
  - Movement
- Further implementation of Tower and Enemy 
  - Tower subclasses 
  - Tower attack() function
- Work on projectiles
- Enemy path creation validity checks (no overlap, within bounds of the map)
3.	Patrik Ahola
-	Further improvements to the Game class
-	Implementation of functions, when possible
-	Likely restructuring


## Meeting 19.11.2021 15:00
**Participants:**
1.	Nuutti Nykänen
2.	Elias Kauranen
3.	Tino Korpelainen
4.	Patrik Ahola

## Summary of works
1.	Nuutti Nykänen & Elias Kauranen
- Enemy movement 
  - works correctly, from start to finish 
  - bidirectional linked-list enemy path 
    - allows for “area of effect” damage (todo)
- Further tower implementation 
  - placement on map 
  - no attack function yet 
  - subclasses SupportTower & AttackTower 
    - subclasses not implemented
- Projectiles 
  - movement on map towards an enemy target works 
  - hits an enemy, damaging it 
  - subclasses possible for different towers
  - 
2.	Tino Korpelainen
-	Added a parent window state class from which different child classes extend
-	Added child classes: GameState, LevelEditorState, LevelSelectorState, MenuState
-	Gui loop calls different states loops. State loops first advance the game state and then draw the updated game stat
4.	Patrik Ahola
-	Wave and player classes first versions
-	Game class - SpawnEnemy, SpawnTower, Startwave functions. 
-	Game constructor initializes a player and waves.
 
## Challenges
-	A rework of Projectile to support different effects for different towers and its integration with LevelMap
## Project status
Enemies seem to move correctly and projectiles seem to function as intended. The game itself still requires an implementation for the Tower::attack() function, which should allow the core map gameplay to work. There is still a lot of honing and debugging to do regarding the LevelMap, but the core is nearly formed.
Working gui elements should be soon implemented to check other classes functionality visually.

## TODOs

1.	Tino Korpelainen
- Add a working menu scene 
  - Implement working buttons in window states which on click execute a function 
  - Different buttons remove current scene and add a new one
- Make a gui “system” 
  - Some sort of a global object from which states can request different gui elements (buttons, enemies, towers etc.)
- Start figuring out how to save levels in to .json files
- Make it so that scenes poll events instead of the main gui

2.	Nuutti Nykänen & Elias Kauranen
- Tower::attack(Enemy*) function 
  - Should launch customized projectiles 
  - Different projectiles for each tower (with different effects)
- AttackTower and SupportTower subclasses
- improve and debug Projectile / Tower / Enemy interaction
3.	Patrik Ahola
-	Further implementation of wave, player and game classes
-	TowerStore - class first version	


# Meeting 26.11.2021 16:00
**Participants**:
1. Tino Korpelainen
2. Nuutti Nykänen
3. Patrik Ahola
4. Elias Kauranen

# Summary of works

1.	Patrik Ahola
-	Further Game, player and wave class implementations and refactoring
-	Logic for selling and buying player’s towers and managing money
-	Removing enemies from waves
-	KillEnemy in Game class
-	Added projectiles and the logic for buying and selling player’s towers in game	


2.	Nuutti Nykänen & Elias Kauranen
- Further implementation and debugging of enemy movement and projectile interaction
- Different projectile types and effects 
  - BombProjectile hits multiple enemies on hit 
  - Easily can create more projectiles
- Different support towers

3. Tino Korpelainen
-  Implemented working buttons, hit detection, global object, text
- Added a global font object
- Separated event polling to each of the states.
- Working state changes through buttons 

## Project status
The interaction between projectiles, towers and enemies (LevelMap) is generally functional, but it still needs heavy testing etc. 
For the testing it’s critical that we get GUI elements so we can visually confirm that everything is working.



## TODOs
Patrik
- Implementing further functionality to Game, Wave and Player classes. Hopefully, if possible, to test these with a prototype map/level (Enemies moving or dying/taking damage from projectiles, towers shooting etc..).
- I’ll implement at least a prototype of the Game’s UpdateState function to get a basic working function to update all the elements in the map and ensure a working game logic.

Nuutti & Elias
- Heavy testing 
- More different projectiles
- More different towers
- Checking path validity in enemy path construction
- Sprites for GUI

Tino
- Buttons with sprites for buying different towers, upgrade buttons.
- Gui elements for different objects in the game.
- Saving and loading levels (maybe should be pushed back until more urgent tasks are done)


## Meeting 3.12.2021 13:00

**Participants**:

1. Tino Korpelainen

2. Nuutti Nykänen

3. Elias Kauranen

4. Patrik Ahola

## Summary of works

1. Tino Korpelainen

- Added temporary sprites to game objects

- Added buttons for starting wave, upgrade tower, sell tower

- Added buttons for buying different towers

- Bugfixes



2. Nuutti Nykänen & Elias Kauranen

- Worked a little on GUI

- Overall debugging of LevelMap

- Validity checks for enemy path in LevelMap initialization



3.    Patrik Ahola 

- Prototype UpdateState function

- Enemies move

- Attacktowers shoot

- Projectiles move

- Game refactoring and debugging

## Project status

Due to time constraints the level editor will only be implemented as typing coordinates in to a text file. LevelMap is still needs heavy debugging and that will be a focus for the finish lap.

## TODOs

1. Tino Korpelainen

- Add tooltip on hovering over tower buttons

- Implement level loading from a file and saving

- Make the current gui more pretty



2. Nuutti Nykänen & Elias Kauranen

- GUI work

- More debugging of LevelMap

- More Tower and Projectile subclasses

3. Patrik Ahola

- UpdateState completion (SupportTowers, anything that’s missing)

- Game debugging and finishing, working UpdateState

- Testing





# Meeting dd.mm.2021 HH::MM

**Participants**: 
1. Member 1
2. Member 2
3. Member 3
4. Member 4 

## Summary of works
1. Member 1 
   
   Implementing the class XX. Tested the class XX. 
   Results are in `tests/<class-xx-tests>`. Resolved the identified problems.

2. Member 2

   Same as above

3. ...

## Challenges

1. The integration of UI with the monsters requires an abstract interface.
2. ...

## Actions
1. Member 1 is going to look into defining an abstract interface for monsters 
   to enable easy UI integration.
2. Member 2 is going to work with Member 1 to use abstract interface in derived 
   monster classes.
3. Member 2 is going to test the interface.
4. Member 3 is going to use ...

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Short summary of current project status. 

### TODOs
1. Member 1: Write an action.
2. ...