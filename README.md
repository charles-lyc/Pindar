# Pindar
电子积木模块

# What is Pindar?
Pindar是什么？它是遵循易用性、便携性、可扩展性的原则而设计的一套开发套件（硬件）。

Pindar为了快速建立项目的硬件而生，是对大部分DIY项目的一次浅浅的解构和模块化。

# Some details
它包含三种type类型的板子：
- base：类似电脑主板，负责电源输出和管理
- cpu：负责计算
- app：实际项目的应用

开发工具是KiCad 7.

# How to use it?
S-N-A-P!

仅仅是简单的把你需要的模块叠在一起，伴随一阵清脆的Click声（在我将来找到合适的接插件之后= =）就可以啦！

# Run your code in CPU board
你可以为自己的CPU板写点驱动，然后让你的项目应用以task或者thread的形式运行在上面。当安装某个Pindar兼容的APP模块时，可以启动相应的task应用来工作。

# What about next?
如果你有自己的想法，可以将它实现成Pindar的兼容板，无论是type base、cpu、app等，也无论你用什么硬件EDA设计，只要基于这个template的板框和连接器设计就行。

我自己也会不定期更新自己平时玩的一些app板（四轴、平衡车、LVGL LCD、全向轮、磁悬浮等等经典DIY项目），也考虑将Pindar的形态演变成slot插槽的形式。

期待你我的新作品。😋

# Other else
说点题外话。我一直觉得DIY应该是快乐的，不应该被技术细节限制。诚然有像Arduino这类开源硬件已经做出很大贡献，但我还是觉得差点味道。我接触嵌入式好久好久了，中间也遇到很多重复的坑，正是这些琐碎的细节让大家总是嫌弃跟硬件打交道（me too = =）。我想说，嵌入式的嵌入，正是集中体现在Pindar的app板上，它与项目牢牢绑定，富有创意；而base与cpu只是提供电力和计算的，它们可以一成不变。