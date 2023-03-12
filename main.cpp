#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<cstring>
#include <random>
using namespace std;
class Meniu //clasa pentru creare meniu
{
private:
    string supa;
    string principal;
    string desert;
public:
    void citesteMeniu(int x) //citeste felurile de mancare din fisier si creaza un alt fisier cu cele 3 variante de meniu
    {
        string fname="meniu.csv";
        vector<string> row;
        vector<vector<string>> meniu;
        string line, word;
        fstream file (fname, ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();

                stringstream str(line);

                while(getline(str, word, ','))
                    row.push_back(word);
                meniu.push_back(row);
            }
        }
        file.close();
        fstream file1 ("meniu3.csv", ios::app);
        file1<<endl<<"VARIANTA "<<x<<endl;
        file1<<"---Meniu clasic---"<<endl;
        int poz = rand() % 8; //pe  7 pozitii se gasesste supa pentru cei care sunt apti sa manance orice
        supa=meniu[poz][0];
        poz = rand() % 9;//pe 9 pozitii se gaseste felul principal
        principal=meniu[poz+8][0];//felul principal se gaseste din pozitia 8
        poz = rand() % 7;
        desert=meniu[poz+17][0];
        file1<<"Felul 1: "<<supa<<endl<<"Felul 2: "<<principal<<endl<<"Desert: "<<desert<<endl;
        file1<<"---Meniu vegetarian---"<<endl;
        poz = rand() % 3;
        supa=meniu[poz+5][0];
        poz = rand() % 3;
        principal=meniu[poz+14][0];
        poz = rand() % 7;
        desert=meniu[poz+17][0];
        file1<<"Felul 1: "<<supa<<endl<<"Felul 2: "<<principal<<endl<<"Desert: "<<desert<<endl;
        file1<<"---Meniu flexitarian---"<<endl;
        poz = rand() % 5;
        supa=meniu[poz+3][0];
        poz = rand() % 6;
        principal=meniu[poz+11][0];
        poz = rand() % 7;
        desert=meniu[poz+17][0];
        file1<<"Felul 1: "<<supa<<endl<<"Felul 2: "<<principal<<endl<<"Desert: "<<desert<<endl;
        file1.close();





    }

};

class ResurseUmane
{
public:
    void adaugaFiguranti()//clasa pentru generare figuranti
    {
        fstream file ("personal.csv", ios::app);
        string names[] = {"Alice", "Bob", "Charlie", "Daisy", "Eve", "Frank", "Greta", "Hannah","Aiden", "Alexander", "Benjamin",
                          "Charlie", "Daniel", "Ethan", "William", "Michael", "Olivia", "Emily", "Abigail", "Sophia", "Isabella", "Mia", "Madison",
                          "Elizabeth", "Avery", "Ella", "Chloe", "Victoria", "Harper", "Scarlett", "Grace", "Chloe", "Cameron", "Liam", "Noah", "William",
                          "James", "Oliver", "Benjamin", "Elijah", "Lucas", "Mason", "Logan", "Alexander", "Ethan", "Michael","Ann"
                          "Benjamin", "Elijah", "James", "William", "Oliver", "Benjamin", "Elijah", "Lucas", "Mason", "Logan", "Alexander", "Ethan", "Michael"
                         };
        for (int i=1; i<=132; i++)
        {
            int poz=rand() % 30;//alegem nume1 din prima jumatate a vectorului names
            int poz2=rand() % 30+30; // alegem nume 2 din a doua jumatate
            file<< names[poz]<< " " <<names[poz2]<<','<<"figurant"<<endl;
        }

    }


};

class ActoriFiguranti
{
private:
    static int pret_mancare;
    static int pret_makeup;
    string mancare;
    string monstru;
public:
    string alegeMancarea() //generam random tipul de dieta
    {
        string tip[]= {"Apt pentru orice", "Vegetarian", "Flexitarian"};
        int poz=rand() % 3;
        if(poz==0)
            pret_mancare += 40;
        else if(poz==1)
            pret_mancare += 33;
        else
            pret_mancare += 46;
        mancare=tip[poz];
        return mancare;
    }
    string alegeMonstru() //calculam pretum machiajului pentru o persoana/zi
    {
        string tip[]= {"Vampir","Varcolac","Sirena","Clarvazator","Om"}; // generam random tipul de personaj-monstru pentru machiaj
        int poz=rand() % 5;
        if(poz==0)
            pret_makeup += 230; //adaugam la variabila de tip static pretul machiajului actual, aceasta variabila isi pastreaza valoarea la instantieri succesive
        else if(poz==1)
            pret_makeup += 555;
        else if(poz==2)
            pret_makeup += 345;
        else if(poz==3)
            pret_makeup += 155;
        else
            pret_makeup += 55;
        mancare=tip[poz];
        monstru=tip[poz];
        return monstru;
    }
    static int costZiMancare()
    {
        return pret_mancare;//returnam pretul mancarii/zi folosind varaibila statica
    }
    static int costZiMakeup()
    {
        return pret_makeup;
    }
};
int ActoriFiguranti::pret_mancare=0; //initializam varaibila statica in afara clasei
int ActoriFiguranti::pret_makeup=0;
class RestulPersonalului : public ActoriFiguranti // mostenim clasa Actori si Figuranti pentru a putea folosi metoda alegeMancarea
{
public:
    string alegereMonstru()
    {
        return "None";
    }

};

