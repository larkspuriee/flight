/*
	Title					: FLIGHT BOOKING SYSTEM
	Group Member			: 1.  AISYAH MAISARAH BINTI SUPIAN
							  2. FATIN HUMAIRA BITNI ROSLIZAM
							  3. NUR ADLINA SAKINAH
							  4. MAISARAH BINTI TOBRONI
	Course					:	CDCS230
	Group					:	2A
	Due Date				:	11th July 2023 (10:30pm)
	Program Description		:	Program Development of Kuching Digital Community Run Event
*/
#include <iostream>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

struct nameType{
	char fName[70], lName[70];
};
struct Registeration{
	int expirydate[3];
	string email, passnum;
	nameType name;
	char nationality[20], password[9];   
};
struct passBooking{
	int destination, arrival, departDay, departMonth, departYear, returnDay, returnMonth, returnYear, departTime, returnTime, flightType, 
	enteredTitle[9];
	double totalPrice;
	bool seatAvail[9];
	string passLName2[9], passFName2[9], passportNum[9];
	char userType, cabin[9], citizen, seatPass[9][4], user;
};
struct seat{
	const int BSeatRow=5;		//total row for business seat
	const int BSeatTot=20;		//total seat for businesss class
	const int ESeatRow=45;		//total row for economy seat
	const int ESeatTot=270;		//total seat for economy class
};
void userRegisteration(Registeration *&, int &, ofstream&);
void checkDate(int &, int &, int &);
int flightPage(Registeration *&, passBooking *&, const int, seat, char[][4],char[][4], string [][2], string [][2]);
void payment(Registeration *&, passBooking *&, const int, int);
void ticket(Registeration *&, passBooking *&, const int, int, string [][2], string [][2]);
 
int main()		//main function
{
	string EMAIL;
	int cust; 
	seat passSeat;
	char BSeat[passSeat.BSeatTot][4],column[6][2]={"A", "B", "C", "D", "E", "F"}, row[5], ESeat[passSeat.ESeatTot][4], option, PASSWORD[9];	/*this row untuk tukar integer 
																														row jadi char	*/
	bool login=false, checkemail=false;
	int Row, user=0, j=0, currentuser, numpass;		//used in for loop (nothing special)
	string Time[5][2] = {{"08:10 --------> 09:15", "08:10 --------> 10:15"}, {"14:05 --------> 15:10", "14:05 --------> 16:10"}, 
						{"15:00 --------> 16:05", "15:00 --------> 17:05"}, {"17:00 --------> 18:05", "17:00 --------> 19:05"}, 
						{"20:35 --------> 21:40", "20:35 --------> 22:40"}}, Airport[33][2] = { {"\n", "\n"}, {"Kuala Lumpur (KUL)", "MH0001"}, 
						{ "Subang (SZB)", "MH0003" }, { "Kota Bharu (KBR)", "MH0005" },{ "Kuala Terengganu (TGG)", "MH0007" }, { "Johor Bahru (JHB)", "MH0009" }, 
						{"Alor Setar (AOR)", "MH0001"}, {"Kerteh (KTE)", "MH0003"}, { "Penang (PEN)", "MH0005"}, {"Kuantan (KUA)", "MH0007"}, {"Langkawi (LGK)", "MH0009"},
						{"Miri (MYY)", "MH0002"}, {"Mulu (MZV)", "MH0004"}, {"Sibu (SBW)", "MH0006"}, {"Tawau (TWU)", "MH0008"},{"Labuan (LBU)", "MH0010"}, 
						{"Bintulu (BTU)", "MH0002"}, {"Kuching (KCH)", "MH0004"}, {"Limbang (LMN)", "MH0006"},{"Sandakan (SDK)", "MH0008"}, 
						{"Lahad Datu (LDU)", "MH0010"}, {"Kota Kinabalu (BKI)", "MH0002"}, {"Bario (BBN)", "MH0004"},{"Kudat (KUD)", "MH0006"}, 
						{"Lawa (LWY)", "MH0008"}, {"Mukah (MKM)", "MH0010"}, {"Marudi (MUR)", "MH0002"},{"Bakalalan (BKM)", "MH0004"}, {"Long Akah (LKH)", "MH0006"}, 
						{"Long Banga (LBH)", "MH0008"}, {"Long Lellang (LGL)", "MH0010"}, {"Long Seridan (ODN)", "MH0002"}, {"Tanjung Manis (TGC)", "MH0004"}};
						
	
	ofstream adminFile("CustomerList.txt");
	if(adminFile){
		adminFile << "\t\tNO.\tEMAIL\tFULL NAME\n";
	}
	system("Color 70");
	cout << setw(60)<< "===================\n";
	cout << setw(55)<<"FOR ADMIN\n";
	cout << setw(60) <<"===================\n";
	cout << endl << setw(70) << "Enter maximum number of registered customers : ";
	cin >> cust;
	while(cust==false || cust==false && cust==true){
		cout << setw(60) << " >> INVALID, please enter again : ";
		cin.clear();
        cin.ignore(256,'\n');
		cin >> cust;
    }
	
	Registeration *passenger=new Registeration [cust];
	passBooking *pass1=new passBooking [cust];
	
	for(Row=1; Row<=passSeat.ESeatRow; Row++){	// load seat for economy class
		for(int i=0; i<=5; i++){
			sprintf(row,"%d", Row);		
			strcpy(ESeat[j], row);
			strcat(ESeat[j],column[i]);	
			j++;
		}	
	}
	j=0;
	for(Row=1; Row<=passSeat.BSeatRow; Row++){	// load seat for business class
		for(int i=0; i<=3; i++){
			sprintf(row,"%d", Row);		
			strcpy(BSeat[j], row);
			strcat(BSeat[j],column[i]);	
			j++;
		}	
	}
	
	
	while(option !='X' && option!='x'){
		cout << "\t\t\t\t";
		system("pause");
		system("cls");
		system("Color E4");		//to print colored output
		cout <<"\t\t\t********************************************************\n";
		cout << "\t\t\t\tWELCOME TO MALAYSIA FLIGHT TICKET SYSTEM\n";
		cout <<"\t\t\t********************************************************\n\n";
		cout <<  "\t\t\t\t\t(A) Register\n" << "\t\t\t\t\t(B) Log in\n" << "\t\t\t\t\t(C) Log out\n" << "\t\t\t\t\t(D) Book flight ticket\n" << "\t\t\t\t\t(X) Exit\n" << "\t\t\t\t\tSelect an option : ";
		cin >> option;
	
		switch (option){
			case 'A' : case 'a' :
				if(login==true){
					cout << "\t\t\t<< Current user must log out first for new user to register. >>\n";
				}
				else{
					if(user<cust){
						system("pause");
						system("cls");
						cout <<"\t\t\t********************************************************\n";
						cout << "\t\t\t\t\tREGISTERATION PAGE\n";
						cout <<"\t\t\t********************************************************\n\n";
						userRegisteration(passenger, user, adminFile);
					}
					else{
						cout << "\t\t\t<< New user cannot register because it has exceeded the maximum capacity. >>\n";
						break;
					}
				}
				break;
				
			case 'B' : case 'b' :
				if(login==true){
					cout << "\t\t\t<< Other user is currently logged in. >>\n";
					break;
				}
				system("pause");
				system("cls");
				cout <<"\t\t\t********************************************************\n";
				cout << "\t\t\t\t\t\tLOG IN PAGE\n";
				cout <<"\t\t\t********************************************************\n\n";
				cout << "\t\t\t\tEnter email : ";
				cin.ignore();
				getline(cin, EMAIL);
				for(int i=0; i<user; i++){
					if (passenger[i].email==EMAIL){		//compare email to check if it exists in the system
						checkemail=true;
						currentuser=i;		
					}
				}
				if(checkemail==true){
					do{
						cout << "\t\t\t\tEnter password : ";
						int i;
						for(i=0; i<9; i++){
							PASSWORD[i]=getch();
							cout << "*";		//to hide the display of the password
						}
						PASSWORD[i]='\0';
						cout<<endl;
						if (strcmp(PASSWORD, passenger[currentuser].password)==0){		
							login=true;
							cout << "\n\n\t\t\t\t\tPersonal Information\n\t\t\t\t\t====================\n";		//display the personal information after log in is successful
							cout << "\t\t\t\tFull Name : " << passenger[currentuser].name.lName << " " << passenger[currentuser].name.fName<< endl;
							cout << "\t\t\t\tNationality : " << passenger[currentuser].nationality << endl;
							if (strcmpi(passenger[currentuser].nationality, "MALAYSIAN")!=0){	
								cout << "\n\t\t\t\tTravel Document\n===================\n";
								cout << "\t\t\t\tPassport Number : " << passenger[currentuser].passnum << endl;
								cout << "\t\t\t\tPassport Expiry Date : " << passenger[currentuser].expirydate[0] << "/" << passenger[currentuser].expirydate[1] << "/" << passenger[currentuser].expirydate[2] << endl;
							}
							cout << "\n\t\t\t\tYOU HAVE SUCCESSFULLY LOGGED IN!\n\n";
						}
						else{
							cout << "\n\t\t\t\t>> WRONG PASSWORD!. Please enter again\n";
						}
					}while(login!=true);
				}
				else{
					cout << "\t\t\t\t >> USER DOES NOT EXIST\n" << endl;
				}
				break;	
	
			case 'C' : case 'c' :
				if(login==false){
					cout << "\t\t\t\t>> YOU HAVE NOT LOGGED IN YET.\n" << endl;
				}
				else{
					login=false;
					cout << "\t\t\t\t\t>> YOU HAVE LOGGED OUT.\n";
				}
				break;
				
			case 'D' : case 'd' :
				if(login!=true){
					cout << "\t\t\t\t>> You must login to book flight ticket. Please login \n\n";
				}
				else{
					system("pause");
					system("cls");
					numpass=flightPage(passenger, pass1, currentuser, passSeat, BSeat, ESeat,Time, Airport);
					payment(passenger, pass1, currentuser, numpass); 
					system("pause");
					system("cls");
					ticket(passenger, pass1, currentuser, numpass, Time, Airport);
				}
				break;
			case 'X' : case 'x' :
				break;
				
			default :
				cout << "\t\t\t\t\t>> INVALID INPUT.\n";
				break;
		}		
		cout << endl;
	}
		
}

