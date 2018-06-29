//Use any method to retrieve data from the server and insert it into the recieved_data[].
//Size of this array is adjustable and is currently set to 6 to avoid compile time error.

#include <iostream>
#include <ctime>

using namespace std;


#define NUMBER_OF_PANELS 3
int brightness[7]={1,2,3,4,5,6,7};
float max_current[21]={0.14,0.6,1.04,1.5,2.1,2.2,2.5,0.7,2.7,4.5,6.5,9,10.4,12,1.2,3.9,6.51,9.3,12,15.3,17.1};
float min_current[21]={0.01,0.23,0.45,0.66,0.9,1.1,1.2,0.05,0.4,0.5,0.7,1.25,1.4,1.7,0.15,0.52,0.75,1.5,1.9,2.08,2.66};
float peak_values[2];
float list_max_values[NUMBER_OF_PANELS][6],list_min_values[NUMBER_OF_PANELS][6],received_data[6];
int current_brightness,count,z=0,overflow=20;



////////////////////////////////////////////////////////////////////////////////////

int main() {
    struct tm *theTime;
	time_t tim;
	time(&tim);
	int hour = theTime->tm_hour;

    if (hour>8 && hour<=18)current_brightness = 5;
    if (hour>18 && hour<=23)current_brightness = 2;
    if (hour>=0 && hour<=8)current_brightness = 2;

     void map_values();
     void get_peak_values();
     int get_output(NUMBER_OF_PANELS);
 }


/////////////////////////////////////////////////////////////////////
void largest(float arr[], int n)
{
    int i;
    int max = arr[0];
       for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
      peak_values[1] = max;
}

///////////////////////////////////////////////////

void smallest (float arr[], int n)
{
    int i;
    int min = arr[0];
       for (i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    peak_values[0] = min;
}

////////////////////////////////////////////////////////////////


void get_peak_values(){

  largest(received_data,sizeof(received_data));
  smallest(received_data,sizeof(received_data));
}


/////////////////////////////////////////////////////////////////////
void map_values(){

for(int x = NUMBER_OF_PANELS-1;x>0;x--){
  for(int y = 6;y>0;y--){
  if(y==6)
  list_min_values[x][y] = min_current[((x+1)*y)+2 - z];
  else
  list_min_values[x][y] = min_current[y + (7*x)];
  }
}

for(int x = NUMBER_OF_PANELS-1;x>0;x--){
  for(int y = 6;y>0;y--){
  if(y==6)
list_max_values[x][y] = max_current[((x+1)*y)+2 - z ];
else
list_max_values[x][y] =  max_current[y + (7*x)];
  }
  z++;
}

}
//////////////////////////////////////////////////////////////////////////////
int get_output(int a){
  if(peak_values[0]<list_min_values[a-1][current_brightness] && peak_values[1]<list_max_values[a-1][current_brightness] ){
    count++;
    if(count>overflow)
    cout<<"One or more panel down"; count=0;
  }

  if(peak_values[0]<list_min_values[0][current_brightness] && peak_values[1]<list_max_values[0][current_brightness] ){
    count++;
    if(count>overflow)
    cout<<"All panels down";count=0;
  }
  return 0;
}
//////////////////////////////////////////////////////////////
