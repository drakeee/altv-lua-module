# altv-lua-module
Keep in mind that this module is still WIP (so it should lack some of the functions) and its in beta phase. If you find a bug or missing a function which you think it would be awesome to exists don't hesitate just open an issue for it. The structure and function names are equal to the JavaScript module.
If you have questions feel free to ask on [alt:V's Discord](https://discord.altv.mp) channel (#lua).

## Installing
Installing the module is very simple:
1. Download one of the release from [Releases](https://github.com/drakeee/altv-lua-module/releases).
2. Open the zip file.
3. Drag & Drop the folder from the archive into your server's modules folder.
4. Open your server's server.cfg and add the module:
```
modules: [ lua-module ]
```

## Installing Lua modules
The module itself doesn't come with MySQL/SQLite3, json implemented but you can install it very easily.
1. Download which module you need (mysql-module, sqlite3-module, json-module).
2. Open the zip file.
3. Drag & Drop the folder inside the archive file to your server's modules/lua-module/modules folder.
4. Include the corresponding module in your script:
```lua
-- local sqlite = require("sqlite3")
-- local mysql = require("mysql")
-- local json = require("json")
```

## Example
https://github.com/drakeee/altv-quickstart-lua

I would like to thank [Stuyk](https://github.com/Stuyk) for its [Boilerplate](https://github.com/Stuyk/AltV-JS-Boilerplate) written in JavaScript which is ported to Lua as a good example.

## Wiki
https://wiki.itsdrake.com/index.php/Main_Page

(Wiki is still WIP and I will fill it up with examples if i have free time for it)