void userRegisteration(Registeration *&PASSENGER, int &USER, ofstream &adminFile){		//function (1)
	cin.ignore();
	cout << "\t\t\t\tEnter email : ";
    getline(cin, PASSENGER[USER].email);
	if(USER!=0){
		for(int i=0; i< USER; i++){
			while(PASSENGER[i].email==PASSENGER[USER].email){		//to check wether the email registered is already exist in the system or not
				cout << "\t\t\t\t >> Email is not available. Please enter again : ";
				getline(cin, PASSENGER[USER].email);
				i=0;
			}
		}
	}
	cout << "\t\t\t\tEnter  (9 characters): ";
	int i;
	for(i=0; i<9; i++){
		PASSENGER[USER].password[i]=getch();
		cout << "*";
	}
	PASSENGER[USER].password[i]='\0';
	cout << endl;
	cout << "\t\t\t\t<< You have passed the hidden password. >>\n\t\t\t\t";
	for(i=0; PASSENGER[USER].password[i]!='\0'; i++){
		cout << PASSENGER[USER].password[i];		//display the hidden password
	}
	cout << endl;
	
	cout << "\n\t\t\t\tPersonal details \n";
	cout << "\t\t\t\t====================\n";
	cout << "\t\t\t\tEnter last name : ";
	cin.getline(PASSENGER[USER].name.fName, 70);
	cout << "\t\t\t\tEnter first name : ";
	cin.getline(PASSENGER[USER].name.lName, 70);
	cout << "\t\t\t\tEnter nationality (eg: Malaysian): ";
	cin.getline(PASSENGER[USER].nationality, 20);
	cin.sync();
	if(strcmpi(PASSENGER[USER].nationality, "malaysian")!=0){
		cout << "\t\t\t\tEnter passport number : ";
		getline(cin, PASSENGER[USER].passnum);
		while(PASSENGER[USER].passnum.length()<6 || PASSENGER[USER].passnum.length()>12){
			cout << "\t\t\t\t >> Invalid passport number. Please enter again : ";
			cin.clear();
			cin.ignore(256,'\n');
			getline(cin, PASSENGER[USER].passnum);
		}
		cout << "\t\t\t\tEnter passport expiry date \n";
		cout << "\t\t\t\tDay (dd): ";
		cin >> PASSENGER[USER].expirydate[0];
		// checkdate function
		cout << "\t\t\t\tMonth (mm): ";
		cin >> PASSENGER[USER].expirydate[1];
		//checkdate function
		cout << "\t\t\t\tYear (yyyy): ";
		cin >> PASSENGER[USER].expirydate[2];
		checkDate(PASSENGER[USER].expirydate[0],PASSENGER[USER].expirydate[1], PASSENGER[USER].expirydate[2]);	
		cout << "\t\t\t\tPassport expiry date : " << PASSENGER[USER].expirydate[0] << "/" << PASSENGER[USER].expirydate[1] << "/" << PASSENGER[USER].expirydate[2] << endl;	
	}
	USER++;				//next customer index number
	cout << "\n\t\t\t\t<< YOU HAVE SUCCESSFULLY REGISTERED! >>\n\n";
	
	if(adminFile){
		adminFile << "\t\t" << USER << "\t" << PASSENGER[USER-1].email << "\t" << PASSENGER[USER-1].name.fName << " " << PASSENGER[USER-1].name.lName << endl;
	}
	else
		cout << "\t\t\t\t >> Unable to open the file." << endl;
}

