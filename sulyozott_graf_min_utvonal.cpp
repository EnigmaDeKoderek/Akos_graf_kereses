#include <iostream>
#include <vector>
#include <fstream>
#include <list>

using namespace std;

struct graf{
    string csucs;
    vector<string> el;
};

struct sulyuzottGraf{
    string csucs;
    vector<string> el;
    vector<int> suly;
};

struct utvonal{
    vector<string> ut;
    int uthossz;
};

void feltolt(vector<graf> &tarol, string cs, vector<string> be){
    graf g;
    g.csucs=cs;
    g.el=be;
    tarol.push_back(g);
}

void feltoltSulyozott(vector<sulyuzottGraf> &tarolSulyozott, string cs, vector<string> elBe, vector<int> sulyBe){
    sulyuzottGraf g;
    g.csucs=cs;
    g.el=elBe;
    g.suly=sulyBe;
    tarolSulyozott.push_back(g);
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

void graf_sulyozott_keszit(vector<sulyuzottGraf> &tarolSulyozott){
    vector<string> elBe;
    vector<int> sulyBe;

    elBe.clear();
    elBe={"B","C","D"};
    sulyBe.clear();
    sulyBe={10,1,1};
    feltoltSulyozott(tarolSulyozott,"A",elBe,sulyBe);

    elBe.clear();
    elBe={"A","C","E"};
    sulyBe.clear();
    sulyBe={10,1,1};
    feltoltSulyozott(tarolSulyozott,"B",elBe,sulyBe);

    elBe.clear();
    elBe={"A","B"};
    sulyBe.clear();
    sulyBe={1,1};
    feltoltSulyozott(tarolSulyozott,"C",elBe,sulyBe);

    elBe.clear();
    elBe={"A","E"};
    sulyBe.clear();
    sulyBe={1,7};
    feltoltSulyozott(tarolSulyozott,"D",elBe,sulyBe);

    elBe.clear();
    elBe={"B","D"};
    sulyBe.clear();
    sulyBe={1,1};
    feltoltSulyozott(tarolSulyozott,"E",elBe,sulyBe);
}

int grafCsucsIndex(vector<graf> tarol, string adottCsucs){
    for (size_t i=0;i<tarol.size();i++)
    {
        if (tarol[i].csucs==adottCsucs) {return i;};
    }
}

int graf_sulyozott_csucsIndex(vector<sulyuzottGraf> tarolSulyozott, string adottCsucs){
    for (size_t i=0;i<tarolSulyozott.size();i++)
    {
        if (tarolSulyozott[i].csucs==adottCsucs) {return i;};
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

int graf_sulyozott_csucs_minIndex(vector<utvonal> be){
    int minIndex=0;
    int minimum=be[0].uthossz;

    for (size_t i=1;i<be.size();i++){
        if (be[i].uthossz<minimum)
        {
            minimum=be[i].uthossz;
            minIndex=i;
        }
    }

    return minIndex;
}

utvonal keres_sulyozott(vector<sulyuzottGraf> tarolSulyozott, string honnan, string hova){
    cout << "Honnan: " << honnan << " hova: " << hova << endl;

    vector<utvonal> u;
    utvonal seged;
    string u_nev;
    int u_hossz;
    u_nev=honnan;
    u_hossz=0;

    seged.ut.push_back(u_nev);
    seged.uthossz=u_hossz;

    u.push_back(seged);

    int jelenlegiIndex;
    int jelenlegiHossz;
    vector<string> jelenlegiUtvonal;

    int csucsIndex;

    while (u[graf_sulyozott_csucs_minIndex(u)].ut.back() != hova){
        jelenlegiIndex=graf_sulyozott_csucs_minIndex(u);
        jelenlegiUtvonal=u[jelenlegiIndex].ut;
        jelenlegiHossz=u[jelenlegiIndex].uthossz;
        csucsIndex=graf_sulyozott_csucsIndex(tarolSulyozott,jelenlegiUtvonal.back());

        for (size_t i=0;i<tarolSulyozott[csucsIndex].el.size();i++){
            seged.ut.clear();
            seged.ut=jelenlegiUtvonal;
            seged.uthossz=jelenlegiHossz;

            bool megnincs=true;

            for (size_t j=0;j<jelenlegiUtvonal.size();j++)
            {
                if (tarolSulyozott[csucsIndex].el[i] == jelenlegiUtvonal[j]){
                    megnincs=false;
                }
            }
            if (megnincs){
                seged.ut.push_back(tarolSulyozott[csucsIndex].el[i]);
                seged.uthossz+=tarolSulyozott[csucsIndex].suly[i];

                /*cout<< "Aktualis utvonal: " <<endl;
                for (int i=0;i<seged.ut.size();i++){
                    cout << seged.ut[i] << " " << seged.uthossz << " " <<endl;
                }*/

                u.push_back(seged);
            }
        }
        u.erase(u.begin()+jelenlegiIndex);
    }
    return u[graf_sulyozott_csucs_minIndex(u)];
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
    vector<sulyuzottGraf> tarolSulyozott;
    graf_keszit(tarol);
    graf_sulyozott_keszit(tarolSulyozott);
    /*kiir(tarol);

    //------------------------------------------------------------

    keres(tarol,"A", "F");
    bejar(tarol,"B");*/

    utvonal ki;
    ki = keres_sulyozott(tarolSulyozott,"A","B");

    cout << "Legjobb utvonal: " << endl;
    for (int i=0;i<ki.ut.size();i++){
        cout << ki.ut[i] <<  " ";
    }
    cout << endl << "Uthossz " << ki.uthossz << " " <<endl;

    return 0;
}
