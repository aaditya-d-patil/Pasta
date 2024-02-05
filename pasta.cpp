#include<iostream>
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<chrono>
#include<vector>
#include<windows.h>
#include<time.h>
using namespace std;

int COOKING_TIME_GLOBAL;                                                // Stores the time of the choosen pasta
vector<pair<string,int>> PASTA_TO_PLATE;                                 

void init();    
pair<string,int> sauceType();                                           // Selects the type of sauce: returns <sauce_name> and <time_to_make_sauce>
void cookingSauce(int SAUCE_TIME, string sauce);                        // Cooks sauce (timer)
void pastaCounter(string PASTA_TYPE,int cookingTime, int SAUCE_TIME);   // Cooks pasta (timer)
void printOptions(string PASTA_TYPE);                                   // Prints actions while pasta is being cooked
void select(string PASTA_TYPE,int cookingTime, int SAUCE_TIME);         // Performs the selected action

// enum to perform switch on string
enum pasta{
    Spaghetti,
    Penne,
    Fusilli,
    Cannelloni,
    Ravioli,
    not_a_pasta
};


//Returns the enum element referring to the string
pasta pastaHash(string& stringPasta){
    if(stringPasta == "Spaghetti" || stringPasta == "spaghetti") return Spaghetti;
    if(stringPasta == "Penne" || stringPasta == "penne") return Penne;
    if(stringPasta == "Fusilli" || stringPasta == "fusilli") return Fusilli;
    if(stringPasta == "Cannelloni" || stringPasta == "cannelloni") return Cannelloni;
    if(stringPasta == "Ravioli" || stringPasta == "ravioli") return Ravioli;

    return not_a_pasta;
}

void init(){
    cout<<"Hello mate! What pasta would you like to make today?\n";
    cout<<"-> Spaghetti"<<endl;
    cout<<"-> Penne"<<endl;
    cout<<"-> Ravioli"<<endl;
    cout<<"-> Cannelloni"<<endl;
    cout<<"-> Fusilli"<<endl;

    cout<<"\n\nChoice: ";
    string PASTA_TYPE;
    cin>>PASTA_TYPE;

    int cookingTime;
    switch (pastaHash(PASTA_TYPE)){
        case Spaghetti: //9 mins ~ 50 secs
            system("cls");

            cout<<"Pasta: SPAGHETTI\n";
            cout<<"\nThe long and the short of it: spaghetti, a timeless favorite, takes its time to unwind and "<<endl;
            cout<<"soften in the pot. In \033[1m9-12 minutes\033[0m, it transforms into a culinary masterpiece"<<endl;

            PASTA_TYPE = "SPAGHETTI";
            cookingTime = 50;
            break;
        
        case Penne: //10 mins ~ 60 secs
            system("cls");

            cout<<"Pasta: PENNE\n";
            cout<<"\nPenne, the classic charmer, takes its time to absorb the flavors, savoring the spotlight"<<endl;
            cout<<"for a solid  \033[1m10-12 minutes.\033[0m"<<endl;

            PASTA_TYPE = "PENNE";
            cookingTime = 60;
            break;

        case Ravioli:   
            system("cls");

            cout<<"Pasta: RAVIOLI\n";
            cout<<"\nRavioli is the proof that good things can come in small, flavorful packages."<<endl; 
            cout<<"It's the fast talker of the pasta world, with a cooking time as short as its wit."<<endl;

            cout<<"\nIs it fresh or dried? That's a 1 or 0 difference for me\n";
            cout<<"-> ";
            int ravioliType;
            cin>>ravioliType;
                if(ravioliType){    //4 mins  ~ 25 secs
                    cookingTime = 25;
                }
                else{               //8 mins  ~ 40 secs
                    cookingTime = 40;

                }

            PASTA_TYPE = "RAVIOLI";
            break;

        case Cannelloni:    //12 mins   ~ 80 secs
            system("cls");

            cout<<"Pasta: CANNELLONI\n";
            cout<<"\n Cannelloni pasta plays hard to get, but when boiled, it's ready to reveal its secrets"<<endl;
            cout<<"in about \033[1m10-12 minutes.\033[0m"<<endl;

            PASTA_TYPE = "CANNELLONI";
            cookingTime = 80;
            break;

        case Fusilli:   //8 mins  ~ 40 secs
            system("cls");

            cout<<"Pasta: FUSILLI\n";
            cout<<"\nFusilli, the fun-loving whirligig of the pasta family, spins into your plate in"<<endl;
            cout<<"just \033[1m8-10 minutes.\033[0m"<<endl;

            PASTA_TYPE = "FUSILLI"; 
            cookingTime = 40;
            break;

        default:

            cout<<"Sorry, m only your pasta buddy and to be honest I never imagined you in any different way.. ahem\n";
            cout<<"Hope you find good things in life. Bye\n";
            return;
    }

    Sleep(3000);
    //time to cook the type of sauce:
    pair<string,int> sauceDetails = sauceType();

    //Cooking sauce:
    system("cls");
    cout<<"Pasta: "<<PASTA_TYPE<<endl;
    cookingSauce(sauceDetails.second,sauceDetails.first);

    Sleep(2000);
    system("cls");

    COOKING_TIME_GLOBAL = cookingTime;
    pastaCounter(PASTA_TYPE,cookingTime, sauceDetails.second);

    

}

