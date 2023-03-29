//g++ FT_TutGrp5_A1_7350314_PatelMihir.cpp -o FT_TutGrp5_A1_7350314_PatelMihir.exe
// ./FT_TutGrp5_A1_7350314_PatelMihir.exe
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;
//global variables
int gridXstart;
int gridXend;
int gridYstart;
int gridYend;
//method prototypes
void option1(string filename);
//void readCityName(string & filename);
void cityMapReading(int**& citymap);
void cloudCoverageMap(int**& cloudArray);
void atmosphericPressure(int**& pressureArray);
void summaryReport(int citynumber);
void option2();
void option3();
void option4();
void option5();
void option6();
void option7();
int main_menu();
string* storage_file= new string[3];//hold txt files 
vector<string> nameStorage{ };//holds city names

int main()
{
	string file;
	int enterfile=0;
	int userinput=main_menu();
	while (userinput !=8)
	{
		//switch cases based on user selection
		switch(userinput)
		{
			case 1:
			cout<<"[Read in and process a configuration file]"<<endl;
			cout<<"Please enter config filename"<<endl;
			cin>>file;
			option1(file);
			cout<<"All records successfully stored.Going back to main menu.."<<endl<<endl;
			userinput = main_menu();
			break;
			
			case 2:
			option2();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 3:
			option3();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 4:
			option4();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 5:
			option5();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 6:
			option6();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 7:
			option7();
			cout<<"Press enter to go back to main menu"<<endl;
			cin.ignore();
			if(cin.get() =='\n')
			{
			userinput= main_menu();
			}
			break;
			
			case 8:
			//delete pointer
			delete [] storage_file;
			break;
			
		}
	}
	return 0;
}

int main_menu()
{
	int option;
	string userinput;
	static string myName ="Mihir Mukeshbhai Patel";
	static string myId="7000";
	static string line ="---------------------------------";
	cout<<endl;
	cout<<"Student ID :"<<myId<<endl;;
	cout<<"Student Name:"<<myName<<endl;
	cout<<line<<endl;
	cout<<"Welcome to Weather Information Processing System!"<<endl;
	cout<<endl;
	cout<<"1) Read in and process a configuration file"<<endl;
	cout<<"2) Display city map"<<endl;
	cout<<"3) Display cloud coverage map(cloudiness index)"<<endl;
	cout<<"4) Display cloud coverage mao(LMH symbols)"<<endl;
	cout<<"5) Display atmospheric pressure map(pressure index)"<<endl;
	cout<<"6) Display atmosplheric pressure map(LMH symbols)"<<endl;
	cout<<"7) Show weather forecast summary report "<<endl;
	cout<<"8) Quit(Press 8 or any key to Exit)"<<endl;
	cout<<endl;	
	cout<<"Please enter your choice"<<endl;
	cin>>option;
	//if user enters a unknown number make them type again
	while(!((option==1)||(option==2)||(option==3)||(option==4)||(option==5)||(option==6)||(option==7)||(option==8)))
	{
		cout<<"Please enter a valid choice from (1 to 8);"<<endl;
		cin>>option;
	}	
	return option;
	
	cout<<endl;
}
//delimiter stuff
vector<string> tokenizeString (string input,string delimiter)
{
	 size_t pos =0;
	 string token;
	 vector<string> result;
	 
	 while ((pos = input.find(delimiter)) !=string::npos)
	 {
	 	token = input.substr(0,pos);
	 	result.push_back(token);
	 	input.erase(0,pos+delimiter.length());
	 }
	 result.push_back (input);
	 return(result);
}

