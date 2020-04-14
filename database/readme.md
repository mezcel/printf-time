## CSV or JSON

There are to database file types. A CSV database featuring English quotations and a JSON version featuring Latin quotations.

The JSON is a one file database.
* used only in the CLI version on a Linux
* requires: ```json-c``` from the Debian repos or manually install from [Github](https://github.com/json-c/json-c).

```sh
sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc
```

The CSV is a multi file database.
* used for both the CLI terminal or GTK3 Version

## Feast Days

I made a standalone CSV file for static feast days. The user may add their own additional days.
