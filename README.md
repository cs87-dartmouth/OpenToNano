To build this tool you have to install openvdb and all of its dependencies. If you are on Mac we recommend using:

```
brew install openvdb
```

If you are on Linux we recommend you use:

```
sudo apt install libopenvdb-dev
```

Unfortunatly I (zack) do not use Windows machines so please refer to openvdb.org for how to set everything up for Windows.

These commands should also install the dependencies needed for this tool, however, we have to manually set the paths to the include
folders before building the project. To do so, open `CMakeLists.txt` and look for the lines setting `OPENVDB_INCLUDE_DIR`, `BOOST_INCLUDE_DIR`,
and `TBB_INCLUDE_DIR`. The paths which are currently there will not work for your machine so you will have to replace them. To find where
they are located you should first update the locate database on your computer using the following command:

On Mac:

```
sudo /usr/libexec/locate.updatedb
```

On Linux:

```
sudo updatedb
```

Now you can find the paths for the three libraries above using

```
locate /tbb/
locate /openvdb/
locate /boost/
```

You will get many results, mostly of the form:

```
prefix/{name}/{version}/postfix
```

where `{name}` is either `tbb`, `openvdb`, or `boost`, and the version number will be dependent on what you have installed. You should overwrite what is in `CMakeLists.txt` with:

```
set(OPENVDB_INCLUDE_DIR
   prefix/openvdb/{version}/include)
```

```
set(BOOST_INCLUDE_DIR
   prefix/boost/{version}/include)
```

```
set(TBB_INCLUDE_DIR
   prefix/tbb/{version}/include)
```

Once you have done this, you can build the project by running:

```
mkdir build && cd build && cmake .. && make -j
```

Then you can run the converter by using:

```
./opentonano {path_to_input.vdb} {path_to_output.nvdb}
```