void cityMapReading(int**& city2DArray)
{
	//for option2 to work we need to read the co oridnates of citylocation 
	if(!storage_file[0].empty())
	{
		ifstream thisFile;
		thisFile.open(storage_file[0]);
		string cityline;
		while(!thisFile.eof())
		{	
			while(getline(thisFile,cityline))
			{
			 	if(!cityline.empty())
			 	{
			 		//delimiter stuff
					string cline=cityline;
					vector<string> tokenizeStringVector = tokenizeString (cline,"-");
					string city_co = tokenizeStringVector[0];
					string city_id = tokenizeStringVector[1];
					string city_name = tokenizeStringVector[2];
					
					int cityID= stoi(city_id);
					string cityName = city_name;
							
					city_co.erase(0,1);
					city_co.erase(city_co.length()-1,city_co.length());
					tokenizeStringVector = tokenizeString(city_co,", ");
				
					string city_co_x = tokenizeStringVector[0];
					string city_co_y= tokenizeStringVector[1];
				
					int cityX= stoi(city_co_x);
					int cityY=stoi(city_co_y);
					
					if(0<=cityX<=gridXend && 0<=cityY<=gridYend)
					{
						city2DArray[cityX][cityY]=cityID;
					}
					
				}
			}
		}
		thisFile.close();
	}
	else 
	{
		cout<<"file empty"<<endl;
		main_menu();
	}
}

void option2()
{
	//2d array intialization and dynamic memorty allocation
	int** city2DArray;
	city2DArray= new int*[gridXend+1];
	for (int i=0;i<gridXend+1;i++)
	{
		city2DArray[i] = new int[gridYend+1];
	}	
	//int city2DArray [gridXend +1][gridYend +1];
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			city2DArray [i][j]=0;
		}
	}
	cityMapReading(city2DArray);
	//print top line here
	printf("%4s","#");
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	//print top line 
	printf("%2s%2s\n","#","#");
	//for loop opposite way because the it starts from y end and will print from y bottom to top
	for(int i= gridYend;i>=gridYstart;i--)
	{
		printf("%2d%2s",i,"#");
		for(int j=gridXstart;j<gridXend+1;j++)
		{
			if(city2DArray[j][i] <=0)
			{
				printf("%2s"," ");
			}
			else 
			{
				printf("%2d",city2DArray[j][i]);
			}
		}
		printf("%2s\n","#");
	}
	//print bottom stuff 
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	// prints the range with the numbers
	printf("%4s"," ");
	for(int i=0;i<gridXend+1;i++)
	{
		printf("%2d",i);
	}
	cout<<endl;
	//delete array and its contents to avoid memoryleak
	for(int i=0;i<gridXend+1;i++)
	{
		delete [] city2DArray[i];
	}
	delete[] city2DArray;
	
}

void cloudCoverageMap(int**& cloudArray)
{
	if(!storage_file[1].empty())
	{
		ifstream thisFile;
		thisFile.open(storage_file[1]);
		string cloudline;
		while(!thisFile.eof())
		{	
			while(getline(thisFile,cloudline))
			{
				if(!cloudline.empty())
				{
					//delimiter stuff
					string cloud=cloudline;	
					vector<string> tokenizeStringVector = tokenizeString (cloud,"-");
					string cloud_co = tokenizeStringVector[0];
					string cloud_cover = tokenizeStringVector[1];
				
					int cloudCover = stoi(cloud_cover);
					
					cloud_co.erase(0,1);
					cloud_co.erase(cloud_co.length()-1,cloud_co.length());
					tokenizeStringVector = tokenizeString(cloud_co,", ");
				
					string cloud_co_x = tokenizeStringVector[0];
					string cloud_co_y= tokenizeStringVector[1];
				
					int cloudX= stoi(cloud_co_x);
					int cloudY=stoi(cloud_co_y);
					//check condition whether cloud cover isnt exceeding range
					if(0<=cloudX<=gridXend && 0<=cloudY<=gridYend && 0<=cloudCover<100)
					{
						cloudArray[cloudX][cloudY]=cloudCover;
					}
				}
			}
		}
		thisFile.close();
	}
	else 
	{
		cout<<"file empty"<<endl;
		main_menu();
	}
}


