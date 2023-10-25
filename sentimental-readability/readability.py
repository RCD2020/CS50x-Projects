def main():
    text = input("Text: ")
    words = 1
    sentences = 0
    letters = 0

    for letter in text:
        if letter == " ":
            words += 1
        elif letter in ".!?":
            sentences += 1
        elif letter.upper() in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            letters += 1

    l = letters / words * 100
    s = sentences / words * 100
    index = 0.0588 * l - 0.296 * s - 15.8 + 0.5

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(index)}")


if __name__ == "__main__":
    main()
