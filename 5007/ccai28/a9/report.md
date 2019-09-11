Modified by Chenxi Cai 2019-4-8
Now we can query title->genre or genre->title.
1. Time to index:
Building the OffsetIndex
Took 0.176604 seconds to execute. 
Memory usage: 
Cur Real Mem: 28984	Peak Real Mem: 28984 	 Cur VirtMem: 33780	PeakVirtMem: 33780

Building the TypeIndex
Took 0.043735 seconds to execute. 
Memory usage: 
Cur Real Mem: 28984	Peak Real Mem: 28984 	 Cur VirtMem: 33780	PeakVirtMem: 33780

time : 0.176604 > 0.043735
space: same. So TypeIndex is better.

2. Query: search for comedy movies with "People" in title.
Query on People, Comedy:
Getting docs for movieset term: "people"
indexType: movie
2 items
	5 People
	Sleeping with Other People
Took 0.000001 seconds to execute. 
Destroyed OffsetIndex
Cur Real Mem: 28984	Peak Real Mem: 28984 	 Cur VirtMem: 33780	PeakVirtMem: 33780

Querying movie comedy with people in title:
Movies: Sleeping with Other People
Movies: 5 People
Took 0.000948 seconds to execute. 
Destroyed TypeIndex
Cur Real Mem: 28984	Peak Real Mem: 28984 	 Cur VirtMem: 33780	PeakVirtMem: 33780

time: 0.000001 < 0.00948
space: same

OffsetIndex is better.



Step2: ParseTheFiles_MT:
1. Time to index:
Building the OffsetIndex
Took 0.163874 seconds to execute. 
Memory usage: 
Cur Real Mem: 28972	Peak Real Mem: 28972 	 Cur VirtMem: 33780	PeakVirtMem: 33780

Building the TypeIndex
Took 0.040715 seconds to execute. 
Memory usage: 
Cur Real Mem: 28972	Peak Real Mem: 28972 	 Cur VirtMem: 33780	PeakVirtMem: 33780

time : 0.163874 > 0.040715
space: same. So TypeIndex is better.
Because 0.163874(MT) < 0.176604(sigle thread) , the multithread works, more efficient

2. Query: search for comedy movies with "People" in title.
Query on People, Comedy:
Getting docs for movieset term: "people"
indexType: movie
2 items
	5 People
	Sleeping with Other People
Took 0.000001 seconds to execute. 
Destroyed OffsetIndex
Cur Real Mem: 28972	Peak Real Mem: 28972 	 Cur VirtMem: 33780	PeakVirtMem: 33780

Querying movie comedy with people in title:
Movies: Sleeping with Other People
Movies: 5 People
Took 0.001174 seconds to execute. 
Destroyed TypeIndex
Cur Real Mem: 28972	Peak Real Mem: 28972 	 Cur VirtMem: 33780	PeakVirtMem: 33780

time: 0.000001 < 0.001174
space: same

OffsetIndex is better.
Because 0.001174(MT) < 0.00948(sigle thread) , the multithread works, more efficient
