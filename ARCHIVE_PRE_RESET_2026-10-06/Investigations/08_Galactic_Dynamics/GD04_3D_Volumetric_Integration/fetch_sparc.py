import urllib.request
import csv

def fetch_sparc():
    url = "https://raw.githubusercontent.com/wmmv2311/Dynamical-Classification-of-SPARC-Galaxies/master/SPARC_Morphological_Catalog.csv"
    try:
        urllib.request.urlretrieve(url, "sparc_raw.csv")
        print("Downloaded SPARC morphological catalog.")
    except Exception as e:
        print(f"Failed to fetch. Error: {e}")
        return False
    
    # Read the CSV to see what columns we have and convert to our format
    try:
        with open("sparc_raw.csv", "r") as f:
            reader = csv.DictReader(f)
            headers = reader.fieldnames
            print(f"Headers found: {headers}")
    except Exception as e:
        print(f"Failed to read. Error: {e}")
        return False
    return True

if __name__ == "__main__":
    fetch_sparc()
