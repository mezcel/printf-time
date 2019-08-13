# Readme

2 versions:

* C version (Project In Development)

    * gcc compiler focused
    * ~~jsmn json parser~~
    * manually parse csv files.
		* copy/paste convert json to csv [online json2csv](https://www.csvjson.com/json2csv) I chose this one because it has a mainstream NPM api version (more standard-like than not)
		* for "|" delimiters I used [convertcsv.com](http://www.convertcsv.com/json-to-csv.htm)
		* Wanted to simplfy manual memmory mgnt (no janky workarrounds, faster compiile and run, no non-standard api tools to wrap my head arround)
			* ex: 5k json lines vs 500 csv lines
			* ex: multi function json parse vs 1 fget style csv read
				* either way, I was still going to make my own structs
    * a standalone PFM calulator (embeleshed/bloated version) (DONE/COMPLETED)
    * a Rosary App (UNDER CONSTRUCTION)

* C++ version (Project Not Started Yet)

    * g++ compiler focused
    * jsoncpp json parser (the easiest UI of the json parsers iv come across)
    * a Rosary App

### Backstory:

Prior to ```version 0.2```, The repo was just a gcc app wich calulated the Pashcal Full Moon (PFM) in order to further calulate past/futre Easter dates. I later decided to make a C and C++ cli rosary app based on what I learned from making the previous PFM app.

