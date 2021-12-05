#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>      
#include <ctime> 

using namespace std;

const int TotalFactors = 4;

int Count_Events() {      //count how many events are in the file. To determine the size of array used later.
    ifstream fin;
    string line, firstword;
    int c = 0;

    fin.open("events.txt");
    while (getline(fin, line)) {
        istringstream line_in(line);
        line_in >> firstword;
        if (firstword == "EVENT") {
            c++;
        }
    }
    fin.close();
    return c;
}

struct talent {
    int id;
    string name;
    string d;    //description of talents
    int result[TotalFactors];
    bool got_or_not = false;
};

struct event {
    int id;
    string d;  //description of events
    string A;
    int A_result[TotalFactors];
    string B;
    int B_result[TotalFactors];
    int day_range[2];
};

void Load_talents(talent* tl) {   //read in talents from the file 'talents.txt'
    ifstream fin;
    string line, word;
    int x = -1, num, value;
    fin.open("talents.txt");
    while (getline(fin, line)) {
        istringstream line_in(line);
        line_in >> word;
        if (word == "TALENTS") {
            x++;
            line_in >> num;
            tl[x].id = num;
        }
        else if (word == "description") {
            getline(fin, line);
            tl[x].d = line;
            getline(fin, line);
            istringstream line_in(line);
            line_in >> value;
            tl[x].result[0] = value;
            line_in >> value;
            tl[x].result[1] = value;
            line_in >> value;
            tl[x].result[2] = value;
            line_in >> value;
            tl[x].result[3] = value;
        }
        else if (word == "name") {
            getline(fin, line);
            tl[x].name = line;
        }

    }
    fin.close();
}

void Load_events(event* el) {  //read in events from file 'events.txt'
    ifstream fin;
    string line, word;
    int x = -1, num;
    int value;
    fin.open("events.txt");
    while (getline(fin, line)) {
        istringstream line_in(line);
        line_in >> word;
        if (word == "EVENT") {
            x++;
            line_in >> num;
            el[x].id = num;
        }
        else if (word == "DESCRIPTION") {
            getline(fin, line);
            el[x].d = line;
        }
        else if (word == "A") {
            getline(fin, line);
            el[x].A = line;
            getline(fin, line);
            istringstream line_in(line);
            line_in >> value;
            el[x].A_result[0] = value;
            line_in >> value;
            el[x].A_result[1] = value;
            line_in >> value;
            el[x].A_result[2] = value;
            line_in >> value;
            el[x].A_result[3] = value;
        }
        else if (word == "B") {
            getline(fin, line);
            el[x].B = line;
            getline(fin, line);
            istringstream line_in(line);
            line_in >> value;
            el[x].B_result[0] = value;
            line_in >> value;
            el[x].B_result[1] = value;
            line_in >> value;
            el[x].B_result[2] = value;
            line_in >> value;
            el[x].B_result[3] = value;
        }
        else if (word == "DayRange") {
            getline(fin, line);
            istringstream line_in(line);
            line_in >> value;
            el[x].day_range[0] = value;
            line_in >> value;
            el[x].day_range[1] = value;
        }
    }
    fin.close();
}

int Select_event(int day, event * el, int c, bool l) {          //randomly select a event id to show on screen. The probability of the occurrence of events will change due to days and lucky-factors.
    int n = 0;
    int j1 = 0, j2 = 0;
    for (int i = 0; i < c; i++) {
        if ((day > el[i].day_range[0]) && (day < el[i].day_range[1])) {
            n++;
            if (i < 17)
                j1++;
            else
                j2++;
        }
    }
    int* newlist = new int[n];
    int j = 0;
    for (int i = 0; i < c; i++) {
        if ((day > el[i].day_range[0]) && (day < el[i].day_range[1])) {
            newlist[j] = el[i].id;
            j++;
        }
    }
    if (l == false) {
        srand(time(NULL));
        int s = rand() % 10;
        if (s > 5) {
            int r = rand() % j1;
            return newlist[r];
        }
        else {
            int r = rand() % j2 + j1;
            return newlist[r];
        }
    }
    else {
        srand(time(NULL));
        int s = rand() % 10;
        if (s > 3) {
            int r = rand() % j1;
            return newlist[r];
        }
        else {
            int r = rand() % j2 + j1;
            return newlist[r];
        }
    }
    delete[] newlist;
}

void quit(int v1[], int v2[], int day, int num, talent* tl) {  //to quit the game, save all values into a file 'temp.txt'. It can be reused when opening the game program again.
    ofstream fout;
    fout.open("temp.txt");
    fout << num << " ";
    for (int i = 0; i < TotalFactors; i++) {
        fout << v1[i] << " " << v2[i] << " ";
    }
    fout << day << " ";
    for (int i = 0; i < 8; i++) {
        if (tl[i].got_or_not == true) {
            fout << i << " ";
        }
    }
    fout.close();
}

