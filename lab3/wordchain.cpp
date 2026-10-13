#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::queue; 

struct Node {                                                                                                                                                                             
    vector<string> neighbours;                                                                                                                                                                
    bool visited = false;                                                                                                                                                             
    string link;                                                                                                                                                                     
};                                                                                                                                                                                        


bool bfs(vector<Node> graph, string const& from, string const& to){
    queue<string> que; que.push(from);
    auto curr = find_if(graph.begin(), graph.end(), //curr börjar som start
    [&from](Node n){return n.link == from;});
    (*curr).visited = true;
    while (!((*curr).link ==  to)){
        for(string x : (*curr).neighbours){
            if(x == to){
                return true;
            } 
            if(!((*curr).visited)){
                (*curr).visited = true;
                que.push((*curr).link);
            }
        }
        ++curr;
    }

    return false;
}

/*
Kolla igenom allas neighbours. 
om vi hittar neighbour, add neighbour i que, kolla dens neighb.



*/



              

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef vector<string> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    vector<string> result;
    cout << "TODO: Implement me!" << endl;
    vector<Node> graph;     
    for(const string &word : dict)
   { 
    graph.push_back( Node{
        [dict,word](){ 
        vector<string> res;
        int score{0};
         for(const string &next_word : dict)
         { 
            for(int j{0}; j < 4; ++j) 
            {  
                if(word[j] == next_word[j])
                { 
                    ++score ;
                }                     
            } 
            if(score == 3) 
            { 
                res.push_back(next_word);
                //cout << word << " -> " << next_word << endl;
            }        
            score = 0;
        } 
         return res;}() , false, word});  
   } 
   
   /*for(int karl{0}; karl < graph.size(); ++karl){
       cout << graph[karl].link << " -> ";
   } cout << endl;
   */




   bfs(graph, from, to);

   return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result(1, word);
    cout << "TODO: Implement me!" << endl;
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
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
