## 可以使用idf.py monitor命令直接在终端调试，提供了一些命令：

![image.png](https://image.lceda.cn/oshwhub/pullImage/54b903d59df044e9875b6f5fc888556a.png)

## 硬件上引出了esp32c3的所有gpio口以及axp2101所有电压输出口


![image.png](https://image.lceda.cn/oshwhub/pullImage/388b7a90473b42f6a3675d1791b37456.png)

## 其中现在的固件中gpio12和gpio13分别被软件iic设置为SDA和SCL,可以接oled模块或者aht10传感器模块，已经调试通了。

![image.png](https://image.lceda.cn/oshwhub/pullImage/aae685c67bdb4c84a6a8a8269fdf502b.png)

## 使用不同的模块需要在命令行输入切换命令。sensor0是不启动这项功能，sensor1是启动oled，sensor2是启动aht10。

![image.png](https://image.lceda.cn/oshwhub/pullImage/739cf063b50449a4b3835daf3076cbdf.png)

![P20250906-110857.jpg](https://image.lceda.cn/oshwhub/pullImage/20978ddf92bb4632823d932fbe0dffb0.jpg)

![image.png](https://image.lceda.cn/oshwhub/pullImage/ccd720fc520b46e9ae87be5a97698ed2.png)


![image.png](https://image.lceda.cn/oshwhub/pullImage/38cd3d65c13a4d7a8d7dfa8ff90d0b99.png)

