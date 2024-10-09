#include "Playlist.h"

void Playlist::PrintMenu(const string& title) const {
  cout << "print menu " << title << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  // PROFPAT: This is a stub.  You'll remove it and put in code for a
  // PROFPAT: real insert here.
  cout << "add song" << endl;
}
    
void Playlist::RemoveSong() {
  cout << "remove song" << endl;
}
    
void Playlist::ChangePositionSong() {
  cout << "change position song" << endl;
}
    
void Playlist::OutputSongsByArtist() const {
  cout << "output songs by artist" << endl;
}
    
void Playlist::OutputTotalTime() const {
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
  }
  cout << "output total time" << endl;
}

void Playlist::OutputFullPlaylist() const {
  cout << "Playlist is empty" << endl;
}
    

