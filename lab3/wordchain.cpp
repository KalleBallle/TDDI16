#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm> 
#include <unordered_set> 
#include <unordered_map>

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

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras. 

 */ 

 vector<string> find_neh(Dictionary const& dict, string curr, std::unordered_map<string, string> &graph )
 {   
    vector<string> res{}; 
    for(int i{};i<4; ++i) 
    {   
        char imposter_char {curr[i]};  
        for(char cha{'a'}; cha <= 'z'; ++cha) 
        {  
            if(cha != imposter_char)
            {
                curr[i] = cha;
                
                if ( !graph.count(curr) && dict.count(curr) ) 
                {  
                    res.push_back(curr);    
                } 
            } 
        }       
    curr[i] = imposter_char;
    }  
return res;
} 
      
 
vector<string> find_shortest(Dictionary const& dict, const string &from, const string &to) { 
    vector<string> result{};
    std::unordered_map<string , string> graph ; 

    graph.insert({from,""});  
    std::queue<string> que ;  
    que.push(from);

	while (!que.empty()) {
		string curr = que.front(); que.pop(); 
        for(string word : find_neh(dict, curr, graph)) 
        { 
                graph.insert({word,curr});   
                que.push(word);
                if(word == to) 
                {                    
                    for(string s{to}; s != ""; s = graph[s])
                    {  
                        result.push_back(s);
                    } 
                    reverse(result.begin(),result.end()); 
                    break;
                }         
            }
        } 
    return result;                          
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(Dictionary const& dict, const string &from) {
    vector<string> result{};
    std::unordered_map<string, string> graph; 
    std::queue<string> que;

    graph.insert({from,""});  
    que.push(from);
    string curr{} ;
	while (!que.empty()) {
		curr = que.front(); que.pop(); 
        for(string word : find_neh(dict, curr, graph)) 
        { 
            //cout << que.size() << endl;
            graph.insert({word,curr});
            que.push(word);
        }
    } 
    for(string s{curr}; s != ""; s = graph[s])
    {  
        result.push_back(s);
    } 
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
void read_questions(Dictionary const& dict) {
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
