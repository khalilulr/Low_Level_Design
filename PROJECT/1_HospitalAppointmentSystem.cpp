#include <bits/stdc++.h>
using namespace std;

class Appointment;

// ==================== ROOM ====================

class Room {
private:
    int floorNumber;
    int roomNumber;

    vector<pair<int, int>> slots;

public:
    Room(int floorNumber, int roomNumber)
        : floorNumber(floorNumber),
          roomNumber(roomNumber) {}

    int getFloorNumber() {
        return floorNumber;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    string getRoomDetail() {
        return "Floor " + to_string(floorNumber) +
               ", Room " + to_string(roomNumber);
    }

    void addRoomSlot(int startTime, int endTime) {
        slots.push_back({startTime, endTime});
    }

    bool isRoomAvailable(int startTime, int endTime) {

        for (auto slot : slots) {

            if (startTime < slot.second &&
                endTime > slot.first) {

                return false;
            }
        }

        return true;
    }
};


// ==================== DOCTOR ====================

class Doctor {
private:
    int id;
    string name;
    string specialization;

    vector<Appointment*> appointments;

    vector<pair<int, int>> slots;

    int startTime;
    int endTime;

public:

    Doctor(
        int id,
        string name,
        string specialization,
        int startTime,
        int endTime
    )
        : id(id),
          name(name),
          specialization(specialization),
          startTime(startTime),
          endTime(endTime) {}

    int getDoctorId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getSpecialization() {
        return specialization;
    }

    vector<Appointment*> getAllAppointments() {
        return appointments;
    }

    void addAppointment(Appointment* appointment) {
        appointments.push_back(appointment);
    }

    void addDoctorSlot(int startTime, int endTime) {
        slots.push_back({startTime, endTime});
    }

    bool isDoctorAvailable(int startTime, int endTime) {

        // Doctor's working hours
        if (startTime < this->startTime) {
            return false;
        }

        if (endTime > this->endTime) {
            return false;
        }

        // Existing appointments
        for (auto slot : slots) {

            if (startTime < slot.second &&
                endTime > slot.first) {

                return false;
            }
        }

        return true;
    }
};


// ==================== PATIENT ====================

class Patient {
private:
    int id;
    string name;

    vector<Appointment*> appointments;

public:

    Patient(int id, string name)
        : id(id),
          name(name) {}

    int getPatientId() {
        return id;
    }

    string getName() {
        return name;
    }

    vector<Appointment*> getAllAppointments() {
        return appointments;
    }

    void addAppointment(Appointment* appointment) {
        appointments.push_back(appointment);
    }
};


// ==================== APPOINTMENT ====================

class Appointment {
private:
    int id;

    Doctor* doctor;
    Patient* patient;
    Room* room;

    int startTime;
    int endTime;

public:

    Appointment(
        int id,
        Doctor* doctor,
        Patient* patient,
        Room* room,
        int startTime,
        int endTime
    )
        : id(id),
          doctor(doctor),
          patient(patient),
          room(room),
          startTime(startTime),
          endTime(endTime) {}

    int getId() {
        return id;
    }

    Doctor* getDoctor() {
        return doctor;
    }

    Patient* getPatient() {
        return patient;
    }

    Room* getRoom() {
        return room;
    }

    int getStartTime() {
        return startTime;
    }

    int getEndTime() {
        return endTime;
    }

    void showDetails() {

        cout << "\nAppointment ID : "
             << id << endl;

        cout << "Doctor         : "
             << doctor->getName() << endl;

        cout << "Patient        : "
             << patient->getName() << endl;

        cout << "Specialization : "
             << doctor->getSpecialization()
             << endl;

        cout << "Room           : "
             << room->getRoomDetail()
             << endl;

        cout << "Time           : "
             << startTime << ":00 - "
             << endTime << ":00"
             << endl;
    }
};


// ==================== APPOINTMENT MANAGER ====================

class AppointmentManager {

private:

    vector<Appointment*> appointments;

    int appointmentCounter = 1;

    mutex mtx;

public:

