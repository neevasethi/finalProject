#include <SFML/Graphics.hpp> //whole bunch of other include files
#include "Button.h"
#include "TextureManager.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std;



vector<int> loadScreen(){

	//SFML file managing and loading from COP3503 Minesweeper Project


	//setup
	sf::RenderWindow window(sf::VideoMode(1350, 650), "Playlist Generator!");
	
	//clickable buttons for input
	Button yes(TextureManager::GetTexture("YES"));
	Button no(TextureManager::GetTexture("NO1"));
	Button create(TextureManager::GetTexture("create"));
	create.setPosition({window.getSize().x/5.0f,window.getSize().y/1.75f});
	yes.setPosition({ window.getSize().x / 1.3f, window.getSize().y /1.9f });
	no.setPosition({ window.getSize().x / 1.3f, window.getSize().y / 1.5f });

	vector<Button>buttons;

	buttons.push_back(create);
	buttons.push_back(yes);
	buttons.push_back(no);

	//load all start screens and backgrounds into queue
	queue<sf::Sprite>pages;

	TextureManager::LoadTexture("background1");
	sf::Sprite background(TextureManager::GetTexture("background1"));
	pages.push(background);

	TextureManager::LoadTexture("songChoice");
	sf::Sprite songC(TextureManager::GetTexture("songChoice"));
	pages.push(songC);

	TextureManager::LoadTexture("background2");
	sf::Sprite background2(TextureManager::GetTexture("background2"));
	pages.push(background2);

	TextureManager::LoadTexture("background3");
	sf::Sprite background3(TextureManager::GetTexture("background3"));
	pages.push(background3);

	TextureManager::LoadTexture("background4");
	sf::Sprite background4(TextureManager::GetTexture("background4"));
	pages.push(background4);

	TextureManager::LoadTexture("background5");
	sf::Sprite background5(TextureManager::GetTexture("background5"));
	pages.push(background5);

	TextureManager::LoadTexture("background6");
	sf::Sprite background6(TextureManager::GetTexture("background6"));
	pages.push(background6);

	TextureManager::LoadTexture("background7");
	sf::Sprite background7(TextureManager::GetTexture("background7"));
	pages.push(background7);

	TextureManager::LoadTexture("background8");
	sf::Sprite background8(TextureManager::GetTexture("background8"));
	pages.push(background8);
	

	vector<sf::Sprite>songChoices;
	TextureManager::LoadTexture("25");
	sf::Sprite choice1(TextureManager::GetTexture("25"));
	choice1.setPosition({ window.getSize().x / 3.0f,window.getSize().y / 4.0f });
	songChoices.push_back(choice1);

	TextureManager::LoadTexture("50");
	sf::Sprite choice2(TextureManager::GetTexture("50"));
	choice2.setPosition({ window.getSize().x / 2.0f,window.getSize().y / 3.0f });
	songChoices.push_back(choice2);


	TextureManager::LoadTexture("100");
	sf::Sprite choice3(TextureManager::GetTexture("100"));
	choice3.setPosition({ window.getSize().x /1.5f,window.getSize().y / 4.0f });
	songChoices.push_back(choice3);

	vector<Button>mostImport;
	TextureManager::LoadTexture("danceability");
	Button d(TextureManager::GetTexture("danceability"));
	d.setPosition({ window.getSize().x / 3.0f,window.getSize().y / 1.5f });
	mostImport.push_back(d);

	TextureManager::LoadTexture("energy");
	Button e(TextureManager::GetTexture("energy"));
	e.setPosition({ window.getSize().x / 2.0f,window.getSize().y / 1.5f });
	mostImport.push_back(e);


	TextureManager::LoadTexture("popularity");
	Button p(TextureManager::GetTexture("popularity"));
	p.setPosition({ window.getSize().x / 1.5f,window.getSize().y / 1.5f });
	mostImport.push_back(p);


	vector<int> choices;

	while (window.isOpen()){		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				sf::Vector2f fPosition(position.x, position.y);
				if (event.mouseButton.button == sf::Mouse::Left) {
                    if (create.getGlobalBounds().contains(fPosition) && pages.size() > 1) {
                        //create button clicked-> customize screen
                        pages.pop();
                    }
                    else if (pages.size() < 9 && pages.size() > 1) {
                        pages.pop();
                    }

					if (yes.getGlobalBounds().contains(fPosition))
						choices.push_back(1);
					else if (no.getGlobalBounds().contains(fPosition))
						choices.push_back(0);
					else if (choice1.getGlobalBounds().contains(fPosition))
						choices.push_back(25);
					else if (choice2.getGlobalBounds().contains(fPosition))
						choices.push_back(50);
					else if (choice3.getGlobalBounds().contains(fPosition))
						choices.push_back(100);
					else if (p.getGlobalBounds().contains(fPosition))
						choices.push_back(0);
					else if (e.getGlobalBounds().contains(fPosition))
						choices.push_back(1);
					else if (d.getGlobalBounds().contains(fPosition))
						choices.push_back(2);

					
					
					
				}
				
			}
		}

		window.draw(pages.front());
		if(pages.size()==9)
			window.draw(buttons.front());
		else if (pages.size() == 8) {
			for (int i = 0; i < songChoices.size(); i++)
				window.draw(songChoices[i]);
		}
		else if (pages.size() == 2) {
			for (int i = 0; i < mostImport.size(); i++)
				window.draw(mostImport[i]);
		}
		else if(pages.size() <7 && pages.size() != 1){
			for (int i = 1; i < buttons.size(); i++)
				window.draw(buttons[i]);
		}	

		window.display();
	}
	
	//choices vector will be in the following order

	/*
	1. How many songs (25,50,100)
	2. Do you want to dance to music
	3. Do you want high energy music
	4. Do you want popular music
	5. Explicit yes or no
	6. Which is the most important to you (0,1,2)
		0:popularity
		1:energy
		2:danceability
	*/

	TextureManager::Clear();
	return choices;
}
class Song
{
public:
    string name = "";
    float danceability = 0;
    float energy = 0;
    int popularity = 0;
    int isExplicit = 0;
};
//defining functions
void swap(vector<Song>& songs, int song1, int song2);
void print(vector<Song>&songs, int n, int characteristic);
void callingQuickSort(vector<Song>& songs, int low, int high, int characteristic);
void quickSort(vector<Song>& songs, int low, int high, int characteristic);
int partition(vector<Song>& songs, int low, int high, int characteristic);
void shellSort(vector<Song>& songs, int n, int characteristic);
void heapSort(vector<Song>& songs, int n, int characteristic);
void heapify(vector<Song>& songs, int n, int m, int characteristic);