int flightPage(Registeration *&PASSENGER, passBooking *&PASS1, const int CURRENTUSER, seat PASSSEAT, char BSEAT[][4], char ESEAT[][4], string time[][2], string airport[][2]){
	
	int numPass, passCount=1;
	double price[2][2] = {{74.00, 1000.00}, {148.00, 2000.00}};
	string passtitle[5] = { "Mr", "Mrs", "Ms", "Miss", "-(none)"};
	cout <<"\t\t\t********************************************************\n";
	cout << "\t\t\t\t\tFLIGHT BOOKING PAGE\n";
	cout <<"\t\t\t********************************************************\n\n";
	cout << "\t\t\t\tWelcome onboard, " << PASSENGER[CURRENTUSER].email << endl;
    cout << " \t\t\t\tSelect departure airport :\n";
    for(int i = 1; i <33; i++ ){
        cout << "\t\t\t\t\t" << i << ". " << airport[i][0] << endl;   
	}
    cout << "\t\t\t\tFrom: ";
    cin >> PASS1[CURRENTUSER].destination;

	 while ( PASS1[CURRENTUSER].destination <0 || PASS1[CURRENTUSER].destination > 32 || PASS1[CURRENTUSER].destination == false || PASS1[CURRENTUSER].destination== false && PASS1[CURRENTUSER].destination==true){  
    	cout << "\t\t\t\tDeparture airport chosen is not on the list, please enter again : ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> PASS1[CURRENTUSER].destination;
    }
    cout << PASS1[CURRENTUSER].destination;
    cout << "\n\n\t\t\t\tSelect arrival airport : \n";
    for(int i = 1; i <33; i++ ){
    	if( PASS1[CURRENTUSER].destination != i){
    	    cout << "\t\t\t\t\t" << i << ". " << airport[i][0] << "\n";
    	}
    } 
    cout << "\t\t\t\tTo: ";
    cin >> PASS1[CURRENTUSER].arrival;
    while( PASS1[CURRENTUSER].destination== PASS1[CURRENTUSER].arrival|| PASS1[CURRENTUSER].arrival< 0 || PASS1[CURRENTUSER].arrival> 32 
	|| PASS1[CURRENTUSER].arrival== false || PASS1[CURRENTUSER].arrival == false && PASS1[CURRENTUSER].arrival == true){
    	cout << "\t\t\t\t>> Arrival airport chosen is not on the list, please enter again : ";
    	cin.clear();
        cin.ignore(256,'\n');
        cin >> PASS1[CURRENTUSER].arrival; 
    }
    cin.sync();
	cout << "\t\t\t\tOne Way or Return ? (1 - One Way 2 - Return) : ";
    cin >> PASS1[CURRENTUSER].flightType;
    while(PASS1[CURRENTUSER].flightType!=1 && PASS1[CURRENTUSER].flightType!=2 || PASS1[CURRENTUSER].flightType== false || PASS1[CURRENTUSER].flightType == false && PASS1[CURRENTUSER].flightType == true ){
    	cout << "\t\t\t\tINVALID, please enter again : ";
    	cin >> PASS1[CURRENTUSER].flightType;
    }
    
	cout << "\t\t\t\tEnter departure date day (dd) : ";
	cin >> PASS1[CURRENTUSER].departDay;
	cout << "\t\t\t\tEnter departure month (mm) : ";
	cin >> PASS1[CURRENTUSER].departMonth;
	cout << "\t\t\t\tEnter departure year (yyyy) : ";
	cin >> PASS1[CURRENTUSER].departYear;
	checkDate(PASS1[CURRENTUSER].departDay, PASS1[CURRENTUSER].departMonth, PASS1[CURRENTUSER].departYear);
	if(PASS1[CURRENTUSER].flightType==2){
        cout << "\t\t\t\tEnter return date day (dd) : ";
	    cin >> PASS1[CURRENTUSER].returnDay; 
		cout << "\t\t\t\tEnter return month (mm) : ";
	    cin >> PASS1[CURRENTUSER].returnMonth;
		cout << "\t\t\t\tEnter return year (yyyy) : ";
	    cin >> PASS1[CURRENTUSER].returnYear;
		checkDate(PASS1[CURRENTUSER].returnDay, PASS1[CURRENTUSER].returnMonth, PASS1[CURRENTUSER].returnYear);
		while( PASS1[CURRENTUSER].returnYear<2023 || (PASS1[CURRENTUSER].returnYear,PASS1[CURRENTUSER].departYear && PASS1[CURRENTUSER].returnMonth<=PASS1[CURRENTUSER].departMonth && 
		PASS1[CURRENTUSER].returnDay<=PASS1[CURRENTUSER].departDay ) || (PASS1[CURRENTUSER].returnYear<=PASS1[CURRENTUSER].departYear && 
		PASS1[CURRENTUSER].returnMonth<PASS1[CURRENTUSER].departMonth&& PASS1[CURRENTUSER].returnDay<PASS1[CURRENTUSER].departDay) || 
		(PASS1[CURRENTUSER].returnYear<=PASS1[CURRENTUSER].departYear && PASS1[CURRENTUSER].returnMonth<=PASS1[CURRENTUSER].departMonth && 
		PASS1[CURRENTUSER].returnDay<PASS1[CURRENTUSER].departDay) || (PASS1[CURRENTUSER].returnYear<=PASS1[CURRENTUSER].departYear && 
		PASS1[CURRENTUSER].returnMonth<PASS1[CURRENTUSER].departMonth && PASS1[CURRENTUSER].returnDay<=PASS1[CURRENTUSER].departDay) || 
		PASS1[CURRENTUSER].returnYear==false || PASS1[CURRENTUSER].returnYear==false && PASS1[CURRENTUSER].returnYear==true){
			    cout << " \t\t\t\t>> Year is not valid, please enter again : ";
			    cin.clear();
	            cin.ignore(256,'\n');
		        cin >> PASS1[CURRENTUSER].returnYear;
	    }
		cout << "\t\t\t\tYour chosen date to depart is " << PASS1[CURRENTUSER].departDay << "/" << PASS1[CURRENTUSER].departMonth << "/" << PASS1[CURRENTUSER].departYear << endl;
		cout << "\t\t\t\tYour chosen date to return is " << PASS1[CURRENTUSER].returnDay << "/" << PASS1[CURRENTUSER].returnMonth << "/" << PASS1[CURRENTUSER].returnYear<< endl;
	}

	for(int i = 0; i < 34; i++ ){
		if( PASS1[CURRENTUSER].destination== i){
			cout << "\t\t\t\t" << airport[i][0] << "\n";
    	    cout << "\t\t\t\tDeparture Tickets Available :\t\tEconomic        Business " << endl;
			if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
    	            if(i > 0 && i < 10 ){
    	                cout << setprecision(2)<<fixed;
    	                for(int c=0; c<5; c++){
    	          	 	    cout << "\t\t\t\t\t" << c << ". "<< time[c][1] << "\tRM " << price[1][0] << "\tRM " << price[1][1] << endl;
    	                }
                    }else if(i>9 && i<33){
    	                cout << setprecision(2)<<fixed;
    	                for(int c=0; c<5; c++){
    	          	 	    cout << "\t\t\t\t\t" << c << ". "<< time[c][0] << "\tRM " << price[0][0] << "\tRM " << price[0][1] << endl;
    	                }
    	            }
            } 
			else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
    	            if(i>9 && i<33){
    	               cout << setprecision(2)<<fixed;
    	               for(int c=0; c<5; c++){
    	          	 	    cout << "\t\t\t\t\t" << c << ". "<< time[c][1] << "\tRM " << price[1][0] << "\tRM " << price[1][1] << endl;
    	                }
                    }else if(i>0 && i<10){
    	                cout << setprecision(2)<<fixed;
    	                for(int c=0; c<5; c++){
    	          	 	    cout << "\t\t\t\t\t" << c << ". "<< time[c][0] << "\tRM " << price[0][0] << "\tRM " << price[0][1] <<endl;
    	                }
                    }
            } 
			cout << " \t\t\t\tEnter number your chosen time : ";
            cin >> PASS1[CURRENTUSER].departTime;
            while(PASS1[CURRENTUSER].departTime<0 || PASS1[CURRENTUSER].departTime>4 || PASS1[CURRENTUSER].departTime==false || PASS1[CURRENTUSER].departTime==false && PASS1[CURRENTUSER].departTime==true){
    		        cout << "\t\t\t\tINVALID, please enter again : ";
    		        cin.clear();
                    cin.ignore(256,'\n');
    	     	    cin >> PASS1[CURRENTUSER].departTime;
            }
		}
	}
	
	for(int i = 1; i < 34; i++ ){	        
		if( PASS1[CURRENTUSER].arrival == i && PASS1[CURRENTUSER].flightType==2){
			cout << "\t\t\t\t" << airport[i][0] << "\n";
			cout << "\t\t\t\tReturn Tickets Available :\t\tEconomic        Business " << endl;
        	if( PASS1[CURRENTUSER].destination> 0 && PASS1[CURRENTUSER].destination < 10){
        	    if(i>9 && i<33){
        	    	cout << setprecision(2)<<fixed;
        	        for(int c=0; c < 5; c++){
        	         	cout << "\t\t\t\t\t" << c << ". "<< time[c][1] << "\tRM " << price[1][0] << "\tRM " << price[1][1] << endl;
        	        }
                }else if(i>0 && i<10){
        	        cout << setprecision(2)<<fixed;
        	            for(int c=0; c<5; c++){
        	          	    cout << "\t\t\t\t\t" << c << ". "<< time[c][0] << "\tRM " << price[0][0] << "\tRM " << price[0][1] << endl;
        	            }
        	    }
            }
            else if(PASS1[CURRENTUSER].destination>9 && PASS1[CURRENTUSER].destination<33){
        	    if(i>0 && i<10){
        	        cout << setprecision(2)<<fixed;
        	        for(int c=0; c<5; c++){
        	          	cout << "\t\t\t\t\t" << c << ". "<< time[c][1] << "\tRM " << price[1][0] << "\tRM " << price[1][1] << endl;
        	        }
                }else if(i>9 && i<33){
        	        cout << setprecision(2)<<fixed;
        	        for(int c=0; c<5; c++){
        	          	cout << "\t\t\t\t\t" << c << ". "<< time[c][0] << "\tRM " << price[0][0] << "\tRM " << price[0][1] <<endl;
        	        }
				}
            } 
            cout << "\t\t\t\tEnter number your chosen time : ";
            cin >> PASS1[CURRENTUSER].returnTime;
            while(PASS1[CURRENTUSER].returnTime<0 || PASS1[CURRENTUSER].returnTime>4 || PASS1[CURRENTUSER].returnTime==false || PASS1[CURRENTUSER].returnTime==false && PASS1[CURRENTUSER].returnTime==true){
        		cout << "\t\t\t\t>> INVALID, please enter again : ";
        		cin.clear();
                cin.ignore(256,'\n');
        		cin >> PASS1[CURRENTUSER].returnTime;
            }
			//comparing if the user chose the same time for the same date, month and year in return ticket
            if(PASS1[CURRENTUSER].departYear==PASS1[CURRENTUSER].returnYear && PASS1[CURRENTUSER].departMonth==PASS1[CURRENTUSER].returnMonth && PASS1[CURRENTUSER].departDay==PASS1[CURRENTUSER].returnDay){
               	while(PASS1[CURRENTUSER].returnTime<=PASS1[CURRENTUSER].departTime || PASS1[CURRENTUSER].returnTime==false || PASS1[CURRENTUSER].returnTime==false && PASS1[CURRENTUSER].returnTime==true){
               	    cout << "\t\t\t\t>> INVALID, you cant turn back the time : ";
               	  	cin.clear();
                    cin.ignore(256,'\n');
               	  	cin >> PASS1[CURRENTUSER].returnTime;
               	}
            }
		}
	}
	//user's personal details and passengers
    
    cout << "\t\t\t\t>> Is user the only passenger (Y) or buying for others as well (N) ? ";
    cin >> PASS1[CURRENTUSER].userType;
    
    if(PASS1[CURRENTUSER].userType =='N'|| PASS1[CURRENTUSER].userType =='n'){
        cout << "\t\t\t\t>> Enter number of passengers : ";
        cin >> numPass;
    	while(numPass<=0 || numPass>=10 || numPass==false || numPass==false && numPass==true){
    		cout << "\t\t\t\t>> The limit passengers is 1 to 9, please enter again : ";
    		cin.clear();
            cin.ignore(256,'\n');
    		cin >> numPass;		
    	}
    }
    
	//flag for user's own ticket
    if(PASS1[CURRENTUSER].userType =='Y'|| PASS1[CURRENTUSER].userType =='y'){
        numPass=1;
	}
	int f,k=0;
	while(passCount<=numPass){
        cout << "\t\t\t\tEnter cabin class for passenger "<< passCount << " ('E' or 'B') : ";
        cin >> PASS1[CURRENTUSER].cabin[passCount-1];
        switch (PASS1[CURRENTUSER].cabin[passCount-1]){
        	case 'E' : case 'e' :		
			    for(int AROW=1; AROW<=PASSSEAT.ESeatRow; AROW++){
					for(int c=0; c<66; c++){		
						cout << "-";
					}
					cout << endl;
					for(f=0; f<=5; f++){
						cout << setw(6) << ESEAT[k] << setw(5) << "|";			
						k++;
					}
					cout << endl;	
				}
				do{		
					cout << "\n\t\t\t\tEnter seat passenger " << passCount << " : ";
					cin.ignore();
					cin.getline(PASS1[CURRENTUSER].seatPass[passCount-1], 4);
					for(int e=0; e<PASSSEAT.ESeatTot; e++){
						if(strcmpi(PASS1[CURRENTUSER].seatPass[passCount-1], ESEAT[e])==0){	
							PASS1[CURRENTUSER].seatAvail[passCount-1]=true;
							strcpy(ESEAT[e], "X");	
						}
					}
					if(PASS1[CURRENTUSER].seatAvail[passCount-1]!=true){
						cout << "\t\t\t\t>> Seat is not available. Please enter again \n";
					}				
				}while(PASS1[CURRENTUSER].seatAvail[passCount-1]!=true || strcmp(PASS1[CURRENTUSER].seatPass[passCount-1], "X")==0);
					cout << endl;
					k=0;
        		    break;
        	case 'B' : case 'b' :			//for business class
				for(int AROW=1; AROW<=PASSSEAT.BSeatRow; AROW++){	//  function loadSeat before do-while registeration	with 45 rows
					for(int c=0; c<44; c++){			
						cout << "-";
					}
					cout << endl;
					for(f=0; f<=3; f++){
					cout << setw(6) << BSEAT[k] << setw(5) << "|";			//displaying seating
					k++;
					}
					cout << endl;	
				}
				do{	
					cout << "\n\t\t\t\tEnter seat passenger " << passCount << " : ";
					cin.ignore();
					cin.getline(PASS1[CURRENTUSER].seatPass[passCount-1], 4);
					for(int e=0; e<PASSSEAT.BSeatTot; e++){
						if(strcmpi(PASS1[CURRENTUSER].seatPass[passCount-1], BSEAT[e])==0){		//compare with all BSeat, if it has at least one same, seatAvail is set to true
							PASS1[CURRENTUSER].seatAvail[passCount-1]=true;
							strcpy(BSEAT[e], "X");	
						}
					}
					if(PASS1[CURRENTUSER].seatAvail[passCount-1]!=true){
						cout << "\t\t\t\tSeat is not available. Please enter again \n";
					}		
				}while(PASS1[CURRENTUSER].seatAvail[passCount-1]!=true || strcmp(PASS1[CURRENTUSER].seatPass[passCount-1], "X")==0);
					cout << endl;
					k=0;
        		    break;
        	default : 
				cout << "\t\t\t\tENTER 'E' OR 'B' ONLY ";
				passCount--;
        }
        passCount++;
    } 
    for(int z=0; z<numPass; z++){
        cout << "\t\t\t\t\tPassenger " << z+1 << endl;
        cout << "\t\t\t\tTitles : ";
        for(int i=1; i<5; i++ ){
            cout << i << ". " << passtitle[i] << "\t";
        }
        cout << endl << "\t\t\t\t\t\tPreferred title : ";
        cin >> PASS1[CURRENTUSER].enteredTitle[z];
        while(PASS1[CURRENTUSER].enteredTitle[z]>=5 || PASS1[CURRENTUSER].enteredTitle[z]<=0 || PASS1[CURRENTUSER].enteredTitle[z]==false || PASS1[CURRENTUSER].enteredTitle[z]==false && PASS1[CURRENTUSER].enteredTitle[z]==true){
            cout << "\t\t\t\t>> Title entered is invalid, please enter again : ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> PASS1[CURRENTUSER].enteredTitle[z];
    	}
        for(int j=1; j<5; j++){
            if(j==PASS1[CURRENTUSER].enteredTitle[z]){
            	PASS1[CURRENTUSER].enteredTitle[z] = j;
            	passtitle[j] = passtitle[PASS1[CURRENTUSER].enteredTitle[z]];
            	cout << "\t\t\t\t\t\t" << passtitle[PASS1[CURRENTUSER].enteredTitle[z]] << endl;
            }
        }
        //displaying the user's personal details from registeration function
        if(PASS1[CURRENTUSER].user =='Y'|| PASS1[CURRENTUSER].user =='y'){
            cout << "\t\t\t\t\t\tLast/Family name (as per passport or IC): " << PASSENGER[CURRENTUSER].name.lName << endl;
            cout << "\t\t\t\t\t\tFirst name (as per passport or IC): " << PASSENGER[CURRENTUSER].name.fName << endl;
            cout << "\t\t\t\t\t\tNationality : " << PASSENGER[CURRENTUSER].nationality << endl;
			cout << "\t\t\t\t\t\t\tTravel Document\n===================\n";
			cout << "\t\t\t\t\t\tPassport Number : " << PASSENGER[CURRENTUSER].passnum << endl;  
			cout << "\t\t\t\t\t\tPassport Expiry Date : " << PASSENGER[CURRENTUSER].expirydate[0] << "/" << PASSENGER[CURRENTUSER].expirydate[1] << "/" << PASSENGER[CURRENTUSER].expirydate[2] << endl;
		}
		else{
			cin.ignore();
            cout << "\t\t\t\t\t\tLast/Family name (as per passport or IC): ";
            getline(cin, PASS1[CURRENTUSER].passLName2[z]);
            cout << "\t\t\t\t\t\tFirst name (as per passport or IC): ";
            getline(cin, PASS1[CURRENTUSER].passFName2[z]);
            //for non malaysian passengers other than user registered
            
            cout << "\t\t\t\tIs Passenger " << z+1 << " Malaysian or non Malaysian ? (Y if Malaysian / N if non Malaysian) : ";
                cin >> PASS1[CURRENTUSER].citizen;
            if( PASS1[CURRENTUSER].citizen =='N'|| PASS1[CURRENTUSER].citizen =='n'){
                cout << "\t\t\t\tEnter passport number : ";
                cin.ignore();
                getline(cin, PASS1[CURRENTUSER].passportNum[z]);
                while(PASS1[CURRENTUSER].passportNum[z].length()<6 || PASS1[CURRENTUSER].passportNum[z].length()>12){
					cout << "\t\t\t\t>> Invalid passport number. Please enter again : ";
					cin.clear();
        			cin.ignore(256,'\n');
					getline(cin, PASS1[CURRENTUSER].passportNum[z]);
				}
            }
            
        }
    }
    return numPass;
}

