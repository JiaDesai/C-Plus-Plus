#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {

private: 
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
  }
PlaylistNode()
: uniqueID("none");
  songName("none");
  artistName("none");
  songLength(0);
  nextNodePtr(nullptr);
  {}

PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength)
: uniqueID(uniqueID), 
  songName(songName),        
  artistName(artistName), 
  songLength(songLength), 
  nextNodePtr(nullptr)
  {}
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:

  Playlist()
    : head(nullptr),tail(nullptr)
  {}

  Playlist()
  : head(nullptr), 
    tail(nullptr)
  {}

  ~Playlist(); // destructor

  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

