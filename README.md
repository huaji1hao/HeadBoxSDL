# Zombie Escape Game 🧟‍♂️🏃‍♂️

Welcome to Zombie Escape, a thrilling C++ mini-game based on my childhood game Boxhead, where your goal is to evade a horde of zombies and survive!

## Game Introduction 🎮

In this game, you'll navigate through levels packed with undead enemies. Your mission is to find the exit and move on to the next stage. But beware, the zombies are relentless, and you must use all your wits and weapons at your disposal to escape!

<img src="https://eumcm.com/file/83d178120a8c79f96540f.png" width = 60% align=center />

<img src="https://eumcm.com/file/a87123c13802e366571a8.png" width = 60% align=center />

## Gameplay 🕹️

As shown in the screenshot, you can control your character and interact with the game environment:

- **Moving**: Use `WASD` keys to move around.
- **Pause**: Press `ESC` to pause the game.
- **Fire**: Click to shoot your weapon at zombies.
- **Next Level**: Reach the door to advance.
- **Sword Position**: Change the position of your sword to defeat zombies effectively.

_Tips: Switch the direction of your sword to kill zombies! The faster you kill zombies, the higher scores you get!_

<img src="https://eumcm.com/file/2e8e3fa3b534e233a7754.png" width = 60% align=center />

## Project Structure 📂

The project is organized into several directories and files, each handling different aspects of the game:

- **Objects**:
  - `Bullet.h`
  - `Button.h`
  - `Door.h`
  - `Player.h`
  - `SpriteObject.h`
  - `TextInputField.h`
  - `Weapon.h`
  - `Zombie.h`
  
- **State**:
  - `InstructionState.h`
  - `StartUpState.h`
  - `LeaderBoardState.h`
  - `State.h`
  - `PauseState.h`
  - `WinState.h`
  - `LoseState.h`
  - `RunningState.h`
  
- **Utils**:
  - `AStar.h`
  - `ImagePixelMappingFlip.h`
  - `ObjectIndexes.h`
  - `Scyjz14CollisionDetection.h`
  - `Scyjz14FilterPoints.h`
  - `Scyjz14Image.h`
  - `Scyjz14ImageManager.h`
  - `Scyjz14RawImageData.h`
  - `Scyjz14TileManager.h`
  
- **Engine**:
  - `Scyjz14Engine` serves as the main engine driving the game.

## Game Compilation 🛠️

To compile the game, follow these steps:

1. Download and install Visual Studio.
2. Open the solution file `CourseworkBase2023_vs2019.sln` by double-clicking it.
3. Press the green arrow (Start Debugging) to compile and run the game.

Enjoy and may you survive the zombie apocalypse! 🎉👾

---

We hope you enjoy playing Zombie Escape as much as we've enjoyed creating it! For more games and updates, follow us on social media. Stay alive out there! 🌟🕹️
