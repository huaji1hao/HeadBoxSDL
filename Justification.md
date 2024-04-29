# Project Documentation

## Requirement 1: Handling of program states

### Attempted Tasks

- **Task a**: 
  - Description: a start-up state, a pause state and a running state
  - Implementation Details: I write  `StartUpState.h` , `PauseState.h`, `RunningState.h`in the `State` file filter
  - Result:  `Scyjz14Engine.cpp` can change state between these states
- **Task b**: 
  - Description: including at least one win or lose state
  - Implementation Details: I write `WinState.h` and `LoseState.h` in `States` file filter
  - Result: When player win or lose, the engine will be set to the corresponding state
- **Task c**: 
  - Description: implement the state model (design pattern) using subtype polymorphism
  - Implementation Details: I use the state model for engine `Scyjz14Engine` and it can be justified in `Scyjz14Engine.cpp`
  - Result: Make the code more maintainable

### Expected Mark: 6/6

### Justification

- **Task a, b**: 

  <img src="https://eumcm.com/file/158d7c762f7ae4f6524f0.png" width = 40% align=center />

  <img src="https://eumcm.com/file/83d178120a8c79f96540f.png" width = 60% align=center />

  <img src="https://eumcm.com/file/194655587db8e8aff7dbe.png" width = 60% align=center />

  <img src="https://eumcm.com/file/9f7bfb00e68198854b1f3.png" width = 60% align=center />

  <img src="https://eumcm.com/file/a0c99c01ff0e10d40495e.png" width = 60% align=center />

  <img src="https://eumcm.com/file/0a945db0dc57daa9cdec1.png" width = 60% align=center />

  

- **Task c**: 

  <img src="https://eumcm.com/file/6756e558697aa141fccc3.png" width = 50% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 2: Input/output features

### Attempted Tasks

- **Task a**: 
  - Description: Save and load some non-trivial data
  - Implementation Details: In `LeaderBoard::loadScores()`, I can load historical player scores from a file
  - Result:  Leaderboard can be correctly loaded
- **Task b**: 
  - Description: load some more complex, structured data,
  - Implementation Details: In `Scyjz14TileManager::loadMapFromFile(const char* filename)`, I can load map data by first loading the map width and height, and then load the map value
  - Result: By using different map files, the `Scyjz14TileManager` can draw different maps
- **Task c**: 
  - Description: save and reload the state
  - Implementation Details: In `State::loadGameState(const std::string& filename)` and `State::saveGameState(const std::string& filename, int LevelIdentifier)`, I can save the state data in to a file and reload the state
  - Result: The game can be archived

### Expected Mark: 6/6

### Justification

- **Task c**: 

  <img src="https://eumcm.com/file/717414adf904f18e2b11e.png" width = 60% align=center />

  <img src="https://eumcm.com/file/37d207689ecc7b76be8a3.png" width = 60% align=center />

  <img src="https://eumcm.com/file/85ef36e57b4621908f65a.png" width = 60% align=center />

  

- **Task c (in txt)**: 

  <img src="https://eumcm.com/file/c94fc84c4c11454478d5c.png" width = 50% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17

## Requirement 3: Use appropriate sub-classing with automated objects

### Attempted Tasks

- **Task a**: 

  - Description: have an intermediate class of your own between the framework class and your end class

  - Implementation Details: I write  

    `Scyjz14ImageObject` extends `DisplayableObject`, 

    `SpriteObject` extends `Scyjz14ImageObject`,

    `AgentBaseObject` extends `SpriteObject`,

    `Player` and `Zombie` extend `AgentBaseObject`...

  - Result:  `Scyjz14ImageObject` is just a image with alpha channel, `SpriteObject` is the object that have animation frames, `AgentBaseObject` is the object that can move, have life value...

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/d26a50308d4a51a8743b0.png" width = 30% align=center />

  <img src="https://eumcm.com/file/388514412346249c9ea44.png" width = 60% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 4: Create and destroy displayable objects during operation of a state

### Attempted Tasks

- **Task a**: 
  - Description: Objects appear to be created or destroyed over time
  - Implementation Details: I create each object at `State::initialiseStateObject()` for each state and delete all object if needed in `~State()`
  - Result:  When switch state, the object will be deleted automatically and when new state is set, the object will be automatically created
