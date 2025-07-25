rm ./build/coverage.html
LLVM_PROFILE_FILE="./build/coverage.profraw" ./build/tests
llvm-profdata merge -sparse ./build/coverage.profraw -o ./build/coverage.profdata
llvm-cov show ./build/tests -instr-profile=./build/coverage.profdata --format=html > ./build/coverage.html
chromium ./build/coverage.html