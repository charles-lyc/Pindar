# Pindar
电子积木

# What is Pindar?
Pindar是什么？它的取名来自中文“拼搭”，初衷是遵循易用性、便携性、可扩展性的原则而设计的一套开发套件（硬件）。

Pindar为了快速建立项目的硬件而生，是对平时常见小项目的一次浅浅的解构和模块化。

# Some details
它包含三种type类型的板子：
- type base：类似电脑主板，负责电源输出和管理
- type cpu：负责计算
- type app：实际项目的应用

它提供了几种常见的功能接口：
- adc
- uart
- i2c
- spi
- gpio
- power: 3.3V 5.0V Vbatt

我使用的开发工具是KiCad 7.

# How to use it?
S-N-A-P!

仅仅是简单的把你需要的模块叠在一起（玩法类似Arduino），伴随一阵清脆的Click声（等将来找到合适的连接器能发出此声音之后 = =）就可以啦！


# Run your code
估计没人会对这个项目感兴趣，但万一0.1%的可能性你认可它，加上你有自己的想法和一点点动手能力，就可以将它实现成Pindar的type app板，无论你用什么硬件EDA设计，只要**基于template的板框和板间的连接器**设计就行。剩下的电源、总线、io，Pindar都会为你提供支持。

在安装好某个type app板后，你可以为它写几个驱动，让你的项目应用以task或者thread的形式运行在rtos上面来完成一些工作。

期待你的作品。😋

# What about next?
我自己也会不定期更新自己平时玩的一些app板（四轴、平衡车、LVGL、全向轮、磁悬浮等等），后续考虑将Pindar的形态演变成slot插槽的形式。



