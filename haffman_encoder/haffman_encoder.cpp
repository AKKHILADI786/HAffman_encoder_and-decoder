#include<bits/stdc++.h>
using namespace std;
#define ll long long

class node{
    public:
    int val;
    char data;
    node *left;
    node *right;

    node(char ch,int val){
        data=ch;
        this->val=val;
        left=right=nullptr;
    }
    node(node *a,node *b){
        data='\0';
        val=a->val+b->val;
        left=a;
        right=b;
    }
};

class cmp{
    public:
    bool operator()(node *a,node *b){
        return a->val>b->val;
    }
};
void travers(unordered_map<char,string> &encoder,unordered_map<string,char> &decoder,node *table,string aa){
    if(table==NULL)return;
    if(table->left==NULL and table->right==NULL)
    {
        encoder[table->data]= aa;
        decoder[aa]=table->data;
        cout<<table->data<<" "<<aa<<endl;
        return;
    }
    string x=aa;
    if(table->left){
        aa+="0";
        travers(encoder,decoder,table->left,aa);
        aa=x;
    }
    if(table->right){
        aa+="1";
        travers(encoder,decoder,table->right,aa);
        aa=x;
    }
    return;
}
class Haffman{
    public:
    unordered_map<char,string> encoder;
    unordered_map<string,char> decoder;
    unordered_map<char,int> freq;
    priority_queue<node*,vector<node*>,cmp> data;
    string result="";
    bitset<1024> ans;
    int n;
    Haffman(string str){
        //1.make freq table
        for(int i=0;i<str.length();i++)
        {
            char ch=str[i];
            if(freq.count(ch)==0){
                freq[ch]=1;
            }
            else{
                freq[ch]++;
            }
        }

        //2. create priority queue
        for(auto it:freq){
            node *a=new node(it.first,it.second);
            data.push(a);
        }
        //3. combiing all the nodes

        while(data.size()>1)
        {
            node *one=data.top();
            data.pop();
            node *sec=data.top();
            data.pop();
            node *ans=new node(one,sec);
            data.push(ans);
        }
        //4. time to fill the encoder and decoder
        node *table=data.top();
        travers(encoder,decoder,table,"");
        // 5. encode the given string
        result="";
        for(int i=0;i<str.length();i++)
        {
            result+=encoder[str[i]];
        }
    }
    //***********************************************************//
    
    //thes type of things used for cvonvert to bitset and store them //

    // bitset<1024> encode(){// store the result in the form of bitset
    //     bitset<1024> ak(result);
    //     ans=ak;
    //     return ak;
    // }
    // string decoded_from_bitset(){
    //     return ans.to_string();
    // }

    //**********************************************************//
    void print(){
        cout<<result<<endl;
    }

    string decode(){
        string key="";
        string ans="";
        for(int i=0;i<=result.length();i++)
        {
            if(decoder.count(key)!=0){
                ans+=decoder[key];
                key="";
            }
            key+=result[i];
        }
        return ans;
    }
    

};

int main()
{
    string str;
    cin>>str;
    Haffman ans(str);
    ans.print();
    cout<<ans.decode()<<endl;
    return 0;
}