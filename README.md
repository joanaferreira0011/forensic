# Forensic

_forensic_ is a simple file information utility. It is being developed as a project from the course **Operating Systems** for the Integrated Master's Degree in Informatics Engineering and Computing, taught at the Faculty of Engineering of the University of Porto.

## Authors

* [Claúdia Martins](https://github.com/claudiaicmartins "claudiaicmartins")
* [Joana Ferreira](https://github.com/joanaferreira0011 "joanaferreira0011")
* [João Matos](https://github.com/joaonmatos "joaonmatos")

## Compilation/Installation

Makefile

## Usage

_forensic_ can be used in the following manner:

```
forensic [-r] [-h [md5[,sha1[,sha256]]] [-o <outfile>] [-v] <file|dir>
```

In which the options are:

 * `-r`: Recursive. If the target is a folder, analyse contents and contents of all subfolders.
 * `-h`: Calculate hash. Along with the standard information, outputs the hash of each analysed file. Requires at least one algorithm to be selected. Supports `md5`, `sha1`, and `sha256` hashes, indicated in that order.
 * `-o`: Output to file. Redirects output to a file named `<outfile>.csv`.
 * `-v`: Verbose. Generates a logfile, with the name indicated by the environment variable `$LOGFILENAME`.
 
_forensic_ generates the following output:

TODO
