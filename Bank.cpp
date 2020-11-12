#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;


class date
{
protected :
    int day;
    int month;
    int year;
public : date(string dd="1",string mm="1", string yy="2020")
    {
        stringstream to_intd(dd);
        int d = 0;
        to_intd >> d;
        stringstream to_intm(mm);
        int m = 0;
        to_intm >> m;
        stringstream to_inty(yy);
        int y = 0;
        to_inty >> y;
        if (d<32 && d>0 &&m>0 &&m<13 &&y>0)
           {
            day=d;month=m;year=y;}
        else
            {cout<<"error in date inputs";
            }
    }
    void print_date(){cout<<day<<"/"<<month<<"/"<<year<<endl;}
    int compare (date x )
    {
        if (year < x.year)
            return -1 ;
        if (year > x.year)
            return 1 ;
        if (year = x.year)
        {
            if (month < x.month)
            return -1 ;
            if (month > x.month)
            return 1 ;
            if (month = x.month)
            {
                if (day < x.day)
                return -1 ;
                if (day > x.day)
                return 1 ;
                if (day = x.day)
                    return 0;
            }
        }
    }
};

/////////////////////////exchange rate class ////////////////////////////

class exchange
{
private :
    static int nextex_ID  ;
    int ex_id ;
    int num ,Line ;
    string currency [100] , type [100]  ;
    float rate [100]  ;
    string curr ;
public : exchange ( string x = "" )
 {
    curr = x ;
    const int i = nextex_ID++;
    ex_id = i ;
 }
    void import ()
    {
        string f ;
        cout << "enter the file name with txt extension , pleas note that the form of import file is "<<endl
        <<"Currency name"<<"\t"<<"Type (sell Or buy)"<<"\t"<<"Exchange Rate"<<endl ;
        cin >> f ;
        string b ;
        cout << "enter the currency name : ";
        cin >> b ;
        curr = b;
        string s [100] ,t [100] ;
        float r[100] ;
        int couter = 0 ;
        ifstream rate_file (f.c_str()) ;
        if (rate_file.is_open())
        {
            while (!rate_file.eof())
            {
                rate_file >> s [couter] >> t [couter] >> r [couter] ;
                couter ++ ;
            }
        }
        else
        {
            cout << "can't open file ";
        }
        num = couter -1 ;
        for (int i = 0 ; i < num ; i ++ )
        {
            rate [i] = r[i] ;
            type [i] = t [i] ;
            currency [i] = s [i] ;
        }
        SaveList();
        cout << "your file has been saved to the system successfully" <<endl ;
    }


    void newList (int n = 0 )
    {
        string b ;
        cout << "enter the currency name : ";
        cin >> b ;
        curr = b;
        cout << "how many currency in the list ' each type conceder as currency ' : ";
        cin >> n ;
        num = n ;
        for (int i = 0 ; i < num ; i ++ )
        {
            cout << "currency : " ;
            cin >> currency [i] ;
            cout << "type : ";
            cin >> type [i] ;
            cout << "rate exchange : " ;
            cin >> rate [i] ;
        }
        int exs ;
        int h = 0;
        while (h==0)
        {
            cout <<"The new list has been added to the system, enter 1 to save it or 2 to edit it : "<<endl;
            cin >> exs;
            switch (exs)
            {
                case 1 :
                {
                    SaveList();
                    h= 1;
                    break;
                }
                case 2 :
                {
                    editList();
                    break;
                }
            }
        }
    }


    int search_for ( string x , int w = 0  )
    {
        if (currency[w] == x )
            return w;
        return search_for( x , w+1);
    }


