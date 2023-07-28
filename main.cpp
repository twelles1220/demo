#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
	char bookNumber[6]; //bookno.
	char bookName[50]; //bookname
	char authorName[20]; //authorname
public:
	void createbook()
	{
		cout << "\n***********NEW BOOK***********\n";
		cout << "\nENTER BOOK NO.";
		cin >> bookNumber;
		cin.ignore();
		cout << "\nENTER BOOK NAME: ";
		cin.getline(bookName, 50);
		cout << "\nENTER AUTHOR NAME: ";
		cin.getline(authorName, 20);
		cout << "\n\n\nBook Created..";
	}
	void displayBook()
	{
		cout << "\nBook Number: " << bookNumber;
		cout << "\nBook Name: " << bookName;
		cout << "\nBook Author Name: " << authorName;
	}
	void editBook()
	{
		cout << "\nBook Number: " << bookNumber;
		cout << "\nModify Book Name: ";
		cin.ignore();
		cin.getline(bookName, 50);
		cout << "\nModify Author's Name: ";
		cin.getline(authorName, 20);
	}

	char* returnBookNumber() //string return
	{
		return bookNumber;
	}
	void displayBookSummary()
	{
		cout << bookNumber << setw(30) << bookName << setw(30) << authorName << endl;
	}
}; //class ends here

class Student
{
	char admissionNumber[6]; //admission no.
	char studentName[20];
	char studentBookNumber[6]; // student book no
	int noOfStudentBooks; //total book of student
public:
	void CreateStudentRecord()
	{
		cout << "\nNEW STUDENT ENTRY...\n";
		cout << "\nEnter The Admission No. ";
		cin >> admissionNumber;
		cin.ignore(); // Ignore the newline character in the input buffer
		cout << "Enter The Student Name: ";
		cin.getline(studentName, 20);
		noOfStudentBooks = 0;
		studentBookNumber[0] = '\0';
		cout << "\n\nStudent Record Created...";
	}
	void DisplayStudent()
	{
		cout << "\nAdmission Number: " << admissionNumber;
		cout << "\nStudent Name: " << studentName;
		cout << "\nNo of Book Issued: " << noOfStudentBooks;
		if (noOfStudentBooks == 1)
		{
			cout << "\nBook No.: " << studentBookNumber;
		}
	}
	void EditStudentRecord()
	{
		cout << "\nAdmission No. " << admissionNumber;
		cout << "\nModify Student Name: ";
		cin.ignore();
		cin.getline(studentName, 20);
	}
	char* returnAdmissionNumber()
	{
		return admissionNumber;
	}
	char* returnStudentBookNumber()
	{
		return studentBookNumber;
	}
	int returnNumberOfStudentBooks()
	{
		return noOfStudentBooks;
	}
	void addStudentBooks()
	{
		noOfStudentBooks = 1;
	}
	void resetStudentBooks()
	{
		noOfStudentBooks = 0;
	}
	void getStudentBookNumber(char t[])
	{
		strcpy(studentBookNumber, t);
	}
	void displayBookSummary()
	{
		cout << "\t" << admissionNumber << setw(20) << studentName << setw(10) << noOfStudentBooks << endl;
	}
}; //class ends here

fstream fp, fp1; //object
Book bk; //book class object
Student st; //student class object

