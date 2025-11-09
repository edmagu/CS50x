import os
import re
from mutagen.easyid3 import EasyID3
from mutagen import File as MutagenFile

def safe_filename(name: str) -> str:
    """Sanitize filenames to remove unsafe characters."""
    return re.sub(r'[\\/*?:"<>|]', "", name).strip()

def organize_music(file_storage, upload_dir):
    """Organize uploaded music by genre, renaming properly."""
    filepath = os.path.join(upload_dir, file_storage.filename)
    file_storage.save(filepath)

    audio = MutagenFile(filepath, easy=True)
    artist = title = genre = "Unknown"

    if audio:
        artist = audio.get("artist", ["Unknown Artist"])[0]
        title = audio.get("title", ["Unknown Title"])[0]
        genre = audio.get("genre", ["Unknown Genre"])[0]

    artist = safe_filename(artist)
    title = safe_filename(title)
    genre = safe_filename(genre)

    # Create genre folder
    genre_dir = os.path.join(upload_dir, genre)
    os.makedirs(genre_dir, exist_ok=True)

    # Create new filename
    ext = os.path.splitext(file_storage.filename)[1]
    new_filename = f"{artist} - {title}{ext}"
    new_path = os.path.join(genre_dir, new_filename)

    os.rename(filepath, new_path)

    return {
        "artist": artist,
        "title": title,
        "genre": genre,
        "new_path": new_path
    }
