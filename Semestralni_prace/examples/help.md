# VimXel Help

```
vimxel [filename]
```

filename    - open file given


## Control
### Exiting
:q          - quit, checks unsaved changes
:q!         - quit even with unsaved changes

### Data saving and loading
:w          - write data to the current file
:w   file   - write data to a file
:wq         - write data and quit
:wq  file   - write data and exit
:exp file   - export table into a file
:o   file   - open a file, checks unsaved changes
:o!  file   - open a file and throw away unsaved changes

### Table navigation
h           - go left
j           - go down
k           - go up
l           - go right
:A1         - jump to the cell A1
Enter       - go down (normal mode)
Tab         - go to the cell on the right
Shift + Tab - go to the cell on the left

### Table editing
Esc         - exit insert mode, abort changes (not for s and c)
Enter       - save changes (insert mode)
i, a        - edit a cell
x           - delete the cell under the cursor
c, s        - clear cell and start insert
y           - yank to clipboard
p           - paste from clipboard if possible


## Math
Implemented using cmath library, for behavior info read doc there.
All the operations are performed on long double data type.

### Literals
"", ''      - text literals in math expressions
1.0, 1, .1  - number literals in cells of math expressions

### Basic
+, -, *, /, (), [], {}

### Constants
pi, e, c (light speed), gr (golder ration)

### Functions
pow(a, b), sqrt(a), abs(a), mod(a, d)
exp(a), ln(a), log2(a), log10(a), log(x, base)

### Approximation
round(a), ceil(a), floor(a), trunc(a)

### Trigonometry
sin(x), cos(x), tg(x), cot(x)
asin(x), acos(x), atg(x), acot(x)
(arcsin(x), arccos(x), arctg(x), acrcot(x))

### Aggregate
sum(x, ...), max(x, ...), min(x, ...), avg(x, ...)

### Text manipulation
concat(t, ...), lower(t), upper(t)
