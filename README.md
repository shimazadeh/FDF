# FDF | 3D Wireframe Viewer | 42Paris

## Introduction
The program takes a map as parameter and creates its 3d representation. 

## Implementation
Here is a summary of how the overal program works:
- Parsing: the map which is presented as a file is read line by line and the values are parsed and stored into the following data structure where x, y, z and color values are the directly taken from the map:
-       - typedef struct s_array{
              double	x;
              double	y;
              double	z;
              int		color;
              int		x_screen;
              int		y_screen;
              int		max_color;
            }				t_array;
- Then matrix-vector multiplication of the x, y and z with the rotation matrix is used to calculate the x_screen and y_screen at every point. For this application we chose to initialize the rotation matrix to: roll = 0.523599, pitch = -0.523599, yaw = 0.523599. you can modify these angles accordingly they will represent the first view of the map. 
- Bresenham's Line Drawing Algorithm is used to draw lines between every two points. 
- Hooks:
      - you can rotate around roll, pitch and yaw using D,A,W,X,Z and E keys
      - you can zoom in/out of the map as usual.
      - you can adjust the altitude coefficient using up/down arrow.
      - Colors of the map changes depending on the altitude of the map.

## Usage
One of the requirement of this project was to use 42l's minilibX. 
- This project is designed to work with minilibx for linux version make sure you have the folder in the repository.  
- git clone https://github.com/shimazadeh/FDF.git FDF
- cd FDF
- make
- ./fdf maps/test_maps/map.fdf

## Showcase

https://github.com/shimazadeh/FDF/assets/67879533/9d9998dd-ce92-486d-a6c3-0df45a85bd21


<img width="1000" alt="Screen Shot 2023-09-21 at 5 54 49 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/50281962-c46b-4ce9-b0f8-40a255ace1fc">

### Render large map with millions of points

<img width="1274" alt="Screen Shot 2023-09-21 at 6 02 36 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/9edf6998-a041-4b0f-9324-52884c2c75d9">

### Render maps with different color scheme

<img width="1269" alt="Screen Shot 2023-09-21 at 5 51 12 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/677e2382-18fd-4848-874f-fe55f06ad0ba">

***Explore more by using the maps in the map directory of the repo!***

