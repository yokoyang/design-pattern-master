# 设计模式

标签（空格分隔）： C++ 观察者模式 工厂模式 模板方法模式

---

## 代码改动前缺陷
1.	代码很多地方直接使用字符串来进行图片选择、触发条件等，代码不易维护
2. 变量名命名不规范
3. 代码层次结构不清晰
4. 	函数内部有大量代码冗余
5. 	高耦合低内聚


## 设计思路
项目整体设计思路如下：

![image_1b57slpuc116fnn167eom71lbhm.png-149.2kB][1]


## 观察者模式
我们项目当中每当需要回掉函数是都会使用函数名来调用，我们可以利用观察者模式来进行项目过程的监控，并且将信息的传递通过Message来进行
![image_1b57spa5k1n91o95opvqc91v3r1t.png-161.5kB][2]


  ![image_1b57sq4u01qib1efk1g0u48217k12a.png-46.9kB][3]


## 模板方法模式
### 模板方法概要
![image_1b57srtba1im214ee4q1mjs13la34.png-61.8kB][4]


### 模板方法类图
![image_1b57sta20n4u1p3q17lt1ec08o13h.png-130.6kB][5]


## 工厂模式
工厂模式抽象了对象创建的具体细节创建的时候只需要用特定函数封装特定接口的创建细节

简单工厂封装了new player的过程客户使用时只需要知道创建什么样的player
有更好的拓展性


  [1]: http://static.zybuluo.com/yokoyang/lcf5w7b1s4jplsgteduvqc5e/image_1b57slpuc116fnn167eom71lbhm.png
  [2]: http://static.zybuluo.com/yokoyang/wmmzbtmz4s71o99c9muyj633/image_1b57spa5k1n91o95opvqc91v3r1t.png
  [3]: http://static.zybuluo.com/yokoyang/w32pwvdt6qsnfp7txjj0ef97/image_1b57sq4u01qib1efk1g0u48217k12a.png
  [4]: http://static.zybuluo.com/yokoyang/c3iqtp7v0nt6v0zv019w8neg/image_1b57srtba1im214ee4q1mjs13la34.png
  [5]: http://static.zybuluo.com/yokoyang/tum7sqidfyg94o2j1byd1cmr/image_1b57sta20n4u1p3q17lt1ec08o13h.png
 
