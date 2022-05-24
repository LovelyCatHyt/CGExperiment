# CGExperiment

 计算机图形学实验, 但有一个自制的模仿 Unity 的轮子

## 如何构建

需求列表: 

- Visual Studio > 2019, 已安装 msvc 套件
- OpenGL > 某个版本, 大概是 430
- 开源库 glew, glut 的头文件和库文件, 放在解决方案目录下, 结构为:
  - include: 头文件
  - lib: .lib 静态链接库
  - bin: .dll 动态链接库

运行方法:

- 用 Visual Studio 打开, 然后选择 Debug x64 模式(默认选项)构建并运行.
- 没有 CMake 这个选项, 因为 [这个开发者](https://github.com/LovelyCatHyt) 不会写 CMake

## 项目结构

- 非本人编写的参考代码
  - 2DHomogeneous, 3DTransform 是从老师那里 copy 下来的示例项目, 最后完成之前会删掉
  - vmath.h, LoadShader.h, LoadShader.cpp: 同上, 但是可复用性比较高, 所以也直接拿来用. 不过为了方便传输数据, vmath 相关类加了个成员函数
  - Exp1-FragShaders: 魔改自示例项目
- GLITY: 或称 Glity, GL + Unity = GLITY, 按照类似 Unity 的方式在 OpenGL+glut+glew 上面搭的封装. 具体内容见[下文](#GLITY)
- Exp1-FragShaders: 5个片元着色器, **未使用 Glity**
  - 支持按照 shader 名分类shader, 并运行时切换 shader
- Exp2-Transform: 位移, 旋转, 缩放, 绕指定点的旋转缩放, **使用 Glity**
  - 同时也是验证 Glity 的第一个可执行项目

## GLITY

已实现与待实现功能列表:

- [x] GameObject, Transform, MeshRenderer 可以互相访问
- [ ] Transform
  - [x] 坐标
  - [x] 旋转
  - [x] 缩放
  - [x] 变换矩阵
  - [x] 逆变换矩阵
  - [ ] 嵌套结构
- [ ] Mesh 记录网格信息
  - [ ] 顶点数据
    - [x] 坐标
    - [ ] 纹理坐标
    - [ ] 法线
  - [x] 三角形索引
- [x] MeshRenderer 渲染物体
- [x] 逐 GameObejct 的更新回调
  - [x] AddComponent
    - [x] 主要是添加 Update, LateUpadte, Awake, 之类的东西
    - [x] 使用 IUpdate 等抽象类来判断是否需要注册相应的监听事件
  - [x] GetComponent\<T\>: 获取 T 类型的组件. 底层原理是 `dynamic_cast<T*>`
- [ ] 完全控制 GameLoop
  - [ ] FixedUpdate 与 Update 分离
  - [x] 扫描输入, 为 Input.Getxxx 做准备
- [x] Input
  - [x] GetKeyDown, GetKey, GetKeyUp
  - [x] GetMouseButtonDown, GetMouseButton, GetMouseButtonUp
  - [x] mouePosition
- [ ] Screen
  - [x] vec2 pixelSize
  - [x] int screenSize[2]
  - [x] ScreenToNdc(): 屏幕空间到 NDC 空间
- [ ] Camera
  - [ ] size
  - [ ] aspect = width/height
  - [ ] 可选的正交 or 透视模式
  - [ ] 根据屏幕大小构建矩阵, 保证投影在屏幕上的物体的比例正确
  - [x] 投影矩阵
  - [ ] 天空盒(整个 Unity 的天空盒就非常对味了)
- [ ] Physics
  - [ ] 质点运动学
  - [ ] 碰撞检测
  - [ ] 刚体运动学

从上面的列表可以看出, 仅仅是我个人知道的 Unity 的基础功能都蕴含非常大的工程量, 这个课程实验~~不配~~时间不允许我做这么复杂的系统. 仅仅将渲染这一块的基本流程抽象出来就差不多能搞定所有实验题了.

