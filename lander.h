#include <iostream>
#include <cstdlib>

using namespace std;

class lander
{
public :
	lander ( double = 0 , double = 0 , double = 0 , double = 0 , double = 0 , int = 0);
	double get_velocity () const ;
	double get_altitude () const ;
	double get_fuel_amount () const ;
	int get_id () const ;
	double get_mass () const ;
	char get_status () const ;
	bool change_flow_rate ( double );
	void simulate ();
	bool operator>( const lander &) const ;

private :
	double flow_rate ;
	double velocity ;
	double altitude ;
	double fuel_amount ;
	bool stillLanding ;
	int id ;
	int timesSimulated ;
	double LANDER_MASS ;
	double MAX_FUEL_CONSUMPTION_RATE ;
	double MAX_THRUST ;
};


/*function_identifier: intialize values
*paarmeters: mass, max_thrust, max_fuel, alt, fuel, id
*return value: none */
lander::lander( double mass, double max_thrust, double max_fuel, double alt, double fuel, int id){
    
    LANDER_MASS = mass;
    MAX_THRUST = max_thrust;
    MAX_FUEL_CONSUMPTION_RATE = max_fuel;
    altitude = alt;
    fuel_amount = fuel;
    this->id = id;
    flow_rate = 0;
    velocity = 0;
    stillLanding = true;
    timesSimulated = 0;

}


/*function_identifier: return the velocity value
*paarmeters: none
*return value: velocity */
double lander::get_velocity () const {
    
    return velocity;
}

/*function_identifier: return altidue value
*paarmeters: none
*return value: altitude */
double lander::get_altitude () const {

    return altitude;
}

/*function_identifier: return fuel amount value
*paarmeters: none
*return value: fuel_amount */
double lander::get_fuel_amount () const {

    return fuel_amount;
}

/*function_identifier: return lander id value
*paarmeters: none
*return value: id */
int lander::get_id () const {

    return id;
}

/*function_identifier: return mass value
*paarmeters: none
*return value: LANDER_MASS */
double lander::get_mass () const {

    return LANDER_MASS;
}

/*function_identifier: return the status character of the lander
*paarmeters: none
*return value: 'a', 'c', 'l' */
char lander::get_status () const {

    if ( stillLanding == true)
        return 'a';
    
    if ( stillLanding == false && velocity < -2)
        return 'c';
    
    return 'l';
}

/*function_identifier: return the flow rate boolen
*paarmeters: r
*return value: true, false */
bool lander::change_flow_rate (double r){

    if ( 0 <= r && r <= 1){
        
        if ( fuel_amount > 0)
            flow_rate = r; 
        else
            flow_rate = 0;
        
        return true;
    }    
    return false;
}

/*function_identifier: simulate the lander
*parameters: none
*return value: none */
void lander::simulate(){
    
    const double TIME = 1;
    
    if ( stillLanding == true){

        double v = (TIME * ( (flow_rate * MAX_THRUST)/(LANDER_MASS + fuel_amount))) - 1.62;
        
        velocity += v;
        
        altitude += (TIME * velocity);
        
        if ( altitude <= 0){
            altitude = 0;
            stillLanding = false;
        }

        
        // :(
        if ( flow_rate > 0)
            fuel_amount -= ( TIME * MAX_FUEL_CONSUMPTION_RATE * abs(v));

        if ( fuel_amount < 0)
            fuel_amount = 0;

        timesSimulated +=1;
        
    }
}

/*function_identifier: compare between our variables and rhs variables 
*paarmeters: rhs
*return value: none */
bool lander::operator >( const lander & rhs) const{

    if ( timesSimulated == rhs.timesSimulated){

        if ( altitude == rhs.altitude){

            if ( fuel_amount == rhs.fuel_amount){

                if ( LANDER_MASS == rhs.LANDER_MASS)
                
                    return id < rhs.id;
                
                return LANDER_MASS > rhs.LANDER_MASS;
            }
            return fuel_amount < rhs.fuel_amount;
        }
        return altitude < rhs.altitude;
    }
    return timesSimulated < rhs.timesSimulated;
} 
