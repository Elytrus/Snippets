// Some utility snippets written in VSCode snippet style
// Note that these are supposed to be imported using the `cp-tools` extension import templates command
// CP-Tools extension: https://github.com/plasmatic1/cp-tools

//begintemplate forbasic
//description For loop from 0 to n - 1
for (int ${1:i} = 0; ${1:i} < ${2:n}; ${1:i}++) {
    $3
}
//endtemplate forbasic

//begintemplate forinclusive
//description for loop from 1 to n
for (int ${1:i} = 1; ${1:i} <= ${2:n}; ${1:i}++) {
    $3
}
//endtemplate forinclusive

//begintemplate all
${1:i}.begin(), ${1:i}.end()
//endtemplate all

//begintemplate unique
sort(${1:i}.begin(), ${1:i}.end());
${1:i}.resize(unique(${1:i}.begin(), ${1:i}.end()) - ${1:i}.begin());
//endtemplate unique
