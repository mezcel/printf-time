### CSV Database (NAB English)

I used npm's json2csv, https://www.csvjson.com/json2csv to convert json to csv

The original json db was taken from my other Rosary apps. I used CSV because it was quicker and easier to parse in a C. I had difficulty using json parsing libraries for C.

This app converts the database into a struct. So if I ever learn how to do Json parsing in C, I wont need to make a new app.

The original database is from [python-curses](https://github.com/mezcel/python-curses). I took out a lot of the html and unicode. I replaced the semicolon char, ```;```, with the string: "<semicolon>".

Previous versions were json was used:

* [electron-container](https://github.com/mezcel/electron-container)

* [jq-tput-terminal](https://github.com/mezcel/jq-tput-terminal)

* [python-curses](https://github.com/mezcel/python-curses)