void checkDate(int &day, int &month, int &year){
	while(day>31 || day<1 || day == false || day == false && day == true){
    		cout << "\t\t\t\t>> Day is not valid, please enter again : ";
    		cin.clear();
            cin.ignore(256,'\n');
    		cin >> day;
    }
	while(month>12 || month<1 || month == false || month == false && month == true){
			cout << "\t\t\t\t>> Month is not valid, please enter again : ";
			cin.clear();
            cin.ignore(256,'\n');
			cin >> month;
	}
	if( month == 2){
		    if( ( year%400 == 0 ) || ( year%4 == 0 && year%100 != 0) ){
			    while(day>29 || day<=0 || day == false || day == false && day == true){
			   	    cout << "\t\t\t\t>> Month is not valid, please enter again : ";
			   	    cin.clear();
                    cin.ignore(256,'\n');
			   	    cin >> day;
		        }
		    }else if( ( year%400 != 0 ) || ( year%4 != 0 && year%100 == 0) ){
		        while(day>28 || day<=0 || day == false || day == false && day == true){
		       	    cout << "\t\t\t\t>> Month is not valid, please enter again : ";
		       	    cin.clear();
                    cin.ignore(256,'\n');
			   	    cin >> day;
		        }  
	        }
	}
    else if( month > 0 && month <= 12 ){
    	    if( month%2!=0 && month != 2){
    		    while(day>31 || day<=0 || day == false || day == false && day == true){
    		        cout << "\t\t\t\t>> Month is not valid, please enter again : ";
    		        cin.clear();
                    cin.ignore(256,'\n');
			   	    cin >> day;
			    }
		    }else if( month%2==0 && month == 2){
    	 	    while(day>30 || day<=0 || day == false || day == false && day == true){
    	 	        cout << "\t\t\t\t>> Month is not valid, please enter again : ";
    	 	        cin.clear();
                    cin.ignore(256,'\n');
			   	    cin >> day;
    	 	    }   
    	    }
    }
	while(year<2023 || year==false || year == false && year == true){
    		cout << "\t\t\t\t>> Year is not valid, please enter again : ";
    		cin.clear();
            cin.ignore(256,'\n');
			cin >> year;
    } 
}
	
