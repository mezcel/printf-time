# Man page

Use Pandoc to convert an R-Markdown file into a Groff file.

### Debian External Prerequisites:

```sh
sudo apt install -y man-db groff pandoc
```

### Render a man page from a markdown.

```sh
## Global Man page
pandoc ./man/manpage.md -s -t man > /usr/bin/printf-time

## Local Man page
pandoc ./man/manpage.md -s -t man > ./man/printf-time
```


## Generate a local man page from the Makefile

```sh
make manpage
```
