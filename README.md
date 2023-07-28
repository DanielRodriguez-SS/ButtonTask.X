# Embedded C with Microchip MPLABX
## Project Name: ButtonTask.X
On this project we will implement a system using a chip **PIC16F18466** that will be able to get a trigger signal from a *push button* to handle a task, in this case, that task will be *toggling an LED*
### Setting the MPLABX project
- Create a new project

![new_project](/screenshots/create_new_project.png)
- Select standalone project

![stand_alone](/screenshots/standalone_project.png)
- Select hardware

Choose the microcontroller you want to use and a Debegger Tool if you have one
![pic_tool](/screenshots/choose_pic_and_tool.png)
- Select C compiler

Depending on what microcontroller you are using, 8 bits, 16 bits or 32 bits, select the right C compiler. In this case we are using an 8 bit microcontroller that will use XC8 compiler.
![C_compiler](/screenshots/choose_C_compiler_suitable_with_pic.png)