void option3()
{
	//2d array intialization and dynamic memorty allocation
	int** cloudArray;
	cloudArray =new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		cloudArray[i]= new int[gridYend+1];
	}
	//int cloudArray [gridXend +1][gridYend +1];//intialize 2d array
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			cloudArray [i][j]=0;
		}
	}
	//call method to remove the delimiter
	cloudCoverageMap(cloudArray);
	//print top line here
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	//for loop opposite way because the it starts from y end and will print from y bottom to top
	for(int colum=gridYend;colum>=gridYstart;colum--)
	{
		printf("%2d%2s",colum,"#");
		
		//check id is within respective ranges and prints numbers accoridingly
		for(int row =gridXstart;row<gridXend+1;row++)
		{
			if(cloudArray[row][colum]>=0 && cloudArray[row][colum]<10)
			{
				printf("%2d",0);
			}
			else if(cloudArray[row][colum]>=10 && cloudArray[row][colum]<20)
			{
				printf("%2d",1);
			}
			else if(cloudArray[row][colum]>=20 && cloudArray[row][colum]<30)
			{
				printf("%2d",2);
			}
			else if(cloudArray[row][colum]>=30 && cloudArray[row][colum]<40)
			{
				printf("%2d",3);
			}
			else if(cloudArray[row][colum]>=40 && cloudArray[row][colum]<50)
			{
				printf("%2d",4);
			}
			else if(cloudArray[row][colum] >=50 && cloudArray[row][colum]<60)
			{
				printf("%2d",5);
			}
			else if(cloudArray[row][colum] >=60 && cloudArray[row][colum]<70)
			{
				printf("%2d",6);
			}
			else if(cloudArray[row][colum] >=70 && cloudArray[row][colum]<80)
			{
				printf("%2d",7);
			}
			else if(cloudArray[row][colum] >=80 && cloudArray[row][colum]<90)
			{
				printf("%2d",8);
			}
			else if(cloudArray[row][colum] >=90 && cloudArray[row][colum]<100)
			{
				printf("%2d",9);
			}
		}
		printf("%2s\n","#");
	}
	printf("%4s","#");
	//print bottom stuff 
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	
	printf("%4s"," ");
	//print the ranges 
	for(int i=0;i<gridXend+1;i++)
	{
		printf("%2d",i);
	}
	cout<<endl;
	//delete pointer and its data
	for(int i=0;i<gridXend;i++)
	{
		delete[] cloudArray[i];
	}
	delete[] cloudArray;
}

void option4()
{
	//2d array intialization and dynamic memorty allocation
	int** cloudArray;
	cloudArray=new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		cloudArray[i]= new int[gridYend+1];
	}
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			cloudArray [i][j]=0;
		}
	}
	//call method to remove the delimiter
	cloudCoverageMap(cloudArray);
	//print top line here
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	
	printf("%2s%2s\n","#","#");

	//for loop opposite way because the it starts from y end and will print from y bottom to top
	for(int colum=gridYend;colum>=gridYstart;colum--)
	{
		printf("%2d%2s",colum,"#");
		//check id meets requirment and prints alphabet 
		for(int row=gridXstart;row<gridXend+1;row++)
		{
			if(cloudArray[row][colum]>=0 && cloudArray[row][colum]<35)
			{
				printf("%2s","L");
			}
			else if(cloudArray[row][colum]>=35 && cloudArray[row][colum]<65)
			{
				printf("%2s","M");
			}
			else if(cloudArray[row][colum]>=65 && cloudArray[row][colum]<100)
			{
				printf("%2s","H");
			}
		}
		printf("%2s\n","#");//insert # at the end of line
	}
	//prints bottom line
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	
	printf("%4s"," ");
	//print ranges
	for(int i=0;i<gridXend+1;i++)
	{
		printf("%2d",i);
	}
	cout<<endl;
	
	//delete pointer and its data to avoid memory leak
	for(int i=0;i<gridXend;i++)
	{
		delete[] cloudArray[i];
	}
	delete[] cloudArray;
	
}
void option5()
{
	//2d array intialization and dynamic memorty allocation
	int** pressureArray;
	pressureArray =new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		pressureArray[i]= new int[gridYend+1];
	}	
	//intializing
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			pressureArray [i][j]=0;
		}
	}
	//call method to remove the delimiter
	atmosphericPressure(pressureArray);
	
	//print top line here
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	
	printf("%2s%2s\n","#","#");
	//for loop opposite way because the it starts from y end and will print from y bottom to top
	for(int colum=gridYend;colum>=gridYstart;colum--)
	{
		printf("%2d%2s",colum,"#");
		//check requiment and print number
		for(int row =gridXstart;row<gridXend+1;row++)
		{
			if(pressureArray[row][colum]>=0 && pressureArray[row][colum]<10)
			{
				printf("%2d",0);
			}
			else if(pressureArray[row][colum]>=10 && pressureArray[row][colum]<20)
			{
				printf("%2d",1);
			}
			else if(pressureArray[row][colum]>=20 && pressureArray[row][colum]<30)
			{
				printf("%2d",2);
			}
			else if(pressureArray[row][colum]>=30 && pressureArray[row][colum]<40)
			{
				printf("%2d",3);
			}
			else if(pressureArray[row][colum]>=40 && pressureArray[row][colum]<50)
			{
				printf("%2d",4);
			}
			else if(pressureArray[row][colum] >=50 && pressureArray[row][colum]<60)
			{
				printf("%2d",5);
			}
			else if(pressureArray[row][colum] >=60 && pressureArray[row][colum]<70)
			{
				printf("%2d",6);
			}
			else if(pressureArray[row][colum] >=70 && pressureArray[row][colum]<80)
			{
				printf("%2d",7);
			}
			else if(pressureArray[row][colum] >=80 && pressureArray[row][colum]<90)
			{
				printf("%2d",8);
			}
			else if(pressureArray[row][colum] >=90 && pressureArray[row][colum]<100)
			{
				printf("%2d",9);
			}
		}
		printf("%2s\n","#");
	}
	//prints bottom line
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	
	printf("%4s"," ");
	
	//print the range
	for(int i=0;i<gridXend+1;i++)
	{
		printf("%2d",i);
	}
	cout<<endl;
	
	//delete pointer and its data
	for(int i=0;i<gridXend;i++)
	{
		delete[] pressureArray[i];
	}
	delete[] pressureArray;
	
}

