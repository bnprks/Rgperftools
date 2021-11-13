#include <Rcpp.h>
#include "gperftools/profiler.h"

using namespace Rcpp;

//' Start gperftools profiler
//' @param str Path to save profile result
//' @export
// [[Rcpp::export]]
SEXP start_profiler(SEXP str) {
  ProfilerStart(as<const char*>(str));
  return R_NilValue;
}

//' Stop gperftools profiler
//' @export
// [[Rcpp::export]]
SEXP stop_profiler() {
  ProfilerStop();
  return R_NilValue;
}