    void editList ()
    {
        string x ;
        cout <<"currency you want to edit his list : ";
        cin >> curr;
        Line_SIZE(curr) ;
        storeList() ;
        int e ;
        cout <<"select the edit type :"<<endl
        <<"1- add currency to the list "<<endl
        <<"2- delete currency from the list "<<endl
        <<"3- edit currency value in the list "<<endl ;
        cin >> e ;
        switch (e)
        {
            case 1 :
            {
                int x ;
                int nume ;
                nume = num ;
                cout << "how many element you want to add : " ;
                cin >> x ;
                num = num + x ;
                for (int i = nume ; i < num ; i ++ )
                {
                    cout << "currency : " ;
                    cin >> currency [i] ;
                    cout << "type : ";
                    cin >> type [i] ;
                    cout << "rate exchange : " ;
                    cin >> rate [i] ;
                }
                 SaveList();
                 break ;
            }
            case 2 :
            {
                string e ,t ;
                int u ,r;
                cout << "enter the currency you want to delete : ";
                cin >> e ;
                cout << "type : ";
                cin >> t ;
                r = search_for(e) ;
                if (type [r]!=t)
                {
                    r = search_for(e,r+1) ;
                }
                u = r ;
                num = num -1 ;
                for (int i = u ; i <num ; i++)
                {
                    rate [i] = rate [i+1];
                    currency [i] = currency [i+1];
                }
                SaveList();
                break ;
            }
            case 3 :
            {
                int y,r ;
                float f ;
                string C,t ;
                cout << " enter the currency you want to edit : ";
                cin >> C ;
                cout << "type : ";
                cin >> t ;
                r = search_for(C) ;
                if (type [r]!=t)
                {
                    r = search_for(C,r+1) ;
                }
                y = r ;
                cout << "enter the new exchange rate : ";
                cin >> f ;
                rate[y] = f ;
                SaveList();
                break ;
            }
        }
    }


    void SaveList ()
    {
        //curr = r ;
        ofstream LIS ;
        LIS.open("Exchange Data.txt" , ios::app) ;
        LIS << curr  << "\t" << ex_id << "\t" << num << "\n"  ;
        for (int j = 0 ; j < num ; j++)
        {
            LIS << currency [j] << "\t" << type [j] << "\t" << rate [j] << "\n" ;
        }
        LIS.close();
    }


    void Line_SIZE (string e)
    {
        string f ;
        string h ;
        float l ;
        ifstream file("Exchange Data.txt");
        int v = 0;
        if(file.is_open())
        {
            while (!file.eof())
            {
                file >> f  >> h>>l ;
                if (f == e&& h == "0" )
                {
                    Line = v;
                    num = l ;
                    break ;
                }
                else {Line = -1;}
                v++ ;
            }
            file.close();
        }
    }


    void storeList ()
    {
        string f , h  ;
        float l ;
        ifstream file1 ("Exchange Data.txt" ) ;
        for (int i = 0 ; i <= num+Line ; i++)
        {
                if (i == Line+1 )
                {
                    for (int j = 0 ; j < num ; j ++)
                    {
                        file1 >> currency[j] >> type [j] >> rate[j] ;
                    }
                }
                else{file1 >> f >> h >> l;}
        }
        file1.close();

    }


    void showlist ()
    {
        string x  ;
        int n , d ;
        string S [100] , N[100] ;
        float R [100] ;
        ifstream Shlist ("Exchange Data.txt") ;
        Shlist >> x >> d >> n ;
        for (int j = 0 ; j < num ; j++)
        {
            Shlist >> S [j] >> N[j] >> R[j] ;
        }
        cout << x << "\t" << d <<"\t"<< n <<endl ;
        for (int j = 0 ; j < num ; j++)
        {
            cout << S [j] << "\t" << N[j]<< "\t" << R[j] << endl ;
        }
    }


    void PrintList ( )
    {
        for (int i = 0 ; i < num ; i++)
        {
             cout << currency [i] << "\t" << type [i] << "\t" << rate [i]<<endl ;
        }
    }
};

int exchange::nextex_ID = 0 ;




/////////////////////////transaction class ////////////////////////////

class transaction
{
private :
    int id  = 1;
    int  a ;
    int cashier_num ;
    string curr ;
    string type ;
    float EQV  ;
    float Amount , EXrate , AmountINAccount ;
    float R ;
    int Line , Size ;
    string C  ;
    string TranFile ;
    string S[100],N[100] ;
    float K[100] ;
    string D , M , Y;
public : transaction (string X)
{
    TranFile  = X ;
    string iD, Id , CASH,Day,Mounth,Year ;
        string CURR , C , TYPE,DASH ;
        string EXRATE , AMOUNT , R , EGP ;
        string  y,dy,mouth,yer;
        string s , c ,t ,dsh;
        string ex ,am,r ,eg ;
        ifstream file(TranFile.c_str()) ;
        while (getline(file,dy))
        {
            getline(file,mouth);
            getline(file,yer);
            getline(file,Id);
            getline(file,t);
            getline(file,y);
            getline(file,s);
            getline(file,c);
            getline(file,ex);
            getline(file,am);
            getline(file,r);
            getline(file,eg);
            iD = Id ;
        }
        file.close();
        stringstream to_int(iD);
        int x = 0;
        to_int >> x;
        id = ++ x ;
   }