    Appointment* createAppointment(
        Doctor* doctor,
        Patient* patient,
        Room* room,
        int startTime
    ) {

        // LOCK
        lock_guard<mutex> lock(mtx);

        int endTime = startTime + 1;

        // ----------------------------
        // Check doctor
        // ----------------------------

        if (!doctor->isDoctorAvailable(
                startTime,
                endTime
            )) {

            cout << "Doctor is not available at "
                 << startTime << ":00"
                 << endl;

            return nullptr;
        }


        // ----------------------------
        // Check room
        // ----------------------------

        if (!room->isRoomAvailable(
                startTime,
                endTime
            )) {

            cout << "Room is not available at "
                 << startTime << ":00"
                 << endl;

            return nullptr;
        }


        // ----------------------------
        // Create appointment
        // ----------------------------

        Appointment* appointment =
            new Appointment(
                appointmentCounter++,
                doctor,
                patient,
                room,
                startTime,
                endTime
            );


        // ----------------------------
        // Store appointment
        // ----------------------------

        appointments.push_back(appointment);


        // ----------------------------
        // Update Doctor
        // ----------------------------

        doctor->addAppointment(appointment);

        doctor->addDoctorSlot(
            startTime,
            endTime
        );


        // ----------------------------
        // Update Patient
        // ----------------------------

        patient->addAppointment(appointment);


        // ----------------------------
        // Update Room
        // ----------------------------

        room->addRoomSlot(
            startTime,
            endTime
        );


        cout << "Appointment created successfully!"
             << endl;

        return appointment;
    }


    void showAllAppointments() {

        cout << "\n========== ALL APPOINTMENTS =========="
             << endl;

        for (Appointment* appointment :
             appointments) {

            appointment->showDetails();
        }
    }
};


// ==================== MAIN ====================

int main() {

    // ----------------------------
    // Rooms
    // ----------------------------

    Room room1(1, 101);
    Room room2(1, 102);


    // ----------------------------
    // Doctors
    // Working hours: 9 AM - 5 PM
    // ----------------------------

    Doctor doctor1(
        1,
        "Dr. Ahmed",
        "Dentist",
        9,
        17
    );

    Doctor doctor2(
        2,
        "Dr. Sarah",
        "Cardiologist",
        9,
        17
    );


    // ----------------------------
    // Patients
    // ----------------------------

    Patient patient1(
        1,
        "Khalil"
    );

    Patient patient2(
        2,
        "Rahul"
    );

    Patient patient3(
        3,
        "Aman"
    );


    // ----------------------------
    // Appointment Manager
    // ----------------------------

    AppointmentManager manager;


    // =================================================
    // TEST 1
    // Doctor 1 + Room 1
    // 10 - 11
    // SUCCESS
    // =================================================

    cout << "\nTEST 1" << endl;

    manager.createAppointment(
        &doctor1,
        &patient1,
        &room1,
        10
    );


    // =================================================
    // TEST 2
    // Same doctor + same time
    // SHOULD FAIL
    // =================================================

    cout << "\nTEST 2" << endl;

    manager.createAppointment(
        &doctor1,
        &patient2,
        &room2,
        10
    );


    // =================================================
    // TEST 3
    // Same doctor + different time
    // SHOULD SUCCESS
    // =================================================

    cout << "\nTEST 3" << endl;

    manager.createAppointment(
        &doctor1,
        &patient2,
        &room2,
        11
    );


    // =================================================
    // TEST 4
    // Different doctor + same time
    // Different room
    // SHOULD SUCCESS
    // =================================================

    cout << "\nTEST 4" << endl;

    manager.createAppointment(
        &doctor2,
        &patient3,
        &room2,
        10
    );


    // =================================================
    // TEST 5
    // Different doctor + same room + same time
    // SHOULD FAIL
    // =================================================

    cout << "\nTEST 5" << endl;

    manager.createAppointment(
        &doctor2,
        &patient3,
        &room1,
        10
    );


    // =================================================
    // TEST 6
    // Outside doctor's working hours
    // SHOULD FAIL
    // =================================================

    cout << "\nTEST 6" << endl;

    manager.createAppointment(
        &doctor1,
        &patient1,
        &room1,
        17
    );


    // =================================================
    // Show everything
    // =================================================

    manager.showAllAppointments();


    return 0;
}