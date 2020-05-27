from sys import argv
import csv


def get_count_of_each_STR(data, pair):
    ans = [0] * len(data)
    # [AATTTT.....] dna(data) size array with value [000000....]

    # range(start, stop, step) here starting from end and decrease by -1 untill len(data) is not -1
    # Like for(i = strlen(data) - strlen(pair) ;  i > -1 ; i--)
    for i in range(len(data) - len(pair), -1, -1):
        if data[i: i + len(pair)] == pair:
            if i + len(pair) > len(data) - 1:
                ans[i] = 1
            else:
                ans[i] = ans[i + len(pair)] + 1
    return max(ans)


def find_match(path, sequence):
    with open(path) as csv_file:
        reader = csv.reader(csv_file)
        next(reader)
        for row in reader:
            person = row[0]
            values = [int(val) for val in row[1:]]
            if values == sequence:
                print(person)
                return
        print("No match")


def main():
    if len(argv) != 3:
        print("Usage: python dna.py  data.csv  sequense.txt")
        exit(1)
        
    csv_file_path = argv[1]
    # if Error in open csv_file_path python interpreter will close the file
    with open(csv_file_path) as csv_file:
        reader = csv.reader(csv_file)
        all_sequences = next(reader)[1:]
        
    text_file_path = argv[2]
    with open(text_file_path) as txt_file:
        s = txt_file.read()
        sequences = [get_count_of_each_STR(s, seq) for seq in all_sequences]
        find_match(csv_file_path, sequences)


if __name__ == "__main__":
    main()
