Windows
--------------
1) Download the dependencies package from: https://dl.dropboxusercontent.com/u/1490400/rpg-dependencies.zip
2) Extract the contents of the dependencies package to the dependencies folder
3) Download and install CMake from here: http://www.cmake.org/cmake/resources/software.html
4) Open CMake and set the source directory to the folder containing
   the CMakeLists.txt file, and set the output directory to a subfolder called build.
   For example:
      Source: C:\Work\rpg
      Output: C:\Work\rpg\build
5) Click Generate and select which C++ compiler you're using:
      Visual Studio 2010 = Visual Studio 10
      Visual Studio 2012 = Visual Studio 11
      Visual Studio 2013 = Visual Studio 12
6) Navigate to the build directory and open the generated SLN file.
7) Right click on rpg and then click "Select as Startup Project"
8) Now you can click the green arrow to build and run the game!

Mac OS X
--------------
--TODO--


Linux
--------------
Install dependencies: lua, glm, glew, rapidjson

Makefiles:
1) mkdir build
2) cd build
3) cmake ..
4) make

Ninja:
1) Get ninja from [here](http://martine.github.io/ninja/)
2) mkdir build
3) cd build
4) cmake .. -GNinja
5) ninja
