#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:" << endl;
  cin >> title;

  Playlist P;

  while(true) {
    P.PrintMenu(title);

    // Read commands until error or end-of-file
    // It is much better to read a string here than a character
    // because it will read a single "chunk" of characters and
    // we don't have to deal with problems reading a character
    // without a newline, or when we make a mistake and don't
    // prompt for something that we needed.
    string command;
    if (!(cin >> command)) break;

    // We support seven commands.  The Lab prompt says only
    // to prompt again on error... so we don't output any message
    // on a bad command
    if (command == "a") {
      P.AddSong("SD123","Peg","Steely Dan",237);
    } else if (command == "d") {
      P.RemoveSong();
    } else if (command == "c") {
      P.ChangePositionSong();
    } else if (command == "s") {
      P.OutputSongsByArtist();
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      P.OutputFullPlaylist();
    } else if (command == "q") {
      break;
    }
  }

  // If cin is in an error state (even end-of-file), then
  // something went wrong
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
