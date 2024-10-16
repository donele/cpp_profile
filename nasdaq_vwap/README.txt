Note:

VWAP prices are printed up to 4 decimal points.

Pre-open trades are not included in the VWAP calculation.

Non-printable executions are included in the VWAP calculation.

Order Cancel and Order Delete are not handled because they do not affect the calculation of VWAP.


How to build:

mkdir build
cd build
cmake ..
make


How to run:

./bin/run_vwap < <(gunzip -c ~/Downloads/01302019.NASDAQ_ITCH50.gz)

