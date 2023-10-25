def main():
    card = get_card()
    print(card)


class Credit:
    def __init__(self, number):
        self.number = number
        self.ints = [int(x) for x in number[::-1]]
        self.length = len(number)

    def __bool__(self):
        if self.length > 16 or self.length < 12:
            return False

        total = 0
        for x in self.ints[1::2]:
            check = x * 2
            if check > 9:
                total += 1
                total += check % 10
            else:
                total += check

        for x in self.ints[::2]:
            total += x

        if total % 10 == 0:
            return True
        return False

    def _checkDigits(self, digits):
        for x in digits:
            if self.number[:2] == x:
                return True
        return False

    def isAmex(self):
        if self.length == 15 and self._checkDigits(["34", "37"]):
            return True
        return False

    def isMasterCard(self):
        if self.length == 16 and self._checkDigits(["51", "52", "53", "54", "55"]):
            return True
        return False

    def isVisa(self):
        if (self.length == 13 or self.length == 16) and self.number[0] == "4":
            return True
        return False

    def cardType(self):
        if not self:
            return "INVALID"

        if self.isAmex():
            return "AMEX"
        elif self.isMasterCard():
            return "MASTERCARD"
        elif self.isVisa():
            return "VISA"
        else:
            return "INVALID"

    def __str__(self):
        return self.cardType()

    def __repr__(self):
        return f"Credit({self.number})"


def get_card():
    "Returns list of integers on card reversed."

    number = input("Number: ")
    card = Credit(number)

    return card


if __name__ == "__main__":
    main()
