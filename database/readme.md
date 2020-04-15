# CSV or JSON

## 1.0 Rosary Database

There are two database file types.
* A CSV database featuring English quotations
* A JSON version featuring Latin quotations.

## 2.0 CSV
### 2.1 The CSV is a multi file database.

* Developed for use on Win10 and Linux
* Contains English translations

### 2.2 User Defined Feast Days

* I made a standalone CSV file for static feast days.
    * Note: Feast days that designate the Liturgical calendar are embedded into the code. Adding those days are redundant.
* The user may add their own additional days.
* Edit the [printf-time/database/csv/feast.csv](csv/feast.csv) file.
    * Note: January starts at month 0, not 1.

## 3.0 JSON
### 3.1 The JSON is a one file database.

* Developed for use on a Linux OS
* Contains Latin translations
* Requires: ```json-c``` from the Debian repos or manually install from [Github](https://github.com/json-c/json-c).

### 3.2 Install json-c
```sh
## Install json-c on Debian Linux
sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc
```


