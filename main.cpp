#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include<algorithm>

using namespace std;

void myMain();
void adminDashboard();
void studentDashboard();
void takeQuiz(string);
void updateInfo();
void updateUserData(string, string);
void personRegister(string);
void genAdminCred();
string generateRandomString(int);
void operationOnUsers();
void delUser(string,string);
void readUser(string,string);
void teacherDashboard();
void createQuiz(string,string);
void viewResult(string, string);
void editQuiz(string,string);
void readQuiz(string,string,string);
void exit();

struct validDetails {
	string username;
	string password;
};
struct Details{
	string name;
	string age;
	string mSubject;
	string username;
	string password;
};
struct Quiz{
	string subjectTitle;
	string description;
	int tQuestions;
	int time;
	string Class;
};
struct Question{
	string statement;
	string options[4];
	int correctOption;
};

int quizTimeA=0;
int quizTimeB=0;
string loggedInUsername;

void shuffleOptions(Question &q);

int main(){
	cout<< "<========== Welcome to our SMART QUIZ MAKER APP ==========>"<<endl<<endl;
	myMain();
	return 0;
}

void myMain(){
	int choise;
	do{
		cout<< "Choose which feature do you want to use?"<<endl;
		cout<< "1. Admin Feature\n";
		cout<< "2. Student Feature\n";
		cout<< "3. Teacher Feature\n";
		cout<< "0. Exit\n";
		
		cin>> choise;
		
		switch(choise){
		case 1:
			cout<< "\n\n==============================\n\nYou choosed Admin Dashboard\n";
			adminDashboard();
			break;
		case 2:
			studentDashboard();
			break;
		case 3:
			teacherDashboard();
			break;
		case 0:
			exit();
			break;
		default:
			cout<< "<==== Invalid Choise!! ====>\nChoose again from (1 to 3 or 0 => exit )\n\n";
		}
	}while (!(choise>=0 && choise<=3));
}

void adminDashboard(){
	cout<< "<========== Welcome to Admin Dashboard ==========>";
	int choise;
	validDetails checkDetails;
	string Username, Password;
	int newRegister;
	string person;
	ifstream file("adminFile.txt");
	string ch;
	bool empty = !(file >> ch);
	file.close();
	 
	if (empty) {
	    ofstream adminFile("adminFile.txt", ios::app);
	    adminFile << "Admin1 Admin112215\n";
	    adminFile.close();
	}
	
	bool found =false;
	
	do{
		cout<< "\n\nEnter Admin Username : ";
		cin>> checkDetails.username;
		cout<< "Enter Admin Password : ";
		cin>> checkDetails.password;
		cout<<endl;
	
		ifstream adminFileRead("adminFile.txt");

        while (adminFileRead >> Username>>Password) {
			found = false;
            if (Username == checkDetails.username &&
                Password == checkDetails.password) {
                found = true;
                break;
            }
        }

        adminFileRead.close();
	    		if(found){
	    			do{
			    		cout<< "Choose which feature do you want to use?"<<endl;
						cout<< "1. LogIn to Teacher Dashboard\n";
						cout<< "2. Update Info\n";
						cout<< "3. Register new Student or Teacher\n";
						cout<< "4. Generate new Admin Credentials\n";
						cout<< "5. Add, Remove, Search User\n";
						cout<< "0. Logout\n";
						cin>> choise;
						
						switch(choise){
							case 1:
								teacherDashboard();
								break;
							case 2:
								updateInfo();
								break;
							case 3:
								do{
									cout<< "\nEnter 1 => Register new Student & 2 => Register new Teacher : ";
									cin>> newRegister;
										if(newRegister == 1){
												person = "Student";
												personRegister(person);
											}else if(newRegister == 2){
												person = "Teacher";
												personRegister(person);
											}else{
												cout<< "<==== Invalid Choise!! ====>\nChoose again from (1 or 2)\n\n";
										}
									}while(newRegister != 1 && newRegister !=2);
									break;
								case 4:
									genAdminCred();
									break;
								case 5:
									operationOnUsers();
									break;
								case 0:
									myMain();
									break;
								default:
									cout<< "<==== Invalid Choise!! ====>\nChoose again from (1 to 3 or 0 => exit )\n\n";
								}
								}while (!(choise<=5 && choise>=1));
						}else{
							cerr<< "Credentials don't Match!!";
					}
	
	}while(!found);
	file.close();
}

