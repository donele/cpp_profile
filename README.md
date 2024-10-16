# job_chain

Unordered map is a preferred because parallel jobs run concurrently, and the job ids need to be looked up.

## Build

```shell
mkdir build
cd build
cmake ..
make -j 4
ln -s ../data/input_few.txt
ln -s ../data/input_many.txt
```

## Benchmark

```shell
./bin/benchmark_chain

Running ./bin/benchmark_chain                                                                                                            
Run on (16 X 3500 MHz CPU s)                                                                                                             
CPU Caches:                                                                                                                              
  L1 Data 32 KiB (x8)                                                                                                                    
  L1 Instruction 32 KiB (x8)                                                                                                             
  L2 Unified 256 KiB (x8)                                                                                                                
  L3 Unified 20480 KiB (x1)                                                                                                              
Load Average: 5.56, 5.81, 5.57                                                                                                           
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------------------------------                                                            
Benchmark                                   Time             CPU   Iterations                                                            
-----------------------------------------------------------------------------                                                            
BM_vector_few/iterations:2          108694139 ns     86902188 ns            2                                                            
BM_map_vector_few/iterations:2      137957404 ns    137954291 ns            2                                                            
BM_unordered_map_few/iterations:2   141954502 ns    141954510 ns            2                                                            
BM_vector_many/iterations:1        2.0097e+10 ns   2.0097e+10 ns            1                                                            
BM_map_many/iterations:1            696172154 ns    696133277 ns            1
BM_unordered_map_many/iterations:1  304046144 ns    304046703 ns            1              
BM_map_vector_many/iterations:1     288276307 ns    288266421 ns            1
```

## perf (vector)

```shell
sudo perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,branch-misses,page-faults,cpu-migrations,context-switches ./bin/benchmark_chain --benchmark_filter=BM_vector_many

Running ./bin/benchmark_chain                                                                                                            
Run on (16 X 3500 MHz CPU s)                                                                                                             
CPU Caches:                                                                                                                              
  L1 Data 32 KiB (x8)                                                                                                                    
  L1 Instruction 32 KiB (x8)                                        
  L2 Unified 256 KiB (x8)                                                                                                                
  L3 Unified 20480 KiB (x1)                                                                                                              
Load Average: 3.76, 4.74, 5.23                                                                                                           
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.                   
----------------------------------------------------------------------                                                                   
Benchmark                            Time             CPU   Iterations                                                                   
----------------------------------------------------------------------
BM_vector_many/iterations:1 2.0864e+10 ns   2.0855e+10 ns            1                                                                   
                                                                                                                                         
 Performance counter stats for './bin/benchmark_chain --benchmark_filter=BM_vector_many':                                                
                                                                                                                                         
       185,712,049      cache-references                                                        (83.33%)                                 
         2,394,932      cache-misses                     #    1.29% of all cache refs           (83.33%)                                 
    66,087,725,653      cycles                                                                  (66.67%)                                 
   131,419,270,342      instructions                     #    1.99  insn per cycle              (83.33%)                                 
    59,561,088,226      branches                                                                (83.34%)                                 
         3,670,404      branch-misses                    #    0.01% of all branches             (83.34%)                                 
             1,256      page-faults                                                                                                      
                15      cpu-migrations                                                         
               113      context-switches                                                                                                 
                                                                                                                                         
      20.867363313 seconds time elapsed                                                                                                  
                                                                                                                                         
      20.830984000 seconds user                                                                                                          
       0.027995000 seconds sys
```

## perf (unordered_map)

```shell
sudo perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,branch-misses,page-faults,cpu-migrations,context-switches ./bin/benchmark_chain --benchmark_filter=BM_unordered_map_many

Running ./bin/benchmark_chain                                                                                                            
Run on (16 X 3500 MHz CPU s)                                                                                                             
CPU Caches:                                                         
  L1 Data 32 KiB (x8)                                                                                                                    
  L1 Instruction 32 KiB (x8)                                                                                                             
  L2 Unified 256 KiB (x8)                                                                                                                
  L3 Unified 20480 KiB (x1)                                                                                                              
Load Average: 3.94, 4.71, 5.20                                                                                                           
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.                   
-----------------------------------------------------------------------------                                                            
Benchmark                                   Time             CPU   Iterations                                                            
-----------------------------------------------------------------------------                                                            
BM_unordered_map_many/iterations:1  322770531 ns    322771694 ns            1                                                            
                                                                                                                                         
 Performance counter stats for './bin/benchmark_chain --benchmark_filter=BM_unordered_map_many':                                         
                                                                                                                                         
        10,964,299      cache-references                                                        (83.34%)              
         1,515,471      cache-misses                     #   13.82% of all cache refs           (83.34%)                                 
     1,082,854,432      cycles                                                                  (66.69%)                                 
       743,907,534      instructions                     #    0.69  insn per cycle              (83.35%)                                 
       143,082,167      branches                                                                (83.33%)                                 
         3,307,625      branch-misses                    #    2.31% of all branches             (83.31%)                                 
             1,955      page-faults                                                                                                      
                 0      cpu-migrations                                                                                                   
                 0      context-switches                                                      
                                                                                                                                         
       0.330790357 seconds time elapsed                                                                                                  
                                                                                                                                         
       0.316811000 seconds user                                                                                                                                                                                                                                                    
       0.013991000 seconds sys
```

# timeseries_handler

Vector is preferred to avoid memory allocations and deallocations.

## Build

```shell
mkdir build
cd build
cmake ..
make -j 4
ln -s ../data/input_few.txt
ln -s ../data/input_many.txt
```

## benchmark

