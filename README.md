# Minicraft3DS
3DS Homebrew port of Notch's ludum dare game "Minicraft"  
Current Version: Version 1.6.1  

----------

**Download:**

If you just want to download the game prebuilt check the releases tab in Github:  
https://github.com/andre111/Minicraft3DS/releases  
For building the game yourself look below.  


----------


**Dependencies:**

For building and installing the dependencies look below.

ctrulib by smea: https://github.com/smealum/ctrulib  
citro3d by fincs: https://github.com/fincs/citro3d  
sf2dlib by xerpi: https://github.com/xerpi/sf2dlib  
sfillib by xerpi: https://github.com/xerpi/sfillib  
zlib: http://www.zlib.net/  


----------


**Building:**

**1. Install devkitARM by devkitPro**
- On Windows download https://sourceforge.net/projects/devkitpro/files/Automated%20Installer/
- And install atleast Minimal System and devkitARM
- This includes make, ctrulib and citro3d

**2. Install zlib, libjpeg-turbo and libpng**
- Download 3DS-Portlibs: https://github.com/devkitPro/3ds_portlibs
- Run these commands:
		
```
	make zlib
	make install-zlib
	make libjpeg-turbo
	make libpng
	make install
```

**3. Install sf2dlib**
- Download https://github.com/xerpi/sf2dlib
- In the libsf2d directory run these commands:
```
	make
	make install
```
**4. Install sfillib**
- Download https://github.com/xerpi/sfillib
- In the libsfil directory run these commands:
```
	make
	make install
```

**5. You can now build Minicraft3DS 3dsx, elf, cia, and 3ds files by running the build.bat file.**


----------


You can do anything with the source code (besides sell it) as long as you give proper credit to the right people. 
If you are going to make a mod of this version, be sure to give credit to Markus "Notch" Perrson because he did create the original game after all.

# Misc

This source code is subject to a lot of change for better optimization/cleanliness.

Forum thread: https://gbatemp.net/threads/release-new-minicraft3ds-fork-v1-4.494947/
