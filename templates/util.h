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

//begintemplate sort
sort(${1:i}.begin(), ${1:i}.end());
//endtemplate sort

//begintemplate reverse
reverse(${1:i}.begin(), ${1:i}.end());
//endtemplate reverse

//begintemplate pbds
//description Policy Based Data Structures
// order statistic idea
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, class comp = less<T>>
using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
//endtemplate pbds

//begintemplate time
//description gets time
using namespace std::chrono;
ll timeMs() { return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); }
ll time() { return high_resolution_clock::now().time_since_epoch}
//endtemplate time
