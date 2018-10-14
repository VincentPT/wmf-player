# wmf-player
Using media foundation and cinder to play video.  
The application can play video from local, direct urls or youtube urls.

![](https://github.com/VincentPT/wmf-player/blob/master/src/doc/Screenshot.PNG)

# Technologies
* CMake
* cppan
* cinder
* imgui
* Cinder-ImGui
* cpprest sdk
* Microsoft Media Foundation

# how to build
1. Download the project from github.  
   git clone https://github.com/VincentPT/wmf-player.git

2. Download external projects.  
   run following command in project root folder.
   ```
   cd wmf-player/src/external
   download-externals.bat
   ```
3. Compile extenal projects.  
   run following command in 'external' folder above.
   ```
   build-externals.bat [Configuration] [Platform]
   ```
   * Configuration should be Debug or Release. Default is Release.
   * Platform should be 'x64' or 'x86'. Default is x64.
   
4. Compile the project.  
   run following commands to configure project for x64
   ```
   cd wmf-player/build
   configure-x64 [Visual Studio Year]
   buid.bat [Configuration]
   ```
   
   run following commands to configure project for x86
   ```
   cd wmf-player/build
   configure-x86 [Platform]
   buid.bat [Configuration]
   ```
   * Configuration should be Debug or Release. Default is Release.  
   * 'Visual Studio Year' should be '2017' ,'2015', '2013' or '2012'. Defaul is '2015
   * Platform should be 'x64' or 'x86'. Default is x64.     
   After build success, the binrary package will be put in folder ./wmf-player/build/application/'Configuration'
   If any error occur, try run buid.bat [Configuration] again.
