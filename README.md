# SFML-MapMaker

General
--------------

- Project created with Visual Studio 2015 and SFML.
- SFML: http://www.sfml-dev.org/


Other:
--------------

- To run SFML with vs15, download appropiate <a href=http://en.sfml-dev.org/forums/index.php?topic=9513.0>vs15-Nightly Build</a> (recommended 32bit Version) and follow the offcicial <a href=http://www.sfml-dev.org/tutorials/2.3/start-vc.php>SFML-Visual Studio Tutorial</a>
- You can use the uploaded *"MapMaker.sln"* file but have to adjust the Project-Properties (correct path to the .lib etc files from SFML, see tutorial)
- I've used the static-linking from SFML (no need to copy over the SFML-DLLs)


To-Do:
--------------

1. Cleaning up some unnecessary functions in my classes and choosing a appropriate name-convention for my variables
(right now it's a huge mess because I just started to code and didnt look back  ;D)
2. Alpha-Support for texture
3. variable Texture-Size (currently the texture-pic has to be 720x720 with 72x72 per tile)
4. Whole-Mode Menu


> Draw: The one currently working

> Select: Selecting multiple tiles with the mouse to fill all / delete all / Ctrl-X / ...

> Objects: Special Objects like animated stuff / enemys / ...


Pictures, etc:
--------------
![Demo-Picture](http://i.imgur.com/WO9Thgi.png)

Youtube: [click me](https://www.youtube.com/watch?v=_FZl1KC_WZo&feature=youtu.be "YoutubeDemo")

SFML-Forum-Post: [click me](http://en.sfml-dev.org/forums/index.php?action=post;topic=18869.0;last_msg=136153 "SFML-Forum")
