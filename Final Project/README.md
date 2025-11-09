# OrganizeMyMusic: Smart Music Organizer
#### Video Demo: <https://youtu.be/KWSbjdbCuQk>
#### Description:

OrganizeMyMusic is a web application that automatically organizes music files by genre.  
You can upload multiple `.mp3` or `.wav` files, and the app will read each file’s metadata (artist, title, and genre), rename them properly, and sort them into folders by genre.

The app is built with **Flask (Python)** for the backend and **Bootstrap 5** for the user interface.  
It uses the **Mutagen** library to extract information from audio files and then organizes them automatically in the `uploads` folder.

When you upload your music, OrganizeMyMusic:
1. Reads the file’s metadata (artist, title, and genre).
2. Renames the file to a clean format like `Artist - Song Title.mp3`.
3. Creates a folder for each genre (if it doesn’t exist already).
4. Moves each song into the correct genre folder.
5. Displays a results page showing all processed songs with their new names and locations.

If no files are uploaded, the app simply refreshes instead of giving an error.  
The interface supports drag-and-drop uploads, live progress bars, and a modern dark theme for an enjoyable experience.

**Tech Stack:**
- **Python 3.14**  
- **Flask** for web routing and backend logic  
- **Mutagen** for reading ID3 tags from audio files  
- **Bootstrap 5** and **CSS** for styling  
- **JavaScript (AJAX)** for handling uploads smoothly  

**Project Structure:**
Final Project/
├── app.py
├── music_utils.py
├── templates/
│ ├── index.html
│ └── results.html
├── static/
│ └── style.css
└── uploads/


**Usage:**
Run the app with:
flask run


Upload your songs, click “Upload & Organize,” and OrganizeMyMusic will instantly rename and sort them for you.

**Future Improvements:**
- Add a built-in music player on the results page  
- Detect genres automatically if metadata is missing  
- Allow exporting playlists or syncing with cloud storage

Created by **Elias Macero**  
For **CS50x 2025 Final Project**
