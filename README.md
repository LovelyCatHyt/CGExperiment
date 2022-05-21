# CGExperiment

 计算机图形学实验, 但有一个自制的模仿 Unity 的轮子

## 如何构建

需求列表: 

- Visual Studio > 2019, 已安装 msvc 套件
- OpenGL > 某个版本, 大概是 430

运行方法:

- 用 Visual Studio 打开, 然后选择 Debug x64 模式(默认选项)构建并运行.
- 没有 CMake 这个选项, 因为 [这个开发者](https://github.com/LovelyCatHyt) 不会写 CMake

## GLITY

已实现与待实现功能列表:

- [x] GameObject, Transform, MeshRenderer 可以互相访问
- [ ] Transform
  - [x] 坐标
  - [x] 旋转
  - [x] 缩放
  - [x] 变换矩阵
  - [ ] 逆变换矩阵
  - [ ] 嵌套结构
- [ ] Mesh 记录网格信息
  - [ ] 顶点数据
    - [x] 坐标
    - [ ] 颜色
    - [ ] 法线
  - [x] 三角形数据
- [x] MeshRenderer 渲染物体
- [x] 逐 GameObejct 的更新回调
- [ ] 完全控制 GameLoop
  - [ ] FixedUpdate 与 Update 分离
  - [ ] 扫描输入, 为 Input.Getxxx 做准备
- [ ] Physics
  - [ ] 质点运动学
  - [ ] 碰撞检测
  - [ ] 刚体运动学

从上面的列表可以看出, 仅仅是我个人知道的 Unity 的基础功能都蕴含非常大的工程量, 这个课程实验~~不配~~时间不允许我做这么复杂的系统. 仅仅将渲染这一块的基本流程抽象出来就差不多能搞定所有实验题了.

