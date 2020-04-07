## CSV or JSON 

There are to database file types. A CSV database featuring English quotations and a JSON version featuring Latin quotations.

The JSON is a one file databse.
* used only in the CLI version on a Linux
* requires: ```json-c``` from the Debian repos or manually install from [Github](https://github.com/json-c/json-c).

```sh
sudo apt install -y build-essential gcc libgtk-3-dev libjson-c-dev libjson-c-doc 
```

The CSV is a multifile databse.
* used for both the CLI or GTK3 Version
