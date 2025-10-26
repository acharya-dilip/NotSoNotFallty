

# NotSoNotFallty
NotSoNotFallty is a GUI Client for git for all the people who're all scared of the CLI ooooOOOoo SCAWYYY!! <br>
Equiped with the ability to post local commits to remote pushes all while with a fall theme <br>
What's better than commiting to git? Commiting to git in the comfort of fall!!

# How to use?
- Navigate towards the Project Directory on the Navigate to project window
- Create a new gh repository by clicking the ➕ button on the header and open the create gh repo window
- Proceed after you've selected your directory
- Code your project and when you want to commit enter your commit title and commit description in the NotSoNotFallty window
- Click the globe button on the header of NotSoNotFallty window to open the push to remote window
- Enter the branch you want to commit to and press the Push Button to commit to your repository
- Also you can click the 🛠️ button to open the config window where you can edit your remote repo url and git credentials
- Add your github username and Personal Access token and you're free to user NotSoNotFallty however you deem fit
# LIUNX BUILD INSTRUCTIONS

| FOR DEBIAN/UBUNTU                | For ARCH                  |      
|----------------------------------|---------------------------|      
| Install Dependencies             | Install Dependencies      |      
| sudo apt install gtk             | sudo pacman -S gtk        |
| sudo apt install curl            | sudo pacman -S curl       |
| sudo apt install build-essential | sudo pacman -S base-devel |
| sudo apt install cmake           | sudo pacman -S cmake      |
| sudo apt install git             | sudo pacman -S git        |
| sudo apt install gh-cli          | sudo pacman -S gh-cli     |  
### Clone into the Github repo

| Command                                                       |
|---------------------------------------------------------------|
| git clone https://github.com/acharya-dilip/NotSoNotFallty.git |
### Navigate to project directory
| Command           |
|-------------------|
| cd NotSoNotFallty |

###  Execute the Build Commands
| Commands   |
|----------------------------|
| cmake ..                   |
| cmake --build .            |

### Run the Program

| Command          |
|------------------|
| ./NotSoNotFallty |