```shell
./bin/benchmark_ts

Running ./bin/benchmark_ts
Run on (16 X 3500 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 20480 KiB (x1)
Load Average: 5.11, 5.10, 5.27
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
^[-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_map/iterations:2    1179054001 ns   1176156426 ns            2
BM_vector/iterations:2  177451436 ns    177002335 ns            2
```

## perf (map)

```shell
sudo perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,branch-misses,page-faults,cpu-migrations,context-switches ./bin/benchmark_ts --benchmark_filter=map

Running ./bin/benchmark_ts
Run on (16 X 3500 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 20480 KiB (x1)
Load Average: 5.10, 5.14, 5.27
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
BM_map/iterations:2 1003083254 ns    999097953 ns            2

 Performance counter stats for './bin/benchmark_ts --benchmark_filter=map':

         1,954,184      cache-references                                                        (83.28%)
           534,172      cache-misses                     #   27.33% of all cache refs           (83.34%)
     6,246,493,244      cycles                                                                  (66.69%)
     5,299,997,598      instructions                     #    0.85  insn per cycle              (83.37%)
     1,505,079,299      branches                                                                (83.39%)
       131,794,996      branch-misses                    #    8.76% of all branches             (83.30%)
               180      page-faults                                                           
                 0      cpu-migrations                                                        
               163      context-switches                                                      

       2.014263564 seconds time elapsed

       1.989463000 seconds user
       0.016978000 seconds sys
```

## perf (vector)

```shell
sudo perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,branch-misses,page-faults,cpu-migrations,context-switches ./bin/benchmark_ts --benchmark_filter=vector

Running ./bin/benchmark_ts
Run on (16 X 3500 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 256 KiB (x8)
  L3 Unified 20480 KiB (x1)
Load Average: 4.59, 5.03, 5.23
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_vector/iterations:2  228986523 ns    228975772 ns            2

 Performance counter stats for './bin/benchmark_ts --benchmark_filter=vector':

           634,836      cache-references                                                        (83.30%)
            74,757      cache-misses                     #   11.78% of all cache refs           (83.30%)
     1,433,601,874      cycles                                                                  (66.59%)
     1,160,532,347      instructions                     #    0.81  insn per cycle              (83.30%)
       262,806,584      branches                                                                (83.51%)
           126,533      branch-misses                    #    0.05% of all branches             (83.29%)
               170      page-faults                                                           
                 0      cpu-migrations                                                        
                 1      context-switches                                                      

       0.461848148 seconds time elapsed

       0.458891000 seconds user
       0.002999000 seconds sys
```

## memusage (map)

There are more heap location when map is used, compared to vector.


```shell
memusage ./bin/benchmark_ts --benchmark_filter=map

Memory usage summary: heap total: 104281467, heap peak: 168022, stack peak: 15536
         total calls   total memory   failed calls                  
 malloc|    2015894      104280427              0                   
realloc|          0              0              0  (nomove:0, dec:0, free:0)   
 calloc|          1           1040              0                   
   free|    2015880      104202661
```

## memusage (vector)


```shell
memusage ./bin/benchmark_ts --benchmark_filter=vector

Memory usage summary: heap total: 8402388, heap peak: 148006, stack peak: 15536
         total calls   total memory   failed calls
 malloc|      15899        8401348              0
realloc|          0              0              0  (nomove:0, dec:0, free:0)
 calloc|          1           1040              0
   free|      15885        8323582
```

## valgrind cachegrind (map)


```shell
valgrind --tool=cachegrind --log-file=valgrind_cache_map.log ./bin/benchmark_ts --benchmark_filter=map

==1128752== I   refs:      75,870,229,414
==1128752== I1  misses:            22,027
==1128752== LLi misses:             6,448
==1128752== I1  miss rate:           0.00%
==1128752== LLi miss rate:           0.00%
==1128752==
==1128752== D   refs:      44,712,706,296  (27,023,874,263 rd   + 17,688,832,033 wr)
==1128752== D1  misses:        29,179,807  (    28,605,592 rd   +        574,215 wr)
==1128752== LLd misses:            13,615  (         9,887 rd   +          3,728 wr)
==1128752== D1  miss rate:            0.1% (           0.1%     +            0.0%  )
==1128752== LLd miss rate:            0.0% (           0.0%     +            0.0%  )
==1128752==
==1128752== LL refs:           29,201,834  (    28,627,619 rd   +        574,215 wr)
==1128752== LL misses:             20,063  (        16,335 rd   +          3,728 wr)
==1128752== LL miss rate:             0.0% (           0.0%     +            0.0%  )
```

## valgrind cachegrind (vector)


```shell
valgrind --tool=cachegrind --log-file=valgrind_cache_vector.log ./bin/benchmark_ts --benchmark_filter=vector

==1129656== I   refs:      7,482,520,931
==1129656== I1  misses:           13,491
==1129656== LLi misses:            6,384
==1129656== I1  miss rate:          0.00%
==1129656== LLi miss rate:          0.00%
==1129656==
==1129656== D   refs:      4,271,201,394  (2,850,617,859 rd   + 1,420,583,535 wr)
==1129656== D1  misses:        1,532,621  (      313,754 rd   +     1,218,867 wr)
==1129656== LLd misses:           12,844  (        9,832 rd   +         3,012 wr)
==1129656== D1  miss rate:           0.0% (          0.0%     +           0.1%  )
==1129656== LLd miss rate:           0.0% (          0.0%     +           0.0%  )
==1129656==
==1129656== LL refs:           1,546,112  (      327,245 rd   +     1,218,867 wr)
==1129656== LL misses:            19,228  (       16,216 rd   +         3,012 wr)
==1129656== LL miss rate:            0.0% (          0.0%     +           0.0%  )
```