- **Task b**: 
  - Description: Correctly create and delete the object at a time
  - Implementation Details: I create `Bullet` when player press `Space` and add it to `DisplayableObjectContainer`. When the bullet should disappear, I set the bullet`setShouldDeleteOnRemoval(false)`  and in `RunningState::virtMainLoopPostUpdate()` I notify the Engine by `drawableObjectsChanged()` and manually remove the object from `DisplayableObjectContainer` and delete it if the bullet is useless
  - Result:  

### Expected Mark: 4/4

### Justification

- **Task b**: 

  <img src="https://eumcm.com/file/d08d88225627e803a2bad.png" width = 60% align=center />

  <img src="https://eumcm.com/file/6255fae27979e3b4376be.png" width = 100% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17

## Requirement 5: Complex intelligence on an automated moving object

### Attempted Tasks

- **Task c**: 

  - Description: A good implementation of some more complex algorithm
  - Implementation Details: When zombies move, in `Zombie::updateDirectionTowardsPlayer`, they will use my own adapted A* algorithm to search the next position and update their directions
  - Result:  Zombies will use my adapted A* algorithms to attack the player

- **Task d**: 

  - Description: An exceptional implementation

  - Implementation Details: 

    - **Problems:**

      In `Zombie::updateDirectionTowardsPlayer` , I first load the map information from `Scyjz14TileManager`into `Graph` and then pass the graph variable to `AStar` by reference to save time. 

      Because my tile size is 30 \* 40 and my player and zombie size are 45 \* 50, if I use the standard A* algorithm, it doesn't meet my agent's pathfinding needs due to a mismatch in size between the agent and the tiles. 

      The issue arises when the A* algorithm directs the agent downward, but a wall blocks the path, trapping the agent. The algorithm doesn't recognize the wall because of the size difference, leading to repeated blockages. 

      To address this, I modified part of the A* algorithm. I input the map positions of four points: the agent’s center, the center offset by pixels to the left, the center offset to the right, and the player's center, into the algorithm. During neighbor initialization, I add the left neighbor of the left point, the right neighbor of the right point, and all common neighbors of these two points into the priority queue. 

      This widens the initial search area, providing more optimal paths and preventing the agent from getting stuck. 

    - **Elegance of the C++ code:**

      - **Use of Standard Template Library (STL):** 

        The function heavily utilizes components from the C++ Standard Template Library, including `std::pair`, `std::priority_queue`, and `std::unordered_map`. These tools are well-optimized for performance and provide a clear and concise way to handle complex data structures and algorithms efficiently.

      - **Lambda Expressions for Local Functionality:** 

        The use of a lambda expression, `addIfPassable`, encapsulates the logic for adding passable neighbors to the search frontier. This approach not only reduces code redundancy but also enhances the readability by keeping the neighbor-checking logic close to where it is applied. It allows for easy modification of the behavior of neighbor handling without affecting the rest of the algorithm's structure.

      - **Graph Abstraction:** 

        The algorithm interacts with the environment through a `Graph` object, which abstracts the details of node connectivity and passability. This separation of concerns ensures that the pathfinding logic is not tightly coupled with the data representation of the graph, making the code more modular and easier to maintain or extend.

      - **Dynamic Path Cost Calculation:** 

        Costs are dynamically calculated using the `Graph::cost(Point from, Point to)` function, which can be tailored to different types of terrain or movement penalties. This flexibility allows the algorithm to be adapted to various scenarios without rewriting the pathfinding logic.

      - **Efficient Path and Cost Management:** 

        The algorithm maintains two maps, `came_from` and `cost_so_far`, to track the path's progression and the cost associated with each point. This method is efficient in terms of both time and space, as it only stores necessary information and updates these structures as the path is built.

      - **Priority Queue for Frontier Management:** 

        The priority queue ensures that the node with the highest priority (lowest cost + heuristic) is always processed next, which is central to the efficiency of the A* algorithm. The `Node` structure, used within the priority queue, is a simple yet powerful way to pair each point with its priority, simplifying the management of the search frontier.

      - **Goal Check and Path Reconstruction:** 

        The loop exits when the goal is reached, preventing unnecessary computations. After finding the goal, the function reconstructs the path from the goal to the start using the `came_from` map and then determines the next step to take, demonstrating a clear use of reverse iteration over the path.

      - **Return Value as Movement Vector:** 

        Finally, the function returns a `std::pair<int, int>`, representing the movement vector from the start to the next step. This approach neatly encapsulates the result in a format that is easy to understand and use in further calculations or movements.

  - Result:  Overall, this code implements heuristic pathfinding for objects of different sizes in the map and the elegance of this C++ code lies in its efficient use of STL, clear separation of concerns, and its adaptability to different pathfinding requirements through dynamic cost calculations and flexible neighbor management.

