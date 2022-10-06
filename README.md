# Birthday Filesort

Simple program to move files into a Year/Month/Day folder structure based on `st_birthtime`, which may not be defined on all filesystems.

Currently takes files as command-line arguments and creates the folder structure in the current working directory.

Does not move files if the destination contains an existing file of the same name.