void option6()
{
	//2darray and its dynamic memory allocation
	int** pressureArray;
	pressureArray=new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		pressureArray[i]= new int[gridYend+1];
	}	
	//2d array intializing
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			pressureArray [i][j]=0;
		}
	}
	//call method to remove the delimiter
	atmosphericPressure(pressureArray);
	//print top line #
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	
	printf("%2s%2s\n","#","#");
	//for loop opposite way because the it starts from y end and will print from y bottom to top
	for(int colum=gridYend;colum>=gridYstart;colum--)
	{
		printf("%2d%2s",colum,"#");
		for(int row=gridXstart;row<gridXend+1;row++)
		{
			if(pressureArray[row][colum]>=0 && pressureArray[row][colum]<35)
			{
				printf("%2s","L");
			}
			else if(pressureArray[row][colum]>=35 && pressureArray[row][colum]<65)
			{
				printf("%2s","M");
			}
			else if(pressureArray[row][colum]>=65 && pressureArray[row][colum]<100)
			{
				printf("%2s","H");
			}
		}
		//bottom # for printing \n for the endline
		printf("%2s\n","#");
	}
	//prints bottom line
	printf("%4s","#");
	
	for(int i=0;i<gridXend;i++)
	{
		printf("%2s","#");
	}
	printf("%2s%2s\n","#","#");
	
	printf("%4s"," ");
	//print the range
	for(int i=0;i<gridXend+1;i++)
	{
		printf("%2d",i);
	}
	cout<<endl;
	
	//delete pointer and its data
	for(int i=0;i<gridXend;i++)
	{
		delete[] pressureArray[i];
	}
	delete[] pressureArray;
}	

void atmosphericPressure(int**& pressureArray )
{
	if(!storage_file[2].empty())
	{
		ifstream thisFile;
		thisFile.open(storage_file[2]);
		string pressureline;
		while(!thisFile.eof())
		{	
			while(getline(thisFile,pressureline))
			{
				if(!pressureline.empty())
				{
					//delimiter stuff
					string pressure=pressureline;	
					vector<string> tokenizeStringVector = tokenizeString (pressure,"-");
					string pressure_co = tokenizeStringVector[0];
					string pressure_area = tokenizeStringVector[1];
				
					int pressureArea = stoi(pressure_area );
					
					pressure_co.erase(0,1);
					pressure_co.erase(pressure_co.length()-1,pressure_co.length());
					tokenizeStringVector = tokenizeString(pressure_co,", ");
				
					string pressure_co_x = tokenizeStringVector[0];
					string pressure_co_y= tokenizeStringVector[1];
				
					int pressureX= stoi(pressure_co_x);
					int pressureY=stoi(pressure_co_y);
					//check range for pressrearea
					if(0<=pressureX<=gridXend && 0<=pressureY<=gridYend && 0<=pressureArea<100)
					{
						pressureArray[pressureX][pressureY]=pressureArea;
					}
					
				}
			}
		}
		thisFile.close();
	}
	else 
	{
		cout<<"file empty"<<endl;
		main_menu();
	}
}