//Available options as you cook pasta 
void printOptions(string PASTA_TYPE){
    system("cls");
    cout<<"Pasta: "<<PASTA_TYPE<<endl;
    cout<<"Meanwhile you can:\n";
    cout<<"1. Time left to serve in the plate?\n";
    cout<<"2. Time left to add the sauce\n";
    cout<<"3. Can I add another pasta?\n";
    cout<<"Action: \n";
}

void select(string PASTA_TYPE,int cookingTime, int SAUCE_TIME){
    const int stirTime = 5; //5 sec

    int COOKING_TIME = COOKING_TIME_GLOBAL;

    // Total time to plate:
    int TIME_TO_PLATE = COOKING_TIME_GLOBAL;
    if(SAUCE_TIME == -1){
        TIME_TO_PLATE++;
    }
    else{
        TIME_TO_PLATE += stirTime;
    }

    vector<string> possible_pasta;      //Holds pastas that can be added newly into the pot

    switch (getch()){
        case 49:    // 1
            
            cout<<"\n->"<<TIME_TO_PLATE-(COOKING_TIME-cookingTime)<<" seconds to serve in the plate";

            Sleep(2000);
            system("cls");
            pastaCounter(PASTA_TYPE, cookingTime, SAUCE_TIME);
            break;
        
        case 50:    // 2
            if(SAUCE_TIME == -1){
                cout<<"\n->You chose for cheese dressing";
                cout<<"\n->"<<cookingTime+1<<" seconds to add dressing";
            }
            else{
                cout<<"\n->"<<cookingTime+1<<" seconds to add sauce";
            }

            Sleep(2000);
            system("cls");
            pastaCounter(PASTA_TYPE, cookingTime,  SAUCE_TIME);
            break;
        
        case 51:    // 3
            int possible_pasta_time;
            
            for(int i=0;i<PASTA_TO_PLATE.size();i++){
                if(cookingTime - PASTA_TO_PLATE[i].second > 0){
                    //Checking for Ravioli
                    if(!PASTA_TO_PLATE[i].first.compare("RavioliF")){
                        possible_pasta.push_back("Fresh Ravioli");
                    }
                    else if(!PASTA_TO_PLATE[i].first.compare("RavioliD")){
                        possible_pasta.push_back("Dried Ravioli");
                    }
                    else{
                        possible_pasta.push_back(PASTA_TO_PLATE[i].first);
                    }
                }
            }

            if(possible_pasta.size() == 0){
                cout<<"\n->Ain\'t possible now !\n";
            }
            else{
                //Printing the list of possible pastas
                cout<<"\n->List of pastas you can add right away: \n";
                for(int i=0;i<possible_pasta.size();i++){
                    cout<<"* "<<possible_pasta[i]<<endl;
                }

                //Clearing the array for future use
                possible_pasta.clear();
            }

            Sleep(4000);
            system("cls");
            pastaCounter(PASTA_TYPE, cookingTime,  SAUCE_TIME);
            break;
        
        default:
            break;
        }
}

