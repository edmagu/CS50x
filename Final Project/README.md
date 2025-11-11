# OrganizeMyMusic: Smart Music Organizer

#### Video Demo: <https://studio.youtube.com/video/KWSbjdbCuQk/edit>
#### Author: Elias Macero
#### GitHub: [@edmagu](https://github.com/edmagu)
#### Date: November 2025
#### City/Country: Milton, Canada

---

## Project Overview

**OrganizeMyMusic** is a Flask-based web application that automatically **organizes uploaded music files by genre**, renaming them cleanly using their embedded metadata (artist, title, and genre).  

Users can drag and drop or select `.mp3` and `.wav` files, and the app instantly sorts them into genre-specific folders, building auto-generated “playlists” that are neatly structured and ready to use.  

This project combines Python, Flask, and Mutagen to provide a practical tool that demonstrates file handling, metadata parsing, web development, and user-interface design — all wrapped in a professional, interactive experience.

---

## Features

### Upload & Organize
- Upload multiple audio files at once using a drag-and-drop or file picker interface.  
- Progress bar animation shows upload progress dynamically.  
- The app automatically:
  - Extracts **artist**, **title**, and **genre** tags from each file’s metadata.  
  - Renames the files using the format:  
    ```
    Artist - Title.mp3
    ```
  - Organizes the renamed files into folders by **genre**:
    ```
    uploads/
    ├── Rock/
    │   ├── Queen - Bohemian Rhapsody.mp3
    ├── Jazz/
    │   ├── Miles Davis - So What.mp3
    └── Unknown Genre/
        ├── Track 01.wav
    ```

### Results Dashboard
- After processing, a results page shows:
  - Artist  
  - Title  
  - Genre  
  - Organized file path  
- All data is displayed in a clean, responsive Bootstrap table.

### Error Handling
- If no files are uploaded, the app simply reloads the page (no crashes or error popups).  
- Missing metadata is handled gracefully with “Unknown” defaults.  

### Modern User Interface
- Sleek **dark-mode design** with gradient backgrounds, rounded panels, and glowing hover effects.  
- Built using **Bootstrap 5**, **Bootstrap Icons**, and custom **CSS animations** for an elegant, professional aesthetic.  
- Fully responsive across devices (desktop, tablet, mobile).

---

## Technical Implementation

### **Backend**
- **Language:** Python 3.14  
- **Framework:** Flask  
- **Modules Used:**
  - `mutagen` — reads and parses ID3 tags from audio files.  
  - `werkzeug` — secure file handling and path management.  
  - `flask`, `os`, `re`, `session` — app logic and routing.

### **Frontend**
- **HTML5**, **Bootstrap 5**, **JavaScript (AJAX)**, **CSS3**  
- Smooth file uploads handled asynchronously via AJAX (`XMLHttpRequest`) to `/upload`.  
- Responsive layout built with Bootstrap’s grid system and cards.

### **Project Structure**
Final Project/
│
├── app.py # Flask routes and app configuration
├── music_utils.py # Handles metadata extraction and file organization
│
├── templates/
│ ├── index.html # Upload page
│ └── results.html # Organized results display
│
├── static/
│ └── style.css # Custom dark theme and UI enhancements
│
└── uploads/ # Automatically generated folders and files


---

## How It Works

1. The user uploads one or more `.mp3` or `.wav` files.
2. Flask receives the files and stores them temporarily in `/uploads`.
3. For each file:
   - The `mutagen` library reads its **ID3 metadata**.
   - Artist, Title, and Genre fields are extracted.
   - A sanitized, human-readable filename is generated.
   - The file is moved into a folder based on its genre.
4. Flask renders a `/results` page showing the organized collection.

---

## Design Choices

- **Flask** was chosen for its simplicity, speed, and clear separation between logic and presentation.  
- **Mutagen** was selected for metadata handling because it’s reliable and supports multiple audio formats.  
- **Bootstrap 5** was used to achieve a professional, responsive design quickly.  
- The app intentionally avoids external APIs, ensuring it works offline and remains self-contained.  
- Clean error handling and redirection prevent confusing messages for non-technical users.