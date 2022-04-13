#include <iostream>
#include <bitset>
#include "math.h"

//szintezis parameterek
//data_length range 8 to 32
#define DATA_LENGTH 8
//canBeNegative can be true or false
#define CANBENEGATVIE false

using namespace std;

bool stateMachine(string &error, const int osztando, const int oszto, int &hanyados, int &maradek){

    if(oszto> pow(2,DATA_LENGTH)-1||osztando> pow(2,DATA_LENGTH)-1){
        error="Nem megfelelo bemeneti meret";
        return false;
    }

    if(oszto <= 0){
        error="Oszto<=0";
        return false;
    }

    if (osztando==0){
        hanyados=maradek=0;
        return true;
    }

    if(osztando==oszto){
        hanyados=1;
        maradek=0;
        return true;
    }

    bitset<DATA_LENGTH> hanyados_bin=0;
    bitset<DATA_LENGTH> osztando_bin=osztando;
    bitset<DATA_LENGTH> oszto_bin=oszto;
    bitset<DATA_LENGTH> temp_osztando_bin=0;
    int osztando_merete;
    int oszto_merete;
    int lepes;
    int meret_kulonbseg;
    bool isNegative = false;

    //TODO: delete, only for debug
    cout<<"BINARISAN"<<endl<<"Osztando: \t"<<osztando_bin<<endl<<"Oszto: \t\t"<<oszto_bin<<endl;
    //end of removable section

    if(CANBENEGATVIE){

        if (osztando_bin[DATA_LENGTH-1] == 1){
            osztando_bin ^= pow(2,DATA_LENGTH)-1;
            osztando_bin = osztando_bin.to_ullong()+1;
            isNegative = true;
        }
        cout<<osztando_bin;
    }

    if(osztando_bin.to_ullong()<oszto_bin.to_ullong()){
        hanyados=0;
        maradek=osztando_bin.to_ullong();
        return true;
    }

    //TODO: delete, only for debug
    cout<<"Oszto: ";
    for (int i = DATA_LENGTH-1; i >= 0; --i) {
        cout<<oszto_bin[i];
    }
    //end of removable section


    //Oszto merete
    lepes=0;
    while (oszto_bin[DATA_LENGTH-1-lepes]!=1){
        lepes++;
    }
    oszto_merete=DATA_LENGTH-lepes;
    cout<<endl<<"Oszto merete: "<<oszto_merete<<endl;
    //Osztando merete
    lepes = 0;
    while (osztando_bin[DATA_LENGTH-1-lepes]!=1){
        lepes++;
    }
    osztando_merete=DATA_LENGTH-lepes;
    cout<<endl<<"Osztando merete: "<<osztando_merete<<endl;
    //meret  kulonbseg
    meret_kulonbseg = osztando_merete-oszto_merete;

    //TEMP_OSZTANDO kezdeti allapota
    for (int i = 0; i < oszto_merete; ++i) {
        temp_osztando_bin[oszto_merete-i-1]=osztando_bin[osztando_merete-i-1];
    }
    cout<<endl<<"TEMP_osztando: "<<temp_osztando_bin<<endl;

    //
    //Szamitas kezdete
    cout<<endl<<"=========||=========="<<endl<<"Szamitas kezdete"<<endl;
    for (int i = 0; i < meret_kulonbseg; ++i) {
        cout<<"i: "<<i<<endl;
        cout<<"Kezdeti ertekek: "<<endl;
        cout<<"temp:\t"<<temp_osztando_bin<<endl;

        hanyados_bin<<=1;
        if(oszto_bin.to_ullong()>temp_osztando_bin.to_ullong()){
            hanyados_bin[0]=0;
        } else{
            hanyados_bin[0]=1;
            temp_osztando_bin=temp_osztando_bin.to_ullong()-oszto_bin.to_ullong();
        }

        temp_osztando_bin<<=1;
        temp_osztando_bin[0]=osztando_bin[meret_kulonbseg-i-1];

        cout<<"Vegso ertekek: "<<endl;
        cout<<"temp:\t"<<temp_osztando_bin<<endl;
        cout<<"hanyados:\t"<<hanyados_bin<<endl;
    }

    //
    //Utolso bit
    hanyados_bin<<=1;
    if(oszto_bin.to_ullong()>temp_osztando_bin.to_ullong()){
        hanyados_bin[0]=0;
    }else{
        hanyados_bin[0]=1;
        temp_osztando_bin=temp_osztando_bin.to_ullong()-oszto_bin.to_ullong();
    }

    //ha Negativ volt az osztando
    if (CANBENEGATVIE&&isNegative){
        hanyados_bin ^= pow(2,DATA_LENGTH)-1;
        hanyados_bin = hanyados_bin.to_ullong()+1;
    }//bitset nem kezeli le, hogy negativ lett, manualisan kell visszavaltani fejben

    hanyados=hanyados_bin.to_ullong();
    maradek=temp_osztando_bin.to_ullong();

    //TODO:delete, only for debug
    cout<<endl<<hanyados_bin<<endl;
    //end of removable section

    return true;
}

int main() {
    string errorStr = "";
    int osztando, oszto, hanyados, maradek;

    cin>>osztando;
    cin>>oszto;
    cout<<"Osztando: "<<osztando<<endl<<"Oszto: "<<oszto<<endl;

    if(!stateMachine(errorStr, osztando, oszto, hanyados, maradek)){
        cout<<"HIBA!: "<<errorStr;
    }else{
        cout<<endl<<"Hanyados: "<<hanyados<<endl<<"Maradek: "<<maradek<<endl;
    }


    cout <<endl<< "----"<<endl<<"Program vege!" << endl;
    return 0;
}