class Transport
{
public:
    void numarAutocare(int n)//calculam numarul de autocare
    {
        cout<<n/50+1;

    }
    virtual int cost(int n) //calculam costul total al transportului in lei, acesta nu se schimba in functie de perioada
    {
        return (n/50+1)*5680*2;
    }

};
class Cazare : public Transport // folosind tipul de data virtual putem reutiliza metodele definite mai sus
{
private:
    int cam3;
    int cam2;
public:
    int cost(int n) //calculam pertul total al cazarii
    {
        cam2=(n-132)/2;
        cam3=132/3;
        cam2=cam2*350;
        cam3=cam3*450;
        return cam2+cam3;
    }

};
void Total(int zile, int n, int c1, int c2, int c3) // generam cossturile totale in functie de perioada
{
    fstream file3("cost.csv", ios::app);
    float dolar=4.64;
    Transport autocar;
    Cazare camera;
    float cost_autocar=autocar.cost(n)/dolar;
    float cost_cazare=camera.cost(n)*zile/dolar;
    float cost_makeup=c1*zile/dolar;
    float cost_mancare=(c2+c3)*zile/dolar;
    float cost_apa=(n/2*6)*zile/dolar;
    float cost_chirie=(10000*zile - zile/10*(2/100)*10000*zile)/dolar; // aplicam reducerea chiriei in functie de numarul de zile

    file3<<"---Perioada de "<<zile<<" de zile---"<<endl;
    file3<<"Transport: "<<","<<int(cost_autocar)<<"$"<<endl;
    file3<<"Cazare: "<<","<<int(cost_cazare)<<"$"<<endl;
    file3<<"Machiaj: "<<","<<int(cost_makeup)<<"$"<<endl;
    file3<<"Mancare: "<<","<<int(cost_mancare)<<"$"<<endl;
    file3<<"Apa: "<<","<<int(cost_apa)<<"$"<<endl;
    file3<<"Inchiriere spatiu: "<<","<<int(cost_chirie)<<"$"<<endl<<endl;
    file3.close();

}

int main()
{
    //meniu pentru cele 3 zile
    Meniu meniul;
    meniul.citesteMeniu(1);
    meniul.citesteMeniu(2);
    meniul.citesteMeniu(3);

    ResurseUmane figuranti;
    figuranti.adaugaFiguranti();

    string fname="personal.csv";
    vector<string> row;
    vector<vector<string>> personal;
    string line, word;
    fstream file (fname, ios::in);
    fstream file2("date_personal.csv", ios::out);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            personal.push_back(row);
        }
    }
    ActoriFiguranti actorifiguranti;
    RestulPersonalului restul;
    string mancare, makeup;
    int n=0;
    file2<<"Nume"<<","<<"Functie"<<","<<"Dieta"<<","<<"Personaj"<<endl;
    for(int i=0; i<personal.size(); i++)
    {
        if( personal[i][1].find("actor",0)==0 || personal[i][1].compare("figurant")==0)//doar daca o persoana este actor sau figurant are nevoie de machiaj
        {
            mancare=actorifiguranti.alegeMancarea();
            makeup=actorifiguranti.alegeMonstru();
        }
        else
        {
            mancare=restul.alegeMancarea();
            makeup=restul.alegereMonstru();
        }
        file2<<personal[i][0]<<","<<personal[i][1]<<","<<mancare<<","<<makeup<<endl;//scriem in fisierul date_personal toate detaliile intregului personal
        n++;
    }
    file.close();
    file2.close();
    n++;

    int c1=actorifiguranti.costZiMakeup(); //salvam costurile returnate de metodele virtual pentru a putea calcula costul total in functie de numarul de zile
    int c2=actorifiguranti.costZiMancare();
    int c3=restul.costZiMancare();


    Total(30,n,c1,c2,c3);
    Total(45,n,c1,c2,c3);
    Total(60,n,c1,c2,c3);
    Total(100, n, c1,c2,c3);



    return 0;
}
