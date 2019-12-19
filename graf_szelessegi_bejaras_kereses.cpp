#include <iostream>
#include <vector>
#include <fstream>
#include <list>

using namespace std;

struct graf{
    string csucs;
    vector<string> el;
};

void feltolt(vector<graf> &tarol, string cs, vector<string> be){
    graf g;
    g.csucs=cs;
    g.el=be;
    tarol.push_back(g);
}

void kiir(vector<graf> tarol){
    ofstream f("graf.dot");
    f << "graph graf {" << endl;

    for (size_t i=0;i<tarol.size();i++)
    {
        for (size_t j=0;j<tarol[i].el.size();j++)
        {
            f << tarol[i].csucs << " -- " <<tarol[i].el[j] << endl;
        }
    }

    f << "}";
    f.close();

}

void graf_keszit(vector<graf> &tarol){
    vector<string> be;
    be.clear();
    be.push_back("C");
    be.push_back("D");
    be.push_back("H");
    feltolt(tarol,"A",be);

    be.clear();
    be.push_back("D");
    feltolt(tarol,"B",be);

    be.clear();
    be.push_back("A");
    be.push_back("E");
    feltolt(tarol,"C",be);

    be.clear();
    be.push_back("A");
    be.push_back("B");
    be.push_back("F");
    feltolt(tarol,"D",be);

    be.clear();
    be.push_back("C");
    be.push_back("G");
    be.push_back("H");
    feltolt(tarol,"E",be);

    be.clear();
    be.push_back("D");
    be.push_back("G");
    feltolt(tarol,"F",be);

    be.clear();
    be.push_back("E");
    be.push_back("F");
    feltolt(tarol,"G",be);

     be.clear();
    be.push_back("A");
    be.push_back("E");
    feltolt(tarol,"H",be);
}

int grafCsucsIndex(vector<graf> tarol, string adottCsucs){
    for (size_t i=0;i<tarol.size();i++)
    {
        if (tarol[i].csucs==adottCsucs) {return i;};
    }
}

void keres(vector<graf> tarol, string honnan, string hova){
    int jelenlegiIndex = jelenlegiIndex=grafCsucsIndex(tarol,honnan);
    string currentPoint=tarol[jelenlegiIndex].csucs;
    list<vector<string> > szomszedok;

    vector<string> be;
    be.clear();
    be.push_back(honnan);

    szomszedok.push_back(be);

    cout << "Honnan: " << honnan << " Hova: " << hova << endl;

    while (szomszedok.front().back() != hova)
    {
        jelenlegiIndex=grafCsucsIndex(tarol,szomszedok.front().back());
        for (size_t i=0;i<tarol[jelenlegiIndex].el.size();i++)
        {
            be.clear();
            be=szomszedok.front();
            bool megnincs=true;
            for (size_t j=0;j<be.size();j++)
            {
                if (tarol[jelenlegiIndex].el[i]==be[j])
                {
                    megnincs=false;
                }
            }
            if (megnincs)
            {
                 be.push_back(tarol[jelenlegiIndex].el[i]);
                 szomszedok.push_back(be);
                 currentPoint=tarol[jelenlegiIndex].el[i];
            }
        }

        szomszedok.pop_front();
    }

    for (size_t i=0;i<szomszedok.front().size();i++)
    {
        cout<<szomszedok.front()[i];
    }
    cout<<endl;

}

void bejar(vector<graf> tarol, string honnan){
    int jelenlegiIndex = jelenlegiIndex=grafCsucsIndex(tarol,honnan);
    list<vector<string> > szomszedok;

    vector<string> be;
    vector<string> megvoltcsucsok;
    megvoltcsucsok.push_back(honnan);
    be.clear();
    be.push_back(honnan);

    szomszedok.push_back(be);

    cout << "Honnan: " << honnan << endl;

    while (megvoltcsucsok.size() != tarol.size())
    {
        jelenlegiIndex=grafCsucsIndex(tarol,szomszedok.front().back());
        for (size_t i=0;i<tarol[jelenlegiIndex].el.size();i++)
        {
            be.clear();
            be=szomszedok.front();
            bool megnincs=true;
            for (size_t j=0;j<megvoltcsucsok.size();j++)
            {
                if (tarol[jelenlegiIndex].el[i]==megvoltcsucsok[j])
                {
                    megnincs=false;
                }
            }
            if (megnincs)
            {
                megvoltcsucsok.push_back(tarol[jelenlegiIndex].el[i]);
                be.push_back(tarol[jelenlegiIndex].el[i]);
                szomszedok.push_back(be);
            }
        }

        szomszedok.pop_front();
    }

    for (size_t i=0;i<megvoltcsucsok.size();i++)
    {
        cout<<megvoltcsucsok[i];
    }
    cout<<endl;

}

int main()
{
    vector<graf> tarol;
    graf_keszit(tarol);
    kiir(tarol);

    //------------------------------------------------------------

    keres(tarol,"A", "F");
    bejar(tarol,"B");

   // cout << "Hello world!" << endl;
    return 0;
}
