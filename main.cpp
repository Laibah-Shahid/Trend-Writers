#include <iostream>
#include <limits>
#include<chrono>
#include<thread>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define MAX 100
using namespace std;

template<class DT>
struct node {
    DT title;
    DT data;
    node *next;
};

template<class DT>
class mainclass {
    node<DT> *ql_front = NULL;
    node<DT> *ql_rear = NULL;
    node<DT> *prev = NULL;
    int sa_size, sa_top;
    DT *sa_ptr;
    int qa_front, qa_rear, qa_size;
    unsigned capacity;
    DT *array;

public:
    mainclass(DT val = DT(), int s = 0, DT sl_val = DT(), DT ql_val = DT(), int size = 0) {

        size = s;
        sa_ptr = new DT[size];
        sa_top = -1;
        qa_front = -1;
        qa_rear = -1;
        qa_size = size;
        array = new DT[size];
    }

    // singly linked list
    //  a) Insert a node at head
    void S_InsertAtHead(mainclass *&head, DT val) {
        node<DT> *n = new node<DT>(val);

        if (head == NULL) {
            head = n;
        }

        n->next = head;
        head = n;
    }

    // b) Insert a node at tail/end/back
    void S_InsertAtTail(mainclass *&head, DT val) {
        node<DT> *n = new node<DT>(val);

        if (head == NULL) {
            head = n;
            return;
        }

        node<DT> *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = n;
    }

    // c) Insert a node at any position
    void S_InsertAtPos(mainclass *&head, int pos, DT val) {
        node<DT> *n = new node<DT>(val);
        node<DT> *current = head;

        for (int i = 1; i < pos - 1; i++) {
            if (current == NULL) {
                cout << "Position out of bounds." << endl;
                return;
            }
            current = current->next;
        }

        n->next = current->next;
        current->next = n;
    }

    // e) Delete head
    void S_DeleteAtHead(node<DT> *&head) {
        node<DT> *todelete = head;
        head = head->next;

        delete todelete;
    }

    // d) Delete a node by value
    void S_DelByValue(node<DT> *&head, DT val) {
        if (head == NULL) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->data == val) {
            DeleteAtHead(head);
        }

        node<DT> *temp = head;