    int search_for ( string x , int w = 0  )
    {
        if (S[w] == x )
            return w;
        return search_for( x , w+1);
    }


    void Line_SIZE (string e)
    {
        string f ;
        string h  ;
        float l ;
        ifstream file("Exchange Data.txt");
        int v = 0;
        if(file.is_open())
        {
            while (!file.eof())
            {
                file >> f  >> h>>l ;
                if (f == e&& h == "0" )
                {
                    Line = v;
                    Size = l ;
                    break ;
                }
                else {Line = -1;}
                v++ ;
            }
            file.close();
        }
    }


    void storeList ()
    {
        string f , h  ;
        float l ;
        ifstream file1 ("Exchange Data.txt" ) ;
        for (int i = 0 ; i <= Size+Line ; i++)
        {
                if (i == Line+1 )
                {
                    for (int j = 0 ; j < Size ; j ++)
                    {
                        file1 >> S[j] >> N[j] >> K[j] ;
                    }
                }
                else{file1 >> f >> h >> l;}
        }
        file1.close();
    }

    void edit ()
    {
        int r ;
        cout << "1- edit exchange type "<<endl
        << "2- edit the amount "<<endl
        << "3- change to another currency "<<endl;
        cin >> r ;
        switch (r)
        {
            case 1 :
            {
                int a ;
                cout << " the new exchange type is : " ;
                cin >>  type ;
                storeList();
                a = search_for(C);
                if (N[a]!= type )
                {
                    a = search_for(C,a+1);
                }
                EXrate = K [a];
                R = Amount * EXrate ;
                DonOrExit ();
                break ;
            }
            case 3 :
            {
                int a ;
                cout << " the new currency is : " ;
                cin >> C ;
                a = search_for(C);
                if (N[a]!= type )
                {
                    a = search_for(C,a+1);
                }
                EXrate = K[a];
                R = Amount*EXrate ;
                DonOrExit ();
                break ;
            }
            case 2 :
            {
                cout << " the new Amount is : " ;
                cin >> Amount ;
                R = Amount * EXrate ;
                DonOrExit ();
                break ;
            }
        }
    }


    float Equ_EGP ()
    {
        int E ;
        E = search_for("EGP");
        if (N[E]!= type )
        {
            E = search_for("EGP",E+1);
        }
        EQV = K[E] * Amount ;
        return EQV ;
    }


    void SaveList ()
    {
        /*I had a problem with reading the data from file with a variable name using file >> data ; "data was corrupted"
        so i saved each variable in a separate Line to use getline function instead */
        ofstream LIS(TranFile.c_str() , ios::app) ;
            LIS << D << endl << M  << endl <<Y<<endl
            << id  << endl
            << type << endl
            << cashier_num << endl
            << curr << endl
            << C << endl
            << EXrate << endl
            << Amount << endl
            << R << endl
            << Equ_EGP() << endl;
        LIS.close();
    }


