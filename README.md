# mpiFileUtils
mpiFileUtils is a suite of MPI-based tools to manage large datasets, which may vary from large directory trees to large files. High-performance computing users often generate large datasets with parallel applications that run with many processes (millions in some cases). However those users are then stuck with single-process tools like cp and rm to manage their datasets. This suite provides MPI-based tools to handle typical jobs like copy, remove, and compare for such datasets, providing speedups of up to 20-30x.

 - [dbcast](docs/markdown/dbcast.1.md) - Broadcast files to compute nodes.
 - [dchmod](docs/markdown/dchmod.1.md) - Change permissions and group access on files.
 - [dcmp](docs/markdown/dcmp.1.md) - Compare files.
 - [dcp](docs/markdown/dcp.1.md) - Copy files.
 - [dfilemaker](docs/markdown/dfilemaker.1.md) - Generate random files.
 - [drm](docs/markdown/drm.1.md) - Remove files.
 - [dstripe](docs/markdown/dstripe.1.md) - Restripe files.
 - [dwalk](docs/markdown/dwalk.1.md) - List files.

## Experimental Utilities
To enable experimental utilities, run configure with the enable experimental option.

  ./configure --enable-experimental

 - [dfind](docs/markdown/dfind.1.md) - Find files by path name (experimental).
 - [dgrep](docs/markdown/dgrep.1.md) - Search contents of files (experimental).
 - [dparallel](docs/markdown/dparallel.1.md) - Perform commands in parallel (experimental).
 - [dtar](docs/markdown/dtar.1.md) - Create file tape archives (experimental).

## Build
mpiFileUtils depends on several libraries.  To simplify builds, there are two scripts: buildme\_dependencies and buildme.  The buildme\_dependencies script downloads and installs all the necessary libraries.  The buildme script then builds mpiFileUtils assuming the libraries have been installed.  Both scripts require that mpicc is in your path, and that it is for an MPI library that supports at least v2.2 of the MPI standard.  Please review each buildme script, and edit if necessary.  Then run them in sequence:

  ./buildme\_dependencies

  ./buildme

Alternatively, mpiFileUtils is available in [Spack](https://spack.io/), which simplifies the install to just:

  spack install mpifileutils

or to enable all features:

  spack install mpifileutils +lustre +experimental

## Build Status
The current status of the mpiFileUtils master branch is [![Build Status](https://travis-ci.org/hpc/mpifileutils.png?branch=master)](https://travis-ci.org/hpc/mpifileutils).
