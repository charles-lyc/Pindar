进行四轮麦克纳姆轮的控制，融合了imu和鼠标光流，后续如果上激光+ros的话（光流不太靠谱），Panda就只是嵌入式系统的执行器，cpu可能要用box来承担。

# 基本功能
- 遥控定位
- 根据设定点平滑（贝兹曲线），并按某个速度走过这个轨迹
- 目前测了4k速率的光学鼠标，效果还不错，
- 传感器内外参标定
- 鼠标光学引擎是无法测量旋转量的，只能测xy的位移量，所以配合麦克纳姆轮是非常合适的，车子依靠陀螺仪锁头，然后依靠xy平移来走线，光学引擎可以直接出来位移结果，虽然还是需要叠加，误差必然有（平滑启停 并且做好外参标定 提高光学引擎的回报率）
- 全向轮版本（平面自由度其实只需要两个电机，无转动约束下用三个电机已经够了）
https://www.bilibili.com/video/BV1ek4y1H7ry/?spm_id_from=333.337.search-card.all.click&vd_source=71ddf76158b50bfe37a0c2df7f36b37b
https://www.bilibili.com/video/BV18T4y1c75M/?vd_source=71ddf76158b50bfe37a0c2df7f36b37b
https://www.bilibili.com/video/BV14T411e7vE/?vd_source=71ddf76158b50bfe37a0c2df7f36b37b
- 