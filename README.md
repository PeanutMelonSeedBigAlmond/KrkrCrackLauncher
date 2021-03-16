# KrkrCrackLauncher

一个绕过使用 KrkrZ 引擎的游戏首次启动时序列号验证的工具

代码来源于[【教程】kirikiri序列号验证盲拆笔记](https://bbs.zdfx.net/thread-385589-1-1.html)

在此表示感谢

# 使用

1. 下载release中的压缩包解压得到`KrkrCrack.dll` 和 `KrkrCrackLauncher.exe`

2. 将这两个文件复制到**与游戏启动exe同级的目录下**

3. 在**同级目录下**创建`KrkrCrackConfig.ini`，内容为

    ```ini
    [GameConfig]
    ExecutableFile = 游戏启动exe的全名
    ```
    **注意**：自行修改`GameConfig`节点下的ExecutableFile的值

4. 运行`KrkrCrackLauncher.exe`，如果原游戏需要转区运行，此时只需要转区运行`KrkrCrackLauncher.exe`即可

# 项目编译须知

1. 项目使用 `Release/x86` 配置编译

2. 编译出来的成果为 `Release` 文件夹下的 `KrkrCrack.dll` 和 `KrkrCrackLauncher.exe`

3. 参考[使用](#使用)部分配置ini文件并运行