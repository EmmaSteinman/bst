//Hannah Kerr and Emma Steinman
// movies.cpp
// A program that builds a Movie class and functions to read in
// a text file and create a corresponding dictionary with title as key
// and cast list as value. Finally a function that returns the cast list given
// movie title
// November 1, 2017


#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

using namespace std;

class Movie
{
public:
  string title;
  string cast;

  bool operator< ( Movie& a) const
  {
    return this->title <= a.title;
  };
  bool operator> (const Movie& a)           //overloading comparison operators
  {                                         //to compare key specifically
    return this->title > a.title;
  };
  bool operator== (const Movie& a)
  {
    return this->title == a.title;
  };
  bool operator!= (const Movie& a)
  {
    return this->title != a.title;
  };

  friend ostream & operator<< (ostream &os, const Movie &mov)   //overloading
  {                                                            //cout operator
      os << mov.cast;
      return os;
  };
};
//------------------------------------------------------------------------
//movieDict
//takes string of text file as parameter and reads in and separates
//and creates a dictionary of movie titles and cast lists and returns
//said dictionary
//------------------------------------------------------------------------
Dictionary<Movie> movieDict(string movieFile)
{
  ifstream file;
  file.open(movieFile);
  string line;
  Dictionary<Movie> movieDictionary;
  while (file)
  {
    getline(file, line);
    int index = line.find('\t');
    Movie *mov = new Movie;
    mov->title = line.substr(0, index);
    mov->cast = line.substr(index+1);
    //cout << mov->title << endl;
    movieDictionary.insert(mov);
  }
  file.close();
  return movieDictionary;
}
//------------------------------------------------------------------------
//getCast
//takes the key representing movie title for which you want cast
//as a parameter and returns corresponding cast lists
//------------------------------------------------------------------------
Movie getCast (string movieTitle)
{
  Dictionary<Movie> movies = movieDict("movies_mpaa.txt");
  Movie *search = new Movie;
  search->title = movieTitle;
  Movie castList = *(movies.get(*search));
  return castList;
}
//------------------------------------------------------------------------
//see it works!
//------------------------------------------------------------------------
int main(void)
{
  cout << "When Evil calls: " << endl;
  cout << getCast("\"When Evil Calls\" (2006)");
  cout << endl;
  cout << "27 Dresses (2008): " << endl;
  cout << getCast("27 Dresses (2008)");
  cout << endl;
  cout << "300 (2006): " << endl;
  cout << getCast("300 (2006)");
  cout << endl;
  cout << "A Knight's Tale (2001): " << endl;
  cout << getCast("A Knight's Tale (2001)");

}