int main()
{
    char x, s, t, y;
    int c, days, num, event_id, n, m;
    int values1[TotalFactors] = { 5,5,0,50 };
    int values[TotalFactors];
    bool lose = false, success = false, lucky = false;
    string losereason;

    cout << "Loading.......Please wait." << endl;
    c = Count_Events();
    event* Eventlist = new event[c];
    talent* Talentlist = new talent[8];
    Load_events(Eventlist);
    Load_talents(Talentlist);
    ifstream fin;
    fin.open("temp.txt");
    fin >> num;
    if (num == 0) {
        cout << "Please enter 's' to start the game!" << endl;
        cin >> x;
        if (x != 's') {
            cout << "Well, you can come to our game later." << endl;
            return 0;
        }
        cout << "You're starting to run a tech company. Start your career now!" << endl;
        days = 1;
    }
    else {
        cout << "Welcome back to the game!" << endl;
        for (int i = 0; i < TotalFactors; i++) {
            fin >> values[i] >> values1[i];
        }
        fin >> days;
        while (fin >> m) {
            Talentlist[m].got_or_not = true;
        }
    }
    fin.close();
    
    
    while (true) {
        if ((num == 3) && (days == 1)) {    //Lucky-talent, which affects the probability of occurrence of events.
            cout << "Congrats! You unlocked a new special talent----Lucky_Man. (Increases the probability of occurence of positive events)" << endl;
            lucky = true;
            for (int i = 0; i < TotalFactors; i++) {
                values[i] = values1[i];
            }
        }
        else if (days == 1) {    //select a talents. Notice that talents are stackable. (Once you fail, you can gain a new talent next round.)
            cout << "You can select a 'Talent' which help you run the company." << endl;
            cout << "The talents you select will not be removed until your success." << endl;
            for (int i = 0; i < 8; i++) {
                if (Talentlist[i].got_or_not == false) {
                    cout << "Talent" << i+1 << " " << Talentlist[i].name << " : " << Talentlist[i].d << endl;                    
                }    
            }
            cout << "Please enter a number.(1-8)" << endl;
            cin >> n;
            for (int j = 0; j < TotalFactors; j++) {
                values1[j] += Talentlist[n-1].result[j];
            }
            Talentlist[n-1].got_or_not = true;
            for (int i = 0; i < TotalFactors; i++) {
                values[i] = values1[i];
            }
        }
        num++;        
        while (true) {
            cout << "Day: " << days << endl;
            event_id = Select_event(days, Eventlist, c, lucky);
            cout << Eventlist[event_id - 1].d << endl;
            cout << "A: " << Eventlist[event_id - 1].A << endl;
            cout << "B: " << Eventlist[event_id - 1].B << endl;

            cin >> s;
            if ((s == 'p') || (s == 'P')) {
                cout << "Game Paused" << endl;
                cout << "Continue: please answer 'a' or 'b'" << endl;
                cout << "Quit the game: enter 'q'" << endl;
                cin >> t;
                if (t == 'q') {
                    quit(values, values1, days, num, Talentlist);
                    cout << "The game progress has been saved. Bye!" << endl;
                    return 0;
                }
                s = t;
            }
            if ((s == 'a') || (s == 'A')) {
                for (int i = 0; i < TotalFactors; i++) {
                    values[i] += Eventlist[event_id - 1].A_result[i];
                }
                values[3] += values[2];
                cout << "integrity: " << values[0] << endl;
                cout << "influence: " << values[1] << endl;
                cout << "monthly profit: " << values[2] << endl;
                cout << "total asset: " << values[3] << endl;
                cout << " " << endl;
            }
            else if ((s == 'b') || (s == 'B')) {
                for (int i = 0; i < TotalFactors; i++) {
                    values[i] += Eventlist[event_id - 1].B_result[i];
                }
                values[3] += values[2];
                cout << "integrity: " << values[0] << endl;
                cout << "influence: " << values[1] << endl;
                cout << "monthly profit: " << values[2] << endl;
                cout << "total asset: " << values[3] << endl;
                cout << " " << endl;
            }
            else if ((s == 'q') || (s == 'Q')) {
                quit(values, values1, days, num, Talentlist);
                cout << "The game progress has been saved. Bye!" << endl;
                return 0;
            }
            else {
                cout << "invalid answer." << endl;
                continue;
            }
            for (int i = 0; i < TotalFactors; i++) {
                if (values[i] < 0) {
                    if (i == 0) {
                        losereason = "your company's image of integrity suffered a blow.";
                    }
                    if (i == 1) {
                        losereason = "your company didn't have enough influence.";
                    }
                    if (i == 2) {
                        losereason = "your company has no profit this month.";
                    }
                    if (i == 3) {
                        losereason = "your company is lack of money!";
                    }
                    lose = true;
                }
            }
            days += 30;
            if (lose == true) {
                days = 1;
                break;
            }
            if (days >= 600) {
                success = true;
                cout << "Perfect! You have successfully run the company 600 days. You are an excellent manager!" << endl;
                break;
            }
        }
        if (lose == true) {
            lose = false;
            cout << "Sorry! You failed because " << losereason << endl;
            cout << "Try again? enter a letter except 'q'." << endl;
            cout << "quit: enter 'q'" << endl;
            cin >> y;
            if (y == 'q') {
                quit(values, values1, days, num, Talentlist);
                return 0;
            }
        }
        if (success == true) {
            delete[] Eventlist;
            delete[] Talentlist;
            return 0;
        }
    }
    
    return 0;
    
}
