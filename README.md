# Birthday Filesort

Simple program to move files into a Year/Month/Day folder structure in the current working directory.

Takes files to be sorted as command-line arguments, i.e. `argv[]`.

Does not move files if the destination contains an existing file of the same name.

## Issues
- based on `st_birthtime`, which may not be defined on all filesystems
