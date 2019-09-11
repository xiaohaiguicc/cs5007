/*
 *  Created by Adrienne Slaughter
 *  CS 5007 Spring 2019
 *  Northeastern University, Seattle
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "htll/LinkedList.h"
#include "MovieIndex.h"
#include "Movie.h"
#include "MovieReport.h"
#include "FileParser.h"


int main(int argc, char* argv[]) {

  // TODO: Parse command-line args to index based on the correct field (see getopt)
  extern int optind, optopt;
  enum IndexField field_to_index;
  char *filename;

  int opt;
  while ((opt = getopt(argc, argv, "tgy")) != -1) {
    char c = opt;
    printf("sorting by type: %c\n", c);
    switch (opt) {
      case 't':
        field_to_index = Type;
        break;
      case 'g':
        field_to_index = Genre;
        break;
      case 'y':
        field_to_index = Year;
        break;
      case 'i':
        field_to_index = Id;
        break;
      case '?':
        printf("Unrecognized option -%c\n", optopt);
        return 1;
    }
  }

  if (optind < argc) {
    filename = argv[optind];
  }
  LinkedList movie_list  = ReadFile(filename);
  Index index = BuildMovieIndex(movie_list, field_to_index);
  
  // TODO: Output report to file, rather than terminal (see MovieReport.h)
  PrintReport(index);
  SaveReport(index, "indexed_movies.txt");

  DestroyTypeIndex(index);
 
  return 0;
}

