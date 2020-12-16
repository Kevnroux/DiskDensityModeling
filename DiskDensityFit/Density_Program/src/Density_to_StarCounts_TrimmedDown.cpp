#include "Density_to_Star_Counts.h"
#include <stdlib.h>
int sdss_or_pan = 0;
int sdss_include_near = 1;
using namespace std;
//Generates and returns a vector with randomly initialized values in the range of 
//min to max.
vector<double> randomVector(int min, int max, int length)
{
	//srand (time(NULL));
	vector<double> random = vector<double>(length, 0.0);
	for (unsigned int i = 0; i< random.size(); i+=1)
	{
		random[i] = (int)(rand() % (max-min) + min);
		//cout<<random[i]<<" ";	
	}
	//cout<<"DONE\n";
	return random;
}

//Takes a vector which should be interpolated
//returns a vector that is the interpolated version of the original vector
//This vector will have a size == input.size() + (input.size()-1)
vector<double> interpolate(const vector<double> &input) 
{
    vector<double> result = vector<double>(input.size()+(input.size()-1), 0.0);
	//Insert input values into result in every other position so we can interpolate
    for (int i = 0; i < result.size(); i += 2)
    {
        result[i] = input[i/2];
    }
    //Interpolate the values from input using linear interpolation
    for (int i = 1; i < result.size(); i += 2)
    {
        result[i] = (result[i-1]+result[i+1])/2.0;
    }
    
    return result;
}


//multiplies the first value with first value, second value with second value, etc. of two arrays (must be same length)
vector<double> mult2arrays(const vector<double> &array1, const vector<double> &array2) //ampersands are the address of a variable, which is why they are constants here (i think)
{
	int size1 = array1.size();
	int size2 = array2.size();
    
	vector<double> result (size1, 0);
    
	if (size1 != size2)
	{
		return result;
	}
	
	for (int i = 0; i < size1; i++)
	{
		result[i] = array1[i] * array2[i];
	}
	
	return result; 
}

