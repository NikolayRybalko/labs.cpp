#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Vehicle {
  string id;
  string make;
  string model;
  string year;
  string price;

  string to_string() const {
    return id + "|" + make + "|" + model + "|" + year + "|" + price;
  }

  static Vehicle from_string(const string &data) {
    Vehicle vehicle;
    stringstream ss(data);
    getline(ss, vehicle.id, '|');
    getline(ss, vehicle.make, '|');
    getline(ss, vehicle.model, '|');
    getline(ss, vehicle.year, '|');
    getline(ss, vehicle.price, '|');
    return vehicle;
  }
};

void loadDatabase(const string &filename, Vehicle *&vehicles, int &count) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return;
  }

  count = 0;
  string line;
  while (getline(file, line)) {
    count++;
  }
  file.clear();
  file.seekg(0, ios::beg);

  vehicles = new Vehicle[count];
  int index = 0;
  while (getline(file, line)) {
    vehicles[index++] = Vehicle::from_string(line);
  }

  file.close();
}

void saveDatabase(const string &filename, Vehicle *vehicles, int count) {
  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return;
  }

  for (int i = 0; i < count; ++i) {
    file << vehicles[i].to_string() << endl;
  }

  file.close();
}

void addVehicle(Vehicle *&vehicles, int &count) {
  Vehicle *newVehicles = new Vehicle[count + 1];

  for (int i = 0; i < count; ++i) {
    newVehicles[i] = vehicles[i];
  }

  cout << "Enter vehicle ID: ";
  cin >> newVehicles[count].id;
  cout << "Enter vehicle make: ";
  cin.ignore();
  getline(cin, newVehicles[count].make);
  cout << "Enter vehicle model: ";
  getline(cin, newVehicles[count].model);
  cout << "Enter vehicle year: ";
  getline(cin, newVehicles[count].year);
  cout << "Enter vehicle price: ";
  getline(cin, newVehicles[count].price);

  delete[] vehicles;
  vehicles = newVehicles;
  ++count;
}

void editVehicle(Vehicle *vehicles, int count) {
  string id;
  cout << "Enter vehicle ID to edit: ";
  cin >> id;

  for (int i = 0; i < count; ++i) {
    if (vehicles[i].id == id) {
      cout << "Enter new vehicle make: ";
      cin.ignore();
      getline(cin, vehicles[i].make);
      cout << "Enter new vehicle model: ";
      getline(cin, vehicles[i].model);
      cout << "Enter new vehicle year: ";
      getline(cin, vehicles[i].year);
      cout << "Enter new vehicle price: ";
      getline(cin, vehicles[i].price);
      return;
    }
  }

  cout << "Vehicle ID not found." << endl;
}

void deleteVehicle(Vehicle *&vehicles, int &count) {
  string id;
  cout << "Enter vehicle ID to delete: ";
  cin >> id;

  int index = -1;
  for (int i = 0; i < count; ++i) {
    if (vehicles[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "Vehicle ID not found." << endl;
    return;
  }

  Vehicle *newVehicles = new Vehicle[count - 1];
  for (int i = 0, j = 0; i < count; ++i) {
    if (i != index) {
      newVehicles[j++] = vehicles[i];
    }
  }

  delete[] vehicles;
  vehicles = newVehicles;
  --count;
}

void searchVehicle(const Vehicle *vehicles, int count) {
  string id;
  cout << "Enter vehicle ID to search: ";
  cin >> id;

  for (int i = 0; i < count; ++i) {
    if (vehicles[i].id == id) {
      cout << "ID: " << vehicles[i].id << endl;
      cout << "Make: " << vehicles[i].make << endl;
      cout << "Model: " << vehicles[i].model << endl;
      cout << "Year: " << vehicles[i].year << endl;
      cout << "Price: " << vehicles[i].price << endl;
      return;
    }
  }

  cout << "Vehicle ID not found." << endl;
}

void printVehicles(const Vehicle *vehicles, int count) {
  for (int i = 0; i < count; ++i) {
    cout << "ID: " << vehicles[i].id << endl;
    cout << "Make: " << vehicles[i].make << endl;
    cout << "Model: " << vehicles[i].model << endl;
    cout << "Year: " << vehicles[i].year << endl;
    cout << "Price: " << vehicles[i].price << endl;
    cout << "---------------------" << endl;
  }
}

int main() {
  Vehicle *vehicles = nullptr;
  int count = 0;
  const string filename = "vehicle_database.txt";
  loadDatabase(filename, vehicles, count);

  while (true) {
    cout << "1. Add vehicle" << endl;
    cout << "2. Edit vehicle" << endl;
    cout << "3. Delete vehicle" << endl;
    cout << "4. Search vehicle" << endl;
    cout << "5. Print all vehicles" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      addVehicle(vehicles, count);
      saveDatabase(filename, vehicles, count);
      break;
    case 2:
      editVehicle(vehicles, count);
      saveDatabase(filename, vehicles, count);
      break;
    case 3:
      deleteVehicle(vehicles, count);
      saveDatabase(filename, vehicles, count);
      break;
    case 4:
      searchVehicle(vehicles, count);
      break;
    case 5:
      printVehicles(vehicles, count);
      break;
    case 6:
      delete[] vehicles;
      return 0;
    default:
      cout << "Invalid choice, try again." << endl;
    }
  }

  return 0;
}
