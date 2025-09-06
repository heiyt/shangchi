## 可以使用idf.py monitor命令直接在终端调试，提供了一些命令：  

<img width="543" height="309" alt="image" src="https://github.com/user-attachments/assets/e5123a74-b407-4f51-9ddc-47d954390d39" />  

## 硬件上引出了esp32c3的所有gpio口以及axp2101所有电压输出口  

<img width="825" height="1293" alt="image" src="https://github.com/user-attachments/assets/48ad0e72-d108-4594-837c-4ac01fb47092" />  

## 其中现在的固件中gpio12和gpio13分别被软件iic设置为SDA和SCL,可以接oled模块或者aht10传感器模块，已经调试通了。  

<img width="284" height="54" alt="image" src="https://github.com/user-attachments/assets/8f64795b-6352-4e43-b03c-290f2851fb4a" />  

## 使用不同的模块需要在命令行输入切换命令。sensor0是不启动这项功能，sensor1是启动oled，sensor2是启动aht10。  

<img width="210" height="77" alt="image" src="https://github.com/user-attachments/assets/86dec02d-a2c6-49ac-be04-1abb79557640" />  

![b](https://github.com/user-attachments/assets/5c50341d-ce96-425e-b264-8cb5b0605dc9)

<img width="303" height="41" alt="image" src="https://github.com/user-attachments/assets/dc7ea016-e02b-4e15-9648-35daebe7c11a" />  

![a](https://github.com/user-attachments/assets/583ae89d-1f2f-450a-9062-e60487c94345)