### Expected Mark: 9/9

### Justification

- **Task d**: 

  <img src="https://eumcm.com/file/ee95871da5a2c6a4277f3.png" width = 100% align=center />

  <img src="https://eumcm.com/file/dd85603acd7cca00540f2.png" width = 100% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 6: Non-trivial pixel-perfect collision detection between objects

### Attempted Tasks

- **Task a**: 

  - Description: Improved collision detection which will work on more complex shapes
  - Implementation Details: In `Scyjz14CollisionDetection` I implement many function about check pixels with alpha channel
  - Result:  I can directly use these functions to check two images with transparency

- **Task b**: 

  - Description: pixel-perfect collision detection on an arbitrarily complex irregular shape

  - Implementation Details: I implement these in  `Scyjz14CollisionDetection` 

    ```c++
    // Check if two images collide by checking the pixels
    static bool checkPixel(
        Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, 
        int iScreenX1, int iScreenY1,
        Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, 
        int iScreenX2, int iScreenY2);
        
    // Expand the opaque part of image1 by `offset` pixels
    // and detect whether it collides with image2.
    static bool checkPixelWithOffset(int offSet,
        const Scyjz14Image& image1, int iSourceX1, int iSourceY1, 
        int width1, int height1, int iScreenX1, int iScreenY1,
        const Scyjz14Image& image2, int iSourceX2, int iSourceY2, 
        int width2, int height2, int iScreenX2, int iScreenY2);
    
    // Check if a image collides with a straight line
    static bool checkPixelWithStraightLine(
        Scyjz14Image image, int iSourceX, int iSourceY, 
        int width, int height, int iScreenX, int iScreenY,
        int startX, int startY, int endX, int endY);
    
    // Check if image2 is in image1
    static bool checkPixelIsImg2InImg1(
        Scyjz14Image image1, int iSourceX1, int iSourceY1, int width1, int height1, 
        int iScreenX1, int iScreenY1,
        Scyjz14Image image2, int iSourceX2, int iSourceY2, int width2, int height2, 
        int iScreenX2, int iScreenY2);
    ```

  - Result:  They are very useful. For instance, when the player kills all the zombies and need to go to the next level, I check whether the player moves to the door for all pixel by`checkPixelIsImg2InImg1`. I check the zombies and player collision by `checkPixelWithOffset`...

### Expected Mark: 4/4

### Justification

- **Task b**: 

  <img src="https://eumcm.com/file/f6895205d449819805e20.png" width = 100% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17

## Requirement 7: Implement a scrolling background by manipulating the way that the background image is drawn

### Attempted Tasks

- **Task a**: 
  - Description: Scrolling background
  - Implementation Details: In `WinState`, I make a scrolling background image to congratulate the player
  - Result:  It is very cool and excited

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/5806bd8def61ce043661a.png" width = 100% align=center />

  <img src="https://eumcm.com/file/be0ba617454025f77a189.png" width = 40% align=center />

  <img src="https://eumcm.com/file/a0c99c01ff0e10d40495e.png" width = 40% align=center />

  <img src="https://eumcm.com/file/b6f0a80ba58597c1a218b.png" width = 40% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 8: Have an animated or changing background by utilising multiple images

### Attempted Tasks

