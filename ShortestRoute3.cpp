// Lab 6, The Shortest Route 2 Program 
// Programmer: Connor Carpenter
// Editor(s) used: Visual Studio 2015
// Compiler(s) used: VC++ 2015 Express

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <vector>
using std::vector;

#include <string>
using std::string;

class Route;

class Leg {
  const char* startCity;
  const char* endCity;
  const int distance;
public:
  Leg(const char startCity[], const char endCity[], const int distance);
  Leg& operator=(const Leg& l);
  friend ostream& operator<<(ostream& out, const Leg& leg);
  friend ostream& operator<<(ostream&, const Route&);
  friend Route;
  friend class ShortestRoute;
};

Leg::Leg(const char startCity[], const char endCity[], const int distance)
  :startCity(startCity), endCity(endCity), distance(distance)
{
}

Leg & Leg::operator=(const Leg & l)
{
  this->startCity = l.startCity;
  this->endCity = l.endCity;
  const_cast<int&> (distance) = l.distance;
  return *this;
}

class Route {
  const Leg** const legs;
  const int nTimes;
  const double distance;
public:
  Route(const Leg&);
  Route(const Route&, const Leg&);
  Route(const Route&);
  
  ~Route();

  friend ostream& operator<<(ostream&, const Route&);
  
};

Route::Route(const Leg& l)
  :nTimes(1), distance(l.distance), legs(new const Leg*[1])
{
  legs[0] = &l;
}

Route::Route(const Route& r, const Leg& l)
  : nTimes(r.nTimes + 1), distance(r.distance + l.distance), legs(new const Leg*[r.nTimes + 1])
{
  for (int i = 0; i < r.nTimes; i++) {
    legs[i] = r.legs[i];
  }

  legs[r.nTimes] = &l;
}

Route::Route(const Route& r)
  : nTimes(r.nTimes), distance(r.distance), legs(new const Leg*[r.nTimes])
{
  for (int i = 0; i < r.nTimes; i++) {
    legs[i] = r.legs[i];
  }
}

Route::~Route() {
  delete[] legs;
}

class ShortestRoute {
  static vector<Leg> allLegs;
  ShortestRoute(){};
public:
  static void initialize();
  static const Route getAnyRoute(const string from, const string to);
  static const Route getShortestRoute(const string from, const string to);
  
};

vector<Leg> ShortestRoute::allLegs;

const Route ShortestRoute::getAnyRoute(const string from, const string to)
{
  bool found = false;
  int indexOfLeg = 0;
  int size = allLegs.size();
  for (int i = 0; i < size && !found; i++) {
    if (allLegs[i].endCity == to) {
      indexOfLeg = i;
      found = true;
    }
  }
  if (allLegs[indexOfLeg].startCity == from) {
    return Route(allLegs[indexOfLeg]);
  }
  else {
    return Route(getAnyRoute(from, allLegs[indexOfLeg].startCity), allLegs[indexOfLeg]);
  }
}

const Route ShortestRoute::getShortestRoute(const string from, const string to)
{
 
  vector<int> indexOfLegs; //All valid legs leading to "to"
  int size = allLegs.size();
  for (int i = 0; i < size; i++) {
    if (allLegs[i].endCity == to) {
      indexOfLegs.push_back(i);
    }
  }
  int indexOfShortestLeg = indexOfLegs[0];
  size = indexOfLegs.size();
  if(indexOfLegs.size() != 1){
    for (int i = 1; i < size; i++) {
      if (allLegs[indexOfLegs[i]].distance < allLegs[indexOfShortestLeg].distance) {
        indexOfShortestLeg = indexOfLegs[i];
      }
    }
  }
  if (allLegs[indexOfShortestLeg].startCity == from) {
    return Route(allLegs[indexOfShortestLeg]);
  }
  else {
    return Route(getShortestRoute(from, allLegs[indexOfShortestLeg].startCity), allLegs[indexOfShortestLeg]);
  }
}

int main() {
  ShortestRoute::initialize();
  cout << ShortestRoute::getAnyRoute("San Francisco", "New York City");
  cout << ShortestRoute::getShortestRoute("San Francisco", "New York City");
  return 0;
}

