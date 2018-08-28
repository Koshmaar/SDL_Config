
# SDL_Config

C++ library designed for reading and writing configuration files (aka .ini files) in an easy, cross-platform way. Example of supported .cfg file:
```
[Camera]
    // C++ style comment
    name = "main" 
    position = -50.0, -50.0 /* example of multi value entry */
    clipping_rect = 0.0, 0.0, 0.5, 1.0 
	
[Game]
    instal_dir = "C:/Games/" # Key-Value substitutions
    subdir = "MagicPencil/"
    game = "MagicPencil.exe"
    full_exec = $(instal_dir) $(subdir) $(game)
```

**Features**:
- sophisticated parsing engine, native support for .INI files from Windows
- reads / writes config files in a cross-platform way
- SDL_RWops gives you ability to parse config files not only from hard-drive, but also from memory, .zip files, internet streams etc
- unique .ini file format extensions - key value replacement, storing multiple values in one entry (comma separeted), multiple groups with the same name, many flavours of comments (example follows)
- iteration over groups, over entries and over values of multiple value entries - separately and simultaneously
- many ways of customizing library, ie. changing keywords and operators
- beautiful formatting when saving files: indenting, white spaces, comments that were found during loading, can be easily saved along with normal groups, entries etc. Can be disabled when space is priority. 
- built with high speed and low memory usage in mind; many ways of customizing library, ie. changing keywords and operators
- comprehensive, high quality online and offline html documentation
- mature implementation with autotests, stable interface, proven to work in many projects; already more than *13* years on the market (initialy hosted on Sourceforge https://sourceforge.net/projects/sdl-cfg/, around 9k downloads)
- full suite of test programs, that show how to use SDL_Config, and of auto test programs, which ensure that library is without bugs

Disadvantages of SDL_Config:
- you have to compile it by yourself to .lib - yet that's very easy
- you have to link with SDL

## Documentation

You can find the *documentation* and *changelog* on website: http://koshmaar.linuxpl.info/sdl_config

First read the tutorial: http://koshmaar.linuxpl.info/sdl_config/readarticle.php?article_id=3

And very thorough offline API listing and manual is also in the doc/index.html 


## Legal

Created by Hubert Rutkowski around 2005 (which explains the old smell), distributed as GNU LGPL

What it means, in a nutshell:
* you don't need to pay anything, to anyone for using this library - it is absolutely free
* you can use this library both in open source and closed source (usually commercial) applications, games etc.
* you can link statically or dynamically to this library, and in both cases, you don't need to release source
