#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std;


class Song
{
public:
    string name="";
    float danceability=0;
    float energy=0;
    int popularity=0;
    int isExplicit=0;
};
//defining functions
void swap(vector<Song>&songs,int song1, int song2);
void print(vector<Song>songs,int n, int characteristic);

void callingQuickSortPop(vector<Song>&songs,int low, int high);
void quickSortPop(vector<Song>&songs,int low, int high);
int partitionPop(vector<Song>&songs, int low, int high);
void shellSortPop(vector<Song>&songs, int n);
void heapSortPop(vector<Song>&songs, int n);
void heapifyPop(vector<Song>&songs, int n, int m);

void callingQuickSortDance(vector<Song>&songs,int low, int high);
void quickSortDance(vector<Song>&songs,int low, int high);
int partitionDance(vector<Song>&songs, int low, int high);
void shellSortDance(vector<Song>&songs,int n);
void heapSortDance(vector<Song>&songs, int n);
void heapifyDance(vector<Song>&songs, int n, int m);

void callingQuickSortEnergy(vector<Song>&songs,int low, int high);
void quickSortEnergy(vector<Song>&songs,int low, int high);
int partitionEnergy(vector<Song>&songs, int low, int high);
void shellSortEnergy(vector<Song>&songs,int n);
void heapSortEnergy(vector<Song>&songs, int n);
void heapifyEnergy(vector<Song>&songs, int n, int m);

//helper functions for all sorting
//swap: used to swap two songs in the vector
void swap(vector<Song>&songs,int song1, int song2)
{
    Song holder= songs.at(song1);
    songs.at(song1)=songs.at(song2);
    songs.at(song2)=holder;
}
//print: used to print songs for user
void print(vector<Song>songs,int n, int characteristic)
{
    int k=1;
    //print for danceability
    if(characteristic==1)
    {
        for(int i=songs.size()-1; i>songs.size()-n-1; i--)
        {
            cout<< to_string(k) << ". " << songs.at(i).name << " / Danceability: " << songs.at(i).danceability <<endl;
            k++;
        }
    }
    //print for energy
    else if(characteristic==2)
    {
        for(int i=songs.size()-1; i>songs.size()-n-1; i--)
        {
            cout<< to_string(k) << ". " << songs.at(i).name << " / Energy: " << songs.at(i).energy <<endl;
            k++;
        }
    }
    //print out for popularity
    else if(characteristic==3)
    {
        for(int i=songs.size()-1; i>songs.size()-n-1; i--)
        {
            cout<< to_string(k) << ". " << songs.at(i).name << " / Popularity: " << songs.at(i).popularity <<endl;
            k++;
        }
    }
}

