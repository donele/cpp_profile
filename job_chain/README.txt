# job_chain

Unordered map is a preferred because parallel jobs run concurrently, and the job ids need to be looked up.

## Build
```shell
ln -s ../data/input_few.txt
ln -s ../data/input_many.txt
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
