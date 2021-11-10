#include<bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
#define indexOf(c) ((int)c - (int)'a')

// trie node
class TrieNode
{   public:
    TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
    
    //  methods
    TrieNode* getNode(string word);
    TrieNode* insert(TrieNode *root, string key);
    void insertToMap(fstream& dictFile, unordered_map<string, string> & dictMap, string st);
    void createDictionary(fstream& dictFile, unordered_map<string, string>& dictMap);
    void lowerCase(string & str);
    void createFileTree(fstream & newfile, vector<string> & words, TrieNode* root);
    void suggestionsRec(TrieNode* root, string currPrefix);
    int printAutoSuggestions(TrieNode* root, const string query);
    bool isLastNode(TrieNode* root);
    bool search(TrieNode *root, const string key);

};
 
// Returns new trie node (initialized to NULLs)
TrieNode *getNode(void)
{
    TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(TrieNode *root, string key)
{
    TrieNode *trie_iterator = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!trie_iterator->children[index])
            trie_iterator->children[index] = getNode();
 
        trie_iterator = trie_iterator->children[index];
    }
 
    // mark last node as leaf
    trie_iterator->isEndOfWord = true;
}
 
// Returns true if key presents in trie, else false
bool search(TrieNode *root, const string key)
{
    int length = key.length();
    TrieNode *trie_iterator = root;
    for (int level = 0; level < length; level++)
    {
        int index = indexOf(key[level]);
 
        if (!trie_iterator->children[index])
            return false;
 
        trie_iterator = trie_iterator->children[index];
    }
 
    return (trie_iterator != NULL && trie_iterator->isEndOfWord);
}
 
// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool isLastNode(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}
 
// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << currPrefix;
        cout << endl;
    }
 
    // All children node pointers are NULL
    if (isLastNode(root))
        return;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix string
            currPrefix.push_back(97 + i);
 
            // recur over the rest
            suggestionsRec(root->children[i], currPrefix);
            // remove last character
            currPrefix.pop_back();
        }
    }
}
 
// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    TrieNode* trie_iterator = root;
 
    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given string.
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = indexOf(query[level]);
 
        // no string in the Trie has this prefix
        if (!trie_iterator->children[index])
            return 0;
 
        trie_iterator = trie_iterator->children[index];
    }
 
    // If prefix is present as a word.
    bool isWord = (trie_iterator->isEndOfWord == true);
 
    // If prefix is last node of tree (has no
    // children)
    bool isLast = isLastNode(trie_iterator);
 
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }
 
    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(trie_iterator, prefix);
        return 1;
    }
}
 
void createFileTree(fstream & newfile, vector<string> & words, TrieNode* root){
    newfile.open("C:/vscode_codes/ds_tries/words/unigram_freq.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            // cout << tp << ", "; //print the data of the string
            words.push_back(tp);
        }
        newfile.close(); 

    }
        cout<< words.size()<< " words allocated in the tree\n";
        int n= words.size(); 

        // Contrie
        for (int i = 0; i < n; i++){
            insert(root, words[i]);
        }
}
void lowerCase(string & str){
      for (int i = 0; i < (str.length()); i++) {
    // convert str[i] to lowercase
    str[i]= tolower(str[i]);
  }
}

void createDictionary(fstream& dictFile, unordered_map<string, string>& dictMap){
    
    dictFile.open("C:/vscode_codes/ds_tries/words/dictionary.txt",ios::in); //open a file to perform read operation using file object
    if (dictFile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(dictFile, tp)){ //read data from file object and put it into string.
            // cout << tp <<endl; //print the data of the string
            // each line has words seperated by "," with their meanings
            int pos = (tp.find(" "));
            string word= (tp.substr(0, pos));
            lowerCase(word);
            string meaning = (tp.substr(pos+1, tp.length()));
            lowerCase(meaning);
            // cout<< "word "<< word << " meaning "<< meaning<< endl;
            if(dictMap[word]!=""){
                string temp= dictMap[word];
                temp.append("\n \n");
                temp.append(meaning);
                dictMap[word]= temp;
            }else 
                dictMap[word]= meaning;
        }

    }
    dictFile.close(); 

}

void insertToMap(fstream& dictFile, unordered_map<string, string> & dictMap, string st){
    string meaning;
    cout<< "Enter one word meaning\n";
    cin>> meaning;
    dictFile.open("C:/vscode_codes/ds_tries/words/dictionary.txt",ios::app); //open a file to perform read operation using file object 

    if (dictFile.is_open()){ //checking whether the file is open
        dictFile<<"\n"<<st<<" "<<meaning;
        dictFile.close(); 
        dictMap[st]= meaning;
    }
    dictFile.close();
}
int main(){

    char cnt= 'n';
    vector<string> words;
    fstream dictFile, newfile;
    unordered_map<string, string> dictMap;
    string st, str;
    TrieNode *root = getNode();
    // Creating file
    createFileTree(newfile, words, root);
    createDictionary(dictFile, dictMap);

    do{
        system("cls");
        int choice=0;
        cout<<"--------------------------------------------------MENU-------------------------------------------------------------------------------\n";
        cout<< "1. Enter 1 to use word search + autocomplete feature \n2. Enter 2 to find meaning of a word \n3. Enter 3 to add a new word to the dictionary\n";
        cout<< "Enter your choice\n";
        cin>> choice;
        switch(choice){
            case 1:
                // Search for words
                cout<< "enter the item to search:\n";
                cin>> str;
                search(root, str)? cout << "Word found\nsearch suggestions are: \n" : cout << "Word not found\n";
                int ans;
                ans = printAutoSuggestions(root, str);            
                break;

            case 2: 
                //  dictionary part
                char preference;
                cout<<"enter the word to search the meaning\n";
                cin>> st;
                if(dictMap[st]!="")
                    cout<< "meaning of the word is \n"<< dictMap[st];
                else{
                    cout<< "meaning of the word does not exist\n";
                    cout<<"want to enter the meaning? in break (y/n)";
                    cin>> preference;
                    if(preference!= 'n')
                        insertToMap(dictFile, dictMap, st);
                }
                break;

            case 3: 
                cout<< "Enter the word \n";
                cin>> st;
                insertToMap(dictFile, dictMap, st);
                break;
            default:
                cout<< "wrong choice !! exiting";
                exit(0);

        }
        cout<< "\nWant to continue in while loop(y/n)?\n";
        cin>> cnt;
    }while(cnt!= 'n');
    
    return 0;
}