//requires the gaussian vectors inside vector gaussian to have odd length
vector<double> Discrete_Convolution_2_Odd(vector<double> list1)
{
	vector< vector <double> > vectorGaussian = {{1.2052866803926663e-10, 3.49333526582688e-07, 0.0001571114227252507, 0.01140333754568543, 0.14231048066713145, 0.3391056009949741, 0.2851457269219317, 0.15306899858635778, 0.05409854771692879, 0.012580185444477835, 0.0019232539484265385}, {1.2052591708326127e-10, 3.4932555336620393e-07, 0.00015710783680151255, 0.011403077274992887, 0.14230723256128422, 0.3390980582493449, 0.2851433414201688, 0.15307389640040295, 0.054103934317084615, 0.012582632520255158, 0.0019238637128806274}, {1.205190932375891e-10, 3.4930577551490675e-07, 0.00015709894178823935, 0.011402431664145063, 0.14229917551748375, 0.3390793481124942, 0.28513742264071956, 0.15308604410681786, 0.054117296717676545, 0.012588704005103476, 0.0019253769412132592}, {1.2049887008267482e-10, 3.4924716185775983e-07, 0.00015707258051923776, 0.011400518331280127, 0.1422752976555338, 0.33902389803134453, 0.28511986955137164, 0.15312203251454803, 0.05415690376647048, 0.012606709394541494, 0.0019298672894351842}, {1.2042386619705418e-10, 3.4902977480538875e-07, 0.00015697481152061302, 0.011393422138823312, 0.14218673914751892, 0.3388182349099229, 0.28505460933105975, 0.15325534277579295, 0.054303879940726184, 0.012673643885755094, 0.0019465963206471925}, {1.2005661834000183e-10, 3.479653642288756e-07, 0.0001564960969189093, 0.01135867645263077, 0.14175312264854562, 0.3378110212176847, 0.2847314586864725, 0.15390433464555583, 0.05502534972334591, 0.013004933412676832, 0.0020302355692876435}, {1.1762900043299752e-10, 3.4092929274111296e-07, 0.000153331650572597, 0.01112899710019238, 0.13888678821672928, 0.3311445359938526, 0.28244616932675837, 0.15803347350141309, 0.05986364932896228, 0.015345043049498049, 0.00266005175236688}, {1.0273114435306686e-10, 2.977501828448016e-07, 0.00013391201039610897, 0.009719496071514745, 0.1212966074395388, 0.2899499444874817, 0.2631588100437829, 0.17640424861547988, 0.09040333074044168, 0.035415723745626446, 0.010604230529488032}, {8.443266387109737e-11, 2.4471489404704965e-07, 0.00011005959130776517, 0.007988258575045818, 0.09969124503713647, 0.23884207423581413, 0.229066642694846, 0.18029198894967624, 0.12083646623391317, 0.06896368392842481, 0.033514690714276665}, {8.236763426278535e-11, 2.387297281333743e-07, 0.0001073677857397656, 0.007792884063334255, 0.09725302547550488, 0.23304795392455768, 0.22463222015610004, 0.17939942301865813, 0.12320525925422596, 0.07275986410821364, 0.03694896732069376}, {8.231505929049892e-11, 2.3857734778455296e-07, 0.00010729925325840633, 0.007787909892747373, 0.09719094921017433, 0.2329003786621855, 0.22451796128436313, 0.17937326363174524, 0.12326204074386192, 0.07285531943381421, 0.0370379428784837}, {8.231458297073454e-11, 2.3857596724608207e-07, 0.00010729863236648848, 0.0077878648276591975, 0.09719038681040902, 0.23289904164380537, 0.22451692581532098, 0.17937302585658418, 0.1232625543601839, 0.07285618394055471, 0.037038749304877085}, {8.231458170386427e-11, 2.3857596357425634e-07, 0.00010729863071509884, 0.007787864707799335, 0.0971903853145913, 0.2328990380877299, 0.22451692306127102, 0.17937302522415374, 0.12326255572623261, 0.07285618623988085, 0.03703875144974157}};

	/* The old double gaussian. This should be incorrect
    vector< vector <double> > vectorGaussian = {{0.000146222,0.00152518,0.0104476,0.0470463,0.139381,0.271853,0.343851,0.169326,0.0163913,0.000275136,0.000000749684},
												{0.000146292,0.00152567,0.0104498,0.0470513,0.139386,0.271852,0.343844,0.169322,0.016391,0.00027513,0.000000749667},
												{0.00014647,0.00152694,0.0104552,0.0470641,0.139399,0.271849,0.343826,0.169312,0.01639,0.000275115,0.000000749625},
												{0.000146993,0.00153067,0.0104711,0.0471017,0.139438,0.271838,0.34377,0.169284,0.0163873,0.000275069,0.000000749499},
												{0.000148947,0.00154456,0.0105301,0.0472411,0.139583,0.271799,0.343566,0.169179,0.0163771,0.000274897,0.000000749033},
												{0.000158861,0.00161417,0.0108227,0.0479266,0.140287,0.271603,0.342566,0.168663,0.0163271,0.000274059,0.000000746749},
												{0.000240385,0.0021425,0.0129031,0.0525479,0.144804,0.270141,0.335936,0.165252,0.015997,0.000268518,0.000000731649},
												{0.00202997,0.00913824,0.0314354,0.0826496,0.166109,0.255227,0.294742,0.144323,0.013971,0.00023451,0.000000638985},
												{0.0124662,0.0306631,0.0642212,0.114533,0.173935,0.224931,0.243223,0.118616,0.0114824,0.000192738,0.000000525168},
												{0.0145973,0.0339889,0.0680515,0.117162,0.173455,0.220825,0.237361,0.115715,0.0112016,0.000188025,0.000000512324},
												{0.0146547,0.0340756,0.0681486,0.117226,0.17344,0.220719,0.237212,0.115641,0.0111945,0.000187905,0.000000511997},
												{0.0146552,0.0340765,0.0681495,0.117226,0.173439,0.220718,0.23721,0.11564,0.0111944,0.000187903,0.000000511994},
												{0.0146552,0.0340765,0.0681495,0.117226,0.173439,0.220718,0.23721,0.11564,0.0111944,0.000187903,0.000000511994}};
    */
	vector<double> result(list1.size(), 0.0);
	for (int i = 0; i < list1.size(); i += 1)
	{
		for (int j = 0; j < vectorGaussian[i].size(); j+=1)
		{
			int loc = i + j - vectorGaussian[i].size()/2;
			if (loc >= 0 and loc < result.size())
			{
				result[loc] += list1[i] * vectorGaussian[i][j];
			}
		}
	}
	return result;
}


