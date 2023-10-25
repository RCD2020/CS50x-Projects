def main():
    change = get_float("Change owed: ", False, 0)
    change = int(change * 100)
    coins = 0
    for x in (25, 10, 5, 1):
        fit = change // x
        if fit > 0:
            coins += fit
            change -= fit * x

    print(coins)


class InputError(Exception):
    pass


def get_float(message, feedback=True, minRange=None, maxRange=None):
    "Forces a float input. Input the question to ask the user."

    while True:
        floaty = input(message)

        try:
            floaty = float(floaty)

            if minRange != None:
                if floaty < minRange:
                    raise InputError

            if maxRange != None:
                if floaty > maxRange:
                    raise InputError

            return floaty
        except:
            if feedback:
                print("Invalid input, looking for a float.")


if __name__ == "__main__":
    main()
