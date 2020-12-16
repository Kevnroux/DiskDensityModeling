build- This is my verison of the build folder. To create your own look at the word doc. Make sure you have a good c++ compiler. To run go into /build/Density_Program. type /.Diskfit and 
it should run. It needs input file names and output file names as command line arguments to crunch data. 

DiskDensityFit- contains the meat of the program. It has all the c++ files you would ever need to edit. All you should need is 
DiskDensityFit\Density_Program\includes "Density_to_Star_Counts.h", the DiskDensityFit\Density_Program\src "Density_to_StarCounts_TrimmedDown.cpp"
, and you are free to look over some of the test cases as well in DiskDensityFit\Density_Program\Tests\src "Tests_main.cpp".

Density Comparison- Contains python scripts to model the disk for a comparision. This is where the files that "Future Work" refrences resides. 

PANNSTARRS- Where pannstarrs raw data and results live. 

SDSS- Where SDSS raw data and results live.