//helper function to call quicksort so that the time is not printed out multiple times
void callingQuickSort(vector<Song>& songs, int low, int high, int characteristic)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    quickSort(songs, low, high, characteristic);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Using Quick Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
//quick sort function
void quickSort(vector<Song>& songs, int low, int high, int characteristic)
{
    if (low < high)
    {
        int part = partition(songs, low, high, characteristic);
        quickSort(songs, low, part - 1, characteristic);
        quickSort(songs, part + 1, high, characteristic);
    }
}
//quicksort helper partitioning function
int partition(vector<Song>& songs, int low, int high, int characteristic)
{
    //sorting by danceability
    if (characteristic == 1)
    {
        //danceability
        Song pivot = songs.at(high);
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++)
        {
            if (songs.at(j).danceability < pivot.danceability)
            {
                i++;
                swap(songs, i, j);
            }
        }
        swap(songs, i + 1, high);
        return(i + 1);
    }
    //sorting by energy
    else if (characteristic == 2)
    {
        //energy
        Song pivot = songs.at(high);
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++)
        {
            if (songs.at(j).energy < pivot.energy)
            {
                i++;
                swap(songs, i, j);
            }
        }
        swap(songs, i + 1, high);
        return(i + 1);
    }
    //sorting by popularity
    else
    {
        //popularity
        Song pivot = songs.at(high);
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++)
        {
            if (songs.at(j).popularity < pivot.popularity)
            {
                i++;
                swap(songs, i, j);
            }
        }
        swap(songs, i + 1, high);
        return(i + 1);
    }
}
//shell sort function
void shellSort(vector<Song>& songs, int n, int characteristic)
{
    //sorting by danceability
    if (characteristic == 1)
    {
        //sort by danceability
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Song temp = songs.at(i);
                int j;
                for (j = i; j > gap && songs.at(j - gap).danceability > temp.danceability; j -= gap)
                {
                    songs.at(j) = songs.at(j - gap);
                }
                songs.at(j) = temp;
            }

        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds!" << endl;

    }
    //sorting by energy
    else if (characteristic == 2)
    {
        //sort by energy
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Song temp = songs.at(i);
                int j;
                for (j = i; j > gap && songs.at(j - gap).energy > temp.energy; j -= gap)
                {
                    songs.at(j) = songs.at(j - gap);
                }
                songs.at(j) = temp;
            }

        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds" << endl;
    }
    //sorting by popularity
    else
    {
        //sort by popularity
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Song temp = songs.at(i);
                int j;
                for (j = i; j > gap && songs.at(j - gap).popularity > temp.popularity; j -= gap)
                {
                    songs.at(j) = songs.at(j - gap);
                }
                songs.at(j) = temp;
            }

        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Using Shell Sort, your playlist was generated in " << duration << " microseconds!" << endl;
    }
}
//heap sort function
void heapSort(vector<Song>& songs, int n, int characteristic)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(songs, n, i, characteristic);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(songs, 0, i);
        heapify(songs, i, 0, characteristic);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Using Heap Sort, your playlist was generated in " << duration << " microseconds!" << endl;
}
//heap sort helper heapify function
void heapify(vector<Song>& songs, int n, int m, int characteristic)
{
    //sorting by danceability
    if (characteristic == 1)
    {
        int largest = m;
        int leftChild = (2 * m) + 1;
        int rightChild = (2 * m) + 2;
        if (leftChild<n && songs.at(leftChild).danceability>songs.at(largest).danceability)
        {
            largest = leftChild;
        }
        if (rightChild<n && songs.at(rightChild).danceability>songs.at(largest).danceability)
        {
            largest = rightChild;
        }
        if (largest != m)
        {
            swap(songs, m, largest);
            heapify(songs, n, largest, characteristic);
        }
    }
    //sorting by energy
    else if (characteristic == 2)
    {
        int largest = m;
        int leftChild = (2 * m) + 1;
        int rightChild = (2 * m) + 2;
        if (leftChild<n && songs.at(leftChild).energy>songs.at(largest).energy)
        {
            largest = leftChild;
        }
        if (rightChild<n && songs.at(rightChild).energy>songs.at(largest).energy)
        {
            largest = rightChild;
        }
        if (largest != m)
        {
            swap(songs, m, largest);
            heapify(songs, n, largest, characteristic);
        }
    }
    //sorting by popularity
    else
    {
        int largest = m;
        int leftChild = (2 * m) + 1;
        int rightChild = (2 * m) + 2;
        if (leftChild<n && songs.at(leftChild).popularity>songs.at(largest).popularity)
        {
            largest = leftChild;
        }
        if (rightChild<n && songs.at(rightChild).popularity>songs.at(largest).popularity)
        {
            largest = rightChild;
        }
        if (largest != m)
        {
            swap(songs, m, largest);
            heapify(songs, n, largest, characteristic);
        }
    }
}