void payment(Registeration *&PASSENGER , passBooking *&PASS1, const int CURRENTUSER, int numPass){ 

	string cardNum,cvv;
	int Class, passcount=1;
	double priceC1, priceC2, priceC3, busP1, busP2, busP3, totalPTax=0, totalPtax=0.0, TOTALD=0.0,TOTAL;
	char PType, lunch;
	const double fuelPriceHour = 20000.0, ecoPrice = fuelPriceHour / 270.0, busPrice = fuelPriceHour / 20.0, ecoPrice2 = fuelPriceHour*2.0 / 270.0, busPrice2 = fuelPriceHour*2.0 / 20.0, taxPrice = 65.0;
	
	cout <<"\t\t\t********************************************************\n";
	cout << "\t\t\t\t\tPACKAGE AVAILABLE\n";
	cout <<"\t\t\t********************************************************\n\n";
	while(passcount<=numPass)	
	{ 
		switch(PASS1[CURRENTUSER].cabin[passcount-1])
	  {
	  	case'E': case'e':
	  			cout<<"1)Economy classic"<<"\nCabin baggage 7kg"<<"\nComplimentary snacks/meal & beverages"<<"\nNo check-in baggage"<<"\nNo free seat selection"<<"\nNo flexibility to board earlier on day of travel"<<"\nRebooking not available"<<"\nRefund not available"<<endl;
	  			cout<<"Normal price = RM "<< ecoPrice << " OR " << ecoPrice2 << endl;
	  			cout<<"\n2)Economy premium"<<"\nCabin baggage 7kg"<<"\nCheck-in baggage 20kg"<<"\nComplimentary snacks/meal & beverages"<<"\nRebooking:1x Free change fee(fare difference applies)"<<"\nRefund at a fee"<<"\nNo free seat selection"<<"\nNo flexibility to board earlier on day of travel"<<endl;
	  			cout<<"*for return ticket add on is added on both ticket"<<endl;
				cout<<"+RM45.50"<<endl;
	  			cout<<"\n3)Economy flex"<<"\nCabin baggage 7kg"<<"\nCheck-in baggage 35kg"<<"\nComplimentary snacks/meal & beverages"<<"\nLunch provided"<<"\nRebooking:Unlimited Free change fee(fare difference applies)"<<"\nFlexibility to board earlier on day of travel(subject to avaibility)";
				cout<<"\nRefund without fee" <<"\nPriority check in"<<"\nPriority Boarding"<<"\nPriority baggage"<<"\nBasic Travel Protection"<<endl;
	  			cout<<"*for return ticket add on is added on both ticket"<<endl;
				cout<<"+RM205.90"<<endl;
	  			
	  			cout<<"Choose Your Economy class type:";
	  			cin>>Class;
	  			while(Class<1 && Class>3 || Class==false || Class==false && Class==true){
		            cout << "\t\t\t\t>> Title entered is invalid, please enter again : ";
		            cin.clear();
		            cin.ignore(256,'\n');
		            cin >> Class;
		    	}
			  			if (Class==1){	
			  			
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination> 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		priceC1 = ecoPrice2 + taxPrice;
								totalPTax+= priceC1;
							}	
							else if(PASS1[CURRENTUSER].flightType==2)
							{  priceC1 = (ecoPrice2 + taxPrice)*2;  
							   totalPTax+= priceC1; 
							}  	
					} 
						else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
							if(PASS1[CURRENTUSER].flightType==1){
								priceC1 = ecoPrice + taxPrice;
        	            		totalPTax+= priceC1; 	
							}
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							{ priceC1 = (ecoPrice + taxPrice)*2;  
							   totalPTax+= priceC1; 
							} 
				        }
					}
					
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		priceC1 = ecoPrice + taxPrice;
	  				        	totalPTax+= priceC1;
        	            	}
	  				        else if(PASS1[CURRENTUSER].flightType==2)
							{ priceC1 = (ecoPrice + taxPrice)*2;  
							   totalPTax+= priceC1; 
							} 
	  				    }
						else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
	  				    	if(PASS1[CURRENTUSER].flightType==1){
	  				    		priceC1 = ecoPrice2 + taxPrice;
        	            		totalPTax+= priceC1; 	
	  				    	}
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC1 = (ecoPrice2 + taxPrice)*2;  
							   totalPTax+= priceC1; } 
				        }	
			        }
			    }
	  			else if (Class==2){	/*economy class 2 + 45.5*/
	  			
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		priceC2 = ecoPrice2 + taxPrice + 45.50 ; 
								totalPTax+= priceC2;  	 	
        	            	}
							else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC2 = (ecoPrice2 + taxPrice + 45.50)*2;
							   totalPTax+= priceC2; } 
					} 
					else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					  		if(PASS1[CURRENTUSER].flightType==1){
					  			priceC2 = ecoPrice + taxPrice + 45.50;
	        	            	totalPTax+= priceC2; 	
							}
							else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC2 = (ecoPrice + taxPrice + 45.50)*2; 
							   totalPTax+= priceC2; }  
				        }
					}
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		priceC2 = ecoPrice + taxPrice + 45.50;
		  				        totalPTax+= priceC2; 	
        	            	}
							else if(PASS1[CURRENTUSER].flightType==2){ 
								priceC2 = (ecoPrice + taxPrice + 45.50)*2; 
								totalPTax+= priceC2; 
							}  
				        }else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
				        	if(PASS1[CURRENTUSER].flightType==1){
				        		priceC2 = ecoPrice2 + taxPrice + 45.50;
					        	totalPTax+= priceC2; 	
				        	} 
				        	else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC2 = (ecoPrice2 + taxPrice + 45.50)*2; 
							   totalPTax+= priceC2; } 
			            }
			    	}
			    }
	  			else if(Class==3){	/*economy class 3 +205.9*/
	  			
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
	        	            	priceC3 = ecoPrice2 + taxPrice + 205.90;
								totalPTax+= priceC3;  
							}
							else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC3 = (ecoPrice2 + taxPrice + 205.90)*2; 
							   totalPTax+= priceC3; 
							}   	
					} 
					else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					  		if(PASS1[CURRENTUSER].flightType==1){
	        	            	priceC3 = ecoPrice + taxPrice + 205.90;
	        	            	totalPTax+= priceC3; 
	        	            }
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC3 = (ecoPrice + taxPrice+ 205.90)*2;  
							   totalPTax+= priceC3; } 
				        }
					}
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
		  				        priceC3 = ecoPrice + taxPrice + 205.90;
		  				        totalPTax+= priceC3; 
		  				    }
	  				        else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC3 = (ecoPrice + taxPrice + 205.90)*2; 
							   totalPTax+= priceC3; 
							} 
	  				    }else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
	  				    	if(PASS1[CURRENTUSER].flightType==1){
							  	priceC3 = ecoPrice2 + taxPrice + 205.90;  
	        	            	totalPTax+= priceC3; 
	        	            }        	            	
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { priceC3 = (ecoPrice2 + taxPrice + 205.90)*2;  
							   totalPTax+= priceC3; } 
			            }
	  			    }
	  				cout<<"Lunch = a)Nasi lemak  b)Spagetti   c)Fish n Chip"<<endl;
	  				cin>>lunch;
	  				cout << endl << endl;
				}
	  		
	  			break;
		case'B': case'b':
	  			cout<<"1)Bussiness classic"<<"\nCabin baggage 7kg"<<"\nComplimentary snacks/meal & beverages"<<"\nLunch provided"<<"\nNo check-in baggage"<<"\nNo free seat selection"<<"\nNo flexibility to board earlier on day of travel"<<"\nRebooking not available"<<"\nRefund not available"<<endl;
	  			cout<<"Normal price = RM"<< busPrice << " OR " << busPrice2 <<endl;
	  			cout<<"\n2)Bussiness premium"<<"\nCabin baggage 7kg"<<"\nCheck-in baggage 20kg"<<"\nComplimentary snacks/meal & beverages"<<"\nLunch provided"<<"\nRebooking:1x Free change fee(fare difference applies)"<<"\nRefund at a fee"<<"\nUpgrade with Enrich Point"<<"\nNo free seat selection"<<"\nNo flexibility to board earlier on day of travel"<<endl;
	  			cout<<"*for return ticket add on is added on both ticket"<<endl;
				cout<<"+RM80.50"<<endl;
	  			cout<<"\n3)Business flex"<<"\nCabin baggage 7kg"<<"\nCheck-in baggage 35kg"<<"\nComplimentary snacks/meal & beverages"<<"\nLunch provided"<<"\nRebooking:Unlimited Free change fee(fare difference applies)"<<"\nFlexibility to board earlier on day of travel(subject to avaibility)";
				cout<<"\nRefund without fee"<<"\nPriority check in"<<"\nPriority Boarding"<<"\nPriority baggage"<<"\nBasic Travel Protection"<<endl;
	  			cout<<"*for return ticket add on is added on both ticket"<<endl;
				cout<<"+RM240.60"<<endl;
	  			
	  			cout<<"Choose Your Bussiness class :";
	  			cin>>Class;
	  			while(Class<1 && Class>3 || Class==false || Class==false && Class==true){
		            cout << "\t\t\t\t>> Title entered is invalid, please enter again : ";
		            cin.clear();
		            cin.ignore(256,'\n');
		            cin >> Class;
		    	}
	  			if (Class==1){
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
	        	            	busP1 = busPrice2 + taxPrice;
								totalPTax+= busP1;   
							}
							else if(PASS1[CURRENTUSER].flightType==2){ 
							busP1 = (busPrice2 + taxPrice)*2;  
							totalPTax+= busP1; 
							}	
					  } else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					  		if(PASS1[CURRENTUSER].flightType==1){
	        	            	busP1 = busPrice + taxPrice;
	        	            	totalPTax+= busP1; 
	        	            }
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { busP1 = (busPrice + taxPrice)*2;
							   totalPTax+= busP1; }	
				        }
					}
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
		  				        busP1 = busPrice + taxPrice;
		  				        totalPTax+= busP1; 
		  				    }
	  				        else if(PASS1[CURRENTUSER].flightType==2){ 
							 busP1 = (busPrice + taxPrice)*2; 
							totalPTax+= busP1; 
							}
	  				    }
						else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					    	if(PASS1[CURRENTUSER].flightType==1){
		    	            	busP1 = busPrice2 + taxPrice ;
		    	            	totalPTax+= busP1; 
		    	        	}
			            	else if(PASS1[CURRENTUSER].flightType==2){ 
								busP1 = (busPrice2 + taxPrice)*2; 
								totalPTax+= busP1; 
							}
			            }
	  				}	
	  				cout<<"Lunch = a)Nasi lemak  b)Spagetti   c)Fish n Chip"<<endl;
	  				cin>>lunch;
	  				cout << endl << endl;	
				}
	  			else if (Class==2)	/*bussiness class2 + 80.50*/
	  			{	
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
	        	            	busP2 = busPrice2 + taxPrice + 80.50;  
								totalPTax+= busP2; 	
							}
							else if(PASS1[CURRENTUSER].flightType==2)
							 { busP2 = (busPrice2 + taxPrice + 80.50)*2;  
							   totalPTax+= busP2; }
					} 
					else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					  		if(PASS1[CURRENTUSER].flightType==1){
	        	            	totalPTax+= busP2; 
	        	            }
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							{ 
								busP2 = (busPrice + taxPrice + 80.50)*2; 
							   	totalPTax+= busP2; }
				        	}
					}
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
		  				        busP2 = busPrice + taxPrice + 80.50;
		  				        totalPTax+= busP2; 
		  				    }
	  				        else if(PASS1[CURRENTUSER].flightType==2)
							 { busP2 = (busPrice + taxPrice + 80.50)*2;
							   totalPTax+= busP2; }
							   
	  				    }
						else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
	  				    	if(PASS1[CURRENTUSER].flightType==1){
	        	            	busP2 = busPrice2 + taxPrice + 80.50;
	        	            	totalPTax+= busP2; 
	        	            }
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { 
								busP2 = (busPrice2 + taxPrice + 80.50)*2; 
								totalPTax+= busP2; 
							}
			            }
	  			    }
	  				cout<<"Lunch = a)Nasi lemak  b)Spagetti   c)Fish n Chip"<<endl;
	  				cin>>lunch;
					cout << endl << endl;
				}
	  			else if(Class==3)	/*business class3 + 240.6*/
	  			{	
	  				if(PASS1[CURRENTUSER].arrival>9 && PASS1[CURRENTUSER].arrival<33){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		busP3 = busPrice2 + taxPrice + 240.60; 
								totalPTax+= busP3; 
							}	
							else if(PASS1[CURRENTUSER].flightType==2)
							 { busP3 = (busPrice2 + taxPrice +240.60)*2;  
							   totalPTax+= busP3; }
							   
					  } else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
					  		if(PASS1[CURRENTUSER].flightType==1){
					  			busP3 = busPrice + taxPrice + 240.60;
	        	            	totalPTax+= busP3; 
							}
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							{ busP3 = (busPrice + taxPrice + 240.60)*2;  
							   totalPTax+= busP3; 
							}
				        }
					}
					else if(PASS1[CURRENTUSER].arrival>0 && PASS1[CURRENTUSER].arrival<10){
        	            if(PASS1[CURRENTUSER].destination > 0 && PASS1[CURRENTUSER].destination < 10 ){
        	            	if(PASS1[CURRENTUSER].flightType==1){
        	            		busP3 = busPrice + taxPrice + 240.60;
		  				        totalPTax+= busP3;
							}
							else if(PASS1[CURRENTUSER].flightType==2)
							 { busP3 = (busPrice + taxPrice + 240.60)*2; \
							   totalPTax+= busP3; 
							   } 
	  				    }else if(PASS1[CURRENTUSER].destination > 9 && PASS1[CURRENTUSER].destination < 33 ){
	  				    	if(PASS1[CURRENTUSER].flightType==1){
	        	            	busP3 = busPrice2 + taxPrice + 240.60 ;\
	        	            	totalPTax+= busP3; 
	        	            }
        	            	else if(PASS1[CURRENTUSER].flightType==2)
							 { busP3 = (busPrice2 + taxPrice + 240.60)*2;  \
							   totalPTax+= busP3; }
			            }
	  			    }
	  				cout<<"Lunch = a)Nasi lemak  b)Spagetti   c)Fish n Chip"<<endl;
	  				cin>>lunch;
	  				cout << endl << endl;
				}
	  			break;          
   	    	}
   		passcount++;
   }
	
    cout << "\t\t\t\t----------------PAYMENT-----------------"<<endl;
	cout<<"\t\t\t\tPayment by Visa or Master? (V/M) :";
	cin>>PType;
	while (PType != 'V' && PType != 'v' && PType != 'M' && PType != 'm') 
	{
		cout<<"\t\t\t\t>> Invalid,Please enter again :";
		cin>>PType;
	}
	
	cout<<"\t\t\t\tEnter card number 16 digit :";
	cin >> cardNum;
	while (cardNum.length() != 16)
	{
		cout<<"\t\t\t\tInvalid card number,Please enter again :";
		cin >> cardNum;
	}
	cout<<"\t\t\t\tEnter CVV/CVV2:";
	cin >> cvv;
	while(cvv.length()!=3)
	{
		cout<<"\t\t\t\tInvalid CVV/CVV2,Please enter again :";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> cvv;
	}
	cout <<"\t\t\t========================================================\n";
	cout << "\t\t\t\tPayment after tax (RM65.00 each ticket) : RM" << totalPTax << endl;
	cout <<"\t\t\t=========================================================\n\n";
       
}