        while (temp->next != NULL && temp->next->data != val) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            cout << "Value not found in the list." << endl;
            return;
        } else {
            node<DT> *todelete = temp->next;
            temp->next = temp->next->next;
            delete todelete;
        }
    }

    // f) Delete tail
    void S_DeleteAtTail(node<DT> *&head) {
        if (head == NULL) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }
        node<DT> *todelete = head;
        while (todelete->next->next != NULL) {
            todelete = todelete->next;
        }

        delete todelete->next;
        todelete->next = NULL;
    }

    // g) Delete a node at any position.
    void S_DeleteByPos(node<DT> *&head, DT pos) {
        if (pos <= 0) {
            cout << "Invalid position." << endl;
            return;
        }

        if (pos == 1) {
            DeleteAtHead(head);
            return;
        }

        node<DT> *current = head;
        int count = 1;

        while (count < pos - 1 && current != NULL) {
            current = current->next;
            count++;
        }

        if (current == NULL || current->next == NULL) {
            cout << "Position out of bounds." << endl;
            return;
        }

        node<DT> *todelete = current->next;
        current->next = current->next->next;
        delete todelete;
    }

    // doubly linked list

    void D_insert_at_beg(node<DT> *&head, DT newdata) {
        node<DT> *new_node = new node<DT>(newdata);
        new_node->data = newdata;
        new_node->prev = NULL;
        new_node->next = head;
        if (head != NULL) {
            head->prev = new_node;
        }
        head = new_node;
    }

    void D_insert_at_end(node<DT> *&head, DT newdata) {
        node<DT> *new_node = new node<DT>(newdata);
        node<DT> *temp = head;
        if (head == NULL) {
            insert_at_beg(newdata);
            return;
        }
        while (temp->next != NULL) {
            temp = temp->next;
            // 	cout<<temp->data<<endl;
        }
        new_node->data = newdata;
        new_node->prev = temp;
        temp->next = new_node;
    }

    void D_insert_at_position(node<DT> *&head, DT newdata, int pos) {
        node<DT> *new_node = new node<DT>(newdata);
        node<DT> *temp = head;
        new_node->data = newdata;
        if (pos == 1) {
            insert_at_beg(newdata);
        } else {
            for (int i = 1; i < pos - 1; i++) {
                if (temp == NULL) {
                    cout << "Position out of bound" << endl;
                }
                temp = temp->next;
            }
            new_node->next = temp->next;
            temp->next = new_node;
            new_node->prev = temp;
        }
    }

    void D_delete_by_value(node<DT> &head, DT value) {
        node<DT> *temp = head;
        node<DT> *deleteitem;
        while (temp->next != NULL) {
            if (temp->data == value) {
                if (temp->prev == NULL) {
                    temp->next->prev = NULL;
                    deleteitem = temp;
                    delete deleteitem;
                    return;
                }
                if (temp->next == NULL) {
                    temp->prev->next = NULL;
                    deleteitem = temp;
                    delete deleteitem;
                    return;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                deleteitem = temp;
                delete temp;
                break;
            }
            temp = temp->next;
        }
        if (temp->data != value && temp->next == NULL) {
            cout << "Value not found in linked list" << endl;
        }
    }

    void D_delete_by_position(node<DT> &head, int pos) {
        node<DT> *deleteitem;
        node<DT> *temp = head;
        if (pos == 1) {
            deleteitem = temp;
            temp->next->prev = NULL;
            head = head->next;
            delete deleteitem;
            return;
        }
        for (int i = 1; i <= pos - 1; i++) {
            temp = temp->next;
            if (temp == NULL) {
                cout << "Position out of bounds" << endl;
                return;
            }
            if (temp->next == NULL) {
                temp->prev->next = NULL;
                deleteitem = temp;
                delete deleteitem;
                return;
            }
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        deleteitem = temp;
        delete deleteitem;
        return;
    }

    void D_display(node<DT> &head) {
        node<DT> *ptr = head;
        while (ptr != NULL) {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
            if (ptr == NULL) {
                cout << "NULL" << endl;
                break;
            }
            if (ptr->next == NULL) {
                cout << ptr->data << " -> NULL" << endl;
                break;
            }
        }
    }

    //	is empty function for stack array
    bool sa_isempty() {
        return sa_top == -1;
    }

    //	is full function for stack array
    bool sa_isfull() {
        return sa_top == sa_size - 1;
    }

    //	puch function for stack array
    void sa_push(DT ch) {
        if (sa_isfull()) {
            cout << "Error: Stack is full" << endl;
            return;
        }
        sa_top++;
        sa_ptr[sa_top] = ch;
    }

    //	pop function for stack array
    DT sa_pop() {
        if (sa_isempty()) {
            cout << "Error: Stack is empty" << endl;
        }
        return sa_ptr[sa_top--];
    }

    //	insert function for stack(linked list)
    node<DT> *sl_insert(node<DT> *sl_head, DT val) {
        node<DT> *n = new node<DT>;
        n->data = val;
        if (sl_head == NULL) {
            sl_head = n;
            n->next = NULL;
        } else {
            n->next = sl_head;
            sl_head = n;
        }
        return sl_head;
    }

    //   delete function for stack(linked list)
    node<DT> *sl_delete(node<DT> *&sl_head) {
        if (sl_head == NULL) {
            cout << "List is empty." << endl;
            return 0;
        }
        if (sl_head->sl_next == NULL) {
            delete sl_head;
            sl_head = NULL;
            return 0;
        }
        node<DT> *todelete = sl_head;
        while (todelete->sl_next->sl_next != NULL) {
            todelete = todelete->sl_next;
        }
        delete todelete->sl_next;
        todelete->sl_next = NULL;
        return sl_head;
    }

    void sl_display(node<DT> *&head) {
        node<DT> *temp = head;
        if (temp->next == NULL) {
            cout << temp->data << endl;
            cout << endl;
            return;
        } else {
            while (temp != NULL) {
                cout << temp->data << endl;
                cout << endl;
                temp = temp->next;
            }
        }
    }

    void traversing(const string &filename, const string &newContent) {
        // Read existing content from the file
        ifstream inputFile(filename);
        stringstream existingContentStream;
        existingContentStream << inputFile.rdbuf();
        inputFile.close();

        // Convert existing content to a string
        string existingContent = existingContentStream.str();

        // Check if 'data' is present in the existing content
        if (existingContent.find(newContent) == string::npos) {
            // Open the file in write mode with the trunc flag
            ofstream outputFile(filename, ios::trunc);

            if (!outputFile.is_open()) {
                cout << "Error occurred in opening file" << endl;
                return;
            }

            // Write the new content to the file
            outputFile << newContent << endl;

            // Write back the existing content
            outputFile << existingContent;
            outputFile.flush();
            outputFile.close();
        } else {
//            cout << "The data is already present in the existing content." << endl;
            return;
        }
    }

    //   is empty for queue array
    bool qa_isEmpty() {
        if (qa_front == -1) {
            return true;
        } else {
            return false;
        }
    }

    //   is full for queue array
    bool qa_isFull() {
        return (qa_front == 0 && qa_rear == qa_size - 1);
    }

    //   get size for queue array
    int qa_getsize() {
        if (qa_isEmpty()) {
            return false;
        } else {
            return qa_rear - qa_front + 1;
        }
    }

    //  insert for queue array
    void qa_insert(DT j) {
        if (qa_isFull()) {
            cout << "queue is overflow";
        } else {
            if (qa_front == -1) {
                qa_front = 0;
            }
            qa_rear++;
            array[qa_rear] = j;
        }
    }

    //	delete for queue array
    DT qa_remove() {
        DT val;
        if (qa_isEmpty()) {
            cout << "queue is underflow";
        } else {
            val = array[qa_front];
            if (qa_front > qa_rear) {
                qa_front = -1;
                qa_rear = -1;
            } else {
                qa_front++;
            }
            return val;
        }
    }

    //   peek for queue array
    int qa_peek() { // equivalent to accessing first element
        if (qa_isEmpty()) {
            cout << "queue is empty";
        } else {
            return array[qa_front];
        }
    }

    //    is empty for queue(linked list)
    bool ql_isempty() {
        return (ql_front == NULL && ql_rear == NULL);
    }

    //	insert for queue(linked list)
    void ql_insert(node<DT> *head, DT newdata) {
        node<DT> *new_node = new node<DT>(newdata);
        new_node->data = newdata;
        if (ql_front == NULL) {
            ql_rear = new_node;
            ql_front = ql_rear;
            new_node->next = NULL;
        } else {
            node<DT> *temp = ql_front;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = NULL;
        }
    }

    //   delete for queue(linked list)
    int ql_delete() {
        node<DT> *new_node = new node<DT>();
        node<DT> *temp = ql_front;
        node<DT> *todelete = temp;
        int val = temp->data;
        ql_front = ql_front->next;
        delete todelete;
        return val;
    }

    ~mainclass() {
        delete[] sa_ptr;
    }
};

string arrtitle[200], arrname[200];
string usersignin[300], passward[300];
string userid;
int commentcount[10];
int i = 0, j = 0, k = 0, l = 0;
node<string> *user[200] = {NULL};

template<class DT>
class blog : public mainclass<DT> {
    node<DT> *personalhead = NULL;
    node<DT> *travelhead = NULL;
    node<DT> *foodhead = NULL;
    node<DT> *lifestylehead = NULL;
    node<DT> *techhead = NULL;
    node<DT> *fitnesshead = NULL;
    node<DT> *parentinghead = NULL;
    node<DT> *productivityhead = NULL;
    node<DT> *currentuser = NULL;
    blog *next;
    string title, content, theme, userid;
    vector<string> comments; // Vector to store comments
    vector<string> titles;
    string reqThemes[10] = {"PERSONAL", "TRAVEL", "FOOD", "LIFESTYLE", "TECH", "FITNESS", "PARENTING", "PRODUCTIVITY"};
public:

    blog(string t = "", string con = "", string th = "", string ud = "", string name = "", string pass = "") : title(t),
                                                                                                               content(con),
                                                                                                               theme(th),
                                                                                                               userid(ud) {}

    bool boolpassword(string &pass) {
        bool alphanumeric = false;
        bool specialcha = false;
        for (size_t i = 0; i < pass.size(); ++i) {
            char c = pass[i];
            if (isalnum(c)) {
                alphanumeric = true;
            } else if (!isspace(c)) {
                specialcha = true;
            }
        }
        return alphanumeric && specialcha;
    }


    void Add_to_file(string name, string pass) {
        ofstream writeID("all_users.txt", ios::app);
        if (writeID.is_open()) {
            writeID << name << endl;
            writeID << pass << endl;
            writeID.close();
            cout << "Data Saved to file" << endl;
        } else {
            cout << "Unable to open all_users.txt for writing" << endl;
        }
    }

    bool isUsernameTaken(const string &username) {
        ifstream read_file("all_users.txt");
        string line;
        if (read_file.is_open()) {
            while (std::getline(read_file, line)) {
                std::stringstream ss(line);
                std::string word;

                // Break the line into words separated by space
                while (ss >> word) {
                    if (word == username) {
                        return true;
                    }

                }
            }
            read_file.close();
        }

        return false;
    }

    bool isValidEmail(const string &email) {

        size_t atrate = email.find('@');
        size_t dot = email.find('.');

        if (atrate == string::npos || dot == string::npos) {
            return false;
        }

        // Check if '@' comes before '.'
        if (atrate > dot) {
            return false;
        }

        // Check if '@' is not the first or last character
        if (atrate == 0 || atrate == email.length() - 1) {
            return false;
        }

        // Check if '.' is not the last character
        if (dot == email.length() - 1) {
            return false;
        }

        return true;
    }

    void signin() {
        system("cls");
        string nameoremail, pass;
        int ch;
        while (true) {
            cout << endl;
            cout << " SIGN UP " << endl;
            cout << "1.Name\n2.Email" << endl;
            cout << "Select from the given Options (1-2): ";
            cin >> ch;

            if (cin.fail() || (ch != 1 && ch != 2)) {
                cout << "Invalid input. Please enter 1 or 2." << endl;
                cin.clear(); // clear input buffer
                while (cin.get() != '\n'); // discard invalid input until newline
            } else {
                break; // Break the loop if input is valid
            }
        }
        bool cont = false;
        if (ch == 1) {
            while (!cont) {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, nameoremail);
                if (isUsernameTaken(nameoremail)) {
                    cout << "Username (email) is already taken. Please choose a different one." << endl;
                    cont = false;
                } else {
                    cont = true;
                }
            }
        }
        if (ch == 2) {
            bool valid_mail = false;
            while (valid_mail != true) {
                cout << "Enter your email: ";
                cin.ignore();
                getline(cin, nameoremail);
                if (isUsernameTaken(nameoremail)) {
                    cout << "Username (email) is already taken. Please choose a different one." << endl;
                    return;
                }
                if (isValidEmail(nameoremail) && !isUsernameTaken(nameoremail)) {
                    cout << "Valid email address." << endl;
                    valid_mail = true;
                } else {
                    cout << "Invalid email address." << endl;
                }
            }
        }
        cont = false;
        while (!cont) {
            cout
                    << "enter password(PASSWORD SHOULD BE OF LENGTH '5' AND SHOULD CONTAIN ALPHA-NUMERIC AND SOME CHARACTER)"
                    << endl;
            getline(cin, pass);
            if (!boolpassword(pass)) {
                cout << "Invalid password.Please try again" << endl;
            }
            if (pass.length() != 5) {
                cout << "Passward should be of length '5'." << endl;
            } else if (boolpassword(pass) && pass.length() == 5) {
                cout << "Sign-up successfully" << endl;
                cont = true;
            }
        }
        Add_to_file(nameoremail, pass);
        usersignin[l] = nameoremail;
        passward[l] = pass;
        l++;
        userid = nameoremail;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        system("cls");

    }

    bool login() {
        string nameoremail, pass;
        bool check = false;
        cout << endl;
        cout << " LOG IN" << endl;
        cout << "Welcome to our blog" << endl;
        cout << "Log in to see more" << endl;
        while (!check) {
            int ch;
            while (true) {
                cout << "1.Name\n2.Email" << endl;
                cout << "Select from the given Options (1-2): ";
                cin >> ch;

                if (cin.fail() || (ch != 1 && ch != 2)) {
                    cout << "Invalid input. Please enter 1 or 2." << endl;
                    cin.clear(); // clear input buffer
                    while (cin.get() != '\n'); // discard invalid input until newline
                } else {
                    break; // Break the loop if input is valid
                }
            }
            if (ch == 1) {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, nameoremail);
            } else if (ch == 2) {
                bool valid_mail = false;
                while (valid_mail != true) {
                    cout << "Enter your email: ";
                    cin.ignore();
                    getline(cin, nameoremail);

                    if (isValidEmail(nameoremail)) {
                        cout << "Valid email address." << endl;
                        valid_mail = true;
                    } else {
                        cout << "Invalid email address." << endl;
                    }
                }
            }

            cout << "Enter password (PASSWORD SHOULD CONTAIN ALPHA-NUMERIC AND SOME CHARACTER)" << endl;
            getline(cin, pass);
            ifstream read("all_users.txt");
            string user_name, user_password, line;
            if (read.is_open()) {
                cout << "Verifying details in the system\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                int count = 1;
                while (getline(read, line)) {
                    if (count % 2 != 0) {
                        user_name = line;
                    }
                    if (count % 2 == 0) {
                        user_password = line;
                    }
                    if (nameoremail == user_name && pass == user_password) {
                        cout << "Welcome back " << user_name << endl;
                        check = true;
                        userid = nameoremail;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");

                    }
                    count++;

                }
                if (check == true) {
                    return true;
                } else {
                    int count = 0;
                    bool cont = false;
                    cout << "No account exist for this email and password . Enter correct email and password." << endl;
                    while (!cont) {
                        cout << "Press (1) to continue with login and (2) to go to signup page";
                        cin >> count;
                        if (cin.fail() || (count != 1 && count != 2)) {
                            cout << "Invalid input. Please enter 1 or 2." << endl;
                            cin.clear(); // clear input buffer
                            while (cin.get() != '\n'); // discard invalid input until newline
                            cont = false;
                        } else {
                            if (count == 1) {
                                login();
                            } else if (count == 2) {
                                signin();
                            }
                            cont = true;
                            return 0;
                        }

                    }
                }
            }

        }
    }


    bool approvecontent(string content, string title) {
        node<DT> *currentHead;

        title = "TITLE: " + title;
        content = "CONTENT: " + content;

        string line;
        ifstream read_file1("PersonalBlogs.txt");
        ifstream read_file2("TravelBlogs.txt");
        ifstream read_file3("FoodBlogs.txt");
        ifstream read_file4("LifestyleBlogs.txt");
        ifstream read_file5("TechBlogs.txt");
        ifstream read_file6("FitnessBlogs.txt");
        ifstream read_file7("ParentingBlogs.txt");
        ifstream read_file8("ProductivityBlogs.txt");
        bool check=false;
        ifstream *files[] = {&read_file1, &read_file2, &read_file3, &read_file4, &read_file5,
                             &read_file6, &read_file7, &read_file8};

        for (int i = 0; i < 8; ++i) {
            while (getline(*files[i], line)) {
                // Compare content and title with the input
                if (line == content || line == title) {
                    check=true;
                    return false;
                }
            }
            files[i]->close();
        }
        while (currentHead != NULL) {
            if (currentHead->data == content || currentHead->title == title) {
                check=true;
                return false;
            }
            currentHead = currentHead->next;
        }

        return true;
    }


    void previousblogs(string theme, string title, string briefcontent) {

        string blogpost =
                "TITLE: " + title + '\n' + "AUTHOR: " + userid + '\n' + "THEME: " + theme + '\n' + "CONTENT: " +
                briefcontent + "\n";

        theme = "THEME: " + theme;
        char themes[10][MAX] = {"PERSONAL", "TRAVEL", "FOOD", "LIFESTYLE", "TECH", "FITNESS", "PARENTING",
                                "PRODUCTIVITY"};
        if (theme == "THEME: PERSONAL") {
            personalhead = this->sl_insert(personalhead, blogpost);
            this->traversing("PersonalBlogs.txt", blogpost);
        }
        if (theme == "THEME: TRAVEL") {
            travelhead = this->sl_insert(travelhead, blogpost);
            this->traversing("TravelBlogs.txt", blogpost);
        }
        if (theme == "THEME: FOOD") {
            foodhead = this->sl_insert(foodhead, blogpost);
            this->traversing("FoodBlogs.txt", blogpost);
        }
        if (theme == "THEME: LIFESTYLE") {
            lifestylehead = this->sl_insert(lifestylehead, blogpost);
            this->traversing("LifestyleBlogs.txt", blogpost);
        }
        if (theme == "THEME: TECH" || theme == "THEME: TECHNICAL") {
            techhead = this->sl_insert(techhead, blogpost);
            this->traversing("TechBlogs.txt", blogpost);
        }
        if (theme == "THEME: FITNESS") {
            fitnesshead = this->sl_insert(fitnesshead, blogpost);
            this->traversing("FitnessBlogs.txt", blogpost);
        }
        if (theme == "THEME: PARENTING") {
            parentinghead = this->sl_insert(parentinghead, blogpost);
            this->traversing("ParentingBlogs.txt", blogpost);
        }
        if (theme == "THEME: PRODUCTIVITY") {
            productivityhead = this->sl_insert(productivityhead, blogpost);
            this->traversing("ProductivityBlogs.txt", blogpost);
        }
        this->traversing("PreviousBlogs.txt", blogpost);
        for (int j = 0; j < title.length(); j++) {
            title[j] = toupper(title[j]);
        }

        arrname[i] = userid;
        i++;

    }

    void display_prev_blogs() {
        string read_file1 = "PersonalBlogs.txt";
        string read_file2 = "TravelBlogs.txt";
        string read_file3 = "FoodBlogs.txt";
        string read_file4 = "LifestyleBlogs.txt";
        string read_file5 = "TechBlogs.txt";
        string read_file6 = "FitnessBlogs.txt";
        string read_file7 = "ParentingBlogs.txt";
        string read_file8 = "ProductivityBlogs.txt";
        int count = 1;
        string filename;
        while (count <= 8) {
            switch (count) {
                case 1: {
                    cout << "\nPERSONAL BLOGS:\n" << endl;
                    filename = "PersonalBlogs.txt";
                    break;
                }
                case 2: {
                    cout << "\nTRAVEL BLOGS:\n" << endl;
                    filename = "TravelBlogs.txt";
                    break;
                }
                case 3: {
                    cout << "\nFOOD BLOGS:\n" << endl;
                    filename = "FoodBlogs.txt";
                    break;
                }
                case 4: {
                    cout << "\nLIFESTYLE BLOGS:\n" << endl;
                    filename = "LifestyleBlogs.txt";
                    break;
                }
                case 5: {
                    cout << "\nTECH BLOGS:\n" << endl;
                    filename = "TechBlogs.txt";
                    break;
                }
                case 6: {
                    cout << "\nFITNESS BLOGS:\n" << endl;
                    filename = "FitnessBlogs.txt";
                    break;
                }
                case 7: {
                    cout << "\nPARENTING BLOGS:\n" << endl;
                    filename = "ParentingBlogs.txt";
                    break;
                }
                case 8: {
                    cout << "\nPRODUCTIVITY BLOGS:\n" << endl;
                    filename = "ProductivityBlogs.txt";
                    break;
                }
            }
            bool cont = displayfile(filename);
            if(!cont){
                cout<<"No previous blogs available for these themes"<<endl;
            }
            count++;
            if(count==9){
                break;
            }
        }
    }


    bool displayfile(string filename) {
        ifstream read_file(filename);
        string line;
        if (read_file.is_open()) {
            while (getline(read_file, line)) {
                cout << line << endl;
            }
            read_file.close();
            return true;
        } else if (!read_file.is_open()) {
            return false;
        }

    }

    void searchByTheme() {
        bool check = false;
        cout << "Available themes: " << endl;
        cout << "PERSONAL | TRAVEL | FOOD | LIFESTYLE | TECH | FITNESS | PARENTING | PRODUCTIVITY" << endl;
        string theme;
        cout << "Enter the theme : ";
        cin >> theme;
        for (int i = 0; i < theme.length(); i++) {
            theme[i] = toupper(theme[i]);
        }
        theme = "THEME: " + theme;
        if (theme == "THEME: PERSONAL") {
            displayfile("PersonalBlogs.txt");
            check = true;

        }
        if (theme == "THEME: TRAVEL") {
            displayfile("TravelBlogs.txt");
            check = true;
        }
        if (theme == "THEME: FOOD") {
            displayfile("FoodBlogs.txt");
            check = true;
        }
        if (theme == "THEME: LIFESTYLE") {
            displayfile("LifestyleBlogs.txt");
            check = true;
        }
        if (theme == "THEME: TECH" || theme == "THEME: TECHNICAL") {
            displayfile("TechBlogs.txt");
            check = true;
        }
        if (theme == "THEME: FITNESS") {
            displayfile("FitnessBlogs.txt");
            check = true;
        }
        if (theme == "THEME: PARENTING") {
            displayfile("ParentingBlogs.txt");
            check = true;
        }
        if (theme == "THEME: PRODUCTIVITY") {
            displayfile("ProductivityBlogs.txt");
            check = true;
        } else if (!check) {
            cout << "Theme not available" << endl;
        }
    }

    void searchByTitle() {
        cout << endl;
        display_prev_blogs();
        cout << "\n\n" << endl;
        string entertitle;
        cout << "Enter the title of the blog you want to search: ";
        cin.ignore();
        getline(cin, entertitle);
        for (int i = 0; i < entertitle.length(); i++) {
            entertitle[i] = toupper(entertitle[i]);
        }
        cout << entertitle << endl;
        string title = "TITLE: " + entertitle;

        std::ifstream read_file1("PersonalBlogs.txt");
        std::ifstream read_file2("TravelBlogs.txt");
        std::ifstream read_file3("FoodBlogs.txt");
        std::ifstream read_file4("LifestyleBlogs.txt");
        std::ifstream read_file5("TechBlogs.txt");
        std::ifstream read_file6("FitnessBlogs.txt");
        std::ifstream read_file7("ParentingBlogs.txt");
        std::ifstream read_file8("ProductivityBlogs.txt");
        std::vector<std::string> lines;
        int count = 0;

        if (read_file1.is_open()) {
            std::string line;
            while (std::getline(read_file1, line)) {
                lines.push_back(line);
            }

            read_file1.close();
        }
        auto titleIt2 = std::find_if(lines.begin(), lines.end(),
                                     [title](const std::string &line) { return line.find(title) == 0; });

        if (titleIt2 == lines.end()) {

            if (read_file2.is_open()) {
                std::string line;
                while (std::getline(read_file2, line)) {
                    lines.push_back(line);
                }

                read_file2.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file3.is_open()) {
                std::string line;
                while (std::getline(read_file3, line)) {
                    lines.push_back(line);
                }

                read_file3.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file4.is_open()) {
                std::string line;
                while (std::getline(read_file4, line)) {
                    lines.push_back(line);
                }

                read_file4.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file5.is_open()) {
                std::string line;
                while (std::getline(read_file5, line)) {
                    lines.push_back(line);
                }

                read_file5.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file6.is_open()) {
                std::string line;
                while (std::getline(read_file6, line)) {
                    lines.push_back(line);
                }

                read_file6.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file7.is_open()) {
                std::string line;
                while (std::getline(read_file7, line)) {
                    lines.push_back(line);
                }

                read_file7.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            if (read_file8.is_open()) {
                std::string line;
                while (std::getline(read_file8, line)) {
                    lines.push_back(line);
                }

                read_file8.close();
            }
        }
        titleIt2 = std::find_if(lines.begin(), lines.end(),
                                [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines.end()) {
            std::cout << "Title not found" << std::endl;
            return;

        }
        // Find the iterator pointing to the next title
        auto nextTitleIt2 = std::find_if(std::next(titleIt2), lines.end(),
                                         [](const std::string &line) { return line.find("TITLE") == 0; });
        for (auto it = titleIt2; it != nextTitleIt2; ++it) {
            std::cout << *it << std::endl;
        }

    }

    void searchByauthor() {
        string author;
        bool found = false;
        cout << "Enter author name: ";
        cin >> author;

        for (int j = 0; j < i; j++) {
            if (author == arrname[j]) {
                found = true;
                return;
            }
        }
        string filename = author + "_file.txt";
        string line;
        ifstream read_file(filename);
        if (read_file.is_open()) {
            while (getline(read_file, line)) {
                cout << line << endl;
            }
        } else {
            if (!found) {
                cout << "The author name you entered does not exist" << endl;
            } else {
                cout << "Ãuthor has not created any posts yet" << endl;
            }
        }
    }

    bool displayUserRecords() {
        string id, line;
        string filename = blog::userid + "_file.txt";
        std::ifstream read_file(filename);
        if (read_file.is_open()) {
            if (read_file.is_open() && read_file.peek() == std::ifstream::traits_type::eof()) {
                // File is empty
                std::cout << "User does not have any previous records" << std::endl;
            }
            while (std::getline(read_file, line)) {
                cout << line << endl;
            }
            read_file.close();
            return true;
        } else {
            cout << "User does not have any previous records" << endl;
            return false;
        }


    }

    void userrecord(string title, string theme, string content) {
        string filename = userid + "_file.txt";
//        string author =  userid;
        string blogpost =
                "TITLE: " + title + '\n' + "AUTHOR: " + userid + '\n' + "THEME: " + theme + '\n' + "CONTENT: " +
                content + '\n';
        this->traversing(filename, blogpost);

    }

    void deletepost() {
        cout << "Displaying your previous blogs: " << endl;
        if (!displayUserRecords()) {
            return;
        }
        string entertitle;
        cout << "Enter the title of the blog to be deleted: ";

        getline(cin, entertitle);
        for (int i = 0; i < entertitle.length(); i++) {
            entertitle[i] = toupper(entertitle[i]);
        }

        cout << entertitle << endl;
        string title = "TITLE: " + entertitle;
        string filename = userid + "_file.txt";
        std::ifstream read_file(filename);
        std::ifstream read_file1("PersonalBlogs.txt");
        std::ifstream read_file2("TravelBlogs.txt");
        std::ifstream read_file3("FoodBlogs.txt");
        std::ifstream read_file4("LifestyleBlogs.txt");
        std::ifstream read_file5("TechBlogs.txt");
        std::ifstream read_file6("FitnessBlogs.txt");
        std::ifstream read_file7("ParentingBlogs.txt");
        std::ifstream read_file8("ProductivityBlogs.txt");
        std::vector<std::string> lines;
        std::vector<std::string> lines2;
        if (read_file.is_open()) {
            std::string line;
            while (std::getline(read_file, line)) {
                lines.push_back(line);
            }

            read_file.close();
        } else {
            std::cerr << "Error opening file " << endl;
            return;
        }
        auto titleIt = std::find_if(lines.begin(), lines.end(),
                                    [title](const std::string &line) { return line.find(title) == 0; });
        if (titleIt == lines.end()) {
            std::cout << "Title not found in the file." << std::endl;
            return;
        }
        auto nextlineIt = titleIt;
        std::advance(nextlineIt, 2); // Move two lines after the start title

        // Check if nextLineIt is still within the vector bounds
        if (nextlineIt != lines2.end()) {
        } else {
            std::cerr << "Error: nextLineIt is out of bounds." << std::endl;
            return;
        }

        std::transform(nextlineIt->begin(), nextlineIt->end(), nextlineIt->begin(), ::toupper);

        string theme = *nextlineIt;
        // Find the iterator pointing to the next title
        auto nextTitleIt = std::find_if(nextlineIt, lines.end(),
                                        [](const std::string &line) { return line.find("TITLE") == 0; });
        lines.erase(titleIt, nextTitleIt);
        std::ofstream modifiedfile(userid + "_file.txt",
                                   std::ofstream::trunc); // Open in trunc mode to remove existing content
        if (modifiedfile.is_open()) {
            for (const auto &line: lines) {
                modifiedfile << line << std::endl;
            }
            modifiedfile.close();
            std::cout << "Post with title '" << title << "' deleted successfully." << std::endl;
        } else {
            std::cerr << "Error opening file for writing: " << std::endl;
        }
        if (theme == "THEME: PERSONAL") {
            if (read_file1.is_open()) {
                std::string line;
                while (std::getline(read_file2, line)) {
                    lines2.push_back(line);
                }

                read_file1.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: TRAVEL") {
            if (read_file2.is_open()) {
                std::string line;
                while (std::getline(read_file2, line)) {
                    lines2.push_back(line);
                }

                read_file2.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: FOOD") {
            if (read_file3.is_open()) {
                std::string line;
                while (std::getline(read_file3, line)) {
                    lines2.push_back(line);
                }

                read_file3.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: LIFESTYLE") {
            if (read_file4.is_open()) {
                std::string line;
                while (std::getline(read_file4, line)) {
                    lines2.push_back(line);
                }

                read_file4.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: TECH" || theme == "THEME: TECHNICAL") {
            if (read_file5.is_open()) {
                std::string line;
                while (std::getline(read_file5, line)) {
                    lines2.push_back(line);
                }

                read_file5.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: FITNESS") {
            if (read_file6.is_open()) {
                std::string line;
                while (std::getline(read_file6, line)) {
                    lines2.push_back(line);
                }

                read_file6.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: PARENTING") {
            if (read_file7.is_open()) {
                std::string line;
                while (std::getline(read_file7, line)) {
                    lines2.push_back(line);
                }

                read_file7.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        if (theme == "THEME: PRODUCTIVITY") {
            if (read_file8.is_open()) {
                std::string line;
                while (std::getline(read_file8, line)) {
                    lines2.push_back(line);
                }

                read_file8.close();
            } else {
                std::cerr << "Error opening file " << endl;
                return;
            }
        }
        auto titleIt2 = std::find_if(lines2.begin(), lines2.end(),
                                     [title](const std::string &line) { return line.find(title) == 0; });
        // Check if the title was not found
        if (titleIt2 == lines2.end()) {
            std::cout << "Title not found in the file." << std::endl;
            return;
        }
        // Find the iterator pointing to the next title
        auto nextTitleIt2 = std::find_if(std::next(titleIt2), lines2.end(),
                                         [](const std::string &line) { return line.find("TITLE") == 0; });
        lines2.erase(titleIt2, nextTitleIt2);

        if (theme == "THEME: PERSONAL") {
            std::ofstream modifiedfile("PersonalBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {

                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: TRAVEL") {
            std::ofstream modifiedfile("TravelBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }

        if (theme == "THEME: FOOD") {
            std::ofstream modifiedfile("FoodBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: LIFESTYLE") {
            std::ofstream modifiedfile("LifestyleBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: TECH") {
            std::ofstream modifiedfile("TechBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: FITNESS") {
            std::ofstream modifiedfile("FitnessBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: PARENTING") {
            std::ofstream modifiedfile("ParentingBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }
        if (theme == "THEME: PRODUCITVITY") {
            std::ofstream modifiedfile("ProductivityBlogs.txt",
                                       std::ofstream::trunc); // Open in trunc mode to remove existing content
            if (modifiedfile.is_open()) {
                for (const auto &line: lines2) {
                    modifiedfile << line << std::endl;
                }
                modifiedfile.close();
            } else {
                std::cerr << "Error opening file for writing: " << std::endl;
            }
        }

    }


    bool createPost() {
        blog newPost("", "", "", "");
        cout << "Enter title: ";
        getline(std::cin, newPost.title);
        for (int i = 0; i < newPost.title.length(); i++) {
            newPost.title[i] = toupper(newPost.title[i]);
        }
        // Store the title in the vector
        titles.push_back(newPost.title);

        cout << "Select from the following themes:" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << reqThemes[i] << " | ";
        }
        cout << "\nEnter the theme: ";
        cin >> newPost.theme;
        for (int i = 0; i < newPost.theme.length(); i++) {
            newPost.theme[i] = toupper(newPost.theme[i]);
        }
        bool validTheme = false;
        for (int i = 0; i < 8; ++i) {
            if (newPost.theme == reqThemes[i]) {
                validTheme = true;
                break;
            }
        }

        if (!validTheme || cin.fail()) {
            cout << "Error! Please use themes from the following list: ";
            for (int i = 0; i < 8; ++i) {
                cout << reqThemes[i] << " ";
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter the theme: ";
            cin >> newPost.theme;
        }
        cout << "Enter the content: ";
        cin.ignore();
        getline(cin, newPost.content);
        for (int i = 0; i < newPost.content[i]; i++) {
            newPost.content[i] = tolower(newPost.content[i]);
        }
        title = newPost.title;
        theme = newPost.theme;
        content = newPost.content;
        if (approvecontent(content, title)) {
            previousblogs(theme, title, content);
            userrecord(title, theme, content);
            cout << endl;
            cout << "Checking your content" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Your content is approved" << endl;

        } else {
            cout << "Checking your content" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            cout << "Content not approved. Post creation canceled." << endl;

        }
//        previousblogs(theme, title, content);
//        userrecord(title, theme, content);

        return true;
        system("cls");
    }

    const string FILE_NAME = "feedback.txt";

    void saveFeedback(int rating, const string &suggestion, const string &userid) {
        ofstream outFile(FILE_NAME, ios::app);
        if (outFile.is_open()) {
            outFile << "Userid: " << userid << "\nRating: " << rating << "\nSuggestion: " << suggestion << "\n\n";
            outFile.close();
        } else {
            cout << "Unable to open the file for saving feedback." << endl;
        }
    }

    void showPreviousFeedback() {
        ifstream inFile(FILE_NAME);
        if (inFile.is_open()) {
            cout << "\nPrevious Feedback:\n";
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "No previous feedback." << endl;
        }
    }

    void rateAndSuggestion() {
        int userRating;
        string suggestion;

        cout << "PLEASE RATE OUR APPLICATION (between 1 to 5):" << endl;
        cout << "---------------------" << endl;

        while (true) {
            if (cin >> userRating && userRating >= 1 && userRating <= 5) {
                cout << "\nThank you for your rating :)\n" << endl;
                break;
            } else {
                cout << "Sorry! Please enter a valid rating between 1 to 5." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Give any suggestion if you want (yes/no): ";
        cin >> suggestion;

        if (suggestion == "yes") {
            cout << "\nPlease write your suggestion:" << endl;
            cin.ignore(); // Ignore newline character left in the buffer
            string userSuggestion;
            getline(cin, userSuggestion);
            saveFeedback(userRating, userSuggestion, userid);
            cout << "\nThank you for giving us your suggestion!!" << endl;
        } else if (suggestion == "no") {
            cout << "\nThank you for using and rating our app!!" << endl;
        } else {
            cout << "Invalid input. Exiting without saving feedback." << endl;
        }

        showPreviousFeedback();

    }
};

class titlepage {
    int top;
    int rating;
    blog<string> b;

public:
    titlepage() : top(-1) {
    }

    void welcome() {
        int ch;
        while (true) {
            cout << "1. Login\n2. Sign-up" << endl;
            cout << "Select from the given Options (1-2): ";
            cin >> ch;
            system("cls");
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if (cin.fail() || (ch != 1 && ch != 2)) {
                cout << "Invalid input. Please enter 1 or 2." << endl;
                cin.clear(); // clear input buffer
                while (cin.get() != '\n'); // discard invalid input until newline
            } else {
                break; // Break the loop if input is valid
            }
        }

        switch (ch) {
            case 1: {
                b.login();
                break;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");

            }
            case 2: {
                b.signin();
                break;
            }
        }
    }


    void display() {
        welcome();
        int choice;
        do {
            cout << "---------------------- WELCOME TO TrendWriters -----------------------    \n  " << endl;
            cout
                    << "1.New Blog          2.Search a Blog          3.View existing blog posts         4. View User Records\n"
                    << "5.Rate/Suggestions         6.Delete post           7.About                8.Exit      " << endl;
            cout << "Select from the given options: (1-8): ";
            cin >> choice;
            system("cls");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: {

                    b.createPost();
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");
                    break;
                }

                case 2: {
                    int ch;
//                    bool cont=false;
//                    int ch;
                    while (true) {
                        cout << "Search on basis of: " << endl;
                        cout << "1)Title\n2)Theme\n3)Author" << endl;
                        cout << "Enter your choice: ";
                        cin >> ch;
                        if (cin.fail() || (ch != 1 && ch != 2 && ch != 3)) {
                            cout << "Invalid input. Please enter 1 , 2 or 3." << endl;
                            cin.clear(); // clear input buffer
                            while (cin.get() != '\n'); // discard invalid input until newline
                        }
                        if (ch == 1 || ch == 2 || ch == 3) {
                            false;
                            break;
                        }
                    }
                    if (ch == 1) {
                        b.searchByTitle();
                    }
                    if (ch == 2) {
                        b.searchByTheme();
                    }
                    if (ch == 3) {
                        b.searchByauthor();
                    }
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");

                    break;
                }


                case 3: {
                    b.display_prev_blogs();
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");

                    break;
                }
                case 4: {
                    b.displayUserRecords();
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");

                    break;
                }
                case 5: {
                    b.rateAndSuggestion();
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");

                    break;
                }
                case 6: {
                    b.deletepost();
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");
                    break;
                }

                case 7: {
                    cout << "--------------------- ABOUT TrendWriters -----------------------    \n " << endl;
                    cout << "Welcome to TrendWriters \n"
                         << endl;
                    cout
                            << "This is simple blogging application which allows you to create,search and interact with blog post \n "
                            << endl;
                    cout << "Features :" << endl;
                    cout << "-Create a new blog post." << endl;
                    cout << "-Search for existing blog ." << endl;
                    cout << "-Suggest improvement for blog post." << endl;
                    cout << "-Rate and give suggestion for improvement in application." << endl;
                    cout << "-and many more" << endl;
                    cout << "Thank you for using our blog and happy blogging." << endl;
                    string key;
                    cout << "press any alphanumeric key to go homepage:" << endl;
                    cin >> key;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");
                    break;
                }

                case 8:
                    cout << "Exiting the application. Goodbye!" << endl;
                    break;

                default:
                    cout << "Invalid choice. Please select a valid option." << endl;
            }
        } while (choice != 8);
    }
};

int main() {
    titlepage coverpg;
    coverpg.display();

}