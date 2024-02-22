#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
using namespace std;
//sourced from ChatGPT
//Erica Ricci AERSP424

//defining class 'Plane" for question 3
class Plane
{
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    //const int myPlane;
    std::string origin;
    std::string destination;


public:
    Plane(const std::string& from, const std::string& to, std::map <std::pair<std::string, std::string>, double>pathdistances)
        : pos(0.0), vel(0.0), distance(0.0), at_SCE(false), origin(from), destination(to)
    {
        // if statements to check the user input to the string variables in pathdistances
        origin = from;
        destination = to;

        if (origin == "SCE" && destination == "PHL" || origin == "PHL" && destination == "SCE") \
        {
            distance = pathdistances[{"SCE", "PHL"}];
        }
        else if (origin == "SCE" && destination == "EWR" || origin == "EWR" && destination == "SCE") \
        {
            distance = pathdistances[{"SCE", "EWR"}];
        }
        else if (origin == "SCE" && destination == "ORD" || origin == "ORD" && destination == "SCE") \
        {
            distance = pathdistances[{"SCE", "ORD"}];
        }
        else {
            
        }

        //distance = pathdistances[{;
        std::cout << "Plane Created at " << this << std::endl;//question 4
    }
    // Destructor
    ~Plane()
    {
        std::cout << "Plane Destroyed" << std::endl;//question 4
    }
    // Function to operate the plane
    void operate(double dt)
    {
        if (pos < distance)
        {
            pos += vel * dt;
            at_SCE = 0;
        }
        else
        {
            if (destination == "SCE")
            {
                at_SCE = 1;

                std::swap(origin, destination);
                pos = 0.0;
            }
            else {
                // Swap the values of "origin" and "destination"
                std::swap(origin, destination);
                pos = 0.0;
                ;
            }
        }
        
    }
    //get functions
    double getPos() const
    {
        return pos;
    }
    double getDistance() const
    {
        return distance;
    }
    bool isAtSCE() const
    {
        return at_SCE;
    }
    std::string getOrigin() const
    {
        return origin;
    }
    std::string getDestination() const
    {
        return destination;
    }
    double getVel() const
    {
        return vel;
    }
    //set function for vel
    void setVel(double newVel) {
        vel = newVel;
    }
   
};



//question 6 & 7 
class Pilot {
private:
    std::string name;
    

public:
    // Constructor
    Plane* myPlane;//Q 7 pointer
    //std::shared_ptr<Plane> myPlane; Q8 pointer

    Pilot(const std::string& pilotName, Plane* plane)
        : name(pilotName), myPlane(plane) {
        // Print out pilot's name, memory address, and message
        std::cout << "Pilot " << name << " created at " << this << " is ready to board the plane." << std::endl;
    }

    // Destructor
    ~Pilot() {
        // Print out pilot's name and message
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    // Getter function for the variable "name"
    std::string getName() const {
        return name;
    }

    // Getter function for the pointer "myPlane" Q7
    Plane* getMyPlane() const {
        return myPlane;
    }
    // Getter function for the pointer "myPlane" Q8
  /*  std::shared_ptr<Plane> getMyPlane() const {
        return myPlane;
    }*/


};
int main() {
    //Container from question 2
    std::map <std::pair<std::string, std::string>, double>pathdistances;

    pathdistances[{"SCE", "PHL"}] = 160;
    pathdistances[{"SCE", "EWR"}] = 220;
    pathdistances[{"SCE", "ORD"}] = 640;

    std::string from;
    std::string to;
    cout << "input airport leaving from: ";
    cin >> from;
    cout << "input airport going to: ";
    cin >> to;
    double position = 0;
    //Question 7
    Plane myPlane(from, to, pathdistances);
    //question 8
    //auto myPlane = std::make_shared<Plane>(from, to, pathDistances);
    Pilot pilot1("Pilot-in-Command", &myPlane);
    Pilot pilot2("Co-Pilot", &myPlane);
    //Question 8
    
    // Set the speed of the airplane in the range [400, 500] mps
    double speed = 450.0 / 3600.0;
    myPlane.setVel(speed);
    double distance = myPlane.getDistance();

    // Choose a timestep between [10, 100]
    double timestep = 15;
    double time = 0;
   

    // Choose the maximum number of iterations between [1000, 2000]
    int maxIterations = 1500;

    // Perform iterations
    for (int i = 0; i < maxIterations; ++i) {
 
        // Update the position and time
        
        myPlane.operate(timestep);
        position = myPlane.getPos();
        time = time + timestep;
        cout << "Time: " << time << " seconds, " << " Position: " << position << " miles." << std::endl;

    }

    //question 7
    for (int i = 0; i < maxIterations; ++i) {
        // Switch between pilots when the plane lands at SCE
        if (myPlane.isAtSCE() == 1) {
            std::cout << "Plane landed at SCE."<<std::endl ;

            // Switch pilots
            Pilot* currentPilot = (i % 2 == 0) ? &pilot1 : &pilot2;
            std::cout << "Switching to " << currentPilot->getName() << ". Memory address: " << currentPilot->getMyPlane() << std::endl;
        }

        
        myPlane.operate(timestep);
        time += timestep;
    }
    return 0;
    
}