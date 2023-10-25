def main():
    height = get_int("Height: ", False, 1, 8)

    for x in range(1, height + 1):
        print(" " * (height - x), end="")
        print("#" * x)


class InputError(Exception):
    pass


def get_int(message, feedback=True, minRange=None, maxRange=None):
    "Forces an integer input. Input the question to ask the user."

    while True:
        inty = input(message)
        try:
            inty = int(inty)

            if minRange != None:
                if inty < minRange:
                    raise InputError

            if maxRange != None:
                if inty > maxRange:
                    raise InputError

            return inty
        except:
            if feedback:
                print("Invalid input, looking for an integer.")


if __name__ == "__main__":
    main()