- **Task a**: 
  - Description: Have at least five drawing surfaces, set up with at least slightly different contents
  - Implementation Details: In `LoseState`, I draw a slightly floating soul for the player to indicate that the player has died. I use `std::vector<DrawingSurface>` to manage the background surfaces and avoid redundant code. At the same time, I use `m_iSwitchThreshold` and `m_iSwitchCounter` to make the changing rate slower rather than slower down the frame rate
  - Result:  The changes look smooth

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/8b7ed98a09ae2ba732e7d.png" width = 100% align=center />

  <img src="https://eumcm.com/file/0a945db0dc57daa9cdec1.png" width = 50% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 9: Correctly implement scrolling and zooming of the foreground, allowing the user to scroll around using keys and/or mouse

### Attempted Tasks

- **Task a**: 
  - Description: Allow a player to scroll the screen by using keys
  - Implementation Details: In `InstructionState::virtKeyDown(int iKeyCode)`,  the user can use `SDLK_LEFT`, `SDLK_RIGHT`, `SDLK_UP` and `SDLK_DOWN` to scrolly move the instruction board and use `SDLK_SPACE` to restore the window's position
  - Result:  The foreground can be scrolled by keys
- **Task b**: 
  - Description: Allow a player to zoom in and out the foreground by mouse
  - Implementation Details: In `InstructionState::virtMouseWheel(int x, int y, int which, int timestamp)`, the player can use the mouse wheel to zoom in and out the instruction board where the mouse is pointed. To implement these two functions, I create my own `Scyjz14FilterPoints` class. It inherits from `FilterPointsTranslation` and is composed of a `FilterPointsScaling` so this class allows the engine to zoom and pan at the same time.
  - Result:  If the player cannot clearly see the word on the board, this may be useful..

### Expected Mark: 4/4

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/2e8e3fa3b534e233a7754.png" width = 60% align=center />

  <img src="https://eumcm.com/file/6e5a64c06165e5200821d.png" width = 60% align=center />

  

- **Task b**

  <img src="https://eumcm.com/file/afdc2afe9384d9678bae4.png" width = 50% align=center />
  
  <img src="https://eumcm.com/file/405538dafd485116f997c.png" width = 80% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 10: Animate moving objects

### Attempted Tasks

- **Task b**: 
  - Description: Your objects should have animated rather than fixed appearances
  - Implementation Details:  In `SpriteObject`, I implement `SpriteObject::updateAnimationFrame(int iCurrentTime)` to update the animation frame for current time. The principle is that the image is loaded as sprite sheet, and I force each `SpriteObject` to override a `getFrameCount()` to represent the number of frames in the sprite sheet by make it virtual. Every time the object is updated, `m_iCurrentFrameX` and `m_iCurrentFrameY` will also be updated if the time difference from the last update exceeds `iElapsedTime`. In `virtDraw()`, the object is drawn using the source position calculated from the current frame.
  - Result:  The agent objects move smoothly in the `RunningState`

### Expected Mark: 5/5

### Justification

- **Task b**: 

  <img src="https://eumcm.com/file/6337a86e4f2712aeddff8.png" width = 70% align=center />

  <img src="https://eumcm.com/file/34c623418588bd29c55ef.png" width = 70% align=center />

  <img src="https://eumcm.com/file/76777991dcb4dc996aed5.png" width = 60% align=center />

  

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 11: Image rotation/manipulation using the `ImagePixelMapping` object

### Attempted Tasks

- **Task a**: 
  - Description: Creating and using your own `ImagePixelMapping` class and draw at least one object to the screen
  - Implementation Details:  I create `ImagePixelMappingFlip`, it inherits from `ImagePixelMapping`, which can flip images horizontally, vertically, and both horizontally and vertically. In `StartUpState::virtSetupBackgroundBuffer()`, I draw a red pin on the top right of the photo frame and I horizontally flip the red pin and draw it on the top left of the photo frame
  - Result:  It makes the background look nice

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/833be3a4e8d118140de61.png" width = 100% align=center />

  <img src="https://eumcm.com/file/83d178120a8c79f96540f.png" width = 60% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 12: Interesting and impressive tile manager usage

### Attempted Tasks

