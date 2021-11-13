# Rgperftools

This is a short package designed to help profile Rcpp packages based on the
excellent advice from this [blog post](http://minimallysufficient.github.io/r/programming/c++/2018/02/16/profiling-rcpp-packages.html) by Minimally Sufficient.

It provides two functions `start_profiler` and `stop_profiler`, to be used as follows:
```R
start_profiler("/tmp/profile.out")
run_your_cpp_stuff()
stop_profiler()

start_profile("/tmp/another-thing.out")
that_other_thing(1:1000)
stop_profiler()
```

It can then be used with Google's pprof to visualize the profiler results in a convenient web interface.
```
pprof --http=localhost:[port_num] MyPackage/src/MyPackage.so /tmp/profile.out
```

# Installation
Before installing, you must install gperftools, e.g with conda:
```
conda install -c conda-forge gperftools
```

And I recommend using the [current Go version](https://github.com/google/pprof) of pprof for results 
visualization. This will require installing Go if you haven't already, then running
```
go get -u github.com/google/pprof
```
which will install `pprof` to `$GOPATH/bin/pprof`

Then to install, run:
```R
# Set compiler variables, so we'll find the conda-based gperftools install
Sys.setenv(
    CPATH=sprintf("%s:%s/include", Sys.getenv("CPATH"), Sys.getenv("CONDA_PREFIX")),
    LIBRARY_PATH=sprintf("%s:%s/lib", Sys.getenv("CPATH"), Sys.getenv("CONDA_PREFIX"))
)
devtools::install_github("bnprks/Rgperftools")
```
