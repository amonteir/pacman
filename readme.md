# Pacman game

This is a clone of the original and legendary [Pacman](https://en.wikipedia.org/wiki/Pac-Man) game, written in C++. 
I used Visual Studio 2019 and [vcpkg](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)
to install the required libraries such as [SDL2](https://www.libsdl.org/).

This is how you install SDL2 with vcpkg and use it in Visual Studio 2019.
1. Download and install vcpkg.
2. Open powershell and, in the vcpkg root directory, run the vcpkg bootstrapper `<bootstrap-vcpkg.bat>`.
3. To see what packages are available, for instance SDL2, type `<.\vcpkg.exe search sdl2>`.
4. Download and install SDL2 library, type `<.\vcpkg.exe install sdl2:x86-windows>`
5. After the installation is complete, type `<.\vcpkg.exe integrate install>` to integrate vcpkg with your Visual Studio.
6. Open Visual Studio and create your new SDL2 project. 
7. In the "Solution Explorer" side bar, right click on the name of your Solution and select Properties at the very bottom.
8. In "Linker", pick "Console (/SUBSYSTEM:CONSOLE)" in "SubSystem" and make sure that "Configuration" at the top is "All Configurations".
9. Then change "Configuration" to "Debug", go to "Linker" > "Input" and in "Additional Dependencies", click on the dropdown icon then Edit and in the top editable window add `<SDL2maind.lib>`. Press OK and then Apply.
10. Finally, change "Configuration" to "Release", go to "Linker" > "Input" and in "Additional Dependencies", click on the dropdown icon then Edit and in the top editable window add `<SDL2main.lib>`. Press OK, then Apply and OK to leave the menu.
11. In your cpp code, add #include `<<SDL2/SDL.h>>`. Well done, the SDL2 library is now available for use.

Enjoy. I am groot.
