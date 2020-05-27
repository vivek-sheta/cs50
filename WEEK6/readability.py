def main():
    word = 1
    sentences = 0
    letter = 0
    paragraph = input("Text: ")
    print()

    for i in paragraph:
        if i.isalpha():
            letter += 1
        if i == '.' or i == '?' or i == '!':
            sentences += 1
        if i == ' ':
            word += 1

    i = 0.0588 * (100 * letter / word) - 0.296 * (100 * sentences / word) - 15.8
    print(f"{i} {letter} {word} {sentences}")
    if i >= 1 and i <= 16:
        print(f"Grade: {round(i)}")
    elif i > 16:
        print("Grade: 16+")
    else:
        print("Before Grade 1")


main()
