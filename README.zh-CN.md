# 僵尸危机🧟‍♂️🏃‍♂️

[English Version](README.md)

欢迎来到僵尸危机，这是一款基于我童年游戏 Boxhead 的惊险 C++ 迷你游戏，你的目标是逃避一群僵尸并生存下来！

## 游戏介绍 🎮

在这个游戏中，你将穿越充满僵尸敌人的关卡。你的任务是找到出口并进入下一个阶段。但要小心，僵尸是无情的，你必须利用所有的智慧和武器来逃脱！

<img src="https://eumcm.com/file/83d178120a8c79f96540f.png" width = 60% align=center /> <img src="https://eumcm.com/file/a87123c13802e366571a8.png" width = 60% align=center />

## 游戏玩法 🕹️

如截图所示，你可以控制你的角色并与游戏环境互动：

- **移动**: 使用 `WASD` 键移动。
- **暂停**: 按 `ESC` 键暂停游戏。
- **射击**: 点击射击武器对僵尸开火。
- **下一关**: 到达门口以进入下一关。
- **剑的位置**: 改变剑的位置以有效击败僵尸。

*提示：切换剑的方向来杀死僵尸！杀死僵尸的速度越快，得分越高！*

<img src="https://eumcm.com/file/2e8e3fa3b534e233a7754.png" width = 60% align=center />

## 项目结构 📂

该项目组织成多个目录和文件，每个文件处理游戏的不同方面：

- Objects:
  - `Bullet.h`
  - `Button.h`
  - `Door.h`
  - `Player.h`
  - `SpriteObject.h`
  - `TextInputField.h`
  - `Weapon.h`
  - `Zombie.h`
- State:
  - `InstructionState.h`
  - `StartUpState.h`
  - `LeaderBoardState.h`
  - `State.h`
  - `PauseState.h`
  - `WinState.h`
  - `LoseState.h`
  - `RunningState.h`
- Utils:
  - `AStar.h`
  - `ImagePixelMappingFlip.h`
  - `ObjectIndexes.h`
  - `Scyjz14CollisionDetection.h`
  - `Scyjz14FilterPoints.h`
  - `Scyjz14Image.h`
  - `Scyjz14ImageManager.h`
  - `Scyjz14RawImageData.h`
  - `Scyjz14TileManager.h`
- Engine:
  - `Scyjz14Engine` 作为驱动游戏的主要引擎。

## 游戏编译 🛠️

要编译游戏，请按照以下步骤操作：

1. 下载并安装 Visual Studio。
2. 双击打开解决方案文件 `CourseworkBase2023_vs2019.sln`。
3. 按绿色箭头（开始调试）以编译并运行游戏。

享受游戏并希望你能在僵尸启示录中生存下来！🎉👾

------

我们希望你在玩 Zombie Escape 时能够像我们创建它一样享受！🌟🕹️