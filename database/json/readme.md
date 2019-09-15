### JSON Database (Vulgate Latin)

This scriptures and prayers database is pulled from [jq-tput-terminal](https://github.com/mezcel/jq-tput-terminal). The rest is from [python-curses](https://github.com/mezcel/python-curses). Took out a lot of the html and unicode.

This app uses the [json-c](https://github.com/json-c/json-c) library to easily parse json with C.

Debian provides it within it repository. It is not the lightest json parser, nor does it have the least dependencies, but it's UI/Api is easy and it is popular enough be easily referenced.

#### [json-c](https://packages.debian.org/source/stretch/json-c) and its dependencies for Debian

```sh
## Source: https://packages.debian.org/source/stretch/json-c

## build dependency
sudo apt install autotools-dev debhelper dh-autoreconf dh-exec

## stretch (libs): 0.12.1-1.1
sudo apt install libjson-c-dev libjson-c-doc libjson-c3
``
