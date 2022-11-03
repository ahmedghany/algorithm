/*Name: Ahmed Abdel Ghany, NSHE ID: 2001445844, CS302 Assignment 8,
 *Description: decide which land should land first using proiority queue 
 *Input: file
 *Output: rocket id, velocity, fuel, altitude */


/*Algorithm: build up the priorityQ class to decide which land,
* would have the advantage to be the first one, using land class,
* to simulate landers velocity, fuel_amount and altitude, then we
* implement both class headers in main here, and prompt the user,
to enter the files and we store the data from the files, and then,
*output we output velocity, id, fuel, altitude for each rocket.*/


#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "priorityQ.h"
#include "lander.h"
using namespace std;

int main(){
    
    ifstream infile, infile2;
    string file;
    double mass, max_thrust, max_fuel, alt, fuel;
    int id;
    double flow;
    lander land;
    priorityQ <lander> queue;
    
    cout<<endl;

    //get the file name
    while(true){

        cout <<"Enter lander file: ";
        cin>>file;
        
        infile.open(file);
        
        if (infile.is_open())
            break;
    }
    
    while(true){
        
        //store data
        infile>>mass>>max_thrust>>max_fuel>>alt>>fuel>>id;
        
        if ( infile.eof())
            break;
    
        land = lander ( mass, max_thrust, max_fuel, alt, fuel, id);

        queue.insert(land);
    }
    cout<<endl;
    while(true){

        cout <<"Enter simulation file: ";
        cin>>file;
        
        infile2.open(file);
        
        if (infile2.is_open())
            break;
    }

    while(true){
        
        //get data
        getline(infile2, file);
        
        if ( infile2.eof())
            break;
        //convert from string to double
        try{
            flow = stod(file);
        }
        
        catch(invalid_argument e){
            continue;
        }
        land=queue.getHighestPriority();
 
        //check the flow rate to output
        if (!land.change_flow_rate( flow))
            continue;
        
       
        queue.deleteHighestPriority();

        cout<<endl;    
        cout<<"Rocket "<<land.get_id()<<endl;
        cout<<"Fuel: "<<land.get_fuel_amount()<<endl;
        cout<<"Altitude: "<<land.get_altitude()<<endl;
        cout<<"Velocity: "<<land.get_velocity()<<endl;

        land.simulate();
        //check satus for crashed
        if ( land.get_status() == 'c'){
            cout<<endl<<"Rocket ID: "<<land.get_id()<<" has crashed :( At least nobody was on board"<<endl;
            continue;
        }
        //check status for landed
        if ( land.get_status() == 'l'){
            cout<<endl<<"Rocket ID: "<<land.get_id()<<" has successfully landed and all astronauts are accounted for :)"<<endl;
            continue;
        }
        queue.insert(land);
    }
    cout<<endl<<endl;
    //if we don't have any elementsin the queue
    if (!queue.isEmpty())
        cout<<"There are landers still trying to land..."<<endl;
    
    //output landers who still landing
    while (queue.getSize() > 0){
        
        land=queue.getHighestPriority();
        queue.deleteHighestPriority();

        cout<<"Lander ID: "<<land.get_id()<<" Altitude: "<<land.get_altitude()<<" mission aborted."<<endl;

    }
    
    infile.close();
    infile2.close();
    return 0;
}
