#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::queue;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef std::unordered_set<string> Dictionary;
Dictionary dict;

vector<string> find_neighbours(string word, const std::unordered_map<string, string> &graph) {
  vector<string> neighbours;

  for (size_t i = 0; i < word.size(); i++) {
    char orig = word[i];

    for (char ch = 'a'; ch <= 'z'; ch++) {
      if (ch != orig) {
        word[i] = ch;

        if (!graph.count(word) && dict.count(word)) {
          neighbours.push_back(word);
        }
      }
    }
    word[i] = orig;
  }
  return neighbours;
}

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const string &from, const string &to) {
  vector<string> result {};
  queue<string> q; 
  std::unordered_map<string, string> graph;

  graph.insert({from, ""}); q.push(from);

  while (!q.empty()) {
    string current = q.front(); q.pop();

    for (string word : find_neighbours(current, graph)) {
      graph.insert({word, current}); q.push(word);
      
      if (word == to) {
        while(word != from) {
          result.push_back(word);
          word = graph.find(word)->second;
        }
        result.push_back(from);

        std::reverse(result.begin(), result.end());
        return result;
      }
    }
  }
  return result; //returnar tom sträng, aka ingen lösning
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const string &to) {
  vector<string> result;
  queue<string> q; 

  std::unordered_map<string, string> graph;
  graph.insert({to, ""}); q.push(to);

  string current;
  while(!q.empty()) {
    current  = q.front(); q.pop();

    for (string word : find_neighbours(current, graph)) {
      graph.insert({word, current}); q.push(word);
    }
  }

  while(current != to) {
    result.push_back(current);
    current = graph.find(current)->second;
  }

  result.push_back(to);
  return result;
}

/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
  string line;
  vector<string> result;
  while (std::getline(std::cin, line)) {
    if (line == "#")
      break;

    result.push_back(line);
  }

  return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
  if (chain.empty())
    return;

  vector<string>::const_iterator i = chain.begin();
  cout << *i;

  for (++i; i != chain.end(); ++i)
    cout << " -> " << *i;

  cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const vector<string> &chain) {
  if (chain.empty()) {
    cout << "ingen lösning" << endl;
  } else {
    cout << chain.size() << " ord" << endl;
    print_chain(chain);
  }
}

/**
  vector<string> find_neighbours(const Dictionary &dict, const string &word) {
  vector<string> neighbours;


 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions() {
  string line;
  while (std::getline(std::cin, line)) {
    size_t space = line.find(' ');
    if (space != string::npos) {
      string first = line.substr(0, space);
      string second = line.substr(space + 1);
      vector<string> chain = find_shortest(first, second);

      cout << first << " " << second << ": ";
      print_answer(chain);
    } else {
      vector<string> chain = find_longest(line);

      cout << line << ": ";
      print_answer(chain);
    }
  }
}

int main() {
  dict = read_dictionary();
  read_questions();

  return 0;
}