vector<double> Completeness(double Mag_min, double Mag_max, double interval)
{
	double s0,s1,s2;
	vector<double> vectorCompleteness;
	//detection efficiency
	//The sdss option was choosen, lets use sdss completeness and selection.
	if (sdss_or_pan == 0)
	{
		vectorCompleteness = {0.986088,0.972016,0.957948,0.944999,0.934449,0.927228,0.922852,0.917635,0.902512,0.861945,0.777409,0.640076,0.471073};
		s0 = .9402;
		s1 = 1.6171;
		s2 = 23.5877;
	}
	//The panstarrs option was chosen, lets use panstarrs completeness and selection.
	else
	{
		vectorCompleteness = {0.85222234, 0.85222234, 0.85222234, 0.85222234, 0.852222339999997, 0.852222339999806, 0.8522223399873892, 0.8522223391798939, 0.852222286666763, 0.8522188716397806, 0.8519968439031266, 0.837802165517221, 0.4021192989396328};
		s0 = 0.85222234;
		s1 = 8.34976298;
		s2 = 22.23649929;
	}
	int iterations = (int)((Mag_max - Mag_min) / interval);
	
	vector<double> CC;
    
    
    //adds values of completeness for each iteration in the array of stars
	for (double i = 0; i < iterations; i++)
	{
		double value = s0 / (exp(s1*(i * interval + Mag_min + (interval/2.0) - s2)) + 1); // gives 16.25 - s2, 16.75 - s2, 17.25 - s2, etc. it is using the midpointof each bin as magnitude
		CC.push_back(value);
	} 
	
	//selection efficiency
	
    assert(CC.size() == vectorCompleteness.size());
    
    //Element-wise multiply the input array by the completeness
    for (int i = 0; i < vectorCompleteness.size(); i++)
    {
        CC[i] *= vectorCompleteness[i];  
    }

    return CC;
}

//returns chi-squared value
//DOES NOT WORK WHEN THERE ARE ZEROS IN THE EXPECTED (INPUT) DATA
double chi_squared(vector<double> observed, vector<double> expected)
{
	if (observed.size() != expected.size())
		return -1;
    
	double chi_sq = 0;
    
	for (unsigned int i = 0; i < observed.size(); i++)
	{
		chi_sq += ((observed[i] - expected[i])*(observed[i] - expected[i]))/expected[i];
	}
	return chi_sq; 
}


//function that takes input (2 histograms with lengths) with output (chi-squared value)
//t1 is the guess of star counts, t2 is the expected star counts
//Temporarily add global variable since TAO can only handle objective functions with 1 argument
//t1 should be of a length that when interpolated it is the same length as t2
vector<double> objective_function_t2;
vector<double> storage;
vector<double> input;
double fitness;

double objective_function(const vector<double> &t1)
{	
	//Interpolate guess and store for output
	vector<double> starcounts = interpolate(t1);
	input = t1;
	if (sdss_or_pan == 0 and sdss_include_near == 0)
	{
		starcounts[0] = 0;
		starcounts[1] = 0;
		input[0] = 0;
	}
    
	storage = starcounts;
	
	//Calculate magnitude ranges
	double lowerbound = 16;
	double upperbound = 16 + double(starcounts.size())/2.0;
	
    vector<double> convolved = Discrete_Convolution_2_Odd(starcounts);
    
	if (sdss_or_pan == 0 and sdss_include_near == 0)
	{
		convolved[0] = 0;
		convolved[1] = 0;
	}
	
	vector<double> CC = Completeness(lowerbound, upperbound, .5);

	//because the convolution adds extra bins on the end, this removes the bins
	//to make the two vectors have the same size
	//this is not needed, as long as the input to the convolution is the same size
	//as the completeness array
	while (convolved.size() != CC.size())
	{
		convolved.pop_back();
		convolved.erase(convolved.begin());
	}
	
	vector<double> final_star_count = mult2arrays(convolved, CC);

	double result = chi_squared(final_star_count, objective_function_t2);
    fitness = result;

	return -(result);
}

void optimize(vector<double> t1)
{
    
    std::vector<double> min_bound(t1.size(), 0.5); //recall this makes a vector of size t1.size() full of 0.0
    std::vector<double> max_bound(t1.size(), 100000.0); // was a million
    
    
    vector<double> step_size(t1.size(), 1); //would decreasing the step size help the smoothness problem? (step size was originally 1)
    vector<double> starting_point = t1;
    
	vector<double> final_parameters;
    
	double final_fitness = 0;
	vector <string> args;
	args.push_back("--min_improvement");
	
	
	args.push_back("1e-10");//from e-10
	args.push_back("--gd_quiet");//from e-10
	args.push_back("--max_iterations");
	
	
	args.push_back("1000000");
    synchronous_gradient_descent(args, objective_function, min_bound, max_bound, starting_point, step_size, final_parameters, final_fitness); //added min_bound and max_bound
}