    float NewTransaction(string c , string s,string t ,float A , float AAA )
    {
        AmountINAccount = AAA;
        cout << "pleas enter the transaction data :. "<< endl ;
        cout << "Cashier Number : " ;
        cin >> cashier_num ;
        cout << "Date  DD MM YY: " ;
        cin >> D >> M >> Y ;
        date DD (D,M,Y);
        type = t ;
        curr = c;
        Line_SIZE(curr);
        if (Line == -1 )
        {
            int t ;
            exchange ne ;
            cout << "the entered currency has no exchange list pleas add or import a new one : "<<endl
            << "1- add "<<endl << "2- import"<<endl ;
            cin >> t ;
            switch (t)
            {
                case 1 :
                {
                    ne.newList() ;
                    ne.SaveList() ;
                    Line_SIZE(curr);
                    storeList() ;
                    break ;
                }
                case 2 :
                {
                    ne.import() ;
                    ne.SaveList() ;
                    Line_SIZE(curr);
                    storeList() ;
                    break ;
                }
            }

        }
        else{storeList() ;}
        C = s;
        a = search_for(C);
        if (N[a] != type)
        {
            a = search_for(C,a+1);
        }
        Amount = A ;
        EXrate = K[a];
        R = Amount*EXrate ;
        return DonOrExit ();
    }
    float DonOrExit ()
    {
       if (type == "buy")
       {
        if (AmountINAccount>= R )
        {
            int z ;
            int h = 0;
            while (h == 0)
            {
                cout <<Amount << curr <<" = "<<R << C << " ( "<< type <<" ) "<<endl
                <<"Your Transaction with ID: " << id <<" done successfully:. Enter 1 to save it or 2 to edit it "<<endl ;
                cin >>z;
                switch (z)
                {
                    case 1 :
                    {
                        SaveList() ;
                        h=1;
                        return R ;
                        break;
                    }
                    case 2 :
                    {
                        edit();
                    }
                }
            }
        }
        else
        {
            int z ;
            int h = 0;
            while (h == 0)
            {
                cout <<"Not enough money in balance account, Operation Failed:. Enter 1 to edit it or 2 to exit it "<<endl ;
                cin >>z;
                switch (z)
                {
                    case 1 :
                    {
                        edit();
                    }
                    case 2 :
                    {
                        h = 1 ;
                        break;
                    }
                }
            }
        }
       }
       if (type == "sell")
       {
        if (AmountINAccount>= Amount )
        {
            int z ;
            int h = 0;
            while (h == 0)
            {
                cout <<Amount << curr <<" = "<<R << C << " ( "<< type <<" ) "<<endl
                <<"Your Transaction with ID: " << id <<" done successfully:. Enter 1 to save it or 2 to edit it "<<endl ;
                cin >>z;
                switch (z)
                {
                    case 1 :
                    {
                        SaveList() ;
                        h=1;
                        return R ;
                        break;
                    }
                    case 2 :
                    {
                        edit();
                    }
                }
            }
        }
        else
        {
            int z ;
            int h = 0;
            while (h == 0)
            {
                cout <<"Not enough money in balance account, Operation Failed:. Enter 1 to edit it or 2 to exit it "<<endl ;
                cin >>z;
                switch (z)
                {
                    case 1 :
                    {
                        edit();
                    }
                    case 2 :
                    {
                        h = 1 ;
                        break;
                    }
                }
            }
        }
       }
    }

};

/////////////////////////account class ////////////////////////////

class Account
{
    private :
    int NextAC = 0 ;
    int AccNum ;
    string AccName ;
    string FileName ;
    string curr ;
    string AllCurr [100];
    float AmountOfCurr [100] ;
    string DWCurr ;
    float DWAmount ;
    float Profite ;
    public :

        void NewAccount ()
        {
            int d ;
            string na,naf ;
            ifstream ac("All Accounts Data.txt");
            if(ac.is_open())
            {
                while(!ac.eof())
                {
                    ac>>d>>na>>naf;
                }
            }
            ac.close();
            AccNum = d+1;
            cout<<"Welcome to our trusted banking system, please enter your name : "<<endl;
            cin>> AccName ;
            cout<<"Creating a bank account..."<<endl;
            cout<<"Account created successfully, your account number is : " <<AccNum<<endl;
            stringstream ss;
            ss << AccNum ;
            string s ;
            ss >> s ;
            FileName = "Data_for_Account_" + s + ".txt" ;
            ofstream AccountData ;
            AccountData.open("All Accounts Data.txt", ios::app) ;
            AccountData << AccNum  << "\t" << AccName << "\t" << FileName << "\n"  ;
            AccountData.close ();
            ofstream file(FileName.c_str()) ;
            file.close ();
        }
        int OpenAccount ()
        {
                string nam ,  f;
                int num ,r;
                cout << "enter your name : ";
                cin >> nam ;
                cout << "enter your Account Number : ";
                cin >> num ;
                ifstream Acc("All Accounts Data.txt", ios::app) ;
                if (Acc.is_open())
                {
                    while (!Acc.eof())
                    {
                        Acc >> AccNum >> AccName  ;
                        if (num == AccNum && nam == AccName)
                        {
                            Acc >> FileName  ;
                            r = 1;
                            return 1 ;
                            break;
                        }
                        Acc >> f ;

                    }
                    Acc.close ();
                }
                if (r != 1)
                {
                    cout <<"incorrect Name or Account Number ";
                    return 0;
                }
}


    int search_for ( string x , int w  )
    {
        if (AllCurr[w] == x )
            return w;
        return search_for( x , w-1);
    }


