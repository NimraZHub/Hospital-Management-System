#include <iostream>
using namespace std;
class Doctor
{
public:
    int id;
    string name;
    string specialization;
    bool availability;
    Doctor* prev;
    Doctor* next;

    Doctor(int id, string name, string specialization, bool availability)
        : id(id), name(name), specialization(specialization), availability(availability), prev(nullptr), next(nullptr)
    {

    }

    void display()
    {
        cout<<"ID: "<<id<<", Name: "<<name<<", Specialization: "<<specialization<<", Availability: "<<(availability ? "Yes" : "No")<<endl;
    }
};

class DoctorManager
{
    Doctor* head;
    Doctor* tail;

public:
    DoctorManager() : head(nullptr), tail(nullptr)
    {

    }

    // Add doctor sorted by ID, check duplicates
    void addDoctor(int id, const string& name, const string& specialization, bool availability)
    {
        if(searchDoctorById(id) != nullptr)
        {
            cout<<"Error: Doctor with ID "<<id<<" already exists."<<endl;
            return;
        }
        Doctor* newDoctor = new Doctor(id, name, specialization, availability);
        if (!head) //1st doctor
        {
            head = tail = newDoctor;
            cout<<"Doctor added successfully."<<endl;
            return;
        }

        if (id < head->id)
        {
            newDoctor->next = head;
            head->prev = newDoctor;
            head = newDoctor;
            cout<<"Doctor added successfully."<<endl;
            return;
        }

        Doctor* current = head;
        while(current->next != nullptr && current->next->id < id)
        {
            current = current->next;
        }

        newDoctor->next = current->next;
        newDoctor->prev = current;

        if (current->next != nullptr)
        {
            current->next->prev = newDoctor;
        }
        else
        {
            tail = newDoctor;
        }

        current->next = newDoctor;
        cout<<"Doctor added successfully."<<endl;;
    }

    // Print all doctors
    void viewDoctors()
    {
        if (!head)
        {
            cout<<"No doctors available."<<endl;
            return;
        }

        Doctor* temp = head;
        cout<<"---------Doctors in the Hospital-----------"<<endl;
        while(temp)
        {
            temp->display();
            temp = temp->next;
        }
        cout<<"-------------------------------------------------"<<endl;
    }

