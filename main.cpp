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
    string artist="";
    float danceability=0;
    float energy=0;
    int popularity=0;
    int isExplicit=0;
};

void mergeSort(vector<Song>songs, int number, int length);
void merge(vector<Song>songs, int number, int half, int length);
void shellSort(vector<Song>songs);

void mergeSort(vector<Song>songs,int number, int length)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    if(number<length)
    {
        int half = number+ (length-1) /2;
        mergeSort(songs, number, half);
        mergeSort(songs, half+1, length);
        merge(songs, number, half, length);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Merge Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
void merge(vector<Song>songs, int number, int half, int length)
{
    int first = half-number+1;
    int second = length-half;
    int i;
    int j;
    int k;
    //temporary vectors
    vector<Song>firstVec;
    vector<Song>secondVec;
    for(i=0; i<first; i++)
    {
        firstVec.at(i)=songs.at(number+i);
    }
    for(j=0; j<second; j++)
    {
        secondVec.at(j)=songs.at(half+number+j);
    }
    i=0;
    j=0;
    k=1;
    while(i<first && j<second)
    {
        if(firstVec.at(i).popularity <= secondVec.at(j).popularity)
        {
            songs.at(k)=firstVec.at(i);
            i++;
        }
        else
        {
            songs.at(k)=secondVec.at(j);
            j++;
        }
        k++;
    }
    while(i<first)
    {
        songs.at(k)=firstVec.at(i);
        i++;
        k++;
    }
    while(j<second)
    {
        songs.at(k)=secondVec.at(j);
        j++;
        k++;
    }
}
void shellSort(vector<Song>songs)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    int  length=songs.size();
    for(int gap=length/2; gap>0; gap/=2)
    {
        for(int i=gap; i<length; i++)
        {
            int key=songs.at(i).popularity;
            int j=i;
            while(j>=gap && songs.at(j-gap).popularity>key)
            {
                songs.at(j)=songs.at(j-gap);
                j-=gap;
            }
            songs.at(j).popularity=key;
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}


int main()
{
    //.5 1
    unordered_map<float,unordered_map<float,unordered_map<int, vector<Song>>>>nestedMap;
    ifstream data("/Users/neevasethi/CLionProjects/DSA_project3_readingSpotifyData/data.csv");
    //if(!ip.is_open()) cout << "ERROR: file open" << endl;
    int n=0;
    while(n<10000)
    {
        n++;
        Song newSong;
        vector<string>dataInput;
            string danceability;
            getline(data,danceability,',');
            try
            {
                stof(danceability.substr(3));
            }
            catch (const std::invalid_argument& ia)
            {
                break;
            }
            if(danceability.at(0)=='"')
            {
                danceability=danceability.substr(3);
            }
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
        //now add the new song to the correct place in the map
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
        vector<Song>currentSongs = nestedMap[danceInt][energyInt][newSong.isExplicit];
        currentSongs.push_back(newSong);
        nestedMap[danceInt][energyInt][newSong.isExplicit] = currentSongs;
    }
    cout << "Your playlist is being selected from " << to_string(n) << " songs!"<<endl;
    //the whole map is initialized and loaded now
    //ask the user what they would like their playlist to look like
    //1.danceability
    //2.energy
    //3.isExplicit
    //4.name
    //5. popularity
    //in a bool, 0 =false, 1=true
    cin.clear();
    string dancing;
    cout << "Would you like your playlist to be danceable? 1= danceable 0=not danceable" << endl;
    cin >> dancing;
    int dancingInt = stoi(dancing);
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
    cout << "Thank you for your responses! Here is a customized playlist based on your preferences: " << endl;
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
    vector<Song>songs = nestedMap[dancingConversion][energyConversion][explicitSongsInt];
    vector<Song>songsCopy=songs;

    //calling the shell sort function
    //shell code needs to be swtiched so it goes from most to least popular
    shellSort(songsCopy);
    int j=1;
    for(int i=songsCopy.size()-1; i>songsCopy.size()-26; i--)
    {
        cout<< to_string(j) << ". " << songsCopy.at(i).name << endl;
        j++;
    }
    //call the merge sort function
    mergeSort(songs,0,songs.size()-1);
    for(int i=0; i<25; i++)
    {
        cout<< songs.at(i).name << endl;
    }
}