void updateInfo(){
	string person;
	
	cout<< "\n\n==============================\n\nYou choosed to Update Info of Users\n";
	
	do{
		cout<< "Whose info you want to update? (t => Teacher OR s => Student) : ";
		cin>>person;
		
		if(person != "s" && person != "t") {
			cout<< "<==== Invalid Choise!! ====>\nChoose again (t => Teacher OR s => Student)\n\n";
		}
	}while(person != "s" && person != "t");
	
	if(person == "t"){
		person = "Teacher";
		updateUserData("teacherFile.txt", person);
		myMain();
	}else{
		person = "Student";
		updateUserData("studentFile.txt", person);
		myMain();
	}
}

void updateUserData(string filename, string person) {

    ifstream readFile(filename);
    vector<Details> userDetail;
    Details d;
    string updateChoise;

    while (readFile >> d.name >> d.age >> d.mSubject >> d.username >> d.password) {
        userDetail.push_back(d);
    }
    readFile.close();

    for (int i = 0; i < userDetail.size(); i++) {
        cout << i + 1 << ". " << userDetail[i].name << endl;
    }

    int choice;
    do {
        cout << "Whose Data you want to Update? (1 - " << userDetail.size() << "): ";
        cin >> choice;

        if (choice < 1 || choice > userDetail.size()) {
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice < 1 || choice > userDetail.size());

    do {
        cout << "Which info of this " << person << " you want to update?";
    	cout << "\nName (Input n)?\nAge (Input a)?\nMajor Subject (Input m)?\nUsername (Input u)?\nPassword (Input p)?\n";
    	cin >> updateChoise;

        if (updateChoise != "n" && updateChoise != "a" &&
            updateChoise != "m" && updateChoise != "u" &&
            updateChoise != "p") {
            cout << "Invalid option! Try again.\n";
        }

    } while (updateChoise != "n" && updateChoise != "a" &&
             updateChoise != "m" && updateChoise != "u" &&
             updateChoise != "p");

    if (updateChoise == "n") {
        cout << "Enter new name: ";
        cin >> userDetail[choice - 1].name;
    }
    else if (updateChoise == "a") {
            cout << "Enter new age: ";
            cin >> userDetail[choice - 1].age;
    }
    else if (updateChoise == "m") {
        cout << "Enter new Major Subject: ";
        cin >> userDetail[choice - 1].mSubject;
    }
    else if (updateChoise == "u") {
        cout << "Enter new Username: ";
        cin >> userDetail[choice - 1].username;
    }
    else if (updateChoise == "p") {
        cout << "Enter new Password: ";
        cin >> userDetail[choice - 1].password;
    }

    ofstream writeFile(filename);
    for (int i = 0; i < userDetail.size(); i++) {
        writeFile << userDetail[i].name << " "
                  << userDetail[i].age << " "
                  << userDetail[i].mSubject << " "
                  << userDetail[i].username << " "
                  << userDetail[i].password << endl;
    }
    writeFile.close();

    cout << "\nUser updated successfully!" << endl;
}

void personRegister(string person) {
    Details details;

    cout << "\nYou chose " << person << " Registration\n";
    cout << "<========== Register New " << person << " ==========>\n";

    cout << "Enter " << person << " Name : ";
    cin >> details.name;

    cout << "Enter " << person << " Age : ";
    cin >> details.age;

    cout << "Enter " << person << " Major Subject : ";
    cin >> details.mSubject;

    cout << "Enter " << person << " Username : ";
    cin >> details.username;

    cout << "Enter " << person << " Password : ";
    cin >> details.password;

    if (person == "Student") {
        ofstream studentFile("studentFile.txt", ios::app);
        studentFile << details.name << " "
                    << details.age << " "
                    << details.mSubject << " "
                    << details.username << " "
                    << details.password << "\n";
        studentFile.close();
    } else {
        ofstream teacherFile("teacherFile.txt", ios::app);
        teacherFile << details.name << " "
                    << details.age << " "
                    << details.mSubject << " "
                    << details.username << " "
                    << details.password << "\n";
        teacherFile.close();
    }

    cout << "\n<========== New " << person << " Registered Successfully ==========>\n";
    myMain();
}

void genAdminCred(){
	validDetails details;
	int length =8;
	srand(time(0));
	
	details.username = generateRandomString(length);
	cout<< "Your New Admin Username is : " <<details.username ;
	details.password = generateRandomString(length);
	cout<< "\nYour New Admin Password is : " <<details.password <<endl;
	
	ofstream newAdmin("adminFile.txt", ios::app);
	newAdmin<<endl<<details.username<< " " <<details.password;
	newAdmin.close();
	cout<< "New admin registered successfully !!\n";
	
	myMain();
}

string generateRandomString(int length) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string result = "";

    for (int i = 0; i < length; ++i) {
        result += chars[rand() % chars.size()];
    }

    return result;
}

