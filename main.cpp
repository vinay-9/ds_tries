#include<bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
#define indexOf(c) ((int)c - (int)'a')

 
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *trie_iterator = root;
 
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
bool search(struct TrieNode *root, const string key)
{
    int length = key.length();
    struct TrieNode *trie_iterator = root;
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
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}
 
// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << currPrefix;
        cout << endl;
    }
 
    // All children struct node pointers are NULL
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
    struct TrieNode* trie_iterator = root;
 
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
 
void createFile(fstream & newfile, vector<string> & words, TrieNode* root){
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

        // Construct trie
        for (int i = 0; i < n; i++){
            insert(root, words[i]);
        }
}

void createDictionary(fstream& dictFile, unordered_map<string, string>& dictMap){
    
    dictFile.open("C:/vscode_codes/ds_tries/words/word_meaning.txt",ios::in); //open a file to perform read operation using file object
    if (dictFile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(dictFile, tp)){ //read data from file object and put it into string.
            // cout << tp <<endl; //print the data of the string
            // each line has words seperated by "," with their meanings
            int pos = tp.find(",");
            string word= tp.substr(0, pos);
            string meaning = tp.substr(pos+1, tp.length());
            // cout<< "word "<< word << " meaning "<< meaning<< endl;
            if(dictMap[word]!=""){
                string temp= dictMap[word];
                temp.append(", ");
                temp.append(meaning);
                dictMap[word]= temp;
            }else 
                dictMap[word]= meaning;
        }
        dictFile.close(); 

    }

}

void insertToMap(fstream& dictFile, unordered_map<string, string> & dictMap, string st){
    dictFile.open("C:/vscode_codes/ds_tries/words/word_meaning.txt",ios::app); //open a file to perform read operation using file object 
        cout<< "meaning of the word does not exists\n";
        cout<<"want to enter the meaning?(y/n)";
        char ans;
        cin>>ans;
        if(ans=='y'){
            string meaning;
            cout<< "Enter the meaning\n";
            cin>> meaning;
            if (dictFile.is_open()){ //checking whether the file is open
                dictFile<<st<<","<<meaning;
                dictFile.close(); 
                dictMap[st]= meaning;
            }
        }
}
int main(){
  
    vector<string> words;
    fstream dictFile, newfile;
    unordered_map<string, string> dictMap;
    string st, str;
    struct TrieNode *root = getNode();

    // Creating file
    createFile(newfile, words, root);
    
    
    // Search for words
    cout<< "enter the item to search:\n";
    cin>> str;
    search(root, "the")? cout << "Word found\n" : cout << "Word not found\n";
    
    cout<< "print autocomplete suggestions for:\n";
    cin>> str;
    int comp = printAutoSuggestions(root, str);

    
    //  dictionary part
    createDictionary(dictFile, dictMap);
    cout<<"enter the word to search the meaning\n";
    cin>> st;
    if(dictMap[st]!="")
        cout<< "meaning of the word is \n"<< dictMap[st];
    else{
        insertToMap(dictFile, dictMap, st);
    }
    

    return 0;
}
