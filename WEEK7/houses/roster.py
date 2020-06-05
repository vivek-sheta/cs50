# TODO
from cs50 import SQL
from sys import argv


def main():
    if len(argv) != 2:
        print("Usage: python roster.py house_name")
        exit(1)

    open("students.db", "r").close()
    db = SQL("sqlite:///students.db")

    house_name = argv[1]
    data = []
    data = db.execute("SELECT first,last,middle,birth FROM students WHERE house = ? ORDER BY last,first", house_name)
    for row in data:
        print(row["first"], end=" ")
        if row["middle"] != None:
            print(row["middle"], end=" ")
        print(row["last"], end=",")
        print("born", row["birth"])


if __name__ == "__main__":
    main()