    void SaveAllCurr ()
    {
        ofstream Alcu (curr.c_str(),ios::app) ;
        Alcu << DWCurr << "\t" << DWAmount << "\n" ;
        Alcu.close();
    }


    void ADD (string C,float A)
    {
        string c ;
        float E = 0 ;
        int r ;
        stringstream ss;
        ss << AccNum ;
        string s ;
        ss >> s ;
        curr = "CURR_for_Account_" + s + ".txt" ;
        ifstream ALLCURR;
        ALLCURR.open(curr.c_str());
        if(ALLCURR.is_open())
        {
                while (!ALLCURR.eof())
                {
                    ALLCURR >> c  ;
                    if (c == DWCurr  )
                    {
                        ALLCURR >> E ;
                        r = 1;
                    }
                }
                ALLCURR.close();
                DWAmount = E + DWAmount ;
                SaveAllCurr();
        }
        if (r!=1)
        {
            SaveAllCurr();
        }

    }



    void SUB (string C,float A)
    {
        string c ;
        float E = 0 ;
        stringstream ss;
        ss << AccNum ;
        string s ;
        ss >> s ;
        curr = "CURR_for_Account_" + s + ".txt" ;
        ifstream ALLCURR;
        ALLCURR.open(curr.c_str());
        if(ALLCURR.is_open())
        {
                while (!ALLCURR.eof())
                {
                    ALLCURR >> c  ;
                    if (c == DWCurr  )
                    {
                        ALLCURR >> E ;
                    }
                }
                ALLCURR.close();
                if (DWAmount>E)
                {
                   cout << "Not enough money in balance account, Operation Failed" <<endl ;
                   DWAmount = E ;
                }
                else
                {
                    E = E - DWAmount ;
                    DWAmount = E ;
                }
                SaveAllCurr();
        }
    }



    void deposit()
    {
        cout << "enter the currency you want to deposit : " ;
        cin >> DWCurr ;
        cout << "enter the value you want to deposit : " ;
        cin >> DWAmount ;
        ADD(DWCurr,DWAmount);
    }



    void withdraw ()
    {
        cout << "enter the currency you want to withdraw : " ;
        cin >> DWCurr ;
        cout << "enter the value you want to withdraw : " ;
        cin >> DWAmount ;
        SUB(DWCurr,DWAmount);
    }


    int store_Currenies()
    {
        string c  ;
        float x  ;
        stringstream ss;
        ss << AccNum ;
        string s ;
        ss >> s ;
        curr = "CURR_for_Account_" + s + ".txt" ;
        ifstream ALLCURR;
        ALLCURR.open(curr.c_str());
        int v = 0;
        if(ALLCURR.is_open())
        {
            while (!ALLCURR.eof())
            {
                ALLCURR >> c  >> x ;
                AllCurr [v] = c ;
                AmountOfCurr [v] = x  ;
                v++ ;
            }
            ALLCURR.close();
        }
        return v ;
    }

    float trans ()
    {
        float e ,A,AAA ;
        string c , s ,t ;
        cout << "currency you want to exchange : " ;
        cin >> c;
        cout << "enter the currency you want to exchange to : ";
        cin >> s;
        cout << "transaction type : " ;
        cin >> t;
        cout << "the amount is : ";
        cin >> A;
        if (t == "sell")
        {
            int v  , j ;
            v = store_Currenies ();
            j=search_for (c, v-1) ;
            AAA = AmountOfCurr[j] ;
        }
        if (t == "buy")
        {
            int v  , j ;
            v = store_Currenies ();
            j=search_for (s, v-1) ;
            AAA = AmountOfCurr[j] ;
        }
        transaction T (FileName) ;
        e = T.NewTransaction(c,s,t,A,AAA);
         if (t == "sell")
        {
            DWCurr = s ;
            DWAmount = e ;
            ADD(DWCurr,DWAmount);
            DWCurr = c ;
            DWAmount = A ;
            SUB(DWCurr,DWAmount);
        }
        if (t == "buy")
        {
            DWCurr = s ;
            DWAmount = e ;
            SUB(DWCurr,DWAmount);
            DWCurr = c ;
            DWAmount = A ;
            ADD(DWCurr,DWAmount);
        }
    }

