#include <nasdaq_vwap.h>
#include <stdio.h>
using namespace std;

int main() {
    freopen(nullptr, "rb", stdin);
    VwapColl vw;
    vw.run();
    return 0;
}