vector<double> startingFitEfficiency(vector<double> startingData)
{
    vector<double> startingFit;
    vector<double> CC = Completeness(16., (startingData.size()/2.0 + 16.), .5);
    
    for (int i = 0; i < startingData.size(); i++)
    {
        startingFit.push_back(startingData[i]/CC[i]);
    }
    
    return startingFit;
}

void recordTranformation(string filePath, vector<double> transformedData, vector<double> startingFit)
{
    ofstream recorded;
    recorded.open(filePath, ofstream::out | ofstream::trunc);
    
    recorded << "Number," << "16," << "16.5," << "17," << "17.5," << "18," << "18.5," << "19," << "19.5," << "20," << "20.5," << "21," << "21.5," << "22," << "22.5" << endl;
    
    recorded << "Transformed Data:";
    for (unsigned int j = 0; j < transformedData.size(); j++)
    {
        recorded << "," << transformedData[j];
    }
    
    recorded << endl << "Starting Fit:";
    for (unsigned int j = 0; j < startingFit.size(); j++)
    {
        recorded << "," << startingFit[j];
    }
    
    recorded.close();
}

void record(string filePath, int line, vector<double> data) //had vector<double> data
{
    ofstream recorded;
    recorded.open(filePath, ofstream::out | ofstream::app);
    
    recorded << endl << to_string(line);
    for (unsigned int j = 0; j < data.size(); j++)
    {
        recorded << "," << data[j];
    }
    
    recorded << "," << fitness;
    
    recorded.close();
}

void record(string filePath, int index, vector<double> data, bool start)
{
	//`cout<<"OUTPUT FILE "<<filePath<<endl;
	ofstream recorded;
    recorded.open(filePath, ofstream::out | ofstream::app);
	if (start)
	{
		if (index == -1)
		{
			recorded<<","<< "16," << "17," << "18," <<"19," << "20," << "21," << "22,"<< "16," << "16.5," << "17," << "17.5," << "18," << "18.5," << "19," << "19.5," << "20," << "20.5," << "21," << "21.5," << "22,"<< "fitness"<<endl;
		}
		else
		{
			recorded<<","<< "16," << "16.5," << "17," << "17.5," << "18," << "18.5," << "19," << "19.5," << "20," << "20.5," << "21," << "21.5," << "22,"<< "fitness"<<endl;
		}
	}
	else
	{
		cout<<index*5<<endl;
		int l = index * 5;
		recorded<<l;
		for (unsigned int j = 0; j < data.size(); j++)
		{
			recorded << "," << data[j];
		}
		recorded<<","<<fitness<<"\n";
	}
	
	recorded.close();
}

//Read data from file
vector<vector<double>> getRealTransformedData (int line1, string filePath)
{
    
    ifstream infile(filePath); // for example
    string line = "";
	vector<vector<double>> values; 
    
	//opens file
	//cout<<filePath<<endl;
    if (infile.is_open())
    {
		//iterates through all lines
		int line_number = 0;
        while (getline(infile, line, '\n'))
        {
			
			//skips the first two lines in the file as they are unrelated to 
			//star counts
			if (line_number <= 1)
			{
				line_number += 1;
				continue; 
			}
			//cout<<line<<endl;
			vector<double> Attempt1;
			//creates a stream from a single line
            stringstream strstr(line);
            string word = "";
            
			//iterates through the new stream line, stopping at each comma
            
			//skip the first element in the line as it will be the angle, not 
			//star count
			getline(strstr,word, ',');
			
			while (getline(strstr,word, ','))
			{
			//skip the first element in the line as it will be the angle, not 
			//star count

				
				
				Attempt1.push_back(stod(word));
				//std::cout<<word<<std::endl;
				
			}
            values.push_back(Attempt1);
        }
    }
    else
    {
        cout << "Failed to open file" << endl;
    }
  
	/*
    vector<double> temp = values[6];
    cout << "number (" << temp.size() << "): ";
    for (int i = 0; i < temp.size(); i++)
    {
    cout << temp[i] << ", ";
    }
    */
    cout << endl;
    return values;

}

