# Rgperftools

This is a short package designed to help profile Rcpp packages based on the
excellent advice from this [blog post](http://minimallysufficient.github.io/r/programming/c++/2018/02/16/profiling-rcpp-packages.html) by Minimally Sufficient.

## Usage

Rgperftools provides two functions `start_profiler` and `stop_profiler`, to be used as follows:
```R
library(Rgperftools)

# Force devtools to compile without debug flags for optimal performance profiling
library(pkgbuild)
flags <- pkgbuild::compiler_flags(debug=FALSE)
new_compiler_flags <- function(debug=FALSE) {flags}
assignInNamespace('compiler_flags', new_compiler_flags, 'pkgbuild')

# Load your library
devtools::load_all()

# Collect profiling data
start_profiler("/tmp/profile.out")
run_your_cpp_stuff()
stop_profiler()
```

It can then be used with Google's pprof to visualize the profiler results in a convenient web interface.
```
pprof --http=localhost:[port_num] src/MyPackage.so /tmp/profile.out
```

<details>
<summary>Additional tips</summary>

- You may need to type `~/go/bin/pprof` if you have not updated your `$PATH` to include `$GOPATH/bin`
- If you set `[port_num]` to 8899, you would navigate to http://localhost:8899 to view results

- For extra customization of compiler flags, replace the `new_compiler_flags` line with:
    ```R
    new_compiler_flags <- function(debug=FALSE) {paste0(flags, " -O2 --some-other-flag")}
    ```

</details>

## Installation
I recommend using the [current Go version](https://github.com/google/pprof) of pprof for results 
visualization. This will require installing Go if you haven't already (instructions [here](https://go.dev/doc/install)), then running the following command to install `pprof` to `$GOPATH/bin/pprof`:
```
go install github.com/google/pprof@latest
```
Note that if `$GOPATH` is not set, this will install to `~/go/bin/pprof`

Next, you'll need to install the gperftools system library, then the Rgperftools
R package:

<details>

<summary>Conda-based installation</summary>

Before installing, you must install gperftools, e.g with conda:
```
conda install -c conda-forge gperftools
```

Then to install, run:
```R
# Set compiler variables, so we'll find the conda-based gperftools install
Sys.setenv(
    CPATH=sprintf("%s:%s/include", Sys.getenv("CPATH"), Sys.getenv("CONDA_PREFIX")),
    LIBRARY_PATH=sprintf("%s:%s/lib", Sys.getenv("CPATH"), Sys.getenv("CONDA_PREFIX"))
)
remotes::install_github("bnprks/Rgperftools")
```

</details>

<details>
<summary>apt-based installation (Debian/Ubuntu)</summary>

Before installing, you must install gperftools:
```
sudo apt install libgoogle-perftools-dev
```

Then to install, run:
```R
remotes::install_github("bnprks/Rgperftools")
```

</details>