void writeBook()
{
	char ch;
	fp.open("book.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		bk.createbook();
		fp.write((char*)&bk, sizeof(Book)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void writeStudent()
{
	char ch;
	fp.open("student.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		st.CreateStudentRecord();
		fp.write((char*)&st, sizeof(Student)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void showBook(char n[])
{
	cout << "\nBOOK DETAILS\n";
	int flag = 0; //book not found
	fp.open("book.dat", ios::in); //read data
	while (fp.read((char*)&bk, sizeof(Book)))
	{
		if (strcmp(bk.returnBookNumber(), n) == 0) //not case sensitive
		{
			bk.displayBook();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //book not found
	{
		cout << "\n\nBook does not exist";
	}
	system("pause");
}

void showStudent(char n[])
{
	cout << "\nSTUDENT DETAILS\n";
	int flag = 0; //student not found
	fp.open("student.dat", ios::in); //read data
	while (fp.read((char*)&st, sizeof(Student)))
	{
		if (strcmp(st.returnAdmissionNumber(), n) == 0) //not case sensitive
		{
			st.DisplayStudent();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //student not found
	{
		cout << "\n\nStudent does not exist";
	}
	system("pause");
}

void editBook()
{
	char n[6];
	int found = 0; //search book of given data
	system("cls");
	cout << "\n\nMODIFY BOOK RECORD...";
	cout << "\n\nEnter the book no. ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&bk, sizeof(Book)) && found == 0)
	{
		if (strcmp(bk.returnBookNumber(), n) == 0)
		{
			bk.displayBook();
			cout << "\nEnter the new details of the book";
			bk.editBook();
			int pos = -1 * (long)sizeof(bk);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char*)&bk, sizeof(Book));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	system("pause"); //press any key to get out
}

void EditStudentRecord()
{
	char n[6];
	int found = 0; //search book of given data
	system("cls");
	cout << "\n\nMODIFY STUDENT RECORD...";
	cout << "\n\nEnter the Admission no. ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(Student)) && found == 0)
	{
		if (strcmp(st.returnAdmissionNumber(), n) == 0)
		{
			st.DisplayStudent();
			cout << "\nEnter the new details of student";
			st.EditStudentRecord();
			int pos = -1 * (long)sizeof(st);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char*)&st, sizeof(Student));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	system("pause"); //press any key to get out
}

void deleteStudent()
{
	char n[6];
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE STUDENT...";
	cout << "\n\nEnter the Admission no> : ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&st, sizeof(Student)))
	{
		if (strcmp(st.returnAdmissionNumber(), n) != 0)
		{
			fp2.write((char*)&st, sizeof(Student));
		}
		else
		{
			flag = 1; //student found
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat", "student.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted..";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	system("pause");
}

void deletebook()
{
	char n[6]; //book no.
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE BOOK...";
	cout << "\n\nEnter the Book no> : ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	fstream fp2; //New object
	fp2.open("Temp.dat", ios::out); //temp having data else than that to be deleted
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&bk, sizeof(Book)))
	{
		if (strcmp(bk.returnBookNumber(), n) != 0)
		{
			fp2.write((char*)&bk, sizeof(Book));
		}
		else
		{
			flag = 1; //book found
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat", "book.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted... ";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	system("pause");
}

void displayAllStudents()
{
	system("cls");
	fp.open("student.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		system("pause");
		return; //press any key and return
	}
	cout << "\n\n\t\tStudent List\n\n";
	cout << "==================================================================\n";
	cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
	cout << "==================================================================\n";
	while (fp.read((char*)&st, sizeof(Student)))
	{
		st.displayBookSummary();
	}
	fp.close();
	system("pause");
}

void displayallb()
{
	system("cls");
	fp.open("book.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		system("pause");
		return; //press any key and return
	}
	cout << "\n\n\t\tBook List\n\n";
	cout << "==================================================================\n";
	cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
	cout << "==================================================================\n";
	while (fp.read((char*)&bk, sizeof(Book)))
	{
		bk.displayBookSummary();
	}
	fp.close();
	system("pause");
}

void bookissue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	system("cls");
	cout << "\n\nBOOK ISSUE...";
	cout << "\n\n\tEnter Admission no.: ";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(Student)) && found == 0)
	{
		if (strcmp(st.returnAdmissionNumber(), sn) == 0) //compare admission no.
		{
			found = 1;
			if (st.returnNumberOfStudentBooks() == 0) //if book not issued
			{
				cout << "\n\n\tEnter The Book No.: ";
				cin >> bn;
				while (fp1.read((char*)&bk, sizeof(Book)) && flag == 0)
				{
					if (strcmp(bk.returnBookNumber(), bn) == 0) //compare book no.
					{
						flag = 1;
						st.addStudentBooks();
						st.getStudentBookNumber(bk.returnBookNumber()); //pass book no.
						int pos = -1 * (long)sizeof(st);
						fp.seekg(pos, ios::cur);
						fp.write((char*)&st, sizeof(Student));
						cout << "\n\n\tBook Issued Successfully\n\nPlease Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day.";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exist";
				}
			}
			else
			{
				cout << "You Have Not Returned The Last Book";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Found...";
	}
	fp.close();
	fp1.close();
	system("pause");
}

void bookdeposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	system("cls");
	cout << "\n\nBOOK DEPOSIT...";
	cout << "\n\n\tEnter Admission no. Of Student: ";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(Student)) && found == 0)
	{
		if (strcmp(st.returnAdmissionNumber(), sn) == 0) //compare admission no.
		{
			found = 1;
			if (st.returnNumberOfStudentBooks() == 1) //if book issued
			{
				while (fp1.read((char*)&bk, sizeof(Book)) && flag == 0)
				{
					if (strcmp(bk.returnBookNumber(), st.returnStudentBookNumber()) == 0)
					{
						flag = 1;
						bk.displayBook();
						cout << "\n\nBook Deposited In No. Of Days: ";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine = " << fine;
						}
						st.resetStudentBooks();
						int pos = -1 * (long)sizeof(st);
						fp.seekg(pos, ios::cur);
						fp.write((char*)&st, sizeof(Student));
						cout << "\n\n\tBook Deposited Successfully";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exist";
				}
			}
			else
			{
				cout << "No Book Issued";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Found...";
	}
	fp.close();
	fp1.close();
	system("pause");
}

void start()
{
	system("cls");
	cout << "\n\tLIBRARY MANAGEMENT SYSTEM";
	system("pause");
}

void adminmenu()
{
	system("cls");
	int ch2;
	cout << "\n\tADMINISTRATOR MENU";
	cout << "\n\t1. CREATE STUDENT RECORD";
	cout << "\n\t2. DISPLAY ALL STUDENT RECORD";
	cout << "\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
	cout << "\n\t4. MODIFY STUDENT RECORD";
	cout << "\n\t5. DELETE STUDENT RECORD";
	cout << "\n\t6. CREATE BOOK";
	cout << "\nt7. DISPLAY SPECIFIC BOOK";
	cout << "\n\t8. MODIFY BOOK RECORD";
	cout << "\n\t9. DELETE BOOK RECORD";
	cout << "\n\t10. BACK TO MAIN MENU";
	cout << "\n\tPLEASE ENTER YOUR CHOICE(1-10): ";
	cin >> ch2;
	switch (ch2)
	{
	case 1:
		writeStudent();
		break;
	case 2:
		displayAllStudents();
		break;
	case 3:
		char num[6];
		system("cls");
		cout << "\n\n\t Please enter admission no.: ";
		cin >> num;
		showStudent(num);
		break;
	case 4:
		EditStudentRecord();
		break;
	case 5:
		deleteStudent();
		break;
	case 6:
		writeBook();
		break;
	case 7:
	{
		char num[6];
		system("cls");
		cout << "\n\n\tPlease enter book no.: ";
		cin >> num;
		showBook(num);
		break;
	}
	case 8:
		editBook();
		break;
	case 9:
		deletebook();
		break;
	case 10:
		return;
	default:
		cout << "Invalid choice";
	}
	system("pause");
	adminmenu();
}

int main()
{
	char ch;
	system("cls");
	start();
	do
	{
		system("cls");
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\n\t1. BOOK ISSUE";
		cout << "\n\n\n\t2. BOOK DEPOSIT";
		cout << "\n\n\n\t3. ADMINISTRATOR MENU";
		cout << "\n\n\n\t4. EXIT";
		cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4): ";
		ch = getchar();

		switch (ch)
		{
		case '1':
			bookissue();
			break;
		case '2':
			bookdeposit();
			break;
		case '3':
			adminmenu();
			break;
		case '4':
			exit(0);
			break;
		default:
			cout << "INVALID CHOICE";
		}
	} while (ch != '4');
	return 0;
}