ostream& operator<<(ostream& out, const Leg& leg) {
  out << leg.startCity << " to " << leg.endCity << ", " << leg.distance << " mile(s)" << endl;
  return out;
}
ostream& operator<<(ostream & out, const Route& r) {
  out << r.legs[0]->startCity << " to ";
  for (int i = 1; i < r.nTimes - 1; i++) {
    out << r.legs[i]->endCity << " to ";
  }
  out << r.legs[r.nTimes - 1]->endCity << ", " << r.distance << " miles." << endl << endl;
  return out;
}

void ShortestRoute::initialize()
{
  //allLegs.push_back(Leg("San Francisco", "Las Vegas", 600));
  //allLegs.push_back(Leg("Boise", "Salt Lake City", 340));
  //allLegs.push_back(Leg("Phoenix", "Albuquerque", 422));
  //allLegs.push_back(Leg("Albuquerque", "Denver", 450));
  //allLegs.push_back(Leg("Albuquerque", "Austin", 700));
  //allLegs.push_back(Leg("Salt Lake City", "Denver", 530));
  //allLegs.push_back(Leg("Salt Lake City", "Licoln", 884));
  //allLegs.push_back(Leg("Licoln", "Nashville", 750));
  //allLegs.push_back(Leg("Dallas", "Chicago", 970));
  //allLegs.push_back(Leg("Boise", "Denver", 835));
  //allLegs.push_back(Leg("San Francisco", "Boise", 650));
  //allLegs.push_back(Leg("Nashville", "Columbus", 380));
  //allLegs.push_back(Leg("Chicago", "Columbus", 360));
  //allLegs.push_back(Leg("San Francisco", "Reno", 220));
  //allLegs.push_back(Leg("Chicago", "Detroit", 280));
  //allLegs.push_back(Leg("Columbus", "Buffalo", 330));
  //allLegs.push_back(Leg("Reno", "Salt Lake City", 520));
  //allLegs.push_back(Leg("Reno", "Boise", 420));
  //allLegs.push_back(Leg("Denver", "Licoln", 490));
  //allLegs.push_back(Leg("Dallas", "New Orleans", 505));
  //allLegs.push_back(Leg("Dallas", "Atlanta", 780));
  //allLegs.push_back(Leg("Dallas", "Nashville", 660));
  //allLegs.push_back(Leg("New Orleans", "Atlanta", 470));
  //allLegs.push_back(Leg("Atlanta", "Charleston", 310));
  //allLegs.push_back(Leg("Nashville", "Charleston", 550));
  //allLegs.push_back(Leg("Charleston", "Washington D.C.", 530));
  //allLegs.push_back(Leg("Nashville", "Washington D.C.", 665));
  //allLegs.push_back(Leg("Licoln", "Chicago", 520));
  //allLegs.push_back(Leg("Las Vegas", "Phoenix", 300));
  //allLegs.push_back(Leg("Austin", "Dallas", 200));
  //allLegs.push_back(Leg("Denver", "Austin", 510));
  //allLegs.push_back(Leg("New Orleans", "Nashville", 530));
  //allLegs.push_back(Leg("Atlanta", "Columbus", 570));
  //allLegs.push_back(Leg("Austin", "New Orleans", 512));
  //allLegs.push_back(Leg("Phoenix", "Dallas", 1065));
  //allLegs.push_back(Leg("Reno", "Phoenix", 745));
  //allLegs.push_back(Leg("Las Vegas", "Albuquerque", 575));
  //allLegs.push_back(Leg("Reno", "Las Vegas", 450));
  //allLegs.push_back(Leg("Columbus", "Philidelphia", 470));
  //allLegs.push_back(Leg("Buffalo", "New york City", 380));
  //allLegs.push_back(Leg("Washington D.C.", "Philidelphia", 140));
  //allLegs.push_back(Leg("Washington D.C.", "Jersey City", 220));
  //allLegs.push_back(Leg("Jersey City", "New York City", 7));
  //allLegs.push_back(Leg("Philidelphia", "New York City", 97));
  //allLegs.push_back(Leg("Philidelphia", "Jersey City", 90));
  //allLegs.push_back(Leg("Detroit", "Buffalo", 260));
  //allLegs.push_back(Leg("Buffalo", "Jersey City", 370));
  //allLegs.push_back(Leg("Charleston", "Buffalo", 862));

  // allLegs.push_back(Leg("", "", ));
  allLegs.push_back(Leg("Little Rock", "Nashville", 350));
  allLegs.push_back(Leg("Kansas City", "Nashville", 555));
  allLegs.push_back(Leg("Salt Lake City", "Denver", 521));
  allLegs.push_back(Leg("Salt Lake City", "Casper", 410));
  allLegs.push_back(Leg("Albuquerque", "Lubbock", 319));
  allLegs.push_back(Leg("Albuquerque", "Wichita", 593));
  allLegs.push_back(Leg("Denver", "Wichita", 520));
  allLegs.push_back(Leg("Washington D.C.", "New York City", 275));
  allLegs.push_back(Leg("Pittsburgh", "Scranton", 283)); 
  allLegs.push_back(Leg("Buffalo", "Scranton", 256 ));
  allLegs.push_back(Leg("Scranton", "New York City", 120));
  allLegs.push_back(Leg("Casper", "Rapid City", 266));
  allLegs.push_back(Leg("Denver", "Licoln", 485));
  allLegs.push_back(Leg("San Francisco", "Los Angeles", 383));
  allLegs.push_back(Leg("Los Angeles", "Las Vegas", 269));
  allLegs.push_back(Leg("Los Angeles", "Phoenix", 373));
  allLegs.push_back(Leg("Reno", "Las Vegas", 448));
  allLegs.push_back(Leg("Reno", "Salt Lake City", 520));
  allLegs.push_back(Leg("Phoenix", "Albuquerque", 422));
  allLegs.push_back(Leg("Casper", "Licoln", 573));
  allLegs.push_back(Leg("Louisville", "Roanoke", 430));
  allLegs.push_back(Leg("San Francisco", "Reno", 220));
  allLegs.push_back(Leg("Lubbock", "Little Rock", 664));
  allLegs.push_back(Leg("Lubbock", "Oklahoma City", 334 ));
  allLegs.push_back(Leg("Wichita", "Kansas City", 199 ));
  allLegs.push_back(Leg("Wichita", "Des Moines", 390));
  allLegs.push_back(Leg("Phoenix", "Denver", 821));
  allLegs.push_back(Leg("Columbus", "Pittsburgh", 185));
  allLegs.push_back(Leg("Columbus", "Buffalo", 327));
  allLegs.push_back(Leg("Detroit", "Pittsburgh", 286));
  allLegs.push_back(Leg("Detroit", "Buffalo", 255));
  allLegs.push_back(Leg("Licoln", "Des Moines", 185));
  allLegs.push_back(Leg("Rapid City", "Des Moines", 625 ));
 // allLegs.push_back(Leg("Oklahoma City", "Little Rock", 340));
  allLegs.push_back(Leg("Oklahoma City", "Kansas City", 354)); 
  allLegs.push_back(Leg("Little Rock", "Jackson", 260));
  allLegs.push_back(Leg("Louisville", "Columbus", 210));
  allLegs.push_back(Leg("Charlotte", "Roanoke", 196));
  allLegs.push_back(Leg("Indianapolis", "Columbus", 175));
  allLegs.push_back(Leg("Roanoke", "Washington D.C.", 245));
  allLegs.push_back(Leg("Kansas City", "Chicago", 510 ));
  allLegs.push_back(Leg("Jackson", "Atlanta", 380 ));
  allLegs.push_back(Leg("Jackson", "Nashville", 480));
  allLegs.push_back(Leg("Nashville", "Atlanta", 248));
  allLegs.push_back(Leg("Nashville", "Charlotte", 500 ));
  allLegs.push_back(Leg("Nashville", "Louisville", 175));
  allLegs.push_back(Leg("Chicago", "Detroit", 280 ));
  allLegs.push_back(Leg("Chicago", "Indianapolis", 185));
  allLegs.push_back(Leg("Atlanta", "Charlotte", 245));

  allLegs.push_back(Leg("San Francisco", "New York City", 21000));
}

