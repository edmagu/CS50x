import csv
import sys


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a list of dictionaries
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        database = list(reader)

    # Read DNA sequence file into a string
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Extract the list of STRs from the CSV header (all columns except 'name')
    str_list = reader.fieldnames[1:]

    # Compute the longest run of each STR in the DNA sequence
    str_counts = {}
    for STR in str_list:
        str_counts[STR] = longest_match(sequence, STR)

    # Compare STR counts against each person in the database
    for person in database:
        match = True
        for STR in str_list:
            if int(person[STR]) != str_counts[STR]:
                match = False
                break
        if match:
            print(person["name"])
            sys.exit(0)

    print("No match")


def longest_match(sequence, subsequence):
    """
    Returns length of the longest run of subsequence in sequence.
    Provided by CS50 staff.
    """
    longest_run = 0
    subseq_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0
        # Check for consecutive runs of the subsequence starting at i
        while True:
            start = i + count * subseq_len
            end = start + subseq_len
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
