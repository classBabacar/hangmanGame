#include "TheGame.h"
#include "colors.h"

// Function : DisplayHiddenWord
// Purpose : To display the word as a combination of (-) example:dog as  (---)
int Thegame::displayHiddenWord() {
  if (topic != "") {
    cout << "\tThe Topic is : " << topic << endl;
    cout << endl;
  }
  int showncounter = 0;
  for (int i = 0; i < (int)response.length(); i++) {
    if (isalnum(response[i])) {
      shown = shown + "-"; // keeping track of user letters
      showncounter++;
    } else {
      shown = shown + response[i]; // If the character is not a letter
    }
  }
  cout << "\t" << shown << endl;
  return showncounter; // this return is important we can determine the size of the unknown the dashes
}

// function : TryLetters
// purpose : the bread and butter of hangman guessing the letters
void Thegame::tryLetters() {

  bool loop = true;
  // going to be used to match letters in word
  int showncounter = displayHiddenWord(); // in function display hidden word that return

  while (loop) {
    bool tracker = false; // used to keep track of the tries 
    int showntracker = 0; // this is used to keep track of the revised hashes to win the game

    char letter;
    cout << "\tWhat letter do you think is here? or enter (?) to leave" << endl;
    cout << "\t";
    cin >> letter;

    if (letter == '?') // leaving
    {
      loop = false;
    } else if (checkSet( mySet, letter)) // checking if the letter hasn't been used before
    {
      mySet.insert(letter); // input letter into set

      for (int b = 0; b < (int)response.size(); b++) {
        if (toupper(letter) == toupper(response[b])) {
          shown[b] = tolower(letter); //
          tracker = true; // to capture if that letter is in the word or not
        }
      }
    } else {
      cout << RED << "\tThis letter has been used before" << endl;
      tracker = true;
      cout << WHITE;
    }

    if (tracker == false) // if no letters matched the string
    {
      addTries();
      hangmandrawing();
    }

    if (shown == response) // if you hit the last step in guessing letter
    {
      loop = false;
      cout << "\tSecret Word: " << response << endl;
      cout << "\tCONGRATS YOU WIN!!!" << endl;
      cout << "\tTry the game again... Thank you" << endl;
      resetword();
    } else if (tries > 0 && showntracker != 0 && shown != response) {
      cout << "\tYou have " << tries << " tries left." << endl;
    }
    cout << "\t" << shown << endl;
    if (tries == 0) {
      loop = false;
      cout << "\tSorry you lose" << endl;
      cout << "\tTHE SECRET WORD WAS: " << response << endl;
      cout << "\tTry the game again." << endl;
      resetword();

      cout << endl;
      cout << endl;
    }
  }
}

// function : AiWord
// purpose : to generate a random word using files
string Thegame::AiWord() {
  resetword();
  vector<string> theVector;
  ifstream inFile;
  inFile.open("words.txt");

  srand(time(NULL));
  int counter = 0; // counter used to find the size of the file
  string catcher;
  while (inFile >> catcher) // counting words in file
  {
    theVector.push_back(catcher); // puts it in a vector
    counter++;                    // to keep track of the total in that file
  }
  int random = rand() % counter;
  string word = theVector.at(random);
  return word;
}

// function: checkSet
// purpose : to figure out if a word is repeated when they are guessing
bool Thegame::checkSet(set<char> mySet, char x) {
  set<char>::iterator it;
  for (it = mySet.begin(); it != mySet.end(); ++it) {
    if (*it == x) {
      return false;
    }
  }
  return true;
}

// function : storetheword
// purpose : storing the secret word
// simply placing the secret phrase in a private variable
void Thegame::storetheword(string x) {
  response = x;
  while (response == "") // If user enters a empty string
  {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    cout << "Invalid phrase try another word :" << endl;
    cout << "\t";
    getline(cin, response);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }

  for (int i = 0; i < (int)response.size(); ++i) {
    response[i] = tolower(response[i]);
  }
}

void Thegame::setTopic(string x) { topic = x; }

// function : resetWord
// purpose : Refreshes everything to a new game
void Thegame::resetword() {
  mySet.clear();
  response = "";
  shown = "";
  topic = "";
  tries = 7;
}

void Thegame::addTries() { tries--; }

void Thegame::hangmandrawing() {
  if (tries == 6 || tries == 7) {
    cout << "\t ___________" << endl;
    cout << "\t|        |" << endl;
    cout << "\t|         " << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  } else if (tries == 5) {
    cout << "\t___________" << endl;
    cout << "\t|         |" << endl;
    cout << "\t|         0 " << endl;
    cout << "\t|______________" << endl;
    cout << endl;

  } else if (tries == 4) {
    cout << "\t___________" << endl;
    cout << "\t|         |" << endl;
    cout << "\t|       \\ 0 " << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  } else if (tries == 3) {
    cout << "\t ___________" << endl;
    cout << "\t|         |" << endl;
    cout << "\t|       \\ 0 /" << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  } else if (tries == 2) {
    cout << "\t ___________" << endl;
    cout << "\t|        |" << endl;
    cout << "\t|      \\ 0 /" << endl;
    cout << "\t|        |" << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  } else if (tries == 1) {
    cout << "\t ___________" << endl;
    cout << "\t|         |" << endl;
    cout << "\t|       \\ 0 /" << endl;
    cout << "\t|         | " << endl;
    cout << "\t|        /  " << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  } else {
    cout << "\t ___________" << endl;
    cout << "\t|         |" << endl;
    cout << "\t|       \\ 0 /" << endl;
    cout << "\t|         | " << endl;
    cout << "\t|        / \\ " << endl;
    cout << "\t|______________" << endl;
    cout << endl;
  }
}