void operationOnUsers(){
	int choise;
	string userChoise;
	do{
		cout<< "\nWhich operation do you want to use?";
		cout<< "\nAdd User?(Press 1)\nDel User?(Press 2)\nSearch User?(Press 3)";
		cin>> choise;	
	}while(!(choise>=1 && choise <=3));
	
	switch(choise){
		case 1:
			do{
				cout<< "Do you want to add new Teacher or Student? (press s=> Student & t=> Teacher) :";
				cin>> userChoise;
				if(userChoise == "t"){
					personRegister("Teacher");
				}else{
					personRegister("Student");
				}	
			}while(!(userChoise == "t" && userChoise == "s"));
			break;
		case 2:
			do{
				cout<< "Which user do you want to del Teacher or Student? (press s=> Student & t=> Teacher) :";
				cin>> userChoise;
				if(userChoise == "t"){
					delUser("teacherFile.txt", "Teacher");
				}else{
					delUser("student.txt","Student");
				}	
			}while(!(userChoise == "t" && userChoise == "s"));
			case 3:
				do{
						cout<< "Which user data do you want to read Teacher or Student? (press s=> Student & t=> Teacher) :";
						cin>> userChoise;
						if(userChoise == "t"){
							readUser("teacherFile.txt", "Teacher");
						}else{
							readUser("studentFile.txt", "Student");
						}	
					}while(!(userChoise == "t" && userChoise == "s"));
	}
	
}