void option7()
{
	cout<<"Weather Forecast Summary Report"<<endl;
	cout<<"--------------------------------"<<endl;
	for(int i=0; i<3;i++)
	{
		summaryReport(i);
		cout<<endl;
	}
	
}

void summaryReport(int citynumber)
{
	int counter = 0;
	int cloudcovervalue=0;
	int cityNumber = citynumber;
	int pressurevalue=0;
	bool isadded =false;
	
	//citymap array
	int** cityArray;
	cityArray= new int*[gridXend+1];
	for (int i=0;i<gridXend+1;i++)
	{
		cityArray[i] = new int[gridYend+1];
	}	
	
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			cityArray [i][j]=0;
		}
	}
	cityMapReading(cityArray);
	
	//cloud Array
	//2darray and its dynamic memory allocation
	int** cloudArray;
	cloudArray =new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		cloudArray[i]= new int[gridYend+1];
	}
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			cloudArray [i][j]=0;
		}
	}
	cloudCoverageMap(cloudArray);
	
	//pressure  Array
	//2darray and its dynamic memory allocation
	int** pressureArray;
	pressureArray =new int* [gridXend+1];
	for(int i=0;i<gridXend+1;i++)
	{
		pressureArray[i]= new int[gridYend+1];
	}	
	//2d array intializing
	for(int i=0;i<gridXend+1;i++)
	{
		for(int j=0;j<gridYend+1;j++)
		{
			pressureArray [i][j]=0;
		}
	}
	atmosphericPressure(pressureArray);
	
	// for loops for getting data
    for (int x = gridXstart; x < gridXend + 1; x++)
     {
        for (int y = gridYstart; y < gridYend + 1; y++) 
        {
            isadded = false;
            //check the data represent the citynumber 
            if (cityArray[x][y] == cityNumber)
             {
                counter++;
                pressurevalue += pressureArray[x][y];
                cloudcovervalue += cloudArray[x][y];
                
             }
			//checks if the number from cityarray matches the id from citynumber
            else if (cityArray[x][y] != cityNumber)
             {
                if (x - 1 >= gridXstart && y + 1 <= gridYend) 
                {
                    if (cityArray[x - 1][y + 1] == cityNumber) 
                    {
                        if (isadded == false)
                         {
                         	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                         }
                    }
                }
                //Checks on top of the cityarray id from y axis
                if (y + 1 <= gridYend)
                {
                    if (cityArray[x][y + 1] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
                 //Checks on top of the cityarray id from y axis and x axis
                if (y + 1 <= gridYend && x + 1 <= gridXend)
                {
                    if (cityArray[x + 1][y + 1] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
                 //Checks on top of the cityarray id from x axis from the left
                if (x - 1 >= gridXstart) 
                {
                    if (cityArray[x - 1][y] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
                 //Checks id of the cityarray id from x axis from the right
                if (x + 1 <= gridXend) 
                {
                    if (cityArray[x + 1][y] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }

                //Checks on below of the cityarray id from y axis and x axis 
                if (x - 1 >=  gridXstart && y - 1 >=  gridYstart) 
                {
                    //Check if it matches 
                    if (cityArray[x - 1][y - 1] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
                //Checks on below of the cityarray id from y axis
                if (y - 1 >= gridYstart) 
                {
                    if (cityArray[x][y - 1] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
                 //Checks on top and  below of the cityarray id from y axis and x axis
                if (y - 1 >= gridYstart && x + 1 <=  gridXend) 
                {
                    if (cityArray[x + 1][y - 1] == cityNumber) 
                    {
                        if (isadded == false) 
                        {
                        	pressurevalue += pressureArray[x][y];
                            cloudcovervalue += cloudArray[x][y];
                            counter++;
                            isadded = true;
                        }
                    }
                }
            }
        }
    }
    // calculate the average for the relevant details 
    double averagePressure = (double)pressurevalue / (double)counter;
    double averageCloudCover = (double)cloudcovervalue / (double)counter;
    //set the symbols
    string cloud_symbol = "L";
    string pressure_symbol = "L";

    //Changes symbol
    //display M when average pressure is met requirement 
    if (averagePressure >= 35 && averagePressure < 65) 
    {
        pressure_symbol = "M";
    }
	//display M when average cloud is met requirment 
    if (averageCloudCover >= 35 && averageCloudCover < 65) 
    {
        cloud_symbol = "M";
    }
	//display H when average pressure is met requirement 
    if (averagePressure >= 65 && averagePressure < 100) 
    {
        pressure_symbol = "H";
    }
	//display H when average cloud is met requirment 
    if (averageCloudCover >= 65 && averageCloudCover < 100) 
    {
        cloud_symbol = "H";
    }

    //print output
    cout << "City Name : " << nameStorage[citynumber] << endl;
    cout << "City ID : " << citynumber << endl;
    printf("Ave. Cloud Cover   (ACC)   : %2.2f ", averageCloudCover);
    cout << " (" << cloud_symbol << ")" << endl;
    printf("Ave. Pressure      (AP)    : %2.2f ", averagePressure);
    cout << " (" << pressure_symbol << ")" << endl;

    //Checks rain in this if else 
    if (averagePressure >= 0 && averagePressure < 35 && averageCloudCover >= 65 && averageCloudCover < 100) 
    {
        cout << "Probility of rain  (%)     : 90.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "\\\\\\\\\\" << endl;
    }
    else if (averagePressure >= 0 && averagePressure < 35 && averageCloudCover >= 35 && averageCloudCover < 65) 
    {
        cout << "Probility of rain  (%)     : 80.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << " \\\\\\\\" << endl;
    }
    else if (averagePressure >= 0 && averagePressure < 35 && averageCloudCover >= 0 && averageCloudCover < 35) 
    {
        cout << "Probility of rain  (%)     : 70.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "  \\\\\\" << endl;
    }
    else if (averagePressure >= 35 && averagePressure < 65 && averageCloudCover >= 65 && averageCloudCover < 100) 
    {
        cout << "Probility of rain  (%)     : 60.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "   \\\\" << endl;
    }
    else if (averagePressure >= 35 && averagePressure < 65 && averageCloudCover >= 35 && averageCloudCover < 65) 
    {
        cout << "Probility of rain  (%)     : 50.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "    \\" << endl;
    }
    else if (averagePressure >= 35 && averagePressure < 65 && averageCloudCover >= 0 && averageCloudCover < 35) 
    {
        cout << "Probility of rain  (%)     : 40.00" << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
    }
    else if (averagePressure >= 65 && averagePressure < 100 && averageCloudCover >= 65 && averageCloudCover < 100) 
    {
        cout << "Probility of rain  (%)     : 30.00" << endl;
        cout << "~~~" << endl;
        cout << "~~~~" << endl;
    }
    else if (averagePressure >= 65 && averagePressure < 100 && averageCloudCover >= 35 && averageCloudCover < 65) 
    {
        cout << "Probility of rain  (%)     : 20.00" << endl;
        cout << "~~" << endl;
        cout << "~~~" << endl;
    }
    else if (averagePressure >= 65 && averagePressure < 100 && averageCloudCover >= 0 && averageCloudCover < 35) 
    {
        cout << "Probility of rain  (%)     : 10.00" << endl;
        cout << "~" << endl;
        cout << "~~" << endl;
    }



    //Delte 2darrays
    for (int i = 0; i < gridXend + 1; i++) 
    {
        delete[] cloudArray[i];
    }
    for (int i = 0; i < gridXend + 1; i++)
    {
        delete[] cityArray[i];
    }
    for (int i = 0; i < gridXend + 1; i++)
    {
        delete[] pressureArray[i];
    }

    delete[] cloudArray;
    delete[] pressureArray;
    delete[] cityArray;

	
}


void option1 (string filename)
{
	int txt_counter=0;
	ifstream inputFile(filename.c_str());
	if (inputFile.is_open())
	{
		string aline;
		while(!inputFile.eof())
		{
			while(getline(inputFile,aline))
			{	
				if(aline.find("GridX_IdxRange") !=string::npos)
				{
					string xline= aline;
					vector<string> tokenizeStringVector = tokenizeString (xline,"=");
					string x_range = tokenizeStringVector[1];
					tokenizeStringVector = tokenizeString (x_range,"-");
					string x_start =tokenizeStringVector[0];
					string x_end = tokenizeStringVector[1];
					gridXstart = stoi(x_start);
					gridXend =  stoi(x_end);
					cout<< "Reading in GridX_IdxRange :"<<gridXstart<<"-"<<gridXend<<"..."<<"done"<<endl<<endl;
				}		
				if(aline.find("GridY_IdxRange") !=string::npos)
				{
					string yline= aline;
					vector<string> tokenizeStringVector = tokenizeString (yline,"=");
					string y_range = tokenizeStringVector[1];
					tokenizeStringVector = tokenizeString (y_range,"-");
					string y_start =tokenizeStringVector[0];
					string y_end = tokenizeStringVector[1];
					gridYstart = stoi(y_start);
					gridYend =  stoi(y_end);
					cout<< "Reading in GridY_IdxRange :"<< gridYstart<<"-"<< gridYend <<"..."<<"done"<<endl<<endl;
					cout<<"Storing Data from input files :"<<endl;
				}	
				if(aline.find(".txt") !=string::npos)
				{
					txt_counter++;
						if(txt_counter ==1)
						{
							storage_file[0]=aline;
						}
						if(txt_counter==2)
						{
							storage_file[1]=aline;
						}
						if(txt_counter==3)
						{
							storage_file[2]=aline;
						}	
						
				}	
			}
		}	
		for(int j=0;j<3;j++)
		{
			cout<<storage_file[j]<<"...done"<<endl;
		}
		cout<<endl;
		inputFile.close();
	}
	else 
	{
	 cout<<"File does not exist:  "<<filename<<endl;
	}
	
    if (!storage_file[0].empty()) 
    {
        ifstream thisFile;
        string testline;
        thisFile.open(storage_file[0],ios::in);
        if (thisFile.is_open())
         {
            while (getline(thisFile, testline)) 
            {
                if (!testline.empty()) 
                {
               	    char const* removecomma{ "," };
    				char const* removebracket{ "]" };
                    int xset;
                    int yset;
                    string gridXstring;
                    string gridYstring;
                    testline.erase(0, 1);
                    int removedComma = testline.find_first_of(removecomma);
                    
                    for (int i = 0; i < removedComma; i++) 
                    {
                        gridXstring += testline[i];
                    }
                    
                    xset = stoi(gridXstring);
                    testline.erase(0, 2);
                    
                    int no_string= testline.find_first_of(removebracket);
                    
                    for (int k = 0; k < no_string; k++)
                    {
                        gridYstring += testline[k];
                    }
                    
                    yset = stoi(gridYstring);
                   
                    if (yset < 10)
                    {
                        testline.erase(0, 4);
                    }
                    else 
                    {
                        testline.erase(0, 5);
                    }
                   
                    int city_num;
                    string city_string_num;
                    string city_name_storage;
                    city_string_num += testline[0];
                    city_num = stoi(city_string_num);

                    testline.erase(0, 2);
                    
                    for (int i = 0; i < testline.length(); i++) 
                    {
                        city_name_storage += testline[i];
                    }
                   
                    if (nameStorage.size() <= city_num)
                    {
                        nameStorage.resize(city_num + 1);
                        nameStorage[city_num] = city_name_storage;
                    }
                    else if (city_num < nameStorage.size()) 
                    {
                        nameStorage[city_num] = city_name_storage;
                    }
                }
            }
            thisFile.close();
        }
    }	
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