void ticket(Registeration *&PASSENGER, passBooking *&PASS1, const int CURRENTUSER, int NUMPASS, string time[][2],string airport[][2]){
	
	int passcount=1;
	cout <<"\t\t\t********************************************************\n";
	cout << "\t\t\t\t\tFLIGHT TICKET\n";
	cout <<"\t\t\t********************************************************\n\n";
	
	while(passcount<=NUMPASS){
		cout<<"\nTHIS IS YOUR BOARDING PASS"<<endl;
		cout<<"_____________________________________________________________________________________\n";
		if (PASS1[CURRENTUSER].cabin[passcount-1]=='E' || PASS1[CURRENTUSER].cabin[passcount-1]=='e' )
			cout<<setw(50)<<"ECONOMY"<<endl;
		else 
		cout<<setw(50)<<"BUSINESS" << endl;
		
		
	    if (PASS1[CURRENTUSER].user=='y' || PASS1[CURRENTUSER].user=='Y'){
			cout<<setw(50)<<"NAME "<<PASSENGER[CURRENTUSER].name.lName<<" "<<PASSENGER[CURRENTUSER].name.fName<<endl;
		}else{
			cout<<setw(50)<<"NAME "<<PASS1[CURRENTUSER].passLName2[passcount-1]<<" "<<PASS1[CURRENTUSER].passFName2[passcount-1]<<endl;
		}
		
		cout<<setw(50)<<"DATE "<<PASS1[CURRENTUSER].departDay<<"/"<<PASS1[CURRENTUSER].departMonth<<"/"<<PASS1[CURRENTUSER].departYear<<endl;
		cout<<setw(50)<<"FROM "<<airport[PASS1[CURRENTUSER].destination][0]<< "| FLIGHT CODE: " << airport[PASS1[CURRENTUSER].destination][1]<<endl;
		cout<<setw(50)<<"TO "<<airport[PASS1[CURRENTUSER].arrival][0]<<endl;
	    cout<<setw(50)<<"SEAT "<<PASS1[CURRENTUSER].seatPass[passcount-1] << endl;
        cout <<setw(50)<< "TIME " << time[PASS1[CURRENTUSER].departTime][0] << endl;
        cout<<"____________________________________________________________________________________________________\n" << endl;
        
		passcount++; 
	}
	passcount=1;
	if(PASS1[CURRENTUSER].flightType==2){
		while(passcount<=NUMPASS){
			cout<<setw(50)<<"\nTHIS IS YOUR BOARDING PASS"<<endl;
			cout<<"_________________________________________________________________________________________________\n" << endl;
			if (PASS1[CURRENTUSER].cabin[passcount-1]=='E' || PASS1[CURRENTUSER].cabin[passcount-1]=='e')
				cout<<setw(50)<<"\t\tECONOMY"<<endl;
			else 
			    cout<<setw(50)<<"\t\tBUSINESS"<<endl;
			
			if (PASS1[CURRENTUSER].user=='y' || PASS1[CURRENTUSER].user=='Y')
				cout<<setw(50)<<"NAME "<<PASSENGER[CURRENTUSER].name.fName<<" "<<PASSENGER[CURRENTUSER].name.fName<<endl;
			else 
				cout<<setw(50)<<"NAME "<<PASS1[CURRENTUSER].passLName2[passcount-1]<<" "<<PASS1[CURRENTUSER].passFName2[passcount-1]<<endl;
			
	
			cout<<setw(50)<<"DATE "<< PASS1[CURRENTUSER].returnDay << "/" << PASS1[CURRENTUSER].returnMonth << "/" << PASS1[CURRENTUSER].returnYear << endl;
			cout<<setw(50)<<"FROM "<<airport[PASS1[CURRENTUSER].arrival][0] << "| FLIGHT CODE: " << airport[PASS1[CURRENTUSER].arrival][1]<<endl;
		 	cout<<setw(50)<<"TO "<<airport[PASS1[CURRENTUSER].destination][0]<<endl;
	  	    cout<<setw(50)<<"SEAT "<<PASS1[CURRENTUSER].seatPass[passcount-1] << endl;
	        cout <<setw(50)<< "TIME " << time[PASS1[CURRENTUSER].returnTime][1] << endl;
	
			cout<<"_____________________________________________________________________________________\n" << endl;
			passcount++;
		}
	}
	

	cout<<setw(50)<<"\nSECURITY REQUIREMENTS\n"<<"1.Ensure that your baggage is in your possession at all times\n"<<"2.You must be aware of the contents in your baggage\n";
	cout<<setw(50)<<"3.You need to be aware that the classified dangerous goods are not permitted in your baggage\n";
	cout<<setw(50)<<"IMPORTANT NOTICE\n"<<"1.Boarding gate closes 20 minutes before departure time\n"<<"2.Ensure that you have all the valid travel documents with you\n";
	cout<<setw(50)<<"3.For travel within Malaysia, ensure that you have bring along your valid Passport or Malaysia MyKad or birth certificate\n";
}