void pastaCounter(string PASTA_TYPE,int cookingTime, int SAUCE_TIME){

    while(!kbhit() && cookingTime-- > 0){
        
        printOptions(PASTA_TYPE);
        Sleep(1000);
    }
    if(cookingTime<=0){
        
        system("cls");
        cout<<"Stiring your pasta in sauce & Dressing your pasta!!"<<endl;
        cout<<"[ah baby, m taken back to my old days]"<<endl;
        cout<<"\n* No actions are allowed now *"<<endl;
        Sleep(5000);
        system("cls");
        cout<<"Bon appetit ;)";
        Sleep(1000000000);
        
    }
    select(PASTA_TYPE, cookingTime, SAUCE_TIME);
    pastaCounter(PASTA_TYPE, cookingTime, SAUCE_TIME);
}

void cookingSauce(int SAUCE_TIME, string sauce){
    if(SAUCE_TIME == -1){
        return;
    }

    cout<<"Sauce: "<<sauce<<endl;

    int dots = SAUCE_TIME;
    while(SAUCE_TIME-- > 0){

        //printing progress bar
        std::cout<<"["; 
            for(int i=0;i<dots+1;i++) 
                if(i<dots-SAUCE_TIME) 
                    std::cout<<'='; 
                else if(i==dots-SAUCE_TIME) 
                    std::cout<<'>'; 
                else 
                    std::cout<<' '; 
            std::cout<<"] "<<'\r'; 


        Sleep(1000); // 1 sec
    }

    cout<<"\nYour Sauce is ready!\n";   

    cout<<"\n\nLet's get started with pasta now!"<<endl;
    
}

pair<string,int> sauceType(){

    int SAUCE_TIME;
    system("cls");
    cout<<"What sauce is your go to?\n";
    cout<<"-> Red\n";
    cout<<"-> White\n";
    cout<<"-> Pink\n";

    cout<<"\n\nChoice: ";

    string sauce;
    cin>>sauce;
    if(!sauce.compare("Red") || !sauce.compare("red")){
        //20 min ~ 8 sec
        cout<<"Your choice has been turning pasta into an Italian masterpiece since forever.\n"<<endl;

        SAUCE_TIME = 8;

        if(!sauce.compare("red")) cout<<"BTW, we call it \"Red\"\n";
        Sleep(7000);
    }
    else if(!sauce.compare("white") || !sauce.compare("White")){
        //10 min ~ 5 sec
        cout<<"Your choice is the unsung hero that turns pasta into a creamy symphony of deliciousness. AKA \"Alfredo\"\n"<<endl;

        SAUCE_TIME = 5;

        if(!sauce.compare("white")) cout<<"BTW, we call it \"White\"\n";
        Sleep(7000);
    }
    else if(!sauce.compare("Pink") || !sauce.compare("pink")){
        //10 min ~ 5 sec
        cout<<"Your choice has tomato and alfredo dance together.\n"<<endl;

        SAUCE_TIME = 5;

        if(!sauce.compare("pink")) cout<<"BTW, we call it \"Pink\"\n";
        Sleep(7000);
    }
    else{
        //1 sec
        cout<<"We don't make that here anymore. Let's just grate cheese on top later\n";

        SAUCE_TIME = -1;
        Sleep(7000);
    }

    return {sauce,SAUCE_TIME};
}



int main(){

    //List of pastas along with their cooking time
    PASTA_TO_PLATE.push_back({"RavioliF",25});
    PASTA_TO_PLATE.push_back({"RavioliD",40});
    PASTA_TO_PLATE.push_back({"Fusilli",40});
    PASTA_TO_PLATE.push_back({"Spaghetti",50});
    PASTA_TO_PLATE.push_back({"Penne",60});
    PASTA_TO_PLATE.push_back({"Cannelloni",80});

    init();

    Sleep(2000);

    return 0;
}