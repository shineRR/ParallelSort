# ParallelSort
- Design a job queue into which multiple threads can insert items atomically.
- Develop a handler for this queue that extracts jobs from it and distributes a given number of threads.
- Develop a program that uses a job queue and a queue handler to sort the lines in a text file:
The input stream reads the file into memory, slices it into pieces and creates several sorting jobs (by the number of sorting streams),
which it puts into the job queue. Sorting streams retrieve jobs, sort their parts of the file, return all results
output stream. The output stream waits for all sorted parts and merges them using a sort-merge method.
