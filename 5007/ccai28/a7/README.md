
```FileParser```:
Responsible for reading in a file, checking for errors, and parse out movies.


```Movie```:
A struct holding all the Movie info (id, title, type, genre, etc.)


```MovieIndex```:
A hashtable that indexes movies according to specified field. Basically wraps a hashtable with functionality specific to adding/removing/destroying with MovieSets. The key is the description for the document set, and the value is the document set.


```MovieReport```:
Responsible for printing out a report given a MovieIndex, to the command line or file.


```MovieSet```:
A set of Movies that are connected somehow: they have the same value for a given field. If the field is Year, all the movies in the set are made in the same year. It consists of a description and a LinkedList of Movies.

The basic tasks you need to complete:

* Modify main to accept flags on input and do the right thing.
* Modify Movie struct to hold an array of genres
* Modify MovieSet to ensure no duplicates of movies
* Bulk up tests

To do this, go through each file, and identify the "TODO" tags (listed below; generated with ```grep -n TODO *.c```). 

## A list of the TODOs and some more details

### TODOs where you should change the code/implement something

* example_indexer.c:17:  // TODO: Parse command-line args to index based on the correct field
* example_indexer.c:20:  // TODO: Output report to file, rather than terminal (see MovieReport.h)
* FileParser.c:45:  // TODO: Check that there is at least one movie
* Movie.c:14:  // TODO: Populate/Initialize movie.
* Movie.c:66:  // TODO: Change such that genres is an array, not just a string.
* MovieIndex.c:47:        // TODO: What to do if there are multiple genres? (Also make a note of what you did in the README)
* MovieIndex.c:71:      // TODO: how to deal with multiple genres?? 
* MovieReport.c:57:  // TODO: Implement this.
* MovieReport.c:63:  // TODO: Implement this. You might utilize OutputReport.
* test_movieindex.cc:61:  // TODO: Create from a improper row
* test_movieindex.cc:116:  // TODO: Implement this test.

### TODOs that you should address in your README.md

* FileParser.c:37:  // TODO: How big to make this hashtable? How to decide? What to think about?
* FileParser.c:55:      // TODO: What to do if there is a collision?
* MovieIndex.c:47:        // TODO: What to do if there are multiple genres? (Also implement it)