- **Task a**: 
  - Description: at least 5 different tile types and load the image only once
  - Implementation Details:  In `Scyjz14TileManager::Scyjz14TileManager(void)`, I just load the image once and the image includes 11 tiles. In `enum Scyjz14TileManager::Type`, each tile type is noted. When draw the tile, I can use change the source X position to draw different tiles
  - Result:  Make it easier to manage the tiles
- **Task b**: 
  - Description: has some interesting behaviour and moving onto some tiles would have effects on tiles elsewhere
  - Implementation Details:  Players cannot pass directly through wall tiles. When the player stands in front of a wall, he will block it. When the player stands behind a wall, the lower body will be blocked by the wall. At the same time, there is a mechanism on the ground in each level. When the player steps on this mechanism, the mechanism will be pressed, and then four old walls will rise. Players can try to use these walls to trap enemies
  - Result:  The game looks more natural and increases the fun of the game

### Expected Mark: 4/4

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/e05bae23023fc4ee658da.png" width = 80% align=center />

  <img src="https://eumcm.com/file/ee2159399b6931aba36f6.png" width = 40% align=center />

- **Task b:**

  <img src="https://eumcm.com/file/f9a0cc75d1de512bfa164.png" width = 60% align=center />

  <img src="https://eumcm.com/file/72d4d85c7d54456d2e5eb.png" width = 60% align=center />

  <img src="https://eumcm.com/file/4d8cef71d8a5a7824dbcb.png" width = 60% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 13: Allow user to enter text which appears on the graphical display

### Attempted Tasks

- **Task a**: 
  - Description: Capture the key presses for letters/characters, and store the key presses somewhere
  - Implementation Details:  In `TextInputField::virtKeyUp(int iKeyCode)`, I capture the keyboard events and store them into `std::string m_sText`
  - Result:  All uppercase and lowercase letters, numeric symbols and punctuation can basically be read and saved
- **Task b**: 
  - Description: Capture the DELETE key press and handle it appropriately and display the text on the screen
  - Implementation Details:  In`TextInputField::virtKeyUp(int iKeyCode)`， `SDLK_BACKSPACE` can also be captured and if the cursor position is not at the head, the tail of the text will be deleted. In `TextInputField::virtDraw()`, I convert the text from `std::string` to `const char*`and then draw them on the text field. At the same time, a cursor will also be drew at the corresponding position
  - Result:  Basically, the text field works and can display words. When there is no words, `<Enter Name>` will be shown and if the player enter something that will be replaced.

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/45663da6dca85350ec237.png" width = 90% align=center />

- **Task b:**

  <img src="https://eumcm.com/file/449596107d1a0068882f1.png" width = 60% align=center />

  <img src="https://eumcm.com/file/220ac194134383ff90a3b.png" width = 60% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 14: Show your understanding of templates, operator overloading OR smart pointers

### Attempted Tasks

- **Task a**: 
  - Description: have created and used smart pointers
  - Implementation Details:  In `Scyjz14Engine`, I use `std::unique_ptr` to manage the `Scyjz14TileManager` and use `std::shared_ptr` to manage the different states. In `ObjectIndexes`, I use the Singleton pattern to manage the `std::vector<int> zombieIndexes` by `static std::unique_ptr`, which makes it easier to manage objects and don't need to care about memory leaks 
  - Result:  The memory of states and objects are managed automatically so don't need to worry about memory leaks

### Expected Mark: 2/2

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/a866cfd442b31910283d9.png" width = 70% align=center />

  <img src="https://eumcm.com/file/505afed4e2efc11aef703.png" width = 80% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 15: Additional complexity

### Attempted Tasks

- **Task a**: 
  - Description: Show exceptional ability in C++
  - Implementation Details:  In `InstructionState::virtKeyDown(int iKeyCode)`, `Player::virtDoUpdate(int iCurrentTime)`, and in`Zombie::updateDirection(int dx, int dy)` instead of using redundant switch, I use `std::map` table to store the key and values. 
  - Result:  Make the code elegant and easier to maintain. 