    void Currencies_Balance ()
    {
            string b ;
            int j  ;
            int v ;
            v = store_Currenies ();
            cout << "enter the currency to get the Currency Balance Report ";
            cin >> b ;
            j=search_for (b, v-1) ;
            cout << "you have : " << AmountOfCurr[j] << b << " in your account"<<endl ;
    }


    void Search_For_Transaction ()
    {
        string D,M,Y ;
        cout << "enter the DATE of the Transaction : ";
        cin >> D>>M>>Y ;
        string iD, Id , CASH,Day,Mounth,Year ;
        string CURR , C , TYPE,DASH ;
        string EXRATE , AMOUNT , R , EGP ;
        string  y,dy,mouth,yer;
        string s , c ,t ,dsh;
        string ex ,am,r ,eg ;
        ifstream file(FileName.c_str()) ;
        while (getline(file,dy))
        {
            getline(file,mouth);
            getline(file,yer);
            getline(file,Id);
            getline(file,t);
            getline(file,y);
            getline(file,s);
            getline(file,c);
            getline(file,ex);
            getline(file,am);
            getline(file,r);
            getline(file,eg);
                if (D == dy&&M==mouth&&Y==yer )
                {
                    Day = dy ;
                    Mounth = mouth ;
                    Year = yer ;
                    iD =Id;
                    TYPE = t;
                    CASH = y;
                    CURR = s;
                    C = c ;
                    EXRATE = ex ;
                    AMOUNT= am ;
                    R = r;
                    EGP = eg ;
                }
        }
        file.close();
        if (D == Day&&M==Mounth&&Y==Year)
        {
            cout << "TRANSACTION DETELS IS "<< endl
            <<"DATE"<<" : "<<Day<<"/"<<Mounth<<"/"<<Year<<"\n"
            <<"ID"<<" : "<<iD<<"\n"
            <<"TYPE"<<" : "<<TYPE<<"\n"
            <<"CASHIER NUMBER"<<" : "<<CASH<<"\n"
            <<"EXCHANGE"<<" : "<<AMOUNT<<CURR<<" to "<<R<<C<<"\n"
            <<"WITH EXCHANGE RATE"<<" : "<<EXRATE<<"\n"
            <<"EQUIVALENT TO EGP" <<" : "<<EGP <<endl ;
        }
        else {cout <<"no Transaction in this Date..."<<endl;}
    }


    void profit ()
    {
        string Ds,Ms,Ys,De,Me,Ye ;
        cout << "enter the DATE of START : ";
        cin >> Ds>>Ms>>Ys ;
        cout << "enter the DATE of END : ";
        cin >> De>>Me>>Ye ;
        date Start(Ds,Ms,Ys);
        date END (De,Me,Ye);
        string iD, Id , CASH,Day,Mounth,Year ;
        string CURR , C , TYPE[100],DASH ;
        string EXRATE , AMOUNT , R , EGP[100] ;
        string  y,dy,mouth,yer;
        string s , c ,t ,dsh;
        string ex ,am,r ,eg ;
        ifstream file(FileName.c_str()) ;
        int i = 0 ;
        TYPE [0]= "0";
        while (getline(file,dy))
        {
            getline(file,mouth);
            getline(file,yer);
            getline(file,Id);
            getline(file,t);
            getline(file,y);
            getline(file,s);
            getline(file,c);
            getline(file,ex);
            getline(file,am);
            getline(file,r);
            getline(file,eg);
            int S , E ;
            date between (dy,mouth,yer);
            S = Start.compare(between);
            E = END.compare(between);
                if ( S==-1 && E==1 )
                {
                    TYPE[i]= t;
                    EGP[i] = eg;
                    i++;
                }
        }
        file.close();
        if (TYPE[0]=="0")
        {
            cout <<"There's  no Transactions between the entered Date..."<<endl;
        }
        else
        {
            float sell=0 ;
            float buy =0;
            float EG ;
            for (int j = 0 ; j <=i ; j++)
            {
                if (TYPE[j]== "buy")
                {
                    EG=atof((EGP[j]).c_str());
                    buy = buy + EG;
                }
                if (TYPE[j]== "sell")
                {
                    EG=atof((EGP[j]).c_str());
                    sell = sell + EG;
                }
            }
            Profite = sell - buy;
            cout<<"Profit in EGP is: " <<Profite<<endl;
        }
    }

