% DWALK(1)

# NAME

dwalk - distributed walk and list

# SYNOPSIS

Parallel MPI application to recursively walk and list contents in a directory.

dwalk provides functionality similar to *ls(1)* and *du(1)*. Like *du(1)*, the tool reports a summary of the total number of files and bytes. Like *ls(1)*, the tool sorts and prints information about individual files.

The output can be sorted on different fields (e.g, name, user, group, size, etc).  A histogram of file sizes can be computed listing the number of files that fall into user-defined bins.

# OPTIONS

-i, \--input FILE
:   Read source list from FILE.  FILE must be generated by another tool from the mpiFileUtils suite.

-o, \--output FILE
:   Write the processed list to a file.

-l, \--lite
:   Walk file system without stat.

-s, \--sort FIELD
:   Sort output by comma-delimited fields (see below).

-d, \--distribution size:SEPARATORS 
:   Print the distribution of file sizes. For example, specifying size:0,80,100 will report the number of files that have size 0 bytes, between 1-80 bytes, between 81-99 bytes, and 100 bytes or greater. 

-p, \--print
:   Print files to the screen.

-v, \--verbose
:   Run in verbose mode.

-h, \--help
:   Print usage.

# SORT FIELDS

By default, the list of files dwalk captures is not sorted.  To sort the list, one or more fields can be specified in a comma-delimited list:

name,user,group,uid,gid,atime,mtime,ctime,size

A field name can be preceded with '-' to sort by that field in reverse order.

A lexicographic sort is executed if more than one field is given.

# EXAMPLES

1. To print summary information for a directory:

mpirun -np 128 dwalk -v /dir/to/walk

2. To print a list of files, sorted by file size, then by file name:

mpirun -np 128 dwalk --print --sort size,name /dir/to/walk

3. To save the list of files:

mpirun -np 128 dwalk --output out.dwalk /dir/to/walk

4. Print the file distribution for specified histogram based on the size field from the top level directory.

mpirun -np 128 dwalk -v --print -d size:0,20,1G src/ 

# SEE ALSO

`dbcast` (1).
`dchmod` (1).
`dcmp` (1).
`dcp` (1).
`drm` (1).
`dstripe` (1).
`dwalk` (1).

The mpiFileUtils source code and all documentation may be downloaded from
<https://github.com/hpc/mpifileutils>
