# TODO
import csv
from cs50 import SQL
from sys import argv


def main():
    if len(argv) != 2:
        print("Usage: python import.py character.csv")
        exit(1)
    elif not argv[1].endswith(".csv"):
        print("Usage: python import.py character.csv")
        exit(1)

    open("students.db", "w").close()
    db = SQL("sqlite:///students.db")

    db.execute("CREATE TABLE students (first TEXT NOT NULL, middle TEXT, last TEXT NOT NULL, house TEXT NOT NULL, birth NUMERIC) ")

    file_name = argv[1]

    with open(file_name, "r") as csv_file:
        reader = csv.DictReader(csv_file)

        for row in reader:
            arr = []
            arr.append(row["name"].split())
            name = arr[0]
            if len(name) == 2:
                db.execute("INSERT INTO students(first, last, house, birth) VALUES(?,?,?,?)",name[0], name[1], row["house"], row["birth"])
            elif len(name) == 3:
                db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?,?,?,?,?)",name[0], name[1], name[2], row["house"], row["birth"])


if __name__ == "__main__":
    main()