    void Report ()
    {
        int c ;
        int h = 0;
        while (h==0)
        {
            cout <<"Chose the report type or enter 3 to exit " << endl
            <<"1- Profit report"<<endl
            <<"2- Currency Balance "<<endl ;
            cin >>c;
            switch (c)
            {
                case 1:
                {
                    profit () ;
                    break;
                }
                case 2:
                {
                    Currencies_Balance() ;
                    break;
                }
                case 3:
                {
                    h=1 ;
                    break;
                }
            }
        }
    }
};

/////////////////////////Show Exchange Rates List ////////////////////////////

void Show_Exchange_Rates_List ()
{
        string e;
        cout << "enter the currency name to show the exchange rates list ";
        cin>> e ;
        int Line , Size  ;
        string f , h  ;
        float l ;
        string S[150],N[150];
        float K[150];
        ifstream file ("Exchange Data.txt" ) ;
        for (int i = 0 ; i < 150 ; i++)
        {
                file >> f >> h >> l;
                if (f == e && h != "sell"&& h != "buy" )
                {
                    Line = i;
                    Size = l ;
                }
        }
        file.close() ;
        ifstream file1 ("Exchange Data.txt" ) ;
        for (int i = 0 ; i <= Size+Line ; i++)
        {
                if (i == Line+1 )
                {
                    for (int j = 0 ; j < Size ; j ++)
                    {
                        file1 >> S[j] >> N[j] >> K[j] ;
                        cout << S[j]<<"\t"<<N[j]<<"\t"<<K[j]<<endl;
                    }
                }
                else{file1 >> f >> h >> l;}
        }
        file1.close();
    }

    void OPEN ()
    {
                int AAA = 0;
                while (AAA==0)
                {
                    int e;
                    Account A ;
                    e = A.OpenAccount();
                    //cout << e;
                    switch(e)
                    {
                        case 0 :
                        {
                            int T ;
                            cout << "1- Try Again "<<endl
                            <<"2- exit"<<endl;
                            cin >>T;
                            if (T==1)
                            {
                                break;
                            }
                            if (T== 2)
                            {
                                AAA=1;
                                break;
                            }

                        }
                        case 1 :
                        {
                            int v ;
                            int  AA = 0;
                            while(AA == 0)
                            {
                                cout << "1- Deposit "<<endl
                                <<"2- Withdraw "<<endl
                                <<"3- Transaction" << endl
                                <<"4- Report "<< endl
                                <<"5- Search for transaction "<< endl
                                <<"6- exit"<<endl ;
                                cin >> v ;
                                switch (v)
                                {
                                    case 1 :
                                    {
                                        A.deposit();
                                        break;
                                    }
                                    case 2 :
                                    {
                                        A.withdraw();
                                        break;
                                    }
                                    case 3 :
                                    {
                                        A.trans();
                                        break;
                                    }
                                    case 4 :
                                    {
                                        A.Report();
                                        break;
                                    }
                                    case 5 :
                                    {
                                        A.Search_For_Transaction();
                                        break;
                                    }
                                    case 6 :
                                    {
                                        AA=1;
                                        AAA=1;
                                        break;
                                    }
                                }
                            }
                            break;
                        }

                    }
                }
}


/////////////////////////main function ////////////////////////////

int main()
{
    int c ;
    int h = 0;

    while(h==0)
    {
        cout <<"welcome....."<<endl
        <<"1- Open your account "<<endl
        <<"2- Make a new account "<<endl
        <<"3- Import New exchange list "<<endl
        <<"4- Add New exchange list "<<endl
        <<"5- Show exchange list "<<endl
        <<"6- Edit exchange List "<<endl               // we forgot to add this option " 6 " in the first submission
        <<"7- Close The Program "<<endl ;               //so we submit it again
        cin >> c;
        switch (c)
        {
            case 1 :
            {
                OPEN() ;
                break ;
            }
            case 2 :
            {
                Account B ;
                B.NewAccount();
                break;
            }
            case 3 :
            {
                exchange IM;
                IM.import() ;
                break;
            }
            case 4 :
            {
                exchange AD ;
                AD.newList();
                break;
            }
            case 5 :
            {
                Show_Exchange_Rates_List();
                break;
            }
            case 7 :
            {
                h=1;
                break;
            }
            case 6 :
            {
                exchange AD ;
                AD.editList();
                break;
            }
        }
    }
    return 0;
}