    // Search doctor by ID
    Doctor* searchDoctorById(int id)
    {
        Doctor* temp = head;
        while(temp)
        {
            if(temp->id == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Update doctor info with validation
    void updateDoctorInfo(int id)
    {
        Doctor* doc = searchDoctorById(id);
        if (!doc)
        {
            cout<<"Error: Doctor not found."<<endl;
            return;
        }

        cout<<"Updating Doctor ID "<<id<<endl;
        string newName;
        cout<<"Enter new name (current: "<< doc->name << "): ";
        getline(cin, newName);
        if(!newName.empty())
        {
            doc->name = newName;
        }
        string newSpec;
        cout<<"Enter new specialization (current: "<<doc->specialization<<"): ";
        getline(cin, newSpec);
        if(!newSpec.empty())
        {
            doc->specialization = newSpec;
        }
        int avail;
        cout<<"Enter availability (1 = Yes, 0 = No) (current: "<<(doc->availability ? "Yes" : "No")<<"): ";
        while(!(cin>>avail) || (avail != 0 && avail != 1))
        {
            cout<<"Invalid input! Enter 1 for Yes or 0 for No: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); // consume leftover newline
        if (avail == 1)
        {
            doc->availability = true;
        }
        else
        {
            doc->availability = false;
        }
        cout<<"Doctor updated successfully."<<endl;
    }

    // Delete doctor by ID
    void deleteDoctor(int id)
    {
        Doctor* temp = head;
        while(temp && temp->id != id)
        {
            temp = temp->next;
        }

        if(!temp)
        {
            cout << "Error: Doctor not found.\n";
            return;
        }

        if(temp == head && temp == tail)   // only one node
        {
            head = tail = nullptr;
        }
        else if(temp == head) //Del from start
        {
            head = head->next;
            if(head)
            {
                head->prev = nullptr;
            }
        }
        else if(temp == tail) //Del from end
        {
            tail = tail->prev;
            if(tail)
            {
                tail->next = nullptr;
            }
        }
        else //Random
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout<<"Doctor deleted successfully."<<endl;
    }

    // Show all available doctors
    void viewAvailableDoctors()
    {
        if(!head)
        {
            cout<<"No doctors available."<<endl;
            return;
        }
        bool found = false;
        Doctor* temp = head;
        cout<<"--- Available Doctors ---"<<endl;
        while (temp)
        {
            if(temp->availability)
            {
                temp->display();
                found = true;
            }
            temp = temp->next;
        }
        if(!found)
        {
            cout<<"No available doctors found."<<endl;
        }
        cout<<"-------------------------"<<endl;
    }

    // Show all unavailable doctors
    void viewUnavailableDoctors()
    {
        if (!head)
        {
            cout<<"No doctors available.\n";
            return;
        }
        bool found = false;
        Doctor* temp = head;
        cout<<"--- Unavailable Doctors ---\n";
        while(temp)
        {
            if(!temp->availability)
            {
                temp->display();
                found = true;
            }
            temp = temp->next;
        }
        if(!found)
        {
            cout << "No unavailable doctors found.\n";
        }
        cout << "---------------------------\n";
    }

    ~DoctorManager()
    {
        Doctor* temp = head;
        while(temp)
        {
            Doctor* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

class Patient
{
public:
    int id;
    string name;
    int age;
    string gender;
    string disease;
    bool isAdmitted;
    Patient* prev;
    Patient* next;

    Patient(int id, string name, int age, string gender, string disease, bool isAdmitted)
        : id(id), name(name), age(age), gender(gender), disease(disease), isAdmitted(isAdmitted), prev(nullptr), next(nullptr)
    {

    }

    void display()
    {
        cout<<"ID: "<<id<<", Name: "<<name<<", Age: "<<age<<", Gender: "<<gender<<", Disease: "<<disease<<", Admitted: "<<(isAdmitted ? "Yes" : "No")<<endl;
    }
};


class PatientManager
{
    Patient* head;
    Patient* tail;

public:
    PatientManager() : head(nullptr), tail(nullptr)
    {

    }

    // Add patient sorted by ID, check duplicates
    void addPatient(int id, const string& name, int age, const string& gender, const string& disease, bool isAdmitted)
    {
        if(searchPatientById(id) != nullptr)
        {
            cout<<"Error: Patient with ID "<<id<<" already exists."<<endl;
            return;
        }
        Patient* newPatient = new Patient(id, name, age, gender, disease, isAdmitted);
        if (!head) //1st patient
        {
            head = tail = newPatient;
            cout<<"Patient added successfully."<<endl;
            return;
        }

        if (id < head->id)
        {
            newPatient->next = head;
            head->prev = newPatient;
            head = newPatient;
            cout<<"Patient added successfully."<<endl;
            return;
        }

        Patient* current = head;
        while(current->next != nullptr && current->next->id < id)
        {
            current = current->next;
        }

        newPatient->next = current->next;
        newPatient->prev = current;

        if (current->next != nullptr)
        {
            current->next->prev = newPatient;
        }
        else
        {
            tail = newPatient;
        }

        current->next = newPatient;
        cout<<"Patient added successfully."<<endl;
    }

    // Print all patients
    void viewPatients()
    {
        if (!head)
        {
            cout<<"No patients available."<<endl;
            return;
        }

        Patient* temp = head;
        cout<<"---------Patients in the Hospital-----------"<<endl;
        while(temp)
        {
            temp->display();
            temp = temp->next;
        }
        cout<<"-------------------------------------------------"<<endl;
    }

    // Search patient by ID
    Patient* searchPatientById(int id)
    {
        Patient* temp = head;
        while(temp)
        {
            if(temp->id == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Update patient info with validation
    void updatePatientInfo(int id)
    {
        Patient* pat = searchPatientById(id);
        if (!pat)
        {
            cout<<"Error: Patient not found."<<endl;
            return;
        }

        cout<<"Updating Patient ID "<<id<<endl;
        string newName;
        cout<<"Enter new name (current: "<< pat->name << "): ";
        getline(cin, newName);
        if(!newName.empty())
        {
            pat->name = newName;
        }
        string newGender;
        cout<<"Enter new gender (current: "<<pat->gender<<"): ";
        getline(cin, newGender);
        if(!newGender.empty())
        {
            pat->gender = newGender;
        }
        string newDisease;
        cout<<"Enter new disease (current: "<<pat->disease<<"): ";
        getline(cin, newDisease);
        if(!newDisease.empty())
        {
            pat->disease = newDisease;
        }
        int newAge;
        cout<<"Enter new age (current: "<<pat->age<<"): ";
        while(!(cin>>newAge) || newAge<=0)
        {
            cout<<"Invalid input! Enter positive integer for age: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        cin.ignore();
        pat->age = newAge;
        int admit;
        cout<<"Is patient admitted? (1 = Yes, 0 = No) (current: "<<(pat->isAdmitted ? "Yes" : "No")<<"): ";
        while(!(cin>>admit) || (admit != 0 && admit != 1))
        {
            cout<<"Invalid input! Enter 1 for Yes or 0 for No: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();
        pat->isAdmitted = (admit == 1);
        cout<<"Patient updated successfully."<<endl;
    }

    // Delete patient (discharge) by ID
    void dischargePatient(int id)
    {
        Patient* temp = head;
        while(temp && temp->id != id)
        {
            temp = temp->next;
        }

        if(!temp)
        {
            cout << "Error: Patient not found."<<endl;
            return;
        }

        if(temp == head && temp == tail)   // only one node
        {
            head = tail = nullptr;
        }
        else if(temp == head) //Del from start
        {
            head = head->next;
            if(head)
            {
                head->prev = nullptr;
            }
        }
        else if(temp == tail) //Del from end
        {
            tail = tail->prev;
            if(tail)
            {
                tail->next = nullptr;
            }
        }
        else //Random
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout<<"Patient discharged successfully."<<endl;
    }

    void viewAdmittedPatients()
    {
        if(!head)
        {
            cout<<"No patients available."<<endl;
            return;
        }
        Patient* temp = head;
        bool found = false;
        cout<<"--- Admitted Patients ---"<<endl;
        while(temp)
        {
            if(temp->isAdmitted)
            {
                temp->display();
                found = true;
            }
            temp = temp->next;
        }
        if(!found)
        {
            cout<<"No admitted patients found."<<endl;
        }
        cout<<"-------------------------"<<endl;
    }

    ~PatientManager()
    {
        Patient* temp = head;
        while(temp)
        {
            Patient* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};


int main()
{
    PatientManager pm;
    int choice;

    do
    {
        cout << "\n--- Patient Management Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Update Patient Info\n";
        cout << "5. Discharge Patient\n";
        cout << "6. View Admitted Patients\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            int id, age;
            string name, gender, disease;
            int admittedInput;

            cout << "Enter Patient ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Patient Name: ";
            getline(cin, name);

            cout << "Enter Patient Age: ";
            while (!(cin >> age) || age <= 0)
            {
                cout << "Invalid input! Enter a positive age: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Enter Patient Gender: ";
            getline(cin, gender);

            cout << "Enter Disease: ";
            getline(cin, disease);

            cout << "Is Patient Admitted? (1 = Yes, 0 = No): ";
            while (!(cin >> admittedInput) || (admittedInput != 0 && admittedInput != 1))
            {
                cout << "Invalid input! Enter 1 for Yes or 0 for No: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            pm.addPatient(id, name, age, gender, disease, admittedInput == 1);
            break;
        }

        case 2:
            pm.viewPatients();
            break;

        case 3:
        {
            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            cin.ignore();
            Patient* found = pm.searchPatientById(id);
            if (found)
                found->display();
            else
                cout << "Patient with ID " << id << " not found.\n";
            break;
        }

        case 4:
        {
            int id;
            cout << "Enter Patient ID to update: ";
            cin >> id;
            cin.ignore();
            pm.updatePatientInfo(id);
            break;
        }

        case 5:
        {
            int id;
            cout << "Enter Patient ID to discharge: ";
            cin >> id;
            cin.ignore();
            pm.dischargePatient(id);
            break;
        }

        case 6:
            pm.viewAdmittedPatients();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
    while (choice != 7);

    return 0;
}