//use when sorting by popularity
void callingQuickSortPop(vector<Song>&songs,int low, int high)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    quickSortPop(songs,low,high);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Quick Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
//quick sort algorithm
void quickSortPop(vector<Song>&songs,int low, int high)
{
    if(low<high)
    {
        int part=partitionPop(songs, low,high);
        quickSortPop(songs,low,part-1);
        quickSortPop(songs,part+1,high);
    }
}
//partitioning for quick sort based on popularity
int partitionPop(vector<Song>&songs, int low, int high)
{
    Song pivot=songs.at(high);
    int i=(low-1);
    for(int j=low; j<=high-1;j++)
    {
        if(songs.at(j).popularity<pivot.popularity)
        {
            i++;
            swap(songs,i,j);
        }
    }
    swap(songs,i+1,high);
    return(i+1);
}
//shell sort algorithm based on popularity
void shellSortPop(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int gap=n/2; gap>0; gap/=2)
    {
        for(int i=gap; i<n; i+=1)
        {
            Song temp=songs.at(i);
            int j;
            for(j=i; j>gap && songs.at(j-gap).popularity>temp.popularity; j-=gap)
            {
                songs.at(j)=songs.at(j-gap);
            }
            songs.at(j)=temp;
        }

    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
//heap sort algorithm base don popularity
void heapSortPop(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i=n/2-1; i>=0 ; i--)
    {
        heapifyPop(songs,n,i);
    }
    for(int i=n-1; i>0; i--)
    {
        swap(songs,0,i);
        heapifyPop(songs,i,0);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Heap Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
//heapify algorithm based on popularity
void heapifyPop(vector<Song>&songs, int n, int m)
{
    int largest=m;
    int leftChild=(2*m)+1;
    int rightChild=(2*m)+2;
    if(leftChild<n && songs.at(leftChild).popularity>songs.at(largest).popularity)
    {
        largest=leftChild;
    }
    if(rightChild<n && songs.at(rightChild).popularity>songs.at(largest).popularity)
    {
        largest=rightChild;
    }
    if(largest!=m)
    {
        swap(songs,m,largest);
        heapifyPop(songs,n,largest);
    }
}

//when sorting by danceability
void callingQuickSortDance(vector<Song>&songs,int low, int high)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    quickSortDance(songs,low,high);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Quick Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void quickSortDance(vector<Song>&songs,int low, int high)
{
    if(low<high)
    {
        int part=partitionDance(songs, low,high);
        quickSortDance(songs,low,part-1);
        quickSortDance(songs,part+1,high);
    }
}
int partitionDance(vector<Song>&songs, int low, int high)
{
    Song pivot=songs.at(high);
    int i=(low-1);
    for(int j=low; j<=high-1;j++)
    {
        if(songs.at(j).danceability<pivot.danceability)
        {
            i++;
            swap(songs,i,j);
        }
    }
    swap(songs,i+1,high);
    return(i+1);
}
void shellSortDance(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int gap=n/2; gap>0; gap/=2)
    {
        for(int i=gap; i<n; i+=1)
        {
            Song temp=songs.at(i);
            int j;
            for(j=i; j>gap && songs.at(j-gap).danceability>temp.danceability; j-=gap)
            {
                songs.at(j)=songs.at(j-gap);
            }
            songs.at(j)=temp;
        }

    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void heapSortDance(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i=n/2-1; i>=0 ; i--)
    {
        heapifyDance(songs,n,i);
    }
    for(int i=n-1; i>0; i--)
    {
        swap(songs,0,i);
        heapifyDance(songs,i,0);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Heap Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void heapifyDance(vector<Song>&songs, int n, int m)
{
    int largest=m;
    int leftChild=(2*m)+1;
    int rightChild=(2*m)+2;
    if(leftChild<n && songs.at(leftChild).danceability>songs.at(largest).danceability)
    {
        largest=leftChild;
    }
    if(rightChild<n && songs.at(rightChild).danceability>songs.at(largest).danceability)
    {
        largest=rightChild;
    }
    if(largest!=m)
    {
        swap(songs,m,largest);
        heapifyDance(songs,n,largest);
    }
}

//when sorting by energy
void callingQuickSortEnergy(vector<Song>&songs,int low, int high)
{
    //used to call quick sort so that the time it took to generate does not print out multiple times
    auto t1 = std::chrono::high_resolution_clock::now();
    quickSortEnergy(songs,low,high);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Quick Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void quickSortEnergy(vector<Song>&songs,int low, int high)
{
    if(low<high)
    {
        int part=partitionEnergy(songs, low,high);
        quickSortEnergy(songs,low,part-1);
        quickSortEnergy(songs,part+1,high);
    }
}
int partitionEnergy(vector<Song>&songs, int low, int high)
{
    //partition function for quick sort
    Song pivot=songs.at(high);
    int i=(low-1);
    for(int j=low; j<=high-1;j++)
    {
        if(songs.at(j).energy<pivot.energy)
        {
            i++;
            swap(songs,i,j);
        }
    }
    swap(songs,i+1,high);
    return(i+1);
}
void shellSortEnergy(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int gap=n/2; gap>0; gap/=2)
    {
        for(int i=gap; i<n; i+=1)
        {
            Song temp=songs.at(i);
            int j;
            for(j=i; j>gap && songs.at(j-gap).energy>temp.energy; j-=gap)
            {
                songs.at(j)=songs.at(j-gap);
            }
            songs.at(j)=temp;
        }

    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds" << endl;
}
void heapSortEnergy(vector<Song>&songs, int n)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i=n/2-1; i>=0 ; i--)
    {
        heapifyEnergy(songs,n,i);
    }
    for(int i=n-1; i>0; i--)
    {
        swap(songs,0,i);
        heapifyEnergy(songs,i,0);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Heap Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void heapifyEnergy(vector<Song>&songs, int n, int m)
{
    int largest=m;
    int leftChild=(2*m)+1;
    int rightChild=(2*m)+2;
    if(leftChild<n && songs.at(leftChild).energy>songs.at(largest).energy)
    {
        largest=leftChild;
    }
    if(rightChild<n && songs.at(rightChild).energy>songs.at(largest).energy)
    {
        largest=rightChild;
    }
    if(largest!=m)
    {
        swap(songs,m,largest);
        heapifyEnergy(songs,n,largest);
    }
}

int main()
{
    //nested map where the data read in will be stored
    unordered_map<float,unordered_map<float,unordered_map<int, vector<Song>>>>nestedMap;
    ifstream data("/Users/neevasethi/CLionProjects/DSA_project3_readingSpotifyData/data.csv");
    int n=0;
    while(n<120000)
    {
        n++;
        Song newSong;
        vector<string>dataInput;
            string danceability;
            getline(data,danceability,',');
            //the input between popularity and danceability contaians characteres that we do not want
            //if there are no valid characters, enter the catch statement which indicates we are done importing songs
            try
            {
                stof(danceability.substr(3));
            }
            catch (const std::invalid_argument& ia)
            {
                break;
            }
            //if the try/catch statement is passed, then the next piece of data will begin with a quotation mark
            if(danceability.at(0)=='"')
            {
                danceability=danceability.substr(3);
            }
            //importing and storing different data values below
            newSong.danceability=stof(danceability);
            string energy;
            getline(data,energy,',');
            newSong.energy=stof(energy);
            string isExplicit;
            getline(data,isExplicit,',');
            newSong.isExplicit=stoi(isExplicit);
            string name;
            getline(data,name,',');
            newSong.name=name;
            string popularity;
            getline(data,popularity,',');
            popularity=popularity.substr(1);
            newSong.popularity=stoi(popularity);
        //now add the new song to the correct place in the map by converting to data point to select places in the map
        //any song with danceability<.5 will be stored at [.5] in the first of the nested maps
        //any song with danceability >.5 will be stored at [1] in the first map
        //any song with energy<.5 will be stored at [.5] in the second of the nested maps
        //any song with energy >.5 will be stored at [1] in the second map
        float danceInt;
        float energyInt;
        if(newSong.danceability<=.5)
        {
            danceInt=.5;
        }
        else
        {
            danceInt=1;
        }
        if(newSong.energy<=.5)
        {
            energyInt=.5;
        }
        else
        {
            energyInt=1;
        }
        //if a song is not explicit, it will be stored in both ending vectors of the map
        //is a song is explcit, it will only be stored in the [1] key of the last map
        if(stoi(isExplicit)==0)
        {
            //only non-explicit songs are placed here
            vector<Song>currentSongs = nestedMap[danceInt][energyInt][0];
            currentSongs.push_back(newSong);
            nestedMap[danceInt][energyInt][0] = currentSongs;
        }
        //explicit and non-explicit songs can be placed here
        vector<Song>currentSongs = nestedMap[danceInt][energyInt][1];
        currentSongs.push_back(newSong);
        nestedMap[danceInt][energyInt][1] = currentSongs;
    }
    cout << "Your playlists are being selected from " << to_string(n) << " songs!"<<endl;
    int numPlaylists;
    cout << "How many playlists would you like to create?" << endl;
    cin >> numPlaylists;
    //the whole map is initialized and loaded now
    //ask the user what they would like their playlist to look like
    //1.danceability
    //2.energy
    //3.isExplicit
    //4.name
    //5. popularity
    for(int i=0; i<numPlaylists; i++)
    {
        cin.clear();
        string dancing;
        cout << "Would you like your playlist to be danceable? 1= danceable 0=not danceable" << endl;
        cin >> dancing;
        int dancingInt = stoi(dancing);
        //make sure the user input is valid
        while(dancingInt!=1)
        {
            while(dancingInt!=0)
            {
                cout << "Invalid answer! Please enter either 1 for danceable or 0 for not danceable" << endl;
                cin.clear();
                cin >> dancing;
                dancingInt=stoi(dancing);
                if(dancingInt==1)
                {
                    break;
                }
            }
            break;
        }
        cin.clear();
        string energy;
        cout << "Would you like your playlist to be high energy? 1= high energy 0=low energy" << endl;
        cin >> energy;
        int energyInt=stoi(energy);
        //make sure the user input is valid
        while(energyInt!=1)
        {
            while(energyInt!=0)
            {
                cout << "Invalid answer! Please enter either 1 for high energy or 0 for low energy" << endl;
                cin.clear();
                cin >> energy;
                energyInt=stoi(energy);
                if(energyInt==1)
                {
                    break;
                }
            }
            break;
        }
        cin.clear();
        string explicitSongs;
        cout << "Is it okay for your playlist to contain explicit songs? Enter 1 to allow explicit songs or 0 for no explicit songs" << endl;
        cin >> explicitSongs;
        int explicitSongsInt=stoi(explicitSongs);
        //make sure the user input is valid
        while(explicitSongsInt!=1)
        {
            while(explicitSongsInt!=0)
            {
                cout << "Invalid answer! Please enter either 1 to allow explicit songs or 0 for no explicit songs" << endl;
                cin >> explicitSongs;
                explicitSongsInt=stoi(explicitSongs);
                if(explicitSongsInt==1)
                {
                    break;
                }
            }
            break;
        }
        //based on what the user entered above, either call [.5] or [1] in the first and second map that store danceability and energy
        //user input only needs to be convereted if it was zero...no [0] key in the map (only [.5] and [1])
        float dancingConversion= float(dancingInt);
        if(dancingInt==0)
        {
            dancingConversion=.5;
        }
        float energyConversion = float(energyInt);
        if(energyInt==0)
        {
            //low energy
            energyConversion=.5;
        }
        //accessing all the songs that match the user criteria
        vector<Song>songs = nestedMap[dancingConversion][energyConversion][explicitSongsInt];
        cin.clear();
        string numSongs;
        cout << "How many songs would you like your playlist to contain?" << endl;
        cin>>numSongs;
        int numSongsInt=stoi(numSongs);
        //if there are not enough songs matching their criteria, tell them to enter a lower number
        while(numSongsInt>songs.size())
        {
                cout << "There are only " << to_string(songs.size()) << " songs that fit your criteria! Please choose a lower number" << endl;
                cin >>numSongs;
                numSongsInt=stoi(numSongs);
                if(numSongsInt<songs.size())
                {
                    break;
                }
            break;
        }
        int mainCharacteristic;
        cout << "Which song characteristic do you want most in your playlist? This is how your playlist will be sorted! \n 1. Danceability \n 2. Energy \n 3. Popularity" << endl;
        cin>>mainCharacteristic;
        //print(songs,25);
        cout << "Thank you for your responses! Here is a customized playlist based on your preferences: " << endl;
        vector<Song>quickSortSongs=nestedMap[dancingConversion][energyConversion][explicitSongsInt];
        vector<Song>shellSortSongs=nestedMap[dancingConversion][energyConversion][explicitSongsInt];
        vector<Song>heapSortSongs=nestedMap[dancingConversion][energyConversion][explicitSongsInt];
        //sorting based on danceability
        if(mainCharacteristic==1)
        {
            //calling the shell sort function
            shellSortDance(shellSortSongs,shellSortSongs.size());
            print(shellSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call the merge sort function
            callingQuickSortDance(quickSortSongs,0,songs.size()-1);
            print(quickSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call heap sort function
            heapSortDance(heapSortSongs,songs.size());
            print(heapSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
        }
        //sorting based on energy
        else if(mainCharacteristic==2)
        {
            cout << "getting here" << endl;
            //calling the shell sort function
            shellSortEnergy(shellSortSongs, shellSortSongs.size());
            print(shellSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call the merge sort function
            callingQuickSortEnergy(quickSortSongs,0,songs.size()-1);
            print(quickSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call heap sort function
            heapSortEnergy(heapSortSongs,songs.size());
            print(heapSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
        }
        //sorting based on popularity
        else if(mainCharacteristic==3)
        {
            //calling the shell sort function
            shellSortPop(shellSortSongs,shellSortSongs.size());
            print(shellSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call the merge sort function
            callingQuickSortPop(quickSortSongs,0,songs.size()-1);
            print(quickSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
            //call heap sort function
            heapSortPop(heapSortSongs,songs.size());
            print(heapSortSongs,numSongsInt,mainCharacteristic);
            cout << endl;
            cout << endl;
        }
    }
    cout << "Thank you for customizing playlists with us today!" << endl;
}