//helper functions for all sorting
//swap: used to swap two songs in the vector
void swap(vector<Song>& songs, int song1, int song2)
{
    Song holder = songs.at(song1);
    songs.at(song1) = songs.at(song2);
    songs.at(song2) = holder;
}
//print: used to print songs for user
void print(vector<Song>&songs, int n, int characteristic)
{
    int k = 1;
    //print for danceability
    if (characteristic == 2)
    {
        for (int i = songs.size() - 1; i > songs.size() - n - 1; i--)
        {
            cout << to_string(k) << ". " << songs.at(i).name << " / Danceability: " << songs.at(i).danceability << endl;
            k++;
        }
    }
    //print for energy
    else if (characteristic == 1)
    {
        for (int i = songs.size() - 1; i > songs.size() - n - 1; i--)
        {
            cout << to_string(k) << ". " << songs.at(i).name << " / Energy: " << songs.at(i).energy << endl;
            k++;
        }
    }
    //print out for popularity
    else if (characteristic == 0)
    {
        for (int i = songs.size() - 1; i > songs.size() - n - 1; i--)
        {
            cout << to_string(k) << ". " << songs.at(i).name << " / Popularity: " << songs.at(i).popularity << endl;
            k++;
        }
    }
}

int main()
{
    //nested map where the data read in will be stored
    unordered_map<float, unordered_map<float, unordered_map<int, vector<Song>>>>nestedMap;
    ifstream data("C:/Users/15613/source/repos/playlistGenerator/data.csv");
    int n = 0;
    while (n < 120000)
    {
        n++;
        Song newSong;
        vector<string>dataInput;
        string danceability;
        getline(data, danceability, ',');
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
        if (danceability.at(0) == '"')
        {
            danceability = danceability.substr(3);
        }
        //importing and storing different data values below
        newSong.danceability = stof(danceability);
        string energy;
        getline(data, energy, ',');
        newSong.energy = stof(energy);
        string isExplicit;
        getline(data, isExplicit, ',');
        newSong.isExplicit = stoi(isExplicit);
        string name;
        getline(data, name, ',');
        newSong.name = name;
        string popularity;
        getline(data, popularity, ',');
        popularity = popularity.substr(1);
        newSong.popularity = stoi(popularity);
        //now add the new song to the correct place in the map by converting to data point to select places in the map
        //any song with danceability<.5 will be stored at [.5] in the first of the nested maps
        //any song with danceability >.5 will be stored at [1] in the first map
        //any song with energy<.5 will be stored at [.5] in the second of the nested maps
        //any song with energy >.5 will be stored at [1] in the second map
        float danceInt;
        float energyInt;
        if (newSong.danceability <= .5)
        {
            danceInt = .5;
        }
        else
        {
            danceInt = 1;
        }
        if (newSong.energy <= .5)
        {
            energyInt = .5;
        }
        else
        {
            energyInt = 1;
        }
        //if a song is not explicit, it will be stored in both ending vectors of the map
        //is a song is explcit, it will only be stored in the [1] key of the last map
        if (stoi(isExplicit) == 0)
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
    cout << "Your playlists are being selected from 120000 songs!" << endl;
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
    vector<int> responses;
    /*
    1. How many songs (25,50,100)
    2. Do you want to dance to music
    3. Do you want high energy music
    4. Do you want popular music
    5. Explicit yes or no
    6. Which is the most important to you (0,1,2)
        0:popularity
        1:energy
        2:danceability
    */
    for (int i = 0; i < numPlaylists; i++)
    {
        responses = loadScreen();
        
        //based on what the user entered above, either call [.5] or [1] in the first and second map that store danceability and energy
        //user input only needs to be convereted if it was zero...no [0] key in the map (only [.5] and [1])
        float dancingConversion = float(responses[1]);
        if (responses[1] == 0)
        {
            dancingConversion = .5;
        }
        float energyConversion = float(responses[2]);
        if (responses[2] == 0)
        {
            //low energy
            energyConversion = .5;
        }
        //accessing all the songs that match the user criteria
        vector<Song>songs = nestedMap[dancingConversion][energyConversion][responses[4]];
       
        //if there are not enough songs matching their criteria, tell them to enter a lower number
        if (responses[0] > songs.size())
        {
            cout << "There will only be " << to_string(songs.size()) << " songs that fit your criteria for your playlist." << endl;
            
        }

        
        cout << "Thank you for your responses! Here is a customized playlist based on your preferences: " << endl;
        vector<Song>quickSortSongs = nestedMap[dancingConversion][energyConversion][responses[4]];
        vector<Song>shellSortSongs = nestedMap[dancingConversion][energyConversion][responses[4]];
        vector<Song>heapSortSongs = nestedMap[dancingConversion][energyConversion][responses[4]];
        //calling the shell sort function
        shellSort(shellSortSongs, shellSortSongs.size(), responses[responses.size()-1]);
        print(shellSortSongs, responses[0], responses[responses.size() - 1]);
        cout << endl;
        cout << endl;
        //call the merge sort function
        callingQuickSort(quickSortSongs, 0, songs.size() - 1, responses[responses.size() - 1]);
        print(quickSortSongs, responses[0], responses[responses.size() - 1]);
        cout << endl;
        cout << endl;
        //call heap sort function
        heapSort(heapSortSongs, songs.size(), responses[responses.size() - 1]);
        print(heapSortSongs, responses[0], responses[responses.size() - 1]);
        cout << endl;
        cout << endl;
    }
    cout << "Thank you for customizing playlists with us today!" << endl;
}





