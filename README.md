# FDF | 3D Wireframe Viewer | 42Paris

##Introduction
The program takes a map as parameter and creates its 3d representation. 

##Implementation
- First step is parsing:
- Draw Line Algorithm: 
- 
- You can rotate, increase altitude coefficient and zoom in/out. All transformations are done through matrixes transformations except for the one translating the picture.
- Colors of the map altermate according to seasons and altitude. Colors slowly change to the next point's color. The program can parse colored maps and also handle transparency. Brightness of the image can also be decreased or increased. Please use menu (H button) for a full list of available options.

##Usage
One of the requirement of this project was to use 42l's minilibX. 
- This project is designed to work with minilibx for linux version make sure you have the folder in the repository.  
- git clone https://github.com/shimazadeh/FDF.git FDF
- cd FDF
- make
- ./fdf maps/test_maps/map.fdf

##Showcase


https://github.com/shimazadeh/FDF/assets/67879533/9d9998dd-ce92-486d-a6c3-0df45a85bd21


<img width="1000" alt="Screen Shot 2023-09-21 at 5 54 49 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/50281962-c46b-4ce9-b0f8-40a255ace1fc">

###Render large map with millions of points

<img width="1274" alt="Screen Shot 2023-09-21 at 6 02 36 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/9edf6998-a041-4b0f-9324-52884c2c75d9">

###Render maps with different color scheme

<img width="1269" alt="Screen Shot 2023-09-21 at 5 51 12 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/677e2382-18fd-4848-874f-fe55f06ad0ba">

<img width="1268" alt="Screen Shot 2023-09-21 at 5 51 47 PM" src="https://github.com/shimazadeh/FDF/assets/67879533/84eb0f36-d9c2-4abe-b935-4594c9f61cac">

Explore more by using the maps in the map directory of the repo!

