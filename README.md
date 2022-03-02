# Stm32-SDcard-library
SDcard library for stm32 is a bare metal implementation which can easily be integrated into existing projects to provide functionality such as read ,write and create files and folders on a SDcard . the library is continuously under development to provide more features and support more protocols  for high speed applications as well 

# Hardware Requirement 
The hardware requirements are :
- STM32f4 based mcu or development board ([this ](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)board hae been used for tsesting  )
- SDcard module ([this module ](https://drive.google.com/file/d/1OMjvtsqhbnj-Lv0XjT_rjlsX-I8Km_mr/view?usp=sharing) have been used )
- A SDcard of any capacity you have 

## Project file structure 

**Src** :   The Src folder contains the main application file ( main.c )  .  The user might change the contents of the file if needed . The folder contains example code each example with its own source file . 

**drivers** : folder contains further sub folder  **Src** and **Inc**   .
- **Src** : Src folder contains driver source (.c) file which has all the driver apis the application file uses 
- **Inc** : Inc folder contains the  driver header (.h) file which has all the function prototypes and configuration macros .  

##  

>    **Note:**  To ensure proper working make sure that all the hardware connections are properly doe and have no loose ends . make sure the wire lenght is as short as possible to avoid any problems commucntion between sdcard and the microcontroller is done over SPI .It is recommended to make connection on a prototyping pcb as shown below or similar    

![ ](https://drive.google.com/uc?export=view&id=1f3EHwJMU6KvdZASp3M_vwiQEmJz3vAp2)

![ ](https://drive.google.com/uc?export=view&id=1f0NEWWk88jMlp61i9zDh2v3lKCrZo3uv)

![ ](https://drive.google.com/uc?export=view&id=1evlGqBQPHWv-eM6SqtXHf4bkGUMMkrra)