void delUser(string filename, string person) {

    ifstream readFile(filename);
    vector<Details> userDetail;
    Details d;
    string updateChoise;

    while (readFile >> d.name >> d.age >> d.mSubject >> d.username >> d.password) {
        userDetail.push_back(d);
    }
    readFile.close();

    for (int i = 0; i < userDetail.size(); i++) {
        cout << i + 1 << ". " << userDetail[i].name << endl;
    }

    int choice;
    do {
        cout << "Whose Data you want to Delete? (1 - " << userDetail.size() << "): ";
        cin >> choice;

        if (choice < 1 || choice > userDetail.size()) {
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice < 1 || choice > userDetail.size());    
    userDetail[choice -1].name = " ";
    userDetail[choice -1].age = " ";
    userDetail[choice -1].mSubject = " ";
    userDetail[choice -1].username = " ";
    userDetail[choice -1].password = " ";
    ofstream writeFile(filename);
    for (int i = 0; i < userDetail.size(); i++) {
        writeFile << userDetail[i].name << " "
                  << userDetail[i].age << " "
                  << userDetail[i].mSubject << " "
                  << userDetail[i].username << " "
                  << userDetail[i].password << endl;
    }
    writeFile.close();

    cout << "\nUser deleted successfully!" << endl;
    
    myMain();
}

void readUser(string filename, string person){
	ifstream readFile(filename);
	Details d;
	while(readFile >> d.name >> d.age >> d.mSubject >> d.username >> d.password){
		cout<< person << " Name : "<<d.name<<endl << person << " Age : "<<d.age<<endl<< person << " Major Subjects : "<<d.mSubject<<endl<< person << " Username : "<<d.username<<endl<< person << " Password : "<<d.password<<endl;
		cout<< endl;
	}
	readFile.close();
	cout<< "\n" << person<< " Readed Successfully !!";
	
	myMain(); 	
}

void studentDashboard(){
	string firstLine;
    int choice;
    validDetails details;
    Details checkDetails;
    bool found = false;

    cout << "\nYou choose Student Dashboard\n";
    cout << "<========== Welcome to Student Dashboard ==========>\n";

    do {
        cout << "\nEnter Student Username: ";
        cin >> details.username;
        cout << "Enter Student Password: ";
        cin >> details.password;

        ifstream studentFileRead("studentFile.txt");

        if (!studentFileRead) {
            cerr << "Error opening file!\n";
            return;
        }
        
        found = false;

        while (studentFileRead >> checkDetails.name
                               >> checkDetails.age
                               >> checkDetails.mSubject
                               >> checkDetails.username
                               >> checkDetails.password) {

            if (details.username == checkDetails.username &&
                details.password == checkDetails.password) {
                found = true;
                break;
            }
        }
		loggedInUsername = checkDetails.name;
        studentFileRead.close();

        if (found) {
            do {
                cout << "\nChoose option:\n";
                cout << "1. Update Info\n";
                cout << "2. Take Quiz\n";
                cout << "0. Logout\n";
                cin >> choice;

                if (choice == 0) {
                    myMain();
                    return;
                }

            } while (choice < 0 || choice > 4);

        } else {
            cout << "\nCredentials don't match! Try again.\n";
        }
        switch(choice){
        	case 1:
        		updateUserData("studentFile.txt", "Student");
        		myMain();
        		break;
        	case 2:
        		readQuiz("quizA.txt", "quizB.txt","Student");
		}
    } while (!found);
	
}

void teacherDashboard() {
    int choice;
    validDetails details;
    Details checkDetails;
    bool found = false;

    cout << "\nYou choose Teacher Dashboard\n";
    cout << "<========== Welcome to Teacher Dashboard ==========>\n";

    do {
        cout << "\nEnter Teacher Username: ";
        cin >> details.username;
        cout << "Enter Teacher Password: ";
        cin >> details.password;

        ifstream teacherFileRead("teacherFile.txt");

        if (!teacherFileRead) {
            cerr << "Error opening file!\n";
            return;
        }

        
        found = false;

        while (teacherFileRead >> checkDetails.name
                               >> checkDetails.age
                               >> checkDetails.mSubject
                               >> checkDetails.username
                               >> checkDetails.password) {

            if (details.username == checkDetails.username &&
                details.password == checkDetails.password) {
                found = true;
                break;
            }
        }

        teacherFileRead.close();

        if (found) {
            do {
                cout << "\nChoose option:\n";
                cout << "1. Update Info\n";
                cout << "2. Create Quiz\n";
                cout << "3. Edit Quiz\n";
                cout << "4. View Result\n";
                cout<< "5. Preview Quiz\n";
                cout << "0. Logout\n";
                cin >> choice;

                if (choice == 0) {
                    myMain();
                    return;
                }

            } while (choice < 0 || choice > 5);

        } else {
            cout << "\nCredentials don't match! Try again.\n";
        }
        switch(choice){
        	case 1:
        		updateUserData("teacherFile.txt", "Teacher");
        		break;
        	case 2:
        		createQuiz("quizA.txt","quizB.txt");
        		break;
        	case 3:
        		editQuiz("quizA.txt","quizB.txt");
        		break;
        	case 4:
        		viewResult("scoreA.txt" , "scoreB.txt");
        		break;
        	case 5:
        		readQuiz("quizA.txt","quizB.txt", "Teacher");
        		break;
		}
    } while (!found);
}

void createQuiz(string filenameA, string filenameB){
	Quiz quiz;
	vector<Question> question;
	Question q;
	cout<< "\n<=========== Create Quiz ==========>"<<endl;
	cout<< "Enter Quiz Title : ";
	cin>> quiz.subjectTitle;
	cout<< "\nEnter brief Description : ";
	cin.ignore();
	getline(cin,quiz.description);
	cout<< "To which section you want to assign this quiz? (There are only 2 Sections A & B): ";
	getline(cin,quiz.Class);
	cout<< "\nEnter Total Questions you want to create : ";
	cin>> quiz.tQuestions;
	cout<< "\nEnter time you want to assing in minutes : ";
	cin>> quiz.time; 
	if(quiz.Class == "A"){
		quizTimeA=quiz.time;
	}else{
		quizTimeB=quiz.time;
	}
	
	                 
	if(quiz.Class == "A"){
		ofstream writeFile(filenameA, ios::app);
		for (int i = 1; i <= quiz.tQuestions; i++) {

		    cout << "\nEnter Statement of Question " << i << " : ";
		    cin.ignore();
		    getline(cin, q.statement);
		
		    for (int j = 0; j < 4; j++) {
		        cout << "Enter Option (" << j + 1 << ") : ";
		        getline(cin, q.options[j]);
		    }
		
		    do {
		        cout << "Enter correct option (1-4) : ";
		        cin >> q.correctOption;
		    } while (q.correctOption < 1 || q.correctOption > 4);
		
		    question.push_back(q);
		
		    writeFile << q.statement << endl;
		    for (int j = 0; j < 4; j++) {
		        writeFile << q.options[j] << endl;
		    }
		    writeFile << q.correctOption << endl;
		    writeFile << "----" << endl;
		}
		
			cout<< "Quiz created Successfully!! (For Section A)";
		
			writeFile.close();
			teacherDashboard();	
	}else if(quiz.Class == "B"){
		ofstream writeFile(filenameB, ios::app);
		for (int i = 1; i <= quiz.tQuestions; i++) {

		    cout << "\nEnter Statement of Question " << i << " : ";
		    cin.ignore();
		    getline(cin, q.statement);
		
		    for (int j = 0; j < 4; j++) {
		        cout << "Enter Option (" << j + 1 << ") : ";
		        getline(cin, q.options[j]);
		    }
		
		    do {
		        cout << "Enter correct option (1-4) : ";
		        cin >> q.correctOption;
		    } while (q.correctOption < 1 || q.correctOption > 4);
		
		    question.push_back(q);
		
		    writeFile << q.statement << endl;
		    for (int j = 0; j < 4; j++) {
		        writeFile << q.options[j] << endl;
		    }
		    writeFile << q.correctOption << endl;
		    writeFile << "----" << endl;
		}
		
			cout<< "Quiz created Successfully!! (For Section A)";
		
			writeFile.close();
			teacherDashboard();
	}
}

void editQuiz(string filenameA, string filenameB) {
    vector<Question> questions;
    Question q;
    string choise;
    
    cout<<"Which section's quiz do you want to create? (A or B) : ";
    cin>> choise;
    
    do{
    if (choise == "A"){
    		ifstream readFile(filenameA);
    		while (getline(readFile, q.statement)) {

			        for (int i = 0; i < 4; i++) {
			            getline(readFile, q.options[i]);
			        }
			
			        readFile >> q.correctOption;
			
			        questions.push_back(q);
			    }
			    readFile.close();
			
			    for (int i = 0; i < questions.size(); i++) {
			        cout << i + 1 << ". " << questions[i].statement << endl;
			    }
			
			    int choice;
			    do {
			        cout << "\nWhich question do you want to edit? ";
			        cin >> choice;
			    } while (choice < 1 || choice > questions.size());
			
			    cin.ignore();
			
			    cout << "\nEnter new statement: ";
			    getline(cin, questions[choice - 1].statement);
			
			    for (int i = 0; i < 4; i++) {
			        cout << "Enter option (" << i + 1 << "): ";
			        getline(cin, questions[choice - 1].options[i]);
			    }
			
			    do {
			        cout << "Enter correct option (1-4): ";
			        cin >> questions[choice - 1].correctOption;
			    } while (questions[choice - 1].correctOption < 1 ||
			             questions[choice - 1].correctOption > 4);
			
			    ofstream writeFile(filenameA);
			    for (int i = 0; i < questions.size(); i++) {
			
			    writeFile << questions[i].statement << endl;
			
			    for (int j = 0; j < 4; j++) {
			        writeFile << questions[i].options[j] << endl;
			    }
			
			    writeFile << questions[i].correctOption << endl;
			    writeFile << "----" << endl;
			}
			    writeFile.close();
			
			    cout << "\nMCQ updated successfully!\n";	
	}else if(choise == "B"){
		ifstream readFile(filenameB);
    		while (getline(readFile, q.statement)) {

			        for (int i = 0; i < 4; i++) {
			            getline(readFile, q.options[i]);
			        }
			
			        readFile >> q.correctOption;
			
			        questions.push_back(q);
			    }
			    readFile.close();
			
			    for (int i = 0; i < questions.size(); i++) {
			        cout << i + 1 << ". " << questions[i].statement << endl;
			    }
			
			    int choice;
			    do {
			        cout << "\nWhich question do you want to edit? ";
			        cin >> choice;
			    } while (choice < 1 || choice > questions.size());
			
			    cin.ignore();
			
			    cout << "\nEnter new statement: ";
			    getline(cin, questions[choice - 1].statement);
			
			    for (int i = 0; i < 4; i++) {
			        cout << "Enter option (" << i + 1 << "): ";
			        getline(cin, questions[choice - 1].options[i]);
			    }
			
			    do {
			        cout << "Enter correct option (1-4): ";
			        cin >> questions[choice - 1].correctOption;
			    } while (questions[choice - 1].correctOption < 1 ||
			             questions[choice - 1].correctOption > 4);
			
			    ofstream writeFile(filenameB);
			    for (int i = 0; i < questions.size(); i++) {
			
			    writeFile << questions[i].statement << endl;
			
			    for (int j = 0; j < 4; j++) {
			        writeFile << questions[i].options[j] << endl;
			    }
			
			    writeFile << questions[i].correctOption << endl;
			    writeFile << "----" << endl;
			}
			    writeFile.close();
			
			    cout << "\nMCQ updated successfully!\n";
	}else cout<<"Invalid Choise!";
	}while(choise != "A" && choise != "B");
}

void readQuiz(string filenameA,string filenameB,string person) {
	string choise;
	 vector<Question> questions;
    Question q;
    string line;
    
	do{
	if(person == "Student"){
		cout<< "Which Section's quiz do you want to take? (A or B) : ";
		cin>> choise;
	}else{
		cout<< "Which Section's quiz do you want to preview? (A or B) : ";
		cin>> choise;
	}
		
	if(choise == "A" || choise == "a"){
		questions.clear();
		ifstream readFile(filenameA);
    if (!readFile) {
        cout << "Error opening file!\n";
        return;
    }

    while (getline(readFile, q.statement)) {

        if (q.statement == "") continue;

        for (int i = 0; i < 4; i++) {
            getline(readFile, q.options[i]);
        }

        readFile >> q.correctOption;
        readFile.ignore(); 

        getline(readFile, line);

        questions.push_back(q);
    }
	srand(time(0));   
	random_shuffle(questions.begin(), questions.end());

	for (int i = 0; i < questions.size(); i++) {
    shuffleOptions(questions[i]);
	}

    readFile.close();
    int userChoise;
    int score=0;

    if (questions.size() == 0) {
        cout << "No questions found in the quiz.\n";
        return;
    }
	
	auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < questions.size(); i++) {
        cout << "\nQuestion " << i+1 << ": " << questions[i].statement << endl;

        for (int j = 0; j < 4; j++) {
            cout << j + 1  << ") " << questions[i].options[j] << endl;
        }
		if (person == "Teacher"){
			cout << "Correct Option: " << questions[i].correctOption << endl;
		}else if(person == "Student"){
			cout<<"Enter correct option (1-4) : ";
			cin>>userChoise; cout<< endl;
			if(userChoise == questions[i].correctOption){
				cout<<"Correct!!\n";
				score++;
				cout<<"Your score is : "<<score;
			}else{
				cout<< "Incorrect !!";
			}
			auto end1 = chrono::high_resolution_clock::now();
    		auto minutesEndA = chrono::duration_cast<chrono::minutes>(end1 - start);
    		if(minutesEndA.count() > quizTimeA){
    			cout<<"\a";
    			break;
			}
		}
    }
    auto end = chrono::high_resolution_clock::now();
    auto minutes = chrono::duration_cast<chrono::minutes>(end - start);
    if (person == "Student"){
    	cout << "\nTime Taken: " << minutes.count() << " minutes";
    	ofstream file("scoreA.txt" , ios::app);
		file <<loggedInUsername<< " " << score <<endl;
    	studentDashboard();
	}else{
		cout << "\n<===== End of Quiz Preview =====>\n";
    	teacherDashboard();
	}	
	}else if(choise == "B"){
		questions.clear();
		ifstream readFile(filenameB);
    if (!readFile) {
        cout << "Error opening file!\n";
        return;
    }

    while (getline(readFile, q.statement)) {

        if (q.statement == "") continue;

        for (int i = 0; i < 4; i++) {
            getline(readFile, q.options[i]);
        }

        readFile >> q.correctOption;
        readFile.ignore(); 

        getline(readFile, line);

        questions.push_back(q);
    }
    srand(time(0));   
	random_shuffle(questions.begin(), questions.end());

	for (int i = 0; i < questions.size(); i++) {
    shuffleOptions(questions[i]);
	}

    readFile.close();
    int userChoise;
    int score=0;

    if (questions.size() == 0) {
        cout << "No questions found in the quiz.\n";
        return;
    }
	
	auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < questions.size() ; i++) {
        cout << "\nQuestion " << i + 1 << ": " << questions[i].statement << endl;

        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ") " << questions[i].options[j] << endl;
        }
		if (person == "Teacher"){
			cout << "Correct Option: " << questions[i].correctOption << endl;
		}else if(person == "Student"){
			cout<<"Enter correct option (1-4) : ";
			cin>>userChoise; cout<< endl;
			if(userChoise == questions[i].correctOption){
				cout<<"Correct!!";
				score++;
				cout<<"\n Your score is : " <<score;
			}else{
				cout<< "Incorrect !!";
			}
			auto end2 = chrono::high_resolution_clock::now();
    		auto minutesEndB = chrono::duration_cast<chrono::minutes>(end2 - start);
    		if(minutesEndB.count() > quizTimeB){
    			cout<<"\a";
    			break;
			}
		}
    }
	auto end = chrono::high_resolution_clock::now();
    auto minutes = chrono::duration_cast<chrono::minutes>(end - start);
    if (person == "Student"){
    	cout << "\nTime Taken: " << minutes.count() << " minutes";
    	ofstream file("scoreB.txt" , ios::app);
		file << loggedInUsername << " " << score <<endl;
    	studentDashboard();
	}else{
		cout << "\n<===== End of Quiz Preview =====>\n";
    	teacherDashboard();
	}
	}
	}while(choise != "A" && choise!= "B");
}

void shuffleOptions(Question &q) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;

        swap(q.options[i], q.options[r]);

        if (q.correctOption == i + 1)
            q.correctOption = r + 1;
        else if (q.correctOption == r + 1)
            q.correctOption = i + 1;
    }
}

void viewResult(string filenameA, string filenameB) {
    string section;
    cout << "Which section's result do you want to see? (A or B): ";
    cin >> section;

    string filename;
    if (section == "A" || section == "a") filename = filenameA;
    else if (section == "B" || section == "b") filename = filenameB;
    else {
        cout << "Invalid section!\n";
        return;
    }

    ifstream file(filename);
    if (!file) {
        cout << "No scores available for section " << section << "!\n";
        return;
    }

    string score,name;
    int count = 1;
    while (file >> name >> score) {
        if (!score.empty()) {
            cout << "Updated Score of "<< name << " is : " << score << endl;
        }
    }

    file.close();
}


void exit(){
	cout<< "You choosed to quit the System!!";
	exit(0);
}