//Takes input data from files with leading zeros
//Remove leading and trailing zeros and return clean data from 16 to 22.5
vector<double> trimData(const vector<double>& input)
{
    vector<double> result = vector<double>(13, 0.0);
    for (int i = 0; i < result.size(); i++)
    {
        cout << input[i+32] << ", ";
        result[i] = input[i+32];
    }
    cout << endl;

    return result;
}

unsigned int findLastDelimiter(string input, char delimiter) 
{
    for( unsigned int i = input.size(); i != 0; i-- ) 
    {
        if ( input[i-1] == delimiter )
        {
            return i-1;
        }    
    }
    return input.size();
}



void run(int argc, char** argv) 
{
	//sets random seed
	srand (time(NULL));
	
	
	cout<<"SDSS data (0) or PANSTARRS data (1): ";
	//sdss_or_pan = 1;
	cin >> sdss_or_pan;
	cout << "You entered " << sdss_or_pan <<endl;
	if (sdss_or_pan == 0) {
		cout<< "Using SDSS Completeness and Selection"<<endl;
		cout<<"Exclude innermost bin(s) (0), include innermost bin(s) (1)"<<endl;
		cin >> sdss_include_near;
		if (sdss_include_near == 0) {
			cout<<"excluding innermost bin(s)"<<endl;
		}
		else {
			sdss_include_near = 1;
			cout<<"including innermost bin(s)"<<endl;
		}
		
		
	}
	else if (sdss_or_pan == 1) {
		cout<< "Using PANSTARRS Completeness and Selection"<<endl;
	}
	else {
		cerr << "Input must be 0 or 1!" << endl;
        return;
	}
	
    if(argc < 3) {
        cerr << "Expected Input: <Trim Input: 0/1> <Output File Location(s)> <Input Files>" << endl;
        return;
    }
    for (int i = 3; i < argc; i++)
    {
		
        string filePathInput = argv[i];
        string filePathOutput = string(argv[2]) + &argv[i][findLastDelimiter(argv[i], '/')+1];
        
		string filePathOutputErr = string(argv[2]) +"Error_"+ &argv[i][findLastDelimiter(argv[i], '/')+1];;
		
		cout<<filePathOutputErr<<endl;
		//cout<<&argv[i][findLastDelimiter(argv[i], '/')+1]<<endl;
		//cout<< string(argv[2])<<endl;
		
        //Input data must have odd number of bins
		vector<vector<double>> allData = getRealTransformedData(0, filePathInput);
		
		//overwrites overold file
		ofstream recorded;
		recorded.open(filePathOutput, ofstream::out);
		recorded.close();
		
		ofstream recordedErr;
		recordedErr.open(filePathOutputErr, ofstream::out);
		recordedErr.close();
		
		record(filePathOutput, 0, storage, true);
		record(filePathOutputErr, -1, storage, true);
		for (unsigned int alpha = 0; alpha < allData.size(); alpha += 1)
		{
			vector<double> realTransformedData = allData[alpha];
			if((argv[1]) == string("1"))
			{
				realTransformedData = trimData(realTransformedData);
			}
			assert(realTransformedData.size()%2);
			
			unsigned int numberOfFitParameters = realTransformedData.size()-(realTransformedData.size()/2); 

			vector<double> startingFit = randomVector(1,10000, numberOfFitParameters);
			int totalStars = 0;
			for(unsigned int j = 0; j < startingFit.size(); j++)
			{
				startingFit[j] = realTransformedData[j*2];
				totalStars += startingFit[j];
			}
			vector<double> error;
			if(totalStars >= 30)
			{
				objective_function_t2 = realTransformedData;
				
				if (sdss_or_pan == 0 and sdss_include_near == 0)
				{
					objective_function_t2[0] = .0000001;
					objective_function_t2[1] = .0000001;
				}
				
				optimize(startingFit);

				record(filePathOutput, alpha, storage, false);
				
				for(unsigned int stor = 0; stor < input.size(); stor += 1)
				{
					error.push_back(input[stor]);
				}
				for (unsigned int obj = 0; obj < objective_function_t2.size(); obj+= 1)
				{
					error.push_back(objective_function_t2[obj]);
				}
				//cout<<"length: "<<error.size()<<endl;
				record(filePathOutputErr, alpha, error, false);

			}
			else
			{
				//cout << "No stars in this histogram" << endl;
				vector<double> nothing (realTransformedData.size(), 0);
				error = vector<double> (realTransformedData.size(), 0);
				fitness = 0;
				record(filePathOutput, alpha, nothing, false);
				record(filePathOutputErr, alpha, nothing, false);
			}   
		}			
    }

}