- **Task b**
  - Description: your implementation was beyond the scope of the existing mark scheme
  - Implementation Details:  In `TextInputField::virtKeyUp(int iKeyCode)`, not only lowercase letters and numbers are captured, but also the shift key, uppercase letters, symbols in`!@#$%^&*()_+-={[]}|\:;"'<,>.?/` are captured. Additionally, the cursor for the next input key is also drawn on the text field. The player can also use `←` and `→` to move the cursor. To calculate the cursor position, I do some research and finally use `SDL_ttf::TTF_SizeText`, which make it work. To prevent players from typing too many words, I also set the maximum length in the text field to 16. When the player clicks on the text field it will be active and if the player clicks on something else or enters `SDLK_RETURN (Enter)` it will be inactive.
  - Result:  The text field works natural and powerful
- **Task c**
  - Description: a useful extension to the framework
  - Implementation Details:  I create `Scyjz14Image` and `Scyjz14RawImageData`, which can draw **transparent** images on the surface. First, I use `Scyjz14RawImageData` to extend `RawImageData` and modified the function `int getRawPixelColour`, so it can get the alpha channel of images. Second, I use `bool Scyjz14RawImageData::loadImage` to overload its base function and use that to calculate and pull pixels with alpha from images. In `Scyjz14Image`, I write help function `unsigned int blendPixels` , which is an algorithm for blending two pixels and is also the basis for rendering transparent images. Finally, `void Scyjz14Image::renderImageWithAlpha` was created, it can calculate the pixel color after blended and draw it on surfaces. To easier use `Scyjz14Image`, I also create `Scyjz14ImageManager`, which is similar with the framework one. I also create some useful functions like `renderImageWithAlphaAndOverlay`, `renderImageWithAlphaAndApplyingMapping` to make it powerful
  - Result:  I can directly draw image with transparent pixels on srufaces

### Expected Mark: 6/6

### Justification

- **Task a**: 

  <img src="https://eumcm.com/file/475ee0715baff09c9cc1c.png" width = 60% align=center />

  <img src="https://eumcm.com/file/9f3f65f057faeced65c66.png" width = 60% align=center />

- **Task b**

  <img src="https://eumcm.com/file/8a6b7abc4ae0ba129099d.png" width = 60% align=center />

- **Task c**

  <img src="https://eumcm.com/file/d788aa2c324781e7b434e.png" width = 60% align=center />

### Demonstration in Video

- Video Time: 00:15-00:17



## Requirement 16: Impact/impression/WOW factor!

### Attempted Tasks

- **Task a**: 

  - [x] you made some effort with the graphical appearance.

    The graphics look not bad as you can see in the screenshot above

  - [x] the background is relevant and not plain or the same as any of the demos.

    It is totally different with the demos

  - [x] the background includes at least some use of relevant shapes (e.g. separating off a score by putting it in a box and labelling it) and/or images.

    Most of my background is drew by images but in win state the rectangle below the text field is drew by shape

  - [x] moving objects are not just plain circles or squares.

    They are agents with animation frames

  - [x] have at least three moving objects.

    They are player, zombie and Boss zombie

  - [x] at least one is user controlled.

    User can control the player agent

  - [x] you accept both mouse and keyboard input in some way.

    In running state, player is controlled by keyboard and in other states user use mouse to click buttons

  - [x] you use both images and drawing primitives appropriately.

    I use many images, framework string drawing and also some shapes

  - [x] you have appropriate states (at least 2).

    I have 7 states, you can see that in State file filter in VS2019

  - [x] have something beyond the minimum required for the other marks (please say what).

    The program is fun and playable. But it is a little bit challenging to pass all three levels

  - [x] your program should work smoothly.

    It runs smoothly except on an unplugged gaming laptop

  - [x] everything looks good with no problems

- **Task b**

  As a game, there are three levels in total and the difficulty of each level increases.

  - **Level 1**

    <img src="https://eumcm.com/file/f9a0cc75d1de512bfa164.png" width = 60% align=center />

  - **Level 2**

    <img src="https://eumcm.com/file/0f5436ce9b3960af34e45.png" width = 60% align=center />

  - **Level 3**

    <img src="https://eumcm.com/file/a87123c13802e366571a8.png" width = 60% align=center />

- **Task c**

  I wrote a README for my game and placed it in the main directory, and hope to open source it one day in the future with the consent of all parties. I wrote a lot of clear and understandable comments in the game code, and hope that someone will continue to maintain and play this game in the future
