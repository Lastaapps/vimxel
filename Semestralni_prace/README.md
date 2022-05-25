# VimXel

VimXel is a simple spreadsheet editor written in C++ supporting nested expressions, exporting to CSV file format and basic Vi navigation shortcuts and commands.

There is inbuilt protection against cycles and errors in math expressions. Cells with this kind of content can't be even inserted.

Files can be saved (.vimcsv extension recommended) and loaded using commands and command-line arguments. See help below.

To view all the available math and text constructs see help below. There are constants, basic operators and functions. They are implemented by using cmath library. For behavior specs read official documentation. All the operations are performed on long double data type. Enclosure names start with uppercase letters, function names and constants start with lowercase. Cell reference is in A1 format, area in A1:B2.




## Help
See [here](HELP.md).



## Info

Developed by Petr Laštovička as semester theses in subject Programming and Algorithmics 2 at FIT CTU in 2022, later developed further.



## Build

Just run `make` or `make compile` on any Linux system. `ncurses` library may be missing. Doxygen and Graphviz are required for doc building.




## License
VimXel is licensed under `GNU-GPL 3.0